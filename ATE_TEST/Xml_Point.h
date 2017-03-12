// Xml_Point.h: interface for the CXml_Point class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_POINT_H__CAF1F0DA_08C5_473D_89EF_B0BFB7B5ECAE__INCLUDED_)
#define AFX_XML_POINT_H__CAF1F0DA_08C5_473D_89EF_B0BFB7B5ECAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

struct Point
{
	int m_intID;
	int m_intItemID;
	int m_intPointID;
};

class CXml_Point  
{
public:
	int ReadPointList(vector<Point> *vPoint);
	CXml_Point();
	CXml_Point(TiXmlNode* pNode_Parent);
	virtual ~CXml_Point();
	TiXmlNode* m_pNode;

};

#endif // !defined(AFX_XML_POINT_H__CAF1F0DA_08C5_473D_89EF_B0BFB7B5ECAE__INCLUDED_)
