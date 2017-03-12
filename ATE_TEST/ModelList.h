#if !defined(AFX_MODELLIST_H__7F6C6ED6_01B8_47FF_9F96_AD8114D38601__INCLUDED_)
#define AFX_MODELLIST_H__7F6C6ED6_01B8_47FF_9F96_AD8114D38601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModelList dialog

class CModelList : public CDialog
{
// Construction
public:
	CModelList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModelList)
	enum { IDD = IDD_DIALOG_MODEL_LIST };
	CListCtrl	m_list_Model;
	//}}AFX_DATA
	CString m_strKind;
	bool    m_bReferSameKind;
	CString m_strReferModelPath;
	CStringArray m_strPathArray;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModelList)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELLIST_H__7F6C6ED6_01B8_47FF_9F96_AD8114D38601__INCLUDED_)
