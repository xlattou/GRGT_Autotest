// Xml_UUTSet.cpp: implementation of the CXml_UUTSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTInfo::CXml_UUTInfo()
{
	CFile_UUTInfo file_UUTInfo;
	m_strStartPath=file_UUTInfo.GetUUTStartPath();
}

CXml_UUTInfo::~CXml_UUTInfo()
{

}

int CXml_UUTInfo::ReadUUTBasicInfo(CString strKind,CString strModel, UUTInfoSet *stucUUTInfo)
{
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTInfoSet xml_UUTInfoSet(m_xmlOpe.pRootEle, "BasicInfo");
	xml_UUTInfoSet.ReadUUTInfo(stucUUTInfo);
	return 1;
}

int CXml_UUTInfo::WriteUUTBasicInfo(CString strKind,CString strModel, UUTInfoSet *stucUUTInfo)
{
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTInfoSet xml_UUTInfoSet(m_xmlOpe.pRootEle, "BasicInfo");
	xml_UUTInfoSet.WriteUUTInfo(stucUUTInfo);
	m_xmlOpe.SaveFile();
	return 1;
}

int	CXml_UUTInfo::ReadUUTItemInfo(CString strKind, CString strModel, CArray<UUTItemInfo, UUTItemInfo> &rItemInfo, int &nUUTItemMax)
{
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTInfoSet xml_UUTInfoSetMax(m_xmlOpe.pRootEle, "BasicInfo");
	xml_UUTInfoSetMax.ReadUUTItemMax(nUUTItemMax);

	CXml_UUTInfoSet xml_UUTInfoSet(m_xmlOpe.pRootEle, "ItemInfo");
	xml_UUTInfoSet.ReadUUTItemInfo(rItemInfo);
	return 1;
}

int	CXml_UUTInfo::WriteUUTItemInfo(CString strKind, CString strModel, CArray<UUTItemInfo, UUTItemInfo> &rItemInfo, int nUUTItemMax)
{
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	
	CXml_UUTInfoSet xml_UUTInfoSetMax(m_xmlOpe.pRootEle, "BasicInfo");
	if(xml_UUTInfoSetMax.m_pNode == NULL)
	{
		TiXmlElement* pEle = new  TiXmlElement("BasicInfo");
		m_xmlOpe.pRootEle->LinkEndChild(pEle);
		xml_UUTInfoSetMax.m_pNode = m_xmlOpe.pRootEle->FirstChild("BasicInfo");
	}
	xml_UUTInfoSetMax.WriteUUTItemMax(nUUTItemMax);

	CXml_UUTInfoSet xml_UUTInfoSet(m_xmlOpe.pRootEle, "ItemInfo");
	if(xml_UUTInfoSet.m_pNode == NULL)
	{
		TiXmlElement* pEle = new  TiXmlElement("ItemInfo");
		m_xmlOpe.pRootEle->LinkEndChild(pEle);
		xml_UUTInfoSet.m_pNode = m_xmlOpe.pRootEle->FirstChild("ItemInfo");
	}

	xml_UUTInfoSet.WriteUUTItemInfo(rItemInfo);
	m_xmlOpe.SaveFile();
	return 1;
}
/*
//将型号、分组信息列在树列表中
int CXml_UUTInfo::FillTreeView(CTreeCtrl* pTree)
{
	HTREEITEM hFirstItem=pTree->GetFirstVisibleItem();
	CString strPath_Model;
	CFileFind ff;
	BOOL res=false;
	HTREEITEM hItem_Model=NULL;
	TiXmlElement *pEle=NULL;
	TiXmlNode* pNode=NULL;
	int intSortID=0;
	HTREEITEM hItem_Sort=NULL;	
	for(HTREEITEM hItem=hFirstItem;hItem;hItem=pTree->GetNextSiblingItem(hItem))
	{
		strPath_Model=m_strPathFolder+pTree->GetItemText(hItem)+"\\*.*"; //获取型号所在的路径
		res=ff.FindFile(strPath_Model);
		while(res)
		{
			res=ff.FindNextFile();
			if(GetXmlPath(&ff))
			{
				hItem_Model=pTree->InsertItem(ff.GetFileTitle(),hItem);
				LoadXmlSetFile();


	            pNode=m_pRootEle_Set->FirstChild("测试分组");
				if(!pNode)
				{
					ThrowErr(XML文件中找不到测试分组节点);
					return 0;
				}

            	for(pNode=pNode->FirstChild();pNode;pNode=pNode->NextSibling())
				{
            		pEle=pNode->ToElement();
	            	hItem_Sort=pTree->InsertItem(pNode->Value(),hItem_Model);	
	            	pEle->Attribute("ID",&intSortID);
	            	pTree->SetItemData(hItem_Sort,intSortID); //插入ID
				}	

			}
		}

	}

	return 1;
}
*/



int CXml_UUTInfo::GetInsList(CString strKind,CString strModel,vector<CString>* vInsList)
{
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTInfoSet xml_UUTInfoSet(m_xmlOpe.pRootEle, "BasicInfo");
    return xml_UUTInfoSet.ReadInsList(vInsList);
}

int CXml_UUTInfo::CreatModelInfo(CString strKind, CString strFactory, CString strModelType)
{
	CString strModel = strFactory + " " + strModelType;
	CString strXmlFilePath=m_strStartPath+strKind+"\\TPS\\"
		+strModel+"\\UUTInfo\\"+strModel+".xml";

	TiXmlDeclaration *dec	= new TiXmlDeclaration("1.0","gb2312","");
	TiXmlElement *Model		= new TiXmlElement(strFactory + "_" + strModelType);
	TiXmlElement *BasicInfo = new TiXmlElement("BasicInfo");
	TiXmlElement *ItemInfo	= new TiXmlElement("ItemInfo");

	TiXmlElement *UUTKind = new TiXmlElement("UUTKind");
	TiXmlElement *Name = new TiXmlElement("Name");
	TiXmlElement *Factory = new TiXmlElement("Factory");
	TiXmlElement *ModelType = new TiXmlElement("Model");

	TiXmlText *UUTKindText = new TiXmlText(strKind);
	TiXmlText *NameText = new TiXmlText(strKind);
	TiXmlText *FactoryText = new TiXmlText(strFactory);
	TiXmlText *ModelTypeText = new TiXmlText(strModelType);

	m_xmlOpe.pDoc->LinkEndChild(dec);
	m_xmlOpe.pDoc->LinkEndChild(Model);
	Model->LinkEndChild(BasicInfo);
	Model->LinkEndChild(ItemInfo);

	BasicInfo->LinkEndChild(UUTKind);
	BasicInfo->LinkEndChild(Name);
	BasicInfo->LinkEndChild(Factory);
	BasicInfo->LinkEndChild(ModelType);

	UUTKind->LinkEndChild(UUTKindText);
	Name->LinkEndChild(NameText);
	Factory->LinkEndChild(FactoryText);
	ModelType->LinkEndChild(ModelTypeText);

	if(!m_xmlOpe.pDoc->SaveFile(strXmlFilePath))
		return 0;
	else
		return 1;
}

int CXml_UUTInfo::CreatTemplateInfo(CString strFilePath, CString strRoot)//创建模板
{
	TiXmlDeclaration *dec		= new TiXmlDeclaration("1.0","gb2312","");
	TiXmlElement *eRoot			= new TiXmlElement(strRoot);
	TiXmlElement *FirstPaper	= new TiXmlElement("FirstPaper");
	TiXmlElement *SolutionList	= new TiXmlElement("SolutionList");
	TiXmlElement *ItemSet		= new TiXmlElement("ItemSet");

	m_xmlOpe.pDoc->LinkEndChild(dec);
	m_xmlOpe.pDoc->LinkEndChild(eRoot);
	eRoot->LinkEndChild(FirstPaper);
	eRoot->LinkEndChild(SolutionList);
	eRoot->LinkEndChild(ItemSet);

	if(!m_xmlOpe.pDoc->SaveFile(strFilePath))
		return 0;
	else
		return 1;
}