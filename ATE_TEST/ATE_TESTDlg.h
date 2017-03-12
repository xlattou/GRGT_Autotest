// ATE_TESTDlg.h : header file
//

#if !defined(AFX_ATE_TESTDLG_H__E47F4E94_45D6_4CBC_8062_7CE1BC61DDBB__INCLUDED_)
#define AFX_ATE_TESTDLG_H__E47F4E94_45D6_4CBC_8062_7CE1BC61DDBB__INCLUDED_

#include "AutoTest.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SetUser.h"
#include "Login.h"
#include "SetResource.h"
#include "NewMenu.h"	// Added by ClassView
#include "InsDocument.h"
#include "ModifyAdvise.h"
#include "NewButton.h"
#include "ShareMemory.h"
#include "System.h"


/////////////////////////////////////////////////////////////////////////////
// CATE_TESTDlg dialog

class CATE_TESTDlg : public CDialog
{
	DECLARE_EASYSIZE   //位置调整宏
// Construction
public:
	void UpDateButton(int intState);
	void DrawButton(CNewButton &newBtn,int BitmapID,int Bitmap2ID,CRect rect,int intBtnID);
	CATE_TESTDlg(CWnd* pParent = NULL);	// standard constructor
	CBrush m_brush;
	CNewButton m_newButton_Test;
	CNewButton m_newButton_Model;
	CNewButton m_newButton_Report;
	CNewButton m_newButton_System;
//	CNewButton m_newButton_Remote;
	CNewButton m_newButton_Moniter;
	CNewButton m_newButton_Help;
	CEdit m_newEdit_Status;
//	CStatic m_newStatic_Status;

	CNewButton m_newButton_Exit;
	CRect m_rect_Test,m_rect_Model,m_rect_Report,m_rect_System,
		/*m_rect_Remote,*/m_rect_Moniter,m_rect_Help,m_rect_Exit;

	CBitmap m_bmp1;
	CBitmap m_bmp2;
	//int m_intMark; //默认标示
	int m_nShowType;//显示模式,0为全屏状态,1为右半屏开发模式
	CRect   rect;


// Dialog Data
	//{{AFX_DATA(CATE_TESTDlg)
	enum { IDD = IDD_ATE_TEST_DIALOG };
//	CStatic	m_static_name;
	CString	m_strAppName;
	CString	m_strStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CATE_TESTDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar m_wndtoolbar;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CATE_TESTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuBack();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMenuSetuser();
	afx_msg void OnMenuSetsource();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMenuitemAutotest();
	afx_msg void OnExit();
	afx_msg void OnManutest();
	afx_msg void OnUutdoc();
	afx_msg void OnAutotest();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnAssistant();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAutoTest dlg_ATest;
	CString m_password;
	CString m_userName;
	HWND dlghand;
	HWND dlghand1;
	CSetUser dlg_SetUser;
	CLogin dlg_Login;  //登陆对话框
	CSetResource dlg_SetResource;
	CInsDocument dlg_InsDoc;
	//CModifyAdvise dlg_ModifyAd;
	CSystem dlg_ModifyAd;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATE_TESTDLG_H__E47F4E94_45D6_4CBC_8062_7CE1BC61DDBB__INCLUDED_)
