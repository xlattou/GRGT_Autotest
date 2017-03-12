// Xml_FaultReason.cpp: implementation of the CXml_FaultReason class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_FaultReason.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_FaultReason::CXml_FaultReason()
{

}

CXml_FaultReason::CXml_FaultReason(TiXmlNode* pNode_Parent)
{
	if(NULL!=pNode_Parent)
	{
		m_pNode=pNode_Parent->FirstChild("ReasonList");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_FaultReason::~CXml_FaultReason()
{

}

int CXml_FaultReason::GetReasonList(vector<stuFaultReason>* vReasonList)
{
	stuFaultReason stuReason;
	TiXmlElement* pEle_temp;
	for(pEle_temp=m_pNode->FirstChildElement();pEle_temp;pEle_temp=pEle_temp->NextSiblingElement())
	{
		stuReason.m_intID=atoi(pEle_temp->Attribute("ID"));
		stuReason.m_strCardName=pEle_temp->Value();
		stuReason.m_strFactor=pEle_temp->Attribute("Factor");
		stuReason.m_strDescription=pEle_temp->Attribute("Description");
		vReasonList->push_back(stuReason);
	}
	return 1;
}
