#if !defined(AFX_TESTLUAADDFUN_H__75039097_7676_401C_9919_F0FF5203B269__INCLUDED_)
#define AFX_TESTLUAADDFUN_H__75039097_7676_401C_9919_F0FF5203B269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListTestLuaAddFun.h"

/////////////////////////////////////////////////////////////////////////////
// TestLuaAddFun dialog

class TestLuaAddFun : public CDialog
{
// Construction
public:
	TestLuaAddFun(CWnd* pParent = NULL);   // standard constructor
	CString m_strInsType;//�豸����
	CString m_strEngineFunName;//���溯������
	CString m_strTestFunDescibe;//��������
	CStringArray m_strParaArray;//�����б�
	CStringArray m_strGetParaArray;//��ò����б�
	bool    m_bGetPara;//�ѻ����ȷ����

// Dialog Data
	//{{AFX_DATA(TestLuaAddFun)
	enum { IDD = IDD_DIALOG_TEST_LUA_ADD_FUN };
	CListTestLuaAddFun	m_List_Para;
	CEdit	m_edt_Lua;
	CEdit	m_edt_C;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TestLuaAddFun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TestLuaAddFun)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLUAADDFUN_H__75039097_7676_401C_9919_F0FF5203B269__INCLUDED_)
