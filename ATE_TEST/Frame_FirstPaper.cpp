// Frame_FirstPaper.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frame_FirstPaper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame_FirstPaper dialog


CFrame_FirstPaper::CFrame_FirstPaper(CWnd* pParent /*=NULL*/)
	: CDialog(CFrame_FirstPaper::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrame_FirstPaper)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrame_FirstPaper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrame_FirstPaper)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrame_FirstPaper, CDialog)
	//{{AFX_MSG_MAP(CFrame_FirstPaper)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame_FirstPaper message handlers
