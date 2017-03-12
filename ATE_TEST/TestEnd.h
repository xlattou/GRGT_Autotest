#if !defined(AFX_TESTEND_H__0A4CB0BF_8D44_47BB_9F41_ECC11D93FD07__INCLUDED_)
#define AFX_TESTEND_H__0A4CB0BF_8D44_47BB_9F41_ECC11D93FD07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestEnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestEnd dialog

class CTestEnd : public CDialog
{
// Construction
public:
	CBrush m_brush;
	CTestEnd(CWnd* pParent = NULL);   // standard constructor
	CTestEnd(CString strConclusion,CWnd* pParent = NULL);   // standard constructor
	CString m_strResult;


// Dialog Data
	//{{AFX_DATA(CTestEnd)
	enum { IDD = IDD_DIALOG_TESTEND };
	CComboBox	m_cb_Result;
	CString	m_strConclusion;
	BOOL	m_bReport;
	BOOL	m_bSave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestEnd)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestEnd)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTEND_H__0A4CB0BF_8D44_47BB_9F41_ECC11D93FD07__INCLUDED_)
