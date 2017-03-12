// ListInsSolution.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListInsSolution.h"
#include "InsDocSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListInsSolution

CListInsSolution::CListInsSolution()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
}

CListInsSolution::~CListInsSolution()
{
}


BEGIN_MESSAGE_MAP(CListInsSolution, CListCtrlCl)
	//{{AFX_MSG_MAP(CListInsSolution)
	ON_CBN_SETFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnSetfocusCombo)		
	ON_CBN_KILLFOCUS(IDC_COMBO_INSBASIC_LIST_CUSTOM, OnKillfocusCombo)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_CLEAR_CELL, OnMenuClearCell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListInsSolution::PreSubclassWindow() 
{
	m_combo.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSBASIC_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::PreSubclassWindow();
}

void CListInsSolution::OnSetfocusCombo()
{
	while(m_combo.DeleteString(0)!=CB_ERR);
	if(m_nEditSubItem == 1)
	{
		for(int i = 0; i < m_strLuaArray.GetSize(); i++)
		{
			m_combo.AddString(m_strLuaArray[i]);
		}
	}
	if(m_nEditSubItem == 2)
	{
		for(int i = 0; i < m_strPicArray.GetSize(); i++)
		{
			m_combo.AddString(m_strPicArray[i]);
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

void CListInsSolution::OnKillfocusCombo() 
{
	int nI = m_combo.GetCurSel();
	if(nI > -1)
	{
		m_combo.GetLBText(nI, m_strEditText);
		SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	}
	m_combo.ShowWindow(SW_HIDE);
}

void CListInsSolution::OnLButtonDblClk(UINT nHitTest, CPoint point) 
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
			point1.y += 360;
			rectCell.SetRect(rectCell.TopLeft(), point1);
			m_combo.MoveWindow(&rectCell, TRUE);
			m_combo.SetFocus();
			m_combo.ShowWindow(SW_SHOW);
		}
	}
}

void CListInsSolution::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CListInsSolution::OnRButtonDown(UINT nFlags, CPoint point) 
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

void CListInsSolution::OnMenuClearCell() 
{
	SetItemText(m_nEditItem, m_nEditSubItem, "");
}
