// Report.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Report.h"
#include "Xml_Bll_UUTItem_Tem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReport dialog

extern CString m_TestAddress1;
extern CString StandardName[4] ;
extern CString StandardNum[4];
CReport::CReport(CWnd* pParent /*=NULL*/)
	: CDialog(CReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReport)
	m_strStatus = _T("");
	m_strSearchKey = _T("");
	//}}AFX_DATA_INIT
}


void CReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReport)
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_cb_Search);
	DDX_Control(pDX, IDC_LIST_TESTRESULT, m_ListV_TestResult);
	DDX_Control(pDX, IDC_LIST_TESTINFO, m_ListV_TestInfo);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strSearchKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReport, CDialog)
	//{{AFX_MSG_MAP(CReport)
	ON_BN_CLICKED(IDC_RETURN, OnReturn)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TESTINFO, OnClickListTestinfo)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHINFO, OnButtonSearchinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReport message handlers

BOOL CReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle=m_ListV_TestInfo.GetExtendedStyle();
	m_ListV_TestInfo.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListV_TestResult.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	InitListView();
	InitListView_Result();

	vector<stucTestInfo> vTestInfo;
	m_tbTestInfo.ReadTestInfoList(&vTestInfo);
	UpdateListView_Info(vTestInfo);
    m_cb_Search.SetCurSel(0);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReport::OnReturn() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	
}

void CReport::OnButtonReport() 
{
	// TODO: Add your control notification handler code here
	POSITION pos=m_ListV_TestInfo.GetFirstSelectedItemPosition();
	if(pos ==NULL)
	{
		MessageBox("请选择测试信息","提示");
		return;
	}
	int nItem=m_ListV_TestInfo.GetNextSelectedItem(pos);
	int intSelID=m_ListV_TestInfo.GetItemData(nItem);

	//m_strStatus="正在生成证书，请稍后...";
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("正在生成证书，请稍后...");

	GetDlgItem(IDC_BUTTON_SEARCHINFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RETURN)->EnableWindow(FALSE);
	GenerateReport(intSelID);   //生成报告
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("");
	GetDlgItem(IDC_BUTTON_SEARCHINFO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_RETURN)->EnableWindow(TRUE);
}

void CReport::InitListView()
{
	while(m_ListV_TestInfo.DeleteColumn(0));
	RECT rRect;
	m_ListV_TestInfo.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);
	m_ListV_TestInfo.InsertColumn(0,"序号",LVCFMT_LEFT,width/13);
	m_ListV_TestInfo.InsertColumn(1,"测试时间",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(2,"委托方",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(3,"委托方地址",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(4,"设备名称",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(5,"设备型号",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(6,"制造厂",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(7,"设备编号",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(8,"设备用途",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(9,"管理编号",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(10,"校准日期",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(11,"有效期",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(12,"校准结果",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(13,"校准结论",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(14,"校准地点",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(15,"温度",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(16,"湿度",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(17,"测试人员",LVCFMT_LEFT,width/4);

}

void CReport::GenerateReport(int nTestInfoID)
{
	CXml_Bll_UUTItem_Tem fP1;

	FirstPaper stucPaper;
	stucTestInfo stuTestInfo;
	m_tbTestInfo.ReadTestInfo(&stuTestInfo,nTestInfoID);  //从数据库读取测试信息

	CString strTemPath=m_pathOpe.GetStartPath()+stuTestInfo.m_strTemplete+".xml"; //模版路径
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("找不到模板配置文件","错误");
		return;
	}
	
	CString strPageIndex;
	CArray<FrontPage, FrontPage> ftpg;
	fP1.ReadFrontPageList(strTemPath, strPageIndex, ftpg);
	////////////////////将测试封面信息转换为报告变量////////////////////////////////////////////
	stucPaper.m_intSheetNumber = -1;
	stucPaper.m_stucCustomer.m_strName=stuTestInfo.m_strCustomer;  //委托方
	stucPaper.m_stucAddress_Customer.m_strName=stuTestInfo.m_strAddress; //委托方地址
	stucPaper.m_stucInsName.m_strName=stuTestInfo.m_strInsName; //计量器具名称
	stucPaper.m_stucInsModel.m_strName=stuTestInfo.m_strModel; //器具型号
	stucPaper.m_stucFactory.m_strName=stuTestInfo.m_strFactory;//制造厂
	stucPaper.m_stucSNumber.m_strName=stuTestInfo.m_strSNumber; //器具编号
	stucPaper.m_stucInsUse.m_intSel=atoi(stuTestInfo.m_strInsUse); //器具用途
	stucPaper.m_stucNumber_Mana.m_strName=stuTestInfo.m_strNumber_Mana; //管理编号
	stucPaper.m_stucCalDate.m_strName=stuTestInfo.m_strCalDate; //校准日期
	stucPaper.m_stucDueCalDate.m_strName=stuTestInfo.m_strDueCalDate; //校准周期/建议再校准日期
	stucPaper.m_StandardName0.m_strName = StandardName[0]; //校准仪器名称
	stucPaper.m_StandardNum0.m_strName = StandardNum[0];  //校准仪器编号
	stucPaper.m_StandardName1.m_strName = StandardName[1]; //校准仪器名称
	stucPaper.m_StandardNum1.m_strName = StandardNum[1];  //校准仪器编号
	stucPaper.m_StandardName2.m_strName = StandardName[2]; //校准仪器名称
	stucPaper.m_StandardNum2.m_strName = StandardNum[2];  //校准仪器编号
	stucPaper.m_StandardName3.m_strName = StandardName[3]; //校准仪器名称
	stucPaper.m_StandardNum3.m_strName = StandardNum[3];  //校准仪器编号

	stucPaper.m_stucResult.m_strName=stuTestInfo.m_strResult; //校准结论，中文说明
	stucPaper.m_stucConclusion.m_intSel=(stuTestInfo.m_strConclusion=="pass"?1:0); //校准结论 是否合格
	stucPaper.m_stucCalStation.m_intSel=atoi(stuTestInfo.m_strCalStation); //校准地点:0=实验室 1=委托方现场 -1=自定义  atoi() 把字符串转换成整型数的一个函数
	stucPaper.m_stucTestAdrress.m_strName = m_TestAddress1;//校准地点
	stucPaper.m_stucTemperature.m_strName=stuTestInfo.m_strTemperature; //温度
	stucPaper.m_stucHumidity.m_strName=stuTestInfo.m_strHumidity;//湿度
	stucPaper.m_stucTester.m_strName=stuTestInfo.m_strTester; //校准人员

	/*if(strPageIndex != "")
		stucPaper.m_intSheetNumber = atoi(strPageIndex);
	for(int i = 0; i < ftpg.GetSize(); i++)
	{
		if(ftpg[i].strName == "Customer")
		{
			stucPaper.m_stucCustomer.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucCustomer.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Address_Customer")
		{
			stucPaper.m_stucAddress_Customer.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucAddress_Customer.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "InsName")
		{
			stucPaper.m_stucInsName.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucInsName.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "InsModel")
		{
			stucPaper.m_stucInsModel.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucInsModel.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Factory")
		{
			stucPaper.m_stucFactory.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucFactory.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "SNumber")
		{
			stucPaper.m_stucSNumber.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucSNumber.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "InsUse")
		{
			stucPaper.m_stucInsUse.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucInsUse.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Number_Mana")
		{
			stucPaper.m_stucNumber_Mana.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucNumber_Mana.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "CalDate")
		{
			stucPaper.m_stucCalDate.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucCalDate.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "DuaCalDate")
		{
			stucPaper.m_stucDueCalDate.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucDueCalDate.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Result")
		{
			stucPaper.m_stucResult.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucResult.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Conclusion")
		{
			stucPaper.m_stucConclusion.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucConclusion.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "CalStation")
		{
			stucPaper.m_stucCalStation.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucCalStation.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Temperature")
		{
			stucPaper.m_stucTemperature.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucTemperature.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Humidity")
		{
			stucPaper.m_stucHumidity.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucHumidity.m_strRow == ftpg[i].strRow;
		}
		if(ftpg[i].strName == "Tester")
		{
			stucPaper.m_stucTester.m_strColumn == ftpg[i].strCol;
			stucPaper.m_stucTester.m_strRow == ftpg[i].strRow;
		}
	}*/
	stucPaper.m_strTemplete=stuTestInfo.m_strTemplete; //模板路径
	//	MessageBox(stucPaper.m_stucAddress_Customer.m_strName);
    //////////////////////从数据库读取测试数据////////////////////////////////////////////////////
	vector<stucTestResult> vTestResult;
	m_tbTestResult.ReadTestResultList(&vTestResult,nTestInfoID);

	//////////////////////将测试结果信息转换为报告变量////////////////////////////////////////////////////
	vector<StringStruct> vstucResult; //测试结果列表
	strTemPath=m_pathOpe.GetStartPath()+stuTestInfo.m_strTemplete+".xls"; //模版路径
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("找不到标准文件模板","错误");
		return;
	}

	StringStruct stuResult;
	CString strSavePath=m_pathOpe.GetStartPath()+"Report";
	CFileFind ff;
	BOOL bFinded = ff.FindFile(strSavePath);
	bool bExist = false;
	while (bFinded)
	{
		bFinded = ff.FindNextFile();
		
		if (ff.IsDots())
			continue;
		if (ff.IsDirectory())
			bExist = true;
		else
			continue;
	}
	if(!bExist)
		CreateDirectory(strSavePath, FALSE);
	strSavePath += "\\"+stuTestInfo.m_strTestTime
		+"_"+stuTestInfo.m_strCustomer+"_"+stuTestInfo.m_strInsName+"_"+stuTestInfo.m_strModel
		+"_"+stuTestInfo.m_strSNumber+"_"+stuTestInfo.m_strNumber_Mana+".xls"; //存储路径

	if(GetFileAttributes(strSavePath)!=-1)
	{
		if(MessageBox("报告已经存在，是否覆盖","提示",MB_OKCANCEL)==1)
		{	
     		if(!DeleteFile(strSavePath))
			{
				MessageBox("证书为只读状态，无法覆盖","错误");
				return;
			}
		}
		else
		{
			return;
		}
	}
	for(int i=0;i<vTestResult.size();i++)
	{
		stuResult.m_strColumn=vTestResult[i].m_strCol;
		stuResult.m_strRow=vTestResult[i].m_strRow;
		stuResult.m_strName=vTestResult[i].m_strResult;
		stuResult.m_strConclusion=vTestResult[i].m_strConclusion;
		stuResult.m_strItemKey=vTestResult[i].m_strItemKey;
		vstucResult.push_back(stuResult);
	}
	stucPaper.vstucResult=vstucResult;
	m_Excel_Ope.WriteResultToExcel(strTemPath,strSavePath,stucPaper);   //将数据写进Excel模板
}

void CReport::UpdateTestResultList(int intTestInfoID)
{
	m_ListV_TestResult.DeleteAllItems();
	//从数据库读取测试数据
	vector<stucTestResult> vTestResult;
	m_tbTestResult.ReadTestResultList(&vTestResult,intTestInfoID);
	CString strID;
	for(int i=0;i<vTestResult.size();i++)
	{
		strID.Format("%d",i+1);
		m_ListV_TestResult.InsertItem(i,strID);
		m_ListV_TestResult.SetItemText(i,1,vTestResult[i].m_strItemName);
		m_ListV_TestResult.SetItemText(i,2,vTestResult[i].m_strTestSet);
		m_ListV_TestResult.SetItemText(i,3,vTestResult[i].m_strResult);
		m_ListV_TestResult.SetItemText(i,4,vTestResult[i].m_strLower);
		m_ListV_TestResult.SetItemText(i,5,vTestResult[i].m_strUpper);	
		m_ListV_TestResult.SetItemText(i,6,vTestResult[i].m_strUnit);						
	}
}

void CReport::InitListView_Result()
{
	while(m_ListV_TestResult.DeleteColumn(0));
	RECT rRect;
	m_ListV_TestResult.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);
	m_ListV_TestResult.InsertColumn(0,"序号",LVCFMT_LEFT,width/13);
	m_ListV_TestResult.InsertColumn(1,"项目名称",LVCFMT_LEFT,width/4);
	m_ListV_TestResult.InsertColumn(2,"测试条件",LVCFMT_LEFT,width/4);
	m_ListV_TestResult.InsertColumn(3,"测试结果",LVCFMT_LEFT,width/8);
	m_ListV_TestResult.InsertColumn(4,"下限值",LVCFMT_LEFT,width/10);
	m_ListV_TestResult.InsertColumn(5,"上限值",LVCFMT_LEFT,width/10);
	m_ListV_TestResult.InsertColumn(6,"单位",LVCFMT_LEFT,width/10);
}

void CReport::OnClickListTestinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CPoint pt=GetCurrentMessage()->pt;//获取当前鼠标消息坐标
	m_ListV_TestInfo.ScreenToClient(&pt);//转换为数控件中的客户坐标
	UINT uFlags=0;
	int intHitLine=m_ListV_TestInfo.HitTest(pt,&uFlags); //点击测试
	if((intHitLine!=-1)&& (TVHT_ONITEM&uFlags))
	{
		if(intHitLine!=m_intHitLine_Pre)
		{
			int intInfoID=m_ListV_TestInfo.GetItemData(intHitLine);
			UpdateTestResultList(intInfoID);
			m_intHitLine_Pre=intHitLine;
		}
	}		
	*pResult = 0;
}

void CReport::OnButtonSearchinfo() 
{
	// TODO: Add your control notification handler code here
	/*
	int intSel=m_cb_Search.GetCurSel();
	CString strContent("");
	if(intSel==1)
	{
		strContent="C";
	}
	else if(intSel==2)
	{
		strContent="InsModel";
	}
	else if(intSel==3)
	{
		strContent="InsFactory";
	}
	else if(intSel==4)
	{
		strContent="Number";
	}
	SearchListV_Basic(strContent);
	*/
	int intSel=m_cb_Search.GetCurSel();
	CString strContent("");
	if(intSel==1)
	{
		strContent="Customer";
	}
	else if(intSel==2)
	{
		strContent="Address";
	}
	else if(intSel==3)
	{
		strContent="InsName";
	}
	else if(intSel==4)
	{
		strContent="Model";
	}
	else if(intSel==5)
	{
		strContent="Factory";
	}
	else if(intSel==6)
	{
		strContent="SNumber";
	}
	else if(intSel==7)
	{
		strContent="Number_Mana";
	}
	SearchListV_TestInfo(strContent);
}

void CReport::SearchListV_TestInfo(CString strContent)
{
	UpdateData(); //保存查询内容
	vector<stucTestInfo> vTestInfo;
	m_strSearchKey.TrimLeft(" ");  //去除字符串前的空字符串
	m_strSearchKey.TrimRight(" "); //去除字符串后的空字符串
	m_tbTestInfo.SearchTestInfoList(&vTestInfo,strContent,m_strSearchKey); //执行查询命令
	UpdateListView_Info(vTestInfo);  //刷新测试结果列表
}

void CReport::UpdateListView_Info(vector<stucTestInfo> vTestInfo)
{
	m_ListV_TestInfo.DeleteAllItems(); //清空测试信息列表
	CString strID("");
	for(int i=0;i<vTestInfo.size();i++)
	{		
		strID.Format("%d",i+1);
		m_ListV_TestInfo.InsertItem(i,strID);
		//m_ListV_TestInfo.SetItemText(i,0,strID);
		m_ListV_TestInfo.SetItemText(i,1,vTestInfo[i].m_strTestTime); //测试时间
		m_ListV_TestInfo.SetItemText(i,2,vTestInfo[i].m_strCustomer);//委托方
		m_ListV_TestInfo.SetItemData(i,vTestInfo[i].m_intID); //测试信息ID
		m_ListV_TestInfo.SetItemText(i,3,vTestInfo[i].m_strAddress); //委托方地址
		m_ListV_TestInfo.SetItemText(i,4,vTestInfo[i].m_strInsName); //设备名称
        m_ListV_TestInfo.SetItemText(i,5,vTestInfo[i].m_strModel); //设备型号
        m_ListV_TestInfo.SetItemText(i,6,vTestInfo[i].m_strFactory); //制造厂
        m_ListV_TestInfo.SetItemText(i,7,vTestInfo[i].m_strSNumber); //出厂编号
        m_ListV_TestInfo.SetItemText(i,8,vTestInfo[i].m_strInsUse); //设备用途
        m_ListV_TestInfo.SetItemText(i,9,vTestInfo[i].m_strNumber_Mana); //管理编号
		m_ListV_TestInfo.SetItemText(i,10,vTestInfo[i].m_strCalDate); //校准日期
		m_ListV_TestInfo.SetItemText(i,11,vTestInfo[i].m_strDueCalDate); //建议再校准日期
		m_ListV_TestInfo.SetItemText(i,12,vTestInfo[i].m_strResult); //校准结论
		m_ListV_TestInfo.SetItemText(i,13,vTestInfo[i].m_strConclusion); //是否合格
		m_ListV_TestInfo.SetItemText(i,14,vTestInfo[i].m_strCalStation); //校准地点
		m_ListV_TestInfo.SetItemText(i,15,vTestInfo[i].m_strTemperature); //温度
		m_ListV_TestInfo.SetItemText(i,16,vTestInfo[i].m_strHumidity); //湿度
        m_ListV_TestInfo.SetItemText(i,17,vTestInfo[i].m_strTester); //测试人员
		
	}
	if(m_ListV_TestInfo.GetItemCount()>0)
	{
		m_ListV_TestInfo.SetItemState(0,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListV_TestInfo.SetFocus();
		int intInfoID=m_ListV_TestInfo.GetItemData(0);
		UpdateTestResultList(intInfoID);
	}
	else
	{
		m_ListV_TestResult.DeleteAllItems();
	}
	m_intHitLine_Pre=0;
}
