// tb_TestResult.cpp: implementation of the Ctb_TestResult class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "tb_TestResult.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ctb_TestResult::Ctb_TestResult()
{
	m_strTable="tb_TestResult";
	m_pCon=GetConnection()->GetConnection();
}

Ctb_TestResult::~Ctb_TestResult()
{

}

int Ctb_TestResult::Add(stucTestResult testResult)
{
	CString strAdd;
	CString strTemp;
	strTemp.Format("%d,%d,'",testResult.m_intID,testResult.m_intTestInfoID);
	strAdd="insert into "+m_strTable+" values("+strTemp+testResult.m_strItemName+"','"+testResult.m_strTestSet+"','"
		+testResult.m_strUpper+"','"+testResult.m_strLower+"','"+testResult.m_strResult	+"','"+testResult.m_strUnit
		+"','"+testResult.m_strRow+"','"+testResult.m_strCol+"','"+testResult.m_strConclusion+"','"
		+testResult.m_strItemKey+"')";
	try
	{
		_bstr_t s=strAdd.AllocSysString();
		_variant_t recordAffected;
		m_pCon->Execute(s,&recordAffected,adCmdText);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	return 1;
}

int Ctb_TestResult::ReadTestResultList(vector<stucTestResult> *vTestResult,int intTestInfoID)
{
	stucTestResult testResult;
	vTestResult->clear();
	CString strInfoID_Temp;
	strInfoID_Temp.Format("%d",intTestInfoID);
	CString strRead="select * from "+m_strTable+" where TestInfoID="+strInfoID_Temp;
	try
	{
		m_DataSet.Open(strRead);
		int intCount=m_DataSet.GetRecordCount();
		for(int i=0;i<intCount;i++)
		{
			testResult.m_intID=m_DataSet.GetFields()->GetItem("ID")->GetValue().lVal;
			//ReadTestResult(&testResult,testResult.m_intID);

			testResult.m_intTestInfoID=intTestInfoID;
			testResult.m_strItemName=m_DataSet.GetFields()->GetItem("ItemName")->GetValue().bstrVal;
			testResult.m_strTestSet=m_DataSet.GetFields()->GetItem("testSet")->GetValue().bstrVal;
			testResult.m_strUpper=m_DataSet.GetFields()->GetItem("Upper")->GetValue().bstrVal;
			testResult.m_strLower=m_DataSet.GetFields()->GetItem("Lower")->GetValue().bstrVal;
			testResult.m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
			testResult.m_strUnit=m_DataSet.GetFields()->GetItem("Unit")->GetValue().bstrVal;
			testResult.m_strRow=m_DataSet.GetFields()->GetItem("Row")->GetValue().bstrVal;
        	testResult.m_strCol=m_DataSet.GetFields()->GetItem("Col")->GetValue().bstrVal;
        	testResult.m_strConclusion=m_DataSet.GetFields()->GetItem("Conclusion")->GetValue().bstrVal;
        	testResult.m_strItemKey=m_DataSet.GetFields()->GetItem("ItemKey")->GetValue().bstrVal;


			vTestResult->push_back(testResult);
			m_DataSet.Next();
		}	
	}
	catch (_com_error * e)
	{
		AfxMessageBox(e->ErrorMessage());
		
	}
	return 1;
}

int Ctb_TestResult::ReadTestResult(stucTestResult *testResult,int intID)
{
	CString strTemp;
	strTemp.Format("%d",intID);
	CString strRead="select * from "+m_strTable+" where ID="+strTemp;
	m_DataSet.Open(strRead);
	if(m_DataSet.GetRecordCount()==0)
		return 0;
	testResult->m_intTestInfoID=m_DataSet.GetFields()->GetItem("TestInfoID")->GetValue().lVal;
	testResult->m_strItemName=m_DataSet.GetFields()->GetItem("ItemName")->GetValue().bstrVal;
	testResult->m_strTestSet=m_DataSet.GetFields()->GetItem("testSet")->GetValue().bstrVal;
	testResult->m_strUpper=m_DataSet.GetFields()->GetItem("Upper")->GetValue().bstrVal;
	testResult->m_strLower=m_DataSet.GetFields()->GetItem("Lower")->GetValue().bstrVal;
	testResult->m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
	testResult->m_strUnit=m_DataSet.GetFields()->GetItem("Unit")->GetValue().bstrVal;
	testResult->m_strRow=m_DataSet.GetFields()->GetItem("Row")->GetValue().bstrVal;
	testResult->m_strCol=m_DataSet.GetFields()->GetItem("Col")->GetValue().bstrVal;
	testResult->m_strConclusion=m_DataSet.GetFields()->GetItem("Conclusion")->GetValue().bstrVal;
	testResult->m_strItemKey=m_DataSet.GetFields()->GetItem("ItemKey")->GetValue().bstrVal;
	return 1;
}

int Ctb_TestResult::GenerateID()
{
	CString strGetID="select ID from "+m_strTable;
	m_DataSet.Open(strGetID);
	return m_DataSet.GenerateID();
}

int Ctb_TestResult::AddList(vector<stucTestResult> vTestResult,int intTestInfoID)
{	
	for (int i=0;i<vTestResult.size();i++)
	{
		vTestResult[i].m_intTestInfoID=intTestInfoID;
		vTestResult[i].m_intID=GenerateID();
		Add(vTestResult[i]);
	}
	return 1;
}
int Ctb_TestResult::DeleteResult(int intTestInfoID) //根据ID删除结果信息
{
	CString strAdd;
	CString strTemp;
	strTemp.Format("%d",intTestInfoID);
	strAdd="DELETE FROM "+m_strTable+" WHERE [TestInfoID]="+strTemp;	
	
	try
	{
		_bstr_t s=strAdd.AllocSysString();
		_variant_t recordAffected;
		m_pCon->Execute(s,&recordAffected,adCmdText);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	return 1;
}
