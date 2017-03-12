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
	};//���尴ť״̬
	CBitmap m_pBmp1,m_pBmp2; //Load����ͼƬ
	CRect m_Rc; //���水ť�ͻ���
	int m_State; //��ť����״̬Ϊenum������ֵ����������ڰ�ť�Ϻ����������
	BOOL m_IsTimerOn; //��ʱ�����������ж�������ť�����λ��
	POINT m_CursorPos;//���λ��
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
