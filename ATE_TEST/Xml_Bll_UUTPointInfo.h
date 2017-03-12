// Xml_Bll_UUTPointInfo.h: interface for the CXml_Bll_UUTPointInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_UUTPOINTINFO_H__EE0A1151_274A_4A7B_8AD8_85C596D630C9__INCLUDED_)
#define AFX_XML_BLL_UUTPOINTINFO_H__EE0A1151_274A_4A7B_8AD8_85C596D630C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//document/tem.xml中对测试点信息的处理类
#include "File_UUTInfo.h"
#include "Xml_TestPointSet.h"
using namespace std;

class CXml_Bll_UUTPointInfo  
{
public:
	int Point_Delete(CString strKind,CString strModel,CString strTestTem,CString strItemName,int intID);
	TiXmlNode* Point_Modify(CString strKind,CString strModel,CString strTestTem,CString strItemName,TestPointSet stuPtSet);
	TiXmlElement* Point_Add(CString strKind,CString strModel,CString strTestTem,CString strItemName,TestPointSet stuPtSet);
	int ReadUUTPointList(TiXmlNode* pNode_Item,CString strItemName,vector<TestPointSet>* vPoint);
	int ReadPointInfo(CString strKind,CString strModel,CString strTestTem,CString strItemName,int intPtID,TestPointSet* stucPtSet);
	TiXmlElement* ReadPointInfo(TiXmlNode* pNode_Parent,CString strItemName, int intPtID,TestPointSet* stucPtSet);
	TiXmlElement* ReadPointInfo(TiXmlNode* pNode_Parent,int intPtID,TestPointSet* stucPtSet);
	CXml_Bll_UUTPointInfo();
	virtual ~CXml_Bll_UUTPointInfo();
	TiXmlNode* GetPointNode(int intPointID);
	TiXmlNode* GetPointNode(CString strKind,CString strModel,CString strTestTem,CString strItemName,int intPointID);

	CXmlFile_Ope m_xmlOpe;
	CString m_strStartPath;
	TiXmlNode* m_pNode_Parent;

};

#endif // !defined(AFX_XML_BLL_UUTPOINTINFO_H__EE0A1151_274A_4A7B_8AD8_85C596D630C9__INCLUDED_)
