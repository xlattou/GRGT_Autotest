// Login.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CATE_TESTApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CLogin dialog


CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogin)
	m_sUserName = _T("");
	m_sPwd = _T("");
	//}}AFX_DATA_INIT
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_EDIT_PSW, m_sPwd);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_UserName);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers

BOOL CLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_pRecordset.CreateInstance(__uuidof(Recordset)); //创建记录集

	//try
	//{
	//	m_pRecordset->CursorLocation = adUseClient;  //需要把数据传输给本地，应用举例是断开数据库进行Recordset操作，即内存中操作
	//	//而不是写入远端数据库。相反的有 adUseServer 是指直接在数据库中操作。
	//	m_pRecordset->Open("select * from [Pwd]",  //tb_User
	//		theApp.m_pConnection.GetInterfacePtr(),
	//		adOpenDynamic,
	//		adLockOptimistic,
	//		adCmdText);		
	//}
	//catch(_com_error *e)
	//{
	//	AfxMessageBox(e->ErrorMessage());
	//}

	//设置背景图
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP18);
	m_brush.CreatePatternBrush(&bmp);
	bmp.DeleteObject();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CLogin::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();  //更新到变量:输入的用户名和密码保存到m_sUserName和m_sPwd

	//检查是否有用户
	CString str;
	m_UserName.GetWindowText(str);
	if(str.IsEmpty())
	{
		AfxMessageBox("用户名不能为空！请输入用户名：");
	}
	else
	{
		CString strCheck;  //检测语句
		//strCheck.Format("Select * from [tb_User] where [User]='%s' and [Password]='%s'",m_sUserName,m_sPwd);
		strCheck.Format("Select * from tb_User where User= '%s' and Password= '%s'",m_sUserName,m_sPwd); //从数据库里面读出用户名和密码，并转换为字符串
		bstr_t s = strCheck.AllocSysString();  //将 CString的strCheck 转化成 BSTR的s，要执行的 SQL 语句
		_variant_t RecordsAffected;   //受查询影响的记录数目
		try
		{
			m_pRecordset=GetConnection()->GetConnection()->Execute(s,&RecordsAffected,adCmdText);
			if(m_pRecordset->adoEOF)
			{
				AfxMessageBox("用户名不存在");
			}
			else
			{
				CDialog::OnOK();  //如果能在数据库里面查到输入的用户名和密码，则进入系统
			}

		}
		catch(_com_error *e)
		{
			AfxMessageBox("执行SQL语句出错");
			AfxMessageBox(e->ErrorMessage());
		}

		try
		{
			if(m_pRecordset!=NULL)
			{
				if(m_pRecordset->GetState()==adStateOpen)
				{
					m_pRecordset->Close();
				}
				m_pRecordset=NULL;
			}
			//  return 1;
		}
		catch(_com_error &)
		{
			//	ThrowErr(e->ErrorMessage());
			//	ThrowErr(连接数据库出错);
			//	return 0;
		}
	}	
}

void CLogin::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	exit(1);
	
}




HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd == this)
	{
		return m_brush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
