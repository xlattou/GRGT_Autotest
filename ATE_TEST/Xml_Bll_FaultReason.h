// Xml_Bll_FaultReason.h: interface for the CXml_Bll_FaultReason class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_BLL_FAULTREASON_H__BA9AFBD5_AC46_4E8F_B990_CF59F5EF5909__INCLUDED_)
#define AFX_XML_BLL_FAULTREASON_H__BA9AFBD5_AC46_4E8F_B990_CF59F5EF5909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "File_UUTInfo.h"
#include "XmlFile_Ope.h"
#include "Xml_FaultReason.h"

class CXml_Bll_FaultReason  
{
public:
	void ModifyReasonAdd(vector<stuFaultReason>* vReasonListA_Result, vector<stuFaultReason>* vReasonListB); //�Թ�һ��Ĺ���ԭ����м�Ȩ����
	int GetModifyReasonList(TiXmlNode* pNode_Parent,vector<stuFaultReason>* vReasonList);
	void SortReasonList(vector<stuFaultReason> *vReasonList); //����ԭ���һ������������ʵ�С��������
	CXml_Bll_FaultReason();
	virtual ~CXml_Bll_FaultReason();
	CString m_strStartPath;
	CXmlFile_Ope m_xmlOpe;

};

#endif // !defined(AFX_XML_BLL_FAULTREASON_H__BA9AFBD5_AC46_4E8F_B990_CF59F5EF5909__INCLUDED_)
