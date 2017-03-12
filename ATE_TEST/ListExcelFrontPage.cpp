// ListExcelFrontPage.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListExcelFrontPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListExcelFrontPage

CListExcelFrontPage::CListExcelFrontPage()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
}

CListExcelFrontPage::~CListExcelFrontPage()
{
}


BEGIN_MESSAGE_MAP(CListExcelFrontPage, CListCtrl)
	//{{AFX_MSG_MAP(CListExcelFrontPage)
		ON_EN_SETFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnSetfocusEdit)		
		ON_EN_KILLFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnKillfocusEdit)
		ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListExcelFrontPage message handlers

void CListExcelFrontPage::PreSubclassWindow() 
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSBASIC_LIST_CUSTOM);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);
	
	CListCtrl::PreSubclassWindow();
}

void CListExcelFrontPage::OnSetfocusEdit()
{
	m_Edit.SetWindowText(m_strEditText);
}

void CListExcelFrontPage::OnKillfocusEdit() 
{
	CString str1;
	m_Edit.GetWindowText(str1);
	m_strEditText = "";
	if(m_nEditSubItem == 1)
	{
		char ch1 = 0;
		for(int i = 0; i < str1.GetLength(); i++)
		{
			ch1 = str1[i];
			if((ch1 >= 'a' && ch1 <= 'z') || (ch1 >= 'A' && ch1 <= 'Z'))
				m_strEditText += ch1;
		}
		m_strEditText.MakeUpper();
	}
	else if(m_nEditSubItem == 2)
	{
		int nText = 0;
		nText = atoi(str1);
		if(nText > 0)
			m_strEditText.Format("%d", nText);
	}
	SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
	m_Edit.ShowWindow(SW_HIDE);
}

void CListExcelFrontPage::OnLButtonDblClk(UINT nHitTest, CPoint point) 
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
		if(m_nEditSubItem == 1 || m_nEditSubItem == 2)
		{
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1); 
			m_Edit.ShowWindow(SW_SHOW);
		}
	}
}
