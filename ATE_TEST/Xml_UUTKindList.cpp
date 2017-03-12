// Xml_UUTKindList.cpp: implementation of the CXml_UUTKindList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTKindList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTKindList::CXml_UUTKindList(TiXmlElement* pRootEle)
{

	m_pNode=pRootEle;  //指向xml文件的根节点
	/*
	if(NULL!=pRootEle)
	{
		m_pNode=pRootEle->FirstChild("ItemSource");
	}
	else
	{
		m_pNode=NULL;
	}
	*/
}

CXml_UUTKindList::CXml_UUTKindList()
{
	m_pNode=NULL;
}

CXml_UUTKindList::~CXml_UUTKindList()
{

}

//获取基本信息中的名字信息
CString CXml_UUTKindList::GetName()
{
	if(NULL==m_pNode)
	{
		ThrowErr(找不到Kind根节点);
		return "";
	}
	TiXmlNode* m_pNode_Basic=m_pNode->FirstChild("BasicInfo");
	if(NULL==m_pNode_Basic)
	{
		ThrowErr(找不到kind基本信息节点);
		return "";	
	}
	//TiXmlNode* m_pNode_Name=m_pNode_Basic->FirstChild("Name");
	TiXmlElement* m_pEle_Name=m_pNode_Basic->FirstChildElement("Name");
	if(NULL==m_pEle_Name)
	{
		ThrowErr(找不到kind名称节点);
		return "";	
	};
	return m_pEle_Name->GetText();
}

//获取基本信息中的备注信息
CString CXml_UUTKindList::GetDescription()
{
	if(NULL==m_pNode)
	{
		ThrowErr(找不到Kind根节点);
		return "";
	}
	TiXmlNode* m_pNode_Basic=m_pNode->FirstChild("BasicInfo");
	if(NULL==m_pNode_Basic)
	{
		ThrowErr(找不到kind基本信息节点);
		return "";	
	}
	TiXmlElement* m_pEle_Name=m_pNode_Basic->FirstChildElement("Description");
	if(NULL==m_pEle_Name)
	{
		ThrowErr(找不到kind备注节点);
		return "";	
	};
	return m_pEle_Name->GetText();
}

int CXml_UUTKindList::GetKindList(vector<UUTKindList> *vKindList)
{
	if(NULL==m_pNode)
	{
		ThrowErr(找不到Kind根节点);
		return -1;
	}
	TiXmlNode* m_pNode_kind=m_pNode->FirstChild("kind");
	if(NULL==m_pNode_kind)
	{
		ThrowErr(找不到kind列表);
		return 0;	
	}
	TiXmlElement* m_pEle_temp=NULL;
	UUTKindList stucUUTKind;
	for(m_pEle_temp=m_pNode_kind->FirstChildElement();m_pEle_temp;m_pEle_temp=m_pEle_temp->NextSiblingElement())
	{
		stucUUTKind.m_strKindName=m_pEle_temp->Value();
		stucUUTKind.m_intID=atoi(m_pEle_temp->Attribute("ID"));
		stucUUTKind.m_intUINumber=atoi(m_pEle_temp->Attribute("UI"));
		vKindList->push_back(stucUUTKind);
	}
	return 1;
}

int CXml_UUTKindList::CreatKind(CString strNewKind)
{
	int nID = 0;
	vector<UUTKindList> vKindList;
	GetKindList(&vKindList);

	for(int i = 0; i < vKindList.size(); i++)
	{
		if(strNewKind == vKindList[i].m_strKindName)
			return 0;
		if(nID < vKindList[i].m_intID) 
			nID = vKindList[i].m_intID;
	}
	TiXmlNode* pNode_kind=m_pNode->FirstChild("kind");
	TiXmlElement* pElem_kind = pNode_kind->ToElement();
	TiXmlElement* pEleNew = new TiXmlElement(strNewKind);
	pEleNew->SetAttribute("UI", 1);
	pEleNew->SetAttribute("ID", nID);
	pElem_kind->LinkEndChild(pEleNew);

	return 1;
}

int CXml_UUTKindList::DeleteKind(CString strNewKind)
{
	TiXmlNode* pNode_kind=m_pNode->FirstChild("kind");
	TiXmlNode* pNode_child =NULL;
	TiXmlElement* pEle_temp=NULL;
	UUTKindList stucUUTKind;
	for(pNode_child=pNode_kind->FirstChild();pNode_child;pNode_child=pNode_child->NextSibling())
	{
		pEle_temp = pNode_child->ToElement();
		if(pEle_temp->Value() == strNewKind)
		{
			pNode_kind->RemoveChild(pNode_child);
			break;
		}
	}
	return 1;
}

