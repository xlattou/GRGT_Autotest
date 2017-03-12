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
	int m_intID; //测试点编号
	CString m_strUpper; //测试点上限
	CString m_strLower; //测试点下限
	CString m_strResultMark; //测试结果标识名
	CString m_strResultUnit; //测试结果单位
	CString m_strCol;   //结果列
	CString m_strLine;  //结果行
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
