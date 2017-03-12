// ItemVarSelection.h: interface for the CItemVarSelection class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_ITEMVARSELECTION_H__9B72D48E_EA6A_487F_88A1_9323F504AA30__INCLUDED_)
#define AFX_ITEMVARSELECTION_H__9B72D48E_EA6A_487F_88A1_9323F504AA30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "XmlFile_Ope.h"
using namespace std;
//Model
struct ItemVarSel
{//��Ŀ����ѡ������
	int m_intVarValue;  //������ֵ
	CString m_strDescription; //����˵��
	CString m_strLogicName; //��������
};

//����
class CItemVarSelection  
{
public:
	int SelDelete(CString strLogicName);
	int SelRead(ItemVarSel* stcItemSel);
	int SelModify(ItemVarSel stcItemSel);
	int SelAdd(ItemVarSel); //��������ѡ��
	int SelReadList(vector<ItemVarSel> *v1);
	TiXmlNode* m_pNode;
	CItemVarSelection();
	CItemVarSelection(TiXmlNode* pNode_Parent);
	virtual ~CItemVarSelection();

	/*
	/////////////////////////��ʱ���ܺͱ���/////////////////////////////////////////////////
	TiXmlNode* m_pNode_Parent;
	int LoadXmlFile();
	CString m_strFilePath;
	TiXmlDocument* m_pDoc;
	CXmlFile_Ope m_XmlOpe;
	TiXmlElement* m_pRootEle;

	int m_intVarValue;  //������ֵ
	CString m_strDescription; //����˵��
	CString m_strLogicName; //��������
	*/


};

#endif // !defined(AFX_ITEMVARSELECTION_H__9B72D48E_EA6A_487F_88A1_9323F504AA30__INCLUDED_)
