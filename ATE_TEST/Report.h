#if !defined(AFX_REPORT_H__243CBDB1_30FC_4990_A855_6A90CEB33638__INCLUDED_)
#define AFX_REPORT_H__243CBDB1_30FC_4990_A855_6A90CEB33638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Report.h : header file
//
#include "tb_TestInfo.h"
#include "tb_TestResult.h"
#include "FileOpe_Excel.h"
#include "PathOperate.h"
//#include "Xml_Bll_UUTItem_Tem.h"
/////////////////////////////////////////////////////////////////////////////
// CReport dialog

class CReport : public CDialog
{
// Construction
public:
	void UpdateListView_Info(vector<stucTestInfo> vTestInfo);
	void SearchListV_TestInfo(CString strContent);
	void InitListView_Result();
	void UpdateTestResultList(int intTestInfoID);
	void GenerateReport(int nTestInfoID);
	void InitListView();
	CReport(CWnd* pParent = NULL);   // standard constructor
	Ctb_TestInfo m_tbTestInfo;
	Ctb_TestResult m_tbTestResult;
	CFileOpe_Excel m_Excel_Ope;
	CPathOperate m_pathOpe;
	int m_intHitLine_Pre;

// Dialog Data
	//{{AFX_DATA(CReport)
	enum { IDD = IDD_DIALOG_REPORT };
	CComboBox	m_cb_Search;
	CListCtrl	m_ListV_TestResult;
	CListCtrl	m_ListV_TestInfo;
	CString	m_strStatus;
	CString	m_strSearchKey;
	CString m_strKind;//设备类型
	CString m_strModel;//设备型号
	CString m_strtem;//模板名
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReport)
	virtual BOOL OnInitDialog();
	afx_msg void OnReturn();
	afx_msg void OnButtonReport();
	afx_msg void OnClickListTestinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSearchinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORT_H__243CBDB1_30FC_4990_A855_6A90CEB33638__INCLUDED_)
