// Xml_UUTItemSet.cpp: implementation of the CXml_UUTItemSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_FrontPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_FrontPage::CXml_FrontPage(TiXmlElement* pRootEle)
{
	if(NULL!=pRootEle)
	{
		m_pNode=pRootEle->FirstChild("FirstPaper");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_FrontPage::CXml_FrontPage()
{
	m_pNode=NULL;
}

CXml_FrontPage::~CXml_FrontPage()
{

}

int CXml_FrontPage::ReadFrontPageList(CString &strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage)
{
	vFrontPage.RemoveAll();
	if(NULL==m_pNode)
		return 0;
	
	TiXmlElement* pEle_Temp=NULL;
	FrontPage frontPage1;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{		
		if((CString)pEle_Temp->Value()=="SheetNumber")
		{
			strSheetNumber=pEle_Temp->Attribute("Value"); //工作表序号
		}
		else
		{
			frontPage1.strName=pEle_Temp->Value();
			frontPage1.strRow=pEle_Temp->Attribute("Row"); //行
			frontPage1.strCol=pEle_Temp->Attribute("Col"); //列
			vFrontPage.Add(frontPage1);
		}
	}
	return 1;
}

int CXml_FrontPage::WriteFrontPageList(CString strSheetNumber, CArray<FrontPage, FrontPage> &vFrontPage)
{
	if(NULL==m_pNode)
		return 0;
	
	TiXmlElement* pEle_Temp=NULL;
	pEle_Temp = m_pNode->ToElement();
	pEle_Temp->Clear();
	FrontPage frontPage1;
	TiXmlElement* pEle1=new TiXmlElement("SheetNumber");
	pEle1->SetAttribute("Value", strSheetNumber); //工作表序号
	pEle_Temp->LinkEndChild(pEle1);

	for(int i = 0; i < vFrontPage.GetSize(); i++)
	{		
		TiXmlElement* pEle2=new TiXmlElement(vFrontPage[i].strName);
		pEle2->SetAttribute("Row", vFrontPage[i].strRow);
		pEle2->SetAttribute("Col", vFrontPage[i].strCol);
		pEle_Temp->LinkEndChild(pEle2);
	}
	return 1;
}