#if !defined(AFX_SAVEADM_H__DF66898B_A06D_4DB1_96E3_79E6F8079708__INCLUDED_)
#define AFX_SAVEADM_H__DF66898B_A06D_4DB1_96E3_79E6F8079708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveAdm.h : header file
//
#include "SaveAdm.h"

/////////////////////////////////////////////////////////////////////////////
// CSaveAdm dialog

class CSaveAdm : public CDialog
{
// Construction
public:
	CSaveAdm(CWnd* pParent = NULL);   // standard constructor
	CBrush m_brush;	
	virtual BOOL DestroyWindow();

// Dialog Data
	//{{AFX_DATA(CSaveAdm)
	enum { IDD = IDD_SAVE_ADM };
	CString	m_SavePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveAdm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
   protected:
	// Generated message map functions
	//{{AFX_MSG(CSaveAdm)		
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelSavePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEADM_H__DF66898B_A06D_4DB1_96E3_79E6F8079708__INCLUDED_)
