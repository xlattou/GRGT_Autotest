// AutoTest.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"iqapi.lib")
/////////////////////////////////////////////////////////////////////////////
// CAutoTest dialog
CString m_IpTest="TCPIP0::192.168.100.254::hislip0::INSTR";          //测试用
CString m_CHTest = "1A";     //通道
CString m_VSGTest = "1";     //通道
CString m_ROUTTest = "1";     //通道
iqapiHndl m_iqApi;         //IQ全局变量
unsigned char isTestQuit = 0 ; 
extern bool IgnoreDialog;  //忽略报错弹窗标志
CString m_TestAddress1 = "";
CString StandardName[4] ={""};
CString StandardNum[4]= {""};
CAutoTest::CAutoTest(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoTest::IDD, pParent)
	, m_IP(_T(""))
	, m_CH(_T(""))
	, m_VSG(_T(""))
	, m_ROUT(_T(""))
{
	//{{AFX_DATA_INIT(CAutoTest)
	m_strManu = _T("");
	m_strModel = _T("");
	m_strName = _T("");
	m_strNumber = _T("");
	m_edit_Progress = _T("");
	m_strCustomer = _T("");
	m_strNumber_Mana = _T("");
	m_strTemperature = _T("");
	m_strHumity = _T("");
	m_strAddress_Customer = _T("");
	m_DateTime = 0;
	m_intTestStation = -1;
	m_intInsUse = -1;
	m_strTestTime = _T("");
	m_intTestLine=0;
	m_strElapseTime = _T("");
	m_bIgnoreCurrentItem = false;
	//}}AFX_DATA_INIT
}
DWORD WINAPI ProgTest(CAutoTest *p)
{
	//仪器驱动接口路径：起始路径+"DataInfo\\UUTTestInfo\\"+设备类型（例如：数字万用表）+"\\InsPortDriver\\"+设备类型（例如：数字万用表）+"_Engine.dll"
	CString strdllPath=p->m_pathOpe.GetStartPath()
		+"DataInfo\\UUTTestInfo\\"+p->m_strThreadKind+"\\InsPortDriver\\"+p->m_strThreadKind+"_Engine.dll";   //仪器驱动接口路径
	CString strLuaFilePath="";
	CString strUUTCom="COM1"; //测试串口为COM1
	CString strInputVar="";
	CString strTestConfigFilePath="";//测试配置文件路径
	int intTestSerial=-1;  //测试序号，还没开始或者测试完毕后被置-1
	int intTestMode=0;
	char testResult[100];
	CString strListValuePre="";
	CString strConnPic_Pre="";
	int i=0;
	
	CString strItemName="";
	UUTItemSet stuItemSet;
	
	
	UUTItemVarSet stuItemInfo; //测试项目信息

	TiXmlNode* pNode=NULL;
	char errBuff[128];
	
	COPYDATASTRUCT cpd;
	TiXmlElement* pEle=NULL;
	UUTInfoSet stucUUTInfo;
	TestPointSet stucPointSet;
	//int count=0;
	stucTestResult sTestResult;
	CString  strKey; //项目关键字

	BOOL isRetest=FALSE; //复测

	vector<CString> vTestResultKey;  //测试结果标识名
	vector<CString> vTestResult; //测试结果
	BOOL bTestResult; //测试结论是否合格
	p->m_bIgnoreCurrentItem = false;

	p->m_bll_UUTInfo.ReadUUTBasicInfo(p->m_strThreadKind,p->m_strThreadModel,&stucUUTInfo);
	//测试配置文件路径：起始路径+"DataInfo\\UUTTestInfo\\"+设备类型（例如：数字万用表）+"\\TPS\\"+模型名称（例如：Agilent 34401A）+"\\Solution\\"+S_5700+"\\TestConfig\\"+模型名称（例如：Agilent 34401A）+" testConfig.ini"
	strTestConfigFilePath=p->m_pathOpe.GetStartPath()
		+"DataInfo\\UUTTestInfo\\"+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel
		+"\\Solution\\"+p->m_strSoluName+"\\TestConfig\\"+p->m_strThreadModel+" testConfig.ini";
	//获得测试项（选中行）的数量
	int intCheckItemCount=p->m_vItemName.size();

	int isStop=FALSE;
	p->m_intPotCount=p->m_List_Result.GetItemCount();
	Sleep(100);   //线程挂起100ms

	
	for(i=0;i<p->m_intPotCount;i++)  //每一次循环测试一个测试点
	{
		p->m_intTestLine=i; //第i测试行
	//	p->m_isPotCheck=p->m_List_Result.GetCheck(i);
		p->m_isPotCheck=p->m_listVCheckState[i];   //获得该行选中的状态
		if(p->m_isPotCheck)  //若该行选中状态为真，选中就测试
		{
			p->m_intTestSerial++;  //测试项计数
			intTestSerial++;        //初始化为-1，首顺序号规定为0。
			try
			{
				p->m_strItemName=p->m_List_Result.GetItemText(i,1);   //获得测试项目名称
				strItemName=p->m_strItemName; //转换成CString 格式
 				if(p->m_intTestSerial<intCheckItemCount && strItemName!=p->m_vItemName[p->m_intTestSerial])
 				//测试序列号 < 勾选项数量  &&  获得的测试项目名称!=选中号相应名称
				{
 					intTestSerial=-1;   //首顺序号
 				}
				if(p->m_intTestSerial==intCheckItemCount)  //测试对话框测试序列号 == 勾选项数量 
				{
 					intTestSerial=-1;  //首顺序号
				}

				p->SendMessage(WM_MYUPDATEDATA,3,0); //确保被选中的行（项）是可见的，如果被选中的行（项）不在控件窗口内，就会发生滚动。
                Sleep(100);
				
				if (strKey != p->m_vKeyList[i])
				{
					strKey=p->m_vKeyList[i];  //获取当前行的测试项目关键字，测试时根据项目关键字，查找并调用Lua
					isTestQuit = 0;
				}
			
			//	strItemName=p->m_strItemName; 
				//从xml文件中读取测试项目信息，并获取该项目节点，保存在stuItemInfo
		//		p->m_bll_UUTItem.GetItemInfo(p->m_strThreadKind,p->m_strThreadModel,strItemName,&stuItemInfo); //从TestConfig文件夹下的XML文件读取测试项目设置信息
				p->m_bll_UUTItem.GetItemInfo(p->m_strThreadKind,p->m_strThreadModel,p->m_strSoluName,strKey, &stuItemInfo);
				strLuaFilePath=stuItemInfo.m_strProgName; //lua脚本文件的路径
				p->m_strConnectPic=stuItemInfo.m_strConnectPic;  //测试连接图
				p->m_strDescription_Conn=stuItemInfo.m_strConnectDescription; //连接提示

				//Lua程序名从刚获得信息中取得
				//获取Lua程序的路径：起始地址+ "DataInfo\\UUTTestInfo\\" + 装置类型（例如：数字万用表）+ "\\TPS\\" + 模型名称（例如：Agilent 34401A）+ 解决方案名称（例如：S_5700_33521） + "\\TestItem\\" + Lua程序名称;
				strLuaFilePath=p->m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
					+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel+"\\Solution\\"+p->m_strSoluName
					+"\\TestItem\\"+strLuaFilePath; //获取Lua程序的路径
                p->m_strTestMark=p->m_List_Result.GetItemText(i,2); 

				//连接图的路径 测试对话框测试接线图及连接提示从刚获得信息中获得
				CString strFilePath=p-> m_strConnectPic;
				strFilePath=p->m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
					+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel+"\\Solution\\"+p->m_strSoluName+"\\TestConfig\\ConnectPic\\"+p->m_strConnectPic;

				if (isTestQuit == 0 && p->m_strConnectPic!=strConnPic_Pre)  //isTestQuit==1表示一次测试过程中连接对话框已经弹出一次，在该测试过程后不需再弹出连接对话框
				{
					isTestQuit = 1;
					CFrame_TestConnect frm_Connect(strFilePath,p->m_strItemName,p->m_strDescription_Conn);//连接图的路径，测试项目的名称，连接提示
					frm_Connect.DoModal();     //弹出连接对话框
					if (frm_Connect.m_Quit)  //如果按下连接对话框的终止按键
					{
						p->OnButtonStop() ;
						p->UpdateControl(1);
						p->m_TestButton.EnableWindow(TRUE); //测试按键可用
						p->UpdateListView();  //更新测试结果列表框
						/*KillTimer(p->m_hWnd,1);
						KillTimer(p->m_hWnd,2);
						KillTimer(p->m_hWnd,3);*/
						return 1; 
					}
				}
				///////////////////////////测试提示对话框///////////////////////////////////////////////
				//	Sleep(100);
				if(p->m_intTestSerial==1)  //是否是刚开始测试
				{
					p->SendMessage(WM_MYUPDATEDATA,1,0); //1测试提示对话框
					if(p->m_bIgnoreCurrentItem)   //忽略当前测试项标志位
					{
						strConnPic_Pre = "";
						p->m_bIgnoreCurrentItem = false;
						continue;
					}
					else
						strConnPic_Pre=p->m_strConnectPic;   //测试连接图
				}
				else if(p->m_intTestSerial<=intCheckItemCount && strItemName!=p->m_vItemName[p->m_intTestSerial-2])
				//非刚开始，选数量质量之内且测试项目不与前一个测试项目相同
				{
					if(p->m_strConnectPic!=strConnPic_Pre) //如果连接图名称与弹出时连接图不相同，则弹出
					{
			    		Sleep(100);
						p->SendMessage(WM_MYUPDATEDATA,1,0); //1测试提示对话框
					}
					if(p->m_bIgnoreCurrentItem)
					{
						strConnPic_Pre = "";
						p->m_bIgnoreCurrentItem = false;
						continue;
					}
					else
						strConnPic_Pre=p->m_strConnectPic;  	
				}
					

				if(p->m_strTestMark!="Control") //从xml文件中获取测试项目关键字不是“Control”
				{
					p->m_intPointID=p->m_List_Result.GetItemData(i);
					//根据项目ID获得测试点节点
					pNode=p->m_bll_UUTPointInfo.GetPointNode(p->m_strThreadKind,p->m_strThreadModel,p->m_strTem,
						strKey,p->m_intPointID);
					if(pNode==NULL)
					{
						ThrowErr(找不到测试点);
					}
					//读取节点信息
					p->m_bll_UUTPointInfo.ReadPointInfo(pNode->Parent()->Parent(),p->m_intPointID,&stucPointSet);
					//获得测试条件字符串
					strInputVar=p->m_bll_UUTPointVar.GetPtVarTestString(pNode->ToElement());
		    		strInputVar+=";Result="+stucPointSet.m_strResultUnit;
				}
				else
				{
					
				}

				//保存测试上下限及单位到测试对话框
				p->m_strUpper=stucPointSet.m_strUpper;
				p->m_strLower=stucPointSet.m_strLower;
				p->m_strUnit=stucPointSet.m_strResultUnit;	
				int intTestSerial_Temp=intTestSerial;  //临时存储测试顺序号
				do 
				{
					//加载TP（测试程序）
					CLoadTP::MyLoadTP(strdllPath,strLuaFilePath,strUUTCom,strInputVar,strTestConfigFilePath,intTestSerial,intTestMode,testResult,m_IpTest,m_CHTest,m_VSGTest,m_ROUTTest);
					p->m_strResult=testResult;

					vTestResultKey.clear();  //清空测试结果关键字
					vTestResult.clear();  //清空测试结果缓冲
					p->m_strResultIndicate="";  //界面显示的测试结果
					if(stucPointSet.m_strResultMark.Find(",")==-1||p->m_strResult.Find(",")==-1)
					{
						p->m_strResultIndicate=p->m_strResult;  //只有一个测试结果直接显示实际测试结果
					}
					else
					{
					    p->StringToArray(stucPointSet.m_strResultMark,",",&vTestResultKey); //使用“，”分割测试条件内测试结果，放入向量
						p->StringToArray(p->m_strResult,",",&vTestResult); //使用“，”分割实际测试结果，放入向量
						for(int k=0;k<vTestResultKey.size();k++)
						{
							p->m_strResultIndicate+=vTestResultKey[k];
							p->m_strResultIndicate+="="+vTestResult[k]+",";
						}
						p->m_strResultIndicate=p->m_strResultIndicate.Left(p->m_strResultIndicate.GetLength()-1);
					}	
					//向主界面发送消息
					cpd.dwData=0;
					cpd.cbData=50;
					cpd.lpData=(void*)testResult;//无类型指针,给应用程序传递数据用的.测试结果传递给界面线程，在测试结果列表显示
					p->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);  //显示测试结果
		    		Sleep(300);
					//////////////////////判断是否合格，如果不合格启用错误处理提示框////////////////////////////////////////////////////

	    		    if(p->m_strTestMark!="Control") //测试项目标志位为Control
					{
		    			bTestResult=p->Aduge(testResult,stucPointSet.m_strUpper,stucPointSet.m_strLower);
		    			if(bTestResult==FALSE)   //测试结果为不合格
						{
				    		p->SendMessage(WM_MYUPDATEDATA,4,0); //弹出测试结果不合格对话框
				    		Sleep(100);
				    		if(p->m_intRetestMark==1)
							{
		    		    		//intTestSerial=-1;
					    		isRetest=TRUE;  //重测
							}
				    		else if(p->m_intRetestMark==2)
							{
						    	isRetest=FALSE;
							}
					    	else if(p->m_intRetestMark==3)
							{
						    	isRetest=FALSE;
						    	p->m_isStop=TRUE;   //终止
							}
							else if(p->m_intRetestMark==4)
							{
								isRetest = FALSE;
								strConnPic_Pre = "";  //忽略
							}
						}
					
			    		else
						{
					    	isRetest=FALSE;
						}
					}

				} while (isRetest);
				intTestSerial=intTestSerial_Temp; //还原测试顺序号，主要跟TP程序有关
								

				p->SendMessage(WM_MYUPDATEDATA,2,p->m_intTestSerial*100/intCheckItemCount);  ///更新测试进度
				Sleep(100);  //线程挂起100ms
                
				///////////////////////////测试结果信息临时处理///////////////////////////////////////////////
		    	
				if(p->m_strTestMark!="Control")
				{
					sTestResult.m_strItemName=strItemName;		
					sTestResult.m_strUpper=stucPointSet.m_strUpper;
					sTestResult.m_strLower=stucPointSet.m_strLower;
					sTestResult.m_strUnit=stucPointSet.m_strResultUnit;
					sTestResult.m_strCol=stucPointSet.m_strCol;  //
					sTestResult.m_strRow=stucPointSet.m_strLine; //
					sTestResult.m_strResult=testResult;
					sTestResult.m_strTestSet=p->m_strTestMark;
					sTestResult.m_strConclusion=bTestResult?"1":"0"; //测试结果是否合格 1=合格 0=不合格
					sTestResult.m_strItemKey=strKey;
		    		p->m_vTestResult.push_back(sTestResult);   //将测试结果存入数据库中
				}
			}
			catch (CMemoryException* e)
			{
				e->GetErrorMessage(errBuff,10);
				MessageBox(p->GetSafeHwnd(),errBuff,"错误",0);	
			}
			catch (char* e)
			{
				MessageBox(p->GetSafeHwnd(),e,"错误",0);
			}
		}   //end若该行选中状态为真，选中就测试
		if(p->m_isStop)  // 判断是否有终止测试标志位
		{
			break;
		}
	}
	p->SendMessage(WM_MYUPDATEDATA,1,1); //测试结果处理,1测试中止
	Sleep(100);
	IgnoreDialog = false ; 
	return 0;
}

void CAutoTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoTest)
	DDX_Control(pDX, IDC_CALIBRATION_ALL, m_calibration_All);
	DDX_Control(pDX, IDC_LIST_INS, m_list_Ins);
	DDX_Control(pDX, IDC_COMBO_SOLUTION, m_cb_Solution);
	DDX_Control(pDX, IDC_COMBO_DUETIME, m_cbb_DuTime);
	DDX_Control(pDX, IDC_EDIT_LIST, m_edit_List);
	DDX_Control(pDX, IDC_CHECK_ALL, m_check_All);
	DDX_Control(pDX, IDC_PROGRESS_TEST, m_progress_test);
	DDX_Control(pDX, IDC_COMBO_MODULE, m_cbModule);
	DDX_Control(pDX, IDC_LIST_STATUS, m_listBox_Status);
	DDX_Control(pDX, IDC_LIST_RESULT, m_List_Result);
	DDX_Control(pDX, IDC_TREE_TPS, m_tree_tps);
	DDX_Text(pDX, IDC_EDIT_MANUFACTORY, m_strManu);
	DDX_Text(pDX, IDC_EDIT_MODEL, m_strModel);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_STATIC_PROGRESS, m_edit_Progress);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER, m_strCustomer);
	DDX_Text(pDX, IDC_EDIT_NUMBER_M, m_strNumber_Mana);
	DDX_Text(pDX, IDC_EDIT_TEMPER, m_strTemperature);
	DDX_Text(pDX, IDC_EDIT_SHI, m_strHumity);
	DDX_Text(pDX, IDC_EDIT_CUSTADD, m_strAddress_Customer);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_CAL, m_DateTime);
	DDX_CBIndex(pDX, IDC_COMBO_TESTSTATION, m_intTestStation);
	DDX_CBIndex(pDX, IDC_COMBO_INSUSE, m_intInsUse);
	DDX_Text(pDX, IDC_STATIC_TESTTIME, m_strTestTime);
	DDX_Text(pDX, IDC_STATIC_ELAPTIME, m_strElapseTime);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_TEST, m_TestButton);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_Num);
	DDX_Control(pDX, IDC_EDIT_NUMBER_M, m_ManageNum);
	DDX_Control(pDX, IDC_COMBO_TESTSTATION, m_TestAddress);
	DDX_Control(pDX, IDC_BUTTON_GETSN, m_GetSN);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	DDX_Text(pDX, IDC_CH_EDIT, m_CH);
	DDX_Text(pDX, IDC_VSG_EDIT2, m_VSG);
	DDX_Text(pDX, IDC_ROUT_EDIT3, m_ROUT);
}


BEGIN_MESSAGE_MAP(CAutoTest, CDialog)
	//{{AFX_MSG_MAP(CAutoTest)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_NOTIFY(NM_CLICK, IDC_TREE_TPS, OnClickTreeTps)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_NOTIFY(HDN_ITEMDBLCLICK, IDC_LIST_RESULT, OnItemdblclickListResult)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT, OnDblclkListResult)
	ON_EN_SETFOCUS(IDC_EDIT_NUMBER, OnSetfocusEditNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMBER, OnKillfocusEditNumber)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TESTSET, OnButtonTestset)
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE, OnSelchangeComboModule)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP3, OnButtonReTest)
	ON_CBN_SELCHANGE(IDC_COMBO_SOLUTION, OnSelchangeComboSolution)
	ON_BN_CLICKED(IDC_STATIC_NUM, OnStaticNum)
	ON_BN_CLICKED(IDC_BUTTON_INSTRSTATE, OnButtonInstrstate)
	ON_BN_CLICKED(IDC_CALIBRATION_ALL, OnCalibrationAll)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT, OnClickListResult)
	ON_EN_SETFOCUS(IDC_EDIT_NAME, OnSetfocusEditNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, OnKillfocusEditNumber)
	ON_EN_SETFOCUS(IDC_EDIT_MODEL, OnSetfocusEditNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_MODEL, OnKillfocusEditNumber)
	ON_EN_SETFOCUS(IDC_EDIT_MANUFACTORY, OnSetfocusEditNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_MANUFACTORY, OnKillfocusEditNumber)
	ON_MESSAGE(WM_MYUPDATEDATA,OnUpdateMyData)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_GETSN, OnButtonGetsn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CAutoTest)

//EASYSIZE(IDC_LIST_USER,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0);
//EASYSIZE(IDC_LIST_STATUS,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_EDIT_LIST,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_LIST_INS,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)

EASYSIZE(IDC_LIST_RESULT,ES_BORDER,IDC_STATIC_BASICINFO,ES_BORDER,ES_BORDER,0)
EASYSIZE(IDC_EDIT_NAME,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_EDIT_MODEL,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_EDIT_MANUFACTORY,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_NAME,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_MODEL,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_STATIC_MANUFACT,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_TREE_TPS,ES_BORDER,ES_BORDER,ES_KEEPSIZE,IDC_EDIT_NAME,0)
EASYSIZE(IDC_STATIC_PROGRESS,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
EASYSIZE(IDC_PROGRESS_TEST,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
//EASYSIZE(IDC_STATIC_BASICINFO,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
//EASYSIZE(IDC_PIC_CONN,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);

END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CAutoTest message handlers

BOOL CAutoTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CBitmap bmp;
	//LoadImage()
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);	
	
	// TODO: Add extra initialization here
	m_ShareMem.nSize=255;
	m_progress_test.SetRange(0,100);
	m_hItem_Pre=NULL;

	UpdateFirstPaper();
	InitTreeList(); //初始化树控件
	m_List_Result.SetImageList(&m_imageList,LVSIL_SMALL);
	CComboBox* pCbb_Due=(CComboBox*)GetDlgItem(IDC_COMBO_DUETIME);
	pCbb_Due->SetCurSel(1);
	m_edit_Progress="0 %";
	UpdateData(FALSE);
	m_strStartPath=m_pathOpe.GetAppPath();
	DWORD dwStyle=m_List_Result.GetExtendedStyle();
	m_List_Result.SetExtendedStyle(dwStyle|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);  //|LVS_EX_SUBITEMIMAGES
	
	m_list_Ins.SetImageList(&m_imageListSmall,LVSIL_SMALL);
	
	dwStyle=m_list_Ins.GetExtendedStyle();
	m_list_Ins.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	UpdateControl(0); //初始化各种控件

	//m_tree_tps.ModifyStyle(0,TVS_SHOWSELALWAYS|TVS_FULLROWSELECT);

	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//初始化证书首页信息
void CAutoTest::UpdateFirstPaper()
{
	m_DateTime=CTime::GetCurrentTime();
	m_intInsUse=0;
	m_intTestStation=0;
	m_strTemperature="23";
	m_strHumity="60";
	UpdateData(FALSE);

	
}

////////////////////////////初始化树列表////////////////////////////////////////
void CAutoTest::InitTreeList()
{
	//图形列表
	HICON hIcon[4];
	
	m_imageList.Create(32,32,ILC_COLOR32|ILC_MASK,4,4);
	hIcon[0]=AfxGetApp()->LoadIcon(IDI_ICON5);
	hIcon[1]=AfxGetApp()->LoadIcon(IDI_ICON6);
	hIcon[2]=AfxGetApp()->LoadIcon(IDI_ICON7);
	hIcon[3]=AfxGetApp()->LoadIcon(IDI_ICON8);
	
	for(int i=0;i<4;i++)
	{
		m_imageList.Add(hIcon[i]);
	}
	m_tree_tps.SetImageList(&m_imageList,TVSIL_NORMAL);
	HICON hIconSmall[2];
	
	m_imageListSmall.Create(16,16,ILC_COLOR32|ILC_MASK,2,2);
	hIconSmall[0]=AfxGetApp()->LoadIcon(IDI_ICON13);
	hIconSmall[1]=AfxGetApp()->LoadIcon(IDI_ICON12);
	for(int i=0;i<2;i++)
	{
		m_imageListSmall.Add(hIconSmall[i]);
	}
	//加载数据
	try
	{
		vector<UUTKindList> vKindList;
		vector<FileInfo> vFileInfo;
		m_xml_Kind.GetKindList(&vKindList);    //设备种类列表
		for(int i=0;i<vKindList.size();i++)
		{
			HTREEITEM hTreeItem=m_tree_tps.InsertItem(vKindList[i].m_strKindName,2,2);//在树控件添加种类列表
			
			m_tree_tps.SetItemData(hTreeItem,vKindList[i].m_intUINumber);
			m_file_UUTInfo.GetUUTList(vKindList[i].m_strKindName,&vFileInfo);  //型号列表
			
			for(int j=0;j<vFileInfo.size();j++)
			{
				//在树控件添加型号列表
				HTREEITEM hTreeItem_UUT=m_tree_tps.InsertItem(vFileInfo[j].m_strFileName,1,1,hTreeItem);
				
			}
			vFileInfo.clear();
		}
	}
	catch(char* e)
	{
		MessageBox(e);
	}
}

//初始化列表控件
void CAutoTest::InitListView()
{
	//m_List_Result.GetHeaderCtrl()->GetItemCount();
	while(m_List_Result.DeleteColumn(0));

	RECT rRect;
	m_List_Result.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);	
	m_List_Result.InsertColumn(0,"序号",LVCFMT_LEFT,width/8);
	m_List_Result.InsertColumn(1,"测试项目",LVCFMT_LEFT,width*2/11);
	m_List_Result.InsertColumn(2,"测试条件",LVCFMT_LEFT,width*3/14);
	m_List_Result.InsertColumn(3,"测试结果",LVCFMT_LEFT,width/9);
	m_List_Result.InsertColumn(4,"下限值",LVCFMT_LEFT,width/11);
	m_List_Result.InsertColumn(5,"上限值",LVCFMT_LEFT,width/11);
	m_List_Result.InsertColumn(6,"单位",LVCFMT_LEFT,width/12);
	m_List_Result.InsertColumn(7,"结论",LVCFMT_LEFT,width/12);
}

void CAutoTest::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CAutoTest::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	Invalidate(); //重绘
	UPDATE_EASYSIZE;
}

void CAutoTest::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(150,100,fwSide,pRect);		
}

void CAutoTest::OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pt=GetCurrentMessage()->pt;  //获取当前鼠标消息坐标
	m_tree_tps.ScreenToClient(&pt);   //转换为数控件中的客户坐标
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_tps.HitTest(pt,&uFlags); //点击测试
	if((hItem!=NULL)&&(TVHT_ONITEM&uFlags)) //如果点击项目有效
	{
		if(m_tree_tps.GetParentItem(hItem)!=NULL&&m_tree_tps.GetParentItem(m_tree_tps.GetParentItem(hItem))==NULL)
		{
			//如果选中第二层，即型号层
			m_strThreadModel=m_tree_tps.GetItemText(hItem);
			m_strThreadKind=m_tree_tps.GetItemText(m_tree_tps.GetParentItem(hItem));	
			UpdateControl(1); //更改按钮状态为测试前状态
			if(hItem!=m_hItem_Pre) //该选择型号与上一次不同，刷新测试信息
			{
				UpdateTestInfo();
				UpdateListView();	
				for(int i=0;i<m_List_Result.GetItemCount();i++)
				{
					m_List_Result.SetCheck(i,TRUE);
				}
			}
			
		}
		else
		{
			UpdateControl(0); //如果没有选中测试分组层,更改为不可测试状态
		}
		m_hItem_Pre=hItem;
	}
	m_TestButton.EnableWindow(FALSE);
	*pResult = 0;
}

////////////////////////////刷新基本信息表/////////////////////////////////////////
void CAutoTest::UpdateTestInfo()
{
	try
	{
    	UUTInfoSet stucUUTInfo;
    	m_bll_UUTInfo.ReadUUTBasicInfo(m_strThreadKind,m_strThreadModel,&stucUUTInfo); //类别，例数字万用表；型号，例Agilent 34401A
    	m_strName=stucUUTInfo.m_strName;
    	m_strModel=stucUUTInfo.m_strModel;
    	m_strManu=stucUUTInfo.m_strFactory;
    	UpdateModuleList(stucUUTInfo.m_strTestTem);
	//	if(m_cbModule)
    	UpdateData(FALSE);
	}
	catch (char* e)
	{
		MessageBox(e);
	}
}
BOOL CAutoTest::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_imageList)
		m_imageList.DeleteImageList();
	if(m_imageListSmall)
		m_imageListSmall.DeleteImageList();

	m_brush.DeleteObject();
	

	return CDialog::DestroyWindow();
}

void CAutoTest::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	m_TestAddress.GetWindowText(strTemp);  
	m_TestAddress1 = strTemp;
	
	isTestQuit = 0 ;  //需要弹出连接框
	m_progress_test.SetPos(0);  //进度条恢复为初始状态
	UpdateData();
	if(m_strNumber.IsEmpty())
	{
		MessageBox("设备编号不能为空");
		return;
	}
	m_vItemName.clear();
	m_listVCheckState.clear();
	char szListValue[50];
	for(int i=0;i<m_List_Result.GetItemCount();i++)
	{
		if(m_List_Result.GetCheck(i))
		{
			m_List_Result.GetItemText(i,1,szListValue,50);
			
			//	intCheckItemCount++;
			m_vItemName.push_back((CString)szListValue);
		//	m_List_Result.SetItem()
		}
		m_listVCheckState.push_back(m_List_Result.GetCheck(i));
	}
	if(m_vItemName.size()==0)
	{
		MessageBox("请选择测试项目");
		return;
	}
	///////////////////////////////初始化状态文件///////////////////////////////////////////
	CFile fileMyFile;
	fileMyFile.Open(m_strStartPath+"\\DeviceHandle.ini",CFile::modeCreate);
	fileMyFile.Close();
	WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停
	
    for(int i=0;i<m_List_Result.GetItemCount();i++)
	{
		m_List_Result.SetItemText(i,3,"");
		m_List_Result.SetItemText(i,7,"");
	}
	UpdateListBox(0);
	UpdateControl(2);
    m_vTestResult.clear();
	int intSel=m_cbModule.GetCurSel();
	m_cbModule.GetLBText(intSel,m_strTem);

    m_intTestSerial=0;
	SetTimer(1,50,NULL);
	SetTimer(2,10,NULL);
	SetTimer(3,1000,NULL);
	HANDLE hThread1;
	m_isTestEnd=FALSE;
    m_isStop=FALSE;
    m_intTestLine=0;
	m_intTimeTick=0;
	m_strConclusion="Pass";

	DWORD dwStyle=m_List_Result.GetExtendedStyle();
	m_List_Result.SetExtendedStyle(dwStyle&~LVS_EX_CHECKBOXES);
	

	hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ProgTest,this,0,NULL);
	
	m_List_Result.SetFocus();
	CloseHandle(hThread1);	

}

LRESULT CAutoTest::OnUpdateMyData(WPARAM wParam, LPARAM lParam)
{
	if(wParam==2)
	{
		m_progress_test.SetPos(lParam);
		m_edit_Progress.Format("%d",lParam);
		m_edit_Progress+="%";
		UpdateData(FALSE);
	}
	else if(wParam==1&&lParam==0)
	{
		m_isTestEnd=TRUE;
		//CFrame_TestConnect frm_Connect(this);

		//测试连接图的路径
		CString strFilePath= m_strConnectPic;
		strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
			+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\ConnectPic\\"+m_strConnectPic;
		CFrame_TestConnect frm_Connect(strFilePath,m_strItemName,m_strDescription_Conn);
		if (isTestQuit == 0)  //isTestQuit==1表示一次测试过程中连接对话框已经弹出一次，在该测试过程后不需再弹出连接对话框
		{
			isTestQuit = 1;

			frm_Connect.DoModal(); //弹出测试连接对话框
			if (frm_Connect.m_Quit) //如果按下终止按键
			{ 
				OnButtonStop() ;
				UpdateControl(1);
				m_TestButton.EnableWindow(TRUE);
				KillTimer(1);
				KillTimer(2);
				KillTimer(3);
				return 1; 
			}
		}
		/*CString strFilePath= m_strConnectPic;
		strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
			+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\ConnectPic\\"+m_strConnectPic;

		CFrame_TestConnect frm_Connect(strFilePath,m_strItemName,m_strDescription_Conn,this);
		frm_Connect.DoModal();*/
		if(frm_Connect.m_bIgnoreItem)//如果手动取消当前测试项
		{
			CString str1 = m_List_Result.GetItemText(m_intTestLine, 1);//获得当前测试项目

			for(int i = m_intTestLine; i <= m_List_Result.GetItemCount(); i++)//获得当前测试行向下名称相同的行
			{
				if(str1 != m_List_Result.GetItemText(i, 1))
					break;
				m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);//取消勾选
				m_listVCheckState[i] = FALSE;
				m_List_Result.SetItemText(i, 3, "人为取消测试");
			}

			m_bIgnoreCurrentItem = true;
		}

		m_isTestEnd=FALSE;
	}

	else if(wParam==3&&lParam==0)
	{
		m_List_Result.EnsureVisible(m_intTestLine,FALSE);
	}
	
	else if(wParam==4&&lParam==0)
	{
		CString strTestSet=m_List_Result.GetItemText(m_intTestLine,2);
		if ( false == IgnoreDialog)
		{
			CFrame_FAIL frm_Fail(m_strItemName,"不合格",m_strUpper,m_strLower,m_strUnit,m_strResult,strTestSet,m_strStartPath,this);
			frm_Fail.DoModal();
			m_intRetestMark=frm_Fail.m_intControlMark;
			if(m_intRetestMark==1)
			{
				///////////////////////////////初始化状态文件///////////////////////////////////////////
				CFile fileMyFile;
				fileMyFile.Open(m_strStartPath+"\\DeviceHandle.ini",CFile::modeCreate);
				fileMyFile.Close();
				WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停
			}
			else if(m_intRetestMark == 4)
			{
				CString str1 = m_List_Result.GetItemText(m_intTestLine, 1);//获得当前测试项目

				for(int i = m_intTestLine; i <= m_List_Result.GetItemCount(); i++)//获得当前测试行向下名称相同的行
				{
					if(str1 != m_List_Result.GetItemText(i, 1))
						break;
					m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);//取消勾选
					m_listVCheckState[i] = FALSE;
					m_List_Result.SetItemText(i, 3, "人为取消测试");
				}			
			}
		}
	}
	else if(wParam==1&&lParam==1)
	{
		m_List_Result.SetItemState(m_intTestLine,0,LVIS_SELECTED|LVIS_FOCUSED);
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);

		m_isTestEnd=TRUE;
		UpdateControl(1);
		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(TRUE);

		//列表选项显示
		DWORD dwStyle=m_List_Result.GetExtendedStyle();
		m_List_Result.SetExtendedStyle(dwStyle|LVS_EX_CHECKBOXES);	
		for(int i=0;i<m_List_Result.GetItemCount();i++)
		{
			m_List_Result.SetCheck(i,m_listVCheckState[i]);
		}

		//测试结果提示 及保存

		if(m_vTestResult.size()!=0)
		{   
			//获取所有被测试的值结果列表
            //p->m_vTestResult
			//判断该列表中是否含有Fail
            for(int i=0;i<m_vTestResult.size();i++)
			{
				if(m_vTestResult[i].m_strConclusion=="0")
				{   m_strConclusion="Fail";
				    break;
				}
                
			}


			m_TestAddress.SetWindowText(m_TestAddress1);
			//将最终的结果赋值给m_strConclusion
			CTestEnd dlg_TestEnd(m_strConclusion,this);
			dlg_TestEnd.DoModal();

			//结果保存
			int testInfoID;
			if(dlg_TestEnd.m_bSave)
			{
				//搜索判断是否有相同序列号的产品进行过测试
                vector<stucTestInfo> vTestInfotemp; //保存获取的测试信息
				m_bll_TestInfo.SearchTestInfoList(&vTestInfotemp,"SNumber",m_strNumber,"InsName",m_strName);//根据搜索sn和仪器名称获取页面信息			
                if(!vTestInfotemp.empty())  //非空则进行如下操作
				{
					//获取最近的一次结果
					CString m_strConclusionTemp=vTestInfotemp[0].m_strConclusion;//获取校准结论
                    CString m_strTestTimeTemp=vTestInfotemp[0].m_strTestTime;//获取校准时间
					//判断上次计量时间与当前时间差距，如果差距小于15天（不需要太精确），表明是重复计量，则判断是否需要覆盖
                    //上次计量时间转换
					CTime strTimelast(atoi(m_strTestTimeTemp.Mid(0,4)),atoi(m_strTestTimeTemp.Mid(6,2)),atoi(m_strTestTimeTemp.Mid(10,2))
						,atoi(m_strTestTimeTemp.Mid(14,2)),atoi(m_strTestTimeTemp.Mid(18,2)),atoi(m_strTestTimeTemp.Mid(22,2)));
   					//获取当前时间
                	SYSTEMTIME st;
                	GetLocalTime(&st);
                    CTime strTime(st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); 
                    CTimeSpan tspan=strTime-strTimelast;
					long m_timeTemp=tspan.GetDays();
                    if(m_timeTemp<=15)
					{
                    CString strTemp;
					strTemp.Format("该仪器已经经过计量！\r\n \r\n上次计量时间为 %s.\r\n \r\n上次计量结果为 %s.\r\n \r\n是否覆盖之前的结果?",m_strTestTimeTemp,m_strConclusionTemp);
					int messageOut=MessageBox(strTemp,"警告",MB_ICONWARNING|MB_YESNO);
					//messageOut返回值为6 表明为YES,返回值为7表明为NO,
                    if(messageOut==6)
					{  
					   //获取ID值
                       int testInfoIDTemp=vTestInfotemp[0].m_intID;
					   //根据ID获取相关的测试信息
					   vector<stucTestResult>  m_testResultTemp;
					   Ctb_TestResult  m_ctbTestResultTemp;
					   m_ctbTestResultTemp.ReadTestResultList(&m_testResultTemp,testInfoIDTemp);
					   //根据行列值来判断是否需要覆盖
					   for(int j=0;j<m_vTestResult.size();j++)
						   for(int k=0;k<m_testResultTemp.size();k++)
						   {
							 if((m_vTestResult[j].m_strRow==m_testResultTemp[k].m_strRow)&&(m_vTestResult[j].m_strCol==m_testResultTemp[k].m_strCol)) //行与行相等，列与列相等
							 {
								m_testResultTemp[k].m_strResult=m_vTestResult[j].m_strResult;
								m_testResultTemp[k].m_strConclusion=m_vTestResult[j].m_strConclusion;
								break;								
							 }
							 else if(k==m_testResultTemp.size()-1)
							 {
							    m_testResultTemp.push_back(m_vTestResult[j]);	
								break;	
							 }
						   }	
						   //判断更新后的测试结果是否结果合格
                        m_strConclusion="Pass";
				    	for(int i=0;i<m_testResultTemp.size();i++)
						{
				          if(m_testResultTemp[i].m_strConclusion=="0")
						  {   m_strConclusion="Fail";
				              break;
						  }
						}
					    dlg_TestEnd.m_strResult="按校准结果使用";
				    	if(m_strConclusion=="Pass")
						{
					    	dlg_TestEnd.m_strResult="所校项目符合技术要求";
						} 
						//删除已有的数据
						
			        	testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,testInfoIDTemp);  //存入页面信息以及最终结果信息
			        	m_bll_TestResult.AddList(m_testResultTemp,testInfoID);  //存入测试结果信息
					}
				    else if(messageOut==7)  //如果不需要覆盖
					{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //存入页面信息以及最终结果信息
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //存入测试结果信息
					}
					}
					else   //如果计量时间已经超出15天
					{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //存入页面信息以及最终结果信息
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //存入测试结果信息
					}

				}
			    else   //如果第一次计量
				{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //存入页面信息以及最终结果信息
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //存入测试结果信息
				}
			}
                 
		//	}
		}
		
		 m_strNumber = "";
		 m_strNumber_Mana = "";
		 UpdateData(FALSE);
		 m_TestAddress.SetWindowText(m_TestAddress1);
	}
	return 1;
}

BOOL CAutoTest::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CString strTemp=(LPSTR)pCopyDataStruct->lpData;
	strTemp=strTemp.Left(pCopyDataStruct->cbData);
	//UpdateData(FALSE);
	m_List_Result.SetItemText(m_intTestLine,3,m_strResultIndicate);  //显示测试结果
	int intResTimeTick=m_intTimeTick*(m_vItemName.size()-m_intTestSerial)/m_intTestSerial;
	m_strElapseTime=ConvertTickToTime(intResTimeTick);
	if(m_List_Result.GetItemText(m_intTestLine,2)!="Control")
	{
		CString strUpper,strLower;
		char upper[50],lower[50];
		m_List_Result.GetItemText(m_intTestLine,5,upper,50);
		m_List_Result.GetItemText(m_intTestLine,4,lower,50);
		strUpper.Format("%s",upper);
		strLower.Format("%s",lower);
		if(Aduge(strTemp,strUpper,strLower))
		{
			m_List_Result.SetItemText(m_intTestLine,7,"Pass");
		//	if(m_strConclusion=="")
		//		m_strConclusion="Pass";
		}
		else
		{
			m_List_Result.SetItemText(m_intTestLine,7,"Fail");
		//	if(m_strConclusion!="Fail")
		//		m_strConclusion="Fail";
		}		
	}


	
/*	m_List_Result.EnsureVisible(m_intTestLine+1,FALSE);*/

	
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

int intTime=0;
void CAutoTest::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(!m_isTestEnd)
	{
		if(nIDEvent==2)
		{
	    	UpdateListBox(1);
		}
		if(nIDEvent==1)
		{
    		intTime++;
    	    if(intTime>5)
			{
    	       m_List_Result.SetItemState(m_intTestLine,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	   //UpdateData(FALSE);
			}
        	if(intTime>10)
			{
    	      m_List_Result.SetItemState(m_intTestLine,0,LVIS_SELECTED|LVIS_FOCUSED);
	      //UpdateData(FALSE);
    	      intTime=0;
			}
		}
		if(nIDEvent==3)
		{
			m_intTimeTick++;
			m_strTestTime=ConvertTickToTime(m_intTimeTick);
			UpdateData(FALSE);
		}
		
	}
	CDialog::OnTimer(nIDEvent);
}

CString CAutoTest::ConvertTickToTime(int intTickCount)
{
	int intHour=intTickCount/3600;
	int intRes=intTickCount%3600;
	int intMini=intRes/60;
	intRes=intRes%60;
	CString strTestTime("");
    strTestTime.Format("%d 时%d 分%d 秒",intHour,intMini,intRes);
	return strTestTime;	
}

void CAutoTest::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	
	WritePrivateProfileString("RunStatus","TP","1",m_strStartPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停
	m_isStop=TRUE;
	this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);  //中止
	KillTimer(1);
	//intTime=0;
	
}

void CAutoTest::OnItemdblclickListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAutoTest::OnDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   	if(!m_isTestEnd)
	{
		return;
	}
	CPoint pt=GetCurrentMessage()->pt;  //获取当前鼠标消息坐标
	UINT uFlags=0;
	m_List_Result.ScreenToClient(&pt);
	int intLine=m_List_Result.HitTest(pt,&uFlags);
	
    if(uFlags!=LVHT_ONITEMICON)
	{
	   if(uFlags!=LVHT_ONITEMSTATEICON) //判断是否为打钩框
	   {
	     if(m_List_Result.GetCheck(intLine))
			 
		 { m_List_Result.SetCheck(intLine, FALSE);
	       m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
		 }
	    
	     else
		 {	m_List_Result.SetCheck(intLine, TRUE);
            m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
		 }
	   }
	   else
	   {
		   if(m_List_Result.GetCheck(intLine))
		 { m_List_Result.SetCheck(intLine);
	       m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
		 }
	    
	     else
		 {	m_List_Result.SetCheck(intLine, FALSE);
            m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
		 }

	   }

	}
	*pResult = 0;
}

void CAutoTest::UpdateControl(int intStatus)  //刷新控件状态 intStatus:0=初始状态 1=测试前状态 2=测试时状态
{
	if(intStatus==0)
	{
		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);  //开始
		this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);  //中止
		this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE); //暂停
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);  //名称
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(FALSE);  //型号
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(FALSE);  //厂家
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(FALSE);  //编号
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(FALSE); //模版
		this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(FALSE); //测试方案
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(FALSE); //校准日期
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(FALSE); //有效期
		this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(FALSE); //委托方	
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(FALSE); //管理编号
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(FALSE);//温度
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(FALSE); //湿度
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(FALSE); //委托方地址
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(FALSE); //校准地点
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(FALSE); //设备用途
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(TRUE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //获取SN号
        this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(FALSE);  //设备设置
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(FALSE);  //获取连接状态设置

		this->GetParent()->GetDlgItem(10001)->EnableWindow(FALSE);  //自动测试
		this->GetParent()->GetDlgItem(10003)->EnableWindow(FALSE); //手动测试
		this->GetParent()->GetDlgItem(10004)->EnableWindow(FALSE); //维修建议
		this->GetParent()->GetDlgItem(10000)->EnableWindow(TRUE);
		m_strNumber = _T("");
        m_tree_tps.EnableWindow(TRUE);
		
	}
	else if(intStatus==1)
	{
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(TRUE);  //名称
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(TRUE);  //型号
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(TRUE);  //厂家
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(TRUE);  //编号
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(TRUE); //模版
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(TRUE); //校准日期
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(TRUE); //有效期
		this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(TRUE); //委托方
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(TRUE); //管理编号
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(TRUE);//温度
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(TRUE); //湿度
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(TRUE); //委托方地址
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(TRUE); //校准地点
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(TRUE); //设备用途
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(TRUE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //获取SN号
		this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(TRUE);  //设备设置
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(TRUE);  //获取连接状态设置

		//this->GetParent()->GetDlgItem(10003)->EnableWindow(TRUE);  //装备资料
		//this->GetParent()->GetDlgItem(10002)->EnableWindow(TRUE); //手动测试
		//this->GetParent()->GetDlgItem(10004)->EnableWindow(TRUE); //维修建议
		this->GetParent()->GetDlgItem(10000)->EnableWindow(TRUE);

		m_tree_tps.EnableWindow(TRUE);

		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	}
	else if(intStatus==2)
	{
		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);  //名称
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(FALSE);  //型号
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(FALSE);  //厂家
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(FALSE);  //编号
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(FALSE); //模版
		this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(FALSE); //测试方案
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(FALSE); //校准日期
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(FALSE); //有效期
        this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(FALSE); //管理编号
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(FALSE);//温度
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(FALSE); //湿度
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(FALSE); //委托方地址
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(FALSE); //校准地点
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(FALSE); //设备用途
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(FALSE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //获取SN号
		this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(FALSE);  //设备设置
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(FALSE);  //获取连接状态设置
		
		//this->GetParent()->GetDlgItem(10003)->EnableWindow(FALSE); //装备资料
		//this->GetParent()->GetDlgItem(10002)->EnableWindow(FALSE); //手动测试
		//this->GetParent()->GetDlgItem(10004)->EnableWindow(FALSE); //维修建议
		this->GetParent()->GetDlgItem(10000)->EnableWindow(FALSE);

		m_tree_tps.EnableWindow(FALSE);
	}
}

BOOL CAutoTest::Aduge(CString strResult,CString strUpper,CString strLower)
{
	if(strResult=="Invalid")
		return FALSE;
	if(strUpper.IsEmpty()&&strLower.IsEmpty())
	{
		return TRUE;
	}
	else if(!strUpper.IsEmpty()&&strLower.IsEmpty())
	{
		if(strResult.FindOneOf("<")>0)
			return TRUE;
		else if(strResult.FindOneOf(">")>0)
			return FALSE;
		return atof(strResult)<=atof(strUpper);
	}
	else if(!strLower.IsEmpty()&&strUpper.IsEmpty())
	{
		if(strResult.FindOneOf(">")>0)
			return TRUE;
		else if(strResult.FindOneOf("<")>0)
			return FALSE;
		
		return atof(strResult)>=atof(strLower);
	}
	else
	{
		if(atof(strResult)>=atof(strLower)&&atof(strResult)<=atof(strUpper))
			return true;
		else
			return false;
	}
}

void CAutoTest::OnSetfocusEditNumber() 
{
	// TODO: Add your control notification handler code here

	/*
	//Sleep(200);
   // HWND hWnd=::FindWindow(NULL,"屏幕键盘");
	//if(hWnd==NULL)
	//{
	WinExec("osk.exe",SW_SHOWNORMAL);
	HWND hWnd=::FindWindow(NULL,"屏幕键盘");
	//}
	CRect rect,rect_hWnd;
	if(this->GetDlgItem(IDC_EDIT_NUMBER)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_NUMBER)->GetWindowRect(&rect); //获取文本控件位置
	    ::GetWindowRect(hWnd,&rect_hWnd);  //获取键盘程序大小
        ::MoveWindow(hWnd,rect.right,rect.top,rect_hWnd.Width(),rect_hWnd.Height(),TRUE); //定位键盘程序
	}
	else if(this->GetDlgItem(IDC_EDIT_NAME)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_NAME)->GetWindowRect(&rect); //获取文本控件位置
		::GetWindowRect(hWnd,&rect_hWnd);  //获取键盘程序位置
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()/2,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	else if(this->GetDlgItem(IDC_EDIT_MODEL)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_MODEL)->GetWindowRect(&rect); //获取文本控件位置
		::GetWindowRect(hWnd,&rect_hWnd);  //获取键盘程序位置
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()*3/4,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	else if(this->GetDlgItem(IDC_EDIT_MANUFACTORY)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_MANUFACTORY)->GetWindowRect(&rect); //获取文本控件位置
		::GetWindowRect(hWnd,&rect_hWnd);  //获取键盘程序位置
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()*3/4,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	*/

}

void CAutoTest::OnKillfocusEditNumber() 
{
	// TODO: Add your control notification handler code here
	/*
	HWND hWnd=::FindWindow(NULL,"屏幕键盘");
	

	if(this->GetDlgItem(IDC_EDIT_NUMBER)==this->GetFocus()||this->GetDlgItem(IDC_EDIT_NAME)==this->GetFocus()||this->GetDlgItem(IDC_EDIT_MODEL)==this->GetFocus()||this->GetDlgItem(IDC_EDIT_MANUFACTORY)==this->GetFocus())
		return;

	if(hWnd)
	::SendMessage(hWnd,WM_CLOSE,0,0);
	*/
}

HBRUSH CAutoTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}	

	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
		if(pWnd->GetDlgCtrlID()!=IDC_EDIT_NAME && pWnd->GetDlgCtrlID()!=IDC_EDIT_MODEL 
			&&pWnd->GetDlgCtrlID()!=IDC_EDIT_MANUFACTORY && pWnd->GetDlgCtrlID()!=IDC_EDIT_NUMBER
			&&pWnd->GetDlgCtrlID()!=IDC_TREE_TPS&&pWnd->GetDlgCtrlID()!=IDC_EDIT_CUSTOMER
			&&pWnd->GetDlgCtrlID()!=IDC_EDIT_NUMBER_M&&pWnd->GetDlgCtrlID()!=IDC_EDIT_TEMPER
			&&pWnd->GetDlgCtrlID()!=IDC_EDIT_SHI&&pWnd->GetDlgCtrlID()!=IDC_STATIC_PROGRESS
			&&pWnd->GetDlgCtrlID()!=IDC_EDIT_CUSTADD&&pWnd->GetDlgCtrlID()!=IDC_EDIT_LIST
			&&pWnd->GetDlgCtrlID()!=IDC_STATIC_TESTTIME&&pWnd->GetDlgCtrlID()!=IDC_STATIC_ELAPTIME)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255,255,255));	
	    	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		}
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
	//return (HBRUSH)m_brush;
}
//仪器设置
void CAutoTest::OnButtonTestset() 
{
	// TODO: Add your control notification handler code here
	//CString str;   // 存储IP
	//GetDlgItemText(IDC_EDIT_IP, m_IpTest);    //获取IP
	//GetDlgItemText(IDC_CH_EDIT, m_CHTest);    //获取通道
	//GetDlgItemText(IDC_VSG_EDIT2, m_VSGTest);    //获取通道
	//GetDlgItemText(IDC_ROUT_EDIT3, m_ROUTTest);    //获取通道
	m_TestButton.EnableWindow(TRUE);

	//USES_CONVERSION;
	//char* ip1 = T2A(str.GetBuffer(0));
	//str.ReleaseBuffer();

	//
	////char ip1[] = "192.168.100.252";                 //IQP24016
	//IQV_CONNECTION_TYPE connectionType = IQV_CONNECTION_IQ201X;

	//int ret = iqapiInit(true);
	//int ret1 = m_iqApi.ConInit(ip1, connectionType);
	//m_iqApi.SetDefault();
	//if (ret1 == 0)
	//{
	//	MessageBox(_T("IQ库初始化完成!"));
	//}


///////////////////////////////////////////////////////////////
	//int ret3 = m_iqApi.tx->txMode = IQV_INPUT_MOD_DAC_RF;
	//ret3 = m_iqApi.tx->triggerType = IQV_VSG_TRIG_FREE_RUN;

	//ret3 = m_iqApi.tx->vsg[0]->source = IQV_SOURCE_SIGNAL_GENERATOR;   //不加调制时，设置为信号源载波输出

	////端口设置，一个端口不能设置同时接收和发射
	//ret3 = m_iqApi.tx->vsg[0]->port = IQV_PORT_LEFT;                   //将信号发生器端口设置为左边

	//ret3 = m_iqApi.rx->vsa[0]->port = IQV_PORT_RIGHT;                  //将信号分析仪端口设置为右边

	//ret3 = m_iqApi.tx->vsg[0]->rfGainDb = -20;                         //设置RF增益

	////设置发射接收频率，RX和TX频率需要同时设置为一样的数值
	//ret3 = m_iqApi.tx->rfFreqHz = 2414000000;
	////ret3 = iq.tx->freqShiftHz = 0;

	//ret3 = m_iqApi.rx->rfFreqHz = 2414000000;
	////ret3 = iq.rx->freqShiftHz = 0;

	//ret3 = m_iqApi.tx->vsg[0]->sineFreqHz = 0;                         //此处频率设为0，如果不设置默认的会有个偏置

	//ret3 = m_iqApi.tx->vsg[0]->enabled = IQV_RF_ENABLED;               //信号源输出打开

	//ret3 = m_iqApi.SetTxRx();                                          //保存设置，每次设置有修改都要执行这个函数，完成修改
///////////////////////////////////////////////////////////////

	/*CString strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
		+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\"
		+m_strThreadModel+" testConfig.ini";
    CSetInstrAddress dlg_setinstraddress;
	dlg_setinstraddress.strFileIniPath=strFilePath;
	dlg_setinstraddress.DoModal();
	UpdateInsList();*/

}

void CAutoTest::UpdateListView()
{
	try
	{
		TestPointSet stucPointSet;
		vector<TestPointSet> vUUTPoint;
		vector<UUTItemSet> vUUTItem;
		UUTItemSet stucItemSet;
		CString strtemp,strSetString;
		TiXmlElement* pEle=NULL;
		int intline=0;
		m_isTestEnd = TRUE;
		InitListView();	 //初始化m_List_Result表
		m_List_Result.DeleteAllItems(); //删除所有内容
		CString strTem;//保存模板文件名
		int intSelLine=m_cbModule.GetCurSel();
		m_check_All.SetCheck(1);
		m_calibration_All.SetCheck(1);
		m_vKeyList.clear();
		if(intSelLine!=-1)
		{
			this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(TRUE);
			UpdateSoluList("");
	    	m_cbModule.GetLBText(intSelLine,strTem);
	    	m_bll_UUTITem_tem.ReadUUTItemList(m_strThreadKind,m_strThreadModel,strTem,&vUUTItem);//读取ITEMSET顶层KEY/CONTROL的信息
		}
		else
		{
			UpdateControl(0);
			ThrowErr(无测试模版);
		}
		for(int i=0;i<vUUTItem.size();i++)
		{
			if(vUUTItem[i].m_strMarkName=="Control") 
			{
				//m_List_Result.SetItem()
				strtemp.Format("%d",intline+1);
				m_List_Result.InsertItem(intline,strtemp,1);  //插入测试点序号
				m_List_Result.SetCheck(intline,TRUE); //设定为选中状态
				m_List_Result.SetItemText(intline,1,vUUTItem[i].m_strItemName);  //插入项目名称
				m_List_Result.SetItemText(intline,2,"Control");
				m_vKeyList.push_back(vUUTItem[i].m_strKey);		//存储校准项目关键字

				intline++;
			}
			else
			{
				m_bll_UUTPointInfo.ReadUUTPointList(m_bll_UUTITem_tem.m_pNode,vUUTItem[i].m_strKey,&vUUTPoint);
				//根据KEY值找到所有POINT属性给vUUTPoint
				for(int j=0;j<vUUTPoint.size();j++)
				{
					m_vKeyList.push_back(vUUTItem[i].m_strKey);  //存储测试点中测试项目关键字
					strtemp.Format("%d",intline+1);
					m_List_Result.InsertItem(intline,strtemp,1);  //插入测试点序号
					m_List_Result.SetCheck(intline,TRUE); //设定为选中状态
					m_List_Result.SetItemText(intline,1,vUUTItem[i].m_strItemName);  //插入项目名称
					m_List_Result.SetItemData(intline,vUUTPoint[j].m_intID);  //保存测试点ID值
					pEle=m_bll_UUTPointInfo.GetPointNode(vUUTPoint[j].m_intID)->ToElement(); //获取POINT下的ID值
					strSetString=m_bll_UUTPointVar.GetPtVarSetString(pEle); //获取设置内容
					m_List_Result.SetItemText(intline,2,strSetString);
					//		m_List_Result.SetItemText(intline,3,vUUTPoint[j].m_strValue_Ref+vUUTPoint[j].m_strUnit_Ref);
					m_List_Result.SetItemText(intline,4,vUUTPoint[j].m_strLower);
					m_List_Result.SetItemText(intline,5,vUUTPoint[j].m_strUpper);
					m_List_Result.SetItemText(intline,6,vUUTPoint[j].m_strResultUnit);
					intline++;
				}
	    		vUUTPoint.clear();
			}
		}
		vUUTItem.clear();
	}
	catch (char* e)
	{
		MessageBox(e);
	}
}

void CAutoTest::UpdateListBox(int mark) //mark=0 初始化 清空 mark=1 更新
{
	
	if(mark==0)
	{
		m_listBox_Status.ResetContent();
		m_edit_List.SetWindowText("");
		//	m_edit_strList="";
		//	m_strList_Status="";
		//		UpdateData(FALSE);
		return;
	}
	char myShare[255]={0};
	
	try
	{
		m_ShareMem.ReadSharedMemory("ATSSharedMemory",myShare);
		CString s=myShare;	
		if(s.IsEmpty()||s==m_strShare)
			return;		
		if(s.Find(">")<0)
			return;
		//	m_strList_Status+=s+"\r\n";
		//	m_listBox_Status.AddString(s);
		//	m_listBox_Status.SetCurSel(m_listBox_Status.GetCount()-1);
		m_strShare=s;
		CString strValue_ListBox("");
		m_edit_List.GetWindowText(strValue_ListBox);
		if(m_edit_List.GetLineCount()>1000)
		{
			//for(int i=0;i<m_edit_List.GetLineCount()-1;i++)
			strValue_ListBox=strValue_ListBox.Right(strValue_ListBox.GetLength()-strValue_ListBox.Find(_T("\n"))-1);
			m_edit_List.SetWindowText(strValue_ListBox);
			UpdateData(FALSE);
		}
		strcat(myShare,"\r\n");
		//s+="\r\n";
		m_edit_List.SetSel(strValue_ListBox.GetLength(),strValue_ListBox.GetLength());
		m_edit_List.ReplaceSel(myShare);
		m_ShareMem.ReleaseSharedMemory();



	/*
	if(mark==0)
	{
		m_listBox_Status.ResetContent();
		return;
	}
	char myShare[255];
	try
	{
    	m_ShareMem.ReadSharedMemory("ATSSharedMemory",myShare);
    	CString s=myShare;	
		if(s.IsEmpty()||s==m_strShare)
    		return;		
		if(s.Find(">")<0)
			return;
    	m_listBox_Status.AddString(s);
    	m_listBox_Status.SetCurSel(m_listBox_Status.GetCount()-1);
    	m_strShare=s;
	*/		
	}
	catch(CException *)
	{
		MessageBox("Memory Error");
	}

}

BOOL CAutoTest::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	else
	return CDialog::PreTranslateMessage(pMsg);
}
//////////////////////////////////刷新测试模版列表////////////////////////////////////////
void CAutoTest::UpdateModuleList(CString strTemplete)
{	
		vector<CString> vModuleList;
		m_file_UUTInfo.GetModuleList(m_strThreadKind,m_strThreadModel,&vModuleList);  //模版列表
		//CComboBox* pCom_Module=(CComboBox*)(this->GetDlgItem(IDC_COMBO_MODULE));
		while(m_cbModule.DeleteString(0)!=CB_ERR);   //删除模版组合框中的字符串

		for(int i=0;i<vModuleList.size();i++)
		{
			m_cbModule.AddString(vModuleList[i]);
		}

		int intIndex=-1;
		CString strTemp;
		for(int i=0;i<m_cbModule.GetCount();i++)
		{
			m_cbModule.GetLBText(i,strTemp);
			if(strTemp==strTemplete)
			{
				intIndex=i;
				break;
			}
		}
		if(intIndex==-1&&m_cbModule.GetCount()>0)
		{
			m_cbModule.SetCurSel(0);
			return;
		}
		m_cbModule.SetCurSel(intIndex);	

}
/////////////////////////刷新解决方案列表////////////////////////////////////
void CAutoTest::UpdateSoluList(CString strSoluName)
{
	int intCbSolution=m_cb_Solution.GetCount();
	for(int i=0;i<intCbSolution;i++)
	{
		m_cb_Solution.DeleteString(0);
	}
	vector<CString> vSolutionList;
	int intSel=m_cbModule.GetCurSel();
	if(intSel<0)
	{
		return;
	}
	
	m_cbModule.GetLBText(intSel,m_strTem);
	m_bll_UUTITem_tem.ReadSolutionList(m_strThreadKind,m_strThreadModel,m_strTem,&vSolutionList);
	int intSolSize=0;
	for(int i=0;i<vSolutionList.size();i++)
	{
		m_cb_Solution.AddString(vSolutionList[i]);
		intSolSize++;
	}
	if(intSolSize==0)
	{
        m_cb_Solution.SetCurSel(-1);
	}
	else
	{
		m_cb_Solution.SetCurSel(0);
	}
	UpdateInsList();
	m_strNumber = _T("");  //序列号清空
	UpdateData(FALSE);
	
}

void CAutoTest::OnSelchangeComboModule() 
{
	// TODO: Add your control notification handler code here
	UpdateListView();
}

void CAutoTest::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	CString strPauseText;
	this->GetDlgItem(IDC_BUTTON_PAUSE)->GetWindowText(strPauseText);  //读取Pause按钮的文本框
	if(strPauseText=="暂停")
	{
		WritePrivateProfileString("RunStatus","TP","2",m_strStartPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText("继续");
	}
	else
	{
		WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0运行 1=终止 2=暂停
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText("暂停");
	}

}

void CAutoTest::OnButtonReport() 
{
	// TODO: Add your control notification handler code here
	//Ctb_TestInfo ctbInfo;
	//stucTestInfo testInfo;
	//testInfo.m_intID=2;
	//testInfo.m_strCustomer="444";
	//testInfo.m_strAddress="555";
	//testInfo.m_strModel="666";
	//testInfo.m_strFactory="777";
    //	ctbInfo.Add(testInfo);
    //	testInfo.m_intID=ctbInfo.ReadTestInfo(&testInfo,5);
	//MessageBox(testInfo.m_strCustomer);
	CReport frm_Report(this);

	frm_Report.DoModal();
}

int CAutoTest::SaveTestInfoToAccess(CString strResult,CString strConclusion,int m_intIDTemp)  //返回记录ID
{
	stucTestInfo testInfo;
	//Ctb_TestInfo tb_testInfo;
	testInfo.m_strCustomer=m_strCustomer;
	testInfo.m_strAddress=m_strAddress_Customer;
	testInfo.m_strInsName=m_strName;
	testInfo.m_strModel=m_strModel;
	testInfo.m_strFactory=m_strManu;
	testInfo.m_strSNumber=m_strNumber;
	testInfo.m_strInsUse.Format("%d",m_intInsUse); //设备用途 0 1选择
	testInfo.m_strNumber_Mana=m_strNumber_Mana;
	testInfo.m_strCalDate=m_DateTime.Format(_T("%Y-%m-%d"));
	testInfo.m_strDueCalDate="1"; //需要处理
	testInfo.m_strResult=strResult; //需要根据测试结果的选择进行处理
	testInfo.m_strConclusion=strConclusion; // Pass Fail选择
	testInfo.m_strCalStation.Format("%d",m_intTestStation); //校准地点 0 1选择
	testInfo.m_strTemperature=m_strTemperature;
	testInfo.m_strHumidity=m_strHumity;
	testInfo.m_strTester=""; //需要处理

	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strTime.Format("%4d年%2d月%2d日%2d时%2d分%2d秒",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	testInfo.m_strTestTime=strTime; //需要处理
	m_cbModule.GetLBText(m_cbModule.GetCurSel(),testInfo.m_strTemplete);
	testInfo.m_strTemplete="DataInfo\\UUTTestInfo\\"+m_strThreadKind
		+"\\TPS\\"+m_strThreadModel+"\\Document\\"+testInfo.m_strTemplete;

	if(m_intIDTemp==0)
	{
      testInfo.m_intID=m_bll_TestInfo.GenerateID();
	  m_bll_TestInfo.Add(testInfo);
	}
	else
	{
        //删除已有的数据
		testInfo.m_intID=m_intIDTemp;
		m_bll_TestInfo.UpdateTestInfo(testInfo);
		m_bll_TestResult.DeleteResult(m_intIDTemp);
	}
   return testInfo.m_intID;
}

int CAutoTest::SaveTestResultToAccess(vector<stucTestResult> vTestResult,int intTestInfoID)
{//单点复测后使用， 将有结果的测试数据进行保存
	/*
// 	vector<stucTestResult> vTestResult;
// 	int intTestInfoID;
	Ctb_TestResult testResult;

	for (int i=0;i<vTestResult.size();i++)
	{
		vTestResult[i].m_intTestInfoID=intTestInfoID;
		testResult.Add(vTestResult[i]);
	}
	*/
	return 1;
}

void CAutoTest::OnCheckAll() 
{
	// TODO: Add your control notification handler code here
	if(m_check_All.GetCheck()==1)
	{
        m_calibration_All.SetCheck(1);
		for (int i=0;i<m_List_Result.GetItemCount();i++)
		{
			m_List_Result.SetCheck(i);
			m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
			
		}
	}
	else
	{   
		m_calibration_All.SetCheck(0);
		for (int i=0;i<m_List_Result.GetItemCount();i++)
		{
			m_List_Result.SetCheck(i,FALSE);
			m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
			
		}
	}	
}

void CAutoTest::OnButtonReTest() 
{
	// TODO: Add your control notification handler code here
	CFrame_TestConnect frm_Connect(this);
	frm_Connect.DoModal();

	char *szBuffer=new char[255];
	
	CString strTemp=szBuffer;
	int len= strTemp.GetLength();
}

void CAutoTest::OnSelchangeComboSolution() 
{

	//strInsName=m_iniOpe.GetKeyValue()
	UpdateInsList();	
}

void CAutoTest::UpdateInsList()
{
	// TODO: Add your control notification handler code here
	int intSel=m_cb_Solution.GetCurSel();
	m_list_Ins.DeleteAllItems();
	while(m_list_Ins.DeleteColumn(0));
	if(intSel<0)
	{
		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
		return;
	}
	//////////////////初始化列表////////////////////////////////////////////////////////
	this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(TRUE); 
	this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
	RECT rRect;
	m_list_Ins.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);	
	m_list_Ins.InsertColumn(0,"序号",LVCFMT_LEFT,width/9);
	m_list_Ins.InsertColumn(1,"设备名称",LVCFMT_LEFT,width*3/13);
	m_list_Ins.InsertColumn(2,"设备型号",LVCFMT_LEFT,width*3/13);
	m_list_Ins.InsertColumn(3,"物理地址",LVCFMT_LEFT,width*3/11);
	m_list_Ins.InsertColumn(4,"逻辑名称",LVCFMT_LEFT,width/6);
	
	
	m_cb_Solution.GetLBText(intSel,m_strSoluName);
	CString strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
		+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\"
		+m_strThreadModel+" testConfig.ini";
	m_iniOpe.SetINIPth(strFilePath); //设置配置文件路径
	CStringArray strArr_Sec;
	m_iniOpe.GetSections(strArr_Sec); 
	CString strInsName,strInsModel,strInsAddress,strLogicName;
	CString strSerial;
	for(int i=0;i<strArr_Sec.GetSize();i++)
	{
		strSerial.Format("%d",i+1);
		strInsName=m_iniOpe.GetKeyValue(strArr_Sec[i],"InsName");
		strInsModel=m_iniOpe.GetKeyValue(strArr_Sec[i],"Model");
		strInsAddress=m_iniOpe.GetKeyValue(strArr_Sec[i],"Address");
		strLogicName=strArr_Sec[i];
		m_list_Ins.InsertItem(i,strSerial);
		m_list_Ins.SetItemText(i,1,strInsName);
		m_list_Ins.SetItemText(i,2,strInsModel);
		m_list_Ins.SetItemText(i,3,strInsAddress);
		m_list_Ins.SetItemText(i,4,strLogicName);
	}

}

void CAutoTest::StringToArray(CString strInput,CString key,vector<CString>* stringArray)
{
	CString strTemp;
//	CString strInput;
//	vector<CString>* stringArray;
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

void CAutoTest::OnStaticNum() 
{
	// TODO: Add your control notification handler code here
	
}
//获取被测设备的SN号
void CAutoTest::OnButtonGetsn() 
{
	// TODO: Add your control notification handler code here
    this->GetDlgItem(IDC_BUTTON_GETSN)->SetWindowText("读取中");
	CStringArray strArr_Sec;
    CString strInsAddress,funcname;
	char result[255] = {""};
	char errorout[2] = {""};
	int k;
	char j = 0;
	//获取所有字段值
	m_iniOpe.GetSections(strArr_Sec);
	for(int i=0;i<strArr_Sec.GetSize();i++)
	{
		//获取strArr_Sec字段下的ReadSN键值
		funcname=m_iniOpe.GetKeyValue(strArr_Sec[i],"ReadSN");
		if( funcname.IsEmpty())
		{
			if("UUT" == strArr_Sec[i])
				MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
		}
		else 
		{
			k=funcname.Find(">");
			strInsAddress=m_iniOpe.GetKeyValue(strArr_Sec[i],"Address");
			CString strdllPath=funcname.Left(k-1); //截取驱动名称
			strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
				m_iniOpe.GetKeyValue(strArr_Sec[i],"DriverName")+"\\"+strdllPath;
			//MessageBox(strdllPath);
			//funcname.Right(funcname.GetLength()-i);
			//获取dll地址
			CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-k-1),result,errorout);
			if((CString) errorout=="1")
			{
				MessageBox("读取S/N异常!\r\n请检查仪器地址设置是否有问题!\r\n请检查仪器通信线缆连接是否有问题!");
			}
			else if((CString) result=="0")
			{
				MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
			}
			else    //执行成功
			{
				if("UUT" == strArr_Sec[i])
				{
					m_strNumber=(CString) result;
					this->GetDlgItem(IDC_EDIT_NUMBER)->SetWindowText(m_strNumber);
					//UpdateData(FALSE);
				}
				else
				{
					StandardNum[j] =result;
					StandardName[j] = m_iniOpe.GetKeyValue(strArr_Sec[i],"InsName");
					j++;
				}
			}
		}
	}


	//funcname=m_iniOpe.GetKeyValue("UUT","ReadSN");
 //   if(funcname.IsEmpty())
	//{
	//	MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
	//}
	//else
	//{
	//	i=funcname.Find(">");
	//	strInsAddress=m_iniOpe.GetKeyValue("UUT","Address");
	//	CString strdllPath=funcname.Left(i-1); //截取驱动名称
	//	strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
	//				m_iniOpe.GetKeyValue("UUT","DriverName")+"\\"+strdllPath;
	//	//MessageBox(strdllPath);
	//	//funcname.Right(funcname.GetLength()-i);
	//	//获取dll地址
	//	CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-i-1),result,errorout);
	//	if((CString) errorout=="1")
	//	{
	//		MessageBox("读取S/N异常!\r\n请检查仪器地址设置是否有问题!\r\n请检查仪器通信线缆连接是否有问题!");
	//	}
	//	else if((CString) result=="0")
	//	{
	//	 MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
	//	}
	//	else 
	//	{
	//		m_strNumber=(CString) result;
	//		this->GetDlgItem(IDC_EDIT_NUMBER)->SetWindowText(m_strNumber);
	//		//UpdateData(FALSE);
	//	}
	//
	//}


	//CString strInsAddress1,funcname1;
	//char result1[255],errorout1[2];
	//int j;
	//funcname1=m_iniOpe.GetKeyValue("DigSource","ReadSN");
	//if(funcname1.IsEmpty())
	//{
	//	MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
	//}
	//else
	//{
	//	j=funcname1.Find(">");
	//	strInsAddress=m_iniOpe.GetKeyValue("DigSource","Address");
	//	CString strdllPath=funcname1.Left(j-1); //截取驱动名称
	//	strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
	//		m_iniOpe.GetKeyValue("DigSource","DriverName")+"\\"+strdllPath ;
	//	//MessageBox(strdllPath);
	//	//funcname.Right(funcname.GetLength()-i);
	//	//获取dll地址
	//	CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-i-1),result,errorout);
	//	StandardNum = result ;
	//	StandardName = m_iniOpe.GetKeyValue("DigSource","InsName");
	//	if((CString) errorout=="1")
	//	{
	//		MessageBox("读取S/N异常!\r\n请检查仪器地址设置是否有问题!\r\n请检查仪器通信线缆连接是否有问题!");
	//	}
	//	else if((CString) result=="0")
	//	{
	//		MessageBox("很抱歉，该仪器不能读取S/N号!请手工录入!");
	//	}
	//	else 
	//	{
	//		m_strNumber=(CString) result;
	//		//this->GetDlgItem(IDC_EDIT_NUMBER)->SetWindowText(m_strNumber);
	//		//UpdateData(FALSE);
	//	}

	//}

	this->GetDlgItem(IDC_BUTTON_GETSN)->SetWindowText("编号");
}

void CAutoTest::OnButtonInstrstate() 
{
	// TODO: Add your control notification handler code here
	//该按钮变字
	this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->SetWindowText("状态获取中");
	CStringArray strArr_Sec,strArr_Key;
    CString strInsAddress,funcname,strdllPath;
	char handleout[50];
	char errorout[2];

	//获取所有字段值
	m_iniOpe.GetSections(strArr_Sec);
	for(int i=0;i<strArr_Sec.GetSize();i++)
	{
		//获取所有键值
		m_iniOpe.GetKeys(strArr_Key,strArr_Sec[i]);
        //搜索键值最后四位是Init的键， 其对应的一定是初始化函数，如果找不到则不做处理
		for(int j=0;j<strArr_Key.GetSize();j++)
		{
           if(strArr_Key[j].Right(4)=="Init")
		   {
		     //获取对应的驱动以及函数名称
		    funcname=m_iniOpe.GetKeyValue(strArr_Sec[i],strArr_Key[j]);
			int k=funcname.Find(">"); // >左边的是驱动名称，右边的是函数名称
			//funcname.Left(k-1)   左边的 驱动名称
            //funcname.Right(funcname.GetLength()-k-1)   右边的  函数名称
            strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
		        m_iniOpe.GetKeyValue(strArr_Sec[i],"DriverName")+"\\"+funcname.Left(k-1);
			strInsAddress=m_iniOpe.GetKeyValue(strArr_Sec[i],"Address");
            CLoadTP::MyLoadConnect(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-k-1),"0",handleout,errorout);
			//MessageBox((CString)errorout);
            if((CString)errorout=="0")
			{
				//如果返回值为0表明初始化成功，连接上设备
				m_list_Ins.SetItem(i, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
				m_TestButton.EnableWindow(true);
				m_GetSN.EnableWindow(true);
			}
			else
			{
   				m_list_Ins.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
			}
            strArr_Key.RemoveAll();
		    break;
		   }
		}
	}
	this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->SetWindowText("设备连接状态");
}

void CAutoTest::OnCalibrationAll() 
{
	// TODO: Add your control notification handler code here
	//获取校准CONTROL项

	if(m_calibration_All.GetCheck()==1)
	{
		for (int i=0;i<m_List_Result.GetItemCount();i++)
		{
		    if(m_List_Result.GetItemText(i,2)=="Control")	
			{
				m_List_Result.SetCheck(i);
				m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
			}
			
		}
	}
	else
	{
    	for (int i=0;i<m_List_Result.GetItemCount();i++)
		{
			if(m_List_Result.GetItemText(i,2)=="Control")	
			{
				m_List_Result.SetCheck(i,FALSE);
				m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
			}
			
		}
	}
}

void CAutoTest::OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(!m_isTestEnd)
	{
		return;
	}
	CPoint pt=GetCurrentMessage()->pt;  //获取当前鼠标消息坐标
	UINT uFlags=0;
	m_List_Result.ScreenToClient(&pt);
	int intLine=m_List_Result.HitTest(pt,&uFlags);

	if(uFlags==LVHT_ONITEMICON)
	{   
		if(m_List_Result.GetCheck(intLine))
		{ 
		  m_List_Result.SetCheck(intLine, FALSE);
	      m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
	 
		}
	    
    	else
		{	
			m_List_Result.SetCheck(intLine);
            m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
		}
	}
	if(uFlags==LVHT_ONITEMSTATEICON)
	{   
		if(m_List_Result.GetCheck(intLine))
		{ 
		  m_List_Result.SetCheck(intLine);
	      m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);
	 
		}
	    
    	else
		{	
			m_List_Result.SetCheck(intLine,false);
            m_List_Result.SetItem(intLine, 0, LVIF_IMAGE, NULL, 1, LVIS_SELECTED, LVIS_SELECTED , 0);
		}
 	}

	*pResult = 0;
}
