// Xml_Bll_FaultInfo.cpp: implementation of the CXml_Bll_FaultInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Bll_FaultInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_FaultInfo::CXml_Bll_FaultInfo()
{
	CFile_UUTInfo fUUTInfo;
	m_strStartPath=fUUTInfo.GetUUTStartPath();
}

CXml_Bll_FaultInfo::~CXml_Bll_FaultInfo()
{

}

int CXml_Bll_FaultInfo::GetFaultList(CString strKind,CString strModel,vector<stuFaultInfo>* vFaultList)
{
	CString strFilePath=m_strStartPath+strKind+"\\"+strModel+"\\Assistant\\"+strModel+".xml";
	if(GetFileAttributes(strFilePath)==-1)
		return 0;
	m_xmlOpe.LoadXmlFile(strFilePath);
	CXml_FaultInfo xml_Fault(m_xmlOpe.pRootEle);
	xml_Fault.GetFaultList(vFaultList);
	return 1;
}

TiXmlNode* CXml_Bll_FaultInfo::GetFaultNode(CString strKind, CString strModel, int intID)
{
	CString strFilePath=m_strStartPath+strKind+"\\"+strModel+"\\Assistant\\"+strModel+".xml";
	if(GetFileAttributes(strFilePath)==-1)
		return NULL;
	m_xmlOpe.LoadXmlFile(strFilePath);
	CXml_FaultInfo xml_Fault(m_xmlOpe.pRootEle);
	return xml_Fault.GetFaultNode(intID);
}

TiXmlNode* CXml_Bll_FaultInfo::GetFaultNode(CString strKind, CString strModel, CString strFaultName)
{
	CString strFilePath=m_strStartPath+strKind+"\\"+strModel+"\\Assistant\\"+strModel+".xml";
	if(GetFileAttributes(strFilePath)==-1)
		return NULL;
	m_xmlOpe.LoadXmlFile(strFilePath);
	CXml_FaultInfo xml_Fault(m_xmlOpe.pRootEle);
	return xml_Fault.GetFaultNode(strFaultName);
}
void CXml_Bll_FaultInfo::FaultInfoConvert(vector <TestItemState> vItemState,vector<FaultItemInfo>* vFaultItemInfo)
{
	//将测试结果列表 转换为故障信息列表
	CString strItem_Pre="";
	//CString strState_Temp;
	int intCount_Ft=0; //故障列表计数器
	FaultItemInfo stuFltItemInfo;
	//故障判断
	for(int i=0;i<vItemState.size();i++)
	{
		if(vItemState[i].m_strItemName!=strItem_Pre)
		{
			stuFltItemInfo.m_strItemName=vItemState[i].m_strItemName;
			stuFltItemInfo.m_strState=vItemState[i].m_strState;
		    stuFltItemInfo.m_strFault=vItemState[i].m_strFault;
			for(int j=0;j<vItemState.size();j++)
			{
				if(vItemState[j].m_strItemName==stuFltItemInfo.m_strItemName&&vItemState[j].m_strState=="Fail")
				{
					stuFltItemInfo.m_strState=vItemState[j].m_strState;
		        	stuFltItemInfo.m_strFault=vItemState[j].m_strFault;
				}
			}
			if(stuFltItemInfo.m_strState=="Fail")
		    	vFaultItemInfo->push_back(stuFltItemInfo);
		}
		strItem_Pre=stuFltItemInfo.m_strItemName;
	}
}
