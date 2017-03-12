// ListTestLuaAddFun.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListTestLuaAddFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTestLuaAddFun

CListTestLuaAddFun::CListTestLuaAddFun()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
}

CListTestLuaAddFun::~CListTestLuaAddFun()
{
}


BEGIN_MESSAGE_MAP(CListTestLuaAddFun, CListCtrl)
	//{{AFX_MSG_MAP(CListTestLuaAddFun)
		ON_EN_SETFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnSetfocusEdit)		
		ON_EN_KILLFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnKillfocusEdit)	
		ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListTestLuaAddFun::PreSubclassWindow() 
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSTEMP_CONDITION);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);

	CListCtrl::PreSubclassWindow();
}

void CListTestLuaAddFun::OnSetfocusEdit()
{
	m_Edit.SetWindowText(m_strEditText);
}

void CListTestLuaAddFun::OnKillfocusEdit() 
{
	m_Edit.GetWindowText(m_strEditText);
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_Edit.ShowWindow(SW_HIDE);
}

void CListTestLuaAddFun::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrl::OnLButtonDblClk(nHitTest, point);
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if(m_nEditSubItem != 2)
		return;
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		CRect rectCell;
		this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
		m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
		m_Edit.MoveWindow(&rectCell, TRUE);
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1); 
		m_Edit.ShowWindow(SW_SHOW);
	}
}

void CListTestLuaAddFun::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Edit.ShowWindow(SW_HIDE);	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
