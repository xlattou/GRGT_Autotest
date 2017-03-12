// Xml_UUTItemSet.h: interface for the CXml_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTITEMSET_H__1895691B_5F24_46CC_978B_0AA603416C99__INCLUDED_)
#define AFX_XML_UUTITEMSET_H__1895691B_5F24_46CC_978B_0AA603416C99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 //////////////////////////////***************Document/*.xml****************//////////////////////////////////
#include "XmlFile_Ope.h"
#include "Xml_Bll_UUTPointInfo.h"
using namespace std;

struct UUTItemSet
{
	CString m_strKey; //测试项目关键字
	int m_intID; //测试项目ID
	CString m_strItemName; //参数库项目名
	CString m_strMarkName;
	CString m_strResultCol;//测试结论放置Excel的列
	CString m_strResultRow;//测试结论放置Excel的行
	TestPointSet* m_pTestPoint;
};

class CXml_UUTItemSet  
{
public:
	int GetItemPosionByKey(CString strKeyName,UUTItemSet* stuItemSet);  //?????????Excel????????
	int ReadItemList(vector <UUTItemSet>* vItem);  //????????
	TiXmlNode* m_pNode;
	CXml_UUTItemSet();
	CXml_UUTItemSet(TiXmlElement* pRootEle);
	virtual ~CXml_UUTItemSet();

};

#endif // !defined(AFX_XML_UUTITEMSET_H__1895691B_5F24_46CC_978B_0AA603416C99__INCLUDED_)
