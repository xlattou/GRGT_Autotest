// ModelList.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ModelList.h"
#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelList dialog


CModelList::CModelList(CWnd* pParent /*=NULL*/)
	: CDialog(CModelList::IDD, pParent)
{
	m_strKind = "";
	m_strReferModelPath = "";
	m_bReferSameKind = false;
}


void CModelList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelList)
	DDX_Control(pDX, IDC_LIST_MODEL, m_list_Model);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModelList, CDialog)
	//{{AFX_MSG_MAP(CModelList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelList message handlers

void CModelList::OnOK() 
{
	int n1 = m_list_Model.GetSelectionMark();
	if(n1 < m_strPathArray.GetSize())
	{
		m_strReferModelPath = m_strPathArray[n1];
		CString str1 = m_list_Model.GetItemText(n1, 2);
		if(str1 = "是")
			m_bReferSameKind = true;
	}
	CDialog::OnOK();
}

BOOL CModelList::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	DWORD dwStyle=m_list_Model.GetExtendedStyle();
	m_list_Model.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_Model.InsertColumn(0, "设备类型", LVCFMT_LEFT, 120);
	m_list_Model.InsertColumn(1, "设备型号", LVCFMT_LEFT, 160);
	m_list_Model.InsertColumn(2, "是否同种类型", LVCFMT_CENTER, 110);

	vector <UUTKindList> vKindList;
	vector <FileInfo> vUUTList;

	int nRow = 0;
	CString str1;
	m_strPathArray.RemoveAll();

	CXml_UUTKind uutkind;
	CFile_UUTInfo uutinfo;
	uutkind.GetKindList(&vKindList);  //读取型号列表
	for(int i=0;i<vKindList.size();i++)
	{
		if(vKindList[i].m_strKindName == m_strKind)
		{	str1 = "是";
		/*else
			str1 = "否";*/
		uutinfo.GetUUTList(vKindList[i].m_strKindName, &vUUTList);
		for(int j=0;j<vUUTList.size();j++)
		{
			m_list_Model.InsertItem(nRow, vKindList[i].m_strKindName);
			m_list_Model.SetItemText(nRow, 1, vUUTList[j].m_strFileName);
			m_list_Model.SetItemText(nRow, 2, str1);
			m_strPathArray.Add(vUUTList[j].m_strFilePath);
			nRow++;
		}
		}
		vUUTList.clear();
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
