// Xml_Bll_UUTItemSet.h: interface for the CXml_Bll_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_UUTITEM_TEM_H__CFED4759_08C8_47FC_A112_FA33791FD8B0__INCLUDED_)
#define AFX_XML_BLL_UUTITEM_TEM_H__CFED4759_08C8_47FC_A112_FA33791FD8B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//document/tem.xml中对测试项目信息的处理类
#include "File_UUTInfo.h"
#include "Xml_UUTItemSet.h"
#include "ReadSolutionList.h"
#include "Xml_FrontPage.h"
using namespace std;


class CXml_Bll_UUTItem_Tem  
{
public:
	int GetItemPositonByKey(CString strTemPath,CString strKeyName,UUTItemSet* stucItem);
	int ReadSolutionList(CString strKind,CString strModel,CString strtem,vector <CString>* vSolutionName);
	int WriteSolutionList(CString strKind, CString strModel, CString strtem, CStringArray& strSolutionArray);
	int ReadUUTItemList(CString strKind,CString strModel,CString strtem,vector <UUTItemSet>* vItem);
	int ReadFrontPageList(CString strPath, CString &strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage);//读取首页信息
	int WriteFrontPageList(CString strKind,CString strModel,CString strtem, CString strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage);//保存首页信息
//	int ReadUUTItemList(TiXmlElement*pRootEle,vector <UUTItemSet>* vItem);
//	int ReadUUTItemInfo(TiXmlElement* pRootEle,int intItemID,UUTItemSet *stucUUTItem);
//	TiXmlNode* ReadUUTItemInfo(CString strKind,CString strModel,CString strItemName,UUTItemSet *stucUUTItem);
	CString m_strStartPath;
	CXmlFile_Ope m_xmlOpe;

	CXml_Bll_UUTItem_Tem();
	virtual ~CXml_Bll_UUTItem_Tem();
	TiXmlNode* m_pNode;

};

#endif // !defined(AFX_XML_BLL_UUTITEMSET_H__CFED4759_08C8_47FC_A112_FA33791FD8B0__INCLUDED_)
