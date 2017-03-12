// tb_TestResult.h: interface for the Ctb_TestResult class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TB_TESTRESULT_H__E7F31C0C_F9DF_4099_912A_6F1E75B164D2__INCLUDED_)
#define AFX_TB_TESTRESULT_H__E7F31C0C_F9DF_4099_912A_6F1E75B164D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ADO.h"

using namespace std;

struct stucTestResult
{
	int m_intID; //��ID
	int m_intTestInfoID; //������Ϣ���
	CString m_strItemName; //������Ŀ����
	CString m_strTestSet; //��������
	CString m_strUpper; //����ֵ
	CString m_strLower; //����ֵ 
	CString m_strResult; //���Խ��
	CString m_strUnit; //��λ
	CString m_strRow; //��
	CString m_strCol; //��
	CString m_strConclusion; //���Ե����
	CString m_strItemKey; //��Ŀ�ؼ���
};

class Ctb_TestResult  
{
public:
	int AddList(vector<stucTestResult> vTestResult,int intTestInfoID);
	int GenerateID();
	int ReadTestResult(stucTestResult *testResult,int intID);
	int ReadTestResultList(vector<stucTestResult> *vTestResult,int intTestInfoID);
	int Add(stucTestResult testResult);
	int DeleteResult(int intTestInfoID);//����IDɾ�������Ϣ
	CADODataSet m_DataSet;
	CString m_strTable;
	_ConnectionPtr m_pCon;
	Ctb_TestResult();
	virtual ~Ctb_TestResult();

};

#endif // !defined(AFX_TB_TESTRESULT_H__E7F31C0C_F9DF_4099_912A_6F1E75B164D2__INCLUDED_)
