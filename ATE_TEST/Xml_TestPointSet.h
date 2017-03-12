// Xml_TestPointSet.h: interface for the CXml_TestPointSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_TESTPOINTSET_H__9D39F23B_CC00_48E6_8115_43A299AE363B__INCLUDED_)
#define AFX_XML_TESTPOINTSET_H__9D39F23B_CC00_48E6_8115_43A299AE363B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
#include "Xml_PointVarSet.h"
using namespace std;

struct TestPointSet
{
	int m_intID; //���Ե���
	CString m_strUpper; //���Ե�����
	CString m_strLower; //���Ե�����
	CString m_strResultMark; //���Խ����ʶ��
	CString m_strResultUnit; //���Խ����λ
	CString m_strCol;   //�����
	CString m_strLine;  //�����
	struct TestPointSet* next;
	PointVarSet* m_VarSet;
};

class CXml_TestPointSet  
{
public:
	int Point_Delete(TiXmlDocument *pDoc,int intID);
	TiXmlNode* Point_Modify(TiXmlDocument* pDoc,TestPointSet stuTestPt);
	int GenerateID();
	TiXmlElement* Point_Add(TiXmlDocument* pDoc,TestPointSet stuTestPt);
	int ReadPointList(vector <TestPointSet>* vPoint);
	TiXmlElement* ReadPointInfo(TestPointSet* stucTestPtSet,int intPointID);
	TiXmlNode* GetPointNode(int intPointID);

	CXml_TestPointSet();
	CXml_TestPointSet(TiXmlNode* pNode_Parent);
	virtual ~CXml_TestPointSet();
	TiXmlNode* m_pNode;
	TiXmlNode* m_pNode_Parent;

};

#endif // !defined(AFX_XML_TESTPOINTSET_H__9D39F23B_CC00_48E6_8115_43A299AE363B__INCLUDED_)
