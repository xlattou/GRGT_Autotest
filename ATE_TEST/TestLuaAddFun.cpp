// TestLuaAddFun.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "TestLuaAddFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TestLuaAddFun dialog


TestLuaAddFun::TestLuaAddFun(CWnd* pParent /*=NULL*/)
	: CDialog(TestLuaAddFun::IDD, pParent)
{
	m_bGetPara = false;
}


void TestLuaAddFun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TestLuaAddFun)
	DDX_Control(pDX, IDC_LIST_TEST_LUA_ADD_FUN, m_List_Para);
	DDX_Control(pDX, IDC_EDIT_FUN_LUA, m_edt_Lua);
	DDX_Control(pDX, IDC_EDIT_FUN_C, m_edt_C);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TestLuaAddFun, CDialog)
	//{{AFX_MSG_MAP(TestLuaAddFun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TestLuaAddFun message handlers

void TestLuaAddFun::OnOK()
{
	CString str1;
	m_strGetParaArray.RemoveAll();
	for(int i = 0; i < m_List_Para.GetItemCount(); i++)
	{
		str1 = m_List_Para.GetItemText(i, 2);
		if(str1 == "")
		{
			str1.Format("%d", i + 1);
			AfxMessageBox("参数序号" + str1 + "的Lua参数为空, 请重新填写");
			return;
		}
		m_strGetParaArray.Add(str1);
	}
	m_bGetPara = true;
	
	CDialog::OnOK();
}

BOOL TestLuaAddFun::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwStyle=m_List_Para.GetExtendedStyle();
	m_List_Para.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List_Para.InsertColumn(0, "参数序号", LVCFMT_LEFT, 80);
	m_List_Para.InsertColumn(1, "C参数原型", LVCFMT_LEFT, 220);
	m_List_Para.InsertColumn(2, "Lua参数", LVCFMT_LEFT, 220);
	CString str, str1 = "my" + m_strInsType + ":" + m_strEngineFunName + "(";
	for(int i = 0; i < m_strParaArray.GetSize(); i++)
	{
		str.Format("%d", i + 1);
		str1 += "参数" + str + ",";
		m_List_Para.InsertItem(i, str);
		m_List_Para.SetItemText(i, 1, m_strParaArray[i]);
	}
	if(str1.Right(1) == ",")
		str1 = str1.Left(str1.GetLength() - 1);
	str1 += ")";
	m_edt_C.SetWindowText(m_strTestFunDescibe);
	m_edt_Lua.SetWindowText(str1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
