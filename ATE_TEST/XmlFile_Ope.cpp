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
	pDoc=new TiXmlDocument();  //分配内存空间
}
CXmlFile_Ope::CXmlFile_Ope(CString strXmlfPath)
{
	pDoc=new TiXmlDocument();  //分配内存空间
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
	if(pDoc->LoadFile(strXmlFilePath))//加载Xml文件
	{
		pRootEle=pDoc->RootElement();
		if(NULL==pRootEle)
		{
		    ThrowErr(调用XML文件根节点失败);
		}
	}
	else
	{
		pRootEle=NULL;
		ThrowErr(调用XML文件失败);
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
