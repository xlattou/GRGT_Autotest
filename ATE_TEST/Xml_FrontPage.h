// Xml_UUTItemSet.h: interface for the CXml_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_FRONTPAGE_H__INCLUDED_)
#define AFX_XML_FRONTPAGE_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////***************Document/*.xml****************//////////////////////////////////
#include "XmlFile_Ope.h"
#include <afxtempl.h>

typedef struct FRONTPAGE
{
	CString strName;
	CString strRow;
	CString strCol;
}FrontPage;

class CXml_FrontPage
{
public:
	TiXmlNode* m_pNode;
	CXml_FrontPage();
	CXml_FrontPage(TiXmlElement* pRootEle);
	int ReadFrontPageList(CString &strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage);//读取首页信息
	int WriteFrontPageList(CString strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage);//保存首页信息
	virtual ~CXml_FrontPage();
	
};

#endif // !defined(AFX_XML_FRONTPAGE_H__INCLUDED_)
