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
	int m_intID;   //��ĿID��/˳���
	CString m_strLogicName;//��Ŀ�߼���
	CString m_strValueMode;//��ֵ����ģʽ edit=�����͡�enum=ѡ����
	CString m_strName; //��������
	CString m_strUnit; //������λ
	CString m_strUpper; //������������
	CString m_strLower; //������������
	CString m_strNote; //��ע
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
