#if !defined(AFX_FRM_TESTTEMPLE_H__21FDAB5B_0051_4C01_82EA_11EE38F18820__INCLUDED_)
#define AFX_FRM_TESTTEMPLE_H__21FDAB5B_0051_4C01_82EA_11EE38F18820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EditListCtrl.h"
#include "Xml_TestItem.h"
#include "ReadXML.h"
#include "XML.h"
#include "File_UUTInfo.h"
#include "MyTabCtrl.h"
#include "Frame_FirstPaper.h"
#include "Frame_Content.h"

//编辑的状态
#define EDIT 1
#define NEDIT 0

// Frm_TestTemple.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestTemple dialog

struct colID
{
	int Point_ID;
	int Unit;
	int Set;
	int nRange;
	int error;
	int Column;
	int LineNum;
	int nVarSet;
	int nError;
};


class CFrm_TestTemple : public CDialog
{
// Construction
public:
	void InitTreeView();					 //初始化tree控件，显示模板名
	CFrm_TestTemple(CWnd* pParent = NULL);   // standard constructor
	CFrm_TestTemple(CString strKind,CString strModel,CWnd* pParent = NULL);  
	int nSpan;
	struct colID m_colID;
	CString m_selItem;
	//int m_nListPoint;
	vector<VarName> m_testCol;		//记录varSet的项目逻辑名和中文名
	CXML m_pointXML;
	CString m_strKind;
	CString m_strModel;
	CString m_pthFile;
	CFile_UUTInfo m_file_UUTInfo;		//文件类，用于获取文件列表
	int m_state;						//用于标识当前的是否处于编辑状态

	CFrame_FirstPaper m_frmFirst;
	CFrame_Content m_frmContent;
	CBrush m_brush;

// Dialog Data
	//{{AFX_DATA(CFrm_TestTemple)
	enum { IDD = IDD_DIALOG_TESTTEMPLE };
	CTabCtrl	m_tab_Tem;
	CTreeCtrl	m_tree_temp;
//	CListCtrl	m_testList;
//	CEditListCtrl	m_testPoint;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrm_TestTemple)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrm_TestTemple)
	virtual BOOL OnInitDialog();
//	virtual void OnOK();
//	afx_msg void OnClickListPoint(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnDelete();
	afx_msg void OnReturn();
//	afx_msg void OnClickTestItem(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnSave();
//	afx_msg void OnAddUnit();
//	afx_msg void OnNewTemp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRM_TESTTEMPLE_H__21FDAB5B_0051_4C01_82EA_11EE38F18820__INCLUDED_)
