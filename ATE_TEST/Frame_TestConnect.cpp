// Frame_TestConnect.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frame_TestConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame_TestConnect dialog

CFrame_TestConnect::CFrame_TestConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CFrame_TestConnect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrame_TestConnect)
	m_strFilePath="";
	m_bIgnoreItem = false;
	m_Quit = false;
	//}}AFX_DATA_INIT
}

CFrame_TestConnect::CFrame_TestConnect(CString strFilePath,CString strItemName,CString strDescription,CWnd* pParent)
: CDialog(CFrame_TestConnect::IDD, pParent)
{
	m_strFilePath=strFilePath;
	m_strItemName=strItemName;
	//m_vDescription=vDescription;
	m_strDescription=strDescription;
	m_bIgnoreItem = false;
}

void CFrame_TestConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrame_TestConnect)
	DDX_Control(pDX, IDC_PIC_TEST_CONNECT, m_Pic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrame_TestConnect, CDialog)
	//{{AFX_MSG_MAP(CFrame_TestConnect)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_BUTTON_OK, OnButtonOk)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_IGNORE_ITEM, OnButtonConnectIgnoreItem)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Quit_BUTTON, &CFrame_TestConnect::OnBnClickedQuitButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame_TestConnect message handlers

BOOL CFrame_TestConnect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rec1;
	GetClientRect(&rec1);
	rec1.top += 50;
	rec1.left += 20;
	rec1.right -= 20;
	rec1.bottom -= 60;
	GetDlgItem(IDC_STATIC_PICRECT)->MoveWindow(rec1);
	m_Pic.MoveWindow(rec1.left + 1, rec1.top + 10, 10, 10);
	
	HBITMAP hBitmap = LoadPicture(m_strFilePath, rec1.Width() - 3, rec1.Height() - 12);
	m_Pic.SetBitmap(hBitmap);
	GetDlgItem(IDC_EDIT_ITEMNAME)->SetWindowText(m_strItemName);
	return TRUE;
}

BOOL CFrame_TestConnect::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
	
}

HBRUSH CFrame_TestConnect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFrame_TestConnect::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CFrame_TestConnect::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	m_Quit = false;
	CDialog::OnOK();	
}

void CFrame_TestConnect::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CFrame_TestConnect::OnButtonConnectIgnoreItem() 
{
	m_bIgnoreItem = true;
	m_Quit = false;
	EndDialog(0);
}

HBITMAP CFrame_TestConnect::LoadPicture(CString mFile, int THUMWIDTH, int THUMHEIGHT)//加载Jpg、Bmp图片
{
    CString pFSize;
    WCHAR wpath[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, mFile, -1, wpath, MAX_PATH);
	
    IPicture* pPic;
    OleLoadPicturePath(wpath, NULL, NULL, NULL, IID_IPicture,(LPVOID*)&pPic);
	
    if (pPic==NULL) return NULL;
    HBITMAP hPic = NULL;
    pPic->get_Handle((UINT*)&hPic);
	
    long nWidth=THUMWIDTH;
    long nHeight=THUMHEIGHT;
	
    long mWid,mHei;
    pPic->get_Height(&mHei);
    pPic->get_Width(&mWid);
	
    HBITMAP hPicRet = (HBITMAP)CopyImage(hPic, IMAGE_BITMAP, nWidth, nHeight , LR_COPYDELETEORG); 
	return hPicRet;
}


void CFrame_TestConnect::OnBnClickedQuitButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Quit = true;
	CDialog::OnOK();
}
