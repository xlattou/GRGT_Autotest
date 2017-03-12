// Lua_Pic_List_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "LuaList.h"

#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg dialog


CLuaList::CLuaList(CWnd* pParent /*=NULL*/)
	: CDialog(CLuaList::IDD, pParent)
{
	m_strKind		= "";
	m_strModel		= "";
	m_strSolution	= "";
	m_strLua		= "";
	m_strRefTempPath	= "";
	m_strReferModel		= "";
	m_strReferSolution  = "";
	m_bRefer = FALSE;
}


void CLuaList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLuaList)
	DDX_Control(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_EDIT_TEMPLATE_LIST, m_Edit);
	DDX_Control(pDX, IDC_LIST_TEMPLATE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLuaList, CDialog)
	//{{AFX_MSG_MAP(Lua_Pic_List_Dlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg message handlers

void CLuaList::OnOK() 
{
	CString str1 = "";
	((CEdit*)GetDlgItem(IDC_EDIT_TEMPLATE_LIST))->GetWindowText(str1);
	if(str1 == "")
	{
		AfxMessageBox("请填写Lua脚本名称!");
		return;
	}
	str1 += ".lua";
	//判断是否与其他解决方案重复
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(str1 == m_List.GetItemText(i, 3))
		{
			if("是" == m_List.GetItemText(i, 4))
			{
				AfxMessageBox("Lua脚本名称与该方案的其他Lua脚本重复");
				return;
			}
		}
	}
	if(m_bRefer)
	{
		int n1 = m_List.GetSelectionMark();
		if(n1 < 0)
		{
			AfxMessageBox("请选择需要参照的解决方案, 否则去除“参照其他脚本进行添加”勾选框的勾选");
			return;
		}
		if(n1 < m_strPathArray.GetSize())
		{
			m_strRefTempPath = m_strPathArray[n1];
		}
	}	
	m_strLua = str1;
	CDialog::OnOK();
}

BOOL CLuaList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, "设备类型", LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, "设备型号", LVCFMT_LEFT, 160);
	m_List.InsertColumn(2, "解决方案", LVCFMT_LEFT, 150);	
	m_List.InsertColumn(3, "Lua脚本", LVCFMT_LEFT, 180);
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
	CPathOperate paOpe; //获得解决方案文件夹路径
	CString strPathUUT = paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\";

	for(int i=0;i<vKindList.size();i++)
	{
		if(vKindList[i].m_strKindName == m_strKind)
		{
			uutinfo.GetUUTList(vKindList[i].m_strKindName, &vUUTList);
			for(int j=0; j<vUUTList.size(); j++)
			{
				vFileinfo1.clear();
				file_UUTInfo.GetSolutionList(vKindList[i].m_strKindName, vUUTList[j].m_strFileName, &vFileinfo1);

				for(int k = 0; k < vFileinfo1.size(); k++)
				{
					CFileFind ff;
					BOOL res;
					str1 = /*strPathUUT + vKindList[i].m_strKindName + "\\TPS\\" + vUUTList[j].m_strFileName + "\\Solution" + "\\" + */
						vFileinfo1[k].m_strFilePath + "\\TestItem\\*.lua";
					res = ff.FindFile(str1);
					//查找Lua脚本
					while(res)
					{
						res=ff.FindNextFile();
						if(ff.IsDots())
							continue;
						if(ff.IsDirectory())
							continue;
						else
						{
							if(vKindList[i].m_strKindName == m_strKind && vUUTList[j].m_strFileName == m_strModel && vFileinfo1[k].m_strFileName == m_strSolution)
								str1 = "是";
							else
								str1 = "否";

							
							if(str1 == "是")
							{
								n1 = 0;
								m_strModelArray.InsertAt(0, vUUTList[j].m_strFileName);
								m_strSolutionArray.InsertAt(0, vFileinfo1[k].m_strFileName);
								m_strPathArray.InsertAt(0, ff.GetFilePath());
							}
							else
							{
								n1 = nRow;							
								m_strModelArray.Add(vUUTList[j].m_strFileName);
								m_strSolutionArray.Add(vFileinfo1[k].m_strFileName);
								m_strPathArray.Add(ff.GetFilePath());
							}
							m_List.InsertItem(n1, vKindList[i].m_strKindName);
							m_List.SetItemText(n1, 1, vUUTList[j].m_strFileName);
							m_List.SetItemText(n1, 2, vFileinfo1[k].m_strFileName);
							m_List.SetItemText(n1, 3, ff.GetFileName());
							m_List.SetItemText(n1, 4, str1);
							nRow++;
						}
					}
				}
			}
			vUUTList.clear();
		}
	}
	m_bRefer = false;
	m_List.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLuaList::OnCheck1() 
{
	m_bRefer = m_check.GetCheck();
	m_List.EnableWindow(m_bRefer);
}
