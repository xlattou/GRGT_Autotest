// PicList.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "PicList.h"

#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicList dialog


CPicList::CPicList(CWnd* pParent /*=NULL*/)
	: CDialog(CPicList::IDD, pParent)
{
	m_strKind		= "";
	m_strModel		= "";
	m_strSolution	= "";
	m_strPic		= "";
	m_strRefTempPath	= "";
	m_strReferModel		= "";
	m_strReferSolution  = "";
	m_bRefer = FALSE;
}


void CPicList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicList)
	DDX_Control(pDX, IDC_LIST_TEMPLATE, m_List);
	DDX_Control(pDX, IDC_EDIT_TEMPLATE_LIST, m_Edit);
	DDX_Control(pDX, IDC_CHECK1, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPicList, CDialog)
	//{{AFX_MSG_MAP(CPicList)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicList message handlers

void CPicList::OnCheck1() 
{
	m_bRefer = m_check.GetCheck();
	m_List.EnableWindow(m_bRefer);
}

void CPicList::OnOK() 
{
	CString str, str1 = "";
	((CEdit*)GetDlgItem(IDC_EDIT_TEMPLATE_LIST))->GetWindowText(str1);
	if(str1 == "")
	{
		AfxMessageBox("����д����ͼ����!");
		return;
	}
	str = str1.Right(4);
	if(str1.GetLength() < 5 || (str != ".bmp" && str != ".jpg"))
	{
		AfxMessageBox("�ļ���ʽ��д����!ֻ����.bmp��.jpg��ʽ��׺��ͼ��");
		return;
	}
	//�ж��Ƿ���������������ظ�
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(str1 == m_List.GetItemText(i, 3))
		{
			if("��" == m_List.GetItemText(i, 4))
			{
				AfxMessageBox("����ͼ������÷�������������ͼ�ظ�");
				return;
			}
		}
	}
	if(m_bRefer)
	{
		int n1 = m_List.GetSelectionMark();
		if(n1 < 0)
		{
			AfxMessageBox("��ѡ����Ҫ���յĽ������, ����ȥ����������������ͼ������ӡ���ѡ��Ĺ�ѡ");
			return;
		}
		if(n1 < m_strPathArray.GetSize())
		{
			m_strRefTempPath = m_strPathArray[n1];
			CString str2 = m_List.GetItemText(n1, 3);
			if(str1.Right(4) != str2.Right(4))
			{
				AfxMessageBox("��д�Ľ���ͼ��չ������ѡ����յĽ���ͼ����չ������ͬ");
				return;
			}
		}
	}	
	m_strPic = str1;
	
	CDialog::OnOK();
}

BOOL CPicList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, "�豸����", LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, "�豸�ͺ�", LVCFMT_LEFT, 160);
	m_List.InsertColumn(2, "�������", LVCFMT_LEFT, 150);	
	m_List.InsertColumn(3, "����ͼ", LVCFMT_LEFT, 180);
	m_List.InsertColumn(4, "ͬ�������", LVCFMT_CENTER, 90);

	vector <UUTKindList> vKindList;
	vector <FileInfo> vUUTList;

	int n1, nRow = 0;
	CString str1, strName, str2;
	m_strPathArray.RemoveAll();
	m_strModelArray.RemoveAll();
	m_strSolutionArray.RemoveAll();

	CXml_UUTKind uutkind;
	CFile_UUTInfo uutinfo;
	uutkind.GetKindList(&vKindList);  //��ȡ�ͺ��б�

	CFile_UUTInfo file_UUTInfo;
	vector<FileInfo> vFileinfo1;
	CPathOperate paOpe; //��ý�������ļ���·��
	CString strPathUUT = paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\";

	for(int i=0;i<vKindList.size();i++)
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
					vFileinfo1[k].m_strFilePath + "\\TestConfig\\ConnectPic\\*.*";
				res = ff.FindFile(str1);
				//����Lua�ű�
				while(res)
				{
					res=ff.FindNextFile();
					if(ff.IsDots())
						continue;
					if(ff.IsDirectory())
						continue;
					else
					{
						strName = ff.GetFileName();
						if(strName.GetLength() > 4)
						{
							str2 = strName.Right(4);
							str2.MakeUpper();
							if(str2 == ".BMP" || str2 == ".JPG")
							{
								if(vKindList[i].m_strKindName == m_strKind && vUUTList[j].m_strFileName == m_strModel && vFileinfo1[k].m_strFileName == m_strSolution)
									str1 = "��";
								else
									str1 = "��";

								
								if(str1 == "��")
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
								m_List.SetItemText(n1, 3, strName);
								m_List.SetItemText(n1, 4, str1);
								nRow++;
							}
						}
					}
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
