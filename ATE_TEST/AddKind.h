#if !defined(AFX_ADDKIND_H__850D7DB2_37A2_4D07_9B20_458540B62A36__INCLUDED_)
#define AFX_ADDKIND_H__850D7DB2_37A2_4D07_9B20_458540B62A36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddKind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// 装置类型添加方式的选择，按有引擎与无引擎添加

class CAddKind : public CDialog
{
// Construction
public:
	CAddKind(CWnd* pParent = NULL);   // standard constructor
	int m_nHasEngine;
	CString m_strTitle;
	CString m_strHasEngine;

// Dialog Data
	//{{AFX_DATA(CAddKind)
	enum { IDD = IDD_DIALOG_ADD_KIND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddKind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddKind)
	afx_msg void OnButtonHasEngine();
	afx_msg void OnButtonHasNoEngine();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDKIND_H__850D7DB2_37A2_4D07_9B20_458540B62A36__INCLUDED_)
