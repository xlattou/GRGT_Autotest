// FileOpe_Excel.h: interface for the CFileOpe_Excel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_)
#define AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "excel.h"
#include "Xml_Bll_UUTItem_Tem.h"
using namespace MyExcel;
#define ThrowErr(err) throw TEXT(#err)
using namespace std;

//字符串测试信息结构
struct StringStruct
{
	CString m_strName; //测试结果
	CString m_strRow; //行
	CString m_strColumn; //列
	CString m_strConclusion; //结论
	CString m_strItemKey; //项目关键字
};
//整型测试信息结构
struct INTStruct
{
	int m_intSel; //测试选项
	CString m_strRow; //行
	CString m_strColumn; //列
};


//封面信息
struct FirstPaper
{
	StringStruct m_stucCustomer; //委托方
	StringStruct m_stucAddress_Customer; //委托方地址
	StringStruct m_stucInsName; //计量器具名称 
	StringStruct m_stucInsModel; //器具型号
	StringStruct m_stucFactory; //制造厂
	StringStruct m_stucSNumber; //器具编号
	INTStruct m_stucInsUse; //器具用途
	StringStruct m_stucNumber_Mana; //管理编号
	StringStruct m_stucCalDate; //校准日期
	StringStruct m_stucDueCalDate; //建议再校准日期
	StringStruct m_StandardName0;  //标准仪器名称
	StringStruct m_StandardNum0;  //标准仪器编号
	StringStruct m_StandardName1;  //标准仪器名称
	StringStruct m_StandardNum1;  //标准仪器编号
	StringStruct m_StandardName2;  //标准仪器名称
	StringStruct m_StandardNum2;  //标准仪器编号
	StringStruct m_StandardName3;  //标准仪器名称
	StringStruct m_StandardNum3;  //标准仪器编号
	StringStruct m_stucResult; //校准结论,中文说明
	INTStruct m_stucConclusion; //校准结论，是否合格 0=不合格 1=合格
	INTStruct m_stucCalStation; //校准地点 0=实验室 1=委托方现场 -1 = 自定义地址
	StringStruct m_stucTestAdrress;  //测试地点
	StringStruct m_stucTemperature; //温度
	StringStruct m_stucHumidity; //湿度
	StringStruct m_stucTester;  //校准人
	int m_intSheetNumber; //Excel中的写入页面
	vector<StringStruct> vstucResult; //测试结果列表
	CString m_strTemplete; //测试所用的xml证书模板路径
};



class CFileOpe_Excel  
{
public:
	int WriteResultToExcel(CString strTemFilePath,CString strSavefilePath,FirstPaper stucFirstPaper);
	int ReadExcel();
	void CreateExcel();
	CXml_Bll_UUTItem_Tem m_xml_tem;
	CFileOpe_Excel();
	virtual ~CFileOpe_Excel();

private:
	void StringToArray(CString strInput,CString key,vector<CString>* stringArray); //字符串分割
};

#endif // !defined(AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_)
