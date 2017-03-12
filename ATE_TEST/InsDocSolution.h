#if !defined(AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_)
#define AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListSolutionFun.h"
#include "ListInsSolution.h"

#include "Xml_UUTInfoSet.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolution dialog
using namespace std;

enum EnumWindowShow{UUT, LUA};

class CInsDocSolution : public CDialog
{
// Construction
public:
	CInsDocSolution(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocSolution)
	enum { IDD = IDD_INSDOC_SOLUTION };
	CStatic	m_stc_Lua_Pic;
	CButton	m_group_Solution;
	CStatic	m_pic_UUT;
	CStatic	m_pic_Lua;
	CButton	m_btn_Solution_Change;
	CButton	m_btn_Edt_Lua_Pic;
	CButton	m_btn_Del_Solution;
	CStatic	m_stc_Drive_Name_UUT;
	CComboBox	m_com_Drive_UUT;
	CButton	m_btn_Drive_Name_UUT;
	CEdit	m_edt_UUT_Name;
	CButton	m_btn_Save_UUT;
	CButton	m_btn_Save_Ins;
	CButton	m_btn_Save_Lua;
	CStatic	m_stc_Driver_Name_Ins;
	CButton	m_btn_Driver_Name_Ins;
	CComboBox	m_com_Drive_Name;
	CStatic	m_stc_UUT_Addr;
	CStatic	m_stc_Ins_Address;
	CComboBox	m_com_Ins;
	CEdit	m_edt_Ins_Address;
	CEdit	m_edt_UUT_Address;
	CButton	m_group_Ins;
	CButton	m_group_UUT;
	CButton	m_btn_Add_Solution;
	CComboBox	m_com_Solution;
	CListSolutionFun	m_list_Ins;
	CListInsSolution	m_list_Lua;
	CListSolutionFun	m_list_UUT;
	CStatic	m_stc_Ins;
	CStatic	m_stc_UUT;
	//}}AFX_DATA

	
	CArray<UUTItemInfo, UUTItemInfo> m_testItem;//所有可测试项目
	CString m_strKind;				//装置类型
	CString m_strModel;				//装置名称
	CString m_strSolution;			//解决方案名
	CString m_strUUInfoPath;		//测试信息存放路径
	CString m_strEngineINIPath;		//引擎配置文件路径		
	CString	m_strSoluDirPath;		//解决方案文件夹路径
	CString m_strTestConfigINIPath;	//解决方案测试配置文件路径
	CString m_strDllName_UUT;		//UUT的dll名称
	CStringArray m_strFuncArray_UUT;//UUT的dll可用函数
	CString m_strDllName_Ins;		//测试设备的的dll名称
	CStringArray m_strFuncArray_Ins;//当前测试设备的dll可用函数
	CStringArray m_srtInsArray;
	EnumWindowShow m_WindowShow;//显示被测_测试设备 || 脚本_接线图 界面标志
	int 	m_nChangeState;//修改标志位;

	void initAll(CString strKind, CString strModel);
	void initComSolution();			//初始化组合框
	void GetSolution();				//获得解决方案
	void initUUT_InsName_InsDriver();//初始化被测试设备驱动组合框, 引擎函数, 及测试设备组合框, 测试设备驱动组合框
	void initUUTList();				//初始化被测试设备测试配置函数
	void initIns();					//初始化测试设备引擎函数
	void initInsList();				//初始化测试设备测试配置函数
	void initTestFunc();			//初始化Lua列表的测试功能列
	void initLua_ConnectPic();		//初始化Lua列表的脚本及接线图
	void CopyDriver(int nType);		//拷贝驱动,0为UUT驱动, 1为测试设备驱动
	void UUT_LUA_SHOW(int nIUUt_Lua); //显示被测_测试设备 OR 脚本_接线图
	void UpdateChangeState(int nChangeState);//更新所有控件的状态
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocSolution)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_brush;
	// Generated message map functions
	//{{AFX_MSG(CInsDocSolution)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonAddTestsolution();
	afx_msg void OnSelchangeComboSolutionInsdoc();
	afx_msg void OnButtonDriverName();
	afx_msg void OnButtonSaveUut();
	afx_msg void OnButtonDelTestsolution();
	afx_msg void OnSelchangeComboDriverName2();
	afx_msg void OnSelchangeComboIns();
	afx_msg void OnSelchangeComboDriverName();
	afx_msg void OnButtonDriverName2();
	afx_msg void OnButtonSaveIns();
	afx_msg void OnButtonSaveSolution();
	afx_msg void OnButtonEdtLuaPic();
	afx_msg void OnPicUut();
	afx_msg void OnPicLua();
	afx_msg void OnButtonSolutionChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_)
