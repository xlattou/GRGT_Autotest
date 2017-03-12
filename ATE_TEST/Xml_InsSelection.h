// Xml_InsSelection.h: interface for the CXml_InsSelection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_INSSELECTION_H__D86B86CC_7F2C_409D_A759_642983EDEEA7__INCLUDED_)
#define AFX_XML_INSSELECTION_H__D86B86CC_7F2C_409D_A759_642983EDEEA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct InsSelection
{
	CString m_strLogicName;
	CString m_strAddress;
	CString m_strChannel;
};

class CXml_InsSelection  
{
public:
	CXml_InsSelection();
	virtual ~CXml_InsSelection();

};

#endif // !defined(AFX_XML_INSSELECTION_H__D86B86CC_7F2C_409D_A759_642983EDEEA7__INCLUDED_)
