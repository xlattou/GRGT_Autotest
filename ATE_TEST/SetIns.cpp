// SetIns.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "SetIns.h"
#include "AccessDB_Ope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetIns dialog


CSetIns::CSetIns(CWnd* pParent /*=NULL*/)
	: CDialog(CSetIns::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetIns)
	m_strAddress = _T("");
	m_strChann = _T("");
	m_strModel = _T("");
	m_strInsName = _T("");
	m_strManu = _T("");
	m_strSNumber = _T("");
	//}}AFX_DATA_INIT
}


void CSetIns::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetIns)
	DDX_Control(pDX, IDC_COMBO_INSKIND, m_Cb_InsKind);
	DDX_Control(pDX, IDC_COMBO_INSDRIVER, m_Cb_InsDriver);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_strChann);
	DDX_Text(pDX, IDC_EDIT_INSMODEL, m_strModel);
	DDX_Text(pDX, IDC_EDIT_INSNAME, m_strInsName);
	DDX_Text(pDX, IDC_EDIT_MANU, m_strManu);
	DDX_Text(pDX, IDC_EDIT_SNumber, m_strSNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetIns, CDialog)
	//{{AFX_MSG_MAP(CSetIns)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetIns message handlers

CSetIns::CSetIns(int intMark_Control, int intNodeID,CWnd* pParent)
  	: CDialog(CSetIns::IDD, pParent)
{
	m_intMark=intMark_Control; //控制标志位，0=创建 1=修改
	m_intNodeID=intNodeID; //树节点ID	

}


BOOL CSetIns::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		




	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CSetIns::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_Cb_InsDriver.GetLBText(m_Cb_InsDriver.GetCurSel(),m_strDriveName);
	CDialog::OnOK();
}
