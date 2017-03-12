// InsDocSolution.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocSolution.h"
#include "Xml_Bll_UUTItem_Tem.h"
#include "File_UUTInfo.h"
#include "PathOperate.h"
#include "Ini.h"
#include "XmlFile_Ope.h"
#include "Xml_Bll_UUTItem.h"
#include "Xml_UUTInfo.h"
#include "InsDocSolutinoAdd.h"
#include "InsDocSolutionDel.h"
#include "Tool.h"
#include "Edt_Lua_Pic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolution dialog


CInsDocSolution::CInsDocSolution(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocSolution::IDD, pParent)
{
	m_strKind = "";
	m_strModel = "";
	m_strSolution = "";
	m_WindowShow = UUT;
}


void CInsDocSolution::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocSolution)
	DDX_Control(pDX, IDC_STATIC_LUA_PIC, m_stc_Lua_Pic);
	DDX_Control(pDX, IDC_GROUP_SOLUTION, m_group_Solution);
	DDX_Control(pDX, IDC_PIC_UUT, m_pic_UUT);
	DDX_Control(pDX, IDC_PIC_LUA, m_pic_Lua);
	DDX_Control(pDX, IDC_BUTTON_SOLUTION_CHANGE, m_btn_Solution_Change);
	DDX_Control(pDX, IDC_BUTTON_EDT_LUA_PIC, m_btn_Edt_Lua_Pic);
	DDX_Control(pDX, IDC_BUTTON_DEL_TESTSOLUTION, m_btn_Del_Solution);
	DDX_Control(pDX, IDC_STATIC_DRIVER_NAME_INS2, m_stc_Drive_Name_UUT);
	DDX_Control(pDX, IDC_COMBO_DRIVER_NAME2, m_com_Drive_UUT);
	DDX_Control(pDX, IDC_BUTTON_DRIVER_NAME2, m_btn_Drive_Name_UUT);
	DDX_Control(pDX, IDC_EDIT_UUT_NAME, m_edt_UUT_Name);
	DDX_Control(pDX, IDC_BUTTON_SAVE_UUT, m_btn_Save_UUT);
	DDX_Control(pDX, IDC_BUTTON_SAVE_INS, m_btn_Save_Ins);
	DDX_Control(pDX, IDC_BUTTON_SAVE_SOLUTION, m_btn_Save_Lua);
	DDX_Control(pDX, IDC_STATIC_DRIVER_NAME_INS, m_stc_Driver_Name_Ins);
	DDX_Control(pDX, IDC_BUTTON_DRIVER_NAME, m_btn_Driver_Name_Ins);
	DDX_Control(pDX, IDC_COMBO_DRIVER_NAME, m_com_Drive_Name);
	DDX_Control(pDX, IDC_STATIC_UUT_ADDR, m_stc_UUT_Addr);
	DDX_Control(pDX, IDC_STATIC_ADDRESS_INS, m_stc_Ins_Address);
	DDX_Control(pDX, IDC_COMBO_INS, m_com_Ins);
	DDX_Control(pDX, IDC_EDIT_ADDRESS_INS, m_edt_Ins_Address);
	DDX_Control(pDX, IDC_EDIT_UUT_ADDRESS, m_edt_UUT_Address);
	DDX_Control(pDX, IDC_GROUP_INS_INSDOC, m_group_Ins);
	DDX_Control(pDX, IDC_GROUP_UNIT_UNDER_TEST, m_group_UUT);
	DDX_Control(pDX, IDC_BUTTON_ADD_TESTSOLUTION, m_btn_Add_Solution);
	DDX_Control(pDX, IDC_COMBO_SOLUTION_INSDOC, m_com_Solution);
	DDX_Control(pDX, IDC_LIST_INS_INSDOC, m_list_Ins);
	DDX_Control(pDX, IDC_LIST_LUA, m_list_Lua);
	DDX_Control(pDX, IDC_LIST_UNIT_UNDER_TEST, m_list_UUT);
	DDX_Control(pDX, IDC_STATIC_INS_INSDOC, m_stc_Ins);
	DDX_Control(pDX, IDC_STATIC_UNIT_UNDER_TEST, m_stc_UUT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocSolution, CDialog)
	//{{AFX_MSG_MAP(CInsDocSolution)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_ADD_TESTSOLUTION, OnButtonAddTestsolution)
	ON_CBN_SELCHANGE(IDC_COMBO_SOLUTION_INSDOC, OnSelchangeComboSolutionInsdoc)
	ON_BN_CLICKED(IDC_BUTTON_DRIVER_NAME, OnButtonDriverName)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_UUT, OnButtonSaveUut)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TESTSOLUTION, OnButtonDelTestsolution)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVER_NAME2, OnSelchangeComboDriverName2)
	ON_CBN_SELCHANGE(IDC_COMBO_INS, OnSelchangeComboIns)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVER_NAME, OnSelchangeComboDriverName)
	ON_BN_CLICKED(IDC_BUTTON_DRIVER_NAME2, OnButtonDriverName2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_INS, OnButtonSaveIns)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SOLUTION, OnButtonSaveSolution)
	ON_BN_CLICKED(IDC_BUTTON_EDT_LUA_PIC, OnButtonEdtLuaPic)
	ON_BN_CLICKED(IDC_PIC_UUT, OnPicUut)
	ON_BN_CLICKED(IDC_PIC_LUA, OnPicLua)
	ON_BN_CLICKED(IDC_BUTTON_SOLUTION_CHANGE, OnButtonSolutionChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolution message handlers

BOOL CInsDocSolution::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);
	DWORD dwStyle=m_list_UUT.GetExtendedStyle();
	m_list_UUT.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_UUT.InsertColumn(0, "引擎函数", LVCFMT_LEFT, 45);
	m_list_UUT.InsertColumn(1, "对应库", LVCFMT_CENTER, 50);
	m_list_UUT.InsertColumn(2, "库函数", LVCFMT_CENTER, 50);

	dwStyle=m_list_Ins.GetExtendedStyle();
	m_list_Ins.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_Ins.InsertColumn(0, "引擎函数", LVCFMT_LEFT, 45);
	m_list_Ins.InsertColumn(1, "对应库", LVCFMT_CENTER, 50);
	m_list_Ins.InsertColumn(2, "库函数", LVCFMT_CENTER, 50);
	
	dwStyle=m_list_Lua.GetExtendedStyle();
	m_list_Lua.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_Lua.InsertColumn(0, "测试功能_备注", LVCFMT_LEFT, 45);
	m_list_Lua.InsertColumn(1, "对应脚本", LVCFMT_CENTER, 50);
	m_list_Lua.InsertColumn(2, "接线图", LVCFMT_CENTER, 50);

	CPathOperate pathope;
	m_strUUInfoPath = pathope.GetStartPath() + "DataInfo\\UUTTestInfo";

	m_nChangeState = 0;
	UpdateChangeState(m_nChangeState);

	m_WindowShow = UUT;
	UUT_LUA_SHOW(m_WindowShow);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CInsDocSolution::DestroyWindow() 
{
	m_brush.DeleteObject();
	return CDialog::DestroyWindow();
}

HBRUSH CInsDocSolution::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}

	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
    	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	return hbr;
}

BOOL CInsDocSolution::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CInsDocSolution::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	int nWide, nHeight, nWide1, nWide2;
	CRect rect1;
	GetClientRect(&rect1);

	nWide = (rect1.Width() - 10) / 2;
	nWide = rect1.Width() - 20;
	if(IsWindow(m_com_Solution))
		m_com_Solution.MoveWindow(80, 10, nWide - 290, 100);
	if(IsWindow(m_btn_Add_Solution))
		m_btn_Add_Solution.MoveWindow(nWide - 205, 10, 50, 26);
	if(IsWindow(m_btn_Del_Solution))
		m_btn_Del_Solution.MoveWindow(nWide - 150, 10, 50, 26);
	if(IsWindow(m_btn_Solution_Change))
		m_btn_Solution_Change.MoveWindow(nWide - 90, 10, 100, 26);

	nHeight = rect1.Height() - 75;
	if(IsWindow(m_group_Solution))
		m_group_Solution.MoveWindow(5, 65, nWide + 10, nHeight + 8);

	if(IsWindow(m_list_Lua))
	{
		m_list_Lua.MoveWindow(10, 100, nWide, nHeight-30);
		nWide1 = nWide / 7;
		m_list_Lua.SetColumnWidth(0, nWide1 * 3 - 7);
		m_list_Lua.SetColumnWidth(1, nWide1 * 2 - 7);
		m_list_Lua.SetColumnWidth(2, nWide1 * 2 - 7);
	}	
	if(IsWindow(m_btn_Save_Lua))
		m_btn_Save_Lua.MoveWindow(nWide - 130, 77, 140, 22);
	if(IsWindow(m_btn_Edt_Lua_Pic))
		m_btn_Edt_Lua_Pic.MoveWindow(nWide - 270, 77, 130, 22);

	nHeight = (nHeight - 4) / 2;
	nWide1 = nWide - 130;
	nWide2 = nWide - 14;
	
	if(IsWindow(m_group_UUT))
		m_group_UUT.MoveWindow(13, 71, nWide -6, nHeight);

	if(IsWindow(m_stc_UUT))
		m_stc_UUT.MoveWindow(20, 88, 100, 30);
	if(IsWindow(m_edt_UUT_Name))
		m_edt_UUT_Name.MoveWindow(87, 83, nWide1, 25);
	if(IsWindow(m_stc_Drive_Name_UUT))
		m_stc_Drive_Name_UUT.MoveWindow(20, 118, 120, nHeight);
	if(IsWindow(m_com_Drive_UUT))
		m_com_Drive_UUT.MoveWindow(87, 113, nWide1 - 75, 100);
	if(IsWindow(m_btn_Drive_Name_UUT))
		m_btn_Drive_Name_UUT.MoveWindow(17 + nWide1, 113, 70, 25);
	if(IsWindow(m_stc_UUT_Addr))
		m_stc_UUT_Addr.MoveWindow(20, 148, 120, 30);
	if(IsWindow(m_edt_UUT_Address))
		m_edt_UUT_Address.MoveWindow(87, 143, nWide1, 25);
	if(IsWindow(m_btn_Save_UUT))
		m_btn_Save_UUT.MoveWindow(nWide - 39, 83, 42, 86);
	if(IsWindow(m_list_UUT))
	{
		m_list_UUT.MoveWindow(17, 172, nWide2, nHeight - 105);
		m_list_UUT.SetColumnWidth(0, nWide / 3 - 12);
		m_list_UUT.SetColumnWidth(1, nWide / 3 - 12);
		m_list_UUT.SetColumnWidth(2, nWide / 3 - 12);
	}

	if(IsWindow(m_group_Ins))
		m_group_Ins.MoveWindow(13, 70 + nHeight, nWide -6, nHeight);

	if(IsWindow(m_stc_Ins))
		m_stc_Ins.MoveWindow(20, 87 + nHeight, 120, nHeight);
	if(IsWindow(m_com_Ins))
		m_com_Ins.MoveWindow(87, 82 + nHeight, nWide1, 100);
	if(IsWindow(m_stc_Driver_Name_Ins))
		m_stc_Driver_Name_Ins.MoveWindow(20, 117 + nHeight, 120, nHeight);
	if(IsWindow(m_com_Drive_Name))
		m_com_Drive_Name.MoveWindow(87, 112 + nHeight, nWide1 - 75, 100);
	if(IsWindow(m_btn_Driver_Name_Ins))
		m_btn_Driver_Name_Ins.MoveWindow(17 + nWide1, 112 + nHeight, 70, 25);
	if(IsWindow(m_stc_Ins_Address))
		m_stc_Ins_Address.MoveWindow(20, 147 + nHeight, 120, nHeight);
	if(IsWindow(m_edt_Ins_Address))
		m_edt_Ins_Address.MoveWindow(87, 142 + nHeight, nWide1, 25);
	if(IsWindow(m_btn_Save_Ins))
		m_btn_Save_Ins.MoveWindow(nWide - 39, 82 + nHeight, 42, 86);
	if(IsWindow(m_list_Ins))
	{
		m_list_Ins.MoveWindow(17, 171 + nHeight, nWide2, nHeight - 105);
		m_list_Ins.SetColumnWidth(0, nWide / 3 - 12);
		m_list_Ins.SetColumnWidth(1, nWide / 3 - 12);
		m_list_Ins.SetColumnWidth(2, nWide / 3 - 12);
	}
}

void CInsDocSolution::OnButtonAddTestsolution() 
{
	CInsDocSolutinoAdd add1;
	add1.m_strKind = m_strKind;
	add1.m_strModel = m_strModel;
	add1.DoModal();	
	if(add1.m_strTemplate == "")
		return;

	CString str1, strPath;
	str1 = m_strModel;
	str1.Replace(" ", "_");
	strPath = m_strSoluDirPath + "\\" + add1.m_strTemplate;
	if(add1.m_bRefer)//假如参考其他的模板
	{
		CTool tool1;
		//拷贝其他模板		
		tool1.CopyDirectory(add1.m_strRefTempPath, strPath, FALSE);//拷贝文件夹
		tool1.ReplacePartNameInDirectorye(strPath + "\\TestConfig", add1.m_strReferModel, m_strModel);//文件改名
		tool1.ChangeSolutionIni(strPath, m_strKind, m_strModel);
		tool1.changeXMLRootName(strPath + "\\TestConfig", str1);
	}
	else
	{
		CreateDirectory(strPath, NULL);
		CreateDirectory(strPath + "\\TestItem", NULL);
		CreateDirectory(strPath + "\\TestConfig", NULL);
		CreateDirectory(strPath + "\\TestConfig\\ConnectPic", NULL);
		//创建ini文件和xml文件,暂时不创建
	}
	initAll(m_strKind, m_strModel);
}

void CInsDocSolution::initAll(CString strKind, CString strModel)
{
	m_strKind = strKind;
	m_strModel = strModel;
	m_strSolution = "";

	initComSolution();
	GetSolution();
	initUUT_InsName_InsDriver();
	initIns();
	initUUTList();
	initInsList();
	initTestFunc();
	initLua_ConnectPic();
}
void CInsDocSolution::initComSolution()//初始化组合框
{
	m_nChangeState = 0;
	UpdateChangeState(m_nChangeState);
	m_strSolution = "";
	try
	{
		int intCbSolution=m_com_Solution.GetCount();
		for(int i=0;i<intCbSolution;i++)
		{
			m_com_Solution.DeleteString(0);
		}
		
		m_strSoluDirPath = "";

		if(m_strModel == "")
			return;
		
		CFile_UUTInfo file_UUTInfo;
		vector<FileInfo> vFileinfo1;
		file_UUTInfo.GetSolutionList(m_strKind, m_strModel, &vFileinfo1);
		int intSolSize=0;

		for(int i=0; i<vFileinfo1.size(); i++)
		{
			m_com_Solution.AddString(vFileinfo1[i].m_strFileName);
		}
		if(m_com_Solution.GetCount() > 0)
			m_com_Solution.SetCurSel(0);
		m_nChangeState = 1;
		UpdateChangeState(m_nChangeState);
	}	
	catch (char* e)
	{
		MessageBox(e);
	}
}
void CInsDocSolution::GetSolution()
{
	int nI = m_com_Solution.GetCurSel();
	if(nI > -1)
		m_com_Solution.GetLBText(nI, m_strSolution);

	CPathOperate paOpe; //获得解决方案文件夹路径
	m_strSoluDirPath = paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Solution";
}	

void CInsDocSolution::initUUT_InsName_InsDriver()//初始化被测试设备驱动组合框, 引擎函数, 及测试设备组合框, 测试设备驱动组合框
{
	CString str1, str2, str3;
	CIni ini1;
	int nI = m_com_Ins.GetCount();
	for(int i = 0; i < nI; i++)
		m_com_Ins.DeleteString(0);
	m_list_UUT.DeleteAllItems();
	m_edt_UUT_Name.SetWindowText(m_strModel);
	if(m_WindowShow == UUT)
	{
		m_edt_UUT_Name.ShowWindow(SW_HIDE);
		m_edt_UUT_Name.ShowWindow(SW_SHOWNORMAL);
	}
	m_edt_UUT_Address.SetWindowText("");
	while(m_com_Drive_UUT.DeleteString(0)!=CB_ERR);
	m_com_Drive_UUT.SetCurSel(-1);
	while(m_com_Drive_Name.DeleteString(0)!=CB_ERR);
	m_com_Drive_Name.SetCurSel(-1);
	m_srtInsArray.RemoveAll();
	if(m_strModel == "")
		return;

	CFileFind findfileEngineINI, findfileTestConfigINI;
	bool bHasEngineConfigINI = false;
	bool bHasTestConfigINI = true;

	m_strEngineINIPath = m_strUUInfoPath + "\\" + m_strKind + "\\InsPortDriver\\" + m_strKind + "_testConfig.ini";
	m_strTestConfigINIPath = m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Solution\\" + m_strSolution + "\\TestConfig\\" + m_strModel + " testConfig.ini";
	if(!findfileEngineINI.FindFile(m_strEngineINIPath))//查找引擎的配置文件是否存在,如果不存在,报错
	{
		AfxMessageBox("驱动引擎的配置文件不存在\r\n文件路径:" + m_strEngineINIPath);
		return;
	}
	else
	{
		bHasEngineConfigINI = true;

		if(!findfileTestConfigINI.FindFile(m_strTestConfigINIPath))//查找驱动的配置文件是否存在,如果不存在,拷贝文件
		{
			CopyFile(m_strEngineINIPath, m_strTestConfigINIPath, true);
			bHasTestConfigINI = false;
		}
	}

	if(bHasEngineConfigINI)//根据驱动配置文件初始化
	{
		ini1.SetINIPth(m_strEngineINIPath);//初始化被测试设备
		CStringArray saIns;
		CStringArray saKeys;
		ini1.GetSections(saIns);//获得字段列表

		for(int i = 0; i < saIns.GetSize(); i++)//查找引擎函数关键字,写入引擎函数
		{
			if(saIns[i] == "UUT")//查找字段UUT
			{
				ini1.GetKeys(saKeys, "UUT");
				nI = 0;
				for(int j = 0; j < saKeys.GetSize(); j++)
				{
					if(saKeys[j] != "InsName" && saKeys[j] != "Model" && saKeys[j] != "Address" && saKeys[j] != "Channel" && saKeys[j] != "DriverName")
					{
						m_list_UUT.InsertItem(nI, saKeys[j]);
						nI++;
					}
				}
			}
			else//查找其他字段,写入测试设备组合框
			{
				m_com_Ins.AddString(ini1.GetKeyValue(saIns[i], "InsName"));
				m_srtInsArray.Add(saIns[i]);
			}
		}

		if(m_com_Ins.GetCount() > 0)
			m_com_Ins.SetCurSel(0);


		nI = m_com_Drive_UUT.GetCount();//初始化UUT驱动列表
		for(int i = 0; i < nI; i++)
			m_com_Drive_UUT.DeleteString(0);
		CFile_UUTInfo fileUUT1;
		vector<FileInfo> fileinfo1;
		fileUUT1.GetDriverList(m_strKind, m_strModel, &fileinfo1, 0);
		if(fileinfo1.size() > 0)
		{
			for(int i = 0; i < fileinfo1.size(); i++)
			{
				m_com_Drive_UUT.AddString(fileinfo1[i].m_strFileName);
			}
			m_com_Drive_UUT.SetCurSel(-1);
		}

		
		ini1.SetINIPth(m_strTestConfigINIPath);
		str1 = ini1.GetKeyValue("UUT", "DriverName");
		int nI = str1.ReverseFind('\\');
		if(nI > 0)
		{
			str1 = str1.Right(str1.GetLength() - nI - 1);
			for(int i = 0; i < m_com_Drive_UUT.GetCount(); i++)
			{
				m_com_Drive_UUT.GetLBText(i, str2);
				if(str1 == str2)
				{
					m_com_Drive_UUT.SetCurSel(i);
					break;
				}
			}
		}
		str1 = ini1.GetKeyValue("UUT", "Address");
		m_edt_UUT_Address.SetWindowText(str1);

		nI = m_com_Drive_Name.GetCount();//初始化测试设备驱动列表
		for(int i = 0; i < nI; i++)
			m_com_Drive_Name.DeleteString(0);
		fileinfo1.clear();
		fileUUT1.GetDriverList(m_strKind, "", &fileinfo1, 1);
		if(fileinfo1.size() > 0)
		{
			for(int i = 0; i < fileinfo1.size(); i++)
			{
				m_com_Drive_Name.AddString(fileinfo1[i].m_strFileName);
			}
			m_com_Drive_Name.SetCurSel(-1);
		}
	}
}

void CInsDocSolution::initUUTList()
{
	for(int i = 0; i < m_list_UUT.GetItemCount(); i++)
	{
		m_list_UUT.SetItemText(i, 1, "");
		m_list_UUT.SetItemText(i, 2, "");
	}
	CString str1, str2, str3, strdll1, strdll2;
	m_strDllName_UUT = "";
	m_list_UUT.m_srtDll = "";
	m_list_UUT.m_strFuncArray.RemoveAll();
	m_strFuncArray_UUT.RemoveAll();
	CIni ini1;
	
	int nI = m_com_Drive_UUT.GetCurSel();
	if(nI < 0)
		return;
	m_com_Drive_UUT.GetLBText(nI, str1);
	if(str1 == "")
		return;
	CXmlFile_Ope xmlope;//驱动dll的功能列表文件
	xmlope.LoadXmlFile(m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Driver\\" + str1 + "\\" + str1 + ".xml");
	if(xmlope.pRootEle != NULL)
	{
		TiXmlElement *EleTemp = xmlope.pRootEle->FirstChildElement("dllName");
		if(EleTemp != NULL)
			EleTemp = EleTemp->FirstChildElement();
		else
			return;
		if(EleTemp != NULL)
		{
			m_strDllName_UUT = EleTemp->Value();
			m_list_UUT.m_srtDll = m_strDllName_UUT;
		}
		else 
			return;
		EleTemp = xmlope.pRootEle->FirstChildElement("funList");
		if(EleTemp != NULL)
		{
			for(EleTemp = EleTemp->FirstChildElement(); EleTemp != NULL; EleTemp = EleTemp->NextSiblingElement())
			{
				str3 = EleTemp->Value();
				if(str3 != "")
				{
					m_strFuncArray_UUT.Add(str3);
					m_list_UUT.m_strFuncArray.Add(str3);
				}
			}
		}
		if(m_strFuncArray_UUT.GetSize() == 0)
			return;
		ini1.SetINIPth(m_strTestConfigINIPath);
		for(int j = 0; j < m_list_UUT.GetItemCount(); j++)
		{
			str2 = ini1.GetKeyValue("UUT", m_list_UUT.GetItemText(j, 0));
			nI = str2.Find("->");
			if(nI > 4)
			{
				strdll1 = str2.Left(nI);
				strdll2	 = str2.Right(str2.GetLength() - nI - 2);
				if(strdll1 == m_strDllName_UUT)
				{
					m_list_UUT.SetItemText(j, 1, strdll1);
					for(int i = 0; i < m_strFuncArray_UUT.GetSize(); i++)
					{
						if(strdll2 == m_strFuncArray_UUT[i])
						{
							m_list_UUT.SetItemText(j, 2, strdll2);
							break;
						}
					}
				}
			}

		}
	}
}

void CInsDocSolution::initIns()//初始化测试设备地址/引擎函数
{
	m_list_Ins.DeleteAllItems();
	m_edt_Ins_Address.SetWindowText("");
	//获得Ins设备
	int nI = m_com_Ins.GetCurSel();
	if(nI < 0)
		return;
	CString strIns = m_srtInsArray[nI];
	if(strIns == "")
		return;

	CStringArray saKeys;//获得引擎函数列表
	saKeys.RemoveAll();
	CIni ini1;
	ini1.SetINIPth(m_strEngineINIPath);
	ini1.GetKeys(saKeys, strIns);
	nI = 0;
	for(int i = 0; i < saKeys.GetSize(); i++)
	{
		if(saKeys[i] != "InsName" && saKeys[i] != "Model" && saKeys[i] != "Address" && saKeys[i] != "Channel" && saKeys[i] != "DriverName")
		{
			m_list_Ins.InsertItem(nI, saKeys[i]);
			nI++;
		}
	}

	CString str1, str2;
	ini1.SetINIPth(m_strTestConfigINIPath);
	m_com_Drive_Name.SetCurSel(-1);
	str1 = ini1.GetKeyValue(strIns, "DriverName");//获得驱动名
	nI = str1.ReverseFind('\\');
	if(nI > 0)
	{
		str1 = str1.Right(str1.GetLength() - nI - 1);
		for(int i = 0; i < m_com_Drive_Name.GetCount(); i++)
		{	
			m_com_Drive_Name.GetLBText(i, str2);
			if(str1 == str2)
			{
				m_com_Drive_Name.SetCurSel(i);
				break;
			}		
		}
	}

	str1 = ini1.GetKeyValue(strIns, "Address");
	m_edt_Ins_Address.SetWindowText(str1);
	for(int i = 0; i < m_list_UUT.GetItemCount(); i++)
	{
		str1 = m_list_Ins.GetItemText(i, 0);
		str1 = ini1.GetKeyValue(strIns, str1);
		if(str1 != "")
		{
			nI = str1.Find("->");
			if(nI > 4)
			{
				m_list_Ins.SetItemText(i, 1, str1.Left(nI));
				m_list_Ins.SetItemText(i, 2, str1.Right(str1.GetLength() - nI - 2));
			}
		}
	}
}

void CInsDocSolution::initInsList()
{	
	for(int i = 0; i < m_list_Ins.GetItemCount(); i++)
	{
		m_list_Ins.SetItemText(i, 1, "");
		m_list_Ins.SetItemText(i, 2, "");
	}
	CString	strIns, str1, str2, str3, strdll1, strdll2;
	m_strDllName_Ins = "";
	m_strFuncArray_Ins.RemoveAll();
	m_list_Ins.m_srtDll = "";
	m_list_Ins.m_strFuncArray.RemoveAll();
	CIni ini1;
	CXmlFile_Ope xmlope;//驱动dll的功能列表文件
	int nI = m_com_Ins.GetCurSel();
	if(nI < 0)
		return;
	strIns = m_srtInsArray[nI];
	if(strIns == "")
		return;
	nI = m_com_Drive_Name.GetCurSel();
	if(nI < 0)
		return;
	m_com_Drive_Name.GetLBText(nI, str1);
	if(str1 == "")
		return;
	str1 = m_strUUInfoPath + "\\" + m_strKind + "\\InstrDriver\\" + str1 + "\\" + str1 + ".xml";
	xmlope.LoadXmlFile(str1);
	if(xmlope.pRootEle != NULL)
	{
		TiXmlElement *EleTemp = xmlope.pRootEle->FirstChildElement("dllName");
		if(EleTemp != NULL)
			EleTemp = EleTemp->FirstChildElement();
		else
			return;
		if(EleTemp != NULL)
		{
			m_strDllName_Ins = EleTemp->Value();
			m_list_Ins.m_srtDll = m_strDllName_Ins;
		}
		else 
			return;
		EleTemp = xmlope.pRootEle->FirstChildElement("funList");
		if(EleTemp != NULL)
		{
			for(EleTemp = EleTemp->FirstChildElement(); EleTemp != NULL; EleTemp = EleTemp->NextSiblingElement())
			{
				str3 = EleTemp->Value();
				if(str3 != "")
				{
					m_strFuncArray_Ins.Add(str3);
					m_list_Ins.m_strFuncArray.Add(str3);
				}
			}
		}
		if(m_strFuncArray_Ins.GetSize() == 0)
			return;
		ini1.SetINIPth(m_strTestConfigINIPath);
		for(int j = 0; j < m_list_Ins.GetItemCount(); j++)
		{
			str2 = ini1.GetKeyValue(strIns, m_list_Ins.GetItemText(j, 0));
			nI = str2.Find("->");
			if(nI > 4)
			{
				strdll1 = str2.Left(nI);
				strdll2	 = str2.Right(str2.GetLength() - nI - 2);
				if(strdll1 == m_strDllName_Ins)
				{
					m_list_Ins.SetItemText(j, 1, strdll1);
					for(int i = 0; i < m_strFuncArray_Ins.GetSize(); i++)
					{
						if(strdll2 == m_strFuncArray_Ins[i])
						{
							m_list_Ins.SetItemText(j, 2, strdll2);
							break;
						}
					}
				}
			}
		}
	}
}

void CInsDocSolution::initTestFunc()//初始化Lua列表的测试功能列
{
	try
	{
		m_list_Lua.DeleteAllItems();
		if(m_strModel == "")
			return;

		for(int i = 0; i < m_testItem.GetSize(); i++)     //填充可用测试项目列表i
			m_list_Lua.InsertItem(i, m_testItem[i].strName + "_" + m_testItem[i].strNote, 0);
	}
	catch (char* e)
	{
		MessageBox(e);		
	}
}

void CInsDocSolution::initLua_ConnectPic()//初始化Lua列表的脚本及接线图
{
	try
	{
		for(int i = 0; i < m_list_Lua.GetItemCount(); i++)
		{
			m_list_Lua.SetItemText(i, 1, "");
			m_list_Lua.SetItemText(i, 2, "");
		}
		if(m_strModel == "")
			return;

		CString str1, str2;
		CFileFind ff;
		BOOL res;
		str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestItem\\*.lua";
		res=ff.FindFile(str1);
		//查找Lua脚本
		m_list_Lua.m_strLuaArray.RemoveAll();
		while(res)
		{
			res=ff.FindNextFile();
			if(ff.IsDots())
				continue;
			if(ff.IsDirectory())
				continue;
			else
				m_list_Lua.m_strLuaArray.Add(ff.GetFileName());
		}

		str1 = m_strSoluDirPath + "\\" + m_strSolution+ "\\TestConfig\\ConnectPic\\*.*";
		res=ff.FindFile(str1);
		//查找接线图
		m_list_Lua.m_strPicArray.RemoveAll();
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
						m_list_Lua.m_strPicArray.Add(str1);
				}
			}
		}

		CString strItemKey;
		CXml_Bll_UUTItem bll_UUTItem;
		vector<UUTItemVarSet> vLua_ConnectPicInfo;
		CString strLuaPath = m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Solution\\"+m_strSolution + "\\TestConfig\\" + m_strModel+".xml";
		CXmlFile_Ope xmlope;
		xmlope.LoadXmlFile(strLuaPath);
		CXml_UUTItemVarSet xml_UUTVar(xmlope.pRootEle);
		CArray<UUTItemVarSet, UUTItemVarSet> VarSetArray;
		xml_UUTVar.GetItemInfoArray(VarSetArray);

		for(int i = 0; i < m_testItem.GetSize(); i++)
		{
			for(int k = 0; k < VarSetArray.GetSize(); k++)
			{
				if(m_testItem[i].nKey == VarSetArray[k].m_intID)
				{
					for(int j = 0; j < m_list_Lua.m_strLuaArray.GetSize(); j++)
					{
						if(VarSetArray[k].m_strProgName == m_list_Lua.m_strLuaArray[j])
						{	
							m_list_Lua.SetItemText(i, 1, VarSetArray[k].m_strProgName);
							break;
						}
					}
					for(int j = 0; j < m_list_Lua.m_strPicArray.GetSize(); j++)
					{
						if(VarSetArray[k].m_strConnectPic == m_list_Lua.m_strPicArray[j])
						{
							m_list_Lua.SetItemText(i, 2, VarSetArray[k].m_strConnectPic);
							break;
						}
					}

				}
			}
		}
	}
	catch (char* e)
	{
		MessageBox(e);		
	}
}

void CInsDocSolution::OnSelchangeComboSolutionInsdoc() 
{
	GetSolution();
	initUUT_InsName_InsDriver();
	initIns();
	initUUTList();
	initInsList();
	initTestFunc();
	initLua_ConnectPic();
}

void CInsDocSolution::OnButtonDriverName() 
{
	CopyDriver(1);//拷贝测试设备驱动
	initUUT_InsName_InsDriver();
	initIns();
	initUUTList();
	initInsList();
}

void CInsDocSolution::OnButtonSaveUut() 
{
	if(m_strKind == "" || m_strModel == "")//获得名称
	{
		AfxMessageBox("请重新点击装置列表,以获取装置信息");
		return;
	}
	CString strDriver, strAddress, strFun1, strFun2, strFun3;
	strDriver = strAddress = "";
	CFileFind ff;
	bool bExist = false;
	BOOL bFind = ff.FindFile(m_strTestConfigINIPath);
	while(bFind)
	{
		bFind = ff.FindNextFile();

		if (ff.IsDots())
			continue;		
		else if (ff.IsDirectory())
			continue;
		else
			bExist = true;
	}
	if(!bExist)
		CreateFile(m_strTestConfigINIPath, GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//创建一个空的文件;
	CIni ini1;
	ini1.SetINIPth(m_strTestConfigINIPath);
	ini1.WriteKeyValue("UUT", "InsName", m_strKind);
	ini1.WriteKeyValue("UUT", "Model", m_strModel);

	m_edt_UUT_Address.GetWindowText(strAddress);//获得地址
	int nI = m_com_Drive_UUT.GetCurSel();
	if(nI > -1)
	{
		m_com_Drive_UUT.GetLBText(nI, strDriver);//获得驱动
		if(strDriver != "")
			strDriver = m_strKind + "\\TPS\\" + m_strModel + "\\Driver\\" + strDriver;
	}
	ini1.WriteKeyValue("UUT", "Address", strAddress);
	ini1.WriteKeyValue("UUT", "DriverName", strDriver);

	for(int i = 0; i < m_list_UUT.GetItemCount(); i++)
	{	
	//获得对应函数
		strFun1 = m_list_UUT.GetItemText(i, 0);
		strFun2 = m_list_UUT.GetItemText(i, 1);
		strFun3 = m_list_UUT.GetItemText(i, 2);
		if(strFun1 != "" && strFun2 != "" && strFun3 != "")
			ini1.WriteKeyValue("UUT", strFun1, strFun2 + "->" + strFun3);
	}
}

void CInsDocSolution::OnButtonDelTestsolution()
{
	CInsDocSolutionDel del1;
	del1.m_strKind = m_strKind;
	del1.m_strModel = m_strModel;
	del1.DoModal();
	CTool tool1;
	for(int i = 0; i < del1.m_strPathArray.GetSize(); i++)
		tool1.DeleteDirectorye(del1.m_strPathArray[i]);
	initAll(m_strKind, m_strModel);
}

void CInsDocSolution::OnSelchangeComboDriverName2() 
{
	initUUTList();
}

void CInsDocSolution::OnSelchangeComboIns() 
{
	initIns();
	initInsList();
}

void CInsDocSolution::OnSelchangeComboDriverName() 
{
	initInsList();
}
void CInsDocSolution::OnButtonDriverName2() 
{
	CopyDriver(0);//拷贝UUT驱动
	initUUT_InsName_InsDriver();
	initIns();
	initUUTList();
	initInsList();
}
void CInsDocSolution::CopyDriver(int nType) 
{
	CFileDialog dlg(TRUE, ".xml", NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "驱动函数列举文件(*.xml)|*.xml||");
	if(dlg.DoModal()==IDOK)
	{
		CString strDir, strDll, strDllPath, strPath, strName, strTitle;
		strPath = dlg.GetPathName();
		strName	= dlg.GetFileName();
		strTitle = dlg.GetFileTitle();
		if(strPath == "" || strName == "")
		{
			AfxMessageBox("驱动路径不正确");
			return;
		}
		CXmlFile_Ope xmlope;
		xmlope.LoadXmlFile(strPath);
		if(xmlope.pRootEle == NULL)
		{
			AfxMessageBox("配置文件为空文件");
			return;
		}
		TiXmlElement *EleTemp = xmlope.pRootEle->FirstChildElement("dllName");
		if(EleTemp != NULL)
			EleTemp = EleTemp->FirstChildElement();
		else
		{
			AfxMessageBox("驱动配置文件格式不正确");
			return;
		}
		if(EleTemp != NULL)
			strDll = EleTemp->Value();
		else 
		{
			AfxMessageBox("配置文件内无驱动dll字段（.dll）");
			return;
		}
		if(strDll.GetLength() < 4 || strDll.Find(".dll") < 1)
		{
			AfxMessageBox("配置文件内无驱动dll字段（.dll）");
			return;
		}
		strDllPath = strPath.Left(strPath.ReverseFind('\\') + 1) + strDll;
		CFileFind ff;
		BOOL bFind = ff.FindFile(strDllPath);
		bool bCre = false;
		while(bFind)
		{
			bFind = ff.FindNextFile(); 
			if(ff.IsDots())
				continue;
			if( ff.IsDirectory() )
				continue;
			else
			{
				if(nType == 1)
					strDir = m_strUUInfoPath + "\\" + m_strKind + "\\InstrDriver\\" + strTitle;
				else
				{
					strDir = m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Driver";
					if(strPath == strDir + "\\" + strName)
					{
						AfxMessageBox("拷贝驱动路径与现有驱动相同!请重新选择");
						return;
					}
					CTool tool1;
					tool1.DeleteDirectorye1(strDir);//删除路径下所有文件
					strDir += "\\" + strTitle;
				}
				if(!CreateDirectory(strDir, false))
				{
					AfxMessageBox("创建驱动文件夹失败, 请检查拷贝驱动的路径是否与现有驱动冲突!");
					return;
				}
				CopyFile(strPath, strDir + "\\" + strName, false);
				strDll = strDir + "\\" + strDll;
				CopyFile(strDllPath, strDll, false);
				strDllPath = strDllPath.Left(strDllPath.GetLength() - 3) + "h";
				strDll = strDll.Left(strDll.GetLength() - 3) + "h";
				CopyFile(strDllPath, strDll, false);
				bCre = true;
			}
		}
		if(!bCre)
		{
			AfxMessageBox("配置文件同路径下未找到相应驱动文件（.dll）");
			return;
		}
	}	
}

void CInsDocSolution::OnButtonSaveIns() 
{
	if(m_strKind == "" || m_strModel == "")//获得名称
	{
		AfxMessageBox("请重新点击装置列表,以获取装置信息");
		return;
	}
	CString strDriver, strAddress, strFun1, strFun2, strFun3, strIns, strIns1;
	strDriver = strAddress = "";
	int nI = m_com_Ins.GetCurSel();
	if(nI > -1 && nI < m_srtInsArray.GetSize())
	{
		m_com_Ins.GetLBText(nI, strIns1);//获得驱动
		strIns = m_srtInsArray[nI];
	}
	if(strIns == "")
	{
		AfxMessageBox("未获取到测试设备名称,请尝试重新点击装置列表!");
		return;
	}
	CFileFind ff;
	bool bExist = false;
	BOOL bFind = ff.FindFile(m_strTestConfigINIPath);
	while(bFind)
	{
		bFind = ff.FindNextFile();

		if (ff.IsDots())
			continue;		
		else if (ff.IsDirectory())
			continue;
		else
			bExist = true;
	}
	if(!bExist)
		CreateFile(m_strTestConfigINIPath, GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//创建一个空的文件;
	CIni ini1;
	ini1.SetINIPth(m_strTestConfigINIPath);
	
		
	nI = m_com_Drive_Name.GetCurSel();
	if(nI > -1)
	{
		m_com_Drive_Name.GetLBText(nI, strDriver);//获得驱动
		ini1.WriteKeyValue(strIns, "Model", strDriver);
		if(strDriver != "")
			strDriver = m_strKind + "\\InstrDriver\\" + strDriver;
	}
	m_edt_Ins_Address.GetWindowText(strAddress);//获得地址
	ini1.WriteKeyValue(strIns, "Address", strAddress);
	ini1.WriteKeyValue(strIns, "DriverName", strDriver);

	for(int i = 0; i < m_list_Ins.GetItemCount(); i++)
	{	
	//获得对应函数
		strFun1 = m_list_Ins.GetItemText(i, 0);
		strFun2 = m_list_Ins.GetItemText(i, 1);
		strFun3 = m_list_Ins.GetItemText(i, 2);
		if(strFun1 != "" && strFun2 != "" && strFun3 != "")
			ini1.WriteKeyValue(strIns, strFun1, strFun2 + "->" + strFun3);
	}
}

void CInsDocSolution::OnButtonSaveSolution() 
{
	try
	{
		CString strItemKey;
		CXml_Bll_UUTItem bll_UUTItem;
		vector<UUTItemVarSet> vLua_ConnectPicInfo;
		CString strLuaPath = m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Solution\\"+m_strSolution + "\\TestConfig\\" + m_strModel+".xml";
		CXmlFile_Ope xmlope;
		xmlope.LoadXmlFile(strLuaPath);
		CXml_UUTItemVarSet xml_UUTVar(xmlope.pRootEle);
		CArray<UUTItemVarSet, UUTItemVarSet> VarSetArray;
		UUTItemVarSet var1;		

		for(int i = 0; i < m_list_Lua.GetItemCount() && i < m_testItem.GetSize(); i++)
		{
			var1.m_intID = m_testItem[i].nKey;
			var1.m_strProgName = m_list_Lua.GetItemText(i, 1);
			var1.m_strConnectPic = m_list_Lua.GetItemText(i, 2);
			VarSetArray.Add(var1);
		}
		xml_UUTVar.WriteItemInfoArray(VarSetArray);
		if(xmlope.pRootEle == NULL)
		{
			strItemKey = m_strModel;
			strItemKey.Replace(" ", "_");
			xmlope.pRootEle = new TiXmlElement(strItemKey);
		}
		if(xml_UUTVar.m_pNode == NULL)
			xmlope.pRootEle->LinkEndChild(xml_UUTVar.m_pEle);
		xmlope.SaveFile();
	}
	catch (char* e)
	{
		MessageBox(e);		
	}
	initLua_ConnectPic();
}

void CInsDocSolution::OnButtonEdtLuaPic() 
{
	if(m_strSoluDirPath == "" || m_strSolution == "" || m_strKind == "" || m_strModel == "")
		return;
	CEdt_Lua_Pic edt_lua_pic;
	edt_lua_pic.m_strSoluDirPath = m_strSoluDirPath;
	edt_lua_pic.m_strSolution = m_strSolution;
	edt_lua_pic.m_strKind = m_strKind;
	edt_lua_pic.m_strModel = m_strModel;

	edt_lua_pic.DoModal();

	initLua_ConnectPic();
}

void CInsDocSolution::UUT_LUA_SHOW(int nIUUt_Lua)
{
	HBITMAP hbmp[3];
	switch(nIUUt_Lua)
	{
	case 0:
		hbmp[0] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION_DEVICE1);
		hbmp[1] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION_LUA);
		m_pic_UUT.SetBitmap(hbmp[0]);
		m_pic_Lua.SetBitmap(hbmp[1]);

		m_stc_Lua_Pic.ShowWindow(SW_HIDE);
		m_list_Lua.ShowWindow(SW_HIDE);
		m_btn_Save_Lua.ShowWindow(SW_HIDE);
		m_btn_Edt_Lua_Pic.ShowWindow(SW_HIDE);
		
		m_group_UUT.ShowWindow(SW_SHOW);
		m_stc_UUT.ShowWindow(SW_SHOW);
		m_edt_UUT_Name.ShowWindow(SW_SHOW);
		m_stc_Drive_Name_UUT.ShowWindow(SW_SHOW);
		m_com_Drive_UUT.ShowWindow(SW_SHOW);
		m_btn_Drive_Name_UUT.ShowWindow(SW_SHOW);
		m_stc_UUT_Addr.ShowWindow(SW_SHOW);
		m_edt_UUT_Address.ShowWindow(SW_SHOW);
		m_btn_Save_UUT.ShowWindow(SW_SHOW);
		m_list_UUT.ShowWindow(SW_SHOW);
		
		m_group_Ins.ShowWindow(SW_SHOW);
		m_stc_Ins.ShowWindow(SW_SHOW);
		m_com_Ins.ShowWindow(SW_SHOW);
		m_stc_Driver_Name_Ins.ShowWindow(SW_SHOW);
		m_com_Drive_Name.ShowWindow(SW_SHOW);
		m_btn_Driver_Name_Ins.ShowWindow(SW_SHOW);
		m_stc_Ins_Address.ShowWindow(SW_SHOW);
		m_edt_Ins_Address.ShowWindow(SW_SHOW);
		m_btn_Save_Ins.ShowWindow(SW_SHOW);
		m_list_Ins.ShowWindow(SW_SHOW);
		break;
	case 1:
		hbmp[0] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION_DEVICE);
		hbmp[1] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION_LUA1);
		m_pic_UUT.SetBitmap(hbmp[0]);
		m_pic_Lua.SetBitmap(hbmp[1]);

		m_stc_Lua_Pic.ShowWindow(SW_SHOW);
		m_list_Lua.ShowWindow(SW_SHOW);
		m_btn_Save_Lua.ShowWindow(SW_SHOW);
		m_btn_Edt_Lua_Pic.ShowWindow(SW_SHOW);
		
		m_group_UUT.ShowWindow(SW_HIDE);
		m_stc_UUT.ShowWindow(SW_HIDE);
		m_edt_UUT_Name.ShowWindow(SW_HIDE);
		m_stc_Drive_Name_UUT.ShowWindow(SW_HIDE);
		m_com_Drive_UUT.ShowWindow(SW_HIDE);
		m_btn_Drive_Name_UUT.ShowWindow(SW_HIDE);
		m_stc_UUT_Addr.ShowWindow(SW_HIDE);
		m_edt_UUT_Address.ShowWindow(SW_HIDE);
		m_btn_Save_UUT.ShowWindow(SW_HIDE);
		m_list_UUT.ShowWindow(SW_HIDE);
		
		m_group_Ins.ShowWindow(SW_HIDE);
		m_stc_Ins.ShowWindow(SW_HIDE);
		m_com_Ins.ShowWindow(SW_HIDE);
		m_stc_Driver_Name_Ins.ShowWindow(SW_HIDE);
		m_com_Drive_Name.ShowWindow(SW_HIDE);
		m_btn_Driver_Name_Ins.ShowWindow(SW_HIDE);
		m_stc_Ins_Address.ShowWindow(SW_HIDE);
		m_edt_Ins_Address.ShowWindow(SW_HIDE);
		m_btn_Save_Ins.ShowWindow(SW_HIDE);
		m_list_Ins.ShowWindow(SW_HIDE);
		break;
	}
}

void CInsDocSolution::OnPicUut()
{
	m_WindowShow = UUT;
	UUT_LUA_SHOW(m_WindowShow);
}

void CInsDocSolution::OnPicLua() 
{
	m_WindowShow = LUA;
	UUT_LUA_SHOW(m_WindowShow);
}


void CInsDocSolution::UpdateChangeState(int nChangeState)
{
	switch(nChangeState)
	{
	case 1:
		m_btn_Solution_Change.SetWindowText("修改");

		m_btn_Solution_Change.EnableWindow(TRUE);
		m_btn_Add_Solution.EnableWindow(FALSE);
		m_btn_Del_Solution.EnableWindow(FALSE);
		m_btn_Drive_Name_UUT.EnableWindow(FALSE);
		m_btn_Driver_Name_Ins.EnableWindow(FALSE);
		m_btn_Edt_Lua_Pic.EnableWindow(FALSE);
		m_btn_Save_Ins.EnableWindow(FALSE);
		m_btn_Save_Lua.EnableWindow(FALSE);
		m_btn_Save_UUT.EnableWindow(FALSE);
		break;
	case 2:
		m_btn_Solution_Change.SetWindowText("禁止修改");

		m_btn_Solution_Change.EnableWindow(TRUE);
		m_btn_Add_Solution.EnableWindow(TRUE);
		m_btn_Del_Solution.EnableWindow(TRUE);
		m_btn_Drive_Name_UUT.EnableWindow(TRUE);
		m_btn_Driver_Name_Ins.EnableWindow(TRUE);
		m_btn_Edt_Lua_Pic.EnableWindow(TRUE);
		m_btn_Save_Ins.EnableWindow(TRUE);
		m_btn_Save_Lua.EnableWindow(TRUE);
		m_btn_Save_UUT.EnableWindow(TRUE);
		break;
	default:
		m_btn_Solution_Change.SetWindowText("修改");

		m_btn_Solution_Change.EnableWindow(FALSE);
		m_btn_Add_Solution.EnableWindow(FALSE);
		m_btn_Del_Solution.EnableWindow(FALSE);
		m_btn_Drive_Name_UUT.EnableWindow(FALSE);
		m_btn_Driver_Name_Ins.EnableWindow(FALSE);
		m_btn_Edt_Lua_Pic.EnableWindow(FALSE);
		m_btn_Save_Ins.EnableWindow(FALSE);
		m_btn_Save_Lua.EnableWindow(FALSE);
		m_btn_Save_UUT.EnableWindow(FALSE);
		break;
	}
}

void CInsDocSolution::OnButtonSolutionChange() 
{
	m_nChangeState = m_nChangeState == 1 ? 2 : 1;
	UpdateChangeState(m_nChangeState);
}
