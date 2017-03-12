#if !defined(AFX_MYOLECONTROLCONTAINER_H__C480D9FB_E3FE_4E52_A7DB_B9B568A17DB8__INCLUDED_)
#define AFX_MYOLECONTROLCONTAINER_H__C480D9FB_E3FE_4E52_A7DB_B9B568A17DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <..\MFC\SRC\occimpl.h>
/////////////////////////////////////////////////////////////////////////////
// CMyOleControlContainer document

class CMyOleControlContainer : public COleControlContainer
{
public:
	CMyOleControlContainer(CWnd*  pWnd);	// protected constructor used by dynamic creation
	virtual ~CMyOleControlContainer();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOleControlContainer)
	public:
	virtual void OnUIActivate(COleControlSite* pSite);
	protected:
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyOleControlContainer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYOLECONTROLCONTAINER_H__C480D9FB_E3FE_4E52_A7DB_B9B568A17DB8__INCLUDED_)
