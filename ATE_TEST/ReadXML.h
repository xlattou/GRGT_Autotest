// ReadXML.h: interface for the CReadXML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READXML_H__C09C4269_BA50_4D94_867D_79EA23CF2238__INCLUDED_)
#define AFX_READXML_H__C09C4269_BA50_4D94_867D_79EA23CF2238__INCLUDED_

#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	CString logicName;
	CString chiName;
} VarName;

class CReadXML  
{
public:
	int ReadXMLList(CString XMLpath,CString XMLtitle,vector<CString>* vInsList);
	int CReadXML::ReadXMLThdList(CString XMLpath,CString FirTitle,CString SecTitle,CString ThdTitle,vector<VarName>* vInsList);
	CReadXML();
	virtual ~CReadXML();

};

#endif // !defined(AFX_READXML_H__C09C4269_BA50_4D94_867D_79EA23CF2238__INCLUDED_)
