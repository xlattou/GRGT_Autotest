#if !defined(AFX_INSDOCTEMPEXCELFRONTPAGE_H__D4206BB8_0A02_4213_BC43_5D2064A3AF1F__INCLUDED_)
#define AFX_INSDOCTEMPEXCELFRONTPAGE_H__D4206BB8_0A02_4213_BC43_5D2064A3AF1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Xml_FrontPage.h"
#include "ListExcelFrontPage.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcelFrontPage dialog

class CInsDocTempExcelFrontPage : public CDialog
{
// Construction
public:
	CInsDocTempExcelFrontPage(CWnd* pParent = NULL);   // standard constructor

	CString m_strSheetNumber;//Excel工作表序号
	CArray<FrontPage, FrontPage> m_vFrontPage;//工作表首页要填写的信息
	CStringArray m_strXMLArray;//xml存储标志
	CStringArray m_strNameArray;//名称标志
	bool m_bChanged;

// Dialog Data
	//{{AFX_DATA(CInsDocTempExcelFrontPage)
	enum { IDD = IDD_DIALOG_FRONT_PAGE };
	CEdit	m_edt_Page;
	CListExcelFrontPage	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocTempExcelFrontPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocTempExcelFrontPage)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPEXCELFRONTPAGE_H__D4206BB8_0A02_4213_BC43_5D2064A3AF1F__INCLUDED_)
