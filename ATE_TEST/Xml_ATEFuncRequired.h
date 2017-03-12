// Xml_ATEFuncRequired.h: interface for the CXml_ATEFuncRequired class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_ATEFUNCREQUIRED_H__26E98D5D_77ED_40D3_94C9_14544A165185__INCLUDED_)
#define AFX_XML_ATEFUNCREQUIRED_H__26E98D5D_77ED_40D3_94C9_14544A165185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ATEFuncRequired
{
	CString m_strLInsName;
	CString m_strLFuncName;
	CString m_strLFuncType;
	CString m_strFunction;
};

class CXml_ATEFuncRequired  
{
public:
	CXml_ATEFuncRequired();
	virtual ~CXml_ATEFuncRequired();

};

#endif // !defined(AFX_XML_ATEFUNCREQUIRED_H__26E98D5D_77ED_40D3_94C9_14544A165185__INCLUDED_)
