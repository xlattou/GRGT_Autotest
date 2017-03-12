// InsDocBasic.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocBasic.h"
#include "Xml_UUTInfo.h"
#include "InsDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocBasic dialog


CInsDocBasic::CInsDocBasic(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocBasic::IDD, pParent)
{
	m_strKind = "";
	m_strModel = "";
	m_nSeleteIndex = -1;
	m_nUUTItemMax = 0;
	m_nUUTItemMax1 = 0;
	m_nSaveState = 0;
}


void CInsDocBasic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocBasic)
	DDX_Control(pDX, IDC_BUTTON_DEL_TEST_ITEM, m_btn_Del_TestItem);
	DDX_Control(pDX, IDC_BUTTON_ADD_TEST_ITEM, m_btn_Add_TestItem);
	DDX_Control(pDX, IDC_GROUP_TEST_ITEM, m_group_Test_Item);
	DDX_Control(pDX, IDC_BUTTON_SAVE_TEST_ITEM, m_btn_SaveTestItem);
	DDX_Control(pDX, IDC_EDIT_MANUFACTORY_INSDOC, m_edt_Factory);
	DDX_Control(pDX, IDC_EDIT_MODEL_INSDOC, m_edt_Model);
	DDX_Control(pDX, IDC_EDIT_NAME_INSDOC, m_edt_Name);
	DDX_Control(pDX, IDC_LIST_TEST_ITEM, m_list_TestItem);
	DDX_Control(pDX, IDC_STATIC_TEST_ITEM, m_stc_TestItem);
	DDX_Control(pDX, IDC_STATIC_FACTORY_INSDOC, m_stc_Factory);
	DDX_Control(pDX, IDC_STATIC_MODEL_INSDOC, m_stc_Model);
	DDX_Control(pDX, IDC_STATIC_NAME_INSDOC, m_stc_Name);
	DDX_Control(pDX, IDC_GROUP_BASIC_INSDOC, m_group_Basic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocBasic, CDialog)
	//{{AFX_MSG_MAP(CInsDocBasic)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TEST_ITEM, OnRclickListTestItem)
	ON_COMMAND(ID_MENU_INS_BASIC_DEL, OnMenuInsBasicDel)
	ON_COMMAND(ID_MENU_INS_BASIC_NEW, OnMenuInsBasicNew)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TEST_ITEM, OnButtonSaveTestItem)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TEST_ITEM, OnButtonAddTestItem)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TEST_ITEM, OnButtonDelTestItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocBasic message handlers

BOOL CInsDocBasic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);
		
	DWORD dwStyle=m_list_TestItem.GetExtendedStyle();
	m_list_TestItem.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_TestItem.InsertColumn(0,"ID",LVCFMT_LEFT, 30);
	m_list_TestItem.InsertColumn(1,"测试功能",LVCFMT_LEFT,100);
	m_list_TestItem.InsertColumn(2,"备注",LVCFMT_LEFT,100);
	m_list_TestItem.InsertColumn(3,"Key",LVCFMT_CENTER,56);
	m_list_TestItem.InsertColumn(4,"类型",LVCFMT_CENTER,56);
	
	m_btn_SaveTestItem.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CInsDocBasic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}

	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
    	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	return hbr;
}

BOOL CInsDocBasic::DestroyWindow() 
{
	m_brush.DeleteObject();
	return CDialog::DestroyWindow();
}

void CInsDocBasic::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	int nWide, nHeight;
	CRect rect1;
	GetClientRect(&rect1);

	nWide = rect1.Width() - 20;
	if(IsWindow(m_group_Basic))
		m_group_Basic.MoveWindow(12, 20, nWide, 51);
	
	nWide -= 10;
	nWide /= 3;
	if(IsWindow(m_stc_Name))
		m_stc_Name.MoveWindow(18, 41, 60, 30);
	if(IsWindow(m_edt_Name))
		m_edt_Name.MoveWindow(52, 37, nWide - 40, 25);
	if(IsWindow(m_stc_Factory))
		m_stc_Factory.MoveWindow(18 + nWide, 41, 60, 25);
	if(IsWindow(m_edt_Factory))
		m_edt_Factory.MoveWindow(52 + nWide, 37, nWide - 40, 25);
	if(IsWindow(m_stc_Model))
		m_stc_Model.MoveWindow(18 + nWide * 2, 41, 60, 25);
	if(IsWindow(m_edt_Model))
		m_edt_Model.MoveWindow(52 + nWide * 2, 37, nWide - 40, 25);

	if(IsWindow(m_stc_TestItem))
		m_stc_TestItem.MoveWindow(18, 85, 120, 25);
	nHeight = rect1.Height() - 80;
	nWide = rect1.Width() - 20;
	if(IsWindow(m_btn_Add_TestItem))
		m_btn_Add_TestItem.MoveWindow(nWide - 170, 81, 55, 23);
	if(IsWindow(m_btn_Del_TestItem))
		m_btn_Del_TestItem.MoveWindow(nWide - 110, 81, 55, 23);
	if(IsWindow(m_btn_SaveTestItem))
		m_btn_SaveTestItem.MoveWindow(nWide - 50, 81, 55, 23);
	if(IsWindow(m_group_Test_Item))
		m_group_Test_Item.MoveWindow(12, 70, nWide, nHeight);
	if(IsWindow(m_list_TestItem))
	{
		m_list_TestItem.MoveWindow(20, 106, nWide - 16, nHeight - 44);
		m_list_TestItem.SetColumnWidth(1, nWide / 2 - 91);
		m_list_TestItem.SetColumnWidth(2, nWide / 2 - 91);
	}
}

BOOL CInsDocBasic::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CInsDocBasic::UpdateBasicInfo(CString strKind,CString strModel)
{
	try
	{		
		m_strKind = strKind;
		m_strModel = strModel;
		m_nUUTItemMax = 0;
		m_nUUTItemMax1 = 0;
		m_edt_Name.SetWindowText("");
		m_edt_Model.SetWindowText("");
		m_edt_Factory.SetWindowText("");
		m_list_TestItem.DeleteAllItems();
		m_nSaveState = 0;
		UpdateSaveState(m_nSaveState);
		
		m_edt_Name.ShowWindow(SW_HIDE);	
		m_edt_Name.ShowWindow(SW_SHOWNORMAL);
		m_edt_Factory.ShowWindow(SW_HIDE);	
		m_edt_Factory.ShowWindow(SW_SHOWNORMAL);
		m_edt_Model.ShowWindow(SW_HIDE);
		m_edt_Model.ShowWindow(SW_SHOWNORMAL);

		CInsDocument* pParent = (CInsDocument*)GetParent();
		pParent->m_dlg_Templete.m_testItem.RemoveAll();
		pParent->m_dlg_Solution.m_testItem.RemoveAll();

		if(m_strModel == "")
			return;
		
		CXml_UUTInfo Xml_UUTInfo1;
		UUTInfoSet stucUUTInfo;
    	Xml_UUTInfo1.ReadUUTBasicInfo(strKind,strModel,&stucUUTInfo);  //读取设备基本信息
    	m_edt_Name.SetWindowText(stucUUTInfo.m_strName);  //设备名称
    	m_edt_Model.SetWindowText(stucUUTInfo.m_strModel); //设备型号
    	m_edt_Factory.SetWindowText(stucUUTInfo.m_strFactory); //设备制造厂

		CArray<UUTItemInfo, UUTItemInfo> rItemInfo;
		Xml_UUTInfo1.ReadUUTItemInfo(strKind, strModel, rItemInfo, m_nUUTItemMax);//读取所有测试项目

		int nIDLittle, nIndex, intline = 0;
		CString strtemp;

		while(rItemInfo.GetSize() > 0)     //填充可用测试项目列表
		{
			nIndex  = 0;
			nIDLittle = rItemInfo[0].nKey;
			if(nIDLittle > m_nUUTItemMax)
				m_nUUTItemMax = nIDLittle;
			for(int j = 1; j < rItemInfo.GetSize(); j++)
			{
				if(rItemInfo[j].nKey < nIDLittle)
				{
					nIDLittle = rItemInfo[j].nKey;
					nIndex = j;
				}
			}
			strtemp.Format("%d", intline + 1);
			m_list_TestItem.InsertItem(intline, strtemp, 0);
			m_list_TestItem.SetItemText(intline, 1, rItemInfo[nIndex].strName);			
			m_list_TestItem.SetItemText(intline, 2, rItemInfo[nIndex].strNote);
			strtemp.Format("Key%d", nIDLittle);
			m_list_TestItem.SetItemText(intline, 3, strtemp);
			m_list_TestItem.SetItemText(intline, 4, rItemInfo[nIndex].strTestType);
			intline++;

			pParent->m_dlg_Templete.m_testItem.Add(rItemInfo[nIndex]);
			pParent->m_dlg_Solution.m_testItem.Add(rItemInfo[nIndex]);
			rItemInfo.RemoveAt(nIndex);
		}
		m_nUUTItemMax1 = m_nUUTItemMax;
	}
	catch (char* e)
	{
		MessageBox(e);		
	}
	m_nSaveState = 1;
	UpdateSaveState(m_nSaveState);
}

void CInsDocBasic::OnRclickListTestItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_strModel == "")
		return;
	if(m_nSaveState != 2)
		return;
	CListInsBasic* pWndList = (CListInsBasic*) &m_list_TestItem;
	ASSERT_VALID(pWndList);

	CPoint point, pointList;
	point.x = -1;
	point.y = -1;
	GetCursorPos(&point);
	pointList = point;
	CString str1;
	int nType = 1;
	m_nSeleteIndex = -1;

	if (point != CPoint(-1, -1))
	{
		pWndList->ScreenToClient(&pointList); 
		LVHITTESTINFO lvinfo;
		lvinfo.pt = pointList;
		lvinfo.flags = LVHT_ABOVE;    
		int nItem = pWndList->SubItemHitTest(&lvinfo);
		if(nItem != -1)
			m_nSeleteIndex = lvinfo.iItem;
		pWndList->SetFocus();
	}

	if(m_nSeleteIndex != -1)
		nType = 0;
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_INS_BASIC));

	CMenu* pPopup = menu.GetSubMenu(nType);
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}

void CInsDocBasic::OnMenuInsBasicDel()
{
	DelTestItem();
}

void CInsDocBasic::OnMenuInsBasicNew() 
{
	OnButtonAddTestItem();
}

void CInsDocBasic::OnButtonSaveTestItem() 
{
	if(m_nSaveState == 1)
	{
		m_nSaveState = 2;
		UpdateSaveState(m_nSaveState);
	}
	else if(m_nSaveState == 2)
	{
		CArray<UUTItemInfo, UUTItemInfo> strTestItemArray;
		UUTItemInfo tstItm;
		int nInsertType, nI = m_list_TestItem.GetItemCount();
		CString str1;

		for(int i = 0; i < nI; i++)
		{
			str1 = m_list_TestItem.GetItemText(i, 3);
			str1 = str1.Right(str1.GetLength() - 3);
			tstItm.nKey = atoi(str1);
			tstItm.strName = m_list_TestItem.GetItemText(i, 1);
			tstItm.strNote = m_list_TestItem.GetItemText(i, 2);
			tstItm.strTestType = m_list_TestItem.GetItemText(i, 4);
			if(tstItm.strTestType != "Control")
				tstItm.strTestType = "Test";
			if(tstItm.strName == "")
			{
				for(int k = 0; k < m_list_TestItem.GetItemCount(); k++)
					m_list_TestItem.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
				
				m_list_TestItem.EnsureVisible(i, TRUE);
				m_list_TestItem.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
				
				str1.Format("第%d行的可测试项目为空!!!", i + 1);
				AfxMessageBox(str1);
				return;
			}

			nInsertType = 1;
			for(int j = 0; j < strTestItemArray.GetSize(); j++)
			{
				if(strTestItemArray[j].nKey > tstItm.nKey)
				{
					strTestItemArray.InsertAt(j, tstItm);
					nInsertType = 0;
					break;
				}
				else if(strTestItemArray[j].nKey == tstItm.nKey)
				{
					for(int k = 0; k < m_list_TestItem.GetItemCount(); k++)
						m_list_TestItem.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
				
					m_list_TestItem.EnsureVisible(i, TRUE);
					m_list_TestItem.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);

					str1.Format("第%d行的Key与其他行重复!!!", i + 1);
					AfxMessageBox(str1);
					return;
				}
			}
			if(nInsertType)
				strTestItemArray.Add(tstItm);
		}

		CXml_UUTInfo Xml_UUTInfo1;
		Xml_UUTInfo1.WriteUUTItemInfo(m_strKind, m_strModel, strTestItemArray, m_nUUTItemMax1);//保存所有测试项目
		UpdateBasicInfo(m_strKind, m_strModel);

		CInsDocument* pParent = (CInsDocument*)GetParent();
		pParent->m_dlg_Templete.UpdataTempleteCom(m_strKind, m_strModel);
		pParent->m_dlg_Solution.initAll(m_strKind, m_strModel);
		m_nSaveState = 1;
		UpdateSaveState(m_nSaveState);
	}
}

void CInsDocBasic::OnButtonAddTestItem() 
{
	int nIndex = m_list_TestItem.GetItemCount();
	int nI = 1;
	if(nIndex > 0)
		nI = atoi(m_list_TestItem.GetItemText(nIndex - 1, 0)) + 1;
	CString str1;
	str1.Format("%d", nI);
	m_list_TestItem.InsertItem(nIndex, str1);
	m_nUUTItemMax1 = m_nUUTItemMax1 + 1;
	str1.Format("Key%d", m_nUUTItemMax1);
	m_list_TestItem.SetItemText(nIndex, 3, str1);
	m_list_TestItem.EnsureVisible(nIndex, TRUE);
	for(int i = 0; i < nIndex; i++)
		m_list_TestItem.SetItemState(i, 0,LVIS_SELECTED|LVIS_FOCUSED);
	m_list_TestItem.SetItemState(nIndex, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
}

void CInsDocBasic::OnButtonDelTestItem() 
{
	m_nSeleteIndex = m_list_TestItem.GetSelectionMark();
	DelTestItem();
}

void CInsDocBasic::DelTestItem()
{
	if(m_nSeleteIndex < 0)
	{
		AfxMessageBox("未选中测试项目,请重新选择!");
		return;
	}
	CString strKey = m_list_TestItem.GetItemText(m_nSeleteIndex, 3);
	int nLen = strKey.GetLength();
	if(nLen > 3)
	{
		int nI = atoi(strKey.Right(nLen - 3));
		if(nI > m_nUUTItemMax && nI == m_nUUTItemMax1)
			m_nUUTItemMax1--;
	}
	m_list_TestItem.DeleteItem(m_nSeleteIndex);
	nLen = m_list_TestItem.GetItemCount();
	for(int i = 0; i < nLen; i++)
		m_list_TestItem.SetItemState(i, 0,LVIS_SELECTED|LVIS_FOCUSED);
	m_list_TestItem.SetSelectionMark(-1);
}

void CInsDocBasic::UpdateSaveState(int nSaveState)
{
	switch(nSaveState)
	{
	case 1:
		m_btn_SaveTestItem.SetWindowText("修改");
		m_btn_SaveTestItem.EnableWindow(TRUE);
		m_btn_Add_TestItem.EnableWindow(FALSE);
		m_btn_Del_TestItem.EnableWindow(FALSE);
		break;
	case 2:
		m_btn_SaveTestItem.SetWindowText("保存");
		m_btn_SaveTestItem.EnableWindow(TRUE);
		m_btn_Add_TestItem.EnableWindow(TRUE);
		m_btn_Del_TestItem.EnableWindow(TRUE);
		break;
	default:
		m_btn_SaveTestItem.SetWindowText("修改");
		m_btn_SaveTestItem.EnableWindow(FALSE);
		m_btn_Add_TestItem.EnableWindow(FALSE);
		m_btn_Del_TestItem.EnableWindow(FALSE);
		break;
	}
}
