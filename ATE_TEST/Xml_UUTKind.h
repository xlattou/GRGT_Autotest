// Xml_UUTKind.h: interface for the CXml_UUTKind class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_XML_UUTKIND_H__69A820A4_BB23_4AD5_A2E8_5A33F0F8AF19__INCLUDED_)
#define AFX_XML_UUTKIND_H__69A820A4_BB23_4AD5_A2E8_5A33F0F8AF19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PathOperate.h"
#include "XmlFile_Ope.h"
#include "Xml_UUTKindList.h"
using namespace std;

class CXml_UUTKind  
{
public:
	int GetKindList(vector<UUTKindList> *vKindList);
	CXmlFile_Ope m_xmlOpe;
	CXml_UUTKind();
	virtual ~CXml_UUTKind();
	int CreatKind(CString strNewKind);
	int DeleteKind(CString strNewKind);

};

#endif // !defined(AFX_XML_UUTKIND_H__69A820A4_BB23_4AD5_A2E8_5A33F0F8AF19__INCLUDED_)
