// InsDocTempExcelFrontPage.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTempExcelFrontPage.h"
#include "InsDocTemplete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcelFrontPage dialog


CInsDocTempExcelFrontPage::CInsDocTempExcelFrontPage(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocTempExcelFrontPage::IDD, pParent)
{
	m_bChanged = false;
	m_strXMLArray.RemoveAll();
	m_strXMLArray.Add("Customer");
	m_strXMLArray.Add("Address_Customer");
	m_strXMLArray.Add("InsName");
	m_strXMLArray.Add("InsModel");
	m_strXMLArray.Add("Factory");
	m_strXMLArray.Add("SNumber");
	m_strXMLArray.Add("InsUse");
	m_strXMLArray.Add("Number_Mana");
	m_strXMLArray.Add("CalDate");
	m_strXMLArray.Add("DuaCalDate");
	m_strXMLArray.Add("Result");
	m_strXMLArray.Add("Conclusion");
	m_strXMLArray.Add("CalStation");
	m_strXMLArray.Add("Temperature");
	m_strXMLArray.Add("Humidity");
	m_strXMLArray.Add("Tester");

	m_strNameArray.RemoveAll();
	m_strNameArray.Add("ί�з�");
	m_strNameArray.Add("��ַ");
	m_strNameArray.Add("�豸���� ");
	m_strNameArray.Add("�ͺ�/���");
	m_strNameArray.Add("���쳧");
	m_strNameArray.Add("�������");
	m_strNameArray.Add("�豸��;");
	m_strNameArray.Add("������");
	m_strNameArray.Add("У׼����");
	m_strNameArray.Add("���鸴У����");
	m_strNameArray.Add("У׼����(����˵��)");
	m_strNameArray.Add("У׼���(�Ƿ�ϸ�)");
	m_strNameArray.Add("У׼�ص�");
	m_strNameArray.Add("�¶�");
	m_strNameArray.Add("���ʪ��");
	m_strNameArray.Add("У׼��");
}


void CInsDocTempExcelFrontPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocTempExcelFrontPage)
	DDX_Control(pDX, IDC_EDIT_EXCEL_FRONT_PAGE, m_edt_Page);
	DDX_Control(pDX, IDC_LIST_EXCEL_FRONT_PAGE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocTempExcelFrontPage, CDialog)
	//{{AFX_MSG_MAP(CInsDocTempExcelFrontPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsDocTempExcelFrontPage message handlers

BOOL CInsDocTempExcelFrontPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);
	m_List.InsertColumn(0, "����", LVCFMT_CENTER, 200);
	m_List.InsertColumn(1, "�к�", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "�к�", LVCFMT_LEFT, 100);

	for (int i = 0; i < m_strNameArray.GetSize(); i++)
	{
		m_List.InsertItem(i, m_strNameArray[i]);
	}

	m_edt_Page.SetWindowText(m_strSheetNumber);
	for(int i = 0; i < m_vFrontPage.GetSize(); i++)
	{
		for(int j = 0; j < m_strXMLArray.GetSize() && i < m_strNameArray.GetSize();j++)
		{
			if(m_vFrontPage[i].strName == m_strXMLArray[j])
			{
				m_List.SetItemText(i, 1, m_vFrontPage[i].strCol);
				m_List.SetItemText(i, 2, m_vFrontPage[i].strRow);
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocTempExcelFrontPage::OnOK() 
{
	m_vFrontPage.RemoveAll();
	FrontPage fp1;
	for(int i = 0; i < m_List.GetItemCount() && i < m_strXMLArray.GetSize(); i++)
	{
		fp1.strName = m_strXMLArray[i];
		fp1.strCol = m_List.GetItemText(i, 1);
		fp1.strRow = m_List.GetItemText(i, 2);
		if(fp1.strCol == "" || fp1.strRow == "")
		{
			for(int k = 0; k < m_List.GetItemCount(); k++)
			m_List.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
			
			m_List.EnsureVisible(i, TRUE);
			m_List.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);

			AfxMessageBox("����д " + m_strNameArray[i] + " ��Excel" + (fp1.strCol == "" ? "��" : "��") + "��!");
			return;
		}
		for(int j = 0; j < m_vFrontPage.GetSize(); j++)
		{
			if(fp1.strCol == m_vFrontPage[j].strCol && fp1.strRow == m_vFrontPage[j].strRow)
			{
				for(int k = 0; k < m_List.GetItemCount(); k++)
					m_List.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
				
				m_List.EnsureVisible(i, TRUE);
				m_List.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
				
				AfxMessageBox(m_strNameArray[i] + " ��Excel���к������������ظ�,��������д!");
				return;
			}
		}
		m_vFrontPage.Add(fp1);
	}
	
	m_bChanged = true;
	
	CDialog::OnOK();
}
