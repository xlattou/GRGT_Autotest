// Xml_UUTSet.h: interface for the CXml_UUTSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_UUTSET_H__9D34B9AE_1034_490A_AC1E_69E23F19C06D__INCLUDED_)
#define AFX_XML_UUTSET_H__9D34B9AE_1034_490A_AC1E_69E23F19C06D__INCLUDED_

#include "XmlFile_Ope.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "File_UUTInfo.h"
#include "XmlFile_Ope.h"
#include "Xml_UUTInfoSet.h"
using namespace std;

//uut.xml�л�����Ϣ������

class CXml_UUTInfo  
{
public:
	int GetInsList(CString strKind,CString strModel,vector<CString>* vInsList);
	CXmlFile_Ope m_xmlOpe;
	CString m_strStartPath;
	int ReadUUTBasicInfo(CString strKind,CString strModel,UUTInfoSet *stucUUTInfo);
	int WriteUUTBasicInfo(CString strKind,CString strModel, UUTInfoSet *stucUUTInfo);
	int CreatModelInfo(CString strKind, CString strFactory, CString strModelType);//�����豸�ͺ�
	int CreatTemplateInfo(CString strFilePath, CString strRoot);//����ģ��
	int	ReadUUTItemInfo(CString strKind, CString strModel, CArray<UUTItemInfo, UUTItemInfo> &rItemInfo, int &nUUTItemMax);//��ȡ���в�����Ŀ
	int	WriteUUTItemInfo(CString strKind, CString strModel, CArray<UUTItemInfo, UUTItemInfo> &rItemInfo, int nUUTItemMax);//�������в�����Ŀ
	
	
	CXml_UUTInfo();
	virtual ~CXml_UUTInfo();

};

#endif // !defined(AFX_XML_UUTSET_H__9D34B9AE_1034_490A_AC1E_69E23F19C06D__INCLUDED_)
