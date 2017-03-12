// Xml_TestSub.cpp: implementation of the CXml_TestSub class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_TestSub.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_TestSub::CXml_TestSub()
{

}

CXml_TestSub::CXml_TestSub(TiXmlElement *pRootEle)
{
	if(NULL!=pRootEle)
	{
		m_pNode=pRootEle->FirstChild("测试分组");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_TestSub::~CXml_TestSub()
{

}

//读取分组列表
int CXml_TestSub::Sub_ReadList(vector<TestSub> *vSubList)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement *pEle_temp=NULL;
	TestSub stucTestSub;
	for(pEle_temp=m_pNode->FirstChildElement();pEle_temp;pEle_temp=pEle_temp->NextSiblingElement())
	{
	//	if(pEle_temp!=NULL)
	//	{
			stucTestSub.m_strName=pEle_temp->Value();
			stucTestSub.m_intID=atoi(pEle_temp->Attribute("ID"));
	    	vSubList->push_back(stucTestSub);
	//	}
	}
	return 1;
}
