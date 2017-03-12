#if !defined(AFX_INSDOCUMENT_H__29C15C02_6130_4CF9_AEAF_7B75A81CA5F1__INCLUDED_)
#define AFX_INSDOCUMENT_H__29C15C02_6130_4CF9_AEAF_7B75A81CA5F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsDocument.h : header file
//
#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
#include "Xml_UUTInfo.h"
#include "Xml_Bll_UUTItem.h"
#include "Frame_UUTBasicInfo.h"
#include "InsDocBasic.h"
#include "InsDocTemplete.h"
#include "InsDocSolution.h"


/////////////////////////////////////////////////////////////////////////////
// CInsDocument dialog

class CInsDocument : public CDialog
{
// Construction
//	DECLARE_EASYSIZE
public:
	void InitTreeList();
	CBrush m_brush;
	CInsDocument(CWnd* pParent = NULL);   // standard constructor
	CXml_UUTKind m_bll_UUTKind;
	CFile_UUTInfo m_UUTInfo;
	CImageList m_imageList;
	CXml_UUTInfo m_Xml_UUTInfo;
	CXml_Bll_UUTItem m_bll_UUTItem;

	int				m_CurSelTab; //tab页面标示符
	CInsDocBasic	m_dlg_Basic;	//装置基本信息页
	CInsDocTemplete m_dlg_Templete;	//测试模板页
	CInsDocSolution m_dlg_Solution;	//解决方案页
	HBITMAP			m_bitmap[6];

	CString			m_strThreadKind;  //类别，例数字万用表
	CString			m_strThreadModel; //型号，例Agilent 34401A

	void ChildWindowShow(int nIChild);
	void changeXMLRootName(CString strPath, CString strRootName);//修改路径下所有XML文件的根节点名字

// Dialog Data
	//{{AFX_DATA(CInsDocument)
	enum { IDD = IDD_INSDOC };
	CStatic	m_pic_Templete;
	CStatic	m_pic_Solution;
	CStatic	m_pic_Basic;
	CTreeCtrl	m_tree_tps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocument)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreatModelKind(CString strKindName, CString sEngineFilePath);//创建装置类型
	void CreatModel(CString strFactory, CString strModelType, CString strReferModelPath, bool bSameKind);//创建装置类型

	// Generated message map functions
	//{{AFX_MSG(CInsDocument)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPicBasic();
	afx_msg void OnPicTemplete();
	afx_msg void OnPicSolution();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddKind();
	afx_msg void OnAddModel();
	afx_msg void OnDelKind();
	afx_msg void OnDelModel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCUMENT_H__29C15C02_6130_4CF9_AEAF_7B75A81CA5F1__INCLUDED_)
