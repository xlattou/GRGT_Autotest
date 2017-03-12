// InsDocTemplete.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTemplete.h"
#include "Xml_Bll_UUTPointInfo.h"
#include "File_UUTInfo.h"
#include "Xml_Bll_UUTItem_Tem.h"
#include "InsDocTempAddTemplate.h"
#include "Xml_UUTInfo.h"
#include "InsDocTempDel.h"
#include "InsDocTemplateTestCondition.h"
#include "FileOpe_Excel.h"
#include "InsDocTempExcelFrontPage.h"
#include "InsTempAutoFillRow.h"

using namespace MyExcel;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocTemplete dialog


CInsDocTemplete::CInsDocTemplete(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocTemplete::IDD, pParent)
{
	m_nListSelectItem = -1;
	m_nChangeState = 0;
}


void CInsDocTemplete::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocTemplete)
	DDX_Control(pDX, IDC_BUTTON_CHANGE_EXE, m_btn_Change_Excel);
	DDX_Control(pDX, IDC_BUTTON_EXCEL_FRONT_PAGE, m_btn_Excel_Front_Page);
	DDX_Control(pDX, IDC_EDIT_EXPLAIN, m_edt_Explain);
	DDX_Control(pDX, IDC_GROUP_TEMPLATE, m_group_Template);
	DDX_Control(pDX, IDC_BUTTON_DEL_SOLUTION_IN_TEMPLATE, m_btn_Del_Solution);
	DDX_Control(pDX, IDC_BUTTON_ADD_SOLUTION_IN_TEMPLATE, m_btn_Add_Solution);
	DDX_Control(pDX, IDC_STATIC_SOLUTION_IN_TEMPLATE, m_group_Solution);
	DDX_Control(pDX, IDC_BUTTON_CHANGE_TEMPLATE, m_btn_Change_Template);
	DDX_Control(pDX, IDC_BUTTON_SHOW_EXE, m_btn_Show_Excel);
	DDX_Control(pDX, IDC_BUTTON_SAVE_TEMPLATE, m_btn_Save_Template);
	DDX_Control(pDX, IDC_BUTTON_SAVE_SOLUTION_IN_TEMPLATE, m_btn_Save_Solution);
	DDX_Control(pDX, IDC_BUTTON_DEL_TESTMODEL, m_btn_Del_Template);
	DDX_Control(pDX, IDC_STATIC_SOLUTION_IN_TEMPLETE, m_stc_Solution_in_Templete);
	DDX_Control(pDX, IDC_LIST_SOLUTION_IN_TEMPLETE, m_list_Solution_in_Templete);
	DDX_Control(pDX, IDC_COMBO_TEMPLETE_INSDOC, m_com_Templete);
	DDX_Control(pDX, IDC_BUTTON_ADD_TESTMODEL, m_btn_add_Templete);
	DDX_Control(pDX, IDC_LIST_RESULT_INSDOC, m_list_Templete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocTemplete, CDialog)
	//{{AFX_MSG_MAP(CInsDocTemplete)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_TEMPLETE_INSDOC, OnSelchangeComboTempleteInsdoc)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT_INSDOC, OnDblclkListResultInsdoc)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TESTMODEL, OnButtonAddTestmodel)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TESTMODEL, OnButtonDelTestmodel)
	ON_COMMAND(ID_MENU_TEMPLETE_ADD, OnMenuTempleteAdd)
	ON_COMMAND(ID_MENU_TEMPLETE_COPY, OnMenuTempleteCopy)
	ON_COMMAND(ID_MENU_TEMPLETE_DEL, OnMenuTempleteDel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TEMPLATE, OnButtonSaveTemplate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SOLUTION_IN_TEMPLATE, OnButtonSaveSolutionInTemplate)
	ON_COMMAND(ID_MENU_TEMPLETE_SOLUTION_DEL, OnMenuTempleteSolutionDel)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_EXE, OnButtonShowExcel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT_INSDOC, OnClickListResultInsdoc)
	ON_COMMAND(IDR_TEMPLATE_SOLUTION_ADD, OnTemplateSolutionAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SOLUTION_IN_TEMPLATE, OnButtonAddSolutionInTemplate)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SOLUTION_IN_TEMPLATE, OnButtonDelSolutionInTemplate)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_TEMPLATE, OnButtonChangeTemplate)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_FRONT_PAGE, OnButtonExcelFrontPage)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_TEMPLETE_FILL_ITEMROW, OnMenuTempleteFillItemrow)
	ON_COMMAND(ID_MENU_TEMPLETE_COPY_LINES, OnMenuTempleteCopyLines)
	ON_COMMAND(ID_MENU_TEMPLETE_PAST, OnMenuTempletePast)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_EXE, OnButtonChangeExe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocTemplete message handlers

BOOL CInsDocTemplete::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);
	m_list_Templete.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_list_Templete.InsertColumn(0, "���", LVCFMT_CENTER, 32);
	m_list_Templete.InsertColumn(1, "������Ŀ", LVCFMT_LEFT, 50);
	m_list_Templete.InsertColumn(2, "������������", LVCFMT_LEFT, 50);
	m_list_Templete.InsertColumn(3, "����ֵ", LVCFMT_CENTER, 80);
	m_list_Templete.InsertColumn(4, "����ֵ", LVCFMT_CENTER, 80);
	m_list_Templete.InsertColumn(5, "��λ", LVCFMT_CENTER, 30);
	m_list_Templete.InsertColumn(6, "���Խ��Excel����", LVCFMT_CENTER, 72);
	m_list_Templete.InsertColumn(7, "��Ŀ�ܽ���Excel����", LVCFMT_CENTER, 72);

	//m_list_Templete.set

	DWORD dwStyle=m_list_Solution_in_Templete.GetExtendedStyle();
	m_list_Solution_in_Templete.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_Solution_in_Templete.InsertColumn(0, "���", LVCFMT_CENTER, 32);
	m_list_Solution_in_Templete.InsertColumn(1, "���Է���", LVCFMT_LEFT, 50);
	m_list_Solution_in_Templete.InsertColumn(2, "˵��", LVCFMT_LEFT, 50);

	m_strTempDirPath = "";

	m_nChangeState = 0;
	UpdateChangeState(m_nChangeState);

	m_edt_Explain.SetWindowText("");

	return TRUE;
}

BOOL CInsDocTemplete::DestroyWindow()
{
	if(IsWindow(m_Excel))
		m_Excel.DestroyWindow();
	m_brush.DeleteObject();
	KillTimer(1);
	return CDialog::DestroyWindow();
}

HBRUSH CInsDocTemplete::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}

	if(nCtlColor==CTLCOLOR_STATIC)
	{ //���ľ�̬��͸��������ɫΪ��ɫ
    	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	return hbr;
}

BOOL CInsDocTemplete::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE)
			return TRUE;
		else if(pMsg->wParam==VK_RETURN)
			return TRUE;
		else if(pMsg->wParam == 'C' || pMsg->wParam == 'c')
			OnMenuTempleteCopyLines();
		else if(pMsg->wParam == 'V' || pMsg->wParam == 'v')
			OnMenuTempletePast();
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CInsDocTemplete::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	int nWide;
	CRect rect1;
	GetClientRect(&rect1);

	nWide = rect1.Width() - 20;
	if(IsWindow(m_com_Templete))
		m_com_Templete.MoveWindow(80, 10, nWide - 290, 100);
	if(IsWindow(m_btn_add_Templete))
		m_btn_add_Templete.MoveWindow(nWide - 205, 10, 50, 26);
	if(IsWindow(m_btn_Del_Template))
		m_btn_Del_Template.MoveWindow(nWide - 150, 10, 50, 26);
	if(IsWindow(m_btn_Change_Template))
		m_btn_Change_Template.MoveWindow(nWide - 90, 10, 105, 26);

	if(IsWindow(m_group_Solution))
		m_group_Solution.MoveWindow(5, 34, nWide + 10, 140);
	if(IsWindow(m_btn_Add_Solution))
		m_btn_Add_Solution.MoveWindow(nWide - 155, 46, 50, 22);	
	if(IsWindow(m_btn_Del_Solution))
		m_btn_Del_Solution.MoveWindow(nWide - 100, 46, 50, 22);	
	if(IsWindow(m_btn_Save_Solution))
		m_btn_Save_Solution.MoveWindow(nWide - 40, 46, 50, 22);
	if(IsWindow(m_list_Solution_in_Templete))
	{
		m_list_Solution_in_Templete.MoveWindow(10, 70, nWide, 100);
		int nWide1 = (nWide - 56) / 3;
		m_list_Solution_in_Templete.SetColumnWidth(1, nWide1);
		m_list_Solution_in_Templete.SetColumnWidth(2, nWide1 * 2);
	}

	int nHeight = rect1.Height() - 173;
	if(IsWindow(m_group_Template))
		m_group_Template.MoveWindow(5, 170, nWide + 10, nHeight);
	if(IsWindow(m_btn_Change_Excel))
		m_btn_Change_Excel.MoveWindow(nWide - 445, 182, 140, 22);
	if(IsWindow(m_btn_Show_Excel))
		m_btn_Show_Excel.MoveWindow(nWide - 300, 182, 140, 22);
	if(IsWindow(m_btn_Excel_Front_Page))
		m_btn_Excel_Front_Page.MoveWindow(nWide - 155, 182, 110, 22);
	if(IsWindow(m_btn_Save_Template))
		m_btn_Save_Template.MoveWindow(nWide - 40, 182, 50, 22);
	if(IsWindow(m_edt_Explain))
		m_edt_Explain.MoveWindow(10, 204, nWide, 18);
	if(IsWindow(m_list_Templete))
	{
		m_list_Templete.MoveWindow(10, 222, nWide, nHeight - 56);
		nWide -= 390;
		nWide /= 2;
		if(nWide < 100)
			nWide = 100;
		m_list_Templete.SetColumnWidth(1,nWide);
		m_list_Templete.SetColumnWidth(2,nWide);
	}
}

void CInsDocTemplete::UpdataTempleteCom(CString strKind, CString strModel)
{
	m_strKind = strKind;
	m_strModel = strModel;
	m_strTemplete = "";
	m_list_Templete.DeleteAllItems();
	m_list_Solution_in_Templete.DeleteAllItems();
	while(m_com_Templete.DeleteString(0)!=CB_ERR);   //ɾ��ģ����Ͽ��е��ַ���

	m_strTempDirPath = "";

	m_nChangeState = 0;
	UpdateChangeState(m_nChangeState);

	m_list_Templete.m_testItem.RemoveAll();

	m_list_Solution_in_Templete.m_strKind = "";
	m_list_Solution_in_Templete.m_strModel = "";
	m_edt_Explain.SetWindowText("");
	if(IsWindow(m_Excel))
		m_Excel.DestroyWindow();

	if(strModel == "")
		return;

	vector<CString> vModuleList;
	CFile_UUTInfo file_uutinfo;
	file_uutinfo.GetModuleList(strKind, strModel, &vModuleList);  //ģ���б�

	for(int i=0;i<vModuleList.size();i++)
	{
		m_com_Templete.AddString(vModuleList[i]);
	}

	if(vModuleList.size() > 0)
	{
		m_com_Templete.SetCurSel(0);
		m_strTemplete = vModuleList[0];
		UpdataTestTempleteList(m_strTemplete);
		UpdataTestSolutionList(m_strTemplete);
	}
	
	CPathOperate paOpe; //·����������
	m_strTempDirPath = paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + m_strKind + "\\TPS\\" + strModel + "\\Document";


	for(int i = 0; i < m_testItem.GetSize(); i++)
		m_list_Templete.m_testItem.Add(m_testItem[i]);
	m_list_Templete.initTestItemCom();

	m_list_Solution_in_Templete.m_strKind = m_strKind;
	m_list_Solution_in_Templete.m_strModel = m_strModel;

	m_nChangeState = 1;
	UpdateChangeState(m_nChangeState);
}
void CInsDocTemplete::UpdataTestTempleteList(CString strTemplete)
{
	try
	{
		TestPointSet stucPointSet;
		vector<TestPointSet> vUUTPoint;
		vector<PointVarSet> vPtVar;

		UUTItemSet stucItemSet;
		CString strtemp, strID, strSetString;
		TiXmlElement* pEle = NULL;
		int intline=0;//���Ե���ų�ʼ��Ϊ0
		bool bInsertID = false; //�Ƿ��Ѿ�������ID��
		m_list_Templete.DeleteAllItems(); //ɾ����������
		m_edt_Explain.SetWindowText("");
		m_edt_Explain.ShowWindow(SW_HIDE);
		m_edt_Explain.ShowWindow(SW_SHOWNORMAL);
//		if(IsWindow(m_Excel))
//			m_Excel.DestroyWindow();

		CXml_Bll_UUTItem_Tem bll_UUTITem_tem;
		m_vUUTItem.clear();//ɾ����������ģ���б�
	    bll_UUTITem_tem.ReadUUTItemList(m_strKind, m_strModel, strTemplete, &m_vUUTItem);//��ȡITEMSET����KEY/CONTROL����Ϣ
		int nI = m_vUUTItem.size();
		bool bInTestItem, bSameType;//������Ŀ�ڿɲ�����Ŀ��, ������Ŀ����Ӧ�ɲ�����Ŀ����������ͬ
		for(int i = nI - 1; i >= 0; i--)
		{
			bInTestItem = false;
			bSameType = true;
			strID = m_vUUTItem[i].m_strKey.Right(m_vUUTItem[i].m_strKey.GetLength() - 3);
			m_vUUTItem[i].m_intID = atoi(strID);
			for(int j = 0; j < m_testItem.GetSize(); j++)
			{
				if(atoi(m_vUUTItem[i].m_strKey.Mid(3)) == m_testItem[j].nKey)
				{
					strtemp = m_vUUTItem[i].m_strMarkName;
					strSetString = m_testItem[j].strTestType;
					if(m_vUUTItem[i].m_strMarkName != m_testItem[j].strTestType)
					{
						m_vUUTItem.erase(m_vUUTItem.begin() + i);
						bSameType = false;
						break;
					}
					bInTestItem = true;
					break;
				}
			}
			if(bSameType && !bInTestItem)
				m_vUUTItem.erase(m_vUUTItem.begin() + i);
		}
		
		CXml_Bll_UUTPointInfo bll_UUTPointInfo;		

		nI = 1;
		for(int i=0;i<m_vUUTItem.size();i++)
		{

			if(m_vUUTItem[i].m_strMarkName=="Control") 
			{
				if(m_vUUTItem[i].m_strKey.Left(3) != "Key")
					continue;

				strID = m_vUUTItem[i].m_strKey.Right(m_vUUTItem[i].m_strKey.GetLength() - 3);
				m_vUUTItem[i].m_intID = atoi(strID);
				strID.Format("%d", nI);
				m_list_Templete.InsertItem(intline,strID,1);  //������Ե�ID
				m_list_Templete.SetItemText(intline,1,m_vUUTItem[i].m_strItemName);  //������Ŀ����
				m_list_Templete.SetItemText(intline,2,"Control");
				intline++;
			}
			else
			{
				if(m_vUUTItem[i].m_strKey.Left(3) != "Key")
					continue;
				m_vUUTItem[i].m_intID = atoi(m_vUUTItem[i].m_strKey.Right(m_vUUTItem[i].m_strKey.GetLength() - 3));
				bll_UUTPointInfo.ReadUUTPointList(bll_UUTITem_tem.m_pNode, m_vUUTItem[i].m_strKey, &vUUTPoint);
				//����KEYֵ�ҵ�����POINT���Ը�vUUTPoint
				//pTestPoint = 
//				m_vUUTItem[i].m_pTestPoint = new TestPointSet;
				bInsertID = false;
				for(int j=0;j<vUUTPoint.size();j++)
				{
					TestPointSet *pNew = new TestPointSet;
					if(pNew == NULL)
						return;

					pNew->m_intID = vUUTPoint[j].m_intID;//�����ṹ��
					pNew->m_strUpper = vUUTPoint[j].m_strUpper;
					pNew->m_strLower = vUUTPoint[j].m_strLower;
					pNew->m_strResultMark = vUUTPoint[j].m_strResultMark;
					pNew->m_strResultUnit = vUUTPoint[j].m_strResultUnit;
					pNew->m_strCol = vUUTPoint[j].m_strCol;
					pNew->m_strLine = vUUTPoint[j].m_strLine;
					pNew->next = NULL;
					pNew->m_VarSet = NULL;

					if(m_vUUTItem[i].m_pTestPoint == NULL)
						m_vUUTItem[i].m_pTestPoint = pNew;
					else
					{
						TestPointSet* pTestPoint = m_vUUTItem[i].m_pTestPoint;
						while(pTestPoint != NULL)
						{
							if (pTestPoint->next == NULL)
							{
								pTestPoint->next = pNew;
								break;
							}
							pTestPoint = pTestPoint->next;
						}
					}

					if(bInsertID)  //�Ѿ�������Ե����
						strID = "";
					else
					{
						strID.Format("%d",nI); //������Ե����
						bInsertID = true;						 //����Ѳ���
					}

					m_list_Templete.InsertItem(intline,strID, 1);
					if(strID != "")
					{
						m_list_Templete.SetItemText(intline,1,m_vUUTItem[i].m_strItemName);  //������Ŀ����
						m_list_Templete.SetItemText(intline, 7, m_vUUTItem[i].m_strResultCol + ":" + m_vUUTItem[i].m_strResultRow);
					}
					pEle = bll_UUTPointInfo.GetPointNode(vUUTPoint[j].m_intID)->ToElement(); //��ȡPOINT�µ�IDֵ

					vPtVar.clear();
					CXml_PointVarSet xml_ptVarSet(pEle);
					xml_ptVarSet.ReadVarList(&vPtVar);

					CString strSetString="";
					PointVarSet* pVar1 = NULL;// = pNew->m_VarSet;
					for(int k = 0; k < vPtVar.size(); k++)
					{
						PointVarSet* pVarSet = new PointVarSet;
						if(pVarSet == NULL)
							return;

						pVarSet->m_intID = vPtVar[k].m_intID;
						pVarSet->m_strLogicName = vPtVar[k].m_strLogicName;
						pVarSet->m_strName = vPtVar[k].m_strName;
						pVarSet->m_strValue = vPtVar[k].m_strValue;
						pVarSet->m_strUnit = vPtVar[k].m_strUnit;
						pVarSet->next = NULL;

						if(pVar1 == NULL)
							pNew->m_VarSet = pVarSet;
						else
							pVar1->next = pVarSet;
						pVar1 = pVarSet;

						strSetString+=pVarSet->m_strName+"=";
						strSetString+=pVarSet->m_strValue;
						strSetString+=pVarSet->m_strUnit+";";
					}
					strSetString=strSetString.Left(strSetString.GetLength()-1);

					m_list_Templete.SetItemText(intline,2,strSetString);
					m_list_Templete.SetItemText(intline,3,vUUTPoint[j].m_strLower);
					m_list_Templete.SetItemText(intline,4,vUUTPoint[j].m_strUpper);
					m_list_Templete.SetItemText(intline,5,vUUTPoint[j].m_strResultUnit);
					CString str1 = vUUTPoint[j].m_strCol + ',';
					CString str2 = vUUTPoint[j].m_strLine + ',';
					CString str3 = "";
					int n1, n2;
					while(str1.Find(',') >= 0 && str2.Find(',') >= 0)
					{
						n1 = str1.Find(',');
						n2 = str2.Find(',');
						str3 += str1.Left(n1) + ":" + str2.Left(n2) + ",";
						str1 = str1.Right(str1.GetLength() - n1 - 1);
						str2 = str2.Right(str2.GetLength() - n2 - 1);
					}
					str3 = str3.Left(str3.GetLength() - 1);
					m_list_Templete.SetItemText(intline, 6, str3);
					intline++;

					vPtVar.clear();
				}
	    		vUUTPoint.clear();
			}
			nI++;
		}
		
		nI = m_vUUTItem.size();
		for(int i = 0; i < nI; i++)
		{
			for(int j = 0; j < i; j++)
			{
				if(m_vUUTItem[i].m_strKey == m_vUUTItem[j].m_strKey)
					AfxMessageBox(m_vUUTItem[i].m_strItemName + " �� " + m_vUUTItem[j].m_strItemName + " Key����ͬ, ��ɾ������һ��!");
			}
			
		}
	}
	catch (char* e)
	{
		MessageBox(e);
	}
}

void CInsDocTemplete::UpdataTestSolutionList(CString strTemplete)
{
	try
	{
		m_list_Solution_in_Templete.DeleteAllItems();

		vector<CString> vSolutionList;
		
		CXml_Bll_UUTItem_Tem bll_UUTITem_tem;
		bll_UUTITem_tem.ReadSolutionList(m_strKind, m_strModel, m_strTemplete, &vSolutionList);
		int intSolSize=0;

		CString str1;
		
		m_list_Solution_in_Templete.DeleteAllItems();
		for(int i = 0; i < vSolutionList.size(); i++)
		{
			str1.Format("%d", i + 1);
			m_list_Solution_in_Templete.InsertItem(i, str1);
			m_list_Solution_in_Templete.SetItemText(i, 1, vSolutionList[i]);
		}
	}	
	catch (char* e)
	{
		MessageBox(e);
	}
}

void CInsDocTemplete::OnSelchangeComboTempleteInsdoc() 
{
	int nI = m_com_Templete.GetCurSel();
	m_com_Templete.GetLBText(nI, m_strTemplete);
	UpdataTestTempleteList(m_strTemplete);
	UpdataTestSolutionList(m_strTemplete);
}

void CInsDocTemplete::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if(m_strTemplete == "")
		return;
	if(m_nChangeState != 2)
		return;
	CListCtrl* pWndList = (CListCtrl*) &m_list_Templete;
	CListCtrl* pWndList1 = (CListCtrl*) &m_list_Solution_in_Templete;
	ASSERT_VALID(pWndList);

	m_nListSelectItem = -1;
	if (pWnd == pWndList)
	{
		int nMenuIndex;
		pWndList->ScreenToClient(&point); 
		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;    
		int nItem = pWndList->SubItemHitTest(&lvinfo);
		if(nItem != -1)
			m_nListSelectItem = lvinfo.iItem;
		pWndList->SetFocus();

		if(m_nListSelectItem < 0)
			nMenuIndex = 3;//�հ���
		else if(m_list_Templete.GetItemText(m_nListSelectItem, 0) != "")
		{
			if(m_list_Templete.GetItemText(m_nListSelectItem, 2) == "Control")
				nMenuIndex = 2;//Control��
			else
				nMenuIndex = 0;//������Ŀ����
		}
		else
			nMenuIndex = 1;//������Ŀ������
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_TEST_TEMPLETE));

		CMenu* pPopup = menu.GetSubMenu(nMenuIndex);
		ASSERT(pPopup != NULL);

		pWndList->ClientToScreen(&point);

	//	pPopup->ModifyMenu(ID_MENU_TEMPLETE_CHANGE,MF_BYCOMMAND,ID_MENU_TEMPLETE_CHANGE, str1);

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if(pWnd == pWndList1)
	{
		pWndList1->ScreenToClient(&point); 
		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;    
		int nItem = pWndList1->SubItemHitTest(&lvinfo);
		if(nItem != -1)
			m_nListSelectItem = lvinfo.iItem;
		pWndList1->SetFocus();

		int nMenuIndex = 0;
		if(m_nListSelectItem < 0)
			nMenuIndex = 1;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_TEMPLATE_SOLUTION));

		CMenu* pPopup = menu.GetSubMenu(nMenuIndex);
		ASSERT(pPopup != NULL);

		pWndList1->ClientToScreen(&point);

	//	pPopup->ModifyMenu(ID_MENU_TEMPLETE_CHANGE,MF_BYCOMMAND,ID_MENU_TEMPLETE_CHANGE, str1);

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else
		return;
}

void CInsDocTemplete::OnDblclkListResultInsdoc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CInsDocTemplete::OnButtonAddTestmodel() 
{
	CInsDocTempAddTemplate addTempalate;
	addTempalate.m_strKind = m_strKind;
	addTempalate.m_strModel = m_strModel;
	addTempalate.DoModal();
	if(addTempalate.m_strTemplate == "")
		return;

	CString str1, strXMLPath;
	str1 = m_strModel;
	str1.Replace(" ", "_");
	strXMLPath = m_strTempDirPath + "\\" + addTempalate.m_strTemplate;
	if(addTempalate.m_bRefer)//����ο�������ģ��
	{
		//��������ģ��
		
		CopyFile(addTempalate.m_strRefTempPath, strXMLPath + ".xml", FALSE);//�������浽����·��
		CopyFile(addTempalate.m_strRefTempPath.Left(addTempalate.m_strRefTempPath.GetLength() - 3) + "xls", strXMLPath + ".xls", FALSE);//����Excelģ���ļ�
		//ģ��ĸ��ڵ����
		changeXMLRootName(strXMLPath + ".xml", str1);
		//����ģ��Ϊ��ͬ�豸�ͺŵ�ģ��
		if(m_strModel != addTempalate.m_strReferModel)
		{
			//ɾ���������
			CXmlFile_Ope xmlope;
			xmlope.LoadXmlFile(strXMLPath + ".xml");
			if(xmlope.pRootEle != NULL)
			{
				TiXmlElement* pEle = NULL;
				pEle = xmlope.pRootEle->FirstChildElement("SolutionList");
				pEle->Clear();
				xmlope.SaveFile();
			}
		}
	}
	else
	{
		CXml_UUTInfo xmlUUTInfo;
		xmlUUTInfo.CreatTemplateInfo(strXMLPath + ".xml", str1);
	}
	UpdataTempleteCom(m_strKind, m_strModel);
}

void CInsDocTemplete::changeXMLRootName(CString strXMLFile, CString strRootName)//�޸�XML�ļ����ڵ�
{
	CFileFind ff;
	BOOL bFinded = ff.FindFile(strXMLFile);
	int nDirTime = 0;
	while (bFinded)
	{
		bFinded = ff.FindNextFile();
		
		if (ff.IsDots())
			continue;
		if (ff.IsDirectory())
			continue;		
		else
		{
			CXmlFile_Ope xmlope;
			xmlope.LoadXmlFile(strXMLFile);
			if(xmlope.pRootEle != NULL)
			xmlope.pRootEle->SetValue(strRootName);
			xmlope.SaveFile();
		}
	}
	ff.Close();
}

void CInsDocTemplete::OnButtonDelTestmodel() 
{
	CInsDocTempDel delTmp;
	delTmp.m_strDir = m_strTempDirPath;
	delTmp.DoModal();
	CString str1;
	for(int i = 0; i < delTmp.m_strTemplateArray.GetSize(); i++)
	{
		DeleteFile(m_strTempDirPath + "\\" + delTmp.m_strTemplateArray[i] + ".xml");
		DeleteFile(m_strTempDirPath + "\\" + delTmp.m_strTemplateArray[i] + ".xls");
	}
	UpdataTempleteCom(m_strKind, m_strModel);
}

void CInsDocTemplete::OnMenuTempleteAdd() //�����µĲ�����Ŀ
{
	m_list_Templete.AddAllLine(m_nListSelectItem);
}

void CInsDocTemplete::AddNewItem(int nTestItem, int nListItem)//�����µĲ�����Ŀ(������Ŀ���, �б���к�)
{
	bool bAccess = false;
	UUTItemSet uutItS1;
	uutItS1.m_intID  = 0; //ID
	uutItS1.m_strKey.Format("Key%d", m_testItem[nTestItem].nKey);
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(m_vUUTItem[i].m_strKey == uutItS1.m_strKey)
			{
				AfxMessageBox("����ӵ� " + m_testItem[nTestItem].strName + " �����е� " + m_vUUTItem[i].m_strItemName + " Key����ͬ, �����ظ���Ӳ�����Ŀ, �Ѻ���!");
				return;
			}
		}
	}

	if(m_testItem[nTestItem].strTestType == "Control")
	{
		uutItS1.m_strItemName = m_testItem[nTestItem].strName;
		uutItS1.m_strMarkName="Control";
	}
	else
	{
    	uutItS1.m_strItemName = m_testItem[nTestItem].strName + "_" + m_testItem[nTestItem].strNote;
		uutItS1.m_strMarkName = "Test";
		uutItS1.m_strResultCol = "A";
		uutItS1.m_strResultRow = "1";

		uutItS1.m_pTestPoint = new TestPointSet;
		uutItS1.m_pTestPoint->m_intID = 0;
		uutItS1.m_pTestPoint->m_strCol = "A";
		uutItS1.m_pTestPoint->m_strLine = "1";
		uutItS1.m_pTestPoint->m_strLower = "0";
		uutItS1.m_pTestPoint->m_strUpper = "0";
		uutItS1.m_pTestPoint->m_strResultMark = "���Խ��";
		uutItS1.m_pTestPoint->m_strResultUnit = "";
		uutItS1.m_pTestPoint->m_VarSet = NULL;
		uutItS1.m_pTestPoint->next = NULL;
	}
	if(nListItem < 0)//ĩβ���
	{
		m_vUUTItem.push_back(uutItS1);
		bAccess = true;
	}
	else
	{
		int n1, nI = 0;
		int nItem = -1;
		bool bFind = false;
		TestPointSet *pSet;
		TestPointSet *pSetPrew;
		for(int i = 0; i < m_vUUTItem.size(); i++)
		{
			if(m_vUUTItem[i].m_strMarkName == "Control")
			{
				if(nI == m_nListSelectItem)
				{
					nItem = i;
					break;
				}
				nI++;
			}
			else
			{
				pSetPrew = pSet = m_vUUTItem[i].m_pTestPoint;
				n1 = -1;
				while(pSet != NULL)
				{
					n1++;
					if(nI == m_nListSelectItem)
					{
						if(n1 == 0)//�����ҵ����ǲ�����Ŀ�ĵ�һ����Ŀ
						{
							nItem = i;
							bFind = true;
						}
						break;
					}
					pSetPrew = pSet;
					pSet = pSet->next;
					nI++;
				}
			}
			if(bFind)
				break;
		}
		
		if(nItem > -1)
		{
			vector<UUTItemSet>::iterator iter;
			iter = m_vUUTItem.begin();
			iter += nItem;
			m_vUUTItem.insert(iter, uutItS1);
			bAccess = true;
		}
		else
			return;
	}
	
	if(bAccess)
	{
		CString str1;
		str1.Format("%d", m_testItem[nTestItem].nKey);
		if(nListItem < 0)
			nListItem = m_list_Templete.GetItemCount();
		m_list_Templete.InsertItem(nListItem, str1);
		m_list_Templete.SetItemText(nListItem, 1, m_testItem[nTestItem].strName + "_" + m_testItem[nTestItem].strNote);
		if(m_testItem[nTestItem].strTestType == "Control")
			m_list_Templete.SetItemText(nListItem, 2, "Control");
		else
		{
			m_list_Templete.SetItemText(nListItem, 3, "0");
			m_list_Templete.SetItemText(nListItem, 4, "0");
			m_list_Templete.SetItemText(nListItem, 6, "A:1");
			m_list_Templete.SetItemText(nListItem, 7, "A:1");
		}
		ReOrderNumber();
	}
}

void CInsDocTemplete::OnMenuTempleteCopy() //���������벽��
{
	bool bAccess = false;
	//���ҵ������б��������
	int nItemDx, nTestPointDx, n1, nI = 0;
	nItemDx = nTestPointDx = -1;//�ڵ��־
	TestPointSet *pSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
			nI++;
		else
		{
			pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == m_nListSelectItem)
				{
					nItemDx = i;//��ýڵ��־
					nTestPointDx = n1;
					break;
				}
				nI++;
				pSet = pSet->next;
			}
			if(nItemDx >= 0)
				break;
		}
	}
	if(nItemDx >= 0 && nTestPointDx >= 0 && pSet != NULL)
	{
		TestPointSet *pNew = new TestPointSet;
		if(pNew == NULL)
			return;

		pNew->m_intID = pSet->m_intID;//�����ṹ��
		pNew->m_strUpper = pSet->m_strUpper;
		pNew->m_strLower = pSet->m_strLower;
		pNew->m_strResultMark = pSet->m_strResultMark;
		pNew->m_strResultUnit = pSet->m_strResultUnit;
		pNew->m_strCol = pSet->m_strCol;
		pNew->m_strLine = pSet->m_strLine;
		pNew->m_VarSet = NULL;

		pNew->next = pSet->next;//���ڵ���������
		pSet->next = pNew;
		bAccess = true;

		PointVarSet  *pVar1 = pSet->m_VarSet;
		PointVarSet  *pVar2 = NULL;
		while(pVar1 != NULL)
		{
			PointVarSet* pVarSet = new PointVarSet;
			if(pVarSet == NULL)
				return;

			pVarSet->m_intID = pVar1->m_intID;
			pVarSet->m_strLogicName = pVar1->m_strLogicName;
			pVarSet->m_strName = pVar1->m_strName;
			pVarSet->m_strValue = pVar1->m_strValue;
			pVarSet->m_strUnit = pVar1->m_strUnit;
			pVarSet->next = NULL;

			if(pNew->m_VarSet == NULL)
				pNew->m_VarSet = pVarSet;
			else
				pVar2->next = pVarSet;
			pVar2 = pVarSet;

			pVar1 = pVar1->next;
		}
	}
	
	if(bAccess)
	{
		m_list_Templete.InsertItem(m_nListSelectItem + 1, "");
		for(int i = 2; i < 7; i++)
			m_list_Templete.SetItemText(m_nListSelectItem + 1, i, m_list_Templete.GetItemText(m_nListSelectItem, i));
	}
}

void CInsDocTemplete::OnMenuTempleteDel() //ɾ������
{
	//����ɾ���б��������
	int n1, nI = 0;
	TestPointSet *pSet;
	TestPointSet *pSetPrew;
	bool bAccess = false;
	bool bReOrder = false;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
		{
			if(nI == m_nListSelectItem)
			{
				m_vUUTItem.erase(m_vUUTItem.begin() + i);
				bAccess = true;
				bReOrder = true;
				break;
			}
			nI++;
		}
		else
		{
			pSetPrew = pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == m_nListSelectItem)
				{
					if(n1 == 0)//����ɾ�����ǲ�����Ŀ�ĵ�һ����Ŀ
					{
						if(pSet->next == NULL)//�������������Ŀֻ��һ������
						{
							m_vUUTItem.erase(m_vUUTItem.begin() + i);
							bReOrder = true;
							bAccess = true;
						}
						else
						{
							m_vUUTItem[i].m_pTestPoint = pSet->next;
							bAccess = true;
							delete pSet;//ɾ���ڵ�
							m_list_Templete.SetItemText(m_nListSelectItem + 1, 0, m_list_Templete.GetItemText(m_nListSelectItem, 0));
							m_list_Templete.SetItemText(m_nListSelectItem + 1, 1, m_list_Templete.GetItemText(m_nListSelectItem, 1));
							m_list_Templete.SetItemText(m_nListSelectItem + 1, 7, m_list_Templete.GetItemText(m_nListSelectItem, 7));
						}
					}
					else
					{
						pSetPrew->next = pSet->next;
						bAccess = true;
						delete pSet;//ɾ���ڵ�
					}
					break;
				}
				nI++;
				pSetPrew = pSet;
				pSet = pSet->next;
			}
		}
		if(bAccess)
			break;
	}
	if(bAccess)
	{
		m_list_Templete.DeleteItem(m_nListSelectItem);
		if(bReOrder)
			ReOrderNumber();
	}
}

void CInsDocTemplete::SetTestDitional(int nTestItem)//���ò�������
{
	//��ýڵ�
	int nItemDx, nTestPointDx, n1, nI = 0;
	nItemDx = nTestPointDx = -1;//�ڵ��־
	TestPointSet *pSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
			nI++;
		else
		{
			pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == nTestItem)
				{
					nItemDx = i;//��ýڵ��־
					nTestPointDx = n1;
					break;
				}
				nI++;
				pSet = pSet->next;
			}
			if(nItemDx >= 0)
				break;
		}
	}
	if(nItemDx >= 0 && nTestPointDx >= 0)
	{
		pSet = m_vUUTItem[nItemDx].m_pTestPoint;
		for(int i = 0; i < nTestPointDx; i++)
			pSet = pSet->next;//��ø��ڵ�
		if(pSet == NULL)
			return;

		InsDocTemplateTestCondition condit1;
		condit1.m_VarSet.RemoveAll();
		PointVarSet* pVarSet = pSet->m_VarSet;
		PointVarSet var1;
		while(pVarSet != NULL)
		{
			var1.m_strLogicName = pVarSet->m_strLogicName;
			var1.m_strName = pVarSet->m_strName;
			var1.m_strUnit = pVarSet->m_strUnit;
			var1.m_strValue = pVarSet->m_strValue;
			condit1.m_VarSet.Add(var1);
			pVarSet = pVarSet->next;
		}
		condit1.DoModal();//�����Ի���
		if(condit1.m_bChanged == false)
			return;
		//ɾ���������нڵ�
		PointVarSet *p,*h;
		h = pSet->m_VarSet;
		while(h)
		{
			p = h;
			h = h->next;
			free(p);
		}
		pSet->m_VarSet = NULL;
		CString strSetString = "";
		for(int i = 0; i < condit1.m_VarSet.GetSize(); i++)//��öԻ�������
		{
			PointVarSet *pP = new PointVarSet;
			if(pP == NULL)
				return;
			
			pP->m_intID = condit1.m_VarSet[i].m_intID;//�޸�����
			pP->m_strLogicName = condit1.m_VarSet[i].m_strLogicName;
			pP->m_strName = condit1.m_VarSet[i].m_strName;
			pP->m_strValue = condit1.m_VarSet[i].m_strValue;
			pP->m_strUnit = condit1.m_VarSet[i].m_strUnit;
			pP->next = NULL;

			if(pSet->m_VarSet == NULL)
				pSet->m_VarSet = pP;
			else
			{
				PointVarSet* pVar1 = pSet->m_VarSet;
				while(pVar1 != NULL)
				{
					if (pVar1->next == NULL)
						break;
					pVar1 = pVar1->next;
				}
				pVar1->next = pP;
			}
			strSetString+=condit1.m_VarSet[i].m_strName+"=";
			strSetString+=condit1.m_VarSet[i].m_strValue;
			strSetString+=condit1.m_VarSet[i].m_strUnit+";";
		}
		m_list_Templete.SetItemText(nTestItem, 2, strSetString);//�޸���ʾ
	}
}

void CInsDocTemplete::ChangeItem(int nItem, int nSubItem)//�޸Ĳ��Բ����ڵĲ���
{
	//��ýڵ�
	int nItemDx, nTestPointDx, n1, nI = 0;
	nItemDx = nTestPointDx = -1;//�ڵ��־
	TestPointSet *pSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
			nI++;
		else
		{
			pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == nItem)
				{
					nItemDx = i;//��ýڵ��־
					nTestPointDx = n1;
					break;
				}
				nI++;
				pSet = pSet->next;
			}
			if(nItemDx >= 0)
				break;
		}
	}
	if(nItemDx >= 0 && nTestPointDx >= 0 && pSet != NULL)
	{
		CString str1 = m_list_Templete.GetItemText(nItem, nSubItem);

		switch(nSubItem)
		{
		case 1://������Ŀ����
			{
				if(str1.IsEmpty())
				{
					AfxMessageBox("����д�ǿ�����!");
					return;
				}
				char cFirst = str1[0];
				if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
				{
					AfxMessageBox("�������ַ�����Ϊ���š����ּ��ո�!");
					return;
				}
				m_vUUTItem[nItemDx].m_strItemName = str1;
				break;
			}
		case 6://Excel����
			{
				str1.MakeUpper();
				if(str1.Find(',') < 0)//�ж��ǵ��ַ��������ַ�������
				{
					int n2 = 0;
					n1 = 0;
					char cChar;
					for(int i = 0; i < str1.GetLength(); i++)//������ߵ���ĸ
					{
						cChar = str1[i];
						if(cChar < 'A' || cChar > 'Z')
							break;
						n1++;
					}
					for(int i = str1.GetLength() - 1; i >=0 ; i--)
					{
						cChar = str1[i];
						if(cChar < '0' || cChar > '9')
							break;
						n2++;
					}
					CString str2 = str1.Right(n2);
					str1 = str1.Left(n1);
					if(str2 == "" || str1 == "")
					{
						AfxMessageBox("Excel�����к��кŶ�Ҫ��д,�к�ʹ��A-Z����ĸ,�к�ʹ��������, ��A1��AA123");
						return;
					}
					if(atoi(str2) <= 0)
					{
						AfxMessageBox("Excel�����кŲ���Ϊ0");
						return;
					}
					m_list_Templete.SetItemText(nItem, nSubItem, str1 + ":" + str2);
					
					pSet->m_strCol = str1;
					pSet->m_strLine = str2;
				}
				else
				{
					CStringArray strArray1, strArray2, strArray3;
					strArray1.RemoveAll();
					if(str1.Right(1) != ',')
						str1 += ',';
					CString str2 = "";
					while(str1.Find(',') >= 0)//�ַ����и���ַ�����
					{
						n1 = str1.Find(',');
						str2 = str1.Left(n1);
						str1 = str1.Right(str1.GetLength() - n1 - 1);
						strArray1.Add(str2);
					}

					for(int j = 0; j < strArray1.GetSize(); j++)
					{
						int n2 = 0;
						n1 = 0;
						char cChar;
						for(int i = 0; i < strArray1[j].GetLength(); i++)//������ߵ���ĸ
						{
							cChar = strArray1[j][i];
							if(cChar < 'A' || cChar > 'Z')
								break;
							n1++;
						}
						for(int i = str1.GetLength() - 1; i >=0 ; i--)
						{
							cChar = strArray1[j][i];
							if(cChar < '0' || cChar > '9')
								break;
							n2++;
						}
						CString str2 = strArray1[j].Right(n2);
						str1 = strArray1[j].Left(n1);
						if(str2 == "" || str1 == "")
							continue;
						if(atoi(str2) <= 0)
							continue;
						strArray2.Add(str1);
						strArray3.Add(str2);
						//m_list_Templete.SetItemText(nItem, nSubItem, str1 + ":" + str2);
						
						//pSet->m_strCol = str1;
						//pSet->m_strLine = str2;
					}

					pSet->m_strCol = "";
					pSet->m_strLine = "";
					str1 = "";
					for(int j = 0; j < strArray2.GetSize(); j++)
					{
						pSet->m_strCol += strArray2[j] + ",";
						pSet->m_strLine += strArray3[j] + ",";
						str1 += strArray2[j] + ":" + strArray3[j] + ",";
					}
					pSet->m_strCol = pSet->m_strCol.Left(pSet->m_strCol.GetLength() - 1);
					pSet->m_strLine = pSet->m_strLine.Left(pSet->m_strLine.GetLength() - 1);
					str1 = str1.Left(str1.GetLength() - 1);
					m_list_Templete.SetItemText(nItem, nSubItem, str1);
				}
				break;
			}
		case 7://Excel����
			{
				str1.MakeUpper();
				int n2 = 0;
				n1 = 0;
				char cChar;
				for(int i = 0; i < str1.GetLength(); i++)//������ߵ���ĸ
				{
					cChar = str1[i];
					if(cChar < 'A' || cChar > 'Z')
						break;
					n1++;
				}
				for(int i = str1.GetLength() - 1; i >=0 ; i--)
				{
					cChar = str1[i];
					if(cChar < '0' || cChar > '9')
						break;
					n2++;
				}
				CString str2 = str1.Right(n2);
				str1 = str1.Left(n1);
				if((str2 == "" && str1 != "") || (str2 != "" && str1 == ""))
				{
					AfxMessageBox("Excel�����к��кŶ�Ҫ��д,�к�ʹ��A-Z����ĸ,�к�ʹ��������, ��A1��AA123");
					return;
				}
				if( str1 != "" && atoi(str2) <= 0)
				{
					AfxMessageBox("Excel�����кŲ���Ϊ0");
					return;
				}
				m_list_Templete.SetItemText(nItem, nSubItem, str1 + ":" + str2);
				
				m_vUUTItem[nItemDx].m_strResultCol = str1;
				m_vUUTItem[nItemDx].m_strResultRow = str2;
				break;
			}
		case 3://����ֵ
			pSet->m_strLower = str1;
			break;
		case 4://����ֵ
			pSet->m_strUpper = str1;
			break;
		case 5://��λ
			pSet->m_strResultUnit = str1;
			break;
		default:
			break;
		}
	}
}

void CInsDocTemplete::OnButtonSaveTemplate()
{
 	CString str1, strXmlFilePath = m_strTempDirPath + "\\" + m_strTemplete + ".xml";//·��
	CXmlFile_Ope xmlOpe;
	xmlOpe.LoadXmlFile(strXmlFilePath);//����
	TiXmlElement* pEle_ItemSet=NULL;
	if(NULL != xmlOpe.pRootEle)
		pEle_ItemSet=xmlOpe.pRootEle->FirstChildElement("ItemSet");
	else
	{
		str1 = m_strModel;
		str1.Replace(" ", "_");
		xmlOpe.pRootEle = new TiXmlElement(str1);
	}

	if(NULL == pEle_ItemSet)
	{
		pEle_ItemSet = new TiXmlElement("ItemSet");
		xmlOpe.pRootEle->LinkEndChild(pEle_ItemSet);
	}

	pEle_ItemSet->Clear();

	int nID1, nID2, nID = 1;
	TestPointSet *pTestPoint;
	PointVarSet	 *pVarSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		TiXmlElement* pEle_Temp  = NULL;
		TiXmlElement* pEle_Temp1 = NULL;
		TiXmlElement* pEle_Temp2 = NULL;
		TiXmlElement* pEle_Temp3 = NULL;
		TiXmlElement* pEle_Temp4 = NULL;
		if(m_vUUTItem[i].m_strMarkName == "Control")
		{
			pEle_Temp = new TiXmlElement("Control");
			//str1.Format("Key%d", m_vUUTItem[i].m_intID);
			pEle_Temp->SetAttribute("key", m_vUUTItem[i].m_strKey);
			pEle_Temp->SetAttribute("Value", m_vUUTItem[i].m_strItemName);
			pEle_ItemSet->LinkEndChild(pEle_Temp);
		}
		else
		{
			pEle_Temp = new TiXmlElement(m_vUUTItem[i].m_strKey);//����Key*������Ŀ
			pEle_Temp->SetAttribute("Name", m_vUUTItem[i].m_strItemName);
			str1.Format("%d", nID);
			pEle_Temp->SetAttribute("ID", str1);
			pEle_ItemSet->LinkEndChild(pEle_Temp);

			pEle_Temp1 = new TiXmlElement("Conclusion");//����������Ŀ���Excelλ��
			pEle_Temp->LinkEndChild(pEle_Temp1);

			pEle_Temp2 = new TiXmlElement("Value");
			pEle_Temp2->SetAttribute("ColNum", m_vUUTItem[i].m_strResultCol);
			pEle_Temp2->SetAttribute("LineNum", m_vUUTItem[i].m_strResultRow);
			pEle_Temp1->LinkEndChild(pEle_Temp2);

			pEle_Temp1 = new TiXmlElement("PointSet");//�������Բ���
			pEle_Temp->LinkEndChild(pEle_Temp1);

			pTestPoint = m_vUUTItem[i].m_pTestPoint;
			nID1 = 1;
			while(pTestPoint != NULL)
			{
				if(pTestPoint->m_strUpper == "100.819999")
					Sleep(10);
				pEle_Temp2 = new TiXmlElement("Point");//���Բ���
				str1.Format("%d", nID1);
				pEle_Temp2->SetAttribute("ID", str1);
				pEle_Temp1->LinkEndChild(pEle_Temp2);

				pEle_Temp3 = new TiXmlElement("Upper");//���Բ��贴������ֵ
				pEle_Temp3->SetAttribute("Value", pTestPoint->m_strUpper);
				pEle_Temp2->LinkEndChild(pEle_Temp3);

				pEle_Temp3 = new TiXmlElement("Lower");//���Բ��贴������ֵ
				pEle_Temp3->SetAttribute("Value", pTestPoint->m_strLower);
				pEle_Temp2->LinkEndChild(pEle_Temp3);

				pEle_Temp3 = new TiXmlElement("ResultList");//���Բ��贴�����Խ��
				pEle_Temp2->LinkEndChild(pEle_Temp3);

					pEle_Temp4 = new TiXmlElement("Result");//���Բ��贴����������
					pEle_Temp4->SetAttribute("Mark", pTestPoint->m_strResultMark);
					pEle_Temp4->SetAttribute("Unit", pTestPoint->m_strResultUnit);
					pEle_Temp4->SetAttribute("ColNum", pTestPoint->m_strCol);
					pEle_Temp4->SetAttribute("LineNum", pTestPoint->m_strLine);
					pEle_Temp3->LinkEndChild(pEle_Temp4);

				pEle_Temp3 = new TiXmlElement("VarSet");//���Բ��贴����������
				pEle_Temp2->LinkEndChild(pEle_Temp3);

				pVarSet = pTestPoint->m_VarSet;
				nID2 = 1;
				while(pVarSet != NULL)
				{
					pEle_Temp4 = new TiXmlElement(pVarSet->m_strLogicName);//�����������������
					pEle_Temp4->SetAttribute("Value", pVarSet->m_strValue);
					pEle_Temp4->SetAttribute("Unit", pVarSet->m_strUnit);
					pEle_Temp4->SetAttribute("Name", pVarSet->m_strName);
					str1 = pVarSet->m_strValue;
					str1.Format("%d", nID2);
					pEle_Temp4->SetAttribute("ID", str1);
					pEle_Temp3->LinkEndChild(pEle_Temp4);

					pVarSet = pVarSet->next;
					nID2++;
				}
				nID1++;
				pTestPoint = pTestPoint->next;
			}
			nID++;
		}
	}
	xmlOpe.SaveFile();
	UpdataTestTempleteList(m_strTemplete);
	KillTimer(1);
	SetTimer(1, 300000, NULL);
}

void CInsDocTemplete::OnButtonSaveSolutionInTemplate() 
{
	CFile_UUTInfo file_UUTInfo;
	vector<FileInfo> vFileinfo1;
	file_UUTInfo.GetSolutionList(m_strKind, m_strModel, &vFileinfo1);

	CStringArray strSolutionArray;
	CString str1;
	bool bRep, bNoinDir, bNoinDirAnyone;
	bRep = bNoinDir = bNoinDirAnyone = false;

	for(int i = 0; i < m_list_Solution_in_Templete.GetItemCount(); i++)
	{
		str1 = m_list_Solution_in_Templete.GetItemText(i, 1);
		if(str1.IsEmpty())
			continue;
		bRep = false;
		bNoinDir  = false;
		for(int j = 0; j < strSolutionArray.GetSize(); j++)
		{
			if(str1 == strSolutionArray[j])//�ظ�
			{
				bRep = true;
				break;
			}
		}
		if(!bRep)
		{
			for(int k = 0; k < vFileinfo1.size(); k++)
			{
				if(str1 == vFileinfo1[k].m_strFileName)//��·���ļ������޸ý������
				{
					bNoinDir = true;
					break;
				}
			}
		}
		if(bNoinDir)
			strSolutionArray.Add(str1);
		else if(!bRep)
			bNoinDirAnyone = true;

	}

	for(int k = 0; k < strSolutionArray.GetSize(); k++)
			{
				str1 = strSolutionArray[k];
			}
	if(strSolutionArray.GetSize() > 0)
	{
		CXml_Bll_UUTItem_Tem bll_UUTITem_tem;
		bll_UUTITem_tem.WriteSolutionList(m_strKind,m_strModel,m_strTemplete, strSolutionArray);
		UpdataTestSolutionList(m_strTemplete);
	}
	if(bNoinDirAnyone)
		AfxMessageBox("�в��ֽ�������Ҳ�����������ļ���,����ɾ������!");
}

void CInsDocTemplete::OnMenuTempleteSolutionDel() 
{
	int nIndex = m_list_Solution_in_Templete.GetSelectionMark();
	if(nIndex >= 0)
	{
		m_list_Solution_in_Templete.DeleteItem(nIndex);
		int nLen = m_list_Solution_in_Templete.GetItemCount();
		for(int i = 0; i < nLen; i++)
			m_list_Solution_in_Templete.SetItemState(i, 0,LVIS_SELECTED|LVIS_FOCUSED);
		m_list_Solution_in_Templete.SetSelectionMark(-1);
		ReOrderNumber1();
	}
}

void CInsDocTemplete::OnButtonShowExcel() 
{
	CString str1 = m_strTempDirPath + "\\" + m_strTemplete + ".xls";
	CFileFind ff;
	BOOL bFinded = ff.FindFile(str1);
	bool bExcelExist = false;
	while (bFinded)
	{
		bFinded = ff.FindNextFile();
		
		if (ff.IsDots())
			continue;		
		else if (ff.IsDirectory())
			continue;
		else
			bExcelExist = true;
	}
	ff.Close();

	if(bExcelExist)
	{
		if(IsWindow(m_Excel))
		{
			m_Excel.ShowWindow(SW_SHOWNORMAL);
			//m_Excel.m_DosExcel.Invalidate(TRUE);
			return;
		}
		m_Excel.m_strPath  = str1;
		m_Excel.Create(IDD_INSDOC_TEMPLATE_EXCEL, this);
		m_Excel.MoveWindow(0, 0, 200, 400);
		m_Excel.ShowWindow(SW_SHOWNORMAL);
		//m_Excel.m_DosExcel.Invalidate(TRUE);
	}
	else
		AfxMessageBox("Excelģ�岻����,���������!");
}

void CInsDocTemplete::ReOrderNumber() 
{
	int nI = m_list_Templete.GetItemCount();
	int nOrder = 1;
	CString str1;
	for(int i = 0; i < nI; i++)
	{
		if(m_list_Templete.GetItemText(i, 0) != "")
		{
			str1.Format("%d", nOrder);
			m_list_Templete.SetItemText(i, 0, str1);
			nOrder++;
		}
	}
}

void CInsDocTemplete::OnClickListResultInsdoc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_strModel == "")
		return;
	CListInstTemplate* pWndList = (CListInstTemplate*) &m_list_Templete;
	ASSERT_VALID(pWndList);

	CPoint point, pointList;
	point.x = -1;
	point.y = -1;
	GetCursorPos(&point);
	pointList = point;
	m_nListSelectItem = -1;

	if (point != CPoint(-1, -1))
	{
		pWndList->ScreenToClient(&pointList); 
		LVHITTESTINFO lvinfo;
		lvinfo.pt = pointList;
		lvinfo.flags = LVHT_ABOVE;    
		int nItem = pWndList->SubItemHitTest(&lvinfo);
		if(nItem != -1)
			m_nListSelectItem = lvinfo.iItem;
		pWndList->SetFocus();
	}

	if(m_nListSelectItem != -1)
	{
		//����ɾ���б��������
		int nI = 0;
		TestPointSet *pSet;
		TestPointSet *pSetPrew;
		bool bAccess = false;
		int  nKey;
		for(int i = 0; i < m_vUUTItem.size(); i++)
		{
			if(m_vUUTItem[i].m_strMarkName == "Control")
			{
				if(nI == m_nListSelectItem)
				{
					nKey = atoi(m_vUUTItem[i].m_strKey.Mid(3));
					bAccess = true;
					break;
				}
				nI++;
			}
			else
			{
				pSetPrew = pSet = m_vUUTItem[i].m_pTestPoint;
				while(pSet != NULL)
				{
					if(nI == m_nListSelectItem)
					{
						nKey = atoi(m_vUUTItem[i].m_strKey.Mid(3));
						bAccess = true;
						break;
					}
					nI++;
					pSetPrew = pSet;
					pSet = pSet->next;
				}
			}
			if(bAccess)
				break;
		}
		if(bAccess)
		{
			for(int i = 0; i < m_testItem.GetSize(); i++)
			{
				if(nKey == m_testItem[i].nKey)
				{
					CString str1;
					if(m_testItem[i].strTestType == "Test")
					{
						str1.Format("Key%d", m_testItem[i].nKey);
						str1 += "  " + m_testItem[i].strName + "  " + m_testItem[i].strNote + " ������Ŀ";
					}
					else
					{
						str1.Format("Key%d", m_testItem[i].nKey);
						str1 += "  " + m_testItem[i].strName + "  У׼��Ŀ";
					}
					m_edt_Explain.SetWindowText(str1);
					m_edt_Explain.ShowWindow(SW_HIDE);
					m_edt_Explain.ShowWindow(SW_SHOWNORMAL);
				}
			}
		}
	}
	*pResult = 0;
}

void CInsDocTemplete::OnTemplateSolutionAdd() 
{
	int nI = m_list_Solution_in_Templete.GetItemCount();
	m_list_Solution_in_Templete.InsertItem(nI, "");
	ReOrderNumber1();
	m_list_Solution_in_Templete.EnsureVisible(nI, TRUE);
	for(int i = 0; i < nI; i++)
		m_list_Solution_in_Templete.SetItemState(i, 0,LVIS_SELECTED|LVIS_FOCUSED);
	m_list_Solution_in_Templete.SetItemState(nI, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
}

void CInsDocTemplete::ReOrderNumber1() 
{
	int nI = m_list_Solution_in_Templete.GetItemCount();
	int nOrder = 1;
	CString str1;
	for(int i = 0; i < nI; i++)
	{
		if(m_list_Templete.GetItemText(i, 0) != "")
		{
			str1.Format("%d", nOrder);
			m_list_Solution_in_Templete.SetItemText(i, 0, str1);
			nOrder++;
		}
	}
}

void CInsDocTemplete::OnButtonAddSolutionInTemplate() 
{
	OnTemplateSolutionAdd();
}

void CInsDocTemplete::OnButtonDelSolutionInTemplate() 
{
	OnMenuTempleteSolutionDel();	
}

void CInsDocTemplete::UpdateChangeState(int nChangeState)
{
	switch(nChangeState)
	{
	case 1:
		m_btn_Change_Template.SetWindowText("�޸�");

		m_btn_Change_Template.EnableWindow(TRUE);
		m_btn_add_Templete.EnableWindow(FALSE);
		m_btn_Del_Template.EnableWindow(FALSE);	
		m_btn_Change_Excel.EnableWindow(FALSE);
		m_btn_Show_Excel.EnableWindow(FALSE);
		m_btn_Excel_Front_Page.EnableWindow(FALSE);
		m_btn_Save_Template.EnableWindow(FALSE);
		m_btn_Save_Solution.EnableWindow(FALSE);
		m_btn_Add_Solution.EnableWindow(FALSE);
		m_btn_Del_Solution.EnableWindow(FALSE);
		KillTimer(1);
		break;
	case 2:
		m_btn_Change_Template.SetWindowText("��ֹ�޸�");
		m_btn_Change_Template.EnableWindow(TRUE);
		m_btn_add_Templete.EnableWindow(TRUE);
		m_btn_Del_Template.EnableWindow(TRUE);
		m_btn_Change_Excel.EnableWindow(TRUE);	
		m_btn_Show_Excel.EnableWindow(TRUE);
		m_btn_Excel_Front_Page.EnableWindow(TRUE);
		m_btn_Save_Template.EnableWindow(TRUE);
		m_btn_Save_Solution.EnableWindow(TRUE);
		m_btn_Add_Solution.EnableWindow(TRUE);
		m_btn_Del_Solution.EnableWindow(TRUE);
		SetTimer(1, 300000, NULL);
		break;
	default:
		m_btn_Change_Template.SetWindowText("�޸�");

		m_btn_Change_Template.EnableWindow(FALSE);
		m_btn_add_Templete.EnableWindow(FALSE);
		m_btn_Del_Template.EnableWindow(FALSE);	
		m_btn_Change_Excel.EnableWindow(FALSE);
		m_btn_Show_Excel.EnableWindow(FALSE);
		m_btn_Excel_Front_Page.EnableWindow(FALSE);
		m_btn_Save_Template.EnableWindow(FALSE);
		m_btn_Save_Solution.EnableWindow(FALSE);
		m_btn_Add_Solution.EnableWindow(FALSE);
		m_btn_Del_Solution.EnableWindow(FALSE);
		KillTimer(1);
		break;
	}
}

void CInsDocTemplete::OnButtonChangeTemplate() 
{
	m_nChangeState = m_nChangeState == 1 ? 2 : 1;
	UpdateChangeState(m_nChangeState);
}

void CInsDocTemplete::OnButtonExcelFrontPage() 
{
	CInsDocTempExcelFrontPage firstPG;
	CXml_Bll_UUTItem_Tem bll_UUTITem_tem;
	firstPG.m_strSheetNumber = "";
	firstPG.m_vFrontPage.RemoveAll();

	CString strTemPath=m_strTempDirPath + "\\"+m_strTemplete + ".xml"; //ģ��·��
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("�Ҳ���ģ�������ļ�","����");
		return;
	}
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("�Ҳ���ģ�������ļ�","����");
		return;
	}
	bll_UUTITem_tem.ReadFrontPageList(strTemPath, firstPG.m_strSheetNumber, firstPG.m_vFrontPage);
	firstPG.DoModal();
	if(firstPG.m_bChanged)
		bll_UUTITem_tem.WriteFrontPageList(m_strKind, m_strModel, m_strTemplete, firstPG.m_strSheetNumber, firstPG.m_vFrontPage);
}

void CInsDocTemplete::OnCusMenuTempleteDel()
{
	OnMenuTempleteDel();
}
void CInsDocTemplete::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1)
	{
		if(SetFocus() == GetDlgItem(IDC_LIST_RESULT_INSDOC))
		{
			KillTimer(1);
			if(MessageBox("���ڱ���ѡ���ǡ�����ʱ������ѡ����","5���ӱ���ģ����ʾ",MB_YESNO)==IDYES)
				OnButtonSaveTemplate();
			else
				SetTimer(1, 300000, NULL);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CInsDocTemplete::OnMenuTempleteFillItemrow() 
{
	CInsTempAutoFillRow FillRoew;
	FillRoew.DoModal();
	if(FillRoew.m_nRow > 0)
		FillTestResult(FillRoew.m_nRow);
}

void CInsDocTemplete::FillTestResult(int nRow)
{
	CString str1 = m_list_Templete.GetItemText(m_nListSelectItem, 6);
	str1.MakeUpper();
	int n2 = 0;
	int n3 = 0;
	int i;
	char cChar;
	for(i = 0; i < str1.GetLength(); i++)//������ߵ���ĸ
	{
		cChar = str1[i];
		if(cChar < 'A' || cChar > 'Z')
			break;
		n3++;
	}
	for(i = str1.GetLength() - 1; i >=0 ; i--)
	{
		cChar = str1[i];
		if(cChar < '0' || cChar > '9')
			break;
		n2++;
	}
	CString str2 = str1.Right(n2);
	str1 = str1.Left(n3);
	n3 = atoi(str2);
	if(str2 == "" || str1 == "")
	{
		AfxMessageBox("��ѡExcel�����л��кŲ���ȷ,�к�ʹ��A-Z����ĸ,�к�ʹ��������, ��A1��AA123");
		return;
	}
	if(n3 <= 0)
	{
		AfxMessageBox("��ѡExcel����кŲ���Ϊ0��С��0����ֵ");
		return;
	}
	for(int jj = m_nListSelectItem + 1; jj <= m_nListSelectItem + nRow && i < m_list_Templete.GetItemCount(); jj++)   //iֵ����ȷ
	{
		int nItemDx, nTestPointDx, n1, nI = 0;
		nItemDx = nTestPointDx = -1;//�ڵ��־
		TestPointSet *pSet;
		n1 = 0;
		for(int i = 0; i < m_vUUTItem.size(); i++)
		{
			if(m_vUUTItem[i].m_strMarkName == "Control")
				nI++;
			else
			{
				pSet = m_vUUTItem[i].m_pTestPoint;
				n1 = -1;
				while(pSet != NULL)
				{
					n1++;
					if(nI == jj)
					{
						nItemDx = i;//��ýڵ��־
						nTestPointDx = n1;
						break;
					}
					nI++;
					pSet = pSet->next;
				}
				if(nItemDx >= 0)
					break;
			}
		}
		if(nItemDx >= 0 && nTestPointDx >= 0 && pSet != NULL)
		{
			n3++;
			str2.Format("%d", n3);
			m_list_Templete.SetItemText(jj, 6, str1 + ":" + str2);
			pSet->m_strCol = str1;
			pSet->m_strLine = str2;
		}
	}
}

bool CInsDocTemplete::CopyTestPointSet(int nILineIndex, TestPointSet* pNew)
{
	bool bAccess = false;
	//���ҵ������б��������
	int nItemDx, nTestPointDx, n1, nI = 0;
	nItemDx = nTestPointDx = -1;//�ڵ��־
	TestPointSet *pSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
			nI++;
		else
		{
			pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == nILineIndex)
				{
					nItemDx = i;//��ýڵ��־
					nTestPointDx = n1;
					break;
				}
				nI++;
				pSet = pSet->next;
			}
			if(nItemDx >= 0)
				break;
		}
	}
	if(nItemDx >= 0 && nTestPointDx >= 0 && pSet != NULL)
	{
		pNew->m_intID = pSet->m_intID;//�����ṹ��
		pNew->m_strUpper = pSet->m_strUpper;
		pNew->m_strLower = pSet->m_strLower;
		pNew->m_strResultMark = pSet->m_strResultMark;
		pNew->m_strResultUnit = pSet->m_strResultUnit;
		pNew->m_strCol = pSet->m_strCol;
		pNew->m_strLine = pSet->m_strLine;
		pNew->m_VarSet = NULL;
		
		pNew->next = NULL;//���ڵ���������
		bAccess = true;
		
		PointVarSet  *pVar1 = pSet->m_VarSet;
		PointVarSet  *pVar2 = NULL;
		while(pVar1 != NULL)
		{
			PointVarSet* pVarSet = new PointVarSet;
			if(pVarSet == NULL)
				return false;
			
			pVarSet->m_intID = pVar1->m_intID;
			pVarSet->m_strLogicName = pVar1->m_strLogicName;
			pVarSet->m_strName = pVar1->m_strName;
			pVarSet->m_strValue = pVar1->m_strValue;
			pVarSet->m_strUnit = pVar1->m_strUnit;
			pVarSet->next = NULL;
			
			if(pNew->m_VarSet == NULL)
				pNew->m_VarSet = pVarSet;
			else
				pVar2->next = pVarSet;
			pVar2 = pVarSet;
			
			pVar1 = pVar1->next;
		}
	}
	return bAccess;
}



void CInsDocTemplete::OnMenuTempleteCopyLines() 
{
	CArray<int, int> LineArray;
	LineArray.RemoveAll();

	POSITION pos;
	unsigned int nSL = 0;
	pos = (struct __POSITION *)m_list_Templete.GetFirstSelectedItemPosition();
	while(pos)
	{
		LineArray.Add((int)pos - 1);
		m_list_Templete.GetNextSelectedItem(pos);
	}

	m_CopytestSet.RemoveAll();
	for(int i = 0; i < LineArray.GetSize(); i++)
	{
		TestPointSet testSet;
		if(CopyTestPointSet(LineArray[i], &testSet))
			m_CopytestSet.Add(testSet);
	}
}

void CInsDocTemplete::OnMenuTempletePast()
{
	bool bAccess = false;
	//���ҵ������б��������
	int nItemDx, nTestPointDx, n1, nI = 0;
	nItemDx = nTestPointDx = -1;//�ڵ��־
	TestPointSet *pSet;
	for(int i = 0; i < m_vUUTItem.size(); i++)
	{
		if(m_vUUTItem[i].m_strMarkName == "Control")
			nI++;
		else
		{
			pSet = m_vUUTItem[i].m_pTestPoint;
			n1 = -1;
			while(pSet != NULL)
			{
				n1++;
				if(nI == m_nListSelectItem)
				{
					nItemDx = i;//��ýڵ��־
					nTestPointDx = n1;
					break;
				}
				nI++;
				pSet = pSet->next;
			}
			if(nItemDx >= 0)
				break;
		}
	}
	if(nItemDx >= 0 && nTestPointDx >= 0 && pSet != NULL)
	{
		nI = m_nListSelectItem;
		for(int i = 0; i < m_CopytestSet.GetSize(); i++)
		{
			bAccess = false;
			TestPointSet *pNew = new TestPointSet;
			if(pNew == NULL)
				return;
		
			pNew->m_intID = m_CopytestSet[i].m_intID;//�����ṹ��
			pNew->m_strUpper = m_CopytestSet[i].m_strUpper;
			pNew->m_strLower = m_CopytestSet[i].m_strLower;
			pNew->m_strResultMark = m_CopytestSet[i].m_strResultMark;
			pNew->m_strResultUnit = m_CopytestSet[i].m_strResultUnit;
			pNew->m_strCol = m_CopytestSet[i].m_strCol;
			pNew->m_strLine = m_CopytestSet[i].m_strLine;
			pNew->m_VarSet = NULL;
			
			pNew->next = pSet->next;//���ڵ���������
			pSet->next = pNew;
			pSet = pNew;
			bAccess = true;
			
			PointVarSet  *pVar1 = m_CopytestSet[i].m_VarSet;
			PointVarSet  *pVar2 = NULL;
			while(pVar1 != NULL)
			{
				PointVarSet* pVarSet = new PointVarSet;
				if(pVarSet == NULL)
					return;
				
				pVarSet->m_intID = pVar1->m_intID;
				pVarSet->m_strLogicName = pVar1->m_strLogicName;
				pVarSet->m_strName = pVar1->m_strName;
				pVarSet->m_strValue = pVar1->m_strValue;
				pVarSet->m_strUnit = pVar1->m_strUnit;
				pVarSet->next = NULL;
				
				if(pNew->m_VarSet == NULL)
					pNew->m_VarSet = pVarSet;
				else
					pVar2->next = pVarSet;
				pVar2 = pVarSet;
				
				pVar1 = pVar1->next;
			}
	
			if(bAccess)
			{
				nI++;
				m_list_Templete.InsertItem(nI, "");

				CString strSetString="";
				pVar1 = pSet->m_VarSet;
				while(pVar1 != NULL)
				{
					strSetString+=pVar1->m_strName+"=";
					strSetString+=pVar1->m_strValue;
					strSetString+=pVar1->m_strUnit+";";
					pVar1 = pVar1->next;
				}
				strSetString=strSetString.Left(strSetString.GetLength()-1);
				
				m_list_Templete.SetItemText(nI,2,strSetString);
				m_list_Templete.SetItemText(nI,3,pSet->m_strLower);
				m_list_Templete.SetItemText(nI,4,pSet->m_strUpper);
				m_list_Templete.SetItemText(nI,5,pSet->m_strResultUnit);
				CString str1 = pSet->m_strCol + ',';
				CString str2 = pSet->m_strLine + ',';
				CString str3 = "";
				int n11, n12;
				while(str1.Find(',') >= 0 && str2.Find(',') >= 0)
				{
					n11 = str1.Find(',');
					n12 = str2.Find(',');
					str3 += str1.Left(n11) + ":" + str2.Left(n12) + ",";
					str1 = str1.Right(str1.GetLength() - n11 - 1);
					str2 = str2.Right(str2.GetLength() - n12 - 1);
				}
				str3 = str3.Left(str3.GetLength() - 1);
				m_list_Templete.SetItemText(nI, 6, str3);
			}
		}
	}
}

void CInsDocTemplete::OnButtonChangeExe() 
{
	if(IsWindow(m_Excel))
	{
		AfxMessageBox("Excelģ���Ѵ�,���ȹر�!");
		return;
	}
	CFileDialog dlg(TRUE, ".xls", NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Excelģ���ļ�(*.xls)|*.xls||");
	if(dlg.DoModal()==IDOK)
	{
		CString strDir, strPath, strName;
		strPath = dlg.GetPathName();
		strName	= dlg.GetFileName();
		if(strPath == "" || strName == "")
		{
			AfxMessageBox("Excelģ��·������ȷ");
			return;
		}
		CFileFind ff;
		BOOL bFind = ff.FindFile(strPath);
		bool bCre = false;
		while(bFind)
		{
			bFind = ff.FindNextFile(); 
			if(ff.IsDots())
				continue;
			if( ff.IsDirectory())
				continue;
			else
			{
				strDir = m_strTempDirPath + "\\" + m_strTemplete + ".xls";
				if(strPath == strDir)
				{
					AfxMessageBox("����Excelģ����Excelģ����ȫ��ͬ!������ѡ��");
					return;
				}
				DeleteFile(strDir);
				CopyFile(strPath, strDir, false);
				break;
			}
		}
	}	
}
