#if !defined(AFX_EDT_LUA_PIC_H__76E2423D_43DE_4017_8D3B_DB82CCEF0DAE__INCLUDED_)
#define AFX_EDT_LUA_PIC_H__76E2423D_43DE_4017_8D3B_DB82CCEF0DAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TESTLUA.h"

/////////////////////////////////////////////////////////////////////////////
// CEdt_Lua_Pic dialog

class CEdt_Lua_Pic : public CDialog
{
// Construction
public:
	CEdt_Lua_Pic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEdt_Lua_Pic)
	enum { IDD = IDD_DIALOG_EDT_LUA_PIC };
	CListCtrl	m_List_Pic;
	CListCtrl	m_List_Lua;
	//}}AFX_DATA
	CString  m_strSoluDirPath;
	CString  m_strSolution;
	CString  m_strKind;
	CString  m_strModel;

	BOOL InitLua();
	BOOL InitPic();
	void TestLua(CString strLuaPath);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdt_Lua_Pic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEdt_Lua_Pic)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDT_LUA_PIC_H__76E2423D_43DE_4017_8D3B_DB82CCEF0DAE__INCLUDED_)
