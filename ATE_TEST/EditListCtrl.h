#if !defined(AFX_EDITLISTCTRL_H__1BF941DD_BB72_4DD1_950B_1EE9725348E4__INCLUDED_)
#define AFX_EDITLISTCTRL_H__1BF941DD_BB72_4DD1_950B_1EE9725348E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window

#include "ItemEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window
class CEditListCtrl : public CListCtrl
{
// Construction
public:
	CEditListCtrl();
// Attributes
public:
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CEditListCtrl();
	// Generated message map functions
protected:
	//{{AFX_MSG(CEditListCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);//��ʼ�༭ʱ���账�������
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);//�����༭ʱ�账�������
	afx_msg void OnPaint();//�ؼ��ػ�ʱ��Ҫ���������
	afx_msg void OnKillFocus(CWnd* pNewWnd);//�ؼ�ʧȥ���������Ĵ���
	//}}AFX_MSG
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult); //�Զ���ؼ��Ļ���
	DECLARE_MESSAGE_MAP()
private:
	int			m_iItem;
	int			m_iSubItem;
	BOOL		m_bFocus;
	BOOL		m_bHighLight;
	CItemEdit	m_edtItemEdit;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTCTRL_H__1BF941DD_BB72_4DD1_950B_1EE9725348E4__INCLUDED_)
