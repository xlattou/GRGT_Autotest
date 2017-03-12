// ItemEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ItemEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CItemEdit

CItemEdit::CItemEdit()
{
}

CItemEdit::~CItemEdit()
{
}


BEGIN_MESSAGE_MAP(CItemEdit, CEdit)
//{{AFX_MSG_MAP(CItemEdit)
ON_WM_WINDOWPOSCHANGING()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemEdit message handlers

void CItemEdit::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	lpwndpos->x = m_iXPos;
	CEdit::OnWindowPosChanging(lpwndpos);
	
	// TODO: Add your message handler code here
	
}
