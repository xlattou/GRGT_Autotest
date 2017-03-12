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
{//项目变量选项设置
	int m_intVarValue;  //设置数值
	CString m_strDescription; //设置说明
	CString m_strLogicName; //设置名称
};

//功能
class CItemVarSelection  
{
public:
	int SelDelete(CString strLogicName);
	int SelRead(ItemVarSel* stcItemSel);
	int SelModify(ItemVarSel stcItemSel);
	int SelAdd(ItemVarSel); //增加设置选项
	int SelReadList(vector<ItemVarSel> *v1);
	TiXmlNode* m_pNode;
	CItemVarSelection();
	CItemVarSelection(TiXmlNode* pNode_Parent);
	virtual ~CItemVarSelection();

	/*
	/////////////////////////临时功能和变量/////////////////////////////////////////////////
	TiXmlNode* m_pNode_Parent;
	int LoadXmlFile();
	CString m_strFilePath;
	TiXmlDocument* m_pDoc;
	CXmlFile_Ope m_XmlOpe;
	TiXmlElement* m_pRootEle;

	int m_intVarValue;  //设置数值
	CString m_strDescription; //设置说明
	CString m_strLogicName; //设置名称
	*/


};

#endif // !defined(AFX_ITEMVARSELECTION_H__9B72D48E_EA6A_487F_88A1_9323F504AA30__INCLUDED_)
