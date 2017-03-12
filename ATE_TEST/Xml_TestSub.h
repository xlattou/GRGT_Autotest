// Xml_TestSub.h: interface for the CXml_TestSub class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_TESTSUB_H__0C408CCB_2901_4D3E_9311_59D6996C5623__INCLUDED_)
#define AFX_XML_TESTSUB_H__0C408CCB_2901_4D3E_9311_59D6996C5623__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

struct TestSub
{
	int m_intID;
	CString m_strName;
};

class CXml_TestSub  
{
public:
	int Sub_ReadList(vector<TestSub> *vSubList);
	TiXmlNode* m_pNode;
	CXml_TestSub();
	CXml_TestSub(TiXmlElement* pRootEle);
	virtual ~CXml_TestSub();
};

#endif // !defined(AFX_XML_TESTSUB_H__0C408CCB_2901_4D3E_9311_59D6996C5623__INCLUDED_)
