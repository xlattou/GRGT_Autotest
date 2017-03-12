// Xml_UUTFuncRequired.h: interface for the CXml_UUTFuncRequired class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTFUNCREQUIRED_H__D4FCEF11_B649_413C_9AB4_E60345D5A906__INCLUDED_)
#define AFX_XML_UUTFUNCREQUIRED_H__D4FCEF11_B649_413C_9AB4_E60345D5A906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct UUTFuncRequired
{
	CString m_strLFuncName;
	CString m_strFuncTypte;
	CString m_strFunction;
};

class CXml_UUTFuncRequired  
{
public:
	CXml_UUTFuncRequired();
	virtual ~CXml_UUTFuncRequired();

};

#endif // !defined(AFX_XML_UUTFUNCREQUIRED_H__D4FCEF11_B649_413C_9AB4_E60345D5A906__INCLUDED_)
