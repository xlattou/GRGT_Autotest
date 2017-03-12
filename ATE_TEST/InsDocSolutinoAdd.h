#if !defined(AFX_INSDOCSOLUTINOADD_H__8B754729_4BB5_4828_811A_354E9D1A8333__INCLUDED_)
#define AFX_INSDOCSOLUTINOADD_H__8B754729_4BB5_4828_811A_354E9D1A8333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocSolutinoAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutinoAdd dialog

class CInsDocSolutinoAdd : public CDialog
{
// Construction
public:
	CInsDocSolutinoAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocSolutinoAdd)
	enum { IDD = IDD_DIALOG_SOLUTION_LIST };
	CListCtrl	m_List;
	CEdit	m_edt1;
	CButton	m_check;
	//}}AFX_DATA

	CString m_strKind;
	CString m_strModel;
	CString m_strTemplate;
	CString m_strRefTempPath;
	CString m_strReferModel;
	CStringArray m_strPathArray;//参考型号的路径
	CStringArray m_strModelArray;
	BOOL    m_bRefer; //是否参照其他

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocSolutinoAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocSolutinoAdd)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCSOLUTINOADD_H__8B754729_4BB5_4828_811A_354E9D1A8333__INCLUDED_)
