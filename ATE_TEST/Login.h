#if !defined(AFX_LOGIN_H__6522CA8D_EFED_47DF_8584_8DADCAD53931__INCLUDED_)
#define AFX_LOGIN_H__6522CA8D_EFED_47DF_8584_8DADCAD53931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : header file
//
#include "ADO.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

class CLogin : public CDialog
{
// Construction
public:
	CLogin(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr m_pRecordset;  //¼ÇÂ¼¼¯Ö¸Õë

// Dialog Data
	//{{AFX_DATA(CLogin)
	enum { IDD = IDD_LOGIN };
	CString	m_sUserName;
	CString	m_sPwd;
	CADODataSet m_DataSet;
	CBrush m_brush;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogin)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_UserName;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__6522CA8D_EFED_47DF_8584_8DADCAD53931__INCLUDED_)
