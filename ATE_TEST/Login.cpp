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
	//m_pRecordset.CreateInstance(__uuidof(Recordset)); //������¼��

	//try
	//{
	//	m_pRecordset->CursorLocation = adUseClient;  //��Ҫ�����ݴ�������أ�Ӧ�þ����ǶϿ����ݿ����Recordset���������ڴ��в���
	//	//������д��Զ�����ݿ⡣�෴���� adUseServer ��ֱָ�������ݿ��в�����
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

	//���ñ���ͼ
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
	UpdateData();  //���µ�����:������û��������뱣�浽m_sUserName��m_sPwd

	//����Ƿ����û�
	CString str;
	m_UserName.GetWindowText(str);
	if(str.IsEmpty())
	{
		AfxMessageBox("�û�������Ϊ�գ��������û�����");
	}
	else
	{
		CString strCheck;  //������
		//strCheck.Format("Select * from [tb_User] where [User]='%s' and [Password]='%s'",m_sUserName,m_sPwd);
		strCheck.Format("Select * from tb_User where User= '%s' and Password= '%s'",m_sUserName,m_sPwd); //�����ݿ���������û��������룬��ת��Ϊ�ַ���
		bstr_t s = strCheck.AllocSysString();  //�� CString��strCheck ת���� BSTR��s��Ҫִ�е� SQL ���
		_variant_t RecordsAffected;   //�ܲ�ѯӰ��ļ�¼��Ŀ
		try
		{
			m_pRecordset=GetConnection()->GetConnection()->Execute(s,&RecordsAffected,adCmdText);
			if(m_pRecordset->adoEOF)
			{
				AfxMessageBox("�û���������");
			}
			else
			{
				CDialog::OnOK();  //����������ݿ�����鵽������û��������룬�����ϵͳ
			}

		}
		catch(_com_error *e)
		{
			AfxMessageBox("ִ��SQL������");
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
			//	ThrowErr(�������ݿ����);
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

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd == this)
	{
		return m_brush;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
