// Xml_UUTKind.cpp: implementation of the CXml_UUTKind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTKind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTKind::CXml_UUTKind()
{
	CPathOperate paOpe; //路径操作对象
	CString strPath_Kind=paOpe.GetStartPath();
	strPath_Kind+="DataInfo\\UUTKind.xml";
	m_xmlOpe.LoadXmlFile(strPath_Kind);
	
}

CXml_UUTKind::~CXml_UUTKind()
{
}

int CXml_UUTKind::GetKindList(vector<UUTKindList> *vKindList)
{
	CXml_UUTKindList xml_KindList(m_xmlOpe.pRootEle);   //构造类对象
	return xml_KindList.GetKindList(vKindList);
}

int CXml_UUTKind::CreatKind(CString strNewKind)
{
	CXml_UUTKindList xml_KindList(m_xmlOpe.pRootEle);
	if(xml_KindList.CreatKind(strNewKind) != 0)
		return m_xmlOpe.SaveFile();
	return 0;
}

int CXml_UUTKind::DeleteKind(CString strNewKind)
{
	CXml_UUTKindList xml_KindList(m_xmlOpe.pRootEle);
	if(xml_KindList.DeleteKind(strNewKind) != 0)
		return m_xmlOpe.SaveFile();
	return 0;
}