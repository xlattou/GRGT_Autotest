// Xml_TestPointSet.cpp: implementation of the CXml_TestPointSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_TestPointSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_TestPointSet::CXml_TestPointSet()
{

}
CXml_TestPointSet::CXml_TestPointSet(TiXmlNode* pNode_Parent)
{
	m_pNode_Parent=pNode_Parent;
	if(pNode_Parent!=NULL)
	{
		m_pNode=pNode_Parent->FirstChild("PointSet");
		
	}
	else
	{
		m_pNode=NULL;
	}	
}

CXml_TestPointSet::~CXml_TestPointSet()
{

}

TiXmlElement* CXml_TestPointSet::ReadPointInfo(TestPointSet* stucTestPtSet,int intPointID)
{
	if(m_pNode==NULL)
		return NULL;
	TiXmlElement* pEle_Temp=NULL;
	TiXmlElement* pEle_Temp2=NULL;
	TiXmlElement* pEle_Temp3=NULL;
	BOOL ret=false;
	for(pEle_Temp=m_pNode->FirstChildElement();pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement())
	{
		if(atoi(pEle_Temp->Attribute("ID"))==intPointID)
		{
			ret=true; 
	    	stucTestPtSet->m_intID=atoi(pEle_Temp->Attribute("ID"));  //测试点ID
	    	pEle_Temp2=pEle_Temp->FirstChildElement("Upper");
	    	if(!pEle_Temp2)
			{
	    		ThrowErr(找不到测试点上限);
	    		return NULL;
			}
	    	stucTestPtSet->m_strUpper=pEle_Temp2->Attribute("Value");   //上限值
	    	pEle_Temp2=pEle_Temp->FirstChildElement("Lower");
	    	if(!pEle_Temp2)
			{
		    	ThrowErr(找不到测试点下限);
		    	return NULL;
			}
	    	stucTestPtSet->m_strLower=pEle_Temp2->Attribute("Value");//下限值

			/*
	    	pEle_Temp2=pEle_Temp->FirstChildElement("Result");
	    	if(!pEle_Temp2)
			{
		    	ThrowErr(找不到测试结果设置);
		    	return NULL;
			}
	    	stucTestPtSet->m_strResultUnit=pEle_Temp2->Attribute("Unit"); //结果单位
	    	stucTestPtSet->m_strCol=pEle_Temp2->Attribute("ColNum"); //结果列
	    	stucTestPtSet->m_strLine=pEle_Temp2->Attribute("LineNum"); //结果行
			*/

	    	pEle_Temp2=pEle_Temp->FirstChildElement("ResultList"); //测试结果列表
			stucTestPtSet->m_strResultMark="";
			stucTestPtSet->m_strResultUnit="";
			stucTestPtSet->m_strCol="";
			stucTestPtSet->m_strLine="";
			for(pEle_Temp3=pEle_Temp2->FirstChildElement("Result");pEle_Temp3;pEle_Temp3=pEle_Temp3->NextSiblingElement("Result"))
			{
				if(pEle_Temp3!=NULL)
				{
					stucTestPtSet->m_strResultMark+=pEle_Temp3->Attribute("Mark");
					stucTestPtSet->m_strResultMark+=",";
					
					stucTestPtSet->m_strResultUnit+=pEle_Temp3->Attribute("Unit");
					stucTestPtSet->m_strResultUnit+=",";
					
					stucTestPtSet->m_strCol+=pEle_Temp3->Attribute("ColNum");
					stucTestPtSet->m_strCol+=",";
					
					stucTestPtSet->m_strLine+=pEle_Temp3->Attribute("LineNum");
					stucTestPtSet->m_strLine+=",";				
				}
			}
	    	stucTestPtSet->m_strResultMark=stucTestPtSet->m_strResultMark.Left(stucTestPtSet->m_strResultMark.GetLength()-1);
			stucTestPtSet->m_strResultUnit=stucTestPtSet->m_strResultUnit.Left(stucTestPtSet->m_strResultUnit.GetLength()-1);
			stucTestPtSet->m_strCol=stucTestPtSet->m_strCol.Left(stucTestPtSet->m_strCol.GetLength()-1);
	    	stucTestPtSet->m_strLine=stucTestPtSet->m_strLine.Left(stucTestPtSet->m_strLine.GetLength()-1);
			break;
		}
	}
	if(!ret)
	{
		ThrowErr(找不到指定ID的测试点项);
		return NULL;
	}
	return pEle_Temp;

}

TiXmlNode* CXml_TestPointSet::GetPointNode(int intPointID)
{
	if(NULL==m_pNode)
		return NULL;
	TiXmlNode* pNode_temp;
	for(pNode_temp=m_pNode->FirstChild("Point");pNode_temp;pNode_temp=pNode_temp->NextSibling("Point"))
	{
		if(atoi(pNode_temp->ToElement()->Attribute("ID"))==intPointID)
		{
			break;
		}
	}
	return pNode_temp;
}

int CXml_TestPointSet::ReadPointList(vector <TestPointSet>* vPoint)
{
	if(NULL==m_pNode)
		return 0;
	TiXmlElement* pEle_Temp=NULL;
	TiXmlElement* pEle_Temp2=NULL;
	TiXmlElement* pEle_Temp3=NULL;
	TestPointSet stucTestPtSet;
	for(pEle_Temp=m_pNode->FirstChildElement("Point");pEle_Temp;pEle_Temp=pEle_Temp->NextSiblingElement("Point"))
	{
		stucTestPtSet.m_intID=atoi(pEle_Temp->Attribute("ID"));  //测试点ID
		pEle_Temp2=pEle_Temp->FirstChildElement("Upper");
		if(!pEle_Temp2)
		{
			ThrowErr(找不到测试点上限);
			return NULL;
		}
		stucTestPtSet.m_strUpper=pEle_Temp2->Attribute("Value");   //上限值
		pEle_Temp2=pEle_Temp->FirstChildElement("Lower");
		if(!pEle_Temp2)
		{
			ThrowErr(找不到测试点下限);
			return NULL;
		}
		stucTestPtSet.m_strLower=pEle_Temp2->Attribute("Value");//下限值

		pEle_Temp2=pEle_Temp->FirstChildElement("ResultList"); //测试结果列表
		if(!pEle_Temp2)
		{
			ThrowErr(找不到测试结果设置);
			return NULL;
		}
		stucTestPtSet.m_strResultMark="";
		stucTestPtSet.m_strResultUnit="";
		stucTestPtSet.m_strCol="";
		stucTestPtSet.m_strLine="";
		for(pEle_Temp3=pEle_Temp2->FirstChildElement("Result");pEle_Temp3;pEle_Temp3=pEle_Temp3->NextSiblingElement("Result"))
		{
			if(pEle_Temp3!=NULL)
			{
				stucTestPtSet.m_strResultMark+=pEle_Temp3->Attribute("Mark");
				stucTestPtSet.m_strResultMark+=",";

				stucTestPtSet.m_strResultUnit+=pEle_Temp3->Attribute("Unit");
				stucTestPtSet.m_strResultUnit+=",";

				stucTestPtSet.m_strCol+=pEle_Temp3->Attribute("ColNum");
				stucTestPtSet.m_strCol+=",";
				
				stucTestPtSet.m_strLine+=pEle_Temp3->Attribute("LineNum");
				stucTestPtSet.m_strLine+=",";				
			}
		}
		stucTestPtSet.m_strResultMark=stucTestPtSet.m_strResultMark.Left(stucTestPtSet.m_strResultMark.GetLength()-1);
		stucTestPtSet.m_strResultUnit=stucTestPtSet.m_strResultUnit.Left(stucTestPtSet.m_strResultUnit.GetLength()-1);
		stucTestPtSet.m_strCol=stucTestPtSet.m_strCol.Left(stucTestPtSet.m_strCol.GetLength()-1);
		stucTestPtSet.m_strLine=stucTestPtSet.m_strLine.Left(stucTestPtSet.m_strLine.GetLength()-1);


		vPoint->push_back(stucTestPtSet);
	}
	return 1;
}

TiXmlElement* CXml_TestPointSet::Point_Add(TiXmlDocument* pDoc,TestPointSet stuTestPt)
{
	if(NULL==m_pNode_Parent)
		return NULL;
	int intNewID=GenerateID();
	if(m_pNode==NULL)
	{
		TiXmlElement tEle("PointSet");
		m_pNode_Parent->InsertEndChild(tEle);
		m_pNode=m_pNode_Parent->FirstChild("PointSet");
	}
	TiXmlElement* pEle=new TiXmlElement("Point");
	//pNode->SetValue("Point");
	pEle->SetAttribute("ID",intNewID);
	TiXmlElement tEle_Upper("Upper");
	TiXmlText tTxt_Upper(stuTestPt.m_strUpper);
	tEle_Upper.InsertEndChild(tTxt_Upper);
	TiXmlElement tEle_Lower("Lower");
	TiXmlText tTxt_Lower(stuTestPt.m_strLower);
	tEle_Lower.InsertEndChild(tTxt_Lower);
	pEle->InsertEndChild(tEle_Upper);
	pEle->InsertEndChild(tEle_Lower);
	TiXmlElement tEle_Var("VarSet");
	pEle->InsertEndChild(tEle_Var);
	m_pNode->LinkEndChild(pEle);
	//m_pNode->InsertEndChild(*pEle);
	pDoc->SaveFile();
	return pEle;
}

int CXml_TestPointSet::GenerateID()
{
	if(m_pNode==NULL)
		return 0;
	int intID=0;
	int intID_temp;
	TiXmlElement* pEle_temp=NULL;
	for(pEle_temp=m_pNode->FirstChildElement("Point");pEle_temp;pEle_temp=pEle_temp->NextSiblingElement("Point"))
	{
		intID_temp=atoi(pEle_temp->Attribute("ID"));
		if(intID_temp>intID)
		{
			intID=intID_temp;
		}
	}
	return intID+1;
}

TiXmlNode* CXml_TestPointSet::Point_Modify(TiXmlDocument *pDoc,TestPointSet stuTestPt)
{
	if(m_pNode==NULL)
		return 0;
	TiXmlNode* pNode_Temp=NULL;
	TiXmlElement* pEle_Temp2=NULL;
	TiXmlElement* pEle_Temp3=NULL;
	bool isExist=FALSE;
	for(pNode_Temp=m_pNode->FirstChild("Point");pNode_Temp;pNode_Temp=pNode_Temp->NextSibling("Point"))
	{
		if(stuTestPt.m_intID==atoi(pNode_Temp->ToElement()->Attribute("ID")))
		{
			isExist=TRUE;
			break;
		}
	}
	if(!isExist)
	{
		ThrowErr(找不到要修改的测试点);
		return NULL;
	}
	pEle_Temp2=pNode_Temp->FirstChildElement("Upper");
	if(pEle_Temp2==NULL)
	{
		ThrowErr(找不到上限节点);
		return NULL;
	}
	TiXmlText* pTxt_Upper=pEle_Temp2->FirstChild()->ToText();
	pTxt_Upper->SetValue(stuTestPt.m_strUpper);
	pEle_Temp3=pNode_Temp->FirstChildElement("Lower");
	if(pEle_Temp2==NULL)
	{
		ThrowErr(找不到下限节点);
		return NULL;
	}
	TiXmlText* pTxt_Lower=pEle_Temp3->FirstChild()->ToText();
	pTxt_Lower->SetValue(stuTestPt.m_strLower);
	pDoc->SaveFile();
	return pNode_Temp;
}

int CXml_TestPointSet::Point_Delete(TiXmlDocument *pDoc,int intID)
{
	if(m_pNode==NULL)
		return 0;
	TiXmlNode* pNode_Temp=NULL;
	BOOL isExist=FALSE;
	for(pNode_Temp=m_pNode->FirstChild("Point");pNode_Temp;pNode_Temp=pNode_Temp->NextSibling("Point"))
	{
		if(intID==atoi(pNode_Temp->ToElement()->Attribute("ID")))
		{
			isExist=TRUE;
			break;
		}
	}
	if(!isExist)
	{
		ThrowErr(找不到要删除的测试点);
		return 0;
	}

	m_pNode->RemoveChild(pNode_Temp);	
	pDoc->SaveFile();
	return 1;
}
