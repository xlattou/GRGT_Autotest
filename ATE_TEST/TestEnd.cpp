// TestEnd.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "TestEnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestEnd dialog


CTestEnd::CTestEnd(CWnd* pParent /*=NULL*/)
	: CDialog(CTestEnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestEnd)
	m_strConclusion = _T("");
	m_bReport = FALSE;
	m_bSave = FALSE;
	//}}AFX_DATA_INIT
}

CTestEnd::CTestEnd(CString strConclusion,CWnd* pParent)
: CDialog(CTestEnd::IDD, pParent)
{
	m_strConclusion=strConclusion;
}

void CTestEnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestEnd)
	DDX_Control(pDX, IDC_COMBO_RESULT, m_cb_Result);
	DDX_Text(pDX, IDC_STATIC_CONCLUSION, m_strConclusion);
	DDX_Check(pDX, IDC_CHECK_REPORT, m_bReport);
	DDX_Check(pDX, IDC_CHECK_SAVE, m_bSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestEnd, CDialog)
	//{{AFX_MSG_MAP(CTestEnd)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestEnd message handlers

BOOL CTestEnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP7);
	m_brush.CreatePatternBrush(&bmp);
	m_bSave=TRUE;
	m_bReport=TRUE;
	if(m_strConclusion=="Fail")
	{
		m_cb_Result.Clear();
		m_cb_Result.AddString("按校准结果使用");		
	}
	m_cb_Result.SetCurSel(0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestEnd::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	m_cb_Result.GetLBText(m_cb_Result.GetCurSel(),m_strResult);
	UpdateData();
	CDialog::OnOK();
	
}

HBRUSH CTestEnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
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
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CTestEnd::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	return CDialog::DestroyWindow();
}
