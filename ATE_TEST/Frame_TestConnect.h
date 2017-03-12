#if !defined(AFX_FRAME_TESTCONNECT_H__B089E58B_2AF4_4C05_BDD6_F7D1CE5B8A62__INCLUDED_)
#define AFX_FRAME_TESTCONNECT_H__B089E58B_2AF4_4C05_BDD6_F7D1CE5B8A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Frame_TestConnect.h : header file
//
//#include "NewPic.h"
//#include "cv.h"
//#include "highgui.h"
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CFrame_TestConnect dialog

class CFrame_TestConnect : public CDialog
{
// Construction
public:
	CFrame_TestConnect(CWnd* pParent = NULL);   // standard constructor
	CFrame_TestConnect(CString strFilePath,CString strItemName,CString strDescription,CWnd* pParent = NULL); 
	CString m_strFilePath; //图片路径
	CString m_strItemName; //项目名称
	vector<CString> m_vDescription; //连接操作说明
	CString m_strDescription; //连接说明字符串
	bool m_Quit;

//	CNewPic m_newPic;
	bool    m_bIgnoreItem;

	HBITMAP LoadPicture(CString mFile, int THUMWIDTH, int THUMHEIGHT);

// Dialog Data
	//{{AFX_DATA(CFrame_TestConnect)
	enum { IDD = IDD_DIALOG_CONNECT };
	CStatic	m_Pic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrame_TestConnect)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrame_TestConnect)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnButtonOk();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonConnectIgnoreItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuitButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAME_TESTCONNECT_H__B089E58B_2AF4_4C05_BDD6_F7D1CE5B8A62__INCLUDED_)
