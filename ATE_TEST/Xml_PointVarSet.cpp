// Xml_PointVarSet.cpp: implementation of the CXml_PointVarSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_PointVarSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_PointVarSet::CXml_PointVarSet()
{

}

CXml_PointVarSet::CXml_PointVarSet(TiXmlElement* pEle_Parent)
{
	m_pEle_Parent=pEle_Parent;
	if(pEle_Parent!=NULL)
	{
		m_pNode=pEle_Parent->FirstChild("VarSet");
		
	}
	else
	{
		m_pNode=NULL;
	}		
}

CXml_PointVarSet::~CXml_PointVarSet()
{

}

int CXml_PointVarSet::ReadVarList(vector<PointVarSet>* vPtVar)
{
	if(NULL==m_pNode)
	{
		return 0;
	}
	TiXmlElement* pEle_Temp=NULL;
	PointVarSet stucPtVarSet;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{
		stucPtVarSet.m_intID=atoi(pEle_Temp->Attribute("ID"));
		stucPtVarSet.m_strLogicName=pEle_Temp->Value();
		stucPtVarSet.m_strName=pEle_Temp->Attribute("Name");
		stucPtVarSet.m_strUnit=pEle_Temp->Attribute("Unit");
		stucPtVarSet.m_strValue=pEle_Temp->Attribute("Value");
		vPtVar->push_back(stucPtVarSet);
	}
	return 1;
}

TiXmlElement* CXml_PointVarSet::PointVar_Add(TiXmlDocument* pDoc,PointVarSet stuPtVar)
{
	if(NULL==m_pEle_Parent)
		return NULL;
	TiXmlElement* pEle_Temp=new TiXmlElement("Freq");
	pEle_Temp->SetAttribute("ID",stuPtVar.m_intID);
    pEle_Temp->SetAttribute("Name",stuPtVar.m_strName);
	pEle_Temp->SetAttribute("Value",stuPtVar.m_strValue);
	pEle_Temp->SetAttribute("Unit",stuPtVar.m_strUnit);
	if(NULL==m_pNode)
	{
		TiXmlElement tEle("VarSet");
    	tEle.LinkEndChild(pEle_Temp);
		m_pEle_Parent->InsertEndChild(tEle);	
	}
	else
	{
    	m_pNode->LinkEndChild(pEle_Temp);
	}
	pDoc->SaveFile();
    return pEle_Temp;
}

TiXmlElement* CXml_PointVarSet::PointVar_Modify(TiXmlDocument* pDoc,PointVarSet stuPtVar)
{
	if(NULL==m_pNode)
	{
		return 0;
	}
	TiXmlElement* pEle_Temp=m_pNode->FirstChildElement("Freq");
	pEle_Temp->SetAttribute("Value",stuPtVar.m_strValue);
	pDoc->SaveFile();
	return pEle_Temp;
	return NULL;

}
