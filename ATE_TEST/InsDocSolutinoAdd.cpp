// InsDocSolutinoAdd.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocSolutinoAdd.h"

#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutinoAdd dialog


CInsDocSolutinoAdd::CInsDocSolutinoAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocSolutinoAdd::IDD, pParent)
{
	m_strKind = "";
	m_strModel = "";
	m_strTemplate = "";
	m_strRefTempPath = "";
	m_bRefer = 0;
	m_strReferModel = "";
}


void CInsDocSolutinoAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocSolutinoAdd)
	DDX_Control(pDX, IDC_LIST_TEMPLATE, m_List);
	DDX_Control(pDX, IDC_EDIT_TEMPLATE_LIST, m_edt1);
	DDX_Control(pDX, IDC_CHECK1, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocSolutinoAdd, CDialog)
	//{{AFX_MSG_MAP(CInsDocSolutinoAdd)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutinoAdd message handlers

void CInsDocSolutinoAdd::OnCheck1() 
{
	m_bRefer = m_check.GetCheck();
	m_List.EnableWindow(m_bRefer);
}

BOOL CInsDocSolutinoAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, "设备类型", LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, "设备型号", LVCFMT_LEFT, 160);
	m_List.InsertColumn(2, "解决方案", LVCFMT_LEFT, 250);
	m_List.InsertColumn(3, "是否同种型号", LVCFMT_CENTER, 110);

	vector <UUTKindList> vKindList;
	vector <FileInfo> vUUTList;

	int n1, nRow = 0;
	CString str1;
	m_strPathArray.RemoveAll();
	m_strModelArray.RemoveAll();

	CXml_UUTKind uutkind;
	CFile_UUTInfo uutinfo;
	uutkind.GetKindList(&vKindList);  //读取型号列表

	CFile_UUTInfo file_UUTInfo;
	vector<FileInfo> vFileinfo1;

	for(int i=0;i<vKindList.size();i++)
	{
		uutinfo.GetUUTList(vKindList[i].m_strKindName, &vUUTList);
		for(int j=0; j<vUUTList.size(); j++)
		{
			if(vKindList[i].m_strKindName == m_strKind && vUUTList[j].m_strFileName == m_strModel)
				str1 = "是";
			else
				str1 = "否";

			vFileinfo1.clear();
			file_UUTInfo.GetSolutionList(vKindList[i].m_strKindName, vUUTList[j].m_strFileName, &vFileinfo1);

			for(int k = 0; k < vFileinfo1.size(); k++)
			{
				if(str1 == "是")
				{
					n1 = 0;
					m_strPathArray.InsertAt(0, vFileinfo1[k].m_strFilePath);
					m_strModelArray.InsertAt(0, vUUTList[j].m_strFileName);
					m_List.InsertItem(n1, vKindList[i].m_strKindName);
					m_List.SetItemText(n1, 1, vUUTList[j].m_strFileName);
					m_List.SetItemText(n1, 2, vFileinfo1[k].m_strFileName);
					m_List.SetItemText(n1, 3, str1);
					nRow++;
				}
				else if(vKindList[i].m_strKindName == m_strKind)
				{
					n1 = nRow;
					m_strPathArray.Add(vFileinfo1[k].m_strFilePath);
					m_strModelArray.Add(vUUTList[j].m_strFileName);
					m_List.InsertItem(n1, vKindList[i].m_strKindName);
					m_List.SetItemText(n1, 1, vUUTList[j].m_strFileName);
					m_List.SetItemText(n1, 2, vFileinfo1[k].m_strFileName);
					m_List.SetItemText(n1, 3, str1);
					nRow++;
				}
			}
		}
		vUUTList.clear();
	}
	m_bRefer = false;
	m_List.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocSolutinoAdd::OnOK() 
{
	CString str1 = "";
	((CEdit*)GetDlgItem(IDC_EDIT_TEMPLATE_LIST))->GetWindowText(str1);
	if(str1 == "")
	{
		AfxMessageBox("请填写解决方案名称!");
		return;
	}

	char cFirst = str1[0];
	if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
	{
		AfxMessageBox("名称首字符不能为符号、数字及空格!");
		return;
	}
	//判断是否与其他解决方案重复
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(str1 == m_List.GetItemText(i, 2))
		{
			if("是" == m_List.GetItemText(i, 3))
			{
				AfxMessageBox("解决方案名称与该型号的其他解决方案重复");
				return;
			}
		}
	}
	if(m_bRefer)
	{
		int n1 = m_List.GetSelectionMark();
		if(n1 < 0)
		{
			AfxMessageBox("请选择需要参照的解决方案, 否则去除“参照其他模板进行添加”勾选框的勾选");
			return;
		}
		if(n1 < m_strPathArray.GetSize())
		{
			m_strRefTempPath = m_strPathArray[n1];
			m_strReferModel  = m_strModelArray[n1];
		}
	}	
	m_strTemplate = str1;
	CDialog::OnOK();
}
