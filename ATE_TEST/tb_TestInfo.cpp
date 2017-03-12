// tb_TestInfo.cpp: implementation of the Ctb_TestInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "tb_TestInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Ctb_TestInfo::Ctb_TestInfo()
{
	m_strTable="tb_TestInfo";
	m_pCon=GetConnection()->GetConnection();
}

Ctb_TestInfo::~Ctb_TestInfo()
{

}

int Ctb_TestInfo::Add(stucTestInfo TestInfo)
{
	CString strAdd;
	CString strTemp;
	strAdd="insert into "+m_strTable;
	/*	+"(";
	strAdd+="ID,Customer,Address,Model,Factory,SNumber,InsUse,Number_Mana,";
	strAdd+="CalDate,DuaCalDate,Result,Conclsion,CalStation,Temperature,Humidity,";
	strAdd+="Tester,TestTime,Templete)";
	*/
	strAdd+=" values (";
	strTemp.Format("%d",TestInfo.m_intID);
	strAdd+=strTemp+",'"+TestInfo.m_strCustomer+"','"+TestInfo.m_strAddress+"','"+TestInfo.m_strInsName+"','"
		+TestInfo.m_strModel+"','"+TestInfo.m_strFactory+"','"+TestInfo.m_strSNumber
		+"','"+TestInfo.m_strInsUse+"','"+TestInfo.m_strNumber_Mana+"','"
		+TestInfo.m_strCalDate+"','"+TestInfo.m_strDueCalDate+"','"+TestInfo.m_strResult
		+"','"+TestInfo.m_strConclusion+"','"+TestInfo.m_strCalStation+"','"
		+TestInfo.m_strTemperature+"','"+TestInfo.m_strHumidity+"','"+TestInfo.m_strTester
		+"','"+TestInfo.m_strTestTime+"','"+TestInfo.m_strTemplete+"')";
	_bstr_t s = strAdd.AllocSysString();
	_variant_t RecordsAffected; 
	try
	{
		m_pCon->Execute(s,&RecordsAffected,adCmdText);
	}
	catch (_com_error *e)
	{
	   AfxMessageBox(e->ErrorMessage());
	}
	return 1;
}
int Ctb_TestInfo::UpdateTestInfo(stucTestInfo TestInfo)//????
{
	CString strAdd;
	CString strTemp;
	strAdd="UPDATE "+m_strTable;
	/*	+"(";
	strAdd+="ID,Customer,Address,Model,Factory,SNumber,InsUse,Number_Mana,";
	strAdd+="CalDate,DueCalDate,Result,Conclsion,CalStation,Temperature,Humidity,";
	strAdd+="Tester,TestTime,Templete)";
	*/
	strAdd+=" SET ";
	strTemp.Format("%d",TestInfo.m_intID);
	strAdd+="[Customer]='"+TestInfo.m_strCustomer+"',[Address]='"+TestInfo.m_strAddress
		+"',[InsName]='"+TestInfo.m_strInsName
		+"',[Model]='"+TestInfo.m_strModel+"',[Factory]='"+TestInfo.m_strFactory
		+"',[SNumber]='"+TestInfo.m_strSNumber+"',[InsUse]='"+TestInfo.m_strInsUse
		+"',[Number_Mana]='"+TestInfo.m_strNumber_Mana+"',[CalDate]='"+TestInfo.m_strCalDate
		+"',[DueCalDate]='"+TestInfo.m_strDueCalDate+"',[Result]='"+TestInfo.m_strResult
		+"',[Conclsion]='"+TestInfo.m_strConclusion+"',[CalStation]='"+TestInfo.m_strCalStation
		+"',[Temperature]='"+TestInfo.m_strTemperature+"',[Humidity]='"+TestInfo.m_strHumidity
		+"',[Tester]='"+TestInfo.m_strTester+"',[TestTime]='"+TestInfo.m_strTestTime
        +"',[Templete]='"+TestInfo.m_strTemplete+"'";

	strAdd+="  WHERE [ID]="+strTemp;
	_bstr_t s = strAdd.AllocSysString();
	_variant_t RecordsAffected; 
	try
	{
		m_pCon->Execute(s,&RecordsAffected,adCmdText);
	}
	catch (_com_error *e)
	{
	   AfxMessageBox(e->ErrorMessage());
	}
	return 1;
}
int Ctb_TestInfo::GenerateID()
{
	CString strGetMax;
	strGetMax="select ID from "+m_strTable;
	m_DataSet.Open(strGetMax);
    return m_DataSet.GenerateID();
}

int Ctb_TestInfo::ReadTestInfo(stucTestInfo *TestInfo,int intID)
{
	CString strTemp;
	strTemp.Format("%d",intID);
	CString strRead="select * from "+m_strTable+" where ID="+strTemp;
	m_DataSet.Open(strRead);	//	"ID,Customer,Address,Model,Factory,SNumber,InsUse,Number_Mana,";
                            	//"CalDate,DueCalDate,Result,Conclsion,CalStation,Temperature,Humidity,";
                                 	//"Tester,TestTime,Templete)";
	if(m_DataSet.GetRecordCount()==0)
		return 0;
	TestInfo->m_strCustomer=m_DataSet.GetFields()->GetItem("Customer")->GetValue().bstrVal;
	
	TestInfo->m_strAddress=m_DataSet.GetFields()->GetItem("Address")->GetValue().bstrVal;

	TestInfo->m_strInsName=m_DataSet.GetFields()->GetItem("InsName")->GetValue().bstrVal;
	TestInfo->m_strModel=m_DataSet.GetFields()->GetItem("Model")->GetValue().bstrVal;
	TestInfo->m_strFactory=m_DataSet.GetFields()->GetItem("Factory")->GetValue().bstrVal;
	TestInfo->m_strSNumber=m_DataSet.GetFields()->GetItem("SNumber")->GetValue().bstrVal;
    TestInfo->m_strInsUse=m_DataSet.GetFields()->GetItem("InsUse")->GetValue().bstrVal;
	TestInfo->m_strNumber_Mana=m_DataSet.GetFields()->GetItem("Number_Mana")->GetValue().bstrVal;
    TestInfo->m_strCalDate=m_DataSet.GetFields()->GetItem("CalDate")->GetValue().bstrVal;
    TestInfo->m_strDueCalDate=m_DataSet.GetFields()->GetItem("DueCalDate")->GetValue().bstrVal;
    TestInfo->m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
    TestInfo->m_strConclusion=m_DataSet.GetFields()->GetItem("Conclsion")->GetValue().bstrVal;
	TestInfo->m_strCalStation=m_DataSet.GetFields()->GetItem("CalStation")->GetValue().bstrVal;
	TestInfo->m_strTemperature=m_DataSet.GetFields()->GetItem("Temperature")->GetValue().bstrVal;
	TestInfo->m_strHumidity=m_DataSet.GetFields()->GetItem("Humidity")->GetValue().bstrVal;
    TestInfo->m_strTester=m_DataSet.GetFields()->GetItem("Tester")->GetValue().bstrVal;
    TestInfo->m_strTestTime=m_DataSet.GetFields()->GetItem("TestTime")->GetValue().bstrVal;
    TestInfo->m_strTemplete=m_DataSet.GetFields()->GetItem("Templete")->GetValue().bstrVal;
	return 1;
}

int Ctb_TestInfo::ReadTestInfoList(vector<stucTestInfo>* vTestInfo)
{
	stucTestInfo testInfo;
	vTestInfo->clear();
	CString strRead="select * from "+m_strTable+" order by ID Desc";
	try
	{
		m_DataSet.Open(strRead);
		int intCount=m_DataSet.GetRecordCount();
		for(int i=0;i<intCount;i++)
		{
			testInfo.m_intID=m_DataSet.GetFields()->GetItem("ID")->GetValue().lVal;


			testInfo.m_strCustomer=m_DataSet.GetFields()->GetItem("Customer")->GetValue().bstrVal;
			
			testInfo.m_strAddress=m_DataSet.GetFields()->GetItem("Address")->GetValue().bstrVal;
			
			testInfo.m_strInsName=m_DataSet.GetFields()->GetItem("InsName")->GetValue().bstrVal;
			testInfo.m_strModel=m_DataSet.GetFields()->GetItem("Model")->GetValue().bstrVal;
			testInfo.m_strFactory=m_DataSet.GetFields()->GetItem("Factory")->GetValue().bstrVal;
			testInfo.m_strSNumber=m_DataSet.GetFields()->GetItem("SNumber")->GetValue().bstrVal;
			testInfo.m_strInsUse=m_DataSet.GetFields()->GetItem("InsUse")->GetValue().bstrVal;
			testInfo.m_strNumber_Mana=m_DataSet.GetFields()->GetItem("Number_Mana")->GetValue().bstrVal;
			testInfo.m_strCalDate=m_DataSet.GetFields()->GetItem("CalDate")->GetValue().bstrVal;
			testInfo.m_strDueCalDate=m_DataSet.GetFields()->GetItem("DueCalDate")->GetValue().bstrVal;
			testInfo.m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
			testInfo.m_strConclusion=m_DataSet.GetFields()->GetItem("Conclsion")->GetValue().bstrVal;
			testInfo.m_strCalStation=m_DataSet.GetFields()->GetItem("CalStation")->GetValue().bstrVal;
			testInfo.m_strTemperature=m_DataSet.GetFields()->GetItem("Temperature")->GetValue().bstrVal;
			testInfo.m_strHumidity=m_DataSet.GetFields()->GetItem("Humidity")->GetValue().bstrVal;
			testInfo.m_strTester=m_DataSet.GetFields()->GetItem("Tester")->GetValue().bstrVal;
			testInfo.m_strTestTime=m_DataSet.GetFields()->GetItem("TestTime")->GetValue().bstrVal;
            testInfo.m_strTemplete=m_DataSet.GetFields()->GetItem("Templete")->GetValue().bstrVal;

			vTestInfo->push_back(testInfo);
			m_DataSet.Next();
			
		}
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());		
	}
	return 1;
}
///////////////////////////²éÑ¯×Ö·û´®///////////////////////////////////////////////
int Ctb_TestInfo::SearchTestInfoList(vector<stucTestInfo>* vTestInfo,CString strSearchContent,CString strKey)
{

	stucTestInfo testInfo;
	vTestInfo->clear();
	CString strRead("");
	if(strSearchContent.IsEmpty()||strKey.IsEmpty())
	{
		strRead="select * from "+m_strTable+" order by ID Desc";
	}
	else
	{
		strRead="select * from "+m_strTable+" where "+strSearchContent+" like '%"+strKey + "%' order by ID Desc";
	}
	try
	{
		m_DataSet.Open(strRead);
		int intCount=m_DataSet.GetRecordCount();
		for(int i=0;i<intCount;i++)
		{
			testInfo.m_intID=m_DataSet.GetFields()->GetItem("ID")->GetValue().lVal;
			
			
			testInfo.m_strCustomer=m_DataSet.GetFields()->GetItem("Customer")->GetValue().bstrVal;
			
			testInfo.m_strAddress=m_DataSet.GetFields()->GetItem("Address")->GetValue().bstrVal;
			
			testInfo.m_strInsName=m_DataSet.GetFields()->GetItem("InsName")->GetValue().bstrVal;
			testInfo.m_strModel=m_DataSet.GetFields()->GetItem("Model")->GetValue().bstrVal;
			testInfo.m_strFactory=m_DataSet.GetFields()->GetItem("Factory")->GetValue().bstrVal;
			testInfo.m_strSNumber=m_DataSet.GetFields()->GetItem("SNumber")->GetValue().bstrVal;
			testInfo.m_strInsUse=m_DataSet.GetFields()->GetItem("InsUse")->GetValue().bstrVal;
			testInfo.m_strNumber_Mana=m_DataSet.GetFields()->GetItem("Number_Mana")->GetValue().bstrVal;
			testInfo.m_strCalDate=m_DataSet.GetFields()->GetItem("CalDate")->GetValue().bstrVal;
			testInfo.m_strDueCalDate=m_DataSet.GetFields()->GetItem("DueCalDate")->GetValue().bstrVal;
			testInfo.m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
			testInfo.m_strConclusion=m_DataSet.GetFields()->GetItem("Conclsion")->GetValue().bstrVal;
			testInfo.m_strCalStation=m_DataSet.GetFields()->GetItem("CalStation")->GetValue().bstrVal;
			testInfo.m_strTemperature=m_DataSet.GetFields()->GetItem("Temperature")->GetValue().bstrVal;
			testInfo.m_strHumidity=m_DataSet.GetFields()->GetItem("Humidity")->GetValue().bstrVal;
			testInfo.m_strTester=m_DataSet.GetFields()->GetItem("Tester")->GetValue().bstrVal;
			testInfo.m_strTestTime=m_DataSet.GetFields()->GetItem("TestTime")->GetValue().bstrVal;
            testInfo.m_strTemplete=m_DataSet.GetFields()->GetItem("Templete")->GetValue().bstrVal;
			
			vTestInfo->push_back(testInfo);
			m_DataSet.Next();
			
		}
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());		
	}
	return 1;

}
///////////////////////////Á½¸ö¹Ø¼ü×Ö²éÑ¯×Ö·û´®///////////////////////////////////////////////
int Ctb_TestInfo::SearchTestInfoList(vector<stucTestInfo>* vTestInfo,CString strSearchContent1,
									 CString strKey1,CString strSearchContent2,CString strKey2)
{
	stucTestInfo testInfo;
	vTestInfo->clear();
	CString strRead("");
	if(strSearchContent1.IsEmpty()||strKey1.IsEmpty()||strSearchContent2.IsEmpty()||strKey2.IsEmpty())
	{
		strRead="select * from "+m_strTable+" order by ID Desc";
	}
	else
	{
		strRead="select * from "+m_strTable+" where "+strSearchContent1+" like '%"+strKey1
		    	+"%' AND "+strSearchContent2+" like '%"+strKey2
		    	+"%' order by ID Desc";
	}
	try
	{
		m_DataSet.Open(strRead);
		int intCount=m_DataSet.GetRecordCount();
		for(int i=0;i<intCount;i++)
		{
			testInfo.m_intID=m_DataSet.GetFields()->GetItem("ID")->GetValue().lVal;
			
			
			testInfo.m_strCustomer=m_DataSet.GetFields()->GetItem("Customer")->GetValue().bstrVal;
			
			testInfo.m_strAddress=m_DataSet.GetFields()->GetItem("Address")->GetValue().bstrVal;
			
			testInfo.m_strInsName=m_DataSet.GetFields()->GetItem("InsName")->GetValue().bstrVal;
			testInfo.m_strModel=m_DataSet.GetFields()->GetItem("Model")->GetValue().bstrVal;
			testInfo.m_strFactory=m_DataSet.GetFields()->GetItem("Factory")->GetValue().bstrVal;
			testInfo.m_strSNumber=m_DataSet.GetFields()->GetItem("SNumber")->GetValue().bstrVal;
			testInfo.m_strInsUse=m_DataSet.GetFields()->GetItem("InsUse")->GetValue().bstrVal;
			testInfo.m_strNumber_Mana=m_DataSet.GetFields()->GetItem("Number_Mana")->GetValue().bstrVal;
			testInfo.m_strCalDate=m_DataSet.GetFields()->GetItem("CalDate")->GetValue().bstrVal;
			testInfo.m_strDueCalDate=m_DataSet.GetFields()->GetItem("DueCalDate")->GetValue().bstrVal;
			testInfo.m_strResult=m_DataSet.GetFields()->GetItem("Result")->GetValue().bstrVal;
			testInfo.m_strConclusion=m_DataSet.GetFields()->GetItem("Conclsion")->GetValue().bstrVal;
			testInfo.m_strCalStation=m_DataSet.GetFields()->GetItem("CalStation")->GetValue().bstrVal;
			testInfo.m_strTemperature=m_DataSet.GetFields()->GetItem("Temperature")->GetValue().bstrVal;
			testInfo.m_strHumidity=m_DataSet.GetFields()->GetItem("Humidity")->GetValue().bstrVal;
			testInfo.m_strTester=m_DataSet.GetFields()->GetItem("Tester")->GetValue().bstrVal;
			testInfo.m_strTestTime=m_DataSet.GetFields()->GetItem("TestTime")->GetValue().bstrVal;
            testInfo.m_strTemplete=m_DataSet.GetFields()->GetItem("Templete")->GetValue().bstrVal;
			
			vTestInfo->push_back(testInfo);
			m_DataSet.Next();
			
		}
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());		
	}
	return 1;
}
