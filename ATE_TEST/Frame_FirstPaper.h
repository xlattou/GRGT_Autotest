#if !defined(AFX_FRAME_FIRSTPAPER_H__CACE942C_2140_42B5_8F0F_295B9D17E9E9__INCLUDED_)
#define AFX_FRAME_FIRSTPAPER_H__CACE942C_2140_42B5_8F0F_295B9D17E9E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Frame_FirstPaper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrame_FirstPaper dialog

class CFrame_FirstPaper : public CDialog
{
// Construction
public:
	CFrame_FirstPaper(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrame_FirstPaper)
	enum { IDD = IDD_TEM_FIRST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrame_FirstPaper)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrame_FirstPaper)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAME_FIRSTPAPER_H__CACE942C_2140_42B5_8F0F_295B9D17E9E9__INCLUDED_)
