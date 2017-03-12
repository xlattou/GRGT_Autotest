#if !defined(AFX_TESTLUA_H__3D028FF1_6C30_49D1_B096_83EE4BE22834__INCLUDED_)
#define AFX_TESTLUA_H__3D028FF1_6C30_49D1_B096_83EE4BE22834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AFXTEMPL.H>
#include "CodeSymbol.h"
#include "CodeText.h"
#include "TestLuaStruct.h"

/////////////////////////////////////////////////////////////////////////////
// TESTLUA dialog
typedef struct CODEINFO
{
	bool	bIsDebug;
	bool	bIsBreak;
	CString strCode;
}codeinfo;

class TESTLUA : public CDialog
{
// Construction
public:
	TESTLUA(CWnd* pParent = NULL);   // standard constructor
	~TESTLUA();   // standard constructor
	bool  m_bDebug;

	CString m_strPath;//Lua脚本路径
	int		m_nVScroll;//纵向进度条刻度
	int		m_nHScroll;//横向进度条刻度
	CString m_strUUInfoPath;
	CString m_strSoluDirPath;
	CString m_strSolution;
	CString m_strKind;
	CString m_strModel;
	CString m_strEngineINIPath;
	CString m_strTestConfigINIPath;
	CImageList m_imageList;
	CArray<TestLuaInstr, TestLuaInstr> m_TestInstructionArray;

	CArray<codeinfo, codeinfo> m_CodeInfo_Array;

	int     m_nInsType;
	CString m_strLuaFun;

	BOOL ReadLua();
	BOOL WriteLua();
	void ReadEngineFun();
	void initEngineFunTree();
	
	void OnVScrollCus(int nSBCode);
	void OnHScrollCus(int nSBCode);
// Dialog Data
	//{{AFX_DATA(TESTLUA)
	enum { IDD = IDD_DIALOG_TEST_LUA };
	CButton	m_btn_Test_Lua_Ins_Fun;
	CEdit	m_edt_Test_Lua_Para;
	CEdit	m_edt_Test_Lua_Addr;
	CComboBox	m_com_Test_Lua_Seri;
	CComboBox	m_com_Test_Lua_Mode;
	CStatic	m_stc_Lua_Name;
	CEdit	m_edt_Lua_Fun_Disc;
	CStatic	m_stc_Engine_Func;
	CButton	m_group_Output;
	CTreeCtrl	m_tree_Lua_Func;
	CStatic	m_stc_Variant;
	CStatic	m_stc_Debug;
	CListCtrl	m_list_Variant;
	CEdit	m_edt_Lua_Output;
	CCodeText	m_Lua_Text;
	CCodeSymbol	m_Lua_Symbol;
	CScrollBar	m_scroll_V;
	CScrollBar	m_scroll_H;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TESTLUA)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TESTLUA)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLuaSave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnClickTreeLuaFunc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonTestLuaInstFun();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLUA_H__3D028FF1_6C30_49D1_B096_83EE4BE22834__INCLUDED_)
