// Xml_Point.cpp: implementation of the CXml_Point class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Point.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Point::CXml_Point()
{
	m_pNode=NULL;
}

CXml_Point::CXml_Point(TiXmlNode* pNode_Parent)
{
	if(pNode_Parent!=NULL)
	{
		m_pNode=pNode_Parent->FirstChild("Point");
		
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_Point::~CXml_Point()
{

}

int CXml_Point::ReadPointList(vector<Point> *vPoint)
{
	if(m_pNode==NULL)
		return 0;
	TiXmlElement* pEle_Temp;
	Point pt;
	for(pEle_Temp=m_pNode->FirstChildElement("Point");pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement("Point"))
	{
	   	pt.m_intPointID=atoi(pEle_Temp->Attribute("PointID"));
	   	pt.m_intItemID=atoi(pEle_Temp->Attribute("ItemID"));
	   	pt.m_intID=atoi(pEle_Temp->Attribute("ID"));
	   	vPoint->push_back(pt);
	}
	return 1;
}
