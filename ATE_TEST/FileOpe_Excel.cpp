// FileOpe_Excel.cpp: implementation of the CFileOpe_Excel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "FileOpe_Excel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOpe_Excel::CFileOpe_Excel()
{

}

CFileOpe_Excel::~CFileOpe_Excel()
{

}

void CFileOpe_Excel::CreateExcel()
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	MyExcel::Font font;
	Range cols;
	COleVariant covOpetional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	if(!app.CreateDispatch("Excel.Application"))
	{
		ThrowErr(无法创建Excel应用);
		return;
	}
	books=app.GetWorkbooks();
	book=books.Add(covOpetional);
	sheets=book.GetSheets();
	sheet=sheets.GetItem(COleVariant((short)1));
	range=sheet.GetRange(COleVariant("A1"),COleVariant("A1"));
	range.SetValue2(COleVariant("HELLO EXCEL!"));
	font=range.GetFont();
	font.SetBold(COleVariant((short)TRUE));
	range=sheet.GetRange(COleVariant("B2"),COleVariant("B3"));
	range.SetFormula(COleVariant("=RAND()*10000"));
	range.SetNumberFormat(COleVariant("$0.00"));
	cols=range.GetEntireColumn();
	cols.AutoFit();
	app.SetVisible(TRUE);
	app.SetUserControl(TRUE);
	//range.SetValue2(COleVariant("BB"));

	book.SaveAs(COleVariant("D:\\a.xls"),covOpetional,covOpetional,covOpetional,covOpetional,
		covOpetional,0,covOpetional,covOpetional,covOpetional,covOpetional,covOpetional);
	//app.Quit();

}

int CFileOpe_Excel::ReadExcel()
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	LPDISPATCH lpDisp;//接口指针
	Range range;
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	if(!app.CreateDispatch("Excel.Application"))
	{
		ThrowErr(无法创建Excel应用);
		return 0;
	}
	books=app.GetWorkbooks();
	lpDisp=books.Open("D:\\34401k.xls",covOptional,covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional);
	book.AttachDispatch(lpDisp);
	sheets=book.GetSheets();
	sheet=sheets.GetItem(COleVariant((short)4));
	range=sheet.GetRange(COleVariant("G21"),COleVariant("G21"));
//	range.SetStyle(COleVariant(short(VT_)));
	//range.SetValue(COleVariant(short(VT_BOOL)),COleVariant((short)TRUE));
//	range.SetValue2(COleVariant((short)TRUE));
	//range.GetValue(covOptional);
//	range.GetStyle();
    //sheet.get
	//sheet.get
	//CheckBoxes checks=sheet.GetSmartTags();
	//CheckBox check=((CheckBoxes)sheet.GetListObjects())[1];

//	Shapes checks=sheet.GetShapes();
//	int n= checks.GetCount();
//	checks.Item(COleVariant());
//	CheckBox check=checks.Item(COleVariant((CString)("CheckBox")));
	//CheckBox check=checks.GetRange(COleVariant((long)1));
//	BOOL isEnable= check.GetEnabled();
	//CheckBox check=checks.getra
	//CheckBox check=checks.Item(COleVariant((short)2));
	//check.GetText();


//	CheckBox check=checks.Item(COleVariant((short)0));
//	BOOL ischeck=(BOOL)check.GetValue().boolVal;


	//Shapes myshapes=sheet.GetShapes();
	//sheet.GetCells()



//	check.SetValue(COleVariant((short)1));
	


//	checks[1].SetValue(COleVariant((short)1));

    range.SetValue2(COleVariant("TRUE"));
	


	/*
	COleVariant rValue;
	rValue=COleVariant(range.GetValue2());
	rValue.ChangeType(VT_BSTR);
	//BOOL status=(BOOL)rValue.boolVal;
	MessageBox(0,CString(rValue.bstrVal),"",0);
*/

	
	book.SetSaved(TRUE);
	//app.Quit();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.Close(covOptional,covOptional,vtMissing);
	books.Close();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();

	return 1;

}

int CFileOpe_Excel::WriteResultToExcel(CString strTemFilePath,CString strSavefilePath,FirstPaper stucFirstPaper)
{
	//////////////////////初始化首页行列信息////////////////////////////////////////////////////
    //内容页号
	if(stucFirstPaper.m_intSheetNumber < 0)
		stucFirstPaper.m_intSheetNumber=4;
	//委托方名称
	if(stucFirstPaper.m_stucCustomer.m_strColumn=="" || stucFirstPaper.m_stucCustomer.m_strRow=="")
	{
		stucFirstPaper.m_stucCustomer.m_strColumn="G";
		stucFirstPaper.m_stucCustomer.m_strRow="13";
	}
	//委托方地址
	if(stucFirstPaper.m_stucAddress_Customer.m_strColumn=="" || stucFirstPaper.m_stucAddress_Customer.m_strRow=="")
	{
		stucFirstPaper.m_stucAddress_Customer.m_strColumn="G";
		stucFirstPaper.m_stucAddress_Customer.m_strRow="14";
	}
	//设备名称
	if(stucFirstPaper.m_stucInsName.m_strColumn=="" || stucFirstPaper.m_stucInsName.m_strRow=="")
	{
		stucFirstPaper.m_stucInsName.m_strColumn="G";
		stucFirstPaper.m_stucInsName.m_strRow="15";
	}
	//设备型号
	if(stucFirstPaper.m_stucInsModel.m_strColumn=="" || stucFirstPaper.m_stucInsModel.m_strRow=="")
	{
		stucFirstPaper.m_stucInsModel.m_strColumn="G";
		stucFirstPaper.m_stucInsModel.m_strRow="17";
	}
	//制造厂
	if(stucFirstPaper.m_stucFactory.m_strColumn=="" || stucFirstPaper.m_stucFactory.m_strRow=="")
	{
		stucFirstPaper.m_stucFactory.m_strColumn="G";
		stucFirstPaper.m_stucFactory.m_strRow="18";
	}
	//出厂编号
	if(stucFirstPaper.m_stucSNumber.m_strColumn=="" || stucFirstPaper.m_stucSNumber.m_strRow=="")
	{
		stucFirstPaper.m_stucSNumber.m_strColumn="G";
		stucFirstPaper.m_stucSNumber.m_strRow="19";
	}
    //设备用途
	if(stucFirstPaper.m_stucInsUse.m_strColumn=="" || stucFirstPaper.m_stucInsUse.m_strRow=="")
	{
		stucFirstPaper.m_stucInsUse.m_strColumn="G";
		stucFirstPaper.m_stucInsUse.m_strRow="12";
	}
	//管理编号
	if(stucFirstPaper.m_stucNumber_Mana.m_strColumn=="" || stucFirstPaper.m_stucNumber_Mana.m_strRow=="")
	{
		stucFirstPaper.m_stucNumber_Mana.m_strColumn="X";
		stucFirstPaper.m_stucNumber_Mana.m_strRow="19";
	}
	//校准日期
	if(stucFirstPaper.m_stucCalDate.m_strColumn=="" || stucFirstPaper.m_stucCalDate.m_strRow=="")
	{
		stucFirstPaper.m_stucCalDate.m_strColumn="X";
		stucFirstPaper.m_stucCalDate.m_strRow="17";
	}
	//建议校准周期
	if(stucFirstPaper.m_stucDueCalDate.m_strColumn=="" || stucFirstPaper.m_stucDueCalDate.m_strRow=="")
	{
		stucFirstPaper.m_stucDueCalDate.m_strColumn="X";
		stucFirstPaper.m_stucDueCalDate.m_strRow="18";
	}
	//校准仪器名称
	if(stucFirstPaper.m_StandardName0.m_strColumn=="" || stucFirstPaper.m_StandardName0.m_strRow=="")
	{
		stucFirstPaper.m_StandardName0.m_strColumn="A";
		stucFirstPaper.m_StandardName0.m_strRow="24";
	}
	//校准仪器编号
	if(stucFirstPaper.m_StandardNum0.m_strColumn=="" || stucFirstPaper.m_StandardNum0.m_strRow=="")
	{
		stucFirstPaper.m_StandardNum0.m_strColumn="H";
		stucFirstPaper.m_StandardNum0.m_strRow="24";
	}

	//校准仪器名称
	if(stucFirstPaper.m_StandardName1.m_strColumn=="" || stucFirstPaper.m_StandardName1.m_strRow=="")
	{
		stucFirstPaper.m_StandardName1.m_strColumn="A";
		stucFirstPaper.m_StandardName1.m_strRow="25";
	}
	//校准仪器编号
	if(stucFirstPaper.m_StandardNum1.m_strColumn=="" || stucFirstPaper.m_StandardNum1.m_strRow=="")
	{
		stucFirstPaper.m_StandardNum1.m_strColumn="H";
		stucFirstPaper.m_StandardNum1.m_strRow="25";
	}

	//校准仪器名称
	if(stucFirstPaper.m_StandardName2.m_strColumn=="" || stucFirstPaper.m_StandardName2.m_strRow=="")
	{
		stucFirstPaper.m_StandardName2.m_strColumn="A";
		stucFirstPaper.m_StandardName2.m_strRow="26";
	}
	//校准仪器编号
	if(stucFirstPaper.m_StandardNum2.m_strColumn=="" || stucFirstPaper.m_StandardNum2.m_strRow=="")
	{
		stucFirstPaper.m_StandardNum2.m_strColumn="H";
		stucFirstPaper.m_StandardNum2.m_strRow="26";
	}


	//校准仪器名称
	if(stucFirstPaper.m_StandardName3.m_strColumn=="" || stucFirstPaper.m_StandardName3.m_strRow=="")
	{
		stucFirstPaper.m_StandardName3.m_strColumn="A";
		stucFirstPaper.m_StandardName3.m_strRow="27";
	}
	//校准仪器编号
	if(stucFirstPaper.m_StandardNum3.m_strColumn=="" || stucFirstPaper.m_StandardNum3.m_strRow=="")
	{
		stucFirstPaper.m_StandardNum3.m_strColumn="H";
		stucFirstPaper.m_StandardNum3.m_strRow="27";
	}
	//校准结论,中文说明
	if(stucFirstPaper.m_stucResult.m_strColumn=="" || stucFirstPaper.m_stucResult.m_strRow=="")
	{
		stucFirstPaper.m_stucResult.m_strColumn="H";
		stucFirstPaper.m_stucResult.m_strRow="21";
	}
	//校准结论，是否合格
	if(stucFirstPaper.m_stucConclusion.m_strColumn=="" || stucFirstPaper.m_stucConclusion.m_strRow=="")
	{
		stucFirstPaper.m_stucConclusion.m_strColumn="G";
		stucFirstPaper.m_stucConclusion.m_strRow="21";
	}
	//校准地点 0=实验室 1=委托方现场 -1=自定义地址
	if(stucFirstPaper.m_stucCalStation.m_strColumn=="" || stucFirstPaper.m_stucCalStation.m_strRow=="")
	{
		stucFirstPaper.m_stucCalStation.m_strColumn="D";
		stucFirstPaper.m_stucCalStation.m_strRow="34";
	}
	if(stucFirstPaper.m_stucTestAdrress.m_strColumn=="" || stucFirstPaper.m_stucTestAdrress.m_strRow=="")
	{
		stucFirstPaper.m_stucTestAdrress.m_strColumn="J";
		stucFirstPaper.m_stucTestAdrress.m_strRow="34";
	}

	//温度
	if(stucFirstPaper.m_stucTemperature.m_strColumn=="" || stucFirstPaper.m_stucTemperature.m_strRow=="")
	{
		stucFirstPaper.m_stucTemperature.m_strColumn="Q";
		stucFirstPaper.m_stucTemperature.m_strRow="34";
	}
	//湿度
	if(stucFirstPaper.m_stucHumidity.m_strColumn=="" || stucFirstPaper.m_stucHumidity.m_strRow=="")
	{
		stucFirstPaper.m_stucHumidity.m_strColumn="AA";
		stucFirstPaper.m_stucHumidity.m_strRow="34";
	}
	//测试人员
	if(stucFirstPaper.m_stucTester.m_strColumn=="" || stucFirstPaper.m_stucTester.m_strRow=="")
	{
		stucFirstPaper.m_stucTester.m_strColumn="G";
		stucFirstPaper.m_stucTester.m_strRow="37";
	}

//	MessageBox(0,stucFirstPaper.m_stucAddress_Customer.m_strName,"xx",0);

	////////////////////////打开Excel//////////////////////////////////////////////////
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	LPDISPATCH lpDisp;//接口指针
	Range range;
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	if(!app.CreateDispatch("Excel.Application"))
	{
		ThrowErr(无法创建Excel应用);
		return 0;
	}
	books=app.GetWorkbooks();
	lpDisp=books.Open(strTemFilePath,covOptional,covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional);
	book.AttachDispatch(lpDisp);
	sheets=book.GetSheets();
	int intSheetNum=stucFirstPaper.m_intSheetNumber;  //测试页面
	//sheet=sheets.GetItem(COleVariant((short)intSheetNum));
	sheet=sheets.GetItem(COleVariant((short)4));
	//range=sheet.GetRange(COleVariant("G21"),COleVariant("G21"));

	app.SetVisible(FALSE);
	app.SetUserControl(FALSE);
	///////////////////////写入Excel///////////////////////////////////////////////////

	///////////////////////////////////委托方///////////////////////////////////////
	CString strRange1=stucFirstPaper.m_stucCustomer.m_strColumn + stucFirstPaper.m_stucCustomer.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucCustomer.m_strName)); 
    /////////////////////////////////委托方地址///////////////////////////////////////
	strRange1=stucFirstPaper.m_stucAddress_Customer.m_strColumn+stucFirstPaper.m_stucAddress_Customer.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucAddress_Customer.m_strName));
	
	/////////////////////////////////设备名称/////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucInsName.m_strColumn+stucFirstPaper.m_stucInsName.m_strRow;  // g15
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucInsName.m_strName));
	/////////////////////////////// /设备型号//////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucInsModel.m_strColumn+stucFirstPaper.m_stucInsModel.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucInsModel.m_strName));
	/////////////////////////////////设备编号/////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucSNumber.m_strColumn+stucFirstPaper.m_stucSNumber.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucSNumber.m_strName));
	/////////////////////////////////管理编号/////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucNumber_Mana.m_strColumn+stucFirstPaper.m_stucNumber_Mana.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucNumber_Mana.m_strName));
	////////////////////////////////制造厂//////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucFactory.m_strColumn+stucFirstPaper.m_stucFactory.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucFactory.m_strName));
	////////////////////////////////校准日期//////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucCalDate.m_strColumn+stucFirstPaper.m_stucCalDate.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucCalDate.m_strName));
	////////////////////////////////建议再校准日期//////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucDueCalDate.m_strColumn+stucFirstPaper.m_stucDueCalDate.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucDueCalDate.m_strName));
	///////////////////////////////标准仪器///////////////////////////////////////////
	strRange1=stucFirstPaper.m_StandardName0.m_strColumn+stucFirstPaper.m_StandardName0.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardName0.m_strName));

	strRange1=stucFirstPaper.m_StandardNum0.m_strColumn+stucFirstPaper.m_StandardNum0.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardNum0.m_strName));

	strRange1=stucFirstPaper.m_StandardName1.m_strColumn+stucFirstPaper.m_StandardName1.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardName1.m_strName));

	strRange1=stucFirstPaper.m_StandardNum1.m_strColumn+stucFirstPaper.m_StandardNum1.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardNum1.m_strName));
	strRange1=stucFirstPaper.m_StandardName2.m_strColumn+stucFirstPaper.m_StandardName2.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardName2.m_strName));

	strRange1=stucFirstPaper.m_StandardNum2.m_strColumn+stucFirstPaper.m_StandardNum2.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardNum2.m_strName));
	strRange1=stucFirstPaper.m_StandardName3.m_strColumn+stucFirstPaper.m_StandardName3.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardName3.m_strName));

	strRange1=stucFirstPaper.m_StandardNum3.m_strColumn+stucFirstPaper.m_StandardNum3.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_StandardNum3.m_strName));
	///////////////////////////////器具用途///////////////////////////////////////////
//	strRange1=stucFirstPaper.m_stucInsUse.m_strColumn+stucFirstPaper.m_stucInsUse.m_strRow;
//	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
//	range.SetValue2(COleVariant(stucFirstPaper.m_stucInsUse.m_intSel==0?"FALSE":"TRUE"));
	///////////////////////////////校准结论///////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucConclusion.m_strColumn+stucFirstPaper.m_stucConclusion.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucConclusion.m_intSel==0?"FALSE":"TRUE"));
	///////////////////////////////校准地点///////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucCalStation.m_strColumn+stucFirstPaper.m_stucCalStation.m_strRow;  //d34
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucCalStation.m_intSel==0?"TRUE":"FALSE"));  //FALSE勾选右边，TRUE勾选左边
	if (stucFirstPaper.m_stucTestAdrress.m_strName == "实验室")
	{
		
	}
	else /*if (stucFirstPaper.m_stucTemperature.m_strName == "委托方现场")*/
	{
		strRange1=stucFirstPaper.m_stucTestAdrress.m_strColumn + stucFirstPaper.m_stucTestAdrress.m_strRow;  //j34
		range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
		range.SetValue2(COleVariant(stucFirstPaper.m_stucTestAdrress.m_strName));
	}
	
	///////////////////////////////温度///////////////////////////////////////////
    strRange1=stucFirstPaper.m_stucTemperature.m_strColumn+stucFirstPaper.m_stucTemperature.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucTemperature.m_strName));
	///////////////////////////////湿度///////////////////////////////////////////
	strRange1=stucFirstPaper.m_stucHumidity.m_strColumn+stucFirstPaper.m_stucHumidity.m_strRow;
	range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
	range.SetValue2(COleVariant(stucFirstPaper.m_stucHumidity.m_strName));

	//////////////////////////////测试结果////////////////////////////////////////////
//	sheet=sheets.GetItem(COleVariant((short)4));
	UUTItemSet stuItemSet;
	
	for(int i=0;i<stucFirstPaper.vstucResult.size();i++)
	{
		/////////////////////////写测试结果/////////////////////////////////////////////////
		//首先要根据逗号将结果单位等分开

		if(stucFirstPaper.vstucResult[i].m_strColumn.Find(",")==-1)  //只有一个值返回
		{	
		  strRange1=stucFirstPaper.vstucResult[i].m_strColumn+stucFirstPaper.vstucResult[i].m_strRow;
    	  range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
		  range.SetValue2(COleVariant(stucFirstPaper.vstucResult[i].m_strName));
		}
		else  //多个值返回
		{ 
		  vector<CString> m_strColumnTemp;//保存列
          vector<CString> m_strRowTemp;//保存行
          vector<CString> m_strNameTemp;//保存结果信息
	      StringToArray(stucFirstPaper.vstucResult[i].m_strColumn,",",&m_strColumnTemp); 
	      StringToArray(stucFirstPaper.vstucResult[i].m_strRow,",",&m_strRowTemp);
		  int sizeTemp; //保存存入数据的个数
		  if(stucFirstPaper.vstucResult[i].m_strName.Find(",")==-1)  //如果仅返回一个值，则表明返回值异常。
		  {
             sizeTemp=1; //存入1个值
			 m_strNameTemp.push_back("Invalid");
		  }
		  else
		  {
			 StringToArray(stucFirstPaper.vstucResult[i].m_strName,",",&m_strNameTemp);
			 sizeTemp=m_strNameTemp.size();
		  }         
          for(int j=0;j<sizeTemp;j++)
			  if(!m_strColumnTemp[j].IsEmpty())   //如果列属性为空，则表明不需要填进表格中
			  {
                  strRange1=m_strColumnTemp[j]+m_strRowTemp[j];
    	          range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
		          range.SetValue2(COleVariant(m_strNameTemp[j]));
			  }
		
		}
		/////////////////////////写结论/////////////////////////////////////////////////
		m_xml_tem.GetItemPositonByKey(stucFirstPaper.m_strTemplete,stucFirstPaper.vstucResult[i].m_strItemKey,&stuItemSet);
        if(stuItemSet.m_strResultCol!="")
		{
			strRange1=stuItemSet.m_strResultCol+stuItemSet.m_strResultRow;
			range=sheet.GetRange(COleVariant(strRange1),COleVariant(strRange1));
			if(stucFirstPaper.vstucResult[i].m_strConclusion=="0")
	    	range.SetValue2(COleVariant("Failed"));
		}
	}
	///////////////////////保存并关闭Excel///////////////////////////////////////////////////
	//book.SetSaved(TRUE);
	//book.Save();

	book.SaveAs(COleVariant(strSavefilePath),covOptional,covOptional,covOptional,covOptional,
		covOptional,0,covOptional,covOptional,covOptional,covOptional,covOptional);

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	//book.Close(covOptional,covOptional,vtMissing);
	//books.Close();
	//book.ReleaseDispatch();
	//books.ReleaseDispatch();
	app.SetVisible(TRUE);
//	app.Quit();
//	app.ReleaseDispatch();
	
	return 1;
}
void CFileOpe_Excel::StringToArray(CString strInput,CString key,vector<CString>* stringArray)
{
	CString strTemp;
	int intPos=0;
	while(strInput.Find(key)>=0)
	{
		intPos=strInput.Find(key);
		strTemp=strInput.Left(intPos);  //读取分割字符串
		strInput=strInput.Right(strInput.GetLength()-intPos-1);
		stringArray->push_back(strTemp);
	}
	 stringArray->push_back(strInput);
}