// XmlFile_Ope.cpp: implementation of the CXmlFile_Ope class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "XmlFile_Ope.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlFile_Ope::CXmlFile_Ope()
{
	pDoc=new TiXmlDocument();  //�����ڴ�ռ�
}
CXmlFile_Ope::CXmlFile_Ope(CString strXmlfPath)
{
	pDoc=new TiXmlDocument();  //�����ڴ�ռ�
	LoadXmlFile(strXmlfPath);
}


CXmlFile_Ope::~CXmlFile_Ope()
{
	delete pDoc;
	if(pRootEle)
		pRootEle=NULL;
}


int CXmlFile_Ope::LoadXmlFile(CString strXmlFilePath)
{
	if(pDoc->LoadFile(strXmlFilePath))//����Xml�ļ�
	{
		pRootEle=pDoc->RootElement();
		if(NULL==pRootEle)
		{
		    ThrowErr(����XML�ļ����ڵ�ʧ��);
		}
	}
	else
	{
		pRootEle=NULL;
		ThrowErr(����XML�ļ�ʧ��);
	}
	return 1;
}

int CXmlFile_Ope::SaveFile()
{
	if(!pDoc->SaveFile())
	{
		return 0;
	}
	return 1;
}
