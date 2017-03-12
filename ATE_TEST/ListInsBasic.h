#if !defined(AFX_LISTINSBASIC_H__94EE77DA_3F24_41B1_877A_0E42F970C90B__INCLUDED_)
#define AFX_LISTINSBASIC_H__94EE77DA_3F24_41B1_877A_0E42F970C90B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListCtrlCl.h"

class CListInsBasic : public CListCtrlCl
{
// Construction
public:
	CListInsBasic();

	CEdit		m_Edit;
	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListInsBasic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListInsBasic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListInsBasic)
		afx_msg void OnSetfocusEdit();
		afx_msg void OnKillfocusEdit();
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

#endif // !defined(AFX_LISTINSBASIC_H__94EE77DA_3F24_41B1_877A_0E42F970C90B__INCLUDED_)
