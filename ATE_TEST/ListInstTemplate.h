#if !defined(AFX_LISTINSTTEMPLATE_H__279529F0_F7F7_41E4_8393_5FA057E7C836__INCLUDED_)
#define AFX_LISTINSTTEMPLATE_H__279529F0_F7F7_41E4_8393_5FA057E7C836__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListCtrlCl.h"
#include "Xml_UUTInfoSet.h"

/////////////////////////////////////////////////////////////////////////////
// CListInstTemplate window

class CListInstTemplate : public CListCtrlCl
{
// Construction
public:
	CListInstTemplate();

	CEdit		m_Edit;
	CComboBox   m_combo;
	int			m_nEditItem;
	int			m_nEditSubItem;
	CString		m_strEditText;
	bool        m_bIgnore;
	
	CArray<UUTItemInfo, UUTItemInfo> m_testItem;//所有可测试项目
public:

	void initTestItemCom();
	void AddAllLine(int nListSelectItem);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListInstTemplate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListInstTemplate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListInstTemplate)
		afx_msg void OnSetfocusEdit();
		afx_msg void OnKillfocusEdit();
		afx_msg void OnSetfocusCombo();
		afx_msg void OnKillfocusCombo();
		afx_msg void OnLButtonDblClk(UINT nHitTest, CPoint point);
		afx_msg void OnSelchangeComboItem();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINSTTEMPLATE_H__279529F0_F7F7_41E4_8393_5FA057E7C836__INCLUDED_)
