#if !defined(AFX_LISTEXCELFRONTPAGE_H__8CDF0CFA_F8EA_47D2_8222_6895DEACC35E__INCLUDED_)
#define AFX_LISTEXCELFRONTPAGE_H__8CDF0CFA_F8EA_47D2_8222_6895DEACC35E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListExcelFrontPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListExcelFrontPage window

class CListExcelFrontPage : public CListCtrl
{
// Construction
public:
	CListExcelFrontPage();
	CEdit		m_Edit;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListExcelFrontPage)
	protected:
		virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListExcelFrontPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListExcelFrontPage)
		afx_msg void OnSetfocusEdit();
		afx_msg void OnKillfocusEdit();
		afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTEXCELFRONTPAGE_H__8CDF0CFA_F8EA_47D2_8222_6895DEACC35E__INCLUDED_)
