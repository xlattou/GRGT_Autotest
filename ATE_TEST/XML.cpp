// XML.cpp: implementation of the CXML class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "XML.h"
#include "ReadXML.h"
#include "Xml_PointVarSet.h"
#include "Xml_TestPointSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXML::CXML()
{

}

CXML::~CXML()
{

}

void CXML::SetXMLname(CString fName)
{
	m_name= fName;
}

void CXML::SetXMLPth(CString pth)
{
	m_pth= pth;
}

void CXML::WriteXMLPoint(vector<VarItem> m_vArr,vector<TestPoint> m_pArr,int pnum,int nVar)
{
	TiXmlDocument* m_xmlDoc = new TiXmlDocument();
	TiXmlElement* tEle=new TiXmlElement("PointSet");
	
	for(int i=0;i<pnum;i++)
	{
		TiXmlElement* pEle=new TiXmlElement("Point");
		
		pEle->SetAttribute("ID",m_pArr[i].m_ID);
		tEle->LinkEndChild(pEle);
		
		//加入upper节点
		TiXmlElement tEle_Upper("Upper");
		tEle_Upper.SetAttribute("Value",m_pArr[i].m_Upper);
		pEle->InsertEndChild(tEle_Upper);
		
		//加入lower节点
		TiXmlElement tEle_Lower("Lower");
		tEle_Lower.SetAttribute("Value",m_pArr[i].m_Lower);
		pEle->InsertEndChild(tEle_Lower);
		
		//加入Result节点
		TiXmlElement tEle_Result("Result");
		tEle_Result.SetAttribute("Unit",m_pArr[i].m_Unit);
		tEle_Result.SetAttribute("ColNum",m_pArr[i].m_Col);
		tEle_Result.SetAttribute("LineNum",m_pArr[i].m_Line);
		pEle->InsertEndChild(tEle_Result);
		
		
		//此处用一个for循环，将VarSet的数组加进去
		TiXmlElement* tEle_VarSet = new TiXmlElement("VarSet");
		pEle->LinkEndChild(tEle_VarSet);
		for(int j=0;j<nVar;j++)
		{
			TiXmlElement tEle_Var = (m_vArr[i*nVar+j].logicName);
			tEle_Var.SetAttribute("Value",m_vArr[i*nVar+j].Value);
			tEle_Var.SetAttribute("Unit",m_vArr[i*nVar+j].Unit);
			tEle_Var.SetAttribute("Name",m_vArr[i*nVar+j].Name);
			tEle_Var.SetAttribute("ID",m_vArr[i*nVar+j].ID);
			tEle_VarSet->InsertEndChild(tEle_Var);
		}
	}
	
	m_xmlDoc->LinkEndChild(tEle);
	m_xmlDoc->SaveFile(m_pth);
}