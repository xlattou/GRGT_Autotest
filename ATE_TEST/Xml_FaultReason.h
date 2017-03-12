// Xml_FaultReason.h: interface for the CXml_FaultReason class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_FAULTREASON_H__C8E1ED50_7B30_47CF_AF8E_9ECF3F1A608F__INCLUDED_)
#define AFX_XML_FAULTREASON_H__C8E1ED50_7B30_47CF_AF8E_9ECF3F1A608F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

struct stuFaultReason 
{
	int m_intID;
	CString m_strCardName;
	CString m_strFactor;
	CString m_strDescription;
};


class CXml_FaultReason  
{
public:
	int GetReasonList(vector<stuFaultReason>* vReasonList);
	CXml_FaultReason();
	CXml_FaultReason(TiXmlNode* pNode_Parent);
	virtual ~CXml_FaultReason();
	TiXmlNode* m_pNode;

};

#endif // !defined(AFX_XML_FAULTREASON_H__C8E1ED50_7B30_47CF_AF8E_9ECF3F1A608F__INCLUDED_)
