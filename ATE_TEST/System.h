#if !defined(AFX_SYSTEM_H__6D82B943_709C_4847_9A67_297C98C20003__INCLUDED_)
#define AFX_SYSTEM_H__6D82B943_709C_4847_9A67_297C98C20003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// System.h : header file
//
#include "SetUser.h"
#include "WebAdm.h"
#include "DatabaseAdm.h"
#include "SaveAdm.h"
#include "EasySize.h"
#include "MyTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSystem dialog

class CSystem : public CDialog
{
// Construction
public:
	CSetUser m_setUser;
	CWebAdm m_webAdm;
	CDatabaseAdm m_DataBaseAdm;
	CSaveAdm m_SaveAdm;
	CSystem(CWnd* pParent = NULL);   // standard constructor
	CBrush m_brush;
// Dialog Data
	//{{AFX_DATA(CSystem)
	enum { IDD = IDD_SYSTEM };
	CMyTabCtrl	m_tab;	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystem)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystem)

    afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EASYSIZE
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEM_H__6D82B943_709C_4847_9A67_297C98C20003__INCLUDED_)
