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

//������Ŀ����
int CXml_ItemVar::ItemVar_Add(ItemVar stcItemVar)
{
	if(m_pNode==NULL)
	{
		return 0;
	}
	TiXmlElement xEle(stcItemVar.m_strLogicName);
	xEle.SetAttribute("ID",stcItemVar.m_intID);
	xEle.SetAttribute("ValueMode",stcItemVar.m_strValueMode);

	TiXmlElement xEle_Name("Name");  //����������Ԫ��
	TiXmlText txtName(stcItemVar.m_strName); //�½�Text
	xEle_Name.InsertEndChild(txtName);
	xEle.InsertEndChild(xEle_Name);//���ӵ����ڵ�
	
	TiXmlElement xEle_Note("note"); //����������עԪ��
	TiXmlText txt_note(stcItemVar.m_strNote);
	xEle_Note.InsertEndChild(txt_note);
	xEle.InsertEndChild(xEle_Note);

	if(stcItemVar.m_strValueMode=="Enum")
	{
		TiXmlElement xle_Sel("Selection"); //����ѡ��Ԫ��
		xEle.InsertEndChild(xle_Sel);
	}
	else
	{
		
		TiXmlElement xEle_Upper("Upper"); //��������Ԫ��
		TiXmlText txt_Upper(stcItemVar.m_strUpper);
		xEle_Upper.InsertEndChild(txt_Upper);
		xEle.InsertEndChild(xEle_Upper);

		TiXmlElement xEle_Lower("Lower");//��������Ԫ��
		TiXmlText txt_Lower(stcItemVar.m_strLower);
		xEle_Lower.InsertEndChild(txt_Lower);
		xEle.InsertEndChild(xEle_Lower);
		TiXmlElement xEle_Unit("Unit"); //����������λԪ��
		TiXmlText txt_Unit(stcItemVar.m_strUnit);
		xEle_Unit.InsertEndChild(txt_Unit);
	    xEle.InsertEndChild(xEle_Unit);
	}
	m_pNode->InsertEndChild(xEle);
	return 1;
}
//����ID
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
