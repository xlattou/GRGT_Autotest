// List_Lua_Pic.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "List_Lua_Pic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CList_Lua_Pic

CList_Lua_Pic::CList_Lua_Pic()
{
	m_nEditItem =  -1;
	m_nEditSubItem = -1;
}

CList_Lua_Pic::~CList_Lua_Pic()
{
}


BEGIN_MESSAGE_MAP(CList_Lua_Pic, CListCtrl)
	//{{AFX_MSG_MAP(CList_Lua_Pic)	
	ON_EN_SETFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnSetfocusEdit)		
	ON_EN_KILLFOCUS(IDC_EDIT_INSTEMP_CONDITION, OnKillfocusEdit)
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CList_Lua_Pic message handlers

void CList_Lua_Pic::PreSubclassWindow() 
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSTEMP_CONDITION);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);
	
	CListCtrl::PreSubclassWindow();
}

void CList_Lua_Pic::OnSetfocusEdit()
{
	if(m_nEditItem ==  -1 || m_nEditSubItem == -1)
		m_Edit.ShowWindow(SW_HIDE);
	CString str1, strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
	str1 = strEditText.Right(4);
	str1.MakeLower();
	if(str1 == ".lua")
		strEditText = strEditText.Left(strEditText.GetLength() - 4);
	m_Edit.SetWindowText(strEditText);
}

void CList_Lua_Pic::OnKillfocusEdit() 
{
	m_nEditItem =  -1;
	m_nEditSubItem = -1;
	m_Edit.ShowWindow(SW_HIDE);
}

void CList_Lua_Pic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_nEditItem =  -1;
	m_nEditSubItem = -1;
	m_Edit.ShowWindow(SW_HIDE);	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CList_Lua_Pic::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonDblClk(nFlags, point);
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if(m_nEditSubItem == 3)
	{
		if (lvhti.flags & LVHT_ONITEMLABEL)
		{
			CRect rectCell;
			this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
			
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1); 
			m_Edit.ShowWindow(SW_SHOW);
		}
	}
}
