// ReadXML.cpp: implementation of the CReadXML class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "ReadXML.h"
#include "XmlFile_Ope.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadXML::CReadXML()
{

}

CReadXML::~CReadXML()
{

}

int CReadXML::ReadXMLList(CString XMLpath,CString XMLtitle,vector<CString>* vInsList)
{
	CXmlFile_Ope m_XML;
	TiXmlNode* m_pNode;
	TiXmlNode* pNode_temp=NULL;
	m_XML.LoadXmlFile(XMLpath);
	m_pNode=m_XML.pRootEle->FirstChild(XMLtitle);
	//TiXmlNode* pInsNode=m_pNode->NextSibling(XMLtitle);	
	for(pNode_temp=m_pNode->FirstChild();pNode_temp;pNode_temp=pNode_temp->NextSibling())
	{
		vInsList->push_back(pNode_temp->Value());
	}
	return 1;
}

int CReadXML::ReadXMLThdList(CString XMLpath,CString FirTitle,CString SecTitle,CString ThdTitle,vector<VarName>* vInsList)
{
	CXmlFile_Ope m_XML;
	TiXmlNode* m_firNode;
	TiXmlNode* m_secNode;
	TiXmlNode* m_thdNode;
	TiXmlNode* pNode_temp=NULL;
	VarName itemTemp;
	TiXmlElement* pEle_temp;

	m_XML.LoadXmlFile(XMLpath);
	m_firNode=m_XML.pRootEle->FirstChild(FirTitle);
	m_secNode=m_firNode->FirstChild(SecTitle);
	m_thdNode=m_secNode->FirstChild(ThdTitle);

	for(pNode_temp=m_thdNode->FirstChild(),pEle_temp=m_thdNode->FirstChildElement();pEle_temp;pNode_temp=pNode_temp->NextSibling(),pEle_temp=pEle_temp->NextSiblingElement())
	{
		
		itemTemp.logicName=pNode_temp->Value();
		itemTemp.chiName=pEle_temp->Attribute("name");
		vInsList->push_back(itemTemp);
	}

	return 1;
}