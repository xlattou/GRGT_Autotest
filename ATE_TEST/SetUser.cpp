// SetUser1.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "SetUser.h"
#include "ADO.h"
#include "EasySize.h"
#define BACKGROUND RGB(0,200,100)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CATE_TESTApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CSetUser dialog


CSetUser::CSetUser(CWnd* pParent /*=NULL*/)
	: CDialog(CSetUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetUser)
	m_sName = _T("");
	m_sPwd1 = _T("");
	m_sPwd2 = _T("");
	m_sPower = _T("");
	m_sPwd = _T("");
	//}}AFX_DATA_INIT
}


void CSetUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetUser)
	DDX_Control(pDX, IDC_LIST_USER, m_userList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_PWD2, m_sPwd2);
	DDX_CBString(pDX, IDC_COMBO_POW, m_sPower);
	DDX_Text(pDX, IDC_EDIT_PWD, m_sPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetUser, CDialog)
	//{{AFX_MSG_MAP(CSetUser)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_NEW_BTN, OnNewBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, OnDelBtn)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, OnClickListUser)
	ON_BN_CLICKED(IDC_CHANGE_BTN, OnChangeBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnSave)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CSetUser)
	EASYSIZE(IDC_LIST_USER,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_SAVE_BTN,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_DEL_BTN,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_NEW_BTN,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)	
	EASYSIZE(IDC_CHANGE_BTN,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_STATIC2,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_STATIC1,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_EDIT_NAME,ES_BORDER,ES_BORDER,IDC_EDIT_PWD,ES_KEEPSIZE,0)
	EASYSIZE(IDC_EDIT_PWD,IDC_EDIT_NAME,ES_BORDER,IDC_EDIT_PWD2,ES_KEEPSIZE,0)
	EASYSIZE(IDC_EDIT_PWD2,IDC_EDIT_PWD,ES_BORDER,IDC_COMBO_POW,ES_KEEPSIZE,0)
	EASYSIZE(IDC_COMBO_POW,IDC_EDIT_PWD2,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)	
	/*
	EASYSIZE(IDC_EDIT_PWD2,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_EDIT_PWD,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_EDIT_NAME,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	
	EASYSIZE(IDC_COMBO_POW,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	*/
	//EASYSIZE(IDC_STATIC_NAME,ES_KEEPSIZE,ES_KEEPSIZE,ES_KEEPSIZE,ES_KEEPSIZE,0)
	//EASYSIZE(IDC_STATIC_PWD1,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	//EASYSIZE(IDC_STATIC_PWD2,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CSetUser message handlers

BOOL CSetUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect itemRC;
	m_userList.GetClientRect(itemRC);
	
	// TODO: Add extra initialization here
	m_brush.CreateSolidBrush(BACKGROUND);
	
	m_userList.InsertColumn(0,"ID",LVCFMT_CENTER,100);
	m_userList.InsertColumn(1,"用户名",LVCFMT_CENTER,100);
	m_userList.InsertColumn(2,"密码",LVCFMT_CENTER,100);
	m_userList.InsertColumn(3,"权限级别",LVCFMT_CENTER,200);
    m_userList.InsertColumn(4,"最后登录日期",LVCFMT_CENTER,itemRC.Width()-500);
	m_userList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);  //表样式设定为虚拟边框，每次选全行
	m_userList.ShowWindow(SW_SHOW);

	UpdateUserList();   //读取数据库

	//初始化ComboBox
	CComboBox* pComboPower=(CComboBox*)GetDlgItem(IDC_COMBO_POW);
	pComboPower->InsertString(0,"设置权限级");
	pComboPower->SetCurSel(0);
	
	pComboPower->AddString("高级管理员");
	pComboPower->AddString("普通管理员");
	pComboPower->AddString("测试操作员");
	UpdateData(FALSE);


	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CSetUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);//return (HBRUSH)m_brush;
	}	
	
	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
		pDC->SetBkMode(BACKGROUND);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);//(HBRUSH)m_brush;
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSetUser::UpdateUserList()
{
	m_userList.DeleteAllItems();				//清除list所有列
	m_DataSet.Open("select* from tb_User");		
	_variant_t value;
	int count = m_DataSet.GetRecordCount();
	_variant_t itemData;
	_variant_t stime;

	for(int i=0;i<count;i++)
	{
		itemData = m_DataSet.GetFields()->GetItem("ID")->GetValue();
		m_userList.InsertItem(i,"");
		m_userList.SetItemData(i,itemData.lVal);
		m_userList.SetItemText(i,0,(_bstr_t)m_DataSet.GetFields()->GetItem("ID")->GetValue());				//ID
		m_userList.SetItemText(i,1,(_bstr_t)m_DataSet.GetFields()->GetItem("User")->GetValue());			//用户名
		m_userList.SetItemText(i,2,(_bstr_t)m_DataSet.GetFields()->GetItem("Password")->GetValue());		//密码
		m_userList.SetItemText(i,3,(_bstr_t)m_DataSet.GetFields()->GetItem("Power")->GetValue());			//权限
		{
			stime = m_DataSet.GetFields()->GetItem("LastTime")->GetValue();									//判断登陆时间是否为空
			if (stime.vt != VT_NULL)
				m_userList.SetItemText(i,4,(_bstr_t)stime);	
		}
		
		m_DataSet.Next();
	}
}

void CSetUser::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	Invalidate();
	UPDATE_EASYSIZE;

	if(m_userList.GetSafeHwnd())
	{
		CRect itemRC;
		m_userList.GetClientRect(itemRC);
		m_userList.SetColumnWidth(4,itemRC.Width()-500);
	}
	
}

void CSetUser::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	//EASYSIZE_MINSIZE(150,100,fwSide,pRect);	
}

//增加用户
void CSetUser::OnNewBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData();  //将控件数据刷新到变量中
	if(m_sName==""||m_sPwd1==""||m_sPwd2==""||m_sPower=="设置权限级")
	{
		AfxMessageBox("请输入用户名、密码、权限级信息!");
		return;
	}
	if(m_sPwd1!=m_sPwd2)
	{
		AfxMessageBox("两次输入密码不一致,请重新输入");
		return;
	}

	CString sql;
	sql.Format("Select * From tb_User Where User = '%s'",m_sName);
	m_DataSet.Open(sql);

	if(m_DataSet.GetRecordCount()!=0)
	{
		MessageBox("该用户名已存在，请选择其他用户名!");
		return;
	}

	m_DataSet.AddNew();
	m_DataSet.SetFieldValue("User",(bstr_t)m_sName);
	m_DataSet.SetFieldValue("Password",(bstr_t)m_sPwd1);
	m_DataSet.SetFieldValue("Power",(bstr_t)m_sPower);
	m_DataSet.Save();
	UpdateUserList();
}

//删除用户
void CSetUser::OnDelBtn() 
{
	/*linlin 修改*/
	POSITION pos=m_userList.GetFirstSelectedItemPosition();
	int n=m_userList.GetNextSelectedItem(pos); 
	if(n==-1)
	{
		AfxMessageBox("请在列表中选择需要删除的用户信息");
		return;
	}
	if(AfxMessageBox("确定删除?",MB_OKCANCEL)==2)
		return;

	CString strDel;
	n = m_userList.GetSelectionMark();
	int iSelID=m_userList.GetItemData(n);
	strDel.Format("select * from tb_User where ID=%d",iSelID);

	m_DataSet.Open(strDel);
	m_DataSet.Delete();
	m_DataSet.Save();
	UpdateUserList();

}

void CSetUser::OnClickListUser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos=m_userList.GetFirstSelectedItemPosition();
	int n=m_userList.GetNextSelectedItem(pos);
	CString selUser=m_userList.GetItemText(n,1);
	CString selPwd=m_userList.GetItemText(n,2);
	CString selPower=m_userList.GetItemText(n,3);
	
	m_sName=selUser;
	m_sPwd1=m_sPwd2=selPwd;
	m_sPower=selPower;
	UpdateData(FALSE);

	*pResult = 0;
}

//修改用户
void CSetUser::OnChangeBtn() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();

	POSITION pos=m_userList.GetFirstSelectedItemPosition();
	int n=m_userList.GetNextSelectedItem(pos);
	//如果选项为空，返回
	if(n==-1)
	{
		AfxMessageBox("请在列表中选择需要修改的用户信息");
		return;
	}
	if(m_sName==""||m_sPwd1==""||m_sPwd2==""||m_sPower=="设置权限级")
	{
		AfxMessageBox("用户名、密码、权限级信息不能为空!");
		return;
	}
	if(m_sPwd1!=m_sPwd2)
	{
		AfxMessageBox("两次输入密码不一致,请重新输入");
		return;
	}

	CString strOpen;
	n = m_userList.GetSelectionMark();
	int iSelID=m_userList.GetItemData(n);
	strOpen.Format("select * from tb_User where ID=%d",iSelID);
	
	m_DataSet.Open(strOpen);
	m_DataSet.SetFieldValue("User",(bstr_t)m_sName);
	m_DataSet.SetFieldValue("Password",(bstr_t)m_sPwd1);
	m_DataSet.SetFieldValue("Power",(bstr_t)m_sPower);
	m_DataSet.Save();
	UpdateUserList();
}


BOOL CSetUser::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();

	return CDialog::DestroyWindow();
}

void CSetUser::OnSave() 
{
	// TODO: Add your control notification handler code here
	// 由于保存工作已做，此处可不做保存处理
}
