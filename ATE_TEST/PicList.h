#if !defined(AFX_PICLIST_H__D7109DA4_8200_4CCF_99E1_BBA2DE262BA1__INCLUDED_)
#define AFX_PICLIST_H__D7109DA4_8200_4CCF_99E1_BBA2DE262BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "List_Lua_Pic.h"

/////////////////////////////////////////////////////////////////////////////
// CPicList dialog

class CPicList : public CDialog
{
// Construction
public:
	CPicList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPicList)
	enum { IDD = IDD_DIALOG_PIC_LIST };
	CList_Lua_Pic	m_List;
	CEdit	m_Edit;
	CButton	m_check;
	//}}AFX_DATA

	CString m_strKind;
	CString m_strModel;
	CString m_strSolution;
	CString m_strPic;
	CString m_strRefTempPath;
	CString m_strReferModel;
	CString m_strReferSolution;
	CStringArray m_strPathArray;//参考型号的路径
	CStringArray m_strModelArray;
	CStringArray m_strSolutionArray;
	BOOL    m_bRefer; //是否参照其他
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPicList)
	afx_msg void OnCheck1();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICLIST_H__D7109DA4_8200_4CCF_99E1_BBA2DE262BA1__INCLUDED_)
