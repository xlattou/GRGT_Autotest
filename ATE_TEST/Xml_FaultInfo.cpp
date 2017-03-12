// Xml_FaultInfo.cpp: implementation of the CXml_FaultInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_FaultInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_FaultInfo::CXml_FaultInfo()
{

}

CXml_FaultInfo::CXml_FaultInfo(TiXmlElement *pEle)
{
	if(NULL!=pEle)
	{
		m_pNode=pEle->FirstChild("FaultList");
	}
	else
	{
		m_pNode=NULL;
	}
	
}


CXml_FaultInfo::~CXml_FaultInfo()
{

}

int CXml_FaultInfo::GetFaultList(vector<stuFaultInfo>* vFaultList)
{
	TiXmlNode* pNode_Temp=NULL;
	TiXmlNode* pNode_Temp2=NULL;
	stuFaultInfo stuFltInfo;
	for(pNode_Temp=m_pNode->FirstChild("Fault");pNode_Temp;pNode_Temp=pNode_Temp->NextSibling("Fault"))
	{
		stuFltInfo.m_intID=atoi(pNode_Temp->ToElement()->Attribute("ID"));
		stuFltInfo.m_strName=pNode_Temp->ToElement()->Attribute("Name");
		pNode_Temp2=pNode_Temp->FirstChild("ModifyAdvise");
		stuFltInfo.m_strAdviseFileName=pNode_Temp2->ToElement()->Attribute("FileName");
		vFaultList->push_back(stuFltInfo);
	}
	return 1;
}

TiXmlNode* CXml_FaultInfo::GetFaultNode(int intID)
{
	TiXmlNode* pNode_Temp=NULL;
	BOOL ret=FALSE;
	for(pNode_Temp=m_pNode->FirstChild("Fault");pNode_Temp;pNode_Temp=pNode_Temp->NextSibling("Fault"))
	{
		if(intID==atoi(pNode_Temp->ToElement()->Attribute("ID")))
		{
			ret=TRUE;
			break;
		}
	}
	if(ret)
	{
		return pNode_Temp;
	}
	else
	{
		ThrowErr(找不到指定故障原因ID的信息);
		return NULL;
	}
}

TiXmlNode* CXml_FaultInfo::GetFaultNode(CString strFaultName)
{
	TiXmlNode* pNode_Temp=NULL;
	BOOL ret=FALSE;
	for(pNode_Temp=m_pNode->FirstChild("Fault");pNode_Temp;pNode_Temp=pNode_Temp->NextSibling("Fault"))
	{
		if(strFaultName==pNode_Temp->ToElement()->Attribute("Name"))
		{
			ret=TRUE;
			break;
		}
	}
	if(ret)
	{
		return pNode_Temp;
	}
	else
	{
		ThrowErr(找不到指定故障原因ID的信息);
		return NULL;
	}
}