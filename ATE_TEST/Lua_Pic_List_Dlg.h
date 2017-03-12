#if !defined(AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_)
#define AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lua_Pic_List_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Lua_Pic_List_Dlg dialog

class Lua_Pic_List_Dlg : public CDialog
{
// Construction
public:
	Lua_Pic_List_Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Lua_Pic_List_Dlg)
	enum { IDD = IDD_DIALOG_LUA_PIC_LIST };
	CButton	m_check2;
	CButton	m_check;
	CEdit	m_Edit;
	CListCtrl	m_List;
	//}}AFX_DATA

	int     m_nType;
	CString m_strKind;
	CString m_strModel;
	CString m_strTemplate;
	CString m_strRefTempPath;
	CString m_strReferModel;
	CStringArray m_strPathArray;//参考型号的路径
	CStringArray m_strModelArray;
	CStringArray m_strSolutionArray;
	BOOL    m_bRefer; //是否参照其他
	BOOL	m_bSameName;//

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Lua_Pic_List_Dlg)
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
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUA_PIC_LIST_DLG_H__17C461FB_205E_4F31_8AFB_46CE5D60BA5D__INCLUDED_)
