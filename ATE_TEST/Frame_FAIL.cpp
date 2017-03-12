// Frame_FAIL.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frame_FAIL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame_FAIL dialog

bool IgnoreDialog = false;  //忽略报错弹窗标志
CFrame_FAIL::CFrame_FAIL(CString strItemName,CString strConclusion,CString strUpper,CString strLower,
		CString strUnit,CString strResult,CString strTestSet,CString strPath,CWnd* pParent)
		: CDialog(CFrame_FAIL::IDD, pParent)
{
	m_strItemName=strItemName;
	m_strConclusion=strConclusion;
	m_strLower=strLower;
	m_strUpper=strUpper;
    m_strUnit=strUnit;
	m_strResult=strResult;
	m_strTestSet=strTestSet;
	m_intControlMark=0; //控制标识符默认为0
	m_strPath = strPath ;
}

CFrame_FAIL::CFrame_FAIL(CWnd* pParent /*=NULL*/)
	: CDialog(CFrame_FAIL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrame_FAIL)
	m_strItemName = _T("");
	m_strLower = _T("");
	m_strTestSet = _T("");
	m_strResult = _T("");
	m_strUpper = _T("");
	m_strConclusion = _T("");
	m_strUnit = _T("");
	
	//}}AFX_DATA_INIT
}


void CFrame_FAIL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrame_FAIL)
	DDX_Text(pDX, IDC_EDIT_ITEMNAME, m_strItemName);
	DDX_Text(pDX, IDC_EDIT_LOWER, m_strLower);
	DDX_Text(pDX, IDC_EDIT_TESTSET, m_strTestSet);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_UPPER, m_strUpper);
	DDX_Text(pDX, IDC_EDIT_CONCLUSION, m_strConclusion);
	DDX_Text(pDX, IDC_STATIC_UNIT, m_strUnit);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_IgnoreDialog_BUTTON, m_IgnoreDialog);
	DDX_Control(pDX, IDC_BUTTON_IGNOR2, m_IgnoreItemPoint);
}


BEGIN_MESSAGE_MAP(CFrame_FAIL, CDialog)
	//{{AFX_MSG_MAP(CFrame_FAIL)
	ON_BN_CLICKED(IDC_BUTTON_RETEST, OnButtonRetest)
	ON_BN_CLICKED(IDC_BUTTON_IGNOR, OnButtonIgnor)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_IGNOR2, OnButtonIgnor2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_IgnoreDialog_BUTTON, &CFrame_FAIL::OnBnClickedIgnoredialogButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame_FAIL message handlers

void CFrame_FAIL::OnButtonRetest() 
{
	// TODO: Add your control notification handler code here
	m_intControlMark=1;
	CDialog::OnOK();
}

void CFrame_FAIL::OnButtonIgnor() 
{
	// TODO: Add your control notification handler code here
	m_intControlMark=2;
	CDialog::OnOK();
}

void CFrame_FAIL::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_intControlMark=3;
	CDialog::OnOK();
}

BOOL CFrame_FAIL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    UpdateData();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFrame_FAIL::OnButtonIgnor2() 
{
	m_intControlMark=4;
	///////////////////////////////初始化状态文件///////////////////////////////////////////
	CFile fileMyFile;
	fileMyFile.Open(m_strPath+"\\DeviceHandle.ini",CFile::modeCreate);
	fileMyFile.Close();
	WritePrivateProfileString("RunStatus","TP","0",m_strPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停

	IgnoreDialog = false ;
	EndDialog(0);
}


void CFrame_FAIL::OnBnClickedIgnoredialogButton()
{
	// TODO: 在此添加控件通知处理程序代码

	IgnoreDialog = true ; 

	EndDialog(0);
}
