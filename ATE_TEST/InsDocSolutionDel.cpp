// InsDocSolutionDel.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocSolutionDel.h"
#include "File_UUTInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutionDel dialog


CInsDocSolutionDel::CInsDocSolutionDel(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocSolutionDel::IDD, pParent)
{
	m_strKind = "";
	m_strModel = "";
}


void CInsDocSolutionDel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocSolutionDel)
	DDX_Control(pDX, IDC_LIST_TEMPLATE_DEL, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocSolutionDel, CDialog)
	//{{AFX_MSG_MAP(CInsDocSolutionDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutionDel message handlers

BOOL CInsDocSolutionDel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_List.InsertColumn(0, "序号", LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, "解决方案", LVCFMT_LEFT, 300);

	if(m_strKind == "" || m_strModel == "")
		return FALSE;

	CFile_UUTInfo file_UUTInfo;
	vector<FileInfo> vFileinfo1;
	file_UUTInfo.GetSolutionList(m_strKind, m_strModel, &vFileinfo1);

	int nRow = 0;
	CString str1;
	for(int k = 0; k < vFileinfo1.size(); k++)
	{
		str1.Format("%d", nRow + 1);
		m_List.InsertItem(nRow, str1);
		m_List.SetItemText(nRow, 1, vFileinfo1[k].m_strFileName);
		m_strPathArray1.Add(vFileinfo1[k].m_strFilePath);
		nRow++;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocSolutionDel::OnOK() 
{
	m_strPathArray.RemoveAll();
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(m_List.GetCheck(i))
			m_strPathArray.Add(m_strPathArray1[i]);
	}

	CDialog::OnOK();
}
