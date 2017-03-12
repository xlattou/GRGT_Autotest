#if !defined(AFX_LISTINSDOCSOLUTION_H__F6FA0E9D_2730_46E1_86F8_42FC8819D05B__INCLUDED_)
#define AFX_LISTINSDOCSOLUTION_H__F6FA0E9D_2730_46E1_86F8_42FC8819D05B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListInsDocSolution.h : header file
#include "ListCtrlCl.h"

/////////////////////////////////////////////////////////////////////////////
// CListInsDocSolution window

class CListInsDocSolution : public CListCtrlCl
{
// Construction
public:
	CListInsDocSolution();

	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
	CString     m_strSolutionPath;
	CString     m_strKind;
	CString     m_strModel;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListInsDocSolution)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListInsDocSolution();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListInsDocSolution)
	afx_msg void OnSetfocusCombo();
	afx_msg void OnKillfocusCombo();
	afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINSDOCSOLUTION_H__F6FA0E9D_2730_46E1_86F8_42FC8819D05B__INCLUDED_)
