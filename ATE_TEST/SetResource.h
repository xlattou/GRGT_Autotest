#if !defined(AFX_SETRESOURCE_H__199635E6_3494_40B4_AFC2_82F7C3C8191F__INCLUDED_)
#define AFX_SETRESOURCE_H__199635E6_3494_40B4_AFC2_82F7C3C8191F__INCLUDED_

#include "NewMenu.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetResource.h : header file
//
#include "NewMenu.h"
/////////////////////////////////////////////////////////////////////////////
// CSetResource dialog

class CSetResource : public CDialog
{
	DECLARE_EASYSIZE
// Construction
public:
	CNewMenu m_newMenu;
	int BrowsFunc(CString strMyFilePath);
	CString ListInsBasic(int intMyID);
//	TiXmlElement * pRootEle;
//	TiXmlDocument * pDoc_Ins;
	CString myStartPath;
	int BrowsIns(HTREEITEM hMyTreeItem,CString strMyDriveName);
	CImageList m_imageList;
	_RecordsetPtr m_pRecordset;
	CSetResource(CWnd* pParent = NULL);   // standard constructor
	

// Dialog Data
	//{{AFX_DATA(CSetResource)
	enum { IDD = IDD_SET_RESOURCE };
	CListCtrl	m_List_Info;
	CListCtrl	m_List_Ins;
	CTreeCtrl	m_tree_res;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetResource)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetResource)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClickTreeRes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTreeRes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMenuCreate();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETRESOURCE_H__199635E6_3494_40B4_AFC2_82F7C3C8191F__INCLUDED_)
