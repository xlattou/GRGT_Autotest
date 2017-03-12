#if !defined(AFX_WEBADM_H__0E374A7F_D754_4D02_A6FA_32C969823E9F__INCLUDED_)
#define AFX_WEBADM_H__0E374A7F_D754_4D02_A6FA_32C969823E9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WebAdm.h : header file
//

#include <WINSOCK2.H>
#pragma comment (lib,"ws2_32.lib")							//Á´½Ó¿âÎÄ¼þ

#include "EasySize.h"
/////////////////////////////////////////////////////////////////////////////
// CWebAdm dialog

class CWebAdm : public CDialog
{
// Construction
public:
	CWebAdm(CWnd* pParent = NULL);   // standard constructor
	char* ip;
	SOCKET m_socket;
	CBrush m_brush;
	virtual BOOL DestroyWindow();
// Dialog Data
	//{{AFX_DATA(CWebAdm)
	enum { IDD = IDD_WEB };
	CString	m_IPP;
	CString	m_port;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebAdm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
			
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWebAdm)
	afx_msg void OnSetWeb();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EASYSIZE
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBADM_H__0E374A7F_D754_4D02_A6FA_32C969823E9F__INCLUDED_)
