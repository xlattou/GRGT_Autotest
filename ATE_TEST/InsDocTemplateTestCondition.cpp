// InsDocTemplateTestCondition.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "InsDocTemplateTestCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InsDocTemplateTestCondition dialog


InsDocTemplateTestCondition::InsDocTemplateTestCondition(CWnd* pParent /*=NULL*/)
	: CDialog(InsDocTemplateTestCondition::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsDocTemplateTestCondition)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void InsDocTemplateTestCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsDocTemplateTestCondition)
	DDX_Control(pDX, IDC_LIST_TEMPLATE_TEST_CONDITION, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsDocTemplateTestCondition, CDialog)
	//{{AFX_MSG_MAP(InsDocTemplateTestCondition)
	ON_BN_CLICKED(IDC_BUTTON_MOVEUP, OnButtonMoveup)
	ON_BN_CLICKED(IDC_BUTTON_MOVEDOWN, OnButtonMovedown)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InsDocTemplateTestCondition message handlers

void InsDocTemplateTestCondition::OnOK() 
{
	m_VarSet.RemoveAll();
	PointVarSet varset;
	int nI = m_List.GetItemCount();
	for(int i = 0; i < nI; i++)
	{
		varset.m_strLogicName = m_List.GetItemText(i, 0);
		if(varset.m_strLogicName == "")
		{
			//AfxMessageBox("英文标志不能为空!");
			//m_List.SetSelectionMark(i);
			continue;
		}
		char cFirst = varset.m_strLogicName[0];
		if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
		{
			AfxMessageBox("英文标志首字符不能为符号、数字及空格!");
			m_List.SetSelectionMark(i);
			return;
		}

		varset.m_strName	= m_List.GetItemText(i, 1);
		varset.m_strValue	= m_List.GetItemText(i, 2);
		varset.m_strUnit	= m_List.GetItemText(i, 3);
		if(varset.m_strUnit == "")
		{
			//AfxMessageBox("单位不能为空!");
			//m_List.SetSelectionMark(i);
			continue;
		}
		cFirst = varset.m_strUnit[0];
		if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
		{
			AfxMessageBox("单位首字符不能为符号、数字及空格!");
			m_List.SetSelectionMark(i);
			return;
		}
		m_VarSet.Add(varset);
	}
	m_bChanged = TRUE;
	
	CDialog::OnOK();
}

BOOL InsDocTemplateTestCondition::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwStyle=m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, "英文关键字", LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, "名称", LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, "数值", LVCFMT_CENTER, 80);
	m_List.InsertColumn(3, "单位", LVCFMT_CENTER, 80);
	m_bChanged = false;

	for(int i = 0; i < m_VarSet.GetSize(); i++)
	{
		m_List.InsertItem(i, m_VarSet[i].m_strLogicName);
		m_List.SetItemText(i, 1, m_VarSet[i].m_strName);
		m_List.SetItemText(i, 2, m_VarSet[i].m_strValue);
		m_List.SetItemText(i, 3, m_VarSet[i].m_strUnit);
	}

	for(int i = m_VarSet.GetSize(); i < 9; i++)
	{
		m_List.InsertItem(i, "");
	}

	m_VarSet.RemoveAll();
	return TRUE;
}

BOOL InsDocTemplateTestCondition::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		OnOK();
	return CDialog::PreTranslateMessage(pMsg);
}

void InsDocTemplateTestCondition::OnButtonMoveup() 
{
	int nId = m_List.GetSelectionMark();
	CString str1, str2, str3, str4;
	if(nId > 0)
	{
		str1 = m_List.GetItemText(nId, 0);
		str2 = m_List.GetItemText(nId, 1);
		str3 = m_List.GetItemText(nId, 2);
		str4 = m_List.GetItemText(nId, 3);
		m_List.DeleteItem(nId);
		m_List.InsertItem(nId - 1, str1);
		m_List.SetItemText(nId - 1, 1, str2);
		m_List.SetItemText(nId - 1, 2, str3);
		m_List.SetItemText(nId - 1, 3, str4);
		for(int k = 0; k < m_List.GetItemCount(); k++)
			m_List.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
		
		m_List.EnsureVisible(nId - 1, TRUE);
		m_List.SetItemState(nId - 1, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_List.SetSelectionMark(nId - 1);
	}
}

void InsDocTemplateTestCondition::OnButtonMovedown() 
{
	int nId = m_List.GetSelectionMark();
	CString str1, str2, str3, str4;
	if(nId < m_List.GetItemCount() - 1)
	{
		str1 = m_List.GetItemText(nId, 0);
		str2 = m_List.GetItemText(nId, 1);
		str3 = m_List.GetItemText(nId, 2);
		str4 = m_List.GetItemText(nId, 3);
		m_List.DeleteItem(nId);
		m_List.InsertItem(nId + 1, str1);
		m_List.SetItemText(nId + 1, 1, str2);
		m_List.SetItemText(nId + 1, 2, str3);
		m_List.SetItemText(nId + 1, 3, str4);
		for(int k = 0; k < m_List.GetItemCount(); k++)
			m_List.SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
		
		m_List.EnsureVisible(nId + 1, TRUE);
		m_List.SetItemState(nId + 1, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_List.SetSelectionMark(nId + 1);
	}
	
}

void InsDocTemplateTestCondition::OnButtonDelete() 
{
	int nId = m_List.GetSelectionMark();
	m_List.DeleteItem(nId);
	nId = m_List.GetItemCount();
	m_List.InsertItem(nId, "");
}
