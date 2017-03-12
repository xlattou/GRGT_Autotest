// WebAdm.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "WebAdm.h"
#include "windows.h"
#include "EasySize.h"
#define BACKGROUND RGB(0,200,100)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebAdm dialog


CWebAdm::CWebAdm(CWnd* pParent /*=NULL*/)
	: CDialog(CWebAdm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebAdm)
	m_IPP = _T("");
	m_port = _T("");
	//}}AFX_DATA_INIT
}


void CWebAdm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebAdm)
	DDX_Text(pDX, IDC_IP_PATH, m_IPP);
	DDX_Text(pDX, IDC_PORT, m_port);
	//}}AFX_DATA_MAP
}

BOOL CWebAdm::OnInitDialog()
{
	CDialog::OnInitDialog();

	char hostname[MAX_PATH];
	gethostname(hostname,MAX_PATH);

	m_brush.CreateSolidBrush(BACKGROUND);
	hostent* ptent = gethostbyname(hostname);
	if(ptent)
	{
		ip = inet_ntoa(*(in_addr*)ptent->h_addr_list[0]);
		m_IPP = ip;
		UpdateData(FALSE);
	}

	INIT_EASYSIZE;
	return true;
}

HBRUSH CWebAdm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CWebAdm::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	
	return CDialog::DestroyWindow();
}


BEGIN_MESSAGE_MAP(CWebAdm, CDialog)
	//{{AFX_MSG_MAP(CWebAdm)
	ON_BN_CLICKED(IDC_SET_WEB, OnSetWeb)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CWebAdm)
	EASYSIZE(IDC_SET_WEB,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER|ES_VCENTER)
	EASYSIZE(IDC_PORT,ES_BORDER,ES_KEEPSIZE,ES_BORDER,IDC_SET_WEB,ES_HCENTER)
	EASYSIZE(IDC_STATIC_PORT,ES_KEEPSIZE,ES_KEEPSIZE,IDC_PORT,IDC_SET_WEB,0)
	EASYSIZE(IDC_IP_PATH,ES_BORDER,ES_KEEPSIZE,ES_BORDER,IDC_PORT,ES_HCENTER)
	EASYSIZE(IDC_STATIC_PATH,ES_KEEPSIZE,ES_KEEPSIZE,IDC_IP_PATH,IDC_PORT,0)	
	//EASYSIZE(IDC_STATIC_NAME)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CWebAdm message handlers

void CWebAdm::OnSetWeb() 
{
	// TODO: Add your control notification handler code here

	UpdateData();

	int iBindResult=-1;//绑定结果
	int iport;
	if(m_port == "")
	{
		MessageBox("请输入端口号");
		return;
	}
	else
	{
		iport = _ttoi(m_port);
	}

	m_socket = socket(AF_INET,SOCK_STREAM,0);;
	struct sockaddr_in socketAddr;
	CString strTmp;
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(iport);
	socketAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	//绑定地址信息
	iBindResult=bind(m_socket,(struct sockaddr*)&socketAddr,sizeof(sockaddr));
	if(iBindResult==0)
	{
		strTmp.Format("网络设置成功!\nIP = %s\nport = %d",ip,iport);
		MessageBox(strTmp);
	}
	else
	{
		MessageBox("绑定端口失败!");
		return;
	}
}

void CWebAdm::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	UPDATE_EASYSIZE;
	// TODO: Add your message handler code here
	
}
