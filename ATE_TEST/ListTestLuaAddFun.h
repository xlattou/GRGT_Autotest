#if !defined(AFX_LISTTESTLUAADDFUN_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_)
#define AFX_LISTTESTLUAADDFUN_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListTestLuaAddFun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ListTestLuaAddFun window

class CListTestLuaAddFun : public CListCtrl
{
// Construction
public:
	CListTestLuaAddFun();

	CEdit		m_Edit;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTestLuaAddFun)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListTestLuaAddFun();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListTestLuaAddFun)
		afx_msg void OnSetfocusEdit();
		afx_msg void OnKillfocusEdit();
		afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTESTLUAADDFUN_H__57F917AB_EF62_4B1F_9FFD_99F891D84E6B__INCLUDED_)
