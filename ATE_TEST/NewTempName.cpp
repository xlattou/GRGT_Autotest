// NewTempName.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "NewTempName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewTempName dialog


CNewTempName::CNewTempName(CWnd* pParent /*=NULL*/)
	: CDialog(CNewTempName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewTempName)
	m_newTempName = _T("");
	//}}AFX_DATA_INIT
}


void CNewTempName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewTempName)
	DDX_Text(pDX, IDC_EDIT1, m_newTempName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewTempName, CDialog)
	//{{AFX_MSG_MAP(CNewTempName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTempName message handlers

void CNewTempName::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CDialog::OnOK();
}
