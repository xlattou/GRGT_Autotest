#if !defined(AFX_INSDOCSOLUTIONDEL_H__3A6B201D_D052_4467_8C22_29F351BADDCE__INCLUDED_)
#define AFX_INSDOCSOLUTIONDEL_H__3A6B201D_D052_4467_8C22_29F351BADDCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocSolutionDel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolutionDel dialog

class CInsDocSolutionDel : public CDialog
{
// Construction
public:
	CInsDocSolutionDel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocSolutionDel)
	enum { IDD = IDD_DIALOG_SOLUTION_DEL };
	CListCtrl	m_List;
	//}}AFX_DATA

	CString m_strKind;
	CString m_strModel;
	CStringArray	m_strPathArray;//需要删除的方案列表
	CStringArray	m_strPathArray1;//方案路径列表
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocSolutionDel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocSolutionDel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCSOLUTIONDEL_H__3A6B201D_D052_4467_8C22_29F351BADDCE__INCLUDED_)
