// SaveAdm.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "SaveAdm.h"
#define BACKGROUND RGB(0,200,100)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveAdm dialog


CSaveAdm::CSaveAdm(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveAdm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveAdm)
	m_SavePath = _T("");
	//}}AFX_DATA_INIT
}


void CSaveAdm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveAdm)
	DDX_Text(pDX, IDC_SAVE_PATH, m_SavePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveAdm, CDialog)
	//{{AFX_MSG_MAP(CSaveAdm)
	ON_BN_CLICKED(IDC_SEL_SAVE_PATH, OnSelSavePath)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveAdm message handlers

void CSaveAdm::OnSelSavePath() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"",AfxGetMainWnd());	//�����ļ��򿪶Ի���
	CString strPath,strText="";							//��������
	if(dlg.DoModal() == IDOK)							//�ж��Ƿ���"��"��ť
	{
		strPath = dlg.GetPathName();					//����ļ�·��
		m_SavePath = strPath;				//��ʾ�ļ�·��
		UpdateData(FALSE);
	}
}

BOOL CSaveAdm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(BACKGROUND);
	return TRUE;
}

HBRUSH CSaveAdm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);//return (HBRUSH)m_brush;
	}	
	
	if(nCtlColor==CTLCOLOR_STATIC)
	{ //���ľ�̬��͸��������ɫΪ��ɫ
		pDC->SetBkMode(BACKGROUND);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);//(HBRUSH)m_brush;
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CSaveAdm::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	
	return CDialog::DestroyWindow();
}