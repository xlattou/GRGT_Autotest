#if !defined(AFX_ITEMEDIT_H__601BABD0_ACDE_489C_AA58_0E2902008684__INCLUDED_)
#define AFX_ITEMEDIT_H__601BABD0_ACDE_489C_AA58_0E2902008684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CItemEdit window

class CItemEdit : public CEdit
{
	// Construction
public:
	CItemEdit();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemEdit)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CItemEdit();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CItemEdit)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iXPos; 
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMEDIT_H__601BABD0_ACDE_489C_AA58_0E2902008684__INCLUDED_)
