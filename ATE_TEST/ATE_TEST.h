// ATE_TEST.h : main header file for the ATE_TEST application
//

#if !defined(AFX_ATE_TEST_H__0D6DEB99_678C_495A_9EEE_50A3D7DD4811__INCLUDED_)
#define AFX_ATE_TEST_H__0D6DEB99_678C_495A_9EEE_50A3D7DD4811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CATE_TESTApp:
// See ATE_TEST.cpp for the implementation of this class
//

class CATE_TESTApp : public CWinApp
{
public:
	_ConnectionPtr m_pConnection;
	CATE_TESTApp();
	void RegesistSoft();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CATE_TESTApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CATE_TESTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATE_TEST_H__0D6DEB99_678C_495A_9EEE_50A3D7DD4811__INCLUDED_)
