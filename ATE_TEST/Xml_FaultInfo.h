// Xml_FaultInfo.h: interface for the CXml_FaultInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_FAULTINFO_H__795CB596_89F5_4959_AF16_EC82ECA5362A__INCLUDED_)
#define AFX_XML_FAULTINFO_H__795CB596_89F5_4959_AF16_EC82ECA5362A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

struct stuFaultInfo 
{
	int m_intID;  //故障ID
	CString m_strName;  //故障现象名称
	CString m_strAdviseFileName; //故障建议文件名
};

class CXml_FaultInfo  
{
public:
	TiXmlNode* GetFaultNode(int intID);  //获取某一故障的节点
	TiXmlNode* GetFaultNode(CString strFaultName);  //获取某一故障的节点
	int GetFaultList(vector<stuFaultInfo>* vFaultList);
	CXml_FaultInfo();
	CXml_FaultInfo(TiXmlElement *pEle);
	virtual ~CXml_FaultInfo();
	TiXmlNode* m_pNode;

};

#endif // !defined(AFX_XML_FAULTINFO_H__795CB596_89F5_4959_AF16_EC82ECA5362A__INCLUDED_)
