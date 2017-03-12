#if !defined(AFX_INSDOCTEMPADDTEMPLATE_H__F1591DB3_294B_4712_A703_5930E22E3823__INCLUDED_)
#define AFX_INSDOCTEMPADDTEMPLATE_H__F1591DB3_294B_4712_A703_5930E22E3823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocTempAddTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempAddTemplate dialog

class CInsDocTempAddTemplate : public CDialog
{
// Construction
public:
	CInsDocTempAddTemplate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocTempAddTemplate)
	enum { IDD = IDD_DIALOG_TEMPLATE_LIST };
	CButton	m_chk_Refer;
	CListCtrl	m_list;
	//}}AFX_DATA
	CString m_strKind;
	CString m_strModel;
	CString m_strTemplate;
	CString m_strRefTempPath;
	CStringArray m_strPathArray;//参考型号的路径
	CStringArray m_strModelArray;
	BOOL    m_bRefer; //是否参照其他模板
	CString	m_strReferModel; //参照型号


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocTempAddTemplate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocTempAddTemplate)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPADDTEMPLATE_H__F1591DB3_294B_4712_A703_5930E22E3823__INCLUDED_)
