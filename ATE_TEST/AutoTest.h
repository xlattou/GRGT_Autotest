#if !defined(AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_)
#define AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoTest.h : header file
//

#include "Xml_UUTKind.h"
#include "File_UUTInfo.h"
#include "Xml_UUTInfo.h"
#include "Xml_Bll_UUTPointInfo.h"
#include "Xml_Bll_PointVarInfo.h"
#include "Xml_Bll_FaultInfo.h"
#include "Xml_Bll_FaultReason.h"
#include "PathOperate.h"
#include "LoadTP.h"
#include "TestEnd.h"
#include "ShareMemory.h"
#include "Xml_Bll_UUTItem_Tem.h"
#include "Xml_Bll_UUTItem.h"
#include "FileOpe_Excel.h"
#include "tb_TestInfo.h"
#include "tb_TestResult.h"
#include "Frame_TestConnect.h"
#include "Report.h"
#include "Ini.h"
#include "Frame_FAIL.h"
#include "SetInstrAddress.h"
#include "afxwin.h"

#define WM_MYUPDATEDATA WM_USER+1000
/////////////////////////////////////////////////////////////////////////////
// CAutoTest dialog
class CAutoTest : public CDialog
{
// Construction
	DECLARE_EASYSIZE
public:
	void StringToArray(CString strInput,CString key,vector<CString>*stringArray);// �ַ���ת�����ַ������飬��Ҫ��","��Ϊ�ָ���
	CString ConvertTickToTime(int intTickCount); //��ʱ
	void UpdateInsList();  //���������б�
	void UpdateSoluList(CString strSoluName); //���½��������
	void UpdateFirstPaper(); //������ҳ���һЩֵ
	int SaveTestResultToAccess(vector<stucTestResult> vTestResult,int intTestInfoID);//���㸴���ʹ�ã� ���н���Ĳ������ݽ��б���
	int SaveTestInfoToAccess(CString strResult,CString strConclusion,int m_intIDTemp); //���Խ��������ACCESS
	void UpdateModuleList(CString strTemplete);  //ˢ�²���ģ���б�
	void UpdateListBox(int mark);  //���²���������ʾ���ı�����������Թ���
	void UpdateListView();  //���²����б������Ŀ
	BOOL Aduge(CString strResult,CString strUpper,CString strLower); //�жϽ��ֵ
	void UpdateControl(int intStatus); //���¿ؼ�״̬
	LRESULT OnUpdateMyData(WPARAM wParam,LPARAM lParam);
    //UINT ProgTest(LPVOID lpParam);
	HTREEITEM m_hItem_Pre; //���ؼ��ͺ�ѡ���־λ

	void InitListView();  //��ʼ�������б�ؼ�
	void UpdateTestInfo();  //ˢ�»�����Ϣ��
	void InitTreeList();  //��ʼ���豸���б�
	CAutoTest(CWnd* pParent = NULL);   // standard constructor
	CImageList m_imageList;
	CImageList m_imageListSmall;  //����������ͨ״̬ͼƬ
	ShareMemory m_ShareMem; //���͵���ʾ�����ݣ���󲻳���255�ֽ�
	CString m_strShare;

	CXml_UUTKind m_xml_Kind;  //UUTKind.xml�л�ȡ�����б�
	CFile_UUTInfo m_file_UUTInfo; //��ȡģ���ļ��б�
	CXml_UUTInfo m_bll_UUTInfo; //uut.xml�л�����Ϣ������
	CXml_Bll_UUTPointInfo m_bll_UUTPointInfo;  //document/tem.xml�жԲ��Ե���Ϣ�Ĵ�����
	CXml_Bll_PointVarInfo m_bll_UUTPointVar;  //Document/templete.xml�жԲ��Ե�����Ĵ�����
//	CXml_Bll_FaultInfo m_bll_faultInfo;  //������Ϣ�������ò���
//	CXml_Bll_FaultReason m_bll_faultReason; //����ԭ�򣬱����ò���
	CXml_Bll_UUTItem_Tem m_bll_UUTITem_tem; //document/tem.xml�жԲ�����Ŀ��Ϣ�Ĵ�����
	CXml_Bll_UUTItem m_bll_UUTItem; //TestConfig/uut.xml����Ŀ������Ϣ
	Ctb_TestInfo m_bll_TestInfo; //���Խ����Ϣ�����ݿ�
	Ctb_TestResult m_bll_TestResult; //���Խ����Ϣ�����ݿ�
	CIni  m_iniOpe;

	CString m_strUpper,m_strLower,m_strUnit,m_strResult;
	


	vector<TestItemState> m_vItemState;  //��Ŀ״̬��Ϣ�б�
	vector<CString> m_vKeyList; //������Ŀ�ؼ����б����ڴ洢�����б��еĹؼ���key������ʱ������Ŀ�ؼ��֣����Ҳ�����Lua
	vector<CString> m_vItemName; //������Ŀ����
	vector<stucTestResult> m_vTestResult;  //���Խ���б�
	vector<BOOL> m_listVCheckState; //��¼���Ե�ѡ��״̬


	CPathOperate m_pathOpe;
	CString m_strThreadKind;  //������������ñ�
	CString m_strThreadModel; //�ͺţ���Agilent 34401A
	CString m_strTem;
	BOOL m_isStop;
	int m_intTestLine;  //������
	int m_intTestSerial; //���������
	BOOL m_isTestEnd;
	CBrush m_brush;
	CString m_strStartPath;
	CString m_strConclusion;
	CString m_strSoluName; //��������ļ�������


	CString m_strConnectPic;  //��������ͼ
	CString m_strDescription_Conn; //������ʾ
	CString m_strItemName; //������Ŀ����
	CString m_strTestMark; //������Ŀ��ʾ
	int m_intPointID;
	int m_intPotCount;
	BOOL m_isPotCheck;

	int m_intTimeTick; //ʱ�������
	int m_intRetestMark;
	CString m_strResultIndicate; //������ʾ�Ĳ��Խ��
	bool m_bIgnoreCurrentItem;				 //���Ե�ǰ������Ŀ��־λ


// Dialog Data
	//{{AFX_DATA(CAutoTest)
	enum { IDD = IDD_AUTOTEST };
	CButton	m_calibration_All;
	CListCtrl	m_list_Ins;//�����豸�б�
	CComboBox	m_cb_Solution;//����
	CComboBox	m_cbb_DuTime;//��Ч��
	CEdit	m_edit_List;//��������
	CButton	m_check_All;//��������ȫѡ
	CProgressCtrl	m_progress_test;//���Խ�����ʾ
	CComboBox	m_cbModule; //����ģ����
	CListBox	m_listBox_Status;
	CListCtrl	m_List_Result; //���Խ��
	CTreeCtrl	m_tree_tps;//���Բ�Ʒ�б�
	CString	m_strManu;//����
	CString	m_strModel;//�ͺ�
	CString	m_strName;//����
	CString	m_strNumber;//���
	CString	m_edit_Progress;//���Խ�����ֵ��ʾ
	CString	m_strCustomer;//ί�з�
	CString	m_strNumber_Mana;//�����
	CString	m_strTemperature;//�¶�
	CString	m_strHumity;//ʪ��
	CString	m_strAddress_Customer;//�ͻ���ַ
	CTime	m_DateTime;//����ʱ��
	int		m_intTestStation;//���Եص�
	int		m_intInsUse;//��;
	CString	m_strTestTime;//����ʱ��
	CString	m_strElapseTime;//ʣ��ʱ��
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoTest)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult);//�����豸ѡ�����������
	afx_msg void OnPaint();
	afx_msg void OnButtonTest(); //���԰�ťѡ��
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);//��ȡ�����б��еĽ��ֵ�����ж�
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnItemdblclickListResult(NMHDR* pNMHDR, LRESULT* pResult);//˫��ת����������ѡ��״̬
	afx_msg void OnDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusEditNumber();
	afx_msg void OnKillfocusEditNumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonTestset();  //�豸����
	afx_msg void OnSelchangeComboModule();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonReport();
	afx_msg void OnCheckAll();
	afx_msg void OnButtonReTest();
	afx_msg void OnSelchangeComboSolution();
	afx_msg void OnStaticNum();
	afx_msg void OnButtonGetsn(); //��ȡSN��
	afx_msg void OnButtonInstrstate();
	afx_msg void OnCalibrationAll();
	afx_msg void OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_TestButton;
	afx_msg void OnButtonStop();
	CEdit m_Num;
	CEdit m_ManageNum;
	CComboBox m_TestAddress;
	CButton m_GetSN;
	CString m_IP;
	CString m_CH;
	CString m_VSG;
	CString m_ROUT;
};
DWORD WINAPI ProgTest(CAutoTest *p);




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOTEST_H__FD71D746_179D_4607_95BB_849DC45BEC41__INCLUDED_)


