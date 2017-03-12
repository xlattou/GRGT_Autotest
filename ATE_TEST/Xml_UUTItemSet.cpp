// Xml_UUTItemSet.cpp: implementation of the CXml_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTItemSet.h"
#include "Xml_Bll_UUTPointInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTItemSet::CXml_UUTItemSet(TiXmlElement* pRootEle)
{
	if(NULL!=pRootEle)
	{
		m_pNode=pRootEle->FirstChild("ItemSet");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_UUTItemSet::CXml_UUTItemSet()
{
	m_pNode=NULL;
}

CXml_UUTItemSet::~CXml_UUTItemSet()
{

}

int CXml_UUTItemSet::ReadItemList(vector <UUTItemSet>* vItem)
{
	if(NULL==m_pNode)
		return 0;
	CXml_Bll_UUTPointInfo pointinfo;

	TiXmlElement* pEle_Temp=NULL;
	TiXmlElement* pEle_Temp2=NULL;
	UUTItemSet stucItem;
	stucItem.m_pTestPoint = NULL;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{		
		if((CString)pEle_Temp->Value()!="Control")
		{
			stucItem.m_intID=atoi(pEle_Temp->Attribute("ID")); //ID
    		stucItem.m_strKey=pEle_Temp->Value(); //项目名称
    		stucItem.m_strItemName=pEle_Temp->Attribute("Name"); //项目名称
			stucItem.m_strMarkName="Test";
		}
		else
		{
			stucItem.m_strKey=pEle_Temp->Attribute("key");
			stucItem.m_strItemName=pEle_Temp->Attribute("Value"); //项目名称
			stucItem.m_strMarkName="Control";
		}

		pEle_Temp2 = pEle_Temp->FirstChildElement("Conclusion");
		if(pEle_Temp2)
		{
			pEle_Temp2 = pEle_Temp2->FirstChildElement("Value");
			if(pEle_Temp2)
			{
				stucItem.m_strResultCol = pEle_Temp2->Attribute("ColNum");
				stucItem.m_strResultRow = pEle_Temp2->Attribute("LineNum");
			}
		}

		vItem->push_back(stucItem);
	}
	return 1;
}

int CXml_UUTItemSet::GetItemPosionByKey(CString strKeyName,UUTItemSet* stucItem)
{

	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_Temp=NULL;
	TiXmlElement* pEle_Temp2=NULL;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{		
		if((CString)pEle_Temp->Value()!="Control")
		{
			
			stucItem->m_strKey=pEle_Temp->Value(); //????
			stucItem->m_intID=atoi(pEle_Temp->Attribute("ID")); //ID

			stucItem->m_strItemName=pEle_Temp->Attribute("Name"); //????
			stucItem->m_strMarkName="test";
			///////////////////????????///////////////////////////////////////////////////////
			if(pEle_Temp->FirstChildElement("Conclusion")!=NULL)
			{
				pEle_Temp2=pEle_Temp->FirstChildElement("Conclusion")->FirstChildElement("Value");
				stucItem->m_strResultCol=pEle_Temp2->Attribute("ColNum");
				stucItem->m_strResultRow=pEle_Temp2->Attribute("LineNum");
			}
			else
			{
				stucItem->m_strResultCol="";
				stucItem->m_strResultRow="";
			}
		}
		else
		{
			stucItem->m_strKey=pEle_Temp->Attribute("key");
			stucItem->m_strItemName=pEle_Temp->Attribute("Value"); //????
			stucItem->m_strMarkName="Control";
			stucItem->m_strResultCol="";
			stucItem->m_strResultRow="";
		}
		if(stucItem->m_strKey==strKeyName)
		{
			break;		
		}
	}
	return 1;
}