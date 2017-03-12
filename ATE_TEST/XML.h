// XML.h: interface for the CXML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_)
#define AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//包含vector头文件
#include <vector>
using namespace std;
#include "ReadXML.h"
#include "Xml_PointVarSet.h"
//#include "Xml_UUTItemSet.h"
#include "Xml_TestPointSet.h"

struct VarItem
{
	CString logicName;
	CString Value;
	CString Unit;
	CString Name;
	CString ID;
};

struct TestPoint
{
	CString m_ID; //测试点编号
	CString m_Upper; //测试点上限
	CString m_Lower; //测试点下限
	CString m_Unit; //测试结果单位
	CString m_Col;   //结果列
	CString m_Line;  //结果行
};



class CXML  
{
public:
	CXML();
	virtual ~CXML();
	void SetXMLname(CString);
	void SetXMLPth(CString);
	void WriteXMLPoint(vector<VarItem>,vector<TestPoint>,int,int);

private:
	CString m_name;
	CString m_pth;
};

#endif // !defined(AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_)
