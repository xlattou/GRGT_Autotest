#if !defined(AFX_INSDOCTEMPLATETESTCONDITION_H__AD7B25C4_DEAE_43D4_ABE0_0045B6AB1430__INCLUDED_)
#define AFX_INSDOCTEMPLATETESTCONDITION_H__AD7B25C4_DEAE_43D4_ABE0_0045B6AB1430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocTemplateTestCondition.h : header file
//
#include "Xml_PointVarSet.h"
#include <afxtempl.h>
#include "ListInsTempCondition.h"
/////////////////////////////////////////////////////////////////////////////
// InsDocTemplateTestCondition dialog

class InsDocTemplateTestCondition : public CDialog
{
// Construction
public:
	InsDocTemplateTestCondition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InsDocTemplateTestCondition)
	enum { IDD = IDD_DIALOG_TEMPLATE_TEST_CONDITION };
	CListInsTempCondition	m_List;
	//}}AFX_DATA


	CArray<PointVarSet, PointVarSet> m_VarSet;
	bool m_bChanged;//是否修改成功标志
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InsDocTemplateTestCondition)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InsDocTemplateTestCondition)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMoveup();
	afx_msg void OnButtonMovedown();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPLATETESTCONDITION_H__AD7B25C4_DEAE_43D4_ABE0_0045B6AB1430__INCLUDED_)
