// Xml_PointVarSet.h: interface for the CXml_PointVarSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_POINTVARSET_H__D88A2C6F_8A2F_409A_A3A9_040F345EAA34__INCLUDED_)
#define AFX_XML_POINTVARSET_H__D88A2C6F_8A2F_409A_A3A9_040F345EAA34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

struct PointVarSet
{
	int m_intID;  //编号
	CString m_strLogicName; //逻辑名称 ,该名称与TP中一致
	CString m_strName;  //名称
	CString m_strValue; //数据
	CString m_strUnit; //单位
	struct PointVarSet* next;
};

class CXml_PointVarSet  
{
public:
	TiXmlElement* PointVar_Modify(TiXmlDocument* pDoc,PointVarSet stuPtVar);
	TiXmlElement* PointVar_Add(TiXmlDocument* pDoc,PointVarSet stuPtVar);
	int ReadVarList(vector<PointVarSet>* vPtVar);
	CXml_PointVarSet();
	CXml_PointVarSet(TiXmlElement* pEle_Parent);
	virtual ~CXml_PointVarSet();

	TiXmlNode* m_pNode;
	TiXmlElement* m_pEle_Parent;

};

#endif // !defined(AFX_XML_POINTVARSET_H__D88A2C6F_8A2F_409A_A3A9_040F345EAA34__INCLUDED_)
