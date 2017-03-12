#if !defined(AFX_NEWTEMPNAME_H__4ADC7A77_6315_4D66_B498_F5BF99591A24__INCLUDED_)
#define AFX_NEWTEMPNAME_H__4ADC7A77_6315_4D66_B498_F5BF99591A24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewTempName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewTempName dialog

class CNewTempName : public CDialog
{
// Construction
public:
	CNewTempName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewTempName)
	enum { IDD = IDD_DIALOG2 };
	CString	m_newTempName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTempName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewTempName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTEMPNAME_H__4ADC7A77_6315_4D66_B498_F5BF99591A24__INCLUDED_)
