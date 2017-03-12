#if !defined(AFX_PRODUCTREGISTER_H__CA6D3093_71A9_49C9_AC8A_0DC6F9D8596C__INCLUDED_)
#define AFX_PRODUCTREGISTER_H__CA6D3093_71A9_49C9_AC8A_0DC6F9D8596C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProductRegister.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProductRegister dialog

class CProductRegister : public CDialog
{
// Construction
public:
	CProductRegister(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProductRegister)
	enum { IDD = IDD_DIALOG_REGIST };
	CStatic	m_pic_Reg_Title;
	CEdit	m_edt_Request;
	CEdit	m_edt_Register;
	//}}AFX_DATA
	CString m_strDLLPath;
	CBrush  m_brush;
	CString m_strRegister;
	CString m_strRegister1;
	CString m_strRequest;

	CString m_strKey[2];//加解密密匙
	CString m_strCharacter;//版本特征码

	CString GetCPUID();
	CString GetDiskId();
	void creatDLL();
	void readKey(char* charKey);
	void writeKey(char* charKey, int nLength);
	BOOL compareKey();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProductRegister)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProductRegister)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCTREGISTER_H__CA6D3093_71A9_49C9_AC8A_0DC6F9D8596C__INCLUDED_)
