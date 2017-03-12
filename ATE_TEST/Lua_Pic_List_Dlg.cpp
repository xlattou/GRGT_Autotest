// Lua_Pic_List_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Lua_Pic_List_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg dialog


Lua_Pic_List_Dlg::Lua_Pic_List_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Lua_Pic_List_Dlg::IDD, pParent)
{
	m_nType = 0;
	m_strKind = "";
	m_strModel = "";
	m_strTemplate = "";
	m_strRefTempPath = "";
	m_strReferModel;
	m_bRefer = FALSE;
	m_bSameName = FALSE;
}


void Lua_Pic_List_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Lua_Pic_List_Dlg)
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_EDIT_TEMPLATE_LIST, m_Edit);
	DDX_Control(pDX, IDC_LIST_TEMPLATE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Lua_Pic_List_Dlg, CDialog)
	//{{AFX_MSG_MAP(Lua_Pic_List_Dlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg message handlers

void Lua_Pic_List_Dlg::OnOK() 
{
	
	
	CDialog::OnOK();
}

BOOL Lua_Pic_List_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str1;
	if(m_nType)
	{
		SetWindowText("请选择需要参照的其他Lua脚本");
		((CButton*)GetDlgItem(IDC_CHECK2))->SetWindowText("与参照的接线图同名");
		((CStatic*)GetDlgItem(65535))->SetWindowText("接线图名");
		str1 = "Lua脚本";
	}
	else
		str1 = "接线图";

	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, "设备类型", LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, "设备型号", LVCFMT_LEFT, 160);
	m_List.InsertColumn(2, "解决方案", LVCFMT_LEFT, 150);	
	m_List.InsertColumn(3, str1, LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "同解决方案", LVCFMT_CENTER, 90);

	vector <UUTKindList> vKindList;
	vector <FileInfo> vUUTList;

	int n1, nRow = 0;
	CString str1;
	m_strPathArray.RemoveAll();
	m_strModelArray.RemoveAll();
	m_strSolutionArray.RemoveAll();

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
			if(vUUTList[j].m_strFileName == m_strModel)
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

				}
				else
				{
					n1 = nRow;
					m_strPathArray.Add(vFileinfo1[k].m_strFilePath);
					m_strModelArray.Add(vUUTList[j].m_strFileName);
				}
				m_List.InsertItem(n1, vKindList[i].m_strKindName);
				m_List.SetItemText(n1, 1, vUUTList[j].m_strFileName);
				m_List.SetItemText(n1, 2, vFileinfo1[k].m_strFileName);
				m_List.SetItemText(n1, 3, str1);
				nRow++;
			}
		}
		vUUTList.clear();
	}
	m_bRefer = false;
	m_List.EnableWindow(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Lua_Pic_List_Dlg::OnCheck1() 
{
	m_bRefer = m_check.GetCheck();
	m_List.EnableWindow(m_bRefer);
}

void Lua_Pic_List_Dlg::OnCheck2() 
{
	BOOL m_bSameName = m_check2.GetCheck();
	m_Edit.EnableWindow(m_bSameName);
	if(m_check2.GetCheck())
		m_Edit.SetWindowText("");
	
}
