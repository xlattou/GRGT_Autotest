#if !defined(AFX_INSTEMPAUTOFILLROW_H__F2EE77EB_FFC2_4831_A322_290C7FFC3DE5__INCLUDED_)
#define AFX_INSTEMPAUTOFILLROW_H__F2EE77EB_FFC2_4831_A322_290C7FFC3DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsTempAutoFillRow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsTempAutoFillRow dialog

class CInsTempAutoFillRow : public CDialog
{
// Construction
public:
	CInsTempAutoFillRow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsTempAutoFillRow)
	enum { IDD = IDD_DIALOG_FILL_ROW };
	CEdit	m_Edit;
	//}}AFX_DATA

	int m_nRow;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsTempAutoFillRow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsTempAutoFillRow)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTEMPAUTOFILLROW_H__F2EE77EB_FFC2_4831_A322_290C7FFC3DE5__INCLUDED_)
