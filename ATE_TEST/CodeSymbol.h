#if !defined(AFX_CODESYMBOL_H__E5D8D040_4925_44C2_828C_FF7761FB1D6B__INCLUDED_)
#define AFX_CODESYMBOL_H__E5D8D040_4925_44C2_828C_FF7761FB1D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCodeSymbol window

class CCodeSymbol : public CStatic
{
// Construction
public:
	CCodeSymbol();
	COLORREF m_bachColor;
	COLORREF m_ColorText;
	CPen   m_penRed, m_penGreen;
	CBrush m_brushRed, m_brushGreen;
	CFont  m_font;
	int	   m_nScreenPosV;
// Attributes
public:

	void DrawSymbol(CDC* pDC);
	void FillBackGround(CDC* pDC);
	void DrawCodeSymbol(CDC* pDC);
	void setScreenPoseV(int npose);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeSymbol)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCodeSymbol();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeSymbol)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODESYMBOL_H__E5D8D040_4925_44C2_828C_FF7761FB1D6B__INCLUDED_)
