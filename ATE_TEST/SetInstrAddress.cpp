// SetInstrAddress.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "SetInstrAddress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetInstrAddress dialog


CSetInstrAddress::CSetInstrAddress(CWnd* pParent/*=NULL*/)
	: CDialog(CSetInstrAddress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetInstrAddress)
	m_instraddress = _T("");
	//}}AFX_DATA_INIT
}


void CSetInstrAddress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetInstrAddress)
	DDX_Control(pDX, IDC_LIST_INSTRINFO, m_instrinfo);
	DDX_Text(pDX, IDC_EDIT_INSTRADDRESS, m_instraddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetInstrAddress, CDialog)
	//{{AFX_MSG_MAP(CSetInstrAddress)
	ON_BN_CLICKED(IDC_BUTTON_SAVEINTR, OnButtonSaveintr)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INSTRINFO, OnClickListInstrinfo)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_INSTRINFO, OnItemclickListInstrinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetInstrAddress message handlers

void CSetInstrAddress::OnButtonSaveintr() 
{
	// TODO: Add your control notification handler code here
	UpdateInstrInfo();
    //将修改后的地址信息进行保存
	WritePrivateProfileString(m_strArr[intLine],"Address",m_instraddress,strFileIniPath);
}

void CSetInstrAddress::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CSetInstrAddress::UpdateInstrInfo()
{
    UpdateData();
	m_instrinfo.SetItemText(intLine,3,m_instraddress);
}

void CSetInstrAddress::InitInstrInfo()
{

	m_instrinfo.DeleteAllItems();
	//////////////////初始化列表////////////////////////////////////////////////////////

	RECT rRect;
	m_instrinfo.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);	
	m_instrinfo.InsertColumn(0,"序号",LVCFMT_LEFT,width/15);
	m_instrinfo.InsertColumn(1,"设备名称",LVCFMT_LEFT,width*3/12);
	m_instrinfo.InsertColumn(2,"设备型号",LVCFMT_LEFT,width*3/12);
	m_instrinfo.InsertColumn(3,"物理地址",LVCFMT_LEFT,width*5/18);
	m_instrinfo.InsertColumn(4,"逻辑名称",LVCFMT_LEFT,width/6);

	
	m_iniope.SetINIPth(strFileIniPath);  //设置配置文件路径

	m_iniope.GetSections(m_strArr);  //
	CString strInsName,strInsModel,strInsAddress,strLogicName;
	CString strSerial;
	for(int i=0;i<m_strArr.GetSize();i++)
	{
		strSerial.Format("%d",i+1);
		strInsName=m_iniope.GetKeyValue(m_strArr[i],"InsName");
		strInsModel=m_iniope.GetKeyValue(m_strArr[i],"Model");
		strInsAddress=m_iniope.GetKeyValue(m_strArr[i],"Address");
		strLogicName=m_strArr[i];
		m_instrinfo.InsertItem(i,strSerial);
		m_instrinfo.SetItemText(i,1,strInsName);
		m_instrinfo.SetItemText(i,2,strInsModel);
		m_instrinfo.SetItemText(i,3,strInsAddress);
		m_instrinfo.SetItemText(i,4,strLogicName);
	}
}


BOOL CSetInstrAddress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwStyle=m_instrinfo.GetExtendedStyle();
	m_instrinfo.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	InitInstrInfo();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetInstrAddress::OnClickListInstrinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code her
	
	CPoint pt=GetCurrentMessage()->pt;  //获取当前鼠标消息坐标
    UINT uFlags=0;
	m_instrinfo.ScreenToClient(&pt);
	intLine=m_instrinfo.HitTest(pt,&uFlags);
    m_instraddress=m_instrinfo.GetItemText(intLine,3);
    UpdateData(false);
	*pResult = 0;
}

void CSetInstrAddress::OnItemclickListInstrinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
