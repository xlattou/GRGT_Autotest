#if !defined(AFX_SETINSTRADDRESS_H__9833242F_D3D4_4E75_A091_EAE4C3B2A2E8__INCLUDED_)
#define AFX_SETINSTRADDRESS_H__9833242F_D3D4_4E75_A091_EAE4C3B2A2E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetInstrAddress.h : header file
//
#include "Ini.h"
/////////////////////////////////////////////////////////////////////////////
// CSetInstrAddress dialog

class CSetInstrAddress : public CDialog
{
// Construction
public:
	CSetInstrAddress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetInstrAddress)
	enum { IDD = IDD_DIALOG_SETINSTR };
	CListCtrl	m_instrinfo;
	CString	m_instraddress;
	//}}AFX_DATA
    CString strFileIniPath;//�洢���ݹ�����INI�ļ�·��
    CIni m_iniope;//INI�������
	CStringArray m_strArr;//�洢INI�б�
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetInstrAddress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int intLine;//����Ҫ�޸ĵĵ�ַ�����к�

    void InitInstrInfo(); //��ʼ����ʾ�б�
	void UpdateInstrInfo();  //������Ϣ
	// Generated message map functions
	//{{AFX_MSG(CSetInstrAddress)
	afx_msg void OnButtonSaveintr();
	afx_msg void OnButtonQuit();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListInstrinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListInstrinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETINSTRADDRESS_H__9833242F_D3D4_4E75_A091_EAE4C3B2A2E8__INCLUDED_)
