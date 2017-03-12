// System.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "System.h"
#include "SetUser.h"
#include "WebAdm.h"
#include "DatabaseAdm.h"
#include "EasySize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystem dialog


BOOL CSystem::OnInitDialog()
{
	CDialog::OnInitDialog();
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);	

	m_tab.InsertItem(0,"用户管理",0);
	m_tab.InsertItem(1,"",1);//网络管理
	m_tab.InsertItem(2,"",2);//数据库管理
	m_tab.InsertItem(3,"",3);//存储管理

	m_setUser.Create(IDD_SET_USER,&m_tab);//
	m_webAdm.Create(IDD_WEB,&m_tab);
	m_DataBaseAdm.Create(IDD_ADM_DATABASE,&m_tab);
	m_SaveAdm.Create(IDD_SAVE_ADM,&m_tab);

	CRect clientRC;	
	this->GetClientRect(clientRC);
	m_tab.MoveWindow(clientRC);


	CRect itemRC;
	m_tab.GetClientRect(clientRC);
	m_tab.GetItemRect(0,itemRC);

	m_tab.SetItemSize(CSize(10,40));
	int itemwith= (clientRC.Width()-4)/6;
	m_tab.SetMinTabWidth(itemwith);

	clientRC.DeflateRect(0,itemRC.Height(),0,0);
	m_setUser.MoveWindow(clientRC);
	m_webAdm.MoveWindow(clientRC);
	m_DataBaseAdm.MoveWindow(clientRC);
	m_SaveAdm.MoveWindow(clientRC);

	m_setUser.ShowWindow(SW_SHOW);
	m_tab.SetCurSel(0);
	INIT_EASYSIZE;

	return TRUE;
}


void CSystem::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//int nCurSel = m_tab.GetCurSel();
	/*if(nCurSel == 0)
	{
		m_setUser.ShowWindow(SW_SHOW);
		m_webAdm.ShowWindow(SW_HIDE);
		m_DataBaseAdm.ShowWindow(SW_HIDE);
		m_SaveAdm.ShowWindow(SW_HIDE);
	}

	else if (nCurSel == 1)
	{
		m_webAdm.ShowWindow(SW_SHOW);
		m_setUser.ShowWindow(SW_HIDE);
		m_DataBaseAdm.ShowWindow(SW_HIDE);
		m_SaveAdm.ShowWindow(SW_HIDE);
	}
	else if(nCurSel == 2)
	{
		m_DataBaseAdm.ShowWindow(SW_SHOW);
		m_setUser.ShowWindow(SW_HIDE);
		m_webAdm.ShowWindow(SW_HIDE);
		m_SaveAdm.ShowWindow(SW_HIDE);
	}
	else if(nCurSel == 3)
	{
		m_SaveAdm.ShowWindow(SW_SHOW);
		m_DataBaseAdm.ShowWindow(SW_HIDE);
		m_setUser.ShowWindow(SW_HIDE);
		m_webAdm.ShowWindow(SW_HIDE);
	}
	Invalidate(); */
	*pResult = 0;
}


CSystem::CSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystem)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CSystem, CDialog)
	//{{AFX_MSG_MAP(CSystem)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CSystem)
	EASYSIZE(IDC_TAB1,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CSystem message handlers

void CSystem::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	Invalidate(); //重绘
	UPDATE_EASYSIZE;

	if(m_setUser.GetSafeHwnd()&& m_SaveAdm.GetSafeHwnd() && m_webAdm.GetSafeHwnd() && m_DataBaseAdm.GetSafeHwnd())
	{
		CRect clientRC,itemRC;	
		m_tab.GetClientRect(clientRC);
		m_tab.GetItemRect(0,itemRC);
		clientRC.DeflateRect(0,itemRC.Height(),0,0);
		int itemwith= (clientRC.Width()-4)/4;
		m_tab.SetMinTabWidth(itemwith);

		m_setUser.MoveWindow(clientRC);
		m_webAdm.MoveWindow(clientRC);
		m_SaveAdm.MoveWindow(clientRC);
		m_DataBaseAdm.MoveWindow(clientRC);
	}
	// TODO: Add your message handler code here
	
}


HBRUSH CSystem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return (HBRUSH)m_brush;
	//return hbr;
}


BOOL CSystem::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	if(m_setUser)
    	m_setUser.DestroyWindow();
	if(m_DataBaseAdm)
		m_DataBaseAdm.DestroyWindow();
	if(m_SaveAdm)
		m_SaveAdm.DestroyWindow();
	if(m_webAdm)
		m_webAdm.DestroyWindow();
	return CDialog::DestroyWindow();
}

BOOL CSystem::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
