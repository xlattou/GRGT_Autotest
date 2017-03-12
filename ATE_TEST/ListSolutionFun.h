#if !defined(AFX_LISTSOLUTIONFUN_H__B6C05CA8_67C4_4323_AD67_011B3AA995FB__INCLUDED_)
#define AFX_LISTSOLUTIONFUN_H__B6C05CA8_67C4_4323_AD67_011B3AA995FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListSolutionFun.h : header file
//
#include "ListCtrlCl.h"
/////////////////////////////////////////////////////////////////////////////
// CListSolutionFun window

class CListSolutionFun : public CListCtrlCl
{
// Construction
public:
	CListSolutionFun();

	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
	
	CStringArray m_strFuncArray;//当前测试设备的dll可用函数
	CString      m_srtDll;
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
	virtual ~CListSolutionFun();

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

#endif // !defined(AFX_LISTSOLUTIONFUN_H__B6C05CA8_67C4_4323_AD67_011B3AA995FB__INCLUDED_)
