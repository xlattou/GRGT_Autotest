// ProductRegister.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ProductRegister.h"
#include "Des.h"
#include "Tool.h"
#include "PathOperate.h"
#include <fstream>
//#include <winioctl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProductRegister dialog


CProductRegister::CProductRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CProductRegister::IDD, pParent)
{
	m_strRegister = "";
	m_strRequest = "";
	CPathOperate pathope1;
	m_strDLLPath = pathope1.GetAppPath() + "\\pcure.dll";
	m_strKey[0] = "PJLFBI45";//加解密密匙
	m_strKey[1] = "MNUTYDKO";//二次加解密密匙
	m_strCharacter = "ATETEST10";//版本特征码
}


void CProductRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProductRegister)
	DDX_Control(pDX, IDC_PIC_REG_TITLE, m_pic_Reg_Title);
	DDX_Control(pDX, IDC_EDIT_REQUEST, m_edt_Request);
	DDX_Control(pDX, IDC_EDIT_REGISTER, m_edt_Register);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProductRegister, CDialog)
	//{{AFX_MSG_MAP(CProductRegister)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProductRegister message handlers

void CProductRegister::OnOK()
{
	if(m_strRequest == "")
	{
		AfxMessageBox("无法获得硬件编码, 请检查系统是否运行正常!");
		exit(0);
	}
	m_edt_Register.GetWindowText(m_strRegister1);
	CTool tool1;
	m_strRegister = tool1.CStrTorHex(m_strRegister1);

	Des des1;
	char chReg[1000] = {0};
	CString str1;
	des1.Des_Go(chReg, m_strRegister.GetBuffer(0), m_strRegister.GetLength(), m_strKey[0].GetBuffer(0), m_strKey[0].GetLength(), DECRYPT); //解密计算
	str1 = chReg;

	if(str1 != m_strRequest + m_strCharacter)
	{
		AfxMessageBox("注册码不正确, 请联系供应商广州山锋测控有限公司获取验证码!");
		return;
	}


	des1.Des_Go(chReg, m_strRegister.GetBuffer(0), m_strRegister.GetLength(), m_strKey[1].GetBuffer(0), m_strKey[1].GetLength()); //加密计算
	str1 = chReg;
	writeKey(str1.GetBuffer(0), str1.GetLength());
	CDialog::OnOK();
}

BOOL CProductRegister::compareKey()
{
	CString str1;
	str1 = GetCPUID();
	int nI = 0;
	for(int i = str1.GetLength() - 1; i >= 0; i--)
	{
		if(str1[i] != '0')
			break;
		nI ++;
	}
	str1 = str1.Left(str1.GetLength() - nI);
	str1 += GetDiskId();
	
	//AfxMessageBox(str1);
	if(str1 != "")
		m_strRequest = str1;

	str1 = m_strRequest + m_strCharacter;
	char chReg[1000] = {0};
	Des des1;

	char chKey[1000] = {0};
	readKey(chKey);
	CString str2 = chKey;
	if(str2 == "")
		return 1;

	for(int i = 0; i< 1000; i++)
		chReg[i] = 0;

	des1.Des_Go(chReg, str2.GetBuffer(0), str2.GetLength(), m_strKey[1].GetBuffer(0), m_strKey[1].GetLength(), DECRYPT); //解密计算
	str2 = chReg;
	for(int i = 0; i< 1000; i++)
		chReg[i] = 0;

	des1.Des_Go(chReg, str2.GetBuffer(0), str2.GetLength(), m_strKey[0].GetBuffer(0), m_strKey[0].GetLength(), DECRYPT); //解密计算
	str2 = chReg;

	//AfxMessageBox(chReg);
	//AfxMessageBox(str1);
	return strcmp(chReg, str1);
}

BOOL CProductRegister::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);

	m_edt_Request.SetWindowText(m_strRequest);
	CString str1 = m_strRegister;
	CTool tool;
	str1 = tool.Hex((unsigned char *)str1.GetBuffer(0), str1.GetLength());
	
	//m_edt_Register.SetWindowText(str1 + " " + m_strRegister);
	/*typedef int(*lpGetSingleItemInfo)(CString,CString,CString&); //宏定义函数指针类型
	HINSTANCE hDll; //DLL句柄
	lpGetSingleItemInfo GetSingleItemInfo; //函数指针
	hDll = LoadLibrary("WebCan.dll");

	if (hDll != NULL)
	{
		GetSingleItemInfo = (lpGetSingleItemInfo)GetProcAddress(hDll, "GetSingleItemInfo");
		if (GetSingleItemInfo != NULL)
		{
			GetSingleItemInfo(_T("Win32_BaseBoard"),_T("SerialNumber"), str1);
		}
		FreeLibrary(hDll);
	}
	
	m_edt_Request.SetWindowText(str1);*/

	HBITMAP hbmp = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_BITMAP_REG_TITLE);
	m_pic_Reg_Title.SetBitmap(hbmp);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CProductRegister::GetCPUID()
{
    CString CPUID;
    unsigned long s1,s2;
    unsigned char vendor_id[]="------------";
    char sel;
    sel='1';
    CString VernderID;
    CString MyCpuID,CPUID1,CPUID2;
	
	switch(sel)
    {
    case '1':
        __asm{
            xor eax,eax      //eax=0:取Vendor信息
				cpuid    //取cpu id指令，可在Ring3级使用
				mov dword ptr vendor_id,ebx
				mov dword ptr vendor_id[+4],edx
				mov dword ptr vendor_id[+8],ecx
        }
        VernderID.Format("%s-",vendor_id);
        __asm{
            mov eax,01h   //eax=1:取CPU序列号
				xor edx,edx
				cpuid
				mov s1,edx
				mov s2,eax
        }
        CPUID1.Format("%08X%08X",s1,s2);
        __asm{
            mov eax,03h
				xor ecx,ecx
				xor edx,edx
				cpuid
				mov s1,edx
				mov s2,ecx
        }
        CPUID2.Format("%08X%08X",s1,s2);
        break;
    case '2':
        {
            __asm{
                mov ecx,119h
					rdmsr
					or eax,00200000h
					wrmsr
            }
        }
        AfxMessageBox("CPU id is disabled.");
        break;
    }
    MyCpuID = CPUID1+CPUID2;
    CPUID = MyCpuID;
    return CPUID;
}

//使用最老的方法获取硬盘序列号
CString CProductRegister::GetDiskId()
{
	CString id; 
	TCHAR Name[MAX_PATH]; 
	DWORD serno; 
	DWORD length; 
	DWORD FileFlag; 
	TCHAR FileName[MAX_PATH]; 
	BOOL Ret; 
	Ret = GetVolumeInformation("c:\\", Name, MAX_PATH, &serno, &length, &FileFlag, FileName, MAX_PATH); 
	if (Ret) 
		id.Format("%X", serno);
	return id;
};

HBRUSH CProductRegister::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}	
	
	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
    	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	return hbr;
}

void CProductRegister::creatDLL()
{
	CFile file1;
	file1.Open(m_strDLLPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	char ch1[10] = {(CHAR)0x0};
	file1.SeekToBegin();
	for(int i = 0; i < 1100; i+=10)
		file1.Write(ch1, 10);
	file1.Close();
}

void CProductRegister::readKey(char* charKey)
{
	CFileStatus status;
	if(!CFile::GetStatus(m_strDLLPath, status))
		return;
	CFile file1;
	file1.Open(m_strDLLPath, CFile::modeRead | CFile::typeBinary);
	file1.GetStatus(status);
	int nL = status.m_size;
		
	if(nL >= 1088)
	{
		file1.Seek(100, CFile::begin);
		file1.Read(charKey, 200);
	}
	file1.Close();
}

void CProductRegister::writeKey(char* charKey, int nLength)
{
	CFileStatus status;
	if(!CFile::GetStatus(m_strDLLPath, status))
		creatDLL();
	CFile file1;
	file1.Open(m_strDLLPath, CFile::modeWrite | CFile::typeBinary);
	file1.GetStatus(status);
	int nL = status.m_size;
		
	if(nL >= 1088)
	{
		file1.Seek(100, CFile::begin);
		file1.Write(charKey, nLength);
		file1.Close();
	}
}