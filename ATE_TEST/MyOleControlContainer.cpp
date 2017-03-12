// MyOleControlContainer.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "MyOleControlContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyOleControlContainer

CMyOleControlContainer::CMyOleControlContainer(CWnd* pWnd) :
	COleControlContainer(pWnd)
{
}

CMyOleControlContainer::~CMyOleControlContainer()
{
	
}

void CMyOleControlContainer::OnUIActivate(COleControlSite* pSite)
{
	if (pSite == m_pSiteUIActive)	// workaround
		return;

	if (m_pSiteUIActive != NULL)
		m_pSiteUIActive->m_pInPlaceObject->UIDeactivate();

	ASSERT(m_pSiteUIActive == NULL);    // did control call OnUIDeactivate?
	m_pSiteUIActive = pSite;
}
