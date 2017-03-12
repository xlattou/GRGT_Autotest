#if !defined(AFX_NEWBUTTON_H__C3770B47_7405_487C_BB21_D8E0714D13DC__INCLUDED_)
#define AFX_NEWBUTTON_H__C3770B47_7405_487C_BB21_D8E0714D13DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewButton window

class CNewButton : public CButton
{
// Construction
public:
	CNewButton();
	enum
	{
		STATE_MOUSEON,
			STATE_NORMAL
	};//定义按钮状态
	CBitmap m_pBmp1,m_pBmp2; //Load两幅图片
	CRect m_Rc; //保存按钮客户区
	int m_State; //按钮所处状态为enum的两个值，代表鼠标在按钮上和正常情况下
	BOOL m_IsTimerOn; //定时器开否，用于判断鼠标跟按钮的相对位置
	POINT m_CursorPos;//鼠标位置
	CDC* m_pDC;
	bool m_bTrackLeave;


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImage(int intState);
	virtual ~CNewButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBUTTON_H__C3770B47_7405_487C_BB21_D8E0714D13DC__INCLUDED_)
