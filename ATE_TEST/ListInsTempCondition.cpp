// ListInsTempCondition.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListInsTempCondition.h"
#include "Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListInsTempCondition

CListInsTempCondition::CListInsTempCondition()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";

	char* s=new char[MAX_PATH];    
	if(!GetModuleFileName(NULL,s,MAX_PATH))
	{
		AfxMessageBox("获取Lua脚本关键字配置失败!");
		delete []s;
		return;
	}
    (_tcsrchr(s,_T('\\')))[0] = 0;  //去掉ATE_TEST.exe
	CString strPath(s);
	delete[] s;
	strPath += "\\测试条件关键字配置表.ini";
	CIni ini1;
	ini1.SetINIPth(strPath);
	m_strTypeArray.RemoveAll();
	ini1.GetKeys(m_strTypeArray, "Condition");

	m_strUnitArray.RemoveAll();
	ini1.GetKeys(m_strUnitArray, "Unit");
}

CListInsTempCondition::~CListInsTempCondition()
{
}


BEGIN_MESSAGE_MAP(CListInsTempCondition, CListCtrl)
	//{{AFX_MSG_MAP(CListInsTempCondition)
		ON_EN_SETFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnSetfocusEdit)		
		ON_EN_KILLFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnKillfocusEdit)
		ON_CBN_SETFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnSetfocusCombo)		
		ON_CBN_KILLFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnKillfocusCombo)
		ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListInsTempCondition::PreSubclassWindow() 
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSTEMP_CONDITION);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);

	m_combo.Create(CBS_DROPDOWN | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSBASIC_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.ShowWindow(SW_HIDE);

	CListCtrl::PreSubclassWindow();
}

void CListInsTempCondition::OnSetfocusEdit()
{
	m_Edit.SetWindowText(m_strEditText);
}

void CListInsTempCondition::OnKillfocusEdit() 
{
	m_Edit.GetWindowText(m_strEditText);
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_Edit.ShowWindow(SW_HIDE);
}

void CListInsTempCondition::OnSetfocusCombo()
{
	while(m_combo.DeleteString(0)!=CB_ERR);
	if(m_nEditSubItem == 0)
	{
		for(int i = 0; i < m_strTypeArray.GetSize(); i++)
		{
			m_combo.AddString(m_strTypeArray[i]);
		}
	}
	if(m_nEditSubItem == 3)
	{
		for(int i = 0; i < m_strUnitArray.GetSize(); i++)
		{
			m_combo.AddString(m_strUnitArray[i]);
		}
	}

	m_combo.SetWindowText(m_strEditText);
}

void CListInsTempCondition::OnKillfocusCombo() 
{
	m_combo.GetWindowText(m_strEditText);
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_combo.ShowWindow(SW_HIDE);
}

void CListInsTempCondition::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrl::OnLButtonDblClk(nHitTest, point);
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		CRect rectCell;
		this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
		m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
		if(m_nEditSubItem == 0 || m_nEditSubItem == 3)
		{
			rectCell.bottom += 100;
			m_combo.MoveWindow(&rectCell, TRUE);
			m_combo.SetFocus();
			m_combo.ShowWindow(SW_SHOW);
		}
		else
		{
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1); 
			m_Edit.ShowWindow(SW_SHOW);
		}
	}
}

void CListInsTempCondition::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Edit.ShowWindow(SW_HIDE);	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CListInsTempCondition::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CListCtrl::OnLButtonDown(nFlags, point);
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		CRect rectCell;
		this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
		m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
		if(m_nEditSubItem == 0 || m_nEditSubItem == 3)
		{
			rectCell.bottom += 100;
			m_combo.MoveWindow(&rectCell, TRUE);
			m_combo.SetFocus();
			m_combo.ShowWindow(SW_SHOW);
		}
		else
		{
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1); 
			m_Edit.ShowWindow(SW_SHOW);
		}
	}
}
