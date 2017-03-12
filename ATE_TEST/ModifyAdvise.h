#if !defined(AFX_MODIFYADVISE_H__70F3137D_C971_4B35_B04C_4CE6A0958BAD__INCLUDED_)
#define AFX_MODIFYADVISE_H__70F3137D_C971_4B35_B04C_4CE6A0958BAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyAdvise.h : header file
//
#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
#include "Xml_Bll_FaultInfo.h"
#include "Xml_Bll_FaultReason.h"
#include "SetUser.h"

/////////////////////////////////////////////////////////////////////////////
// CModifyAdvise dialog

class CModifyAdvise : public CDialog
{
// Construction
	DECLARE_EASYSIZE

public:
	void InitListView();
	void InitTreeList();
	CModifyAdvise(CWnd* pParent = NULL);   // standard constructor
	CBrush m_brush;
	CXml_Bll_FaultInfo m_bll_FaultInfo;
	CXml_UUTKind m_bll_UUTKind;
	CFile_UUTInfo m_UUTInfo;
	CImageList m_imageList;
	CXml_Bll_FaultReason m_bll_FaultReason;
	HTREEITEM m_hItem;

// Dialog Data
	//{{AFX_DATA(CModifyAdvise)
	enum { IDD = IDD_MODIFYADVISE };
	CListCtrl	m_list_reason;
	CTreeCtrl	m_tree_tps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyAdvise)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyAdvise)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYADVISE_H__70F3137D_C971_4B35_B04C_4CE6A0958BAD__INCLUDED_)
