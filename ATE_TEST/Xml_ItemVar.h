// Xml_ItemVar.h: interface for the CXml_ItemVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_ITEMVAR_H__A9A55B89_6BB0_4CBE_B5A1_33116D39DDB8__INCLUDED_)
#define AFX_XML_ITEMVAR_H__A9A55B89_6BB0_4CBE_B5A1_33116D39DDB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PathOperate.h"
#include "XmlFile_Ope.h"
using namespace std;

struct ItemVar
{
	int m_intID;   //项目ID号/顺序号
	CString m_strLogicName;//项目逻辑名
	CString m_strValueMode;//数值表现模式 edit=输入型、enum=选项型
	CString m_strName; //变量名称
	CString m_strUnit; //变量单位
	CString m_strUpper; //变量输入上限
	CString m_strLower; //变量输入下限
	CString m_strNote; //备注
};

class CXml_ItemVar  
{
public:
	int ItemVar_Modify(ItemVar stucItemVar);
	int ItemVar_GenerateID();
	int ItemVar_Add(ItemVar stcItemVar);
	TiXmlNode* m_pNode;
	
	CXml_ItemVar();
	CXml_ItemVar(TiXmlNode* pNode_Parent);
	virtual ~CXml_ItemVar();

};

#endif // !defined(AFX_XML_ITEMVAR_H__A9A55B89_6BB0_4CBE_B5A1_33116D39DDB8__INCLUDED_)
