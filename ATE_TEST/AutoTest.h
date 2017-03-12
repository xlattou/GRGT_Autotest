#if !defined(AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_)
#define AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoTest.h : header file
//

#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
#include "Xml_UUTInfo.h"
#include "Xml_Bll_UUTPointInfo.h"
#include "Xml_Bll_PointVarInfo.h"
#include "Xml_Bll_FaultInfo.h"
#include "Xml_Bll_FaultReason.h"
#include "PathOperate.h"
#include "LoadTP.h"
#include "TestEnd.h"
#include "ShareMemory.h"
#include "Xml_Bll_UUTItem_Tem.h"
#include "Xml_Bll_UUTItem.h"
#include "FileOpe_Excel.h"
#include "tb_TestInfo.h"
#include "tb_TestResult.h"
#include "Frame_TestConnect.h"
#include "Report.h"
#include "Ini.h"
#include "Frame_FAIL.h"
#include "SetInstrAddress.h"
#include "afxwin.h"

#define WM_MYUPDATEDATA WM_USER+1000
/////////////////////////////////////////////////////////////////////////////
// CAutoTest dialog
class CAutoTest : public CDialog
{
// Construction
	DECLARE_EASYSIZE
public:
	void StringToArray(CString strInput,CString key,vector<CString>*stringArray);// 字符串转换成字符串数组，主要以","作为分隔符
	CString ConvertTickToTime(int intTickCount); //计时
	void UpdateInsList();  //更新仪器列表
	void UpdateSoluList(CString strSoluName); //更新解决方案框
	void UpdateFirstPaper(); //更新主页面的一些值
	int SaveTestResultToAccess(vector<stucTestResult> vTestResult,int intTestInfoID);//单点复测后使用， 将有结果的测试数据进行保存
	int SaveTestInfoToAccess(CString strResult,CString strConclusion,int m_intIDTemp); //测试结果保存至ACCESS
	void UpdateModuleList(CString strTemplete);  //刷新测试模版列表
	void UpdateListBox(int mark);  //更新测试流程显示，文本框中输出测试过程
	void UpdateListView();  //更新测试列表测试项目
	BOOL Aduge(CString strResult,CString strUpper,CString strLower); //判断结果值
	void UpdateControl(int intStatus); //更新控件状态
	LRESULT OnUpdateMyData(WPARAM wParam,LPARAM lParam);
    //UINT ProgTest(LPVOID lpParam);
	HTREEITEM m_hItem_Pre; //树控件型号选项标志位

	void InitListView();  //初始化测试列表控件
	void UpdateTestInfo();  //刷新基本信息表
	void InitTreeList();  //初始化设备树列表
	CAutoTest(CWnd* pParent = NULL);   // standard constructor
	CImageList m_imageList;
	CImageList m_imageListSmall;  //保存仪器连通状态图片
	ShareMemory m_ShareMem; //发送到显示区内容，最大不超过255字节
	CString m_strShare;

	CXml_UUTKind m_xml_Kind;  //UUTKind.xml中获取仪器列表
	CFile_UUTInfo m_file_UUTInfo; //获取模板文件列表
	CXml_UUTInfo m_bll_UUTInfo; //uut.xml中基本信息处理类
	CXml_Bll_UUTPointInfo m_bll_UUTPointInfo;  //document/tem.xml中对测试点信息的处理类
	CXml_Bll_PointVarInfo m_bll_UUTPointVar;  //Document/templete.xml中对测试点变量的处理类
//	CXml_Bll_FaultInfo m_bll_faultInfo;  //故障信息，本文用不着
//	CXml_Bll_FaultReason m_bll_faultReason; //故障原因，本文用不着
	CXml_Bll_UUTItem_Tem m_bll_UUTITem_tem; //document/tem.xml中对测试项目信息的处理类
	CXml_Bll_UUTItem m_bll_UUTItem; //TestConfig/uut.xml中项目设置信息
	Ctb_TestInfo m_bll_TestInfo; //测试结果信息与数据库
	Ctb_TestResult m_bll_TestResult; //测试结果信息与数据库
	CIni  m_iniOpe;

	CString m_strUpper,m_strLower,m_strUnit,m_strResult;
	


	vector<TestItemState> m_vItemState;  //项目状态信息列表
	vector<CString> m_vKeyList; //测试项目关键字列表，用于存储测试列表中的关键字key，测试时根据项目关键字，查找并调用Lua
	vector<CString> m_vItemName; //测试项目名称
	vector<stucTestResult> m_vTestResult;  //测试结果列表
	vector<BOOL> m_listVCheckState; //记录测试的选中状态


	CPathOperate m_pathOpe;
	CString m_strThreadKind;  //类别，例数字万用表
	CString m_strThreadModel; //型号，例Agilent 34401A
	CString m_strTem;
	BOOL m_isStop;
	int m_intTestLine;  //测试行
	int m_intTestSerial; //测试项计数
	BOOL m_isTestEnd;
	CBrush m_brush;
	CString m_strStartPath;
	CString m_strConclusion;
	CString m_strSoluName; //解决方案文件夹名称


	CString m_strConnectPic;  //测试连接图
	CString m_strDescription_Conn; //连接提示
	CString m_strItemName; //测试项目名称
	CString m_strTestMark; //测试项目标示
	int m_intPointID;
	int m_intPotCount;
	BOOL m_isPotCheck;

	int m_intTimeTick; //时间计数器
	int m_intRetestMark;
	CString m_strResultIndicate; //界面显示的测试结果
	bool m_bIgnoreCurrentItem;				 //忽略当前测试项目标志位


// Dialog Data
	//{{AFX_DATA(CAutoTest)
	enum { IDD = IDD_AUTOTEST };
	CButton	m_calibration_All;
	CListCtrl	m_list_Ins;//测试设备列表
	CComboBox	m_cb_Solution;//方案
	CComboBox	m_cbb_DuTime;//有效期
	CEdit	m_edit_List;//测试流程
	CButton	m_check_All;//测试流程全选
	CProgressCtrl	m_progress_test;//测试进度显示
	CComboBox	m_cbModule; //测试模板名
	CListBox	m_listBox_Status;
	CListCtrl	m_List_Result; //测试结果
	CTreeCtrl	m_tree_tps;//测试产品列表
	CString	m_strManu;//厂家
	CString	m_strModel;//型号
	CString	m_strName;//名称
	CString	m_strNumber;//编号
	CString	m_edit_Progress;//测试进度数值显示
	CString	m_strCustomer;//委托方
	CString	m_strNumber_Mana;//管理号
	CString	m_strTemperature;//温度
	CString	m_strHumity;//湿度
	CString	m_strAddress_Customer;//客户地址
	CTime	m_DateTime;//测试时间
	int		m_intTestStation;//测试地点
	int		m_intInsUse;//用途
	CString	m_strTestTime;//测试时间
	CString	m_strElapseTime;//剩余时间
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoTest)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult);//测试设备选择树点击操作
	afx_msg void OnPaint();
	afx_msg void OnButtonTest(); //测试按钮选中
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);//获取测试列表中的结果值进行判断
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnItemdblclickListResult(NMHDR* pNMHDR, LRESULT* pResult);//双击转换测试序列选中状态
	afx_msg void OnDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusEditNumber();
	afx_msg void OnKillfocusEditNumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonTestset();  //设备设置
	afx_msg void OnSelchangeComboModule();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonReport();
	afx_msg void OnCheckAll();
	afx_msg void OnButtonReTest();
	afx_msg void OnSelchangeComboSolution();
	afx_msg void OnStaticNum();
	afx_msg void OnButtonGetsn(); //获取SN号
	afx_msg void OnButtonInstrstate();
	afx_msg void OnCalibrationAll();
	afx_msg void OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_TestButton;
	afx_msg void OnButtonStop();
	CEdit m_Num;
	CEdit m_ManageNum;
	CComboBox m_TestAddress;
	CButton m_GetSN;
	CString m_IP;
	CString m_CH;
	CString m_VSG;
	CString m_ROUT;
};
DWORD WINAPI ProgTest(CAutoTest *p);




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_)


