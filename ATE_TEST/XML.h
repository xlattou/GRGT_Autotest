// XML.h: interface for the CXML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_)
#define AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����vectorͷ�ļ�
#include <vector>
using namespace std;
#include "ReadXML.h"
#include "Xml_PointVarSet.h"
//#include "Xml_UUTItemSet.h"
#include "Xml_TestPointSet.h"

struct VarItem
{
	CString logicName;
	CString Value;
	CString Unit;
	CString Name;
	CString ID;
};

struct TestPoint
{
	CString m_ID; //���Ե���
	CString m_Upper; //���Ե�����
	CString m_Lower; //���Ե�����
	CString m_Unit; //���Խ����λ
	CString m_Col;   //�����
	CString m_Line;  //�����
};



class CXML  
{
public:
	CXML();
	virtual ~CXML();
	void SetXMLname(CString);
	void SetXMLPth(CString);
	void WriteXMLPoint(vector<VarItem>,vector<TestPoint>,int,int);

private:
	CString m_name;
	CString m_pth;
};

#endif // !defined(AFX_XML_H__CC57574A_86B5_4F28_A234_710A1D2AA67D__INCLUDED_)
