// Xml_Bll_PointVarInfo.h: interface for the CXml_Bll_PointVarInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_POINTVARINFO_H__7F1A2DCD_D363_46A5_999C_A57152F56CEC__INCLUDED_)
#define AFX_XML_BLL_POINTVARINFO_H__7F1A2DCD_D363_46A5_999C_A57152F56CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Document/templete.xml中对测试点变量的处理类
#include "File_UUTInfo.h"
#include "Xml_PointVarSet.h"
using namespace std;

class CXml_Bll_PointVarInfo  
{
public:
	int PointVar_Modify(TiXmlDocument* pDoc,TiXmlElement* pEle_Parent,CString strFreq);
	int PointVar_Add(TiXmlDocument* pDoc,TiXmlElement* pEle_Parent,CString strFreq);
	CString GetPtVarSetString(TiXmlElement* pEle_Parent);
	CString GetPtVarTestString(TiXmlElement* pEle_Parent);
//	CString GetPtVarTestString(CString strKind,CString strModel,CString strTem,CString strItemName,int intPtID);
	CXml_Bll_PointVarInfo();
	virtual ~CXml_Bll_PointVarInfo();
	TiXmlNode* m_pNode_Parent;

};

#endif // !defined(AFX_XML_BLL_POINTVARINFO_H__7F1A2DCD_D363_46A5_999C_A57152F56CEC__INCLUDED_)
