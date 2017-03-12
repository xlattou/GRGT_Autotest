// ListInsBasic.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListInsBasic.h"
#include "InsDocBasic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListInsBasic

CListInsBasic::CListInsBasic()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
}

CListInsBasic::~CListInsBasic()
{
}


BEGIN_MESSAGE_MAP(CListInsBasic, CListCtrlCl)
	//{{AFX_MSG_MAP(CListInsBasic)
		ON_EN_SETFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnSetfocusEdit)		
		ON_EN_KILLFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnKillfocusEdit)		
		ON_CBN_SETFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnSetfocusCombo)		
		ON_CBN_KILLFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnKillfocusCombo)
		ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListInsBasic message handlers

void CListInsBasic::PreSubclassWindow() 
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSBASIC_LIST_CUSTOM);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);

	m_combo.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSBASIC_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.AddString("Test");
	m_combo.AddString("Control");
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::PreSubclassWindow();
}

void CListInsBasic::OnSetfocusEdit()
{
	m_Edit.SetWindowText(m_strEditText);
}

void CListInsBasic::OnKillfocusEdit() 
{
	m_Edit.GetWindowText(m_strEditText);
	if(m_nEditSubItem == 0)
	{
		int nText = 0;
		nText = atoi(m_strEditText);
		if(nText < 0)
			nText = 0;
		m_strEditText.Format("%d", nText);
	}
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_Edit.ShowWindow(SW_HIDE);
}

void CListInsBasic::OnSetfocusCombo()
{
	if(m_strEditText == "Control")
		m_combo.SetCurSel(1);
	else
		m_combo.SetCurSel(0);
}

void CListInsBasic::OnKillfocusCombo() 
{
	if(m_combo.GetCurSel() == 1)
		m_strEditText = "Control";
	else
		m_strEditText = "Test";
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_combo.ShowWindow(SW_HIDE);
}

void CListInsBasic::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrlCl::OnLButtonDblClk(nHitTest, point);
	if(((CInsDocBasic*)GetParent())->m_nSaveState != 2)
		return;
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
		if(m_nEditSubItem == 4)
		{
			CPoint point1 = rectCell.BottomRight();
			point1.y += 60;
			rectCell.SetRect(rectCell.TopLeft(), point1);
			m_combo.MoveWindow(&rectCell, TRUE);
			m_combo.SetFocus();
			m_combo.SetCurSel(0); 
			m_combo.ShowWindow(SW_SHOW);
		}
		else if(m_nEditSubItem == 1 || m_nEditSubItem == 2)
		{
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1); 
			m_Edit.ShowWindow(SW_SHOW);
		}
	}
}

void CListInsBasic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Edit.ShowWindow(SW_HIDE);
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::OnVScroll(nSBCode, nPos, pScrollBar);
}
