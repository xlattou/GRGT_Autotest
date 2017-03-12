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
	int m_intID; //表ID
	int m_intTestInfoID; //测试信息编号
	CString m_strItemName; //测试项目名称
	CString m_strTestSet; //测试设置
	CString m_strUpper; //上限值
	CString m_strLower; //下限值 
	CString m_strResult; //测试结果
	CString m_strUnit; //单位
	CString m_strRow; //行
	CString m_strCol; //列
	CString m_strConclusion; //测试点结论
	CString m_strItemKey; //项目关键字
};

class Ctb_TestResult  
{
public:
	int AddList(vector<stucTestResult> vTestResult,int intTestInfoID);
	int GenerateID();
	int ReadTestResult(stucTestResult *testResult,int intID);
	int ReadTestResultList(vector<stucTestResult> *vTestResult,int intTestInfoID);
	int Add(stucTestResult testResult);
	int DeleteResult(int intTestInfoID);//根据ID删除结果信息
	CADODataSet m_DataSet;
	CString m_strTable;
	_ConnectionPtr m_pCon;
	Ctb_TestResult();
	virtual ~Ctb_TestResult();

};

#endif // !defined(AFX_TB_TESTRESULT_H__E7F31C0C_F9DF_4099_912A_6F1E75B164D2__INCLUDED_)
