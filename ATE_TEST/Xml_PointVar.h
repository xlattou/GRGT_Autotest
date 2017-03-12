// Xml_PointVar.h: interface for the CXml_PointVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_POINTVAR_H__2B1EEBBD_A38F_41D1_99CA_EA03D385C9AE__INCLUDED_)
#define AFX_XML_POINTVAR_H__2B1EEBBD_A38F_41D1_99CA_EA03D385C9AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct PointVar
{
	int m_intID;
	CString m_strLogicName;
	CString m_strName;
	CString m_strUpper;
	CString m_strLower;
	CString m_strNote;
};

class CXml_PointVar  
{
public:
	CXml_PointVar();
	virtual ~CXml_PointVar();

};

#endif // !defined(AFX_XML_POINTVAR_H__2B1EEBBD_A38F_41D1_99CA_EA03D385C9AE__INCLUDED_)
