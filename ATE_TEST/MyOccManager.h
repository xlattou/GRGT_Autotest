#if !defined(AFX_MYOCCMANAGER_H__E9A967C5_E601_4A5D_8B8E_18F37B61D696__INCLUDED_)
#define AFX_MYOCCMANAGER_H__E9A967C5_E601_4A5D_8B8E_18F37B61D696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "D:\Program Files\Microsoft Visual Studio\VC98\MFC\SRC\occimpl.h"
#include "MyOleControlContainer.h"

class CMyOccManager : public COccManager
{
// Operations
public:
	CMyOccManager();
	~CMyOccManager();
	virtual COleControlContainer* CreateContainer(CWnd* pWnd)
    {
		// Advanced control container applications may want to override.
        return new CMyOleControlContainer(pWnd);
    }
};

#endif // !defined(AFX_MYOCCMANAGER_H__E9A967C5_E601_4A5D_8B8E_18F37B61D696__INCLUDED_)
