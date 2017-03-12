// InsDocTempExcel.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTempExcel.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcel dialog


CInsDocTempExcel::CInsDocTempExcel(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocTempExcel::IDD, pParent)
{
	m_strPath = "";
	GetDebugPriv();
}
CInsDocTempExcel::~CInsDocTempExcel()
{
	m_DosExcel.Close();
	if(m_strPath != "")
		KillExcel();
}

void CInsDocTempExcel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocTempExcel)
	DDX_Control(pDX, IDC_DSOFRAMER, m_DosExcel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocTempExcel, CDialog)
	//{{AFX_MSG_MAP(CInsDocTempExcel)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcel message handlers

BOOL CInsDocTempExcel::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ModifyStyle(NULL, WS_THICKFRAME);
	
	VARIANT vReadOnly, vString, vId;
	vReadOnly.vt = VT_BOOL;
	vReadOnly.boolVal = true;

	vString.vt = VT_BYREF;
	vString.pcVal = NULL;

	vId.vt = VT_INT;
	vId.intVal = 0;

	KillExcel();
	m_DosExcel.SetToolbars(FALSE);
	m_DosExcel.SetMenubar(FALSE);
	m_DosExcel.Open(_variant_t(m_strPath), vReadOnly, vId, vString, vString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CInsDocTempExcel, CDialog)
    //{{AFX_EVENTSINK_MAP(CInsDocTempExcel)
	ON_EVENT(CInsDocTempExcel, IDC_DSOFRAMER, 4 /* OnActivationChange */, OnOnActivationChangeDsoframer, VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CInsDocTempExcel::OnOnActivationChangeDsoframer(BOOL fGoingActive) 
{
	int nI = 12;
	nI++;
	
}

// GetDebugPriv
// 在 Windows NT/2000/XP 中可能因权限不够导致失败
// 如以　System 权限运行的系统进程，服务进程
// 用本函数取得　debug 权限即可,Winlogon.exe 都可以终止哦
BOOL CInsDocTempExcel::GetDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if ( ! OpenProcessToken( GetCurrentProcess(),
	TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		{
	return FALSE;
		}

	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
	CloseHandle(hToken);
	return FALSE;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
    {
        CloseHandle( hToken );
        return FALSE;
    }

    return TRUE;
}

BOOL CInsDocTempExcel::KillExcel()
{
	char c[]={"EXCEL.EXE"}; //定义字符串并初始化,c为8长度,最后结尾有'\0',定义一个字符为'x',
	HANDLE handle; //定义CreateToolhelp32Snapshot系统快照句柄
	HANDLE handle1; //定义要结束进程句柄
	handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//获得系统快照句柄
	PROCESSENTRY32 *info; //定义PROCESSENTRY32结构字指
	//PROCESSENTRY32  结构的 dwSize 成员设置成 sizeof(PROCESSENTRY32)
	info=new PROCESSENTRY32;
	info->dwSize=sizeof(PROCESSENTRY32);
	//调用一次 Process32First 函数，从快照中获取进程列表
	Process32First(handle,info);
	//重复调用 Process32Next，直到函数返回 FALSE 为止
	while(Process32Next(handle,info) != FALSE)
	{
		info->szExeFile;     //指向进程名字
		//strcmp字符串比较函数同要结束相同
		if( strcmp(c,info->szExeFile) == 0 )
		{
			//MessageBox (NULL, info->szExeFile, TEXT ("HelloMsg"));
			//PROCESS_TERMINATE表示为结束操作打开,FALSE=可继承,info->th32ProcessID=进程ID
			handle1=OpenProcess(PROCESS_TERMINATE,FALSE,info->th32ProcessID);
			//结束进程
			TerminateProcess(handle1,0);
		}
	}
	CloseHandle(handle);
	return TRUE;
}

BOOL CInsDocTempExcel::DestroyWindow() 
{
	m_DosExcel.Close();
	KillExcel();
	return CDialog::DestroyWindow();
}

void CInsDocTempExcel::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect1;
	GetClientRect(&rect1);
	m_DosExcel.MoveWindow(rect1);
	m_DosExcel.Invalidate(TRUE);
}
