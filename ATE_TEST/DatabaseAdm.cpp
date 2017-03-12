// DatabaseAdm.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "DatabaseAdm.h"
#define BACKGROUND RGB(0,200,100)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseAdm dialog


CDatabaseAdm::CDatabaseAdm(CWnd* pParent /*=NULL*/)
	: CDialog(CDatabaseAdm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatabaseAdm)
	m_DataBasePath = _T("");
	//}}AFX_DATA_INIT
}

BOOL CDatabaseAdm::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(BACKGROUND);
	INIT_EASYSIZE;
	return true;
}

HBRUSH CDatabaseAdm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CDatabaseAdm::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	
	return CDialog::DestroyWindow();
}


void CDatabaseAdm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseAdm)
	DDX_Text(pDX, IDC_DATABASE_SEL, m_DataBasePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatabaseAdm, CDialog)
	//{{AFX_MSG_MAP(CDatabaseAdm)
	ON_BN_CLICKED(IDC_BUTTON1, OnBtnOpen)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CDatabaseAdm)
	//EASYSIZE(IDC_BUTTON1,IDC_DATABASE_SEL,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
	//EASYSIZE(IDC_DATABASE_SEL,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_HCENTER)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CDatabaseAdm message handlers

void CDatabaseAdm::OnBtnOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Access DataBase(*.mdb)|*.mdb|SQL DataBase(*.MDF)|*.MDF||",AfxGetMainWnd());	//构造文件打开对话框
	CString strPath,strText="";							//声明变量
	if(dlg.DoModal() == IDOK)							//判断是否按下"打开"按钮
	{
		strPath = dlg.GetPathName();					//获得文件路径
		m_DataBasePath = strPath;				//显示文件路径
		UpdateData(FALSE);
	}
}

void CDatabaseAdm::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	//UPDATE_EASYSIZE;
	// TODO: Add your message handler code here
	
}
