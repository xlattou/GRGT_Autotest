// InsTempAutoFillRow.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsTempAutoFillRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsTempAutoFillRow dialog


CInsTempAutoFillRow::CInsTempAutoFillRow(CWnd* pParent /*=NULL*/)
	: CDialog(CInsTempAutoFillRow::IDD, pParent)
{
	m_nRow = 0;
}


void CInsTempAutoFillRow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsTempAutoFillRow)
	DDX_Control(pDX, IDC_EDIT_FILL_ROW, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsTempAutoFillRow, CDialog)
	//{{AFX_MSG_MAP(CInsTempAutoFillRow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsTempAutoFillRow message handlers

void CInsTempAutoFillRow::OnOK() 
{
	CString str1;
	m_Edit.GetWindowText(str1);
	m_nRow = atoi(str1);
	CDialog::OnOK();
}
