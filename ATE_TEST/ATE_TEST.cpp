// ATE_TEST.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "ATE_TESTDlg.h"
#include "ADO.h"
#include "ProductRegister.h"
#include "MyOccManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CATE_TESTApp

BEGIN_MESSAGE_MAP(CATE_TESTApp, CWinApp)
	//{{AFX_MSG_MAP(CATE_TESTApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMyOccManager theManager;
/////////////////////////////////////////////////////////////////////////////
// CATE_TESTApp construction

CATE_TESTApp::CATE_TESTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CATE_TESTApp object

CATE_TESTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CATE_TESTApp initialization

BOOL CATE_TESTApp::InitInstance()
{
	CreateMutex( NULL, FALSE, "ATE_TEST" );// ��ӻ�����,��ֹͬʱ�򿪶������ϵͳ
    if(GetLastError()==ERROR_ALREADY_EXISTS)
        exit(0);
	AfxEnableControlContainer(&theManager);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	RegesistSoft();  //���ע�����

///////���ݿ�����///
    CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection)); //����Connection����

	char* s=new char[MAX_PATH];
	if(!GetModuleFileName(NULL,s,MAX_PATH))
	{
		AfxMessageBox("��ȡ����·��ʧ��");
		return TRUE;
	}
    (_tcsrchr(s,_T('\\')))[0] = 0;  //ȥ��\\ATE_TEST.exe
	(_tcsrchr(s,_T('\\')))[1] = 0;//ȥ��Debug
	CString m_sPath(s);       //��Դ�ļ�·��
	m_sPath+="DataInfo\\SystemInfo\\PavelDemo.mdb";
	m_sPath="Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+m_sPath;
	m_sPath+="; JET OLEDB:DATABASE PASSWORD=''";
	try
	{
		//m_pConnection->Open(_bstr_t(m_sPath),"","",adModeUnknown);
		BOOL openhResult=GetConnection()->Open(m_sPath);  //�����ݿ�
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ݿ�����ʧ��");
	}

	

	////////////////////////////////////////////////////////////////////////
	CATE_TESTDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CATE_TESTApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//
	if(m_pConnection->State)
        m_pConnection->Close(); //�ر����ݿ�����ָ��
	m_pConnection= NULL;
	CoUninitialize();  

	return CWinApp::ExitInstance();
}

void CATE_TESTApp::RegesistSoft()
{
	CProductRegister reg1;
	if(reg1.compareKey() != 0)
	{	if (reg1.DoModal() != IDOK)
	{
		AfxMessageBox("���δע��, ����ϵ����ɽ���ؼ������޹�˾����ע��!");
		exit(0);
	}
	}
}