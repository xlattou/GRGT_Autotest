#if !defined(AFX_INPUTMODELNAME_FACTURY_H__5CCFD58A_DA9E_422E_BB22_12F56D40C3A0__INCLUDED_)
#define AFX_INPUTMODELNAME_FACTURY_H__5CCFD58A_DA9E_422E_BB22_12F56D40C3A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputModelName_Factury.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputModelName_Factury dialog

class CInputModelName_Factury : public CDialog
{
// Construction
public:
	CInputModelName_Factury(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputModelName_Factury)
	enum { IDD = IDD_DIALOG_ADD_MODEL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CString strName;
	CString strFactory;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputModelName_Factury)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputModelName_Factury)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTMODELNAME_FACTURY_H__5CCFD58A_DA9E_422E_BB22_12F56D40C3A0__INCLUDED_)
