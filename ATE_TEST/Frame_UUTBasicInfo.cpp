// Frame_UUTBasicInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frame_UUTBasicInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame_UUTBasicInfo dialog


CFrame_UUTBasicInfo::CFrame_UUTBasicInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CFrame_UUTBasicInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrame_UUTBasicInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrame_UUTBasicInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrame_UUTBasicInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrame_UUTBasicInfo, CDialog)
	//{{AFX_MSG_MAP(CFrame_UUTBasicInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame_UUTBasicInfo message handlers
