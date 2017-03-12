// Xml_Bll_UUTItem.cpp: implementation of the CXml_Bll_UUTItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "Xml_Bll_UUTItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_UUTItem::CXml_Bll_UUTItem()
{
	CFile_UUTInfo cUUTInfo;
	m_strStartPath=cUUTInfo.GetUUTStartPath();

}

CXml_Bll_UUTItem::~CXml_Bll_UUTItem()
{

}

/*
CString CXml_Bll_UUTItem::GetProgName(CString strKind, CString strModel, CString strItemName)
{
	CString strXmlPath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlPath);
	CXml_UUTItemVarSet xml_UUTVar(m_xmlOpe.pRootEle);
	return xml_UUTVar.GetProgName(strItemName);
}
*/

int CXml_Bll_UUTItem::GetItemList(CString strKind, CString strModel,vector<UUTItemVarSet>* vItemList)
{
	CString strXmlPath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\UUTInfo\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlPath);
	CXml_UUTItemVarSet xml_UUTVar(m_xmlOpe.pRootEle);
	return xml_UUTVar.ReadItemList(vItemList);
}

int CXml_Bll_UUTItem::GetItemInfo(CString strKind, CString strModel, CString strSolution,CString strItemKey, UUTItemVarSet* stuItemInfo)
{
	CString strXmlPath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Solution\\"+strSolution+"\\TestConfig\\"+strModel+".xml";
	m_xmlOpe.LoadXmlFile(strXmlPath);
	CXml_UUTItemVarSet xml_UUTVar(m_xmlOpe.pRootEle);
	return xml_UUTVar.GetItemInfo(stuItemInfo,strItemKey);
}
