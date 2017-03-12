#if !defined(AFX_SETUSER_H__FB36314B_E4E0_459E_89AA_0718758AD25D__INCLUDED_)
#define AFX_SETUSER_H__FB36314B_E4E0_459E_89AA_0718758AD25D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
#include "ADO.h"
#include "EasySize.h"
 // _MSC_VER > 1000
// SetUser1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUser dialog

class CSetUser : public CDialog
{
	DECLARE_EASYSIZE
// Construction
public:
	//int GenerateID();
	
	CADODataSet m_DataSet;
	void UpdateUserList();
	CSetUser(CWnd* pParent = NULL);   // standard constructor
    CBrush m_brush;

// Dialog Data
	//{{AFX_DATA(CSetUser)
	enum { IDD = IDD_SET_USER };
	CListCtrl	m_userList;
	CString	m_sName;
	CString	m_sPwd1;
	CString	m_sPwd2;
	CString	m_sPower;
	CString	m_sPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUser)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnNewBtn();
	afx_msg void OnDelBtn();
	afx_msg void OnClickListUser(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeBtn();
	afx_msg void OnSave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUSER_H__FB36314B_E4E0_459E_89AA_0718758AD25D__INCLUDED_)
