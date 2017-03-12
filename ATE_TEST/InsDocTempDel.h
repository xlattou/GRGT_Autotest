#if !defined(AFX_INSDOCTEMPDEL_H__4DF5ED92_9CBB_4154_AAAC_D083C7679831__INCLUDED_)
#define AFX_INSDOCTEMPDEL_H__4DF5ED92_9CBB_4154_AAAC_D083C7679831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocTempDel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempDel dialog

class CInsDocTempDel : public CDialog
{
// Construction
public:
	CInsDocTempDel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocTempDel)
	enum { IDD = IDD_DIALOG_TEMPLATE_DEL };
	CListCtrl	m_list;
	//}}AFX_DATA
	CString			m_strDir;//模板所在文件夹路径
	CStringArray	m_strTemplateArray;//需要删除的模板列表


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocTempDel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsDocTempDel)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPDEL_H__4DF5ED92_9CBB_4154_AAAC_D083C7679831__INCLUDED_)
