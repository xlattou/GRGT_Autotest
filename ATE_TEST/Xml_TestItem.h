// Xml_TestItem.h: interface for the CXml_TestItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_TESTITEM_H__4ECC4F7F_8EA9_460E_BA52_394F2CD974BC__INCLUDED_)
#define AFX_XML_TESTITEM_H__4ECC4F7F_8EA9_460E_BA52_394F2CD974BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct TestItem
{
	int m_intID;
	CString m_strItemKind;
	CString m_strItemName;
	CString m_strFileName;
	CString m_strUnit;
	CString m_strProgName;
	CString m_strFileType;
	CString m_strNote;
};


class CXml_TestItem  
{
public:
	CXml_TestItem();
	virtual ~CXml_TestItem();

};

#endif // !defined(AFX_XML_TESTITEM_H__4ECC4F7F_8EA9_460E_BA52_394F2CD974BC__INCLUDED_)
