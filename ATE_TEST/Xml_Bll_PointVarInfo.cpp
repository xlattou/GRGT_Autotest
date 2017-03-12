// Xml_Bll_PointVarInfo.cpp: implementation of the CXml_Bll_PointVarInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Bll_PointVarInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_PointVarInfo::CXml_Bll_PointVarInfo()
{

}

CXml_Bll_PointVarInfo::~CXml_Bll_PointVarInfo()
{

}

CString CXml_Bll_PointVarInfo::GetPtVarSetString(TiXmlElement* pEle_Parent)
{
	vector<PointVarSet> vPtVar;

	CXml_PointVarSet xml_ptVarSet(pEle_Parent);
	xml_ptVarSet.ReadVarList(&vPtVar);
	CString strRet="";
	for(int i=0;i<vPtVar.size();i++)
	{
		strRet+=vPtVar[i].m_strName+"=";
		strRet+=vPtVar[i].m_strValue;
		strRet+=vPtVar[i].m_strUnit+";";
	}
	strRet=strRet.Left(strRet.GetLength()-1);

	return strRet;
}

CString CXml_Bll_PointVarInfo::GetPtVarTestString(TiXmlElement* pEle_Parent)
{
	vector<PointVarSet> vPtVar;
	
	CXml_PointVarSet xml_ptVarSet(pEle_Parent);
	xml_ptVarSet.ReadVarList(&vPtVar);
	CString strRet="";
	for(int i=0;i<vPtVar.size();i++)
	{
		strRet+=vPtVar[i].m_strLogicName
			+"="+vPtVar[i].m_strValue+"_"+vPtVar[i].m_strUnit
			+";";
	}
	strRet=strRet.Left(strRet.GetLength()-1);
	return strRet;
}

int CXml_Bll_PointVarInfo::PointVar_Add(TiXmlDocument* pDoc,TiXmlElement* pEle_Parent,CString strFreq)
{
	PointVarSet stuPtSet;
	stuPtSet.m_strLogicName="Freq";
	stuPtSet.m_strName="ÆµÂÊ";
	stuPtSet.m_strUnit="Hz";
	stuPtSet.m_intID=1;
	strFreq.Format("%d",(int)(atof(strFreq)*1000000));
	stuPtSet.m_strValue=strFreq;
	CXml_PointVarSet xml_ptVarSet(pEle_Parent);
	xml_ptVarSet.PointVar_Add(pDoc,stuPtSet);
	return 1;
}

int CXml_Bll_PointVarInfo::PointVar_Modify(TiXmlDocument* pDoc,TiXmlElement* pEle_Parent,CString strFreq)
{
	PointVarSet stuPtSet;
	strFreq.Format("%d",(int)(atof(strFreq)*1000000));
	stuPtSet.m_strValue=strFreq;
	CXml_PointVarSet xml_ptVarSet(pEle_Parent);
	xml_ptVarSet.PointVar_Modify(pDoc,stuPtSet);
	return 1;
}
