// Xml_UUTDriver.h: interface for the CXml_UUTDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTDRIVER_H__506A4E2B_C090_43F0_B6C3_335EF868BBE2__INCLUDED_)
#define AFX_XML_UUTDRIVER_H__506A4E2B_C090_43F0_B6C3_335EF868BBE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct UUTDriver
{
	CString m_strName; //驱动标识名
	CString m_strValue;//驱动实际对应的文件名
};

class CXml_UUTDriver  
{
public:
	CXml_UUTDriver();
	virtual ~CXml_UUTDriver();

};

#endif // !defined(AFX_XML_UUTDRIVER_H__506A4E2B_C090_43F0_B6C3_335EF868BBE2__INCLUDED_)
