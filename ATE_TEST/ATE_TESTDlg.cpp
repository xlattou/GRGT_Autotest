// ATE_TESTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "ATE_TESTDlg.h"
#include "Tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CATE_TESTDlg dialog

CATE_TESTDlg::CATE_TESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CATE_TESTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CATE_TESTDlg)
	m_strAppName = _T("ͨ���Զ�����У׼ƽ̨");
	m_strStatus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  //����ͼ��
	dlghand1=NULL;
	m_nShowType = 1;
}

void CATE_TESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CATE_TESTDlg)
//	DDX_Control(pDX, IDC_STATIC_NAME, m_static_name);
//	DDX_Text(pDX, IDC_STATIC_NAME, m_strAppName);
	//DDX_Text(pDX, IDC_EDIT_MAINSTATUS, m_strStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CATE_TESTDlg, CDialog)
	//{{AFX_MSG_MAP(CATE_TESTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_BACK, OnMenuBack)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_COMMAND(ID_MENU_SETUSER, OnMenuSetuser)
	ON_COMMAND(ID_MENU_SETSOURCE, OnMenuSetsource)
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_MENUITEM_AUTOTEST, OnMenuitemAutotest)
	ON_BN_CLICKED(10000, OnExit)
	ON_BN_CLICKED(10002, OnManutest)
	ON_BN_CLICKED(10001, OnAutotest)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(10003, OnAssistant)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
BEGIN_EASYSIZE_MAP(CATE_TESTDlg)
 //   EASYSIZE(IDC_EDIT_MAINSTATUS,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0) 
   EASYSIZE(IDC_STATIC_FRAME,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)


END_EASYSIZE_MAP


/////////////////////////////////////////////////////////////////////////////
// CATE_TESTDlg message handlers

BOOL CATE_TESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//���ñ���ͼ
	
	this->ShowWindow(SW_HIDE);

	//dlg_Login.DoModal();  //������½�Ի���
	m_userName=dlg_Login.m_sUserName;
	m_password=dlg_Login.m_sPwd;
	this->ShowWindow(SW_SHOW);
	SetTimer(1,500,NULL);

	ShowWindow(SW_SHOWMAXIMIZED);//this->

	//���������ڴ�С������ҳ���С��λ��,��ť��Сλ��
	GetClientRect(rect);//��ȡ�ͻ����Ĵ�С
	GetDlgItem(IDC_STATIC_FRAME)->SetWindowPos(&wndTop,60,95,rect.right-70,rect.bottom-100,SWP_SHOWWINDOW);//�ı�һ���Ӵ��ڣ�����ʽ����

	int intHtInterval=(rect.Height()-100)/4;
	int intWidth=48;
	int intHeight=132;
	int x0=5;
	int y0=100;
	m_rect_Test=CRect(x0,y0,x0+intWidth,y0+intHeight);
	m_rect_Model=CRect(x0,y0+intHtInterval,x0+intWidth,y0+intHeight+intHtInterval);
	//m_rect_Report=CRect(x0,y0+intHtInterval*2,x0+intWidth,y0+intHeight+intHtInterval*2);
	//m_rect_Remote=CRect(x0,y0+intHtInterval*2,x0+intWidth,y0+intHeight+intHtInterval*2);
	m_rect_System=CRect(x0,y0+intHtInterval*2,x0+intWidth,y0+intHeight+intHtInterval*2);  

	//m_rect_Moniter=CRect(x0,y0+intHtInterval*5,x0+intWidth,y0+intHeight+intHtInterval*5);
	m_rect_Help=CRect(x0,y0+intHtInterval*3,x0+intWidth,y0+intHeight+intHtInterval*3);  //��������������
	
	m_rect_Exit=CRect(rect.right-130,12,rect.right-20,68);//�˳�����������
	DrawButton(m_newButton_Exit,IDB_BITMAP4,IDB_BITMAP5,m_rect_Exit,10000);  //��̬�����˳�������10000Ϊ������ID
	
	/*CRect rRect_Status;
	rRect_Status=CRect(x0,y0+intHtInterval*5,x0+intWidth,y0+intHeight+intHtInterval*5-20);
    rRect_Status=CRect(10,10,1000,1000);
	m_newEdit_Status.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER
		|ES_READONLY|ES_MULTILINE,rRect_Status,this,10009);
	m_newStatic_Status.Create(_T("11"),WS_CHILD|WS_VISIBLE|SS_LEFT,rRect_Status,this,10009);
	m_newEdit_Status.SetWindowText("dd");
	newBtn.Create("NEW",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD,rect,this,intBtnID);
	*/

	//�����Զ����Թ���ҳ��
	OnAutotest();  
//	CSystem dlg_Sys;
//	dlg_Sys.DoModal();

	INIT_EASYSIZE;  //��ʼ����
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CATE_TESTDlg::DrawButton(CNewButton &newBtn,int BitmapID,int Bitmap2ID,CRect rect,int intBtnID)
{
	if(newBtn)
	{
		newBtn.m_pBmp1.DeleteObject();
		newBtn.m_pBmp2.DeleteObject();		
		newBtn.DestroyWindow();
	}
	newBtn.m_pBmp1.LoadBitmap(BitmapID);
	/*
	int bitmap2ID;
	switch (intBtnID)
	{
	case 1001:
		bitmap2ID=IDB_BITMAP11;
		break;
	case 1002:
		bitmap2ID=IDB_BITMAP12;
		break;
	case 1003:
		bitmap2ID=IDB_BITMAP13;
		break;
	case 1004:
		bitmap2ID=IDB_BITMAP14;
		break;
	case 1005:
		bitmap2ID=IDB_BITMAP15;
		break;
	default:
		break;
	}
	*/
	newBtn.m_pBmp2.LoadBitmap(Bitmap2ID);

	newBtn.Create("NEW",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD,rect,this,intBtnID);  //��̬������ť
}

//��ʼ�����úͰ�����Ӧ  �����Զ����Թ���ҳ��
void CATE_TESTDlg::OnAutotest() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your command handler code here
	UpDateButton(1);  //�л���ť
	if(dlg_ATest)   //���ԶԻ����Ƿ�򿪣����ԶԻ�����CAutoTest
		return;
	if(dlg_InsDoc)
		dlg_InsDoc.DestroyWindow();  //�ر��ͺſ������ڣ��ͺſ���������CInsDocument
	if(dlg_ModifyAd)
		dlg_ModifyAd.DestroyWindow();  //�ر�ϵͳ�����ڣ�ϵͳ��������CSystem   
	CRect rect;
	dlg_ATest.Create(IDD_AUTOTEST,this);   //�����Զ����Է�ģ̬���ڣ��Զ����Դ�����CAutoTest
	dlghand1=dlg_ATest.GetSafeHwnd();
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect); //GetDlgItem���ش�����ָ������ID����Ԫ�صľ��
	ScreenToClient(&rect);
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0); //�ƶ��Զ����Դ��ڵ�Ԥ�����õ�λ��
	dlg_ATest.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч��ʾ�Ի���
	Invalidate(); //�ػ�
}

//������Ӧ   �����ͺſ�������
void CATE_TESTDlg::OnManutest()    
{
	// TODO: Add your control notification handler code here
	UpDateButton(2);   //�л���ť
	if(dlg_InsDoc)   //�ж��ͺſ����Ի����Ƿ��
		return;
	if(dlg_ATest)
		dlg_ATest.DestroyWindow(); //�ر��Զ����Դ���
	if(dlg_ModifyAd)   
		dlg_ModifyAd.DestroyWindow();  //�ر�ϵͳ������
	CRect rect;
	dlg_InsDoc.Create(IDD_INSDOC,this);
	dlghand1=dlg_InsDoc.GetSafeHwnd();
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0); 
	dlg_InsDoc.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч	
	Invalidate(); //�ػ�
}
void CATE_TESTDlg::OnUutdoc() 
{
	// TODO: Add your control notification handler code here
}

//������Ӧ ����ϵͳ���ù���
void CATE_TESTDlg::OnAssistant()   
{
	// TODO: Add your control notification handler code here
	UpDateButton(3);   //�л���ť
	if(dlg_ModifyAd)   //�ж�ϵͳ���ô����Ƿ����
		return;
	if(dlg_InsDoc) 
		dlg_InsDoc.DestroyWindow();  //�ر��ͺſ������ڣ��ͺſ���������CInsDocument
	if(dlg_ATest)
		dlg_ATest.DestroyWindow();  //�ر��Զ����Դ��ڣ��Զ����Դ�����CAutoTest
	CRect rect;
	dlg_ModifyAd.Create(IDD_SYSTEM,this);  //����ϵͳ���ô��ڣ�ϵͳ��������CSystem   
	dlghand1=dlg_ModifyAd.GetSafeHwnd();
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0);//�ƶ�ϵͳ�����ڵ�Ԥ�����õ�λ��
	dlg_ModifyAd.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч��ʾ�Ի���
	Invalidate(); //�ػ�
}

//�˵�������Ӧ����
void CATE_TESTDlg::OnMenuitemAutotest() 
{
	// TODO: Add your command handler code here
	if(dlg_ATest)   //�Զ����Դ����Ƿ����
		return;
	if(dlg_InsDoc)
		dlg_InsDoc.DestroyWindow();//�ر��ͺſ������ڣ��ͺſ���������CInsDocument
	CRect rect;
	dlg_ATest.Create(IDD_AUTOTEST,this);  //�����Զ����Դ��ڣ��Զ����Դ�����CAutoTest
	dlghand1=dlg_ATest.GetSafeHwnd();
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0);//�ƶ��Զ����Դ��ڵ�Ԥ�����õ�λ��
	dlg_ATest.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч��ʾ�Ի���
}
void CATE_TESTDlg::OnMenuSetuser() 
{
	// TODO: Add your command handler code here

	//�����û�������
	if(dlg_SetUser)
		return;
	if(dlg_SetResource)
		dlg_SetResource.DestroyWindow();
	if(dlg_ATest)
		dlg_ATest.DestroyWindow();

	CRect   rect;
	dlg_SetUser.Create(IDD_SET_USER,this);   //����
	dlghand1=dlg_SetUser.GetSafeHwnd();   //��ȡ���ڰ�ȫָ��
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);  //��ȡ����
	ScreenToClient(&rect);  //����ת��
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0);

	dlg_SetUser.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч
}
void CATE_TESTDlg::OnMenuSetsource() 
{
	//������Դ����
	// TODO: Add your command handler code here
	if(dlg_SetResource)
		return;
	if(dlg_SetUser)
		dlg_SetUser.DestroyWindow();
	if(dlg_ATest)
		dlg_ATest.DestroyWindow();

	CRect rect;
	dlg_SetResource.Create(IDD_SET_RESOURCE,this);
	dlghand1=dlg_SetResource.GetSafeHwnd();
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	::MoveWindow(dlghand1,rect.left,rect.top,rect.Width(),rect.Height(),0);
	dlg_SetResource.AnimateWindow(100,AW_BLEND|AW_HOR_POSITIVE);  //������Ч

}

//��̬���Ʋ�ͬ���ܿ�Ŀؼ�
void CATE_TESTDlg::UpDateButton(int intState) //1=�Զ����� 2=�ͺſ��� 3ϵͳ���� 
{                                             // 4=ϵͳ����
	if(intState==1)
	{
		DrawButton(m_newButton_Test,IDB_BITMAP_TEST1,IDB_BITMAP_TEST1,m_rect_Test,10001);
		DrawButton(m_newButton_Model,IDB_BITMAP_MODEL,IDB_BITMAP_MODEL1,m_rect_Model,10002);
		//DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,10003);
		DrawButton(m_newButton_System,IDB_BITMAP_SYSTEM,IDB_BITMAP_SYSTEM1,m_rect_System,10003);
		//DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,1005);
		//DrawButton(m_newButton_Moniter,IDB_BITMAP_MONITER,IDB_BITMAP_MONITER1,m_rect_Moniter,1006);
		DrawButton(m_newButton_Help,IDB_BITMAP_HELP,IDB_BITMAP_HELP1,m_rect_Help,10004);
	}
	if(intState==2)
	{
		DrawButton(m_newButton_Test,IDB_BITMAP_TEST,IDB_BITMAP_TEST1,m_rect_Test,10001);
		DrawButton(m_newButton_Model,IDB_BITMAP_MODEL1,IDB_BITMAP_MODEL1,m_rect_Model,10002);
		//DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,10003);
		DrawButton(m_newButton_System,IDB_BITMAP_SYSTEM,IDB_BITMAP_SYSTEM1,m_rect_System,10003);
//		DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,1005);
//		DrawButton(m_newButton_Moniter,IDB_BITMAP_MONITER,IDB_BITMAP_MONITER1,m_rect_Moniter,1006);
		DrawButton(m_newButton_Help,IDB_BITMAP_HELP,IDB_BITMAP_HELP1,m_rect_Help,10004);
	}
	if(intState==3)
	{
		DrawButton(m_newButton_Test,IDB_BITMAP_TEST,IDB_BITMAP_TEST1,m_rect_Test,10001);
		DrawButton(m_newButton_Model,IDB_BITMAP_MODEL,IDB_BITMAP_MODEL1,m_rect_Model,10002);
		//DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE1,IDB_BITMAP_REMOTE1,m_rect_Remote,10003);
		DrawButton(m_newButton_System,IDB_BITMAP_SYSTEM1,IDB_BITMAP_SYSTEM1,m_rect_System,10003);
//		DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,1005);
//		DrawButton(m_newButton_Moniter,IDB_BITMAP_MONITER,IDB_BITMAP_MONITER1,m_rect_Moniter,1006);
		DrawButton(m_newButton_Help,IDB_BITMAP_HELP,IDB_BITMAP_HELP1,m_rect_Help,10004);
	}
	if(intState==4)
	{
		DrawButton(m_newButton_Test,IDB_BITMAP_TEST,IDB_BITMAP_TEST1,m_rect_Test,10001);
		DrawButton(m_newButton_Model,IDB_BITMAP_MODEL,IDB_BITMAP_MODEL1,m_rect_Model,10002);
		//DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,10003);
		DrawButton(m_newButton_System,IDB_BITMAP_SYSTEM1,IDB_BITMAP_SYSTEM1,m_rect_System,10003);
//		DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE,IDB_BITMAP_REMOTE1,m_rect_Remote,1005);
//		DrawButton(m_newButton_Moniter,IDB_BITMAP_MONITER,IDB_BITMAP_MONITER1,m_rect_Moniter,1006);
		DrawButton(m_newButton_Help,IDB_BITMAP_HELP,IDB_BITMAP_HELP1,m_rect_Help,10004);
	}
	/*if(intState==5)
	{
		DrawButton(m_newButton_Test,IDB_BITMAP_TEST,IDB_BITMAP_TEST1,m_rect_Test,10001);
		DrawButton(m_newButton_Model,IDB_BITMAP_MODEL,IDB_BITMAP_MODEL1,m_rect_Model,10002);
		DrawButton(m_newButton_Remote,IDB_BITMAP_REMOTE1,IDB_BITMAP_REMOTE1,m_rect_Remote,10003);
		DrawButton(m_newButton_System,IDB_BITMAP_SYSTEM,IDB_BITMAP_SYSTEM1,m_rect_System,10004);
		DrawButton(m_newButton_Help,IDB_BITMAP_HELP,IDB_BITMAP_HELP1,m_rect_Help,10005);
	}*/
}

void CATE_TESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CATE_TESTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/*
		HDC hDc,mDc;
		HWND hWnd=this->GetSafeHwnd();
		hDc=::GetDC(hWnd);
		mDc=::CreateCompatibleDC(hDc);
		HBITMAP bg;
		bg=(HBITMAP)::LoadImage(NULL,"aa.bmp",IMAGE_BITMAP,1100,580,LR_LOADFROMFILE);
		::SelectObject(mDc,bg);
		
		StretchBlt(hDc,0,0,1100,580,mDc,0,0,1100,580,SRCCOPY);
		//::BitBlt(hDc,0,0,1100,580,mDc,0,0,SRCAND);
		*/
		CDialog::OnPaint();

		//���ñ���ͼ
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP1);
		m_brush.CreatePatternBrush(&bmp);  //��������ָ��λͼģʽ���߼�ˢ��

		int nBmpWidth, nBmpHeight;
		BITMAP bmInfo;
		bmp.GetBitmap(&bmInfo);
		nBmpWidth=bmInfo.bmWidth;
		nBmpHeight=bmInfo.bmHeight;  //��ȡλͼ��ʵ�ʴ�С

		CRect clientRC;
		GetClientRect(clientRC);  //��ȡ�ͻ�����Ĵ�С

		CDC *pDC=GetDC();  //��ĻDC
		CDC memDC;
		memDC.CreateCompatibleDC(pDC); //�ڴ�DC
		memDC.SelectObject(&bmp);
		pDC->StretchBlt(0,0,clientRC.Width(),clientRC.Height(),&memDC,0,0, nBmpWidth, nBmpHeight, SRCCOPY);   //����λͼ

		memDC.DeleteDC();  
		bmp.DeleteObject();
		ReleaseDC(pDC);//�ͷ�

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CATE_TESTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CATE_TESTDlg::OnMenuBack() 
{
	// TODO: Add your command handler code here
	exit(1);
	
}

void CATE_TESTDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	/* TODO: Add your message handler code here*/
	UPDATE_EASYSIZE;
	if(dlghand1)
	{
    	CRect   rect;
    	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rect);  //��ȡ����
    	ScreenToClient(&rect);  //����ת��
    	::MoveWindow(dlghand,rect.left,rect.top,rect.Width(),rect.Height(),0);
	}
}
void CATE_TESTDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(280,250,fwSide,pRect);
}

void CATE_TESTDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest==HTCAPTION)
		return;
	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CATE_TESTDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CATE_TESTDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CATE_TESTDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	exit(1);
	//CDialog::OnClose();
}

BOOL CATE_TESTDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	else
	return CDialog::PreTranslateMessage(pMsg);
}

void CATE_TESTDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	/*
	CString strTime,strDate,strIndicate;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
	strIndicate=(CString)"������:"+m_userName
		+"\r\n"+(CString)"����:"+strDate
		+"\r\n"+(CString)"ʱ��:"+strTime;
	m_newEdit_Status.SetWindowText(strIndicate);
//	m_newStatic_Status.SetWindowText(strIndicate);
	*/
	//UpdateData(FALSE);
	
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CATE_TESTDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	

	if(nCtlColor!=CTLCOLOR_BTN)
	{
	    return (HBRUSH)m_brush;
	}

	/*
	if(pWnd->GetDlgCtrlID()==10009)
	{ //���ľ�̬��͸��������ɫΪ��ɫ
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	*/
	// TODO: Return a different brush if the default is not desired		
	return hbr;
}

void CATE_TESTDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CATE_TESTDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here

}

BOOL CATE_TESTDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
     m_brush.DeleteObject();
	 
	return CDialog::DestroyWindow();
}