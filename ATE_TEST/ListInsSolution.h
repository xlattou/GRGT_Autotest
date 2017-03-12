#if !defined(AFX_LISTINSSOLUTION_H__69A329A5_F6D3_4C81_8390_E9C202CFC7A6__INCLUDED_)
#define AFX_LISTINSSOLUTION_H__69A329A5_F6D3_4C81_8390_E9C202CFC7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListInsSolution.h : header file
#include "ListCtrlCl.h"

/////////////////////////////////////////////////////////////////////////////
// CListInsSolution window

class CListInsSolution : public CListCtrlCl
{
// Construction
public:
	CListInsSolution();

	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
	
	CStringArray m_strLuaArray;//Lua
	CStringArray m_strPicArray;//Pic
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListSolutionFun)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListInsSolution();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListSolutionFun)
	afx_msg void OnSetfocusCombo();
	afx_msg void OnKillfocusCombo();
	afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuClearCell();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINSSOLUTION_H__69A329A5_F6D3_4C81_8390_E9C202CFC7A6__INCLUDED_)
