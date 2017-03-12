// Xml_UUTInfoSet.cpp: implementation of the CXml_UUTInfoSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTInfoSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTInfoSet::CXml_UUTInfoSet()
{
	m_pNode=NULL;
}
CXml_UUTInfoSet::CXml_UUTInfoSet(TiXmlElement* pRootEle, CString strFirstChild)
{
	if(pRootEle!=NULL)
	{
		m_pNode=pRootEle->FirstChild(strFirstChild);
	}
	else
	{
		m_pNode=NULL;
	}
	
}

CXml_UUTInfoSet::~CXml_UUTInfoSet()
{

}

int CXml_UUTInfoSet::ReadUUTInfo(UUTInfoSet *stucUUTInfo)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_temp=NULL;
	pEle_temp=m_pNode->FirstChildElement("UUTKind");//读取装备类型
	if(pEle_temp==NULL)
	{
		ThrowErr(读不到设备类型);
		return 0;
	}
	stucUUTInfo->m_strUUTKind=pEle_temp->GetText();  

	pEle_temp=m_pNode->FirstChildElement("Name");//读取装备名称
	if(pEle_temp==NULL)
	{
		ThrowErr(读不到设备名称);
		return 0;
	}
	stucUUTInfo->m_strName=pEle_temp->GetText(); 

	pEle_temp=m_pNode->FirstChildElement("Model");//读取装备型号
	if(pEle_temp==NULL)
	{
		ThrowErr(读不到设备型号);
		return 0;
	}
	stucUUTInfo->m_strModel=pEle_temp->GetText(); 

	pEle_temp=m_pNode->FirstChildElement("Factory"); //制造厂
	if(pEle_temp==NULL)
	{
		ThrowErr(读不到设备生产厂家);
		return 0;
	}
	stucUUTInfo->m_strFactory=pEle_temp->GetText();

//	pEle_temp=m_pNode->FirstChildElement("note"); //备注
//	if(pEle_temp==NULL)
//	{
//		ThrowErr(读不到设备备注信息);
//		return 0;
//	}
// 	stucUUTInfo->m_strNote=pEle_temp->GetText();
	
	
//	pEle_temp=m_pNode->FirstChildElement("TestTem"); //装备模版
//	if(pEle_temp==NULL)
//	{
//		ThrowErr(读不到设备模版信息);
//		return 0;
//	}
//	stucUUTInfo->m_strTestTem=pEle_temp->GetText();
//	
//	pEle_temp=m_pNode->FirstChildElement("TestConfig"); //测试配置
//	if(pEle_temp==NULL)
//	{
//		ThrowErr(读不到设备配置信息);
//		return 0;
// 	}
// 	stucUUTInfo->m_strTestConfig=pEle_temp->GetText();
	return 1;
}

int CXml_UUTInfoSet::WriteUUTInfo(UUTInfoSet *stucUUTInfo)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle = m_pNode->ToElement();
	TiXmlElement* pEle_UUTKind=NULL;
	pEle_UUTKind=m_pNode->FirstChildElement("UUTKind");//写入装备类型
	if(pEle_UUTKind==NULL)
	{
		pEle_UUTKind = new TiXmlElement("UUTKind");
		pEle->LinkEndChild(pEle_UUTKind);
	}
	TiXmlText UUTKindText(stucUUTInfo->m_strUUTKind);
	pEle_UUTKind->ReplaceChild(pEle_UUTKind->FirstChild(), UUTKindText);

	TiXmlElement* pEle_Name=NULL;
	pEle_Name=m_pNode->FirstChildElement("Name");//写入装备名称
	if(pEle_Name==NULL)
	{
		pEle_Name = new TiXmlElement("Name");
		pEle->LinkEndChild(pEle_Name);
	}
	TiXmlText NameText(stucUUTInfo->m_strName);
	pEle_Name->ReplaceChild(pEle_Name->FirstChild(), NameText); 

	TiXmlElement* pEle_Model=NULL;
	pEle_Model=m_pNode->FirstChildElement("Model");//写入装备型号
	if(pEle_Model==NULL)
	{
		pEle_Model = new TiXmlElement("Model");
		pEle->LinkEndChild(pEle_Model);
	}
	TiXmlText ModelText(stucUUTInfo->m_strModel);
	pEle_Model->ReplaceChild(pEle_Model->FirstChild(), ModelText); 

	TiXmlElement* pEle_Factory=NULL;
	pEle_Factory=m_pNode->FirstChildElement("Factory");//制造厂
	if(pEle_Factory==NULL)
	{
		pEle_Factory = new TiXmlElement("Factory");
		pEle->LinkEndChild(pEle_Factory);
	}
	TiXmlText FactoryText(stucUUTInfo->m_strFactory);
	pEle_Factory->ReplaceChild(pEle_Factory->FirstChild(), FactoryText);
	return 1;
}

int CXml_UUTInfoSet::ReadUUTItemInfo(CArray<UUTItemInfo, UUTItemInfo> &rItemInfo)
{
	TiXmlElement* pEle_temp=NULL;
	UUTItemInfo itemif1;
	CString str1;
	for(pEle_temp=m_pNode->FirstChildElement();pEle_temp;pEle_temp=pEle_temp->NextSiblingElement())
	{
		str1 = pEle_temp->Value();
		if(str1.Left(3) == "Key")
		{
			itemif1.nKey = atoi(str1.Right(str1.GetLength() - 3));
			itemif1.strName = pEle_temp->Attribute("Name");
			itemif1.strNote = pEle_temp->Attribute("Note");
			itemif1.strTestType = pEle_temp->Attribute("Type");
			rItemInfo.Add(itemif1);
		}
	}
	return 1;
}

int CXml_UUTInfoSet::ReadUUTItemMax(int &nUUTItemMax)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_temp=NULL;
	pEle_temp=m_pNode->FirstChildElement("UUTItemMax");//读取装备类型
	if(pEle_temp==NULL)
	{
		return 0;
	}
	CString str1 = pEle_temp->GetText();
	nUUTItemMax=atoi(str1); 
	return 1;
}

int CXml_UUTInfoSet::WriteUUTItemMax(int nUUTItemMax)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle = m_pNode->ToElement();
	TiXmlElement* pEle_UUTItemMax=NULL;
	pEle_UUTItemMax=m_pNode->FirstChildElement("UUTItemMax");//写入测试项目最大值
	if(pEle_UUTItemMax==NULL)
	{
		pEle_UUTItemMax = new TiXmlElement("UUTItemMax");
		pEle->LinkEndChild(pEle_UUTItemMax);
	}
	CString str1;
	str1.Format("%d", nUUTItemMax);
	TiXmlText UUTItemMax(str1);
	pEle_UUTItemMax->ReplaceChild(pEle_UUTItemMax->FirstChild(), UUTItemMax);
	return 1;
}

int CXml_UUTInfoSet::WriteUUTItemInfo(CArray<UUTItemInfo, UUTItemInfo> &rItemInfo)
{
	TiXmlElement* pEle_temp=NULL;
	UUTItemInfo itemif1;
	if(m_pNode == NULL)
	{	//m_pNode = new TiXmlNode();
		pEle_temp = new TiXmlElement("ItemInfo");
	}
	else
		pEle_temp = m_pNode->ToElement();
	//pEle_temp->SetValue("ItemInfo");
	pEle_temp->Clear();

	CString str1;
	for(int i = 0; i < rItemInfo.GetSize(); i++)
	{
		str1.Format("%d", rItemInfo[i].nKey);
		TiXmlElement* pEle_Child = new TiXmlElement("Key" + str1);
		//TiXmlAttribute* AttName = new TiXmlAttribute("Name");
		//TiXmlAttribute* AttNote = new TiXmlAttribute("Note");
		//AttName->SetValue(rItemInfo[i].strName);
		//AttNote->SetValue(rItemInfo[i].strNote);
		str1.Format("%d", i + 1);
		pEle_Child->SetAttribute("ID", str1);
		pEle_Child->SetAttribute("Name", rItemInfo[i].strName);
		pEle_Child->SetAttribute("Note", rItemInfo[i].strNote);
		pEle_Child->SetAttribute("Type", rItemInfo[i].strTestType);
		pEle_temp->LinkEndChild(pEle_Child);

	}
	return 1;
}

int CXml_UUTInfoSet::ReadInsList(vector<CString>* vInsList)
{
	TiXmlNode* pInsNode=m_pNode->NextSibling("InsSet");
	TiXmlNode* pNode_temp=NULL;
	for(pNode_temp=pInsNode->FirstChild();pNode_temp;pNode_temp=pNode_temp->NextSibling())
	{
		vInsList->push_back(pNode_temp->Value());
	}
	return 1;
}
