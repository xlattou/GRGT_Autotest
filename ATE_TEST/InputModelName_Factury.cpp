// InputModelName_Factury.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InputModelName_Factury.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputModelName_Factury dialog


CInputModelName_Factury::CInputModelName_Factury(CWnd* pParent /*=NULL*/)
	: CDialog(CInputModelName_Factury::IDD, pParent)
{
	strName = "";
	strFactory = "";
}


void CInputModelName_Factury::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputModelName_Factury)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputModelName_Factury, CDialog)
	//{{AFX_MSG_MAP(CInputModelName_Factury)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputModelName_Factury message handlers

void CInputModelName_Factury::OnOK() 
{
	CString str1, str2;
	((CEdit*)GetDlgItem(IDC_EDIT_MODEL_FACTORY))->GetWindowText(str1);
	((CEdit*)GetDlgItem(IDC_EDIT_MODEL_NAME))->GetWindowText(str2);
	if(str1.GetLength() == 0 || str2.GetLength() == 0)
	{
		AfxMessageBox("输入参数不能为空");
		return;
	}
	char cFirst = str1[0];
	if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
	{
		AfxMessageBox("设备厂家首字符不能为符号、数字及空格!");
		return;
	}
	strName = str2;
	strFactory = str1;
	
	CDialog::OnOK();
}
