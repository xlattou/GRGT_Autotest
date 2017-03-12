// ReadSolutionList.h: interface for the CReadSolutionList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READSOLUTIONLIST_H__5F1B82DF_C461_4BD4_9CC2_8C659CD15225__INCLUDED_)
#define AFX_READSOLUTIONLIST_H__5F1B82DF_C461_4BD4_9CC2_8C659CD15225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlFile_Ope.h"
using namespace std;

class CReadSolutionList  
{
public:
	int ReadSolutionList(vector<CString> *vSoluList);
	int WriteSolutionList(CStringArray &strSoluArray);
	CReadSolutionList();
	CReadSolutionList(TiXmlElement *pRootEle);
	virtual ~CReadSolutionList();
	TiXmlNode* m_pNode;
	TiXmlElement* m_pEle;
};

#endif // !defined(AFX_READSOLUTIONLIST_H__5F1B82DF_C461_4BD4_9CC2_8C659CD15225__INCLUDED_)
