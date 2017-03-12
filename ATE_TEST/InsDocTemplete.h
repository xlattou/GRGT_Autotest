#if !defined(AFX_INSDOCTEMPLETE_H__7645B308_3B8C_400B_9AB2_CF83945054E6__INCLUDED_)
#define AFX_INSDOCTEMPLETE_H__7645B308_3B8C_400B_9AB2_CF83945054E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Xml_UUTItemSet.h"
#include "Xml_UUTInfoSet.h"
#include "ListInsBasic.h"
#include "ListInstTemplate.h"
#include "ListInsDocSolution.h"
#include "InsDocTempExcel.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocTemplete dialog

class CInsDocTemplete : public CDialog
{
// Construction
public:
	CInsDocTemplete(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocTemplete)
	enum { IDD = IDD_INSDOC_TEMPLETE };
	CButton	m_btn_Change_Excel;
	CButton	m_btn_Excel_Front_Page;
	CEdit	m_edt_Explain;
	CButton	m_group_Template;
	CButton	m_btn_Del_Solution;
	CButton	m_btn_Add_Solution;
	CButton	m_group_Solution;
	CButton	m_btn_Change_Template;
	CButton	m_btn_Show_Excel;
	CButton	m_btn_Save_Template;
	CButton	m_btn_Save_Solution;
	CButton	m_btn_Del_Template;
	CStatic	m_stc_Solution_in_Templete;
	CListInsDocSolution	m_list_Solution_in_Templete;
	CComboBox	m_com_Templete;
	CButton	m_btn_add_Templete;
	CListInstTemplate	m_list_Templete;
	//}}AFX_DATA

	CInsDocTempExcel m_Excel;
	CString m_strKind;//װ������
	CString m_strModel;//װ������
	CString m_strTemplete;//ģ����	
	CString	m_strTempDirPath; //ģ���ļ���·��
	CArray<UUTItemInfo, UUTItemInfo> m_testItem;//���пɲ�����Ŀ
	int m_nListSelectItem; //ģ���б�ѡ���к�
	int 	m_nChangeState;//�޸ı�־λ;

	vector<UUTItemSet> m_vUUTItem;//����ģ���б�
	CArray<TestPointSet, TestPointSet> m_CopytestSet;

	void UpdataTempleteCom(CString strKind, CString strModel);
	void UpdataTestTempleteList(CString strTemplete);
	void UpdataTestSolutionList(CString strTemplete);
	void changeXMLRootName(CString strXMLFile, CString strRootName);//�޸�XML�ļ����ڵ�
	void AddNewItem(int nTestItem, int nListItem);//�����µĲ�����Ŀ(������Ŀ���, �б���к�)
	void SetTestDitional(int nTestItem);//���ò�������
	void ChangeItem(int nItem, int nSubItem);//�޸Ĳ��Բ����ڵĲ���
	void ReOrderNumber();//�������
	void ReOrderNumber1();//�������
	void UpdateChangeState(int nChangeState);//�������пؼ���״̬
	void OnCusMenuTempleteDel();
	void FillTestResult(int nRow);
	bool CopyTestPointSet(int nILineIndex, TestPointSet* pNew);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocTemplete)
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
	//{{AFX_MSG(CInsDocTemplete)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboTempleteInsdoc();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDblclkListResultInsdoc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAddTestmodel();
	afx_msg void OnButtonDelTestmodel();
	afx_msg void OnMenuTempleteAdd();
	afx_msg void OnMenuTempleteCopy();
	afx_msg void OnMenuTempleteDel();
	afx_msg void OnButtonSaveTemplate();
	afx_msg void OnButtonSaveSolutionInTemplate();
	afx_msg void OnMenuTempleteSolutionDel();
	afx_msg void OnButtonShowExcel();
	afx_msg void OnClickListResultInsdoc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTemplateSolutionAdd();
	afx_msg void OnButtonAddSolutionInTemplate();
	afx_msg void OnButtonDelSolutionInTemplate();
	afx_msg void OnButtonChangeTemplate();
	afx_msg void OnButtonExcelFrontPage();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuTempleteFillItemrow();
	afx_msg void OnMenuTempleteCopyLines();
	afx_msg void OnMenuTempletePast();
	afx_msg void OnButtonChangeExe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCTEMPLETE_H__7645B308_3B8C_400B_9AB2_CF83945054E6__INCLUDED_)
