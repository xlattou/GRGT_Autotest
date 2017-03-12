#if !defined(AFX_CODETEXT_H__30847D40_415B_4912_8090_F53FFD953F05__INCLUDED_)
#define AFX_CODETEXT_H__30847D40_415B_4912_8090_F53FFD953F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeText window

class CCodeText : public CStatic
{
// Construction
public:
	CCodeText();
	bool m_bTrackLeave;
	COLORREF m_bachColor;
	COLORREF m_bachCurserLine;
	
	COLORREF m_ColorBlue;//蓝色，语法
	COLORREF m_ColorDark;//青色，变量	
	COLORREF m_ColorGreen;//绿色，注解
	COLORREF m_ColorRed;//红色，全局保留函数关键字
	COLORREF m_ColorShallowRed;//淡红色，基本保留函数关键字
	COLORREF m_ColorDarkRed;//暗红色，函数名
	COLORREF m_ColorGray;//灰色，响应函数
	COLORREF m_ColorBlack;//黑色，数字，其他
	COLORREF m_ColorDarkYellow;//暗黄色，标点符号
	COLORREF m_ColorCarmine;//洋红色，用于引号
	COLORREF m_ColorWhite;//白色，用于显示选中的字符
	COLORREF m_ColorShallowBlue;//淡蓝色，选中底色
	
	CBrush m_brushBlack;
	CPen   m_PenCursor;
	CFont  m_font;
	bool   m_bIsNoted;//是否被--[[ --]]全局注释
	int	   m_nTextWindowWidth;
	int	   m_nTextWindowHeight;
	int	   m_nScreenPosV;
	int	   m_nScreenPosH;
	bool   m_bCursorFlash;
	CRect  m_RectSelect;
	CPoint m_pointCursor;
	bool   m_bMoveSelect;
	CRect  m_rectSelect;
	bool   m_bLeftMouseDown;
// Attributes
public:

	void DrawText(CDC* pDC);
	void FillBackGround_DrawCodeText(CDC* pDC);
	int  DrawTextWithBlank(CDC* pDC, CString strText, CRect rec1);
	void DrawTextWithKeyword(CDC* pDC, CString strText, CRect rec1);
	void DrawCommonText(CDC* pDC, CString strText, CRect rec1, int nLenth);
	void setScreenPoseV(int npose);
	void setScreenPoseH(int npose);
	void ChangeCursorFlashState();
	void DeleteText();
	void BackspaceText();
	void HomeText();
	void EndText();
	void UpText();
	void DownText();
	void LeftText();
	void RightText();
	void ReturnText();
	void AdjustCursor(bool bPointCursorPrew = true);
	int  JudgeGBK(CString str1, int nIndex);
	void DeleteCharactors_Lines();
	void InsertText();
	void InsertText(CString strText);
	
	void CodeCopy();
	void CodeCut();
	void CodePaste();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeText)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCodeText();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeText)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCodeCopy();
	afx_msg void OnCodeCut();
	afx_msg void OnCodePaste();
	afx_msg void OnCodeDelete();
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODETEXT_H__30847D40_415B_4912_8090_F53FFD953F05__INCLUDED_)
