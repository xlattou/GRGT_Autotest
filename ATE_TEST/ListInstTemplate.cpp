// ListInstTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "ListInstTemplate.h"
#include "InsDocTemplete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListInstTemplate

CListInstTemplate::CListInstTemplate()
{
	m_nEditItem = 0;
	m_nEditSubItem = 0;
	m_strEditText = "";
	m_bIgnore = true;
}

CListInstTemplate::~CListInstTemplate()
{
}


BEGIN_MESSAGE_MAP(CListInstTemplate, CListCtrlCl)
	//{{AFX_MSG_MAP(CListInstTemplate)
		ON_EN_SETFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnSetfocusEdit)	
		ON_EN_KILLFOCUS(IDC_EDIT_INSBASIC_LIST_CUSTOM, OnKillfocusEdit)
		ON_CBN_SETFOCUS(IDC_COMBO_INSTEMPLATE_LIST_CUSTOM, OnSetfocusCombo)
		ON_CBN_KILLFOCUS(IDC_COMBO_INSTEMPLATE_LIST_CUSTOM, OnKillfocusCombo)
		ON_WM_LBUTTONDBLCLK()
		ON_CBN_SELCHANGE(IDC_COMBO_INSTEMPLATE_LIST_CUSTOM, OnSelchangeComboItem)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListInstTemplate::PreSubclassWindow()
{
	m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,
		CRect(0,40,10,50),this, IDC_EDIT_INSBASIC_LIST_CUSTOM);
	m_Edit.SetParent(this);
	m_Edit.ShowWindow(SW_HIDE);
	
	m_combo.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_VISIBLE,
		CRect(0,40,10,60),this, IDC_COMBO_INSTEMPLATE_LIST_CUSTOM);
	m_combo.SetParent(this);
	m_combo.ShowWindow(SW_HIDE);
	
	CListCtrlCl::PreSubclassWindow();
}

void CListInstTemplate::OnSetfocusEdit()
{
	m_bIgnore = false;
	m_Edit.SetWindowText(m_strEditText);
}

void CListInstTemplate::OnKillfocusEdit() 
{
	if(m_bIgnore)
		return;
	m_Edit.GetWindowText(m_strEditText);
	CString str1 = GetItemText(m_nEditItem, m_nEditSubItem);
	if(str1 != m_strEditText)
	{
		SetItemText(m_nEditItem, m_nEditSubItem, m_strEditText);
		((CInsDocTemplete*)GetParent())->ChangeItem(m_nEditItem, m_nEditSubItem);//修改测试项目
	}
	m_Edit.ShowWindow(SW_HIDE);
}

void CListInstTemplate::OnSetfocusCombo()
{
	//if(m_combo.GetCount() > 0)
		m_combo.SetCurSel(-1);
}

void CListInstTemplate::OnKillfocusCombo() 
{
	m_combo.ShowWindow(SW_HIDE);
}

void CListInstTemplate::OnSelchangeComboItem()
{
	if(m_combo.GetCount() == m_testItem.GetSize())
	{
		int nI = m_combo.GetCurSel();
		if(nI >= 0)
			((CInsDocTemplete*)GetParent())->AddNewItem(nI, m_nEditItem);//增加新的测试项目
	}
	m_combo.ShowWindow(SW_HIDE);	
}

void CListInstTemplate::OnLButtonDblClk(UINT nHitTest, CPoint point) 
{	
	CListCtrlCl::OnLButtonDblClk(nHitTest, point);

	if(((CInsDocTemplete*)GetParent())->m_nChangeState != 2)
		return;
	LVHITTESTINFO lvhti;
	
	lvhti.pt = point;
	lvhti.flags=LVHT_ONITEMLABEL;
	this->SubItemHitTest(&lvhti);
	m_nEditItem = lvhti.iItem;
	m_nEditSubItem = lvhti.iSubItem;
	
	if (lvhti.flags & LVHT_ONITEMLABEL)
	{
		if(((m_nEditSubItem == 3 || m_nEditSubItem == 4 || m_nEditSubItem == 5 || m_nEditSubItem == 6) && GetItemText(m_nEditItem, 2) != "Control")
			|| ((m_nEditSubItem == 1 || (m_nEditSubItem == 7 && GetItemText(m_nEditItem, 2) != "Control")) && GetItemText(m_nEditItem, 0) != ""))
		{
			CRect rectCell;
			this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
			m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
			m_Edit.MoveWindow(&rectCell, TRUE);
			m_Edit.SetFocus();
			m_Edit.SetSel(0, -1);
			m_Edit.ShowWindow(SW_SHOW);
		}
		else if(m_nEditSubItem == 2 && GetItemText(m_nEditItem, 2) != "Control")
			((CInsDocTemplete*)GetParent())->SetTestDitional(m_nEditItem);
	}
}

void CListInstTemplate::initTestItemCom()
{
	while(m_combo.DeleteString(0)!=CB_ERR);   //删除模版组合框中的字符串
	CString str1;
	for(int i = 0; i < m_testItem.GetSize(); i++)
	{
		str1.Format("Key%d  ", m_testItem[i].nKey);
		str1 += m_testItem[i].strName + "__" + m_testItem[i].strNote + "  " + m_testItem[i].strTestType;
		m_combo.AddString(str1);
	}
}

void CListInstTemplate::AddAllLine(int nListSelectItem)
{
	m_nEditItem = nListSelectItem;
	CRect rectCell, rec1;
	int nI;
	if(m_nEditItem < 0)
	{
		nI = this->GetItemCount();
		if(nI > 0)
			this->GetSubItemRect(nI - 1, 0, LVIR_LABEL, rectCell);
		else
			rectCell = CRect(0, 0, 30, 20);
	}
	else
		this->GetSubItemRect(m_nEditItem, 0, LVIR_LABEL, rectCell);
	this->GetClientRect(rec1);
	CPoint point1 = rectCell.BottomRight();
	point1.y += 200;
	point1.x += rec1.Width() - rectCell.Width();
	rectCell.SetRect(rectCell.TopLeft(), point1);
	m_combo.MoveWindow(&rectCell, TRUE);
	m_combo.SetFocus();
	m_combo.SetCurSel(0); 
	m_combo.ShowWindow(SW_SHOW);
}

void CListInstTemplate::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Edit.ShowWindow(SW_HIDE);
	m_combo.ShowWindow(SW_HIDE);
	CListCtrlCl::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CListInstTemplate::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			if(GetFocus() == GetDlgItem(IDC_EDIT_INSBASIC_LIST_CUSTOM))
			{
				OnKillfocusEdit();
				if(m_nEditSubItem == 3)
				{
					m_nEditSubItem++;
					
					CRect rectCell;
					this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
					m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
					m_Edit.MoveWindow(&rectCell, TRUE);
					m_Edit.SetFocus();
					m_Edit.SetSel(0, -1);
					m_Edit.ShowWindow(SW_SHOW);
				}
				else if(m_nEditSubItem == 4)
				{
					m_nEditItem++;
					if(m_nEditItem < GetItemCount())
					{
						for(int k = 0; k < GetItemCount(); k++)
							SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
							
						EnsureVisible(m_nEditItem, TRUE);
						SetItemState(m_nEditItem, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);

						m_nEditSubItem--;				
						CRect rectCell;
						this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
						m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
						m_Edit.MoveWindow(&rectCell, TRUE);
						m_Edit.SetFocus();
						m_Edit.SetSel(0, -1);
						m_Edit.ShowWindow(SW_SHOW);
					}
				}
				else if(m_nEditSubItem == 5)
				{
					m_nEditItem++;
					if(m_nEditItem < GetItemCount())
					{
						for(int k = 0; k < GetItemCount(); k++)
							SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
						
						EnsureVisible(m_nEditItem, TRUE);
						SetItemState(m_nEditItem, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
						
						CRect rectCell;
						this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
						m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
						m_Edit.MoveWindow(&rectCell, TRUE);
						m_Edit.SetFocus();
						//m_Edit.SetSel(0, -1);
						m_Edit.ShowWindow(SW_SHOW);
					}
				}
				else if(m_nEditSubItem == 6)
				{
					m_nEditItem++;
					if(m_nEditItem < GetItemCount())
					{
						for(int k = 0; k < GetItemCount(); k++)
							SetItemState(k, 0,LVIS_SELECTED|LVIS_FOCUSED);
						
						EnsureVisible(m_nEditItem, TRUE);
						SetItemState(m_nEditItem, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
						
						CRect rectCell;
						this->GetSubItemRect(m_nEditItem, m_nEditSubItem, LVIR_LABEL, rectCell);
						m_strEditText = this->GetItemText(m_nEditItem, m_nEditSubItem);
						m_Edit.MoveWindow(&rectCell, TRUE);
						m_Edit.SetFocus();
						int nI = m_strEditText.GetLength();
						int nI1 = m_strEditText.Find(':');
						m_Edit.SetSel(nI1+1, nI);
						m_Edit.ShowWindow(SW_SHOW);
					}
				}
				return TRUE;
			}
		}
		else if(pMsg->wParam==VK_DELETE)
		{
			CInsDocTemplete* pPar = (CInsDocTemplete*)GetParent();
			if(pPar->m_nChangeState != 2)
				return TRUE;
			CWnd * pWnd1 = GetFocus();
			if(pWnd1 != GetDlgItem(IDC_EDIT_INSBASIC_LIST_CUSTOM) && pWnd1 != GetDlgItem(IDC_COMBO_INSTEMPLATE_LIST_CUSTOM))
			{
				m_nEditItem = GetSelectionMark();
				pPar->OnCusMenuTempleteDel();
				EnsureVisible(m_nEditItem, TRUE);
				SetItemState(m_nEditItem, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			}
		}
		else if(pMsg->wParam==VK_ESCAPE)
		{
			m_bIgnore = true;
			m_Edit.ShowWindow(SW_HIDE);
			m_combo.ShowWindow(SW_HIDE);
		}
	}
	return CListCtrlCl::PreTranslateMessage(pMsg);
}

BOOL CListInstTemplate::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_Edit.ShowWindow(SW_HIDE);
	m_combo.ShowWindow(SW_HIDE);
	return CListCtrlCl::OnMouseWheel(nFlags, zDelta, pt);
}
