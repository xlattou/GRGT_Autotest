// Xml_UUTKindList.h: interface for the CXml_UUTKindList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTKINDLIST_H__D9D5FDB9_017A_4A24_B9AB_69CF6823FBF3__INCLUDED_)
#define AFX_XML_UUTKINDLIST_H__D9D5FDB9_017A_4A24_B9AB_69CF6823FBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;


//Kind基本信息
struct UUTKind
{
	CString m_strName;
	CString m_strDescription;
};

//Kind信息组成
struct UUTKindList
{
	int m_intID;
	CString m_strKindName;
	int m_intUINumber;
};


class CXml_UUTKindList  
{
public:
	int GetKindList(vector<UUTKindList> *vKindList);
	CString GetDescription();
	CString GetName();
	int CreatKind(CString strNewKind);
	int DeleteKind(CString strNewKind);

	TiXmlNode* m_pNode;
	CXml_UUTKindList(TiXmlElement* pRootEle);
	CXml_UUTKindList();
	

	virtual ~CXml_UUTKindList();

};

#endif // !defined(AFX_XML_UUTKINDLIST_H__D9D5FDB9_017A_4A24_B9AB_69CF6823FBF3__INCLUDED_)
