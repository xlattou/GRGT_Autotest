// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "MyTabCtrl.h"
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl()
{
}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_ERASEBKGND() 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

void CMyTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//������ˢ
	//CBrush      cbr;
	//cbr.CreateSolidBrush(TRANSPARENT);
	CBrush *pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	
	//��ȡѡ���������
	char        szTabText[100];
	TC_ITEM     tci;
	memset(szTabText, '\0', sizeof(szTabText));
	tci.mask        = TCIF_TEXT;
	tci.pszText     = szTabText;
	tci.cchTextMax  = sizeof(szTabText)-1;
	GetItem(lpDrawItemStruct->itemID, &tci);

	//���ѡ�����
	CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);
	dc->SetBkMode(TRANSPARENT);
	dc->FillRect(&lpDrawItemStruct->rcItem, pbrush);
	
	//����ѡ�����
	dc->SetBkColor(TRANSPARENT);
	dc->SetTextColor(WHITE);
	RECT rc;
	rc=lpDrawItemStruct->rcItem;
	rc.top+=3;
	dc->DrawText(tci.pszText,lstrlen(tci.pszText),&rc,DT_CENTER);
}

BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//��ȡ�ؼ�����
/*	CRect   rect;
    GetClientRect(&rect);
//	CBrush brush;
//	brush.CreateSolidBrush(RGB(0,100,0));
	
	//������ˢ
	CBrush *brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	//���ؼ�����
	pDC->SetBkMode(TRANSPARENT);
    pDC->FillRect(&rect,brush);
	
	//return CTabCtrl::OnEraseBkgnd(pDC);*/
	return true;
}
