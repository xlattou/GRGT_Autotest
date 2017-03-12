// ItemVarSelection.cpp: implementation of the CItemVarSelection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "ItemVarSelection.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemVarSelection::CItemVarSelection()
{
	m_pNode=NULL;
}
CItemVarSelection::~CItemVarSelection()
{
}
CItemVarSelection::CItemVarSelection(TiXmlNode* pNode_Parent)
{
	if(pNode_Parent!=NULL)
	{
		m_pNode=pNode_Parent->FirstChild("Selection");
	}
	else
	{
		m_pNode=NULL;
	}
}	
//���ӱ���ѡ��
int CItemVarSelection::SelAdd(ItemVarSel stcItemSel)
{		
	if(m_pNode==NULL)
	{
	    ThrowErr(�Ҳ�����Ŀ�����ڵ�);
		return 0;
	}
	TiXmlElement pEle(stcItemSel.m_strLogicName);
	pEle.SetAttribute("Value",stcItemSel.m_intVarValue);
	pEle.SetAttribute("Name",stcItemSel.m_strDescription);
	m_pNode->InsertEndChild(pEle);
	return 1;
}

//�޸�ĳһ�߼���������Ӧ����Ϣ
int CItemVarSelection::SelModify(ItemVarSel stcItemSel)
{
	if(m_pNode==NULL)
	{
		ThrowErr(�Ҳ�����Ŀ�����ڵ�);
		return 0;
	}
	TiXmlElement* pEle_Child=NULL;
	pEle_Child=m_pNode->FirstChildElement(stcItemSel.m_strLogicName);
	if(pEle_Child==NULL)
	{
		ThrowErr(�Ҳ���������);
		return 0;
	}
	pEle_Child->SetAttribute("Value",stcItemSel.m_intVarValue);
	pEle_Child->SetAttribute("Name",stcItemSel.m_strDescription);
	return 1;
}

//��ȡĳһ�߼���������Ӧ����Ϣ
int CItemVarSelection::SelRead(ItemVarSel* pstcItemSel)
{
	if(m_pNode==NULL)
	{
		ThrowErr(�Ҳ�����Ŀ�����ڵ�);
		return 0;
	}
	TiXmlElement* pEle_Child=NULL;
	pEle_Child=m_pNode->FirstChildElement(pstcItemSel->m_strLogicName);
	if(pEle_Child==NULL)
	{
		ThrowErr(�Ҳ���������);
		return 0;
	}
	pstcItemSel->m_intVarValue=atoi(pEle_Child->Attribute("Value"));
	pstcItemSel->m_strDescription=pEle_Child->Attribute("Name");
	return 1;
}


//ɾ��ĳһ�߼���������Ӧ����Ϣ
int CItemVarSelection::SelDelete(CString strLogicName)
{
	
	if(m_pNode==NULL)
	{
		ThrowErr(�Ҳ�����Ŀ�����ڵ�);
		return 0;
	}
	TiXmlNode* pNode_Child=NULL;
	pNode_Child=m_pNode->FirstChild(strLogicName);
	if(pNode_Child==NULL)
	{
		ThrowErr(�Ҳ���������);
		return 0;
	}
	m_pNode->RemoveChild(pNode_Child);
//	m_pDoc->SaveFile();
	return 1;
}
//��ȡ�б�
int CItemVarSelection::SelReadList(vector <ItemVarSel>* v1)
{
	TiXmlNode* pNode_temp=NULL;
	TiXmlElement* pEle_temp=NULL;
	ItemVarSel varSel_Temp;
	for(pNode_temp=m_pNode->FirstChild();pNode_temp;pNode_temp=pNode_temp->NextSibling())
	{
	    pEle_temp=pNode_temp->ToElement();
		if(pEle_temp!=NULL)
		{
	    	varSel_Temp.m_strLogicName=pEle_temp->Value();
	    	varSel_Temp.m_intVarValue=atoi(pEle_temp->Attribute("Value"));
    		varSel_Temp.m_strDescription=pEle_temp->Attribute("Name");
	    	v1->push_back(varSel_Temp);
		}
	}

	return 1;
}
///////////////////////////////���Դ���///////////////////////////////////////////

/*
CItemVarSelection::CItemVarSelection(CString itemKind,CString itemName)
{
	
	CPathOperate fpath_Ope;
	CString strFilePath=fpath_Ope.GetStartPath();
	strFilePath+="DataInfo\\���Բ�����\\"+itemKind+"\\"+itemName+"\\TestInfo\\"
		+itemName+".dll";
	m_XmlOpe.LoadXmlFile(strFilePath);
	m_pDoc=m_XmlOpe.pDoc;
	m_pRootEle=m_XmlOpe.pRootEle;
	m_pNode=m_pRootEle->FirstChild("ItemVar");
}
*/
/*
//����Xml�ļ�
int CItemVarSelection::LoadXmlFile()
{
	m_XmlOpe.LoadXmlFile(m_strFilePath);
	m_pDoc=m_XmlOpe.pDoc;
	m_pRootEle=m_XmlOpe.pRootEle;
	m_pNode=m_pRootEle->FirstChild("ItemVar");
	m_pNode_Parent=m_pNode->FirstChild("WorkMode");

	if(m_pNode_Parent!=NULL)
	{
		m_pNode=m_pNode_Parent->FirstChild("Selection");
	}
	return 1;
}
*/
