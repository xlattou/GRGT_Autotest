#if !defined(AFX_DATABASEADM_H__BC2EC47B_9557_40FE_95FC_B2244F4F5324__INCLUDED_)
#define AFX_DATABASEADM_H__BC2EC47B_9557_40FE_95FC_B2244F4F5324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EasySize.h"
// DatabaseAdm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatabaseAdm dialog

class CDatabaseAdm : public CDialog
{
// Construction
public:
	CBrush m_brush;
	CDatabaseAdm(CWnd* pParent = NULL);   // standard constructor
	virtual BOOL DestroyWindow();

// Dialog Data
	//{{AFX_DATA(CDatabaseAdm)
	enum { IDD = IDD_ADM_DATABASE };
	CString	m_DataBasePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseAdm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseAdm)
	afx_msg void OnBtnOpen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EASYSIZE
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEADM_H__BC2EC47B_9557_40FE_95FC_B2244F4F5324__INCLUDED_)
