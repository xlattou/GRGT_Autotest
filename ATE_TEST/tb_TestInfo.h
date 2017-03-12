// tb_TestInfo.h: interface for the Ctb_TestInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_)
#define AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ADO.h"
using namespace std;

struct stucTestInfo 
{
	int m_intID; //测试信息ID
	CString m_strCustomer; //委托方
	CString m_strAddress; //委托方地址
	CString m_strInsName; //设备名称
	CString m_strModel; //设备型号
	CString m_strFactory; //制造厂
	CString m_strSNumber; //出厂编号
	CString m_strInsUse; //设备用途
	CString m_strNumber_Mana; //管理编号
	CString m_strCalDate; //校准日期
	CString m_strDueCalDate; //建议再校准日期
	CString m_strResult; //校准结论  中文说明 按校准结果使用/1级合格/ 2级合格
	CString m_strConclusion; //是否合格
	CString m_strCalStation;  //校准地点
	CString m_strTemperature; //温度
	CString m_strHumidity; //湿度
	CString m_strTester; //测试人员
	CString m_strTestTime; //测试时间
	CString m_strTemplete; //测试模板
};

class Ctb_TestInfo  
{
public:
	int SearchTestInfoList(vector<stucTestInfo>* vTestInfo //测试信息列表
		,CString strSearchContent //查询的字段
		,CString strKey //关键字
		);
	int SearchTestInfoList(vector<stucTestInfo>* vTestInfo //测试信息列表
		,CString strSearchContent1 //查询的字段1
		,CString strKey1 //关键字1
		,CString strSearchContent2 //查询的字段2
		,CString strKey2 //关键字2
		);
	int ReadTestInfoList(vector<stucTestInfo>* vTestInfo);
	int ReadTestInfo(stucTestInfo *TestInfo,int intID);
	int GenerateID();
	int Add(stucTestInfo TestInfo);
	int UpdateTestInfo(stucTestInfo TestInfo);//更新信息
	CADODataSet m_DataSet;
	CString m_strTable;
	_ConnectionPtr m_pCon;



	Ctb_TestInfo();
	virtual ~Ctb_TestInfo();

};

#endif // !defined(AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_)
