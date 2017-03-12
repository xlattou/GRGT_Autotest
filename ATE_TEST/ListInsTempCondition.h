#if !defined(AFX_LISTINSTEMPCONDITION_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_)
#define AFX_LISTINSTEMPCONDITION_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListInsTempCondition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListInsTempCondition window

class CListInsTempCondition : public CListCtrl
{
// Construction
public:
	CListInsTempCondition();

	CEdit		m_Edit;
	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
	CStringArray m_strTypeArray;
	CStringArray m_strUnitArray;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListInsTempCondition)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListInsTempCondition();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListInsTempCondition)
		afx_msg void OnSetfocusEdit();
		afx_msg void OnKillfocusEdit();
		afx_msg void OnSetfocusCombo();
		afx_msg void OnKillfocusCombo();
		afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINSTEMPCONDITION_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_)
