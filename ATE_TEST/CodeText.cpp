// CodeText.cpp : implementation file
//

#include "stdafx.h"
#include "CodeText.h"
#include "ate_test.h"
#include "TESTLUA.h"
#include "MemDC.h"
#include "Ini.h"
#include "Tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeText
CStringArray strLua_SyntaxWordArray;//语法关键字
CStringArray strLua_GlobleFuncWordArray;//全局保留函数关键字
CStringArray strLua_BaseLibFuncWordArray;//基本保留函数关键字
CCodeText::CCodeText()
{
	m_bachColor = RGB(255,255,255);
	m_bachCurserLine = RGB(196,232,253);
	m_nScreenPosH = 0;
	m_nScreenPosV = 0;
	m_bCursorFlash = false;
	m_RectSelect.bottom = m_RectSelect.top = 0;
	m_RectSelect.right = m_RectSelect.left = 0;
	m_pointCursor.x = -1;
	m_pointCursor.y = -1;
	m_rectSelect.left = -1;
	m_rectSelect.right = -1;
	m_rectSelect.top = -1;
	m_rectSelect.bottom = -1;
	m_bMoveSelect = false;
	m_bLeftMouseDown = false;
	m_bTrackLeave = 0;
}

CCodeText::~CCodeText()
{
}


BEGIN_MESSAGE_MAP(CCodeText, CStatic)
	//{{AFX_MSG_MAP(CCodeText)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_COMMAND(IDR_CODE_COPY, OnCodeCopy)
	ON_COMMAND(IDR_CODE_CUT, OnCodeCut)
	ON_COMMAND(IDR_CODE_PASTE, OnCodePaste)
	ON_COMMAND(IDR_CODE_DELETE, OnCodeDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeText message handlers

void CCodeText::PreSubclassWindow() 
{
	LOGFONT logfnt;
	logfnt.lfCharSet = GB2312_CHARSET;
	logfnt.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfnt.lfEscapement = 0;	
	logfnt.lfHeight = 16;
	logfnt.lfItalic = false;
	logfnt.lfOrientation = 0;
	logfnt.lfPitchAndFamily = FF_SWISS,//DEFAULT_PITCH | FF_DONTCARE;//;
		logfnt.lfQuality = DEFAULT_QUALITY;
	logfnt.lfStrikeOut = false;
	logfnt.lfUnderline = false;
	logfnt.lfWeight = 0;
	logfnt.lfWidth = 0;
	logfnt.lfOutPrecision = OUT_DEFAULT_PRECIS;
//	strcpy(logfnt.lfFaceName, "微软雅黑");
	m_font.CreateFontIndirect(&logfnt);
	
	m_brushBlack.CreateSolidBrush(RGB(255,255,255));
	m_PenCursor.CreatePen(PS_SOLID,1,RGB(0,0,0));
	
	m_ColorBlue = RGB(0, 0, 220);//蓝色，语法关键字
	m_ColorDark = RGB(0, 0, 100);//青色，变量	
	m_ColorGreen = RGB(0, 128, 0);//绿色，注解
	m_ColorRed = RGB(255, 0, 0);//红色，全局保留函数关键字
	m_ColorShallowRed = RGB(255, 50, 50);//淡红色，基本保留函数关键字
	m_ColorDarkRed = RGB(128, 0, 0);//暗红色，函数名
	m_ColorGray = RGB(128, 128, 128);//灰色，响应函数
	m_ColorBlack = RGB(0, 0, 0);//黑色，符号，数字，其他
	m_ColorWhite = RGB(255, 255, 255);
	m_ColorDarkYellow = RGB(128, 128, 0);//暗黄色, 标点符号
	m_ColorCarmine = RGB(255, 0, 255);//洋红色,用于引号
	m_ColorShallowBlue = RGB(60, 80, 240);//蓝色，语法

	char* s=new char[MAX_PATH];    
	if(!GetModuleFileName(NULL,s,MAX_PATH))
	{
		AfxMessageBox("获取Lua脚本关键字配置失败!");
		delete []s;
		return;
	}
    (_tcsrchr(s,_T('\\')))[0] = 0;  //去掉ATE_TEST.exe
	CString strPath(s);
	delete[] s;
	strPath += "\\LUA脚本的关键字配置表.ini";

	strLua_SyntaxWordArray.RemoveAll();
	strLua_GlobleFuncWordArray.RemoveAll();
	strLua_BaseLibFuncWordArray.RemoveAll();
	CIni ini1;
	ini1.SetINIPth(strPath);
	ini1.GetKeys(strLua_SyntaxWordArray, "Lua_SyntaxWord");
	ini1.GetKeys(strLua_GlobleFuncWordArray, "Lua_GlobleFuncWord");
	ini1.GetKeys(strLua_BaseLibFuncWordArray, "Lua_BaseLibFuncWord");

	SetTimer(1, 500, NULL);
	//SetClassLong(this->GetSafeHwnd(), GCL_HCURSOR, (LONG)LoadCursor(NULL , IDC_IBEAM));//改变鼠标
	CStatic::PreSubclassWindow();
}

void CCodeText::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rectCtrl;
	GetClientRect (&rectCtrl);
	CMemDC memDC(&dc, &rectCtrl);
	DrawText(memDC);
}

void CCodeText::DrawText(CDC* pDC)
{
	FillBackGround_DrawCodeText(pDC);
}

void CCodeText::FillBackGround_DrawCodeText(CDC* pDC)
{
	CRect rect1;//刷背景
	GetClientRect(rect1);
	pDC->FillSolidRect(rect1, m_bachColor);
	
	TESTLUA* pParent = (TESTLUA*)GetParent();//绘制文字
	CString str1;
	CRect rectText(0 - m_nScreenPosH, 0 - m_nScreenPosV, 1000, 20);
	m_bIsNoted = false;
	int nL, nL1, nLenCode;
	nL = nL1 = 0;
	nLenCode = pParent->m_CodeInfo_Array.GetSize();
	for(int i = 0; i < nLenCode; i++)
	{
		pDC->SelectObject(m_font);
		nL = DrawTextWithBlank(pDC, pParent->m_CodeInfo_Array[i].strCode, rectText);
		rectText.top += 20;
		rectText.bottom += 20;
		if(nL > nL1)
			nL1 = nL;
	}

	//绘制鼠标闪烁
	if(m_pointCursor.y >= 0)//绘制行背景
	{
		/*CRect Rect2;
		Rect2.top = m_pointCursor.y;
		Rect2.bottom = m_pointCursor.y + 20;
		Rect2.left = rect1.left;
		Rect2.left = rect1.right;
		pDC->FillSolidRect(Rect2, m_bachCurserLine);*/
		pDC->SetBkColor(m_bachCurserLine);
		rectText.top = m_pointCursor.y;//重绘当前行字符
		rectText.bottom = m_pointCursor.y + 20;
		DrawTextWithBlank(pDC, pParent->m_CodeInfo_Array[(rectText.top + m_nScreenPosV / 2) / 20].strCode, rectText);
		//绘制鼠标闪烁
		if(GetFocus() == this)
		{
			if(m_bCursorFlash)
			{
				if(m_pointCursor.x >= 0)
				{
					CPoint point1;
					point1.x = m_pointCursor.x;
					point1.y = m_pointCursor.y + 20;
					pDC->SelectObject(m_PenCursor);//绘制鼠标闪烁
					pDC->MoveTo(m_pointCursor);
					pDC->LineTo(point1);
				}
			}

		}
	}

	//绘制选中文本
	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
	{
		int nL;
		CPoint pos1, pos2;
		if(m_rectSelect.bottom > m_rectSelect.top)
		{
			pos1.x = m_rectSelect.left;
			pos1.y = m_rectSelect.top;
			pos2.x = m_rectSelect.right;
			pos2.y = m_rectSelect.bottom;
		}
		else if(m_rectSelect.bottom < m_rectSelect.top)
		{
			pos1.x = m_rectSelect.right;
			pos1.y = m_rectSelect.bottom;
			pos2.x = m_rectSelect.left;
			pos2.y = m_rectSelect.top;
		}
		else if(m_rectSelect.right > m_rectSelect.left)
		{
			pos1.x = m_rectSelect.left;
			pos1.y = m_rectSelect.top;
			pos2.x = m_rectSelect.right;
			pos2.y = m_rectSelect.bottom;
		}
		else
		{
			pos1.x = m_rectSelect.right;
			pos1.y = m_rectSelect.bottom;
			pos2.x = m_rectSelect.left;
			pos2.y = m_rectSelect.top;
		}

		pDC->SetBkColor(m_ColorBlack);
		pDC->SetTextColor(m_ColorWhite);

		if(pos1.y == pos2.y)
		{
			rectText.top = pos1.y * 20 - m_nScreenPosV / 2;
			rectText.bottom = rectText.top + 20;
			rectText.left = pos1.x * 8 - m_nScreenPosH;
			rectText.right = pos2.x * 8 - m_nScreenPosH;
			pDC->FillSolidRect(rectText, m_ColorShallowBlue);
			pDC->DrawText(pParent->m_CodeInfo_Array[pos1.y].strCode.Mid(pos1.x).Left(pos2.x - pos1.x), rectText, DT_VCENTER | DT_SINGLELINE);
		}
		else
		{
			for(int i = pos1.y; i <= pos2.y; i++)
			{	
				rectText.top = 20 * i - m_nScreenPosV / 2;
				rectText.bottom = rectText.top + 20;
				nL = pParent->m_CodeInfo_Array[i].strCode.GetLength();
				if(i == pos1.y)
				{
					rectText.left = pos1.x * 8 - m_nScreenPosH;
					rectText.right = nL * 8 - m_nScreenPosH;
					pDC->FillSolidRect(rectText, m_ColorShallowBlue);
					pDC->DrawText(pParent->m_CodeInfo_Array[i].strCode.Right(nL - pos1.x), rectText, DT_VCENTER | DT_SINGLELINE);
				}
				else if(i == pos2.y)
				{
					rectText.left = - m_nScreenPosH;
					rectText.right = pos2.x * 8 - m_nScreenPosH;
					pDC->FillSolidRect(rectText, m_ColorShallowBlue);
					pDC->DrawText(pParent->m_CodeInfo_Array[i].strCode.Left(pos2.x), rectText, DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					rectText.left = - m_nScreenPosH;
					rectText.right = nL * 8 - m_nScreenPosH;
					pDC->FillSolidRect(rectText, m_ColorShallowBlue);
					pDC->DrawText(pParent->m_CodeInfo_Array[i].strCode, rectText, DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
	}


	nLenCode -= rect1.Height() / 20;
	if(nLenCode < 1)
		nLenCode = 1;
	if(pParent->m_nVScroll != nLenCode)//父窗口
	{
		pParent->m_nVScroll = nLenCode + 1;
		pParent->m_scroll_V.SetScrollRange(1, pParent->m_nVScroll);
	}

	nL1 -= rect1.Width() / 8;
	if(nL1 < 1)
		nL1 = 1;
	if(pParent->m_nHScroll != nL1)//父窗口
	{
		pParent->m_nHScroll = nL1 + 1;
		pParent->m_scroll_H.SetScrollRange(1, pParent->m_nHScroll);
	}
}

BOOL CCodeText::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
	return CStatic::OnEraseBkgnd(pDC);
}

int CCodeText::DrawTextWithBlank(CDC* pDC, CString strText, CRect rec1)
{
	int nLReturn, nL = strText.GetLength();
	nLReturn = nL;
	int nNote, nNote1;
	if(m_bIsNoted)//被--[[ ]]全局注释//这里不允许嵌套
	{
		nNote = strText.Find("]]");
		pDC->SetTextColor(m_ColorGreen);
		if(nNote < 0)//全局注释不在本行结束
		{
			rec1.right = rec1.left + nL * 16;
			pDC->DrawText(strText, rec1, DT_VCENTER | DT_SINGLELINE);
			return nLReturn;
		}
		else//本行结束
		{
			nNote += 2;
			rec1.right = rec1.left + nNote * 16;
			pDC->DrawText(strText.Left(nNote), rec1, DT_VCENTER | DT_SINGLELINE);
			rec1.left = rec1.right;
			nL -= nNote;
			strText = strText.Right(nL);
			m_bIsNoted = false;
		}
	}
	unsigned char chText, chText1;
	nNote = nNote1 = 0;
	for(int i = 0; i < nL -1; i++)//查找--注解
	{
		chText = strText[i];
		if(chText == '"')
			nNote++;
		if(chText == '-')
		{
			chText1 = strText[i + 1];
			if(chText1 == '-')
			{
				if(nNote % 2 == 0)
				{
					pDC->SetTextColor(m_ColorGreen);
					if(nL - i > 3)
					{
						if(strText.Mid(i + 2).Left(2) == "[[")
							m_bIsNoted = true;
					}
					CString str1 = strText.Right(nL - i);
					CRect rec2 = rec1;
					rec2.left = rec1.left + i * 8;
					rec2.right = rec2.left + (nL - i) * 8;
					pDC->DrawText(strText.Right(nL - i), rec2, DT_VCENTER | DT_SINGLELINE);
					if(i == 0)
						return  nLReturn;
					nL = i;
					strText = strText.Left(i);
				}
			}
		}
	}
	int nI = 0;
	bool bBlank = false;//是否在查找空格
	for(int i = 0; i < nL; i++)
	{
		chText = strText[i];
		if(chText >= 0x81 && chText <= 0xF2)//GBK编码
		{
			if(bBlank)//判断是否有空格标志
			{
				if(nI < i)
				{
					nNote = i - nI;
					rec1.right = rec1.left + (nNote) * 8;
					pDC->SetTextColor(m_ColorBlack);
					pDC->DrawText(strText.Mid(nI).Left(nNote), rec1, DT_VCENTER | DT_SINGLELINE);
					rec1.left = rec1.right;
					nI = i;
				}
			}
			if(nL > i + 1)
			{
				chText1 = strText[i + 1];
				if(chText1 >= 0x40)
				{
					i++;
					continue;
				}
			}
		}
		else if(chText <= 0x21 || (chText >= 0x23 && chText <= 0x26) || (chText >= 0x28 && chText <= 0x2F)
			|| (chText >= 0x3A && chText <= 0x40) || (chText >= 0x5B && chText <= 0x5E) || (chText >= 0x7B && chText <= 0x7F))//空格及其他字符
		{
			if(!bBlank)
			{
				bBlank = true;
				nNote = i - nI;
				if(nNote == 0)
					continue;
				rec1.right = rec1.left + (nNote) * 8;
				DrawTextWithKeyword(pDC, strText.Mid(nI).Left(nNote), rec1);
				rec1.left = rec1.right;
				nI = i;
			}
		}
		else//ASCII字符
		{
			if(bBlank)//判断是否有空格标志
			{
				if(nI < i)
				{
					nNote = i - nI;
					rec1.right = rec1.left + (nNote) * 8;
					pDC->SetTextColor(m_ColorDarkYellow);
					pDC->DrawText(strText.Mid(nI).Left(nNote), rec1, DT_VCENTER | DT_SINGLELINE);
					rec1.left = rec1.right;
					nI = i;
					bBlank = false;
				}
				if(chText == 0x22 || chText == 0x27)//单引号或双引号
				{
					nNote1 = strText.Find(chText, i + 1);//查询另一个成对的引号
					if(nNote1 > 0)
					{
						nNote = nNote1 - i + 1;
						rec1.right = rec1.left + (nNote) * 8;
						pDC->SetTextColor(m_ColorCarmine);
						CString str1 = strText.Mid(i).Left(nNote);
						pDC->DrawText(strText.Mid(i).Left(nNote), rec1, DT_VCENTER | DT_SINGLELINE);
						rec1.left = rec1.right;
						nI = nNote1 + 1;
						i  = nNote1;
					}
				}
			}
		}
	}
	//行结束处理
	if(nL > nI)
	{
		nNote = nL - nI;
		rec1.right = rec1.left + (nNote) * 8;
		if(bBlank)
		{
			pDC->SetTextColor(m_ColorDarkYellow);
			pDC->DrawText(strText.Mid(nI).Left(nNote), rec1, DT_VCENTER | DT_SINGLELINE);
		}
		else
			DrawTextWithKeyword(pDC, strText.Mid(nI).Left(nNote), rec1);
	}
	return nLReturn;
}

void CCodeText::DrawTextWithKeyword(CDC* pDC, CString strText, CRect rec1)
{
	for(int i = 0; i < strLua_SyntaxWordArray.GetSize(); i++)//语法关键字
	{
		if(strText == strLua_SyntaxWordArray[i])
		{
			pDC->SetTextColor(m_ColorBlue);
			pDC->DrawText(strText, rec1, DT_VCENTER | DT_SINGLELINE);
			return;
		}
	}

	for(int i = 0; i < strLua_GlobleFuncWordArray.GetSize(); i++)//全局保留函数关键字
	{
		if(strText == strLua_GlobleFuncWordArray[i])
		{
			pDC->SetTextColor(m_ColorRed);
			pDC->DrawText(strText, rec1, DT_VCENTER | DT_SINGLELINE);
			return;
		}
	}

	for(int i = 0; i < strLua_BaseLibFuncWordArray.GetSize(); i++)//基本保留函数关键字
	{
		if(strText == strLua_BaseLibFuncWordArray[i])
		{
			pDC->SetTextColor(m_ColorShallowRed);
			pDC->DrawText(strText, rec1, DT_VCENTER | DT_SINGLELINE);
			return;
		}
	}
	pDC->SetTextColor(m_ColorBlack);
	pDC->DrawText(strText, rec1, DT_VCENTER | DT_SINGLELINE);
}

void CCodeText::setScreenPoseV(int npose)
{
	npose = (npose - 1) * 40;
	m_pointCursor.y -= (npose - m_nScreenPosV) / 2;
	m_nScreenPosV = npose;
}

void CCodeText::setScreenPoseH(int npose)
{
	npose = (npose - 1) * 8;
	m_pointCursor.x -= (npose - m_nScreenPosH);
	m_nScreenPosH = npose;
}

void CCodeText::ChangeCursorFlashState()
{
	m_bCursorFlash = !m_bCursorFlash;
}

LRESULT CCodeText::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTrackLeave = false;
	m_bLeftMouseDown = false;
	return false;
}

void CCodeText::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTrackLeave)
	{// 鼠标第一次移入窗口时， 请求一个WM_MOUSELEAVE 消息
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		m_bTrackLeave = true;
	}

	SetClassLong(this->GetSafeHwnd(), GCL_HCURSOR, (LONG)LoadCursor(NULL , IDC_IBEAM));//改变鼠标
	HCURSOR hCur;
	if(m_bMoveSelect)
		hCur = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	else
	{
		if(m_rectSelect.left < point.x && m_rectSelect.right > point.x && m_rectSelect.top < point.y && m_rectSelect.bottom > point.y)
			hCur = ::LoadCursor(NULL, IDC_ARROW);
		else
			hCur = ::LoadCursor(NULL, IDC_IBEAM);
	}

	if(m_bLeftMouseDown && GetFocus() == this)
	{
		TESTLUA* pParent = (TESTLUA*)GetParent();
		
		if(point.y / 20 + m_nScreenPosV / 40 >= pParent->m_CodeInfo_Array.GetSize())
			return;

		m_pointCursor.x = point.x - point.x % 8;
		m_pointCursor.y = point.y - point.y % 20;
		int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
		m_rectSelect.bottom = nArrayIndex;
		int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8;
		if(nL < m_pointCursor.x + m_nScreenPosH)//结尾之外
			m_pointCursor.x = nL - m_nScreenPosH;
		else if(nL > m_pointCursor.x)//查找当前代码是不是GBK编码
		{
			int nI = (m_pointCursor.x + m_nScreenPosH) / 8;
			if(nI >= 0)
			{
				if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nI - 1) == 1)
				{
					m_pointCursor.x += 8;
					m_rectSelect.right += 1;
				}
			}
		}
		m_rectSelect.right = (m_pointCursor.x + m_nScreenPosH) / 8;
		//AdjustCursor(false);

		CRect rec1;
		GetClientRect(&rec1);
		if(m_pointCursor.x < 8)
			pParent->OnHScrollCus(-1);//向左滚动
		else if(rec1.Width() - m_pointCursor.x < 8)
			pParent->OnHScrollCus(1);//向右滚动
		if(m_pointCursor.y < 20)
			pParent->OnVScrollCus(-1);//向上滚动
		else if(rec1.Height() - m_pointCursor.y < 20)
			pParent->OnVScrollCus(1);//向下滚动
	}
	::SetCursor(hCur);
	CStatic::OnMouseMove(nFlags, point);
}

void CCodeText::OnLButtonDown(UINT nFlags, CPoint point)
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	if(point.y / 20 + m_nScreenPosV / 40 >= pParent->m_CodeInfo_Array.GetSize())
		return;
	m_pointCursor.x = point.x - point.x % 8;
	m_pointCursor.y = point.y - point.y % 20;
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	m_rectSelect.top = nArrayIndex;
	int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8;
	if(nL < m_pointCursor.x + m_nScreenPosH)//结尾之外
	{
		m_pointCursor.x = nL - m_nScreenPosH;
		m_rectSelect.left = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength();
	}
	else if(nL > m_pointCursor.x)//查找当前代码是不是GBK编码
	{
		int nI = (m_pointCursor.x + m_nScreenPosH) / 8;
		m_rectSelect.left = nI;
		if(nI >= 0)
		{
			if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nI - 1) == 1)
			{
				m_pointCursor.x -= 8;
				m_rectSelect.left -= 1;
			}
		}
	}
	SetFocus();
	m_bLeftMouseDown = true;
	m_rectSelect.bottom = m_rectSelect.top;
	m_rectSelect.right = m_rectSelect.left;
	CStatic::OnLButtonDown(nFlags, point);
}

void CCodeText::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLeftMouseDown = false;
	
	CStatic::OnLButtonUp(nFlags, point);
}

void CCodeText::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_pointCursor.x < 0 || m_pointCursor.y < 0)
		return;

	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
		DeleteCharactors_Lines();//假如有选择文件内容,删除该内容

	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nI, nArrayIndex, nL;
	nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	nI = (m_pointCursor.x + m_nScreenPosH) / 8;
	nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength();
	if(nI > nL)
		nI = nL;
	
	CTool tool1;
	CString str1 = tool1.UINTtoString(nChar);
	str1.Replace("\t", "    ");
	pParent->m_CodeInfo_Array[nArrayIndex].strCode.Insert(nI, str1);
	m_pointCursor.x += str1.GetLength() * 8;
	AdjustCursor();
	
	CStatic::OnChar(nChar, nRepCnt, nFlags);
}

void CCodeText::DeleteText()
{
	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
		DeleteCharactors_Lines();
	else
	{
		TESTLUA* pParent = (TESTLUA*)GetParent();
		int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
		int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8 - m_nScreenPosH;
		if(m_pointCursor.x >= nL)
		{
			if(nArrayIndex >= pParent->m_CodeInfo_Array.GetSize())
				return;
			else
			{
				pParent->m_CodeInfo_Array[nArrayIndex].strCode += pParent->m_CodeInfo_Array[nArrayIndex + 1].strCode;
				pParent->m_CodeInfo_Array.RemoveAt(nArrayIndex + 1);
			}
		}
		else
		{
			int nC, nI = (m_pointCursor.x + m_nScreenPosH) / 8;
			if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nI) == 1)
				nC = 2;
			else
				nC = 1;
			pParent->m_CodeInfo_Array[nArrayIndex].strCode.Delete(nI, nC);
		}
	}
	
	AdjustCursor();
}

void CCodeText::DeleteCharactors_Lines()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();

	int nL;
	CPoint pos1, pos2;
	if(m_rectSelect.bottom > m_rectSelect.top)
	{
		pos1.x = m_rectSelect.left;
		pos1.y = m_rectSelect.top;
		pos2.x = m_rectSelect.right;
		pos2.y = m_rectSelect.bottom;
	}
	else if(m_rectSelect.bottom < m_rectSelect.top)
	{
		pos1.x = m_rectSelect.right;
		pos1.y = m_rectSelect.bottom;
		pos2.x = m_rectSelect.left;
		pos2.y = m_rectSelect.top;
	}
	else if(m_rectSelect.right > m_rectSelect.left)
	{
		pos1.x = m_rectSelect.left;
		pos1.y = m_rectSelect.top;
		pos2.x = m_rectSelect.right;
		pos2.y = m_rectSelect.bottom;
	}
	else
	{
		pos1.x = m_rectSelect.right;
		pos1.y = m_rectSelect.bottom;
		pos2.x = m_rectSelect.left;
		pos2.y = m_rectSelect.top;
	}

	if(pos1.y == pos2.y)
	{
		pParent->m_CodeInfo_Array[pos1.y].strCode.Delete(pos1.x, pos2.x - pos1.x);
		m_pointCursor.x = pos1.x * 8 - m_nScreenPosH;
	}
	else
	{
		nL = pParent->m_CodeInfo_Array[pos1.y].strCode.GetLength();
		pParent->m_CodeInfo_Array[pos1.y].strCode = pParent->m_CodeInfo_Array[pos1.y].strCode.Left(pos1.x);
		nL = pParent->m_CodeInfo_Array[pos2.y].strCode.GetLength();
		pParent->m_CodeInfo_Array[pos2.y].strCode = pParent->m_CodeInfo_Array[pos2.y].strCode.Right(nL - pos2.x);

		pParent->m_CodeInfo_Array[pos1.y].strCode += pParent->m_CodeInfo_Array[pos2.y].strCode;

		for(int i = pos1.y + 1; i <= pos2.y; i++)
			pParent->m_CodeInfo_Array.RemoveAt(pos1.y + 1);
	
		m_pointCursor.y = pos1.y * 20 - m_nScreenPosV / 2;
		m_pointCursor.x = pos1.x * 8 - m_nScreenPosH;
	}

	m_rectSelect.bottom = m_rectSelect.top;
	m_rectSelect.right = m_rectSelect.left;
}

void CCodeText::BackspaceText()
{
	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
		DeleteCharactors_Lines();
	else
	{
		TESTLUA* pParent = (TESTLUA*)GetParent();
		int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
		int nL = m_pointCursor.x - m_nScreenPosH;
		if(nL == 0)
		{
			if(nArrayIndex == 0)
				return;
			else
			{
				pParent->m_CodeInfo_Array[nArrayIndex - 1].strCode += pParent->m_CodeInfo_Array[nArrayIndex].strCode;
				pParent->m_CodeInfo_Array.RemoveAt(nArrayIndex);
				
				m_pointCursor.y -= 20;
				m_pointCursor.x = pParent->m_CodeInfo_Array[nArrayIndex - 1].strCode.GetLength() * 8 - m_nScreenPosH;
			}
		}
		else
		{
			int nC, nI = (m_pointCursor.x + m_nScreenPosH) / 8;
			nC = 1;
			if(nI >= 2)
			{
				if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nI - 2) == 1)
					nC = 2;
			}
			pParent->m_CodeInfo_Array[nArrayIndex].strCode.Delete(nI - nC, nC);
			m_pointCursor.x -= 8 * nC;
		}
	}
	AdjustCursor();
}

void CCodeText::HomeText()
{
	m_pointCursor.x = - m_nScreenPosH;
	AdjustCursor();
}

void CCodeText::EndText()
{
	m_pointCursor.x = ((TESTLUA*)GetParent())->m_CodeInfo_Array[m_pointCursor.y / 20 + m_nScreenPosV / 40].strCode.GetLength() * 8 - m_nScreenPosH;
	AdjustCursor();
}

void CCodeText::UpText()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40 - 1;
	if(nArrayIndex < 0)
		return;
	m_pointCursor.y -= 20;
	int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8 - m_nScreenPosH;
	if(m_pointCursor.x >= nL)
		m_pointCursor.x = nL;
	else
	{
		nL = m_pointCursor.x + m_nScreenPosH;
		if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nL / 8 - 1) == 1)
			m_pointCursor.x += 8;
	}
	AdjustCursor();
}
void CCodeText::DownText()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40 + 1;
	if(nArrayIndex >= pParent->m_CodeInfo_Array.GetSize())
		return;
	m_pointCursor.y += 20;
	int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8 - m_nScreenPosH;
	if(m_pointCursor.x >= nL)
		m_pointCursor.x = nL;
	else
	{
		nL = m_pointCursor.x + m_nScreenPosH;
		if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nL / 8 - 1) == 1)
			m_pointCursor.x += 8;
	}
	AdjustCursor();
}
void CCodeText::LeftText()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	if(m_pointCursor.x + m_nScreenPosH == 0)
	{
		if(nArrayIndex == 0)
			return;
		nArrayIndex--;
		m_pointCursor.y -= 20;
		m_pointCursor.x = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8 - m_nScreenPosH;
	}
	else
	{
		int nL = m_pointCursor.x + m_nScreenPosH;
		if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nL / 8 - 1) == 1)
			m_pointCursor.x -= 16;
		else
			m_pointCursor.x -= 8;
	}
	AdjustCursor();
}
void CCodeText::RightText()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8 - m_nScreenPosH;
	if(m_pointCursor.x >= nL)
	{
		nArrayIndex++;
		if(nArrayIndex >= pParent->m_CodeInfo_Array.GetSize())
			return;
		m_pointCursor.y += 20;
		m_pointCursor.x = - m_nScreenPosH;
	}
	else
	{
		nL = (m_pointCursor.x + m_nScreenPosH) / 8;
		if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nL) == 1)
			m_pointCursor.x += 16;
		else
			m_pointCursor.x += 8;
	}
	AdjustCursor();
}


void CCodeText::ReturnText()
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	int nL = (m_pointCursor.x + m_nScreenPosH) / 8;
	codeinfo code1;
	code1.bIsBreak = false;
	code1.bIsDebug = false;
	code1.strCode = pParent->m_CodeInfo_Array[nArrayIndex].strCode.Right(pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() - nL);
	pParent->m_CodeInfo_Array.InsertAt(nArrayIndex + 1, code1);
	pParent->m_CodeInfo_Array[nArrayIndex].strCode = pParent->m_CodeInfo_Array[nArrayIndex].strCode.Left(nL);
	m_pointCursor.x = - m_nScreenPosH;
	m_pointCursor.y += 20;
	AdjustCursor();
}

void CCodeText::AdjustCursor(bool bPointCursorPrew)
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	if(m_pointCursor.x < 0)
	{
		pParent->OnHScrollCus(m_pointCursor.x / 8);//向左滚动
	}
	if(m_pointCursor.y < 0)
	{
		pParent->OnVScrollCus(m_pointCursor.y / 20);//向上滚动
	}
	CRect rec1;
	GetClientRect(&rec1);
	if(m_pointCursor.x > rec1.Width())
	{
		pParent->OnHScrollCus((m_pointCursor.x - rec1.Width()) / 8);//向右滚动
	}
	if(m_pointCursor.x > rec1.Height())
	{
		pParent->OnVScrollCus((m_pointCursor.y - rec1.Height()) / 20);//向上滚动
	}
}

int CCodeText::JudgeGBK(CString str1, int nIndex)
{
	if(nIndex + 1 >= str1.GetLength())
		return 0;
	unsigned char ch1, ch2;
	for(int i = 0; i <= nIndex; i++)
	{
		//if(i + 1 >= str1.GetLength())
		//	return 0;
		ch1 = str1[i];
		ch2 = str1[i + 1];
		if(ch1 >= 0x81 && ch1 <= 0xF2 && ch2 >= 0x40)//GBK编码
		{
			if(i == nIndex)
				return 1;
			i++;
		}
	}
	return 0;
}

void CCodeText::OnKillFocus(CWnd* pNewWnd) 
{
	CStatic::OnKillFocus(pNewWnd);
	
	m_bLeftMouseDown = false;
}

void CCodeText::OnRButtonDown(UINT nFlags, CPoint point) 
{
	TESTLUA* pParent = (TESTLUA*)GetParent();
	if(point.y / 20 + m_nScreenPosV / 40 >= pParent->m_CodeInfo_Array.GetSize())
		return;
	m_pointCursor.x = point.x - point.x % 8;
	m_pointCursor.y = point.y - point.y % 20;
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	int nL = pParent->m_CodeInfo_Array[nArrayIndex].strCode.GetLength() * 8;
	if(nL < m_pointCursor.x + m_nScreenPosH)//结尾之外
	{
		m_pointCursor.x = nL - m_nScreenPosH;
	}
	else if(nL > m_pointCursor.x)//查找当前代码是不是GBK编码
	{
		int nI = (m_pointCursor.x + m_nScreenPosH) / 8;
		if(nI >= 0)
		{
			if(JudgeGBK(pParent->m_CodeInfo_Array[nArrayIndex].strCode, nI - 1) == 1)
				m_pointCursor.x -= 8;
		}
	}

	SetFocus();
	CPoint pos1, pos2;
	if(m_rectSelect.bottom > m_rectSelect.top)
	{
		pos1.x = m_rectSelect.left;
		pos1.y = m_rectSelect.top;
		pos2.x = m_rectSelect.right;
		pos2.y = m_rectSelect.bottom;
	}
	else if(m_rectSelect.bottom < m_rectSelect.top)
	{
		pos1.x = m_rectSelect.right;
		pos1.y = m_rectSelect.bottom;
		pos2.x = m_rectSelect.left;
		pos2.y = m_rectSelect.top;
	}
	else if(m_rectSelect.right > m_rectSelect.left)
	{
		pos1.x = m_rectSelect.left;
		pos1.y = m_rectSelect.top;
		pos2.x = m_rectSelect.right;
		pos2.y = m_rectSelect.bottom;
	}
	else
	{
		pos1.x = m_rectSelect.right;
		pos1.y = m_rectSelect.bottom;
		pos2.x = m_rectSelect.left;
		pos2.y = m_rectSelect.top;
	}

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_CODE_TEXT));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	ClientToScreen(&point);

	int nX = (m_pointCursor.x + m_nScreenPosH) / 8;
	int nY = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	if((pos1.x == pos2.x && pos1.y == pos2.y) || (nY < pos1.y || nY > pos2.y) || (nY == pos1.y && nX < pos1.x) || (nY == pos2.y && nX > pos2.x))
	{
		m_rectSelect.bottom = m_rectSelect.top = m_pointCursor.y;
		m_rectSelect.right = m_rectSelect.left = m_pointCursor.x;
		pPopup->EnableMenuItem(IDR_CODE_CUT,MF_BYCOMMAND|MF_GRAYED);
		pPopup->EnableMenuItem(IDR_CODE_COPY,MF_BYCOMMAND|MF_GRAYED);
		pPopup->EnableMenuItem(IDR_CODE_CUT,MF_BYCOMMAND|MF_GRAYED);
		pPopup->EnableMenuItem(IDR_CODE_DELETE,MF_BYCOMMAND|MF_GRAYED);
	}	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	CStatic::OnRButtonDown(nFlags, point);
}

void CCodeText::OnCodeCopy() 
{
	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
	{	
		CString source;
		TESTLUA* pParent = (TESTLUA*)GetParent();

		int nL;
		CPoint pos1, pos2;
		if(m_rectSelect.bottom > m_rectSelect.top)
		{
			pos1.x = m_rectSelect.left;
			pos1.y = m_rectSelect.top;
			pos2.x = m_rectSelect.right;
			pos2.y = m_rectSelect.bottom;
		}
		else if(m_rectSelect.bottom < m_rectSelect.top)
		{
			pos1.x = m_rectSelect.right;
			pos1.y = m_rectSelect.bottom;
			pos2.x = m_rectSelect.left;
			pos2.y = m_rectSelect.top;
		}
		else if(m_rectSelect.right > m_rectSelect.left)
		{
			pos1.x = m_rectSelect.left;
			pos1.y = m_rectSelect.top;
			pos2.x = m_rectSelect.right;
			pos2.y = m_rectSelect.bottom;
		}
		else
		{
			pos1.x = m_rectSelect.right;
			pos1.y = m_rectSelect.bottom;
			pos2.x = m_rectSelect.left;
			pos2.y = m_rectSelect.top;
		}

		if(pos1.y == pos2.y)
			source = pParent->m_CodeInfo_Array[pos1.y].strCode.Mid(pos1.x).Left(pos2.x - pos1.x);
		else
		{
			for(int i = pos1.y; i <= pos2.y; i++)
			{
				nL = pParent->m_CodeInfo_Array[i].strCode.GetLength();
				if(i == pos1.y)
				{
					source = pParent->m_CodeInfo_Array[i].strCode.Right(nL - pos1.x);
					source += '\r';
				}
				else if(i == pos2.y)
					source += pParent->m_CodeInfo_Array[i].strCode.Left(pos2.x);
				else
				{
					source += pParent->m_CodeInfo_Array[i].strCode;
					source += '\r';
				}
			}
		}
		//文本内容保存在source变量中
		if( OpenClipboard() )
		{
			HGLOBAL clipbuffer;
			char * buffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(source));
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_TEXT,clipbuffer);
			CloseClipboard();
		}
	}
}

void CCodeText::OnCodeCut() 
{
	OnCodeCopy();
	DeleteCharactors_Lines();
	AdjustCursor();	
}

void CCodeText::OnCodePaste() 
{
	char * buffer = NULL;
	//打开剪贴板
	CString fromClipboard;
	if ( OpenClipboard() )
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);
		fromClipboard = buffer;
		GlobalUnlock(hData);
		CloseClipboard();
	}
	InsertText(fromClipboard);
	AdjustCursor();
}

void CCodeText::InsertText(CString strText)
{
	if(m_rectSelect.bottom != m_rectSelect.top || m_rectSelect.left != m_rectSelect.right)
		DeleteCharactors_Lines();//假如有选择文件内容,删除该内容

	strText.Remove('\n');
	if(strText.GetLength() == 0)
		return;
	
	int nArrayIndex = m_pointCursor.y / 20 + m_nScreenPosV / 40;
	TESTLUA* pParent = (TESTLUA*)GetParent();
	strText.Replace("\t", "    ");
	if(strText.Find('\r') < 0)
	{
		int nI = (m_pointCursor.x + m_nScreenPosH) / 8;
		pParent->m_CodeInfo_Array[nArrayIndex].strCode.Insert(nI, strText);
		m_pointCursor.x += strText.GetLength() * 8;
	}
	else
	{
		bool bEndReturn = true;
		if(strText.Right(1) != "\r")
		{
			bEndReturn = false;
			strText += "\r";
		}


		long nL, nI = 0;
		nL = strText.GetLength();
		CStringArray strAr1;
		CString str1;
		strAr1.RemoveAll();

		for(int i = 0; i < nL; i++)
		{
			if(strText[i] == '\r')
			{
				str1 = strText.Mid(nI).Left(i - nI);
				strAr1.Add(str1);
				nI = i + 1;
			}
		}

		ReturnText();//ENTER键换行

		nL = strAr1.GetSize();
		
		codeinfo code1;
		code1.bIsBreak = false;
		code1.bIsDebug = false;
		if(bEndReturn)
		{
			nI = nL;
			m_pointCursor.x = - m_nScreenPosH;
		}
		else
		{
			nI = nL - 1;
			pParent->m_CodeInfo_Array[nArrayIndex + 1].strCode.Insert(0, strAr1[nL - 1]);
			m_pointCursor.x = strAr1[nL - 1].GetLength() * 8 - m_nScreenPosH;
		}
		for(int i = 0; i < nI - 1; i++)
			pParent->m_CodeInfo_Array.InsertAt(nArrayIndex + 1, code1);
		for(int i = 0; i < nI; i++)
			pParent->m_CodeInfo_Array[nArrayIndex + i].strCode += strAr1[i];

		m_pointCursor.y = (nArrayIndex + nI) * 20 - m_nScreenPosV / 2;
	}
}

void CCodeText::OnCodeDelete() 
{
	DeleteText();
}

void CCodeText::CodeCopy()
{
	OnCodeCopy();
}

void CCodeText::CodeCut()
{
	OnCodeCut();
}

void CCodeText::CodePaste()
{
	OnCodePaste();
}
