// InsDocTempDel.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTempDel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempDel dialog


CInsDocTempDel::CInsDocTempDel(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocTempDel::IDD, pParent)
{
	m_strDir = "";
}


void CInsDocTempDel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocTempDel)
	DDX_Control(pDX, IDC_LIST_TEMPLATE_DEL, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocTempDel, CDialog)
	//{{AFX_MSG_MAP(CInsDocTempDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempDel message handlers

BOOL CInsDocTempDel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwStyle=m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, "ÐòºÅ", LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, "Ä£°åÃû³Æ", LVCFMT_LEFT, 300);

	if(m_strDir == "")
		return FALSE;

	BOOL res=FALSE;
	CFileFind ff;
	res=ff.FindFile(m_strDir + "\\" + "*.xml");
	int nRow = 0;

	CString str1;
	while(res)
	{
		res=ff.FindNextFile();
		str1.Format("%d", nRow + 1);
		m_list.InsertItem(nRow, str1);
		m_list.SetItemText(nRow, 1, ff.GetFileTitle());
		nRow++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocTempDel::OnOK() 
{
	m_strTemplateArray.RemoveAll();
	for(int i = 0; i < m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
			m_strTemplateArray.Add(m_list.GetItemText(i, 1));
	}
	
	CDialog::OnOK();
}
