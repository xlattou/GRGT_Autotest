// ListInsDocSolution.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListInsDocSolution.h"
#include "File_UUTInfo.h"
#include "InsDocTemplete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListInsDocSolution

CListInsDocSolution::CListInsDocSolution()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
	m_strSolutionPath = "";
	m_strKind = "";
	m_strModel = "";
}

CListInsDocSolution::~CListInsDocSolution()
{
}


BEGIN_MESSAGE_MAP(CListInsDocSolution, CListCtrlCl)
	//{{AFX_MSG_MAP(CListInsDocSolution)	
	ON_CBN_SETFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnSetfocusCombo)		
	ON_CBN_KILLFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnKillfocusCombo)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListInsDocSolution message handlers
void CListInsDocSolution::PreSubclassWindow() 
{
	m_combo.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSBASIC_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::PreSubclassWindow();
}

void CListInsDocSolution::OnSetfocusCombo()
{
	CFile_UUTInfo file_UUTInfo;
	vector<FileInfo> vFileinfo1;
	file_UUTInfo.GetSolutionList(m_strKind, m_strModel, &vFileinfo1);
	while(m_combo.DeleteString(0)!=CB_ERR);

	for(int i = 0; i < vFileinfo1.size(); i++)
	{
		m_combo.AddString(vFileinfo1[i].m_strFileName);
	}

	m_strEditText = GetItemText(m_nEditItem, m_nEditSubItem);
	CString str1;

	for(int i = 0; i < m_combo.GetCount(); i++)
	{
		m_combo.GetLBText(i, str1);
		if(m_strEditText == str1)
		{
			m_combo.SetCurSel(i);
			break;
		}
	}
}

void CListInsDocSolution::OnKillfocusCombo() 
{
	int nI = m_combo.GetCurSel();
	if(nI > -1)
	{
		m_combo.GetLBText(nI, m_strEditText);
		SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	}
	m_combo.ShowWindow(SW_HIDE);
}

void CListInsDocSolution::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrlCl::OnLButtonDblClk(nHitTest, point);

	if(m_strKind == "" || m_strModel == "")
		return;
	if(((CInsDocTemplete*)GetParent())->m_nChangeState != 2)
		return;

	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		if(m_nEditSubItem == 1)
		{
			CRect rectCell;
			this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
			m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
			CPoint point1 = rectCell.BottomRight();
			point1.y += 150;
			rectCell.SetRect(rectCell.TopLeft(), point1);
			m_combo.MoveWindow(&rectCell, TRUE);
			m_combo.SetFocus();
			m_combo.ShowWindow(SW_SHOW);
		}
	}
}

void CListInsDocSolution::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::OnVScroll(nSBCode, nPos, pScrollBar);
}
