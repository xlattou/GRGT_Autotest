//{{AFX_INCLUDES()
#include "dsoframecontrol.h"
//}}AFX_INCLUDES
#if !defined(AFX_INSDOCTEMPEXCEL_H__FB220B76_59A9_4A3A_9001_144811B6B474__INCLUDED_)
#define AFX_INSDOCTEMPEXCEL_H__FB220B76_59A9_4A3A_9001_144811B6B474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dsoframecontrol.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcel dialog

class CInsDocTempExcel : public CDialog
{
// Construction
public:
	CInsDocTempExcel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsDocTempExcel();
	CString m_strPath;

	BOOL KillExcel();
	BOOL GetDebugPriv();
// Dialog Data
	//{{AFX_DATA(CInsDocTempExcel)
	enum { IDD = IDD_INSDOC_TEMPLATE_EXCEL };
	CDSOFrameControl	m_DosExcel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocTempExcel)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocTempExcel)
	virtual BOOL OnInitDialog();
	afx_msg void OnOnActivationChangeDsoframer(BOOL fGoingActive);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPEXCEL_H__FB220B76_59A9_4A3A_9001_144811B6B474__INCLUDED_)
