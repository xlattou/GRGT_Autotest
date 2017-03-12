// Edt_Lua_Pic.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Edt_Lua_Pic.h"
#include "PicList.h"
#include "LuaList.h"
#include "PathOperate.h"
#include "InsDocSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdt_Lua_Pic dialog


CEdt_Lua_Pic::CEdt_Lua_Pic(CWnd* pParent /*=NULL*/)
	: CDialog(CEdt_Lua_Pic::IDD, pParent)
{
	m_strSoluDirPath = "";
	m_strSolution = "";
	m_strKind = "";
	m_strModel = "";
}


void CEdt_Lua_Pic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEdt_Lua_Pic)
	DDX_Control(pDX, IDC_LIST2, m_List_Pic);
	DDX_Control(pDX, IDC_LIST1, m_List_Lua);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEdt_Lua_Pic, CDialog)
	//{{AFX_MSG_MAP(CEdt_Lua_Pic)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdt_Lua_Pic message handlers

void CEdt_Lua_Pic::OnButton1() //增加脚本
{
	CLuaList List1;
	CString strPath;
	List1.m_strKind = m_strKind;
	List1.m_strModel = m_strModel;
	List1.m_strSolution = m_strSolution;
	List1.DoModal();
	if(List1.m_strLua == "")
		return;

	strPath = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestItem\\" + List1.m_strLua;
	if(List1.m_strRefTempPath != "")
	{
		CopyFile(List1.m_strRefTempPath, strPath, FALSE);// 拷贝文件
		TestLua(strPath);
	}
	else
	{
		CPathOperate paOpe;
		CString str1;
		str1 = paOpe.GetAppPath();

		CopyFile(str1 + "\\temp\\Template.lua", strPath, FALSE);// 拷贝文件
		TestLua(strPath);
	}
	InitLua();
}

void CEdt_Lua_Pic::OnButton2() //删除脚本
{
	int nI = m_List_Lua.GetSelectionMark();
	if(nI < 0)
		return;
	CString str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestItem\\" + m_List_Lua.GetItemText(nI, 0);
	if(AfxMessageBox("确定要删除[" + str1 + "]脚本吗?",MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)==IDYES)
		DeleteFile(str1);
	InitLua();	
}

void CEdt_Lua_Pic::OnButton3() //修改脚本
{
	int nI = m_List_Lua.GetSelectionMark();
	if(nI < 0)
	{
		AfxMessageBox("未选择需要修改的脚本,请重新选择");
		return;
	}
	CString strPath = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestItem\\" + m_List_Lua.GetItemText(nI, 0);
	TestLua(strPath);
}

void CEdt_Lua_Pic::OnButton4() //增加图片
{
	CPicList List1;
	List1.m_strKind = m_strKind;
	List1.m_strModel = m_strModel;
	List1.m_strSolution = m_strSolution;
	List1.DoModal();	
	if(List1.m_strPic == "")
		return;

	CString strPath = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestConfig\\ConnectPic\\" + List1.m_strPic;
	if(List1.m_strRefTempPath != "")
		CopyFile(List1.m_strRefTempPath, strPath, FALSE);// 拷贝文件
	else
	{		
		CPathOperate paOpe;
		CString str1;
		str1 = paOpe.GetAppPath();
		
		CopyFile(str1 + "\\temp\\Template" + List1.m_strPic.Right(4), strPath, FALSE);// 拷贝图片文件
		char buffer[MAX_PATH];
		GetShortPathName(strPath.GetBuffer(0), buffer, sizeof(buffer));
		ShellExecute(NULL, "open", "mspaint.exe", buffer, NULL, SW_SHOWNORMAL);
	}
	InitPic();
}

void CEdt_Lua_Pic::OnButton5() //修改图片
{
	int nI = m_List_Pic.GetSelectionMark();
	if(nI < 0)
		return;
	CString str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestConfig\\ConnectPic\\" + m_List_Pic.GetItemText(nI, 0);
	if(AfxMessageBox("确定要删除[" + str1 + "]接线图吗?",MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)==IDYES)
		DeleteFile(str1);
	InitPic();		
}

void CEdt_Lua_Pic::OnButton6() //删除图片
{
	int nI = m_List_Pic.GetSelectionMark();
	if(nI < 0)
		return;
	CString strPath = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestConfig\\ConnectPic\\" + m_List_Pic.GetItemText(nI, 0);
	char buffer[MAX_PATH];
	GetShortPathName(strPath.GetBuffer(0), buffer, sizeof(buffer));
	CPathOperate paOpe;
	CString str1;
	str1 = paOpe.GetStartPath();
	ShellExecute(NULL, "open", "mspaint.exe", buffer, NULL, SW_SHOWNORMAL);
}

BOOL CEdt_Lua_Pic::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List_Lua.InsertColumn(0, "Lua脚本", LVCFMT_LEFT, 300);
	m_List_Pic.InsertColumn(0, "接线图", LVCFMT_LEFT, 300);
	if(m_strSoluDirPath == "" || m_strSolution == "")
		return FALSE;

	InitLua();
	InitPic();

	//ShowWindow(SW_SHOWMAXIMIZED);
	
	return TRUE;
}

BOOL CEdt_Lua_Pic::InitLua()
{
	if(m_strSoluDirPath == "" || m_strSolution == "")
		return FALSE;

	int nI = 0;
	m_List_Lua.DeleteAllItems();
	CString str1, str2;
	CFileFind ff;
	BOOL res;
	str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestItem\\*.lua";
	res=ff.FindFile(str1);
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
			m_List_Lua.InsertItem(nI, ff.GetFileName());
			nI++;
		}
	}
	return TRUE;
}

BOOL CEdt_Lua_Pic::InitPic()
{
	if(m_strSoluDirPath == "" || m_strSolution == "")
		return FALSE;

	int nI = 0;
	m_List_Pic.DeleteAllItems();
	CString str1, str2;
	CFileFind ff;
	BOOL res;

	str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestConfig\\ConnectPic\\*.*";
	res=ff.FindFile(str1);
	nI = 0;
	//查找接线图
	while(res)
	{
		res=ff.FindNextFile();
		if(ff.IsDots())
			continue;
		if(ff.IsDirectory())
			continue;
		else
		{
			str1 = ff.GetFileName();
			if(str1.GetLength() > 4)
			{
				str2 = str1.Right(4);
				str2.MakeUpper();
				if(str2 == ".BMP" || str2 == ".DIB" || str2 == ".JPG" || str2 == ".JPE" || str2 == ".PNG" || str2 == ".PBM" || str2 == ".PGM" || str2 == ".PPM")
				{
					m_List_Pic.InsertItem(nI, str1);
					nI++;
				}
			}
		}
	}
	return TRUE;
}

void CEdt_Lua_Pic::TestLua(CString strLuaPath)
{
	
	CFileFind ff;
	BOOL bFinded = ff.FindFile(strLuaPath);
	bool bLuaExist;
	while (bFinded)
	{
		bFinded = ff.FindNextFile();
		
		if (ff.IsDots())
			continue;		
		else if (ff.IsDirectory())
			continue;
		else
			bLuaExist = true;
	}
	ff.Close();

	if(bLuaExist)
	{
		TESTLUA TestLua;
		TestLua.m_strPath  = strLuaPath;
		TestLua.m_strSoluDirPath = m_strSoluDirPath;
		TestLua.m_strSolution = m_strSolution;
		TestLua.m_strKind = m_strKind;
		TestLua.m_strModel = m_strModel;
		TestLua.DoModal();
	}
	else
		AfxMessageBox("Lua脚本不存在或创建失败,请重新创建!");
}
