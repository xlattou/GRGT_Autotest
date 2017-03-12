// Xml_UUTInfoSet.h: interface for the CXml_UUTInfoSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTINFOSET_H__132C66E7_E0CF_42A7_BF76_9AF6D2B82129__INCLUDED_)
#define AFX_XML_UUTINFOSET_H__132C66E7_E0CF_42A7_BF76_9AF6D2B82129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
#include <afxtempl.h>
using namespace std;

struct UUTInfoSet
{
	CString m_strUUTKind;
	CString m_strName;
	CString m_strModel;
	CString m_strFactory;
	CString m_strTestTem;
	CString m_strTestConfig;
	CString m_strNote;
	CString m_strAtten;
	CString m_strRemotePort;
	CString m_strTestMode;
};

struct UUTItemInfo
{
	int		nKey;
	CString strName;
	CString strNote;
	CString strTestType;//0:Test, 1:control
};

class CXml_UUTInfoSet  
{
public:
	int ReadInsList(vector<CString>* vInsList);
	int ReadUUTInfo(UUTInfoSet* stucUUTInfo);
	int WriteUUTInfo(UUTInfoSet* stucUUTInfo);
	int ReadUUTItemInfo(CArray<UUTItemInfo, UUTItemInfo> &rItemInfo);
	int WriteUUTItemInfo(CArray<UUTItemInfo, UUTItemInfo> &rItemInfo);
	int ReadUUTItemMax(int &nUUTItemMax);
	int WriteUUTItemMax(int nUUTItemMax);
	TiXmlNode* m_pNode;
	CXml_UUTInfoSet(TiXmlElement* pRootEle, CString strFirstChild);
	CXml_UUTInfoSet();

	virtual ~CXml_UUTInfoSet();

};

#endif // !defined(AFX_XML_UUTINFOSET_H__132C66E7_E0CF_42A7_BF76_9AF6D2B82129__INCLUDED_)
