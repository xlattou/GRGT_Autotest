// Xml_UUTItemVarSet.h: interface for the CXml_UUTItemVarSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTITEMVARSET_H__555204AF_FBFF_4B15_95D9_CE172DAA7719__INCLUDED_)
#define AFX_XML_UUTITEMVARSET_H__555204AF_FBFF_4B15_95D9_CE172DAA7719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////uutInfo/uut.xml中项目设置信息
#include "XmlFile_Ope.h"
#include <afxtempl.h>
using namespace std;

struct UUTItemVarSet
{
	int m_intID;
	CString m_strName;
	CString m_strProgName;
	CString m_strConnectPic;
	CString m_strConnectDescription;
};

class CXml_UUTItemVarSet  
{
public:
	int GetItemInfo(UUTItemVarSet* stucUUTItem,CString strItemName, bool bThrowErr = true);
	int GetItemInfoArray(CArray<UUTItemVarSet, UUTItemVarSet> &stucUUTItemVarSet);
	int WriteItemInfoArray(CArray<UUTItemVarSet, UUTItemVarSet> &stucUUTItemVarSet);
	int ReadItemList(vector<UUTItemVarSet>* vItemList);
	CString GetProgName(CString strItemName);
	CXml_UUTItemVarSet();
	CXml_UUTItemVarSet(TiXmlElement* pRootEle);
	virtual ~CXml_UUTItemVarSet();
	TiXmlNode* m_pNode;
	TiXmlElement* m_pEle;

};

#endif // !defined(AFX_XML_UUTITEMVARSET_H__555204AF_FBFF_4B15_95D9_CE172DAA7719__INCLUDED_)
