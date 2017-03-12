#if !defined(AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_)
#define AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lua_Pic_List_Dlg.h : header file
#include "List_Lua_Pic.h"

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg dialog

class CLuaList : public CDialog
{
// Construction
public:
	CLuaList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Lua_Pic_List_Dlg)
	enum { IDD = IDD_DIALOG_LUA_LIST };
	CButton	m_check;
	CEdit	m_Edit;
	CList_Lua_Pic	m_List;
	//}}AFX_DATA

	CString m_strKind;
	CString m_strModel;
	CString m_strSolution;
	CString m_strLua;
	CString m_strRefTempPath;
	CString m_strReferModel;
	CString m_strReferSolution;
	CStringArray m_strPathArray;//参考型号的路径
	CStringArray m_strModelArray;
	CStringArray m_strSolutionArray;
	BOOL    m_bRefer; //是否参照其他

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLuaList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Lua_Pic_List_Dlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_)
