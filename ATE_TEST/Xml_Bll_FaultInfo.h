// Xml_Bll_FaultInfo.h: interface for the CXml_Bll_FaultInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_FAULTINFO_H__164522C4_3115_4C30_B87D_F2F6478724F2__INCLUDED_)
#define AFX_XML_BLL_FAULTINFO_H__164522C4_3115_4C30_B87D_F2F6478724F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "File_UUTInfo.h"
#include "XmlFile_Ope.h"
#include "Xml_FaultInfo.h"
using namespace std;

struct TestItemState 
{ //用来存放测试结果信息,从而进行故障判断和结果处理
	int m_intPointID;
	CString m_strItemName; //项目名称
	CString m_strFreq; //测试频率
	CString m_strUpper; //上限
	CString m_strLower;//下限
	CString m_strResult; //测试结果
	CString m_strUnit; //单位
	CString m_strState; //项目结论
	CString m_strFault; //项目故障现象描述
};

struct FaultItemInfo 
{
	CString m_strItemName;
	CString m_strFault;
	CString m_strState;
};


class CXml_Bll_FaultInfo  
{
public:
	void FaultInfoConvert(vector <TestItemState> vItemState,vector<FaultItemInfo>* vFaultItemInfo);
	TiXmlNode* GetFaultNode(CString strKind,CString strModel,int intID);
	TiXmlNode* GetFaultNode(CString strKind,CString strModel,CString strFaultName);
	int GetFaultList(CString strKind,CString strModel,vector<stuFaultInfo>* vFaultList);
	CXml_Bll_FaultInfo();
	virtual ~CXml_Bll_FaultInfo();
	CString m_strStartPath;
	CXmlFile_Ope m_xmlOpe;

};

#endif // !defined(AFX_XML_BLL_FAULTINFO_H__164522C4_3115_4C30_B87D_F2F6478724F2__INCLUDED_)
