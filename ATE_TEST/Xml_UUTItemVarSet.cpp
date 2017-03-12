// Xml_UUTItemVarSet.cpp: implementation of the CXml_UUTItemVarSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "Xml_UUTItemVarSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXml_UUTItemVarSet::CXml_UUTItemVarSet()
{
	m_pNode=NULL;

}

CXml_UUTItemVarSet::CXml_UUTItemVarSet(TiXmlElement* pRootEle)
{
	if(pRootEle!=NULL)
	{
		m_pNode=pRootEle->FirstChild("ItemSet");
	}
	else
	{
		m_pNode=NULL;
	}
}

CXml_UUTItemVarSet::~CXml_UUTItemVarSet()
{

}

CString CXml_UUTItemVarSet::GetProgName(CString strItemName)
{
	TiXmlNode* pNode_temp=NULL;
	TiXmlElement* pEle_temp=NULL;
	CString strItem_temp="";
	CString strProg_temp="";
    pNode_temp=m_pNode->FirstChild(strItemName);
	if(pNode_temp!=NULL)
	{
		pEle_temp=pNode_temp->FirstChildElement("ProgName");
		if(pEle_temp!=NULL)
		{
			strProg_temp=pEle_temp->GetText();
		}
		else
		{
			ThrowErr(找不到指定程序名节点);
		}
	}
	else
	{
		ThrowErr(找不到指定项目名节点);
	}
	return strProg_temp;
}

int CXml_UUTItemVarSet::ReadItemList(vector<UUTItemVarSet>* vItemList)
{
	TiXmlElement* pEle_temp=NULL;
	TiXmlElement* pEle_temp2=NULL;
	UUTItemVarSet stucItemSet;
	for(pEle_temp=m_pNode->FirstChildElement();pEle_temp;pEle_temp=pEle_temp->NextSiblingElement())
	{
		stucItemSet.m_strName=pEle_temp->Value();
		stucItemSet.m_intID=atoi(pEle_temp->Attribute("ID"));
		if(pEle_temp!=NULL)
		{
			pEle_temp2=pEle_temp->FirstChildElement("ProgName");
			if(pEle_temp2!=NULL)
			{
				stucItemSet.m_strProgName=pEle_temp2->GetText();
			}
			else
			{
				stucItemSet.m_strProgName="";
				ThrowErr(找不到指定程序名节点);
			}
		}
		vItemList->push_back(stucItemSet);
	}

	return 1;
}

int CXml_UUTItemVarSet::GetItemInfo(UUTItemVarSet* stucUUTItem,CString strItemName, bool bThrowErr)
{
	TiXmlNode* pNode_temp=NULL;
	TiXmlElement* pEle_temp=NULL;
    pNode_temp=m_pNode->FirstChild(strItemName);
	stucUUTItem->m_strName=strItemName;
	if(pNode_temp!=NULL)
	{
		pEle_temp=pNode_temp->FirstChildElement("ProgName");
		if(pEle_temp!=NULL)
		{
			stucUUTItem->m_strProgName=pEle_temp->GetText();
		}
		else
		{
			if(bThrowErr)
				ThrowErr(找不到指定程序名节点);
		}

		pEle_temp=pNode_temp->FirstChildElement("ConnectPic");
		if(pEle_temp!=NULL)
		{
			stucUUTItem->m_strConnectPic=pEle_temp->GetText();
		}
		else
		{
			if(bThrowErr)
				ThrowErr(找不到指定连接图节点);
		}
		pEle_temp=pNode_temp->FirstChildElement("Description");

		if(pEle_temp!=NULL)
		{
			stucUUTItem->m_strConnectDescription=pEle_temp->GetText();
		}
		else
		{
			if(bThrowErr)
				ThrowErr(找不到指定连接提示节点);
		}
	}
	else
	{
		if(bThrowErr)
			ThrowErr(找不到指定项目名节点);
	}
	return 1;

}

int CXml_UUTItemVarSet::GetItemInfoArray(CArray<UUTItemVarSet, UUTItemVarSet> &stucUUTItemVarSet)
{
	TiXmlElement* pEle_temp=NULL;
	TiXmlElement* pEle_temp1=NULL;
	UUTItemVarSet stucUUTItem;
	CString str1;
	for(pEle_temp=m_pNode->FirstChildElement(); pEle_temp != NULL; pEle_temp = pEle_temp->NextSiblingElement())
	{
		str1 = pEle_temp->Value();
		if(str1.GetLength() > 3 && str1.Left(3) == "Key")
		{
			stucUUTItem.m_strProgName = "";
			stucUUTItem.m_strConnectPic = "";
			stucUUTItem.m_strConnectDescription = "";
			stucUUTItem.m_intID = atoi(str1.Right(str1.GetLength() - 3));
			pEle_temp1=pEle_temp->FirstChildElement("ProgName");
			if(pEle_temp1!=NULL)
			{
				stucUUTItem.m_strProgName=pEle_temp1->GetText();
			}

			pEle_temp1=pEle_temp->FirstChildElement("ConnectPic");
			if(pEle_temp1!=NULL)
			{
				stucUUTItem.m_strConnectPic=pEle_temp1->GetText();
			}

			pEle_temp1=pEle_temp->FirstChildElement("Description");

			if(pEle_temp1!=NULL)
			{
				stucUUTItem.m_strConnectDescription=pEle_temp1->GetText();
			}
			stucUUTItemVarSet.Add(stucUUTItem);
		}
	}
	return 1;
}
int CXml_UUTItemVarSet::WriteItemInfoArray(CArray<UUTItemVarSet, UUTItemVarSet> &stucUUTItemVarSet)
{
	if(m_pNode != NULL)
		m_pEle = m_pNode->ToElement();
	else
		m_pEle = new TiXmlElement("ItemSet");
	TiXmlElement* pEle_temp=NULL;
	TiXmlElement* pEle_temp1=NULL;
	UUTItemVarSet stucUUTItem;
	CString str1;
	for(int i = 0; i < stucUUTItemVarSet.GetSize(); i++)
	{
		TiXmlElement* pEle_temp = NULL;
		TiXmlElement* pEle_tempProg = NULL;
		TiXmlElement* pEle_tempPic = NULL;
		TiXmlElement* pEle_tempDes = NULL;
		str1.Format("Key%d", stucUUTItemVarSet[i].m_intID);
		pEle_temp = m_pEle->FirstChildElement(str1);
		if(pEle_temp == NULL)
		{
			pEle_temp = new TiXmlElement(str1);
			m_pEle->LinkEndChild(pEle_temp);
		}
		str1.Format("%d", i + 1);
		pEle_temp->SetAttribute("ID", str1);

		pEle_tempProg = pEle_temp->FirstChildElement("ProgName");
		if(pEle_tempProg == NULL)
		{
			pEle_tempProg = new TiXmlElement("ProgName");
			pEle_temp->LinkEndChild(pEle_tempProg);
		}
		pEle_tempProg->Clear();
		TiXmlText *prog = new TiXmlText(stucUUTItemVarSet[i].m_strProgName);
		pEle_tempProg->LinkEndChild(prog);

		pEle_tempPic = pEle_temp->FirstChildElement("ConnectPic");
		if(pEle_tempPic == NULL)
		{
			pEle_tempPic = new TiXmlElement("ConnectPic");
			pEle_temp->LinkEndChild(pEle_tempPic);
		}
		pEle_tempPic->Clear();			
		TiXmlText *pic = new TiXmlText(stucUUTItemVarSet[i].m_strConnectPic);
		pEle_tempPic->LinkEndChild(pic);

		pEle_tempDes = pEle_temp->FirstChildElement("Description");
		if(pEle_tempDes == NULL)
		{
			pEle_tempDes = new TiXmlElement("Description");
			pEle_temp->LinkEndChild(pEle_tempDes);
		}
	}
	return 1;
}