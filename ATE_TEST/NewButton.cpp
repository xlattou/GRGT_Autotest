// NewButton.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "NewButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewButton

CNewButton::CNewButton()
{
	m_IsTimerOn=FALSE;
	m_State=0;
	m_bTrackLeave = 0;
}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	//{{AFX_MSG_MAP(CNewButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewButton message handlers

void CNewButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	
	CButton::PreSubclassWindow();
}

void CNewButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	GetClientRect(&m_Rc);  //�õ���ť���ڵ���Ч��������
	//m_Rc=lpDrawItemStruct->rcItem;
	m_pDC=CDC::FromHandle(lpDrawItemStruct->hDC); //ȡ�ð�ť�ؼ��ͻ�������豸����ָ��
	CDC MemDC;
	MemDC.CreateCompatibleDC(m_pDC);
	CBitmap *pBmp=NULL;
	//	UINT state=lpDrawItemStruct->itemState;
	if(0==m_State)
	{
		pBmp=MemDC.SelectObject(&m_pBmp1);
	}
	else
	{
		pBmp=MemDC.SelectObject(&m_pBmp2);
		
	}
	m_pDC->BitBlt(m_Rc.left,m_Rc.top,m_Rc.right,m_Rc.bottom,&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pBmp);

	
}

void CNewButton::SetImage(int intState)
{
	/*
	CDC MemDC;
	MemDC.CreateCompatibleDC(m_pDC);
	CBitmap *pBmp=NULL;
	//	UINT state=lpDrawItemStruct->itemState;
	if(0==m_State)
	{
		pBmp=MemDC.SelectObject(&m_pBmp1);
	}
	else
	{
		pBmp=MemDC.SelectObject(&m_pBmp2);
		
	}
	m_pDC->BitBlt(m_Rc.left,m_Rc.top,m_Rc.right,m_Rc.bottom,&MemDC,0,0,SRCCOPY);
	*/
}

void CNewButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		m_State=1;
	
	CButton::OnLButtonDown(nFlags, point);
}

void CNewButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		m_State=0;
	
	CButton::OnLButtonUp(nFlags, point);
}

LRESULT CNewButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_State = 0;
	m_bTrackLeave = FALSE;
    InvalidateRect(NULL, FALSE);/**/
	return false;
}

void CNewButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTrackLeave)
	{// ����һ�����봰��ʱ�� ����һ��WM_MOUSELEAVE ��Ϣ
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		m_bTrackLeave = TRUE;
	}
	
	CButton::OnMouseMove(nFlags, point);
}
