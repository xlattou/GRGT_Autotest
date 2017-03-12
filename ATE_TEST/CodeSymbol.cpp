// CodeSymbol.cpp : implementation file
//

#include "stdafx.h"
#include "CodeSymbol.h"
#include "ate_test.h"
#include "TESTLUA.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeSymbol

CCodeSymbol::CCodeSymbol()
{
	m_bachColor = RGB(236,233,216);
	m_ColorText = RGB(43,145,175);
	m_nScreenPosV = 0;
}

CCodeSymbol::~CCodeSymbol()
{
	DeleteObject(m_penRed);
	DeleteObject(m_penGreen);
	DeleteObject(m_brushRed);
	DeleteObject(m_brushGreen);
}


BEGIN_MESSAGE_MAP(CCodeSymbol, CStatic)
	//{{AFX_MSG_MAP(CCodeSymbol)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeSymbol message handlers

void CCodeSymbol::OnPaint() 
{
	CPaintDC dc(this);

	CRect rectCtrl;
	GetClientRect (&rectCtrl);
	CMemDC memDC(&dc, &rectCtrl);
	DrawSymbol(memDC);
}

void CCodeSymbol::DrawSymbol(CDC* pDC)
{
	FillBackGround(pDC);
	DrawCodeSymbol(pDC);
}

void CCodeSymbol::FillBackGround(CDC* pDC)
{
	CRect rect1;
	GetClientRect(rect1);
	pDC->FillSolidRect(rect1, m_bachColor);

}
void CCodeSymbol::DrawCodeSymbol(CDC* pDC)
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_ColorText);
	TESTLUA* pParent = (TESTLUA*)GetParent();
	CString str1;
	CRect rectSymbol(0, 3 - m_nScreenPosV, 25, 15 - m_nScreenPosV);
	CRect rectEclipse1, rectEclipse(30, 3 - m_nScreenPosV, 44, 17);
	rectEclipse1 = rectEclipse;
	CPoint points[10];
	points[0].x = 28;
	points[0].y = 7 - m_nScreenPosV;
	points[1].x = 44;
	points[1].y = points[0].y;
	points[2].x = 47;
	points[2].y = 10 - m_nScreenPosV;
	points[3].x = 44;
	points[3].y = 13 - m_nScreenPosV;
	points[4].x = 28;
	points[4].y = points[3].y;

	points[5] = points[0];
	points[6] = points[1];
	points[7] = points[2];
	points[8] = points[3];
	points[9] = points[4];

	for(int i = 0; i < pParent->m_CodeInfo_Array.GetSize(); i++)
	{
		pDC->SelectObject(m_font);
		str1.Format("%d", i + 1);
		pDC->DrawText(str1, rectSymbol, /*DT_VCENTER | DT_SINGLELINE | TA_RIGHT*/TA_CENTER);
		rectSymbol.top += 20;
		rectSymbol.bottom += 20;

		if(pParent->m_CodeInfo_Array[i].bIsBreak)
		{
			rectEclipse1.top = rectEclipse.top + 20 * i;
			rectEclipse1.bottom = rectEclipse1.top + 14;
			
			pDC->SelectObject(m_penRed);
			pDC->SelectObject(m_brushRed);
			pDC->Ellipse(rectEclipse1);
		}
		
		if(pParent->m_CodeInfo_Array[i].bIsDebug)
		{
			points[5].y = points[0].y + 20 * i;
			points[6].y = points[5].y;
			points[7].y = points[6].y + 3;
			points[8].y = points[7].y + 3;
			points[9].y = points[8].y;
			pDC->SelectObject(m_penGreen);
			pDC->SelectObject(m_brushGreen);		
			pDC-> Polygon(points + 5, 5);
		}
	}
}

void CCodeSymbol::PreSubclassWindow() 
{
	LOGFONT logfnt;
	logfnt.lfCharSet = ANSI_CHARSET;//DEFAULT_CHARSET;//;GB2312_CHARSET
	logfnt.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfnt.lfEscapement = 0;	
	logfnt.lfHeight = 14;
	logfnt.lfItalic = false;
	logfnt.lfOrientation = 0;
	logfnt.lfPitchAndFamily = FF_SWISS,//DEFAULT_PITCH | FF_DONTCARE;//;
		logfnt.lfQuality = DEFAULT_QUALITY;
	logfnt.lfStrikeOut = false;
	logfnt.lfUnderline = false;
	logfnt.lfWeight = 0;
	logfnt.lfWidth = 0;
	logfnt.lfOutPrecision = OUT_DEFAULT_PRECIS;
	
	m_font.CreateFontIndirect(&logfnt);
	
	m_penRed.CreatePen(PS_SOLID,1,RGB(168,0,0));
	m_penGreen.CreatePen(PS_SOLID,1,RGB(20,128,36));
	m_brushRed.CreateSolidBrush(RGB(168,0,0));
	m_brushGreen.CreateSolidBrush(RGB(20,128,36));

	CStatic::PreSubclassWindow();
}

BOOL CCodeSymbol::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
	return CStatic::OnEraseBkgnd(pDC);
}

void CCodeSymbol::setScreenPoseV(int npose)
{
	m_nScreenPosV = (npose - 1) * 20;
}

void CCodeSymbol::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetClassLong(this->GetSafeHwnd(), GCL_HCURSOR, (LONG)LoadCursor(NULL , IDC_HAND));//??¡À?¨º¨®¡À¨º
	//HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
	//::SetCursor(hCur);	
	CStatic::OnMouseMove(nFlags, point);
}
