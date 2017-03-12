// AddKind.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "AddKind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddKind dialog


CAddKind::CAddKind(CWnd* pParent /*=NULL*/)
	: CDialog(CAddKind::IDD, pParent)
{
	m_nHasEngine = -1;	
	m_strTitle = "添加设备类型";
	m_strHasEngine = "根据已有驱动引擎及其配置文件添加";
}


void CAddKind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddKind)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddKind, CDialog)
	//{{AFX_MSG_MAP(CAddKind)
	ON_BN_CLICKED(IDC_BUTTON_HAS_ENGINE, OnButtonHasEngine)
	ON_BN_CLICKED(IDC_BUTTON_HAS_NO_ENGINE, OnButtonHasNoEngine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddKind message handlers

void CAddKind::OnButtonHasEngine() 
{
	m_nHasEngine = 1;
	OnOK();
}

void CAddKind::OnButtonHasNoEngine() 
{
	m_nHasEngine = 0;
	OnOK();
}

BOOL CAddKind::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_strTitle);
	((CButton*)GetDlgItem(IDC_BUTTON_HAS_ENGINE))->SetWindowText(m_strHasEngine);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
