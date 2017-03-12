// NewMenu.h: interface for the CNewMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWMENU_H__2530C473_6A8F_4607_99A3_37767C94FAE5__INCLUDED_)
#define AFX_NEWMENU_H__2530C473_6A8F_4607_99A3_37767C94FAE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CNewMenu : public CMenu  
{
public:
	void ChangeMenuItem(CMenu* pMenu);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT);
	CNewMenu();
	virtual ~CNewMenu();

};

#endif // !defined(AFX_NEWMENU_H__2530C473_6A8F_4607_99A3_37767C94FAE5__INCLUDED_)
