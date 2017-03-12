// InsDocTempAddTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTempAddTemplate.h"
#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempAddTemplate dialog


CInsDocTempAddTemplate::CInsDocTempAddTemplate(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocTempAddTemplate::IDD, pParent)
{
	m_strKind = "";
	m_strModel = "";
	m_strTemplate = "";
	m_strRefTempPath = "";
	m_bRefer = 0;
	m_strReferModel = "";
}


void CInsDocTempAddTemplate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocTempAddTemplate)
	DDX_Control(pDX, IDC_CHECK1, m_chk_Refer);
	DDX_Control(pDX, IDC_LIST_TEMPLATE, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocTempAddTemplate, CDialog)
	//{{AFX_MSG_MAP(CInsDocTempAddTemplate)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempAddTemplate message handlers

BOOL CInsDocTempAddTemplate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CStatic*)GetDlgItem(IDC_STATIC_TEMPLATE_LIST))->SetWindowText(m_strModel);

	DWORD dwStyle=m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "设备类型", LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, "设备型号", LVCFMT_LEFT, 160);
	m_list.InsertColumn(2, "模板", LVCFMT_LEFT, 250);
	m_list.InsertColumn(3, "是否同种型号", LVCFMT_CENTER, 110);

	vector <UUTKindList> vKindList;
	vector <FileInfo> vUUTList;

	int n1, nRow = 0;
	CString str1;
	m_strPathArray.RemoveAll();
	m_strModelArray.RemoveAll();

	CXml_UUTKind uutkind;
	CFile_UUTInfo uutinfo;
	uutkind.GetKindList(&vKindList);  //读取型号列表

	BOOL res=FALSE;
	CFileFind ff;
	for(int i=0;i<vKindList.size();i++)
	{
		if(vKindList[i].m_strKindName == m_strKind)
		{
			uutinfo.GetUUTList(vKindList[i].m_strKindName, &vUUTList);
			for(int j=0; j<vUUTList.size(); j++)
			{
				if(vUUTList[j].m_strFileName == m_strModel)
					str1 = "是";
				else
					str1 = "否";
				res = FALSE;
				CFileFind ff;
				res=ff.FindFile(vUUTList[j].m_strFilePath + "\\Document\\" + vUUTList[j].m_strFileName + "*.xml");
				while(res)
				{
					res=ff.FindNextFile();
					if(str1 == "是")
					{
						n1 = 0;
						m_strPathArray.InsertAt(0, ff.GetFilePath());
						m_strModelArray.InsertAt(0, vUUTList[j].m_strFileName);
						m_list.InsertItem(n1, vKindList[i].m_strKindName);
						m_list.SetItemText(n1, 1, vUUTList[j].m_strFileName);
						m_list.SetItemText(n1, 2, ff.GetFileTitle());
						m_list.SetItemText(n1, 3, str1);
						nRow++;
					}
					else
					{
						n1 = nRow;
						m_strPathArray.Add(ff.GetFilePath());
						m_strModelArray.Add(vUUTList[j].m_strFileName);
						m_list.InsertItem(n1, vKindList[i].m_strKindName);
						m_list.SetItemText(n1, 1, vUUTList[j].m_strFileName);
						m_list.SetItemText(n1, 2, ff.GetFileTitle());
						m_list.SetItemText(n1, 3, str1);
						nRow++;
					}
				}
			}
			vUUTList.clear();
			break;
		}
	}
	m_bRefer = false;
	m_list.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocTempAddTemplate::OnOK() 
{
	CString str1 = "";
	((CEdit*)GetDlgItem(IDC_EDIT_TEMPLATE_LIST))->GetWindowText(str1);
	if(str1 == "")
		str1 = m_strModel;
	/*{
		AfxMessageBox("请填写模板名称!");
		return;
	}*/
	else
		str1 = m_strModel + " " + str1;
	//判断是否与其他模板重复l
	for(int i = 0; i < m_list.GetItemCount(); i++)
	{
		if(str1 == m_list.GetItemText(i, 2))
		{
			if("是" == m_list.GetItemText(i, 3))
			{
				AfxMessageBox("模板名称与该型号的其他模板重复");
				return;
			}
		}

	}
	if(m_bRefer)
	{
		int n1 = m_list.GetSelectionMark();
		if(n1 < 0)
		{
			AfxMessageBox("请选择需要参照的模板, 否则去除“参照其他模板进行添加”勾选框的勾选");
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

void CInsDocTempAddTemplate::OnCheck1() 
{
	m_bRefer = m_chk_Refer.GetCheck();
	m_list.EnableWindow(m_bRefer);
}
