#include "afxwin.h"
#if !defined(AFX_FRAME_FAIL_H__47A39623_1103_4EA8_BDD5_B6FD7F711F05__INCLUDED_)
#define AFX_FRAME_FAIL_H__47A39623_1103_4EA8_BDD5_B6FD7F711F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Frame_FAIL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrame_FAIL dialog

class CFrame_FAIL : public CDialog
{
// Construction
public:
	CFrame_FAIL(CWnd* pParent = NULL);   // standard constructor
	CFrame_FAIL(CString strItemName,CString strConclusion,CString strUpper,CString strLower,
		CString strUnit,CString strResult,CString strTestSet,CString strPath,CWnd* pParent = NULL);   // 自定义构造函数
	int m_intControlMark;  //1=重测 2=忽略 3=终止

// Dialog Data
	//{{AFX_DATA(CFrame_FAIL)
	enum { IDD = IDD_DIALOG_FAIL };
	CString	m_strItemName;
	CString	m_strLower;
	CString	m_strTestSet;
	CString	m_strResult;
	CString	m_strUpper;
	CString	m_strConclusion;
	CString	m_strUnit;
	CString m_strPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrame_FAIL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrame_FAIL)
	afx_msg void OnButtonRetest();
	afx_msg void OnButtonIgnor();
	afx_msg void OnButtonStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonIgnor2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIgnoredialogButton();
	CButton m_IgnoreDialog;
	CButton m_IgnoreItemPoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAME_FAIL_H__47A39623_1103_4EA8_BDD5_B6FD7F711F05__INCLUDED_)
