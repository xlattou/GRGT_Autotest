// Xml_Bll_FaultReason.cpp: implementation of the CXml_Bll_FaultReason class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_Bll_FaultReason.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_Bll_FaultReason::CXml_Bll_FaultReason()
{
}

CXml_Bll_FaultReason::~CXml_Bll_FaultReason()
{

}

int CXml_Bll_FaultReason::GetModifyReasonList(TiXmlNode* pNode_Parent,vector<stuFaultReason>* vReasonList)
{
	CXml_FaultReason fltReason(pNode_Parent);
	return fltReason.GetReasonList(vReasonList);
}
void CXml_Bll_FaultReason::SortReasonList(vector<stuFaultReason> *vReasonList)
{
	vector<stuFaultReason> vSortList;
	int size=vReasonList->size();
	float fSumFact=0.00f;
	float fctor,fctor_Max;
	CString strFactor;
	int mark=0;
	vector<stuFaultReason>::iterator itr=vReasonList->begin();
	
	
	for(int i=0;i<vReasonList->size();i++)
	{
		fSumFact+=atof((*vReasonList)[i].m_strFactor);								
	}
	
	for(int i=0;i<size;i++)
	{
		fctor_Max=atof((*vReasonList)[0].m_strFactor)*100/fSumFact;
		for(int j=0;j<vReasonList->size();j++)
		{
			fctor=atof((*vReasonList)[j].m_strFactor)*100/fSumFact;
			if(fctor>fctor_Max)
			{
				fctor_Max=fctor;
				mark=j;
			}
		}	
		strFactor.Format("%.2f",fctor_Max);
		(*vReasonList)[mark].m_strFactor=strFactor;			
		vSortList.push_back((*vReasonList)[mark]);
		vReasonList->erase(itr+mark);
		mark=0;
	}
	for(int i=0;i<size;i++)
	{
		vReasonList->push_back(vSortList[i]);
	}	
}

void CXml_Bll_FaultReason::ModifyReasonAdd(vector<stuFaultReason>* vReasonListA_Result, vector<stuFaultReason>* vReasonListB)
{
	CString strFactor_Temp,strCardName_temp,strDescrip_Temp;
	stuFaultReason stuFltReason;
	//vector<stuFaultReason> vSortList;  //输出结果项
	vector<stuFaultReason>::iterator itr=vReasonListB->begin();

	for(int i=0;i<vReasonListA_Result->size();i++)
	{
		strCardName_temp=(*vReasonListA_Result)[i].m_strCardName;
		strFactor_Temp=(*vReasonListA_Result)[i].m_strFactor;
		strDescrip_Temp=(*vReasonListA_Result)[i].m_strDescription;
		for(int j=0;j<vReasonListB->size();j++)
		{	
			if((*vReasonListB)[j].m_strCardName==strCardName_temp)
			{
				//如果有相同板卡，进行合并，并删除B中的子项
				(*vReasonListA_Result)[i].m_strFactor.Format("%.2f",atof(strFactor_Temp)+atof((*vReasonListB)[j].m_strFactor));  //如果是相同板卡，对因子进行合并
				if(strDescrip_Temp.FindOneOf((*vReasonListB)[j].m_strDescription)==-1) //对故障描述进行合并
				{
					(*vReasonListA_Result)[i].m_strDescription+=(*vReasonListB)[j].m_strDescription;
				}	
				//删除B中同类的板卡
				vReasonListB->erase(itr+j);
			}
		}
	}
	for(int i=0;i<vReasonListB->size();i++)
	{
		vReasonListA_Result->push_back((*vReasonListB)[i]);
	}
}
