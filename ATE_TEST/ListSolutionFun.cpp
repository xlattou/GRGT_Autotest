// ListSolutionFun.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListSolutionFun.h"
#include "InsDocSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListSolutionFun

CListSolutionFun::CListSolutionFun()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
}

CListSolutionFun::~CListSolutionFun()
{
}


BEGIN_MESSAGE_MAP(CListSolutionFun, CListCtrlCl)
	//{{AFX_MSG_MAP(CListSolutionFun)
	ON_CBN_SETFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnSetfocusCombo)		
	ON_CBN_KILLFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnKillfocusCombo)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_CLEAR_CELL, OnMenuClearCell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListSolutionFun message handlers
void CListSolutionFun::PreSubclassWindow() 
{
	m_combo.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSBASIC_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::PreSubclassWindow();
}

void CListSolutionFun::OnSetfocusCombo()
{
	while(m_combo.DeleteString(0)!=CB_ERR);
	if(m_nEditSubItem == 1)
	{
		m_combo.AddString(m_srtDll);
	}
	if(m_nEditSubItem == 2)
	{
		for(int i = 0; i < m_strFuncArray.GetSize(); i++)
		{
			m_combo.AddString(m_strFuncArray[i]);
		}
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

void CListSolutionFun::OnKillfocusCombo() 
{
	int nI = m_combo.GetCurSel();
	if(nI > -1)
	{
		m_combo.GetLBText(nI, m_strEditText);
		SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
		if(m_nEditSubItem == 2)
			SetItemText(m_nEditItem, 1, m_srtDll);
	}
	m_combo.ShowWindow(SW_HIDE);
}

void CListSolutionFun::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrlCl::OnLButtonDblClk(nHitTest, point);

	if(((CInsDocSolution*)GetParent())->m_nChangeState != 2)
		return;

	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		if(m_nEditSubItem > 0)
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

void CListSolutionFun::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CListSolutionFun::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	CListCtrlCl::OnRButtonDown(nFlags, point);
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		if(m_nEditSubItem > 0)
		{
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_SOLUTION));

			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			ClientToScreen(&point);

			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
	}
}

void CListSolutionFun::OnMenuClearCell() 
{
	SetItemText(m_nEditItem, m_nEditSubItem, "");
	if(m_nEditSubItem == 1)
		SetItemText(m_nEditItem, 2, "");
}
