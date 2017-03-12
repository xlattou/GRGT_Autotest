#if !defined(AFX_SETINS_H__BAC73A62_F8D0_44AC_BA6A_9C3CF5D248B7__INCLUDED_)
#define AFX_SETINS_H__BAC73A62_F8D0_44AC_BA6A_9C3CF5D248B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetIns.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetIns dialog

class CSetIns : public CDialog
{
// Construction
public:
	CString m_strDriveName;
	int m_intNodeID;
	int m_intMark;
	CSetIns(int intMark_Control,int intNodeID,CWnd* pParent=NULL);
	CSetIns(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetIns)
	enum { IDD = IDD_DIALOG_INSSET };
	CComboBox	m_Cb_InsKind;
	CComboBox	m_Cb_InsDriver;
	CString	m_strAddress;
	CString	m_strChann;
	CString	m_strModel;
	CString	m_strInsName;
	CString	m_strManu;
	CString	m_strSNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetIns)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetIns)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETINS_H__BAC73A62_F8D0_44AC_BA6A_9C3CF5D248B7__INCLUDED_)
