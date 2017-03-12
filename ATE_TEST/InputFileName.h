#if !defined(AFX_INPUTFILENAME_H__DC511C52_05FB_4EE7_8BA6_09177CBC9A4E__INCLUDED_)
#define AFX_INPUTFILENAME_H__DC511C52_05FB_4EE7_8BA6_09177CBC9A4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputFileName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputFileName dialog

class CInputFileName : public CDialog
{
// Construction
public:
	CInputFileName(CWnd* pParent = NULL);   // standard constructor
	CString m_strTile;

// Dialog Data
	//{{AFX_DATA(CInputFileName)
	enum { IDD = IDD_DIALOG_INPUTFILENAME };
	CString	m_configFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputFileName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputFileName)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTFILENAME_H__DC511C52_05FB_4EE7_8BA6_09177CBC9A4E__INCLUDED_)
