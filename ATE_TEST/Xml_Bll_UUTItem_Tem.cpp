// Xml_Bll_UUTItemSet.cpp: implementation of the CXml_Bll_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Bll_UUTItem_Tem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_UUTItem_Tem::CXml_Bll_UUTItem_Tem()
{
	CFile_UUTInfo file_UUTInfo;
	m_strStartPath=file_UUTInfo.GetUUTStartPath();
}

CXml_Bll_UUTItem_Tem::~CXml_Bll_UUTItem_Tem()
{

}
/*
int CXml_Bll_UUTItem_Tem::ReadUUTItemInfo(TiXmlElement* pRootEle,int intItemID,UUTItemSet *stucUUTItem)
{
	/*
	CXml_UUTItemSet xml_UUTItem(pRootEle);
	m_pNode=xml_UUTItem.m_pNode;
	return xml_UUTItem.ReadItemInfo(stucUUTItem,intItemID);
	
	return 1;
}

TiXmlNode* CXml_Bll_UUTItem_Tem::ReadUUTItemInfo(CString strKind,CString strModel,CString strItemName,UUTItemSet *stucUUTItem)
{
	/*
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\"+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTItemSet xml_UUTItem(m_xmlOpe.pRootEle);
	//m_pNode=xml_UUTItem.m_pNode;
	return xml_UUTItem.ReadItemInfo(stucUUTItem,strItemName);
	
	return NULL;
}


int CXml_Bll_UUTItem_Tem::ReadUUTItemList(TiXmlElement*pRootEle,vector <UUTItemSet>* vItem)
{
	CXml_UUTItemSet xml_UUTItem(pRootEle); //
	m_pNode=xml_UUTItem.m_pNode; //测试项目根节点指针
	return xml_UUTItem.ReadItemList(vItem);
}
*/
int CXml_Bll_UUTItem_Tem::ReadUUTItemList(CString strKind,CString strModel,CString strtem,vector <UUTItemSet>* vItem)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strtem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTItemSet xml_UUTItem(m_xmlOpe.pRootEle);
	m_pNode=xml_UUTItem.m_pNode; //测试项目根节点指针
	return xml_UUTItem.ReadItemList(vItem);
}

int CXml_Bll_UUTItem_Tem::ReadSolutionList(CString strKind,CString strModel,CString strtem,vector <CString>* vSolutionName)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strtem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CReadSolutionList xml_SoluList(m_xmlOpe.pRootEle);
	m_pNode=xml_SoluList.m_pNode;
	return xml_SoluList.ReadSolutionList(vSolutionName);
}

int CXml_Bll_UUTItem_Tem::WriteSolutionList(CString strKind, CString strModel, CString strtem, CStringArray& strSolutionArray)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strtem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CReadSolutionList xml_SoluList(m_xmlOpe.pRootEle);
	m_pNode=xml_SoluList.m_pNode;
	xml_SoluList.WriteSolutionList(strSolutionArray);
	if(xml_SoluList.m_pNode == NULL)
		m_xmlOpe.pRootEle->LinkEndChild(xml_SoluList.m_pEle);
	return m_xmlOpe.SaveFile();
}

int CXml_Bll_UUTItem_Tem::ReadFrontPageList(CString strPath, CString &strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage)
{
	m_xmlOpe.LoadXmlFile(strPath);
	CXml_FrontPage frontPage1(m_xmlOpe.pRootEle);
	return frontPage1.ReadFrontPageList(strSheetNumber, vFrontPage);
}

int CXml_Bll_UUTItem_Tem::WriteFrontPageList(CString strKind,CString strModel,CString strtem, CString strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strtem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_FrontPage frontPage1(m_xmlOpe.pRootEle);
	frontPage1.WriteFrontPageList(strSheetNumber, vFrontPage);
	return m_xmlOpe.SaveFile();
}

int CXml_Bll_UUTItem_Tem::GetItemPositonByKey(CString strTemPath,CString strKeyName,UUTItemSet* stucItem)
{
	CPathOperate paOpe;
    CString strXmlFilePath=paOpe.GetStartPath()+strTemPath+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);
	CXml_UUTItemSet xml_UUTItem(m_xmlOpe.pRootEle);
	return xml_UUTItem.GetItemPosionByKey(strKeyName,stucItem);
}