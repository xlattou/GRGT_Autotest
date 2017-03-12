#if !defined(AFX_INSDOCBASIC_H__3C3E04C0_5904_4292_8AC5_FFEB4144B90E__INCLUDED_)
#define AFX_INSDOCBASIC_H__3C3E04C0_5904_4292_8AC5_FFEB4144B90E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListInsBasic.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocBasic dialog

class CInsDocBasic : public CDialog
{
// Construction
public:
	CInsDocBasic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocBasic)
	enum { IDD = IDD_INSDOC_BASIC };
	CButton	m_btn_Del_TestItem;
	CButton	m_btn_Add_TestItem;
	CButton	m_group_Test_Item;
	CButton	m_btn_SaveTestItem;
	CEdit	m_edt_Factory;
	CEdit	m_edt_Model;
	CEdit	m_edt_Name;
	CListInsBasic	m_list_TestItem;
	CStatic	m_stc_TestItem;
	CStatic	m_stc_Factory;
	CStatic	m_stc_Model;
	CStatic	m_stc_Name;
	CButton	m_group_Basic;
	//}}AFX_DATA

	CString m_strKind;//装置类型
	CString m_strModel;//装置名称
	int     m_nSeleteIndex;//列表选中行
	int		m_nUUTItemMax;//测试项目最大Key
	int		m_nUUTItemMax1;
	int 	m_nSaveState;//保存标志位;

	void UpdateBasicInfo(CString strKind,CString strModel);
	void DelTestItem();
	void UpdateSaveState(int nSaveState);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocBasic)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBrush m_brush;
	// Generated message map functions
	//{{AFX_MSG(CInsDocBasic)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclickListTestItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuInsBasicDel();
	afx_msg void OnMenuInsBasicNew();
	afx_msg void OnButtonSaveTestItem();
	afx_msg void OnButtonAddTestItem();
	afx_msg void OnButtonDelTestItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCBASIC_H__3C3E04C0_5904_4292_8AC5_FFEB4144B90E__INCLUDED_)
