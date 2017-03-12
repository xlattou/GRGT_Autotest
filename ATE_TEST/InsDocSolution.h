#if !defined(AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_)
#define AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListSolutionFun.h"
#include "ListInsSolution.h"

#include "Xml_UUTInfoSet.h"

/////////////////////////////////////////////////////////////////////////////
// CInsDocSolution dialog
using namespace std;

enum EnumWindowShow{UUT, LUA};

class CInsDocSolution : public CDialog
{
// Construction
public:
	CInsDocSolution(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsDocSolution)
	enum { IDD = IDD_INSDOC_SOLUTION };
	CStatic	m_stc_Lua_Pic;
	CButton	m_group_Solution;
	CStatic	m_pic_UUT;
	CStatic	m_pic_Lua;
	CButton	m_btn_Solution_Change;
	CButton	m_btn_Edt_Lua_Pic;
	CButton	m_btn_Del_Solution;
	CStatic	m_stc_Drive_Name_UUT;
	CComboBox	m_com_Drive_UUT;
	CButton	m_btn_Drive_Name_UUT;
	CEdit	m_edt_UUT_Name;
	CButton	m_btn_Save_UUT;
	CButton	m_btn_Save_Ins;
	CButton	m_btn_Save_Lua;
	CStatic	m_stc_Driver_Name_Ins;
	CButton	m_btn_Driver_Name_Ins;
	CComboBox	m_com_Drive_Name;
	CStatic	m_stc_UUT_Addr;
	CStatic	m_stc_Ins_Address;
	CComboBox	m_com_Ins;
	CEdit	m_edt_Ins_Address;
	CEdit	m_edt_UUT_Address;
	CButton	m_group_Ins;
	CButton	m_group_UUT;
	CButton	m_btn_Add_Solution;
	CComboBox	m_com_Solution;
	CListSolutionFun	m_list_Ins;
	CListInsSolution	m_list_Lua;
	CListSolutionFun	m_list_UUT;
	CStatic	m_stc_Ins;
	CStatic	m_stc_UUT;
	//}}AFX_DATA

	
	CArray<UUTItemInfo, UUTItemInfo> m_testItem;//���пɲ�����Ŀ
	CString m_strKind;				//װ������
	CString m_strModel;				//װ������
	CString m_strSolution;			//���������
	CString m_strUUInfoPath;		//������Ϣ���·��
	CString m_strEngineINIPath;		//���������ļ�·��		
	CString	m_strSoluDirPath;		//��������ļ���·��
	CString m_strTestConfigINIPath;	//����������������ļ�·��
	CString m_strDllName_UUT;		//UUT��dll����
	CStringArray m_strFuncArray_UUT;//UUT��dll���ú���
	CString m_strDllName_Ins;		//�����豸�ĵ�dll����
	CStringArray m_strFuncArray_Ins;//��ǰ�����豸��dll���ú���
	CStringArray m_srtInsArray;
	EnumWindowShow m_WindowShow;//��ʾ����_�����豸 || �ű�_����ͼ �����־
	int 	m_nChangeState;//�޸ı�־λ;

	void initAll(CString strKind, CString strModel);
	void initComSolution();			//��ʼ����Ͽ�
	void GetSolution();				//��ý������
	void initUUT_InsName_InsDriver();//��ʼ���������豸������Ͽ�, ���溯��, �������豸��Ͽ�, �����豸������Ͽ�
	void initUUTList();				//��ʼ���������豸�������ú���
	void initIns();					//��ʼ�������豸���溯��
	void initInsList();				//��ʼ�������豸�������ú���
	void initTestFunc();			//��ʼ��Lua�б�Ĳ��Թ�����
	void initLua_ConnectPic();		//��ʼ��Lua�б�Ľű�������ͼ
	void CopyDriver(int nType);		//��������,0ΪUUT����, 1Ϊ�����豸����
	void UUT_LUA_SHOW(int nIUUt_Lua); //��ʾ����_�����豸 OR �ű�_����ͼ
	void UpdateChangeState(int nChangeState);//�������пؼ���״̬
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsDocSolution)
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
	//{{AFX_MSG(CInsDocSolution)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonAddTestsolution();
	afx_msg void OnSelchangeComboSolutionInsdoc();
	afx_msg void OnButtonDriverName();
	afx_msg void OnButtonSaveUut();
	afx_msg void OnButtonDelTestsolution();
	afx_msg void OnSelchangeComboDriverName2();
	afx_msg void OnSelchangeComboIns();
	afx_msg void OnSelchangeComboDriverName();
	afx_msg void OnButtonDriverName2();
	afx_msg void OnButtonSaveIns();
	afx_msg void OnButtonSaveSolution();
	afx_msg void OnButtonEdtLuaPic();
	afx_msg void OnPicUut();
	afx_msg void OnPicLua();
	afx_msg void OnButtonSolutionChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSDOCSOLUTION_H__547084A6_9D2A_4D2F_9B35_F69061FAB99C__INCLUDED_)
