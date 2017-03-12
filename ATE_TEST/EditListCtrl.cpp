// EditListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "EditListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl

CEditListCtrl::CEditListCtrl()
{
	m_iItem  = -1;
	m_iSubItem  = -1;
	m_bFocus  = FALSE;
	m_bHighLight = FALSE;
}
CEditListCtrl::~CEditListCtrl()
{
}
BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CEditListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl message handlers
void CEditListCtrl::OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW *pNMLVCustomDraw = (NMLVCUSTOMDRAW*) pNMHDR;
	
	*pResult = CDRF_DODEFAULT; //NULL
	if ( pNMLVCustomDraw->nmcd.dwDrawStage ==  CDDS_PREPAINT )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if( pNMLVCustomDraw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( pNMLVCustomDraw->nmcd.dwDrawStage == (CDDS_SUBITEM | CDDS_ITEMPREPAINT))
	{
		int iItem = (int)pNMLVCustomDraw->nmcd.dwItemSpec;
		int iSubItem =  pNMLVCustomDraw->iSubItem;
		CDC *pDC = CDC::FromHandle(pNMLVCustomDraw->nmcd.hdc);
		CString strItemText = GetItemText(iItem, iSubItem);
		CRect rcItem, rcText;
		GetSubItemRect(iItem, iSubItem, LVIR_LABEL, rcItem);
		rcText = rcItem;
		CSize size = pDC->GetTextExtent(strItemText);
		if (strItemText == _T(""))
		{
			size.cx = 41;
		}
		//设置文本高亮矩形
		rcText.left += 4;
		rcText.right = rcText.left + size.cx + 6;
		if ( rcText.right > rcItem.right )
		{
			rcText.right = rcItem.right;
		}
		COLORREF crOldTextColor = pDC->GetTextColor();
		if ( m_bFocus )
		{
			if ( (m_iItem == iItem) && (m_iSubItem == iSubItem))
			{
				if ( m_bHighLight )
				{
					pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
					pDC->FillSolidRect(&rcText, ::GetSysColor(COLOR_HIGHLIGHT));
				}
				pDC->DrawFocusRect(&rcText);
			}
		}
		rcItem.left += 6;
		pDC->DrawText(strItemText, &rcItem,  DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOCLIP);
		pDC->SetTextColor(crOldTextColor);
		*pResult = CDRF_SKIPDEFAULT;
	}
}
void CEditListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bFocus = TRUE;
	LVHITTESTINFO	lvhit;
	lvhit.pt = point;
	int item = SubItemHitTest(&lvhit);
	
	if ( item != -1 && (lvhit.flags & LVHT_ONITEM))
	{
		CListCtrl::OnLButtonDown(nFlags, point);
		if ( m_bHighLight && m_iItem == lvhit.iItem && m_iSubItem == lvhit.iSubItem )
		{
			//第二次单击
			EditLabel(m_iItem);
			return;
		}
		else
		{
			//第一次单击
			m_iItem = lvhit.iItem;
			m_iSubItem = lvhit.iSubItem;
			m_bHighLight = TRUE;
		}
	}
	else
	{
		if ( m_edtItemEdit.m_hWnd == NULL)
		{
			m_bHighLight = FALSE;
		}
		CListCtrl::OnLButtonDown(nFlags, point);
	}
	Invalidate();
}
void CEditListCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( m_iSubItem >= 0)
	{
		ASSERT(m_iItem == pDispInfo->item.iItem);
		CRect rcSubItem;
		GetSubItemRect(pDispInfo->item.iItem, m_iSubItem, LVIR_BOUNDS, rcSubItem);
		HWND hWnd = (HWND) SendMessage(LVM_GETEDITCONTROL); 
		ASSERT( hWnd != NULL);
		VERIFY(m_edtItemEdit.SubclassWindow(hWnd));
		m_edtItemEdit.m_iXPos = rcSubItem.left + 4;
		m_edtItemEdit.SetWindowText(GetItemText(pDispInfo->item.iItem, m_iSubItem));
	}
	*pResult = 0;
}
void CEditListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM *plvItem = &pDispInfo->item;
	
	if ( m_iSubItem >= 0 )
	{
		if ( plvItem->pszText != NULL )
		{
			SetItemText( plvItem->iItem, m_iSubItem, plvItem->pszText);
		}
		
		VERIFY(m_edtItemEdit.UnsubclassWindow() != NULL);
		*pResult = 0;
	}
	
	CRect rect;
	GetWindowRect(&rect);
	CPoint point;
	::GetCursorPos(&point);
	if ( !rect.PtInRect(point))
	{
		m_iItem = -1;
		m_iSubItem = -1;
		m_bFocus = FALSE;
		m_bHighLight = FALSE;
	}
}
void CEditListCtrl::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CListCtrl::OnPaint() for painting messages
	if ( m_iSubItem >= 0 && m_edtItemEdit.m_hWnd )
	{
		CRect rect;
		CRect rcEdit;
		m_edtItemEdit.GetWindowRect(rcEdit);
		ScreenToClient(rcEdit);
		GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, rect);
		
		if ( rcEdit.right < rect.right)
		{
			rect.left = rcEdit.right;
			CClientDC dc(this);
			dc.FillRect(rect, &CBrush(::GetSysColor(COLOR_WINDOW)));
			ValidateRect(rect);
		}
	}
	CListCtrl::OnPaint();
}
void CEditListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetWindowRect(&rect);
	CPoint point;
	::GetCursorPos(&point);
	if ( !rect.PtInRect(point) && GetParent()->GetFocus() != NULL)
	{
		m_iItem = -1;
		m_iSubItem = -1;
		m_bFocus = FALSE;
		m_bHighLight = FALSE;
		Invalidate();
	}
}
void CEditListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, LVS_EDITLABELS);
	CListCtrl::PreSubclassWindow();
}
