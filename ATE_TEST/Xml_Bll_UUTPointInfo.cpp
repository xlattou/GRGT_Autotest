// Xml_Bll_UUTPointInfo.cpp: implementation of the CXml_Bll_UUTPointInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Bll_UUTPointInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_UUTPointInfo::CXml_Bll_UUTPointInfo()
{
	CFile_UUTInfo file_UUTInfo;
	m_strStartPath=file_UUTInfo.GetUUTStartPath();
}

CXml_Bll_UUTPointInfo::~CXml_Bll_UUTPointInfo()
{

}

int CXml_Bll_UUTPointInfo::ReadPointInfo(CString strKind,CString strModel,CString strTestTem,CString strItemName,int intPtID,TestPointSet* stucPtSet)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strTestTem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);  //加载xml文件
	m_pNode_Parent=m_xmlOpe.pRootEle->FirstChild("ItemSet")->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	xml_PointSet.ReadPointInfo(stucPtSet,intPtID);
	return 1;
}


TiXmlElement* CXml_Bll_UUTPointInfo::ReadPointInfo(TiXmlNode* pNode_Granpa,CString strItemName,int intPtID,TestPointSet* stucPtSet)
{ //本函数中的PNode_Parent为项目总节点指针
	m_pNode_Parent=pNode_Granpa->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.ReadPointInfo(stucPtSet,intPtID);
}
TiXmlElement* CXml_Bll_UUTPointInfo::ReadPointInfo(TiXmlNode* pNode_Parent,int intPtID,TestPointSet* stucPtSet)
{ 
	CXml_TestPointSet xml_PointSet(pNode_Parent);
	return xml_PointSet.ReadPointInfo(stucPtSet,intPtID);
}

TiXmlNode* CXml_Bll_UUTPointInfo::GetPointNode(int intPointID)
{
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.GetPointNode(intPointID);
}

int CXml_Bll_UUTPointInfo::ReadUUTPointList(TiXmlNode* pNode_Item,CString strItemName,vector<TestPointSet>* vPoint)
{
	m_pNode_Parent=pNode_Item->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.ReadPointList(vPoint);
}

TiXmlNode* CXml_Bll_UUTPointInfo::GetPointNode(CString strKind,CString strModel,CString strTestTem,CString strItemName, int intPointID)
{//本函数中的PNode_Parent为某一项目节点指针
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strTestTem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);  //加载xml文件
	m_pNode_Parent=m_xmlOpe.pRootEle->FirstChild("ItemSet")->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.GetPointNode(intPointID);
}

TiXmlElement* CXml_Bll_UUTPointInfo::Point_Add(CString strKind,CString strModel,CString strTestTem,CString strItemName,TestPointSet stuPtSet)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strTestTem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);  //加载xml文件
	m_pNode_Parent=m_xmlOpe.pRootEle->FirstChild("ItemSet")->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.Point_Add(m_xmlOpe.pDoc,stuPtSet);
}

TiXmlNode* CXml_Bll_UUTPointInfo::Point_Modify(CString strKind,CString strModel,CString strTestTem,CString strItemName,TestPointSet stuPtSet)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strTestTem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);  //加载xml文件
	m_pNode_Parent=m_xmlOpe.pRootEle->FirstChild("ItemSet")->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);
	return xml_PointSet.Point_Modify(m_xmlOpe.pDoc,stuPtSet);
}

int CXml_Bll_UUTPointInfo::Point_Delete(CString strKind,CString strModel,CString strTestTem,CString strItemName,int intID)
{
	CString strXmlFilePath=m_strStartPath+strKind
		+"\\TPS\\"+strModel+"\\Document\\"+strTestTem+".xml";
	m_xmlOpe.LoadXmlFile(strXmlFilePath);  //加载xml文件
	m_pNode_Parent=m_xmlOpe.pRootEle->FirstChild("ItemSet")->FirstChild(strItemName);
	CXml_TestPointSet xml_PointSet(m_pNode_Parent);

	return xml_PointSet.Point_Delete(m_xmlOpe.pDoc,intID);
}
