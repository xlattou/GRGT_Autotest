#if !defined(AFX_FRM_TESTCONFIG_H__B53B2CC4_90D9_43E1_96F6_36DA58110293__INCLUDED_)
#define AFX_FRM_TESTCONFIG_H__B53B2CC4_90D9_43E1_96F6_36DA58110293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Frm_TestConfig.h : header file
//
#include "File_UUTInfo.h"
#include "Xml_UUTInfo.h"
#include "InputFileName.h"
#include "Ini.h"

#define EDIT 1
#define NEDIT 0

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestConfig dialog

class CFrm_TestConfig : public CDialog
{
	// Construction
	DECLARE_EASYSIZE
public:
	void InitTreeView();
	CFrm_TestConfig(CWnd* pParent = NULL);   // standard constructor
	CFrm_TestConfig(CString strKind,CString strModel,CWnd* pParent = NULL);   // standard constructor
	CInputFileName m_NewFileNameDialog;
	CString m_strModel;
	CString m_strKind;
	CFile_UUTInfo m_file_UUTInfo;
	CXml_UUTInfo m_xml_UUTInfo;
	CBrush m_Brush; //背景刷子
	CString m_pthDriver;
	CString m_pthFunXML;
	CString m_pthINI;
	CString m_pthFile;
	CString m_nameINI;
	CString m_DriverName;
	CString m_pthFileXML;
	CString m_session;
	CString m_pthInstrDriver;
	CString m_driverFile;			//从种类开始的驱动文件夹名
	CString m_openFile;				//要读取的INI文件名 
	CString m_configName;			//在tree下读取的INI配置文件名
	CIni    m_INIFile;				//要进行操作的INI文件
	int		m_state;				//判断当前的状态，编辑或非编辑，编辑状态下可配置，否则不可配置
	
	// Dialog Data
	//{{AFX_DATA(CFrm_TestConfig)
	enum { IDD = IDD_DIALOG_TESTCONFIG };
	CEdit	m_edit_channel;
	CEdit	m_edit_port;
	CListCtrl	m_funList;
	CListCtrl	m_list_Required;
	CTreeCtrl	m_tree_Config;
	CComboBox   m_comboDriver;
	CString	m_port;
	CString	m_chanel;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrm_TestConfig)
public:
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CFrm_TestConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickTreeConfig(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboDriver();
	afx_msg void On_NewINI();
	afx_msg void OnSave();
	afx_msg void OnClickListInsrequired(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	afx_msg void OnEDIT();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRM_TESTCONFIG_H__B53B2CC4_90D9_43E1_96F6_36DA58110293__INCLUDED_)
