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
// �� Windows NT/2000/XP �п�����Ȩ�޲�������ʧ��
// ���ԡ�System Ȩ�����е�ϵͳ���̣��������
// �ñ�����ȡ�á�debug Ȩ�޼���,Winlogon.exe ��������ֹŶ
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
	char c[]={"EXCEL.EXE"}; //�����ַ�������ʼ��,cΪ8����,����β��'\0',����һ���ַ�Ϊ'x',
	HANDLE handle; //����CreateToolhelp32Snapshotϵͳ���վ��
	HANDLE handle1; //����Ҫ�������̾��
	handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//���ϵͳ���վ��
	PROCESSENTRY32 *info; //����PROCESSENTRY32�ṹ��ָ
	//PROCESSENTRY32  �ṹ�� dwSize ��Ա���ó� sizeof(PROCESSENTRY32)
	info=new PROCESSENTRY32;
	info->dwSize=sizeof(PROCESSENTRY32);
	//����һ�� Process32First �������ӿ����л�ȡ�����б�
	Process32First(handle,info);
	//�ظ����� Process32Next��ֱ���������� FALSE Ϊֹ
	while(Process32Next(handle,info) != FALSE)
	{
		info->szExeFile;     //ָ���������
		//strcmp�ַ����ȽϺ���ͬҪ������ͬ
		if( strcmp(c,info->szExeFile) == 0 )
		{
			//MessageBox (NULL, info->szExeFile, TEXT ("HelloMsg"));
			//PROCESS_TERMINATE��ʾΪ����������,FALSE=�ɼ̳�,info->th32ProcessID=����ID
			handle1=OpenProcess(PROCESS_TERMINATE,FALSE,info->th32ProcessID);
			//��������
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
