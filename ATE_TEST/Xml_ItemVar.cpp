// Xml_ItemVar.cpp: implementation of the CXml_ItemVar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_ItemVar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_ItemVar::CXml_ItemVar()
{

}
CXml_ItemVar::CXml_ItemVar(TiXmlNode* pNode_Parent)
{
	if(pNode_Parent!=NULL)
	{
		m_pNode=pNode_Parent->FirstChild("ItemVar");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_ItemVar::~CXml_ItemVar()
{

}

//增加项目变量
int CXml_ItemVar::ItemVar_Add(ItemVar stcItemVar)
{
	if(m_pNode==NULL)
	{
		return 0;
	}
	TiXmlElement xEle(stcItemVar.m_strLogicName);
	xEle.SetAttribute("ID",stcItemVar.m_intID);
	xEle.SetAttribute("ValueMode",stcItemVar.m_strValueMode);

	TiXmlElement xEle_Name("Name");  //创建变量名元素
	TiXmlText txtName(stcItemVar.m_strName); //新建Text
	xEle_Name.InsertEndChild(txtName);
	xEle.InsertEndChild(xEle_Name);//连接到根节点
	
	TiXmlElement xEle_Note("note"); //创建变量备注元素
	TiXmlText txt_note(stcItemVar.m_strNote);
	xEle_Note.InsertEndChild(txt_note);
	xEle.InsertEndChild(xEle_Note);

	if(stcItemVar.m_strValueMode=="Enum")
	{
		TiXmlElement xle_Sel("Selection"); //创建选项元素
		xEle.InsertEndChild(xle_Sel);
	}
	else
	{
		
		TiXmlElement xEle_Upper("Upper"); //创建上限元素
		TiXmlText txt_Upper(stcItemVar.m_strUpper);
		xEle_Upper.InsertEndChild(txt_Upper);
		xEle.InsertEndChild(xEle_Upper);

		TiXmlElement xEle_Lower("Lower");//创建下限元素
		TiXmlText txt_Lower(stcItemVar.m_strLower);
		xEle_Lower.InsertEndChild(txt_Lower);
		xEle.InsertEndChild(xEle_Lower);
		TiXmlElement xEle_Unit("Unit"); //创建变量单位元素
		TiXmlText txt_Unit(stcItemVar.m_strUnit);
		xEle_Unit.InsertEndChild(txt_Unit);
	    xEle.InsertEndChild(xEle_Unit);
	}
	m_pNode->InsertEndChild(xEle);
	return 1;
}
//产生ID
int CXml_ItemVar::ItemVar_GenerateID()
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_Child=NULL;
	int intMaxID=0;
	int intTempID=0;
	for(pEle_Child=m_pNode->FirstChildElement();pEle_Child;pEle_Child=pEle_Child->NextSiblingElement())
	{
		intTempID=atoi(pEle_Child->Attribute("ID"));
		if(intTempID>intMaxID)
			intMaxID=intTempID;
	}
	return intMaxID+1;
}


int CXml_ItemVar::ItemVar_Modify(ItemVar stucItemVar)
{
	
	
	return 1;
}
