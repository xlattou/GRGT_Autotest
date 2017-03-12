// Xml_RemotePort.h: interface for the CXml_RemotePort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_REMOTEPORT_H__E58787BB_B042_45CE_9A14_BE1C740BC71B__INCLUDED_)
#define AFX_XML_REMOTEPORT_H__E58787BB_B042_45CE_9A14_BE1C740BC71B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct RemotePort
{
	CString m_strName;
	CString m_strValue;
};

class CXml_RemotePort  
{
public:
	CXml_RemotePort();
	virtual ~CXml_RemotePort();

};

#endif // !defined(AFX_XML_REMOTEPORT_H__E58787BB_B042_45CE_9A14_BE1C740BC71B__INCLUDED_)
