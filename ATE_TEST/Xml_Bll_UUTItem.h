// Xml_Bll_UUTItem.h: interface for the CXml_Bll_UUTItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_UUTITEM_H__E1403B47_5742_4B7E_9150_1B1D74D1322D__INCLUDED_)
#define AFX_XML_BLL_UUTITEM_H__E1403B47_5742_4B7E_9150_1B1D74D1322D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "File_UUTInfo.h"
#include "Xml_UUTItemVarSet.h"
using namespace std;


class CXml_Bll_UUTItem  
{
public:
	int GetItemInfo(CString strKind, CString strModel,CString strSolution,CString strItemKey, UUTItemVarSet* stuItemInfo);
	int GetItemList(CString strKind, CString strModel,vector<UUTItemVarSet>* vItemList);
//	CString GetProgName(CString strKind,CString strModel, CString strSolution,CString strItemKey);
	CXml_Bll_UUTItem();
	CString m_strStartPath;
	CXmlFile_Ope m_xmlOpe;
	virtual ~CXml_Bll_UUTItem();

};

#endif // !defined(AFX_XML_BLL_UUTITEM_H__E1403B47_5742_4B7E_9150_1B1D74D1322D__INCLUDED_)
