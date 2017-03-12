// ReadSolutionList.cpp: implementation of the CReadSolutionList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "ReadSolutionList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadSolutionList::CReadSolutionList()
{
	m_pEle = NULL;
}
CReadSolutionList::CReadSolutionList(TiXmlElement *pRootEle)
{
	if(NULL!=pRootEle)
	{
		m_pNode=pRootEle->FirstChild("SolutionList");
	}
	else
	{
		m_pNode=NULL;
	}	
}

CReadSolutionList::~CReadSolutionList()
{
     m_pNode=NULL;
}

int CReadSolutionList::ReadSolutionList(vector<CString> *vSoluList)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_Temp=NULL;
	CString strSolutionName;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{		
		strSolutionName=pEle_Temp->Value(); //ÏîÄ¿Ãû³Æ		
		vSoluList->push_back(strSolutionName);
	}
	return 1;
}

int CReadSolutionList::WriteSolutionList(CStringArray &strSoluArray)
{
	m_pEle = NULL;
	if(m_pNode == NULL)
	{
		m_pEle = new TiXmlElement("ItemInfo");
	}
	else
		m_pEle = m_pNode->ToElement();

	m_pEle->Clear();

	for(int i = 0; i < strSoluArray.GetSize(); i++)
	{	
		TiXmlElement* pEle_Temp1 = new TiXmlElement(strSoluArray[i]);
		m_pEle->LinkEndChild(pEle_Temp1);
	}
	return 1;
}