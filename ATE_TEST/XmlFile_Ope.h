// XmlFile_Ope.h: interface for the CXmlFile_Ope class.
//
//////////////////////////////////////////////////////////////////////

#include "tinyxml.h"
#include "tinystr.h"
#define ThrowErr(err) throw TEXT(#err)

#if !defined(AFX_XMLFILE_OPE_H__4855071D_DD5E_469C_9BE9_ACB9F8DB712E__INCLUDED_)
#define AFX_XMLFILE_OPE_H__4855071D_DD5E_469C_9BE9_ACB9F8DB712E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CXmlFile_Ope  
{
public:
	int SaveFile();
	int LoadXmlFile(CString strXmlFilePath);
	TiXmlElement* pRootEle;
	TiXmlDocument* pDoc;
	CXmlFile_Ope();
	CXmlFile_Ope(CString strXmlfPath);
	virtual ~CXmlFile_Ope();

};

#endif // !defined(AFX_XMLFILE_OPE_H__4855071D_DD5E_469C_9BE9_ACB9F8DB712E__INCLUDED_)
