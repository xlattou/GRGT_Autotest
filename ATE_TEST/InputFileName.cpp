// InputFileName.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InputFileName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputFileName dialog


CInputFileName::CInputFileName(CWnd* pParent /*=NULL*/)
	: CDialog(CInputFileName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputFileName)
	m_configFileName = _T("");
	//}}AFX_DATA_INIT
	m_strTile = "请输入文件名";
}


void CInputFileName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputFileName)
	DDX_Text(pDX, IDC_EDIT1, m_configFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputFileName, CDialog)
	//{{AFX_MSG_MAP(CInputFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputFileName message handlers

void CInputFileName::OnOK() 
{
	// TODO: Add extra validation here
	
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(m_configFileName);
	CDialog::OnOK();
}

BOOL CInputFileName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_strTile);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
