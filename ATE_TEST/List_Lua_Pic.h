#if !defined(AFX_LIST_LUA_PIC_H__1FE84C6F_6C90_47E7_A2F3_3710F3965F03__INCLUDED_)
#define AFX_LIST_LUA_PIC_H__1FE84C6F_6C90_47E7_A2F3_3710F3965F03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// List_Lua_Pic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CList_Lua_Pic window

class CList_Lua_Pic : public CListCtrl
{
// Construction
public:
	CList_Lua_Pic();

	CEdit		m_Edit;
	int			m_nEditItem;
	int			m_nEditSubItem;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CList_Lua_Pic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CList_Lua_Pic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CList_Lua_Pic)
	afx_msg void OnSetfocusEdit();
	afx_msg void OnKillfocusEdit();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIST_LUA_PIC_H__1FE84C6F_6C90_47E7_A2F3_3710F3965F03__INCLUDED_)
