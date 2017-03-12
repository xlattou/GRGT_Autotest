// NewMenu.cpp: implementation of the CNewMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "NewMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewMenu::CNewMenu()
{

}

CNewMenu::~CNewMenu()
{

}

void CNewMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight=30; //项高
	lpMeasureItemStruct->itemWidth=100;//项宽
}

void CNewMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect=lpDrawItemStruct->rcItem;
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	dc.FillSolidRect(rect,RGB(219,251,251));
	CFont Font;
	Font.CreatePointFont(125,"宋体");
	dc.SelectObject(&Font);
	CString *pText=(CString*)lpDrawItemStruct->itemData;
	if(lpDrawItemStruct->itemState&ODS_SELECTED)
		dc.FillSolidRect(rect,RGB(255,200,255));
	dc.SetTextColor(RGB(10,0,181));
	dc.DrawText(*pText,rect,DT_VCENTER|DT_LEFT|DT_SINGLELINE);
	dc.Detach();


}

void CNewMenu::ChangeMenuItem(CMenu *pMenu)
{
	int itemCount=pMenu->GetMenuItemCount();
	for(int i=0;i<itemCount;i++)
	{
		CString* pText=new CString;
		UINT itemID=pMenu->GetMenuItemID(i); //获取菜单项ID号
		pMenu->GetMenuString(i,*pText,MF_BYPOSITION); //获取菜单文本
		pMenu->ModifyMenu(i,MF_OWNERDRAW|MF_BYPOSITION|MF_STRING,itemID,(LPSTR)pText);
		if(itemID==-1)
			ChangeMenuItem(pMenu->GetSubMenu(i));
	}

}
