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
CString m_IpTest="TCPIP0::192.168.100.254::hislip0::INSTR";          //������
CString m_CHTest = "1A";     //ͨ��
CString m_VSGTest = "1";     //ͨ��
CString m_ROUTTest = "1";     //ͨ��
iqapiHndl m_iqApi;         //IQȫ�ֱ���
unsigned char isTestQuit = 0 ; 
extern bool IgnoreDialog;  //���Ա�������־
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
	//���������ӿ�·������ʼ·��+"DataInfo\\UUTTestInfo\\"+�豸���ͣ����磺�������ñ�+"\\InsPortDriver\\"+�豸���ͣ����磺�������ñ�+"_Engine.dll"
	CString strdllPath=p->m_pathOpe.GetStartPath()
		+"DataInfo\\UUTTestInfo\\"+p->m_strThreadKind+"\\InsPortDriver\\"+p->m_strThreadKind+"_Engine.dll";   //���������ӿ�·��
	CString strLuaFilePath="";
	CString strUUTCom="COM1"; //���Դ���ΪCOM1
	CString strInputVar="";
	CString strTestConfigFilePath="";//���������ļ�·��
	int intTestSerial=-1;  //������ţ���û��ʼ���߲�����Ϻ���-1
	int intTestMode=0;
	char testResult[100];
	CString strListValuePre="";
	CString strConnPic_Pre="";
	int i=0;
	
	CString strItemName="";
	UUTItemSet stuItemSet;
	
	
	UUTItemVarSet stuItemInfo; //������Ŀ��Ϣ

	TiXmlNode* pNode=NULL;
	char errBuff[128];
	
	COPYDATASTRUCT cpd;
	TiXmlElement* pEle=NULL;
	UUTInfoSet stucUUTInfo;
	TestPointSet stucPointSet;
	//int count=0;
	stucTestResult sTestResult;
	CString  strKey; //��Ŀ�ؼ���

	BOOL isRetest=FALSE; //����

	vector<CString> vTestResultKey;  //���Խ����ʶ��
	vector<CString> vTestResult; //���Խ��
	BOOL bTestResult; //���Խ����Ƿ�ϸ�
	p->m_bIgnoreCurrentItem = false;

	p->m_bll_UUTInfo.ReadUUTBasicInfo(p->m_strThreadKind,p->m_strThreadModel,&stucUUTInfo);
	//���������ļ�·������ʼ·��+"DataInfo\\UUTTestInfo\\"+�豸���ͣ����磺�������ñ�+"\\TPS\\"+ģ�����ƣ����磺Agilent 34401A��+"\\Solution\\"+S_5700+"\\TestConfig\\"+ģ�����ƣ����磺Agilent 34401A��+" testConfig.ini"
	strTestConfigFilePath=p->m_pathOpe.GetStartPath()
		+"DataInfo\\UUTTestInfo\\"+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel
		+"\\Solution\\"+p->m_strSoluName+"\\TestConfig\\"+p->m_strThreadModel+" testConfig.ini";
	//��ò����ѡ���У�������
	int intCheckItemCount=p->m_vItemName.size();

	int isStop=FALSE;
	p->m_intPotCount=p->m_List_Result.GetItemCount();
	Sleep(100);   //�̹߳���100ms

	
	for(i=0;i<p->m_intPotCount;i++)  //ÿһ��ѭ������һ�����Ե�
	{
		p->m_intTestLine=i; //��i������
	//	p->m_isPotCheck=p->m_List_Result.GetCheck(i);
		p->m_isPotCheck=p->m_listVCheckState[i];   //��ø���ѡ�е�״̬
		if(p->m_isPotCheck)  //������ѡ��״̬Ϊ�棬ѡ�оͲ���
		{
			p->m_intTestSerial++;  //���������
			intTestSerial++;        //��ʼ��Ϊ-1����˳��Ź涨Ϊ0��
			try
			{
				p->m_strItemName=p->m_List_Result.GetItemText(i,1);   //��ò�����Ŀ����
				strItemName=p->m_strItemName; //ת����CString ��ʽ
 				if(p->m_intTestSerial<intCheckItemCount && strItemName!=p->m_vItemName[p->m_intTestSerial])
 				//�������к� < ��ѡ������  &&  ��õĲ�����Ŀ����!=ѡ�к���Ӧ����
				{
 					intTestSerial=-1;   //��˳���
 				}
				if(p->m_intTestSerial==intCheckItemCount)  //���ԶԻ���������к� == ��ѡ������ 
				{
 					intTestSerial=-1;  //��˳���
				}

				p->SendMessage(WM_MYUPDATEDATA,3,0); //ȷ����ѡ�е��У���ǿɼ��ģ������ѡ�е��У�����ڿؼ������ڣ��ͻᷢ��������
                Sleep(100);
				
				if (strKey != p->m_vKeyList[i])
				{
					strKey=p->m_vKeyList[i];  //��ȡ��ǰ�еĲ�����Ŀ�ؼ��֣�����ʱ������Ŀ�ؼ��֣����Ҳ�����Lua
					isTestQuit = 0;
				}
			
			//	strItemName=p->m_strItemName; 
				//��xml�ļ��ж�ȡ������Ŀ��Ϣ������ȡ����Ŀ�ڵ㣬������stuItemInfo
		//		p->m_bll_UUTItem.GetItemInfo(p->m_strThreadKind,p->m_strThreadModel,strItemName,&stuItemInfo); //��TestConfig�ļ����µ�XML�ļ���ȡ������Ŀ������Ϣ
				p->m_bll_UUTItem.GetItemInfo(p->m_strThreadKind,p->m_strThreadModel,p->m_strSoluName,strKey, &stuItemInfo);
				strLuaFilePath=stuItemInfo.m_strProgName; //lua�ű��ļ���·��
				p->m_strConnectPic=stuItemInfo.m_strConnectPic;  //��������ͼ
				p->m_strDescription_Conn=stuItemInfo.m_strConnectDescription; //������ʾ

				//Lua�������Ӹջ����Ϣ��ȡ��
				//��ȡLua�����·������ʼ��ַ+ "DataInfo\\UUTTestInfo\\" + װ�����ͣ����磺�������ñ�+ "\\TPS\\" + ģ�����ƣ����磺Agilent 34401A��+ ����������ƣ����磺S_5700_33521�� + "\\TestItem\\" + Lua��������;
				strLuaFilePath=p->m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
					+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel+"\\Solution\\"+p->m_strSoluName
					+"\\TestItem\\"+strLuaFilePath; //��ȡLua�����·��
                p->m_strTestMark=p->m_List_Result.GetItemText(i,2); 

				//����ͼ��·�� ���ԶԻ�����Խ���ͼ��������ʾ�Ӹջ����Ϣ�л��
				CString strFilePath=p-> m_strConnectPic;
				strFilePath=p->m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
					+p->m_strThreadKind+"\\TPS\\"+p->m_strThreadModel+"\\Solution\\"+p->m_strSoluName+"\\TestConfig\\ConnectPic\\"+p->m_strConnectPic;

				if (isTestQuit == 0 && p->m_strConnectPic!=strConnPic_Pre)  //isTestQuit==1��ʾһ�β��Թ��������ӶԻ����Ѿ�����һ�Σ��ڸò��Թ��̺����ٵ������ӶԻ���
				{
					isTestQuit = 1;
					CFrame_TestConnect frm_Connect(strFilePath,p->m_strItemName,p->m_strDescription_Conn);//����ͼ��·����������Ŀ�����ƣ�������ʾ
					frm_Connect.DoModal();     //�������ӶԻ���
					if (frm_Connect.m_Quit)  //����������ӶԻ������ֹ����
					{
						p->OnButtonStop() ;
						p->UpdateControl(1);
						p->m_TestButton.EnableWindow(TRUE); //���԰�������
						p->UpdateListView();  //���²��Խ���б��
						/*KillTimer(p->m_hWnd,1);
						KillTimer(p->m_hWnd,2);
						KillTimer(p->m_hWnd,3);*/
						return 1; 
					}
				}
				///////////////////////////������ʾ�Ի���///////////////////////////////////////////////
				//	Sleep(100);
				if(p->m_intTestSerial==1)  //�Ƿ��Ǹտ�ʼ����
				{
					p->SendMessage(WM_MYUPDATEDATA,1,0); //1������ʾ�Ի���
					if(p->m_bIgnoreCurrentItem)   //���Ե�ǰ�������־λ
					{
						strConnPic_Pre = "";
						p->m_bIgnoreCurrentItem = false;
						continue;
					}
					else
						strConnPic_Pre=p->m_strConnectPic;   //��������ͼ
				}
				else if(p->m_intTestSerial<=intCheckItemCount && strItemName!=p->m_vItemName[p->m_intTestSerial-2])
				//�Ǹտ�ʼ��ѡ��������֮���Ҳ�����Ŀ����ǰһ��������Ŀ��ͬ
				{
					if(p->m_strConnectPic!=strConnPic_Pre) //�������ͼ�����뵯��ʱ����ͼ����ͬ���򵯳�
					{
			    		Sleep(100);
						p->SendMessage(WM_MYUPDATEDATA,1,0); //1������ʾ�Ի���
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
					

				if(p->m_strTestMark!="Control") //��xml�ļ��л�ȡ������Ŀ�ؼ��ֲ��ǡ�Control��
				{
					p->m_intPointID=p->m_List_Result.GetItemData(i);
					//������ĿID��ò��Ե�ڵ�
					pNode=p->m_bll_UUTPointInfo.GetPointNode(p->m_strThreadKind,p->m_strThreadModel,p->m_strTem,
						strKey,p->m_intPointID);
					if(pNode==NULL)
					{
						ThrowErr(�Ҳ������Ե�);
					}
					//��ȡ�ڵ���Ϣ
					p->m_bll_UUTPointInfo.ReadPointInfo(pNode->Parent()->Parent(),p->m_intPointID,&stucPointSet);
					//��ò��������ַ���
					strInputVar=p->m_bll_UUTPointVar.GetPtVarTestString(pNode->ToElement());
		    		strInputVar+=";Result="+stucPointSet.m_strResultUnit;
				}
				else
				{
					
				}

				//������������޼���λ�����ԶԻ���
				p->m_strUpper=stucPointSet.m_strUpper;
				p->m_strLower=stucPointSet.m_strLower;
				p->m_strUnit=stucPointSet.m_strResultUnit;	
				int intTestSerial_Temp=intTestSerial;  //��ʱ�洢����˳���
				do 
				{
					//����TP�����Գ���
					CLoadTP::MyLoadTP(strdllPath,strLuaFilePath,strUUTCom,strInputVar,strTestConfigFilePath,intTestSerial,intTestMode,testResult,m_IpTest,m_CHTest,m_VSGTest,m_ROUTTest);
					p->m_strResult=testResult;

					vTestResultKey.clear();  //��ղ��Խ���ؼ���
					vTestResult.clear();  //��ղ��Խ������
					p->m_strResultIndicate="";  //������ʾ�Ĳ��Խ��
					if(stucPointSet.m_strResultMark.Find(",")==-1||p->m_strResult.Find(",")==-1)
					{
						p->m_strResultIndicate=p->m_strResult;  //ֻ��һ�����Խ��ֱ����ʾʵ�ʲ��Խ��
					}
					else
					{
					    p->StringToArray(stucPointSet.m_strResultMark,",",&vTestResultKey); //ʹ�á������ָ���������ڲ��Խ������������
						p->StringToArray(p->m_strResult,",",&vTestResult); //ʹ�á������ָ�ʵ�ʲ��Խ������������
						for(int k=0;k<vTestResultKey.size();k++)
						{
							p->m_strResultIndicate+=vTestResultKey[k];
							p->m_strResultIndicate+="="+vTestResult[k]+",";
						}
						p->m_strResultIndicate=p->m_strResultIndicate.Left(p->m_strResultIndicate.GetLength()-1);
					}	
					//�������淢����Ϣ
					cpd.dwData=0;
					cpd.cbData=50;
					cpd.lpData=(void*)testResult;//������ָ��,��Ӧ�ó��򴫵������õ�.���Խ�����ݸ������̣߳��ڲ��Խ���б���ʾ
					p->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);  //��ʾ���Խ��
		    		Sleep(300);
					//////////////////////�ж��Ƿ�ϸ�������ϸ����ô�������ʾ��////////////////////////////////////////////////////

	    		    if(p->m_strTestMark!="Control") //������Ŀ��־λΪControl
					{
		    			bTestResult=p->Aduge(testResult,stucPointSet.m_strUpper,stucPointSet.m_strLower);
		    			if(bTestResult==FALSE)   //���Խ��Ϊ���ϸ�
						{
				    		p->SendMessage(WM_MYUPDATEDATA,4,0); //�������Խ�����ϸ�Ի���
				    		Sleep(100);
				    		if(p->m_intRetestMark==1)
							{
		    		    		//intTestSerial=-1;
					    		isRetest=TRUE;  //�ز�
							}
				    		else if(p->m_intRetestMark==2)
							{
						    	isRetest=FALSE;
							}
					    	else if(p->m_intRetestMark==3)
							{
						    	isRetest=FALSE;
						    	p->m_isStop=TRUE;   //��ֹ
							}
							else if(p->m_intRetestMark==4)
							{
								isRetest = FALSE;
								strConnPic_Pre = "";  //����
							}
						}
					
			    		else
						{
					    	isRetest=FALSE;
						}
					}

				} while (isRetest);
				intTestSerial=intTestSerial_Temp; //��ԭ����˳��ţ���Ҫ��TP�����й�
								

				p->SendMessage(WM_MYUPDATEDATA,2,p->m_intTestSerial*100/intCheckItemCount);  ///���²��Խ���
				Sleep(100);  //�̹߳���100ms
                
				///////////////////////////���Խ����Ϣ��ʱ����///////////////////////////////////////////////
		    	
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
					sTestResult.m_strConclusion=bTestResult?"1":"0"; //���Խ���Ƿ�ϸ� 1=�ϸ� 0=���ϸ�
					sTestResult.m_strItemKey=strKey;
		    		p->m_vTestResult.push_back(sTestResult);   //�����Խ���������ݿ���
				}
			}
			catch (CMemoryException* e)
			{
				e->GetErrorMessage(errBuff,10);
				MessageBox(p->GetSafeHwnd(),errBuff,"����",0);	
			}
			catch (char* e)
			{
				MessageBox(p->GetSafeHwnd(),e,"����",0);
			}
		}   //end������ѡ��״̬Ϊ�棬ѡ�оͲ���
		if(p->m_isStop)  // �ж��Ƿ�����ֹ���Ա�־λ
		{
			break;
		}
	}
	p->SendMessage(WM_MYUPDATEDATA,1,1); //���Խ������,1������ֹ
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
	InitTreeList(); //��ʼ�����ؼ�
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
	UpdateControl(0); //��ʼ�����ֿؼ�

	//m_tree_tps.ModifyStyle(0,TVS_SHOWSELALWAYS|TVS_FULLROWSELECT);

	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//��ʼ��֤����ҳ��Ϣ
void CAutoTest::UpdateFirstPaper()
{
	m_DateTime=CTime::GetCurrentTime();
	m_intInsUse=0;
	m_intTestStation=0;
	m_strTemperature="23";
	m_strHumity="60";
	UpdateData(FALSE);

	
}

////////////////////////////��ʼ�����б�////////////////////////////////////////
void CAutoTest::InitTreeList()
{
	//ͼ���б�
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
	//��������
	try
	{
		vector<UUTKindList> vKindList;
		vector<FileInfo> vFileInfo;
		m_xml_Kind.GetKindList(&vKindList);    //�豸�����б�
		for(int i=0;i<vKindList.size();i++)
		{
			HTREEITEM hTreeItem=m_tree_tps.InsertItem(vKindList[i].m_strKindName,2,2);//�����ؼ���������б�
			
			m_tree_tps.SetItemData(hTreeItem,vKindList[i].m_intUINumber);
			m_file_UUTInfo.GetUUTList(vKindList[i].m_strKindName,&vFileInfo);  //�ͺ��б�
			
			for(int j=0;j<vFileInfo.size();j++)
			{
				//�����ؼ�����ͺ��б�
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

//��ʼ���б�ؼ�
void CAutoTest::InitListView()
{
	//m_List_Result.GetHeaderCtrl()->GetItemCount();
	while(m_List_Result.DeleteColumn(0));

	RECT rRect;
	m_List_Result.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);	
	m_List_Result.InsertColumn(0,"���",LVCFMT_LEFT,width/8);
	m_List_Result.InsertColumn(1,"������Ŀ",LVCFMT_LEFT,width*2/11);
	m_List_Result.InsertColumn(2,"��������",LVCFMT_LEFT,width*3/14);
	m_List_Result.InsertColumn(3,"���Խ��",LVCFMT_LEFT,width/9);
	m_List_Result.InsertColumn(4,"����ֵ",LVCFMT_LEFT,width/11);
	m_List_Result.InsertColumn(5,"����ֵ",LVCFMT_LEFT,width/11);
	m_List_Result.InsertColumn(6,"��λ",LVCFMT_LEFT,width/12);
	m_List_Result.InsertColumn(7,"����",LVCFMT_LEFT,width/12);
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
	Invalidate(); //�ػ�
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
	CPoint pt=GetCurrentMessage()->pt;  //��ȡ��ǰ�����Ϣ����
	m_tree_tps.ScreenToClient(&pt);   //ת��Ϊ���ؼ��еĿͻ�����
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_tps.HitTest(pt,&uFlags); //�������
	if((hItem!=NULL)&&(TVHT_ONITEM&uFlags)) //��������Ŀ��Ч
	{
		if(m_tree_tps.GetParentItem(hItem)!=NULL&&m_tree_tps.GetParentItem(m_tree_tps.GetParentItem(hItem))==NULL)
		{
			//���ѡ�еڶ��㣬���ͺŲ�
			m_strThreadModel=m_tree_tps.GetItemText(hItem);
			m_strThreadKind=m_tree_tps.GetItemText(m_tree_tps.GetParentItem(hItem));	
			UpdateControl(1); //���İ�ť״̬Ϊ����ǰ״̬
			if(hItem!=m_hItem_Pre) //��ѡ���ͺ�����һ�β�ͬ��ˢ�²�����Ϣ
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
			UpdateControl(0); //���û��ѡ�в��Է����,����Ϊ���ɲ���״̬
		}
		m_hItem_Pre=hItem;
	}
	m_TestButton.EnableWindow(FALSE);
	*pResult = 0;
}

////////////////////////////ˢ�»�����Ϣ��/////////////////////////////////////////
void CAutoTest::UpdateTestInfo()
{
	try
	{
    	UUTInfoSet stucUUTInfo;
    	m_bll_UUTInfo.ReadUUTBasicInfo(m_strThreadKind,m_strThreadModel,&stucUUTInfo); //������������ñ��ͺţ���Agilent 34401A
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
	
	isTestQuit = 0 ;  //��Ҫ�������ӿ�
	m_progress_test.SetPos(0);  //�������ָ�Ϊ��ʼ״̬
	UpdateData();
	if(m_strNumber.IsEmpty())
	{
		MessageBox("�豸��Ų���Ϊ��");
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
		MessageBox("��ѡ�������Ŀ");
		return;
	}
	///////////////////////////////��ʼ��״̬�ļ�///////////////////////////////////////////
	CFile fileMyFile;
	fileMyFile.Open(m_strStartPath+"\\DeviceHandle.ini",CFile::modeCreate);
	fileMyFile.Close();
	WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0���� 1=��ֹ 2=��ͣ
	
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

		//��������ͼ��·��
		CString strFilePath= m_strConnectPic;
		strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
			+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\ConnectPic\\"+m_strConnectPic;
		CFrame_TestConnect frm_Connect(strFilePath,m_strItemName,m_strDescription_Conn);
		if (isTestQuit == 0)  //isTestQuit==1��ʾһ�β��Թ��������ӶԻ����Ѿ�����һ�Σ��ڸò��Թ��̺����ٵ������ӶԻ���
		{
			isTestQuit = 1;

			frm_Connect.DoModal(); //�����������ӶԻ���
			if (frm_Connect.m_Quit) //���������ֹ����
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
		if(frm_Connect.m_bIgnoreItem)//����ֶ�ȡ����ǰ������
		{
			CString str1 = m_List_Result.GetItemText(m_intTestLine, 1);//��õ�ǰ������Ŀ

			for(int i = m_intTestLine; i <= m_List_Result.GetItemCount(); i++)//��õ�ǰ����������������ͬ����
			{
				if(str1 != m_List_Result.GetItemText(i, 1))
					break;
				m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);//ȡ����ѡ
				m_listVCheckState[i] = FALSE;
				m_List_Result.SetItemText(i, 3, "��Ϊȡ������");
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
			CFrame_FAIL frm_Fail(m_strItemName,"���ϸ�",m_strUpper,m_strLower,m_strUnit,m_strResult,strTestSet,m_strStartPath,this);
			frm_Fail.DoModal();
			m_intRetestMark=frm_Fail.m_intControlMark;
			if(m_intRetestMark==1)
			{
				///////////////////////////////��ʼ��״̬�ļ�///////////////////////////////////////////
				CFile fileMyFile;
				fileMyFile.Open(m_strStartPath+"\\DeviceHandle.ini",CFile::modeCreate);
				fileMyFile.Close();
				WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0���� 1=��ֹ 2=��ͣ
			}
			else if(m_intRetestMark == 4)
			{
				CString str1 = m_List_Result.GetItemText(m_intTestLine, 1);//��õ�ǰ������Ŀ

				for(int i = m_intTestLine; i <= m_List_Result.GetItemCount(); i++)//��õ�ǰ����������������ͬ����
				{
					if(str1 != m_List_Result.GetItemText(i, 1))
						break;
					m_List_Result.SetItem(i, 0, LVIF_IMAGE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED , 0);//ȡ����ѡ
					m_listVCheckState[i] = FALSE;
					m_List_Result.SetItemText(i, 3, "��Ϊȡ������");
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

		//�б�ѡ����ʾ
		DWORD dwStyle=m_List_Result.GetExtendedStyle();
		m_List_Result.SetExtendedStyle(dwStyle|LVS_EX_CHECKBOXES);	
		for(int i=0;i<m_List_Result.GetItemCount();i++)
		{
			m_List_Result.SetCheck(i,m_listVCheckState[i]);
		}

		//���Խ����ʾ ������

		if(m_vTestResult.size()!=0)
		{   
			//��ȡ���б����Ե�ֵ����б�
            //p->m_vTestResult
			//�жϸ��б����Ƿ���Fail
            for(int i=0;i<m_vTestResult.size();i++)
			{
				if(m_vTestResult[i].m_strConclusion=="0")
				{   m_strConclusion="Fail";
				    break;
				}
                
			}


			m_TestAddress.SetWindowText(m_TestAddress1);
			//�����յĽ����ֵ��m_strConclusion
			CTestEnd dlg_TestEnd(m_strConclusion,this);
			dlg_TestEnd.DoModal();

			//�������
			int testInfoID;
			if(dlg_TestEnd.m_bSave)
			{
				//�����ж��Ƿ�����ͬ���кŵĲ�Ʒ���й�����
                vector<stucTestInfo> vTestInfotemp; //�����ȡ�Ĳ�����Ϣ
				m_bll_TestInfo.SearchTestInfoList(&vTestInfotemp,"SNumber",m_strNumber,"InsName",m_strName);//��������sn���������ƻ�ȡҳ����Ϣ			
                if(!vTestInfotemp.empty())  //�ǿ���������²���
				{
					//��ȡ�����һ�ν��
					CString m_strConclusionTemp=vTestInfotemp[0].m_strConclusion;//��ȡУ׼����
                    CString m_strTestTimeTemp=vTestInfotemp[0].m_strTestTime;//��ȡУ׼ʱ��
					//�ж��ϴμ���ʱ���뵱ǰʱ���࣬������С��15�죨����Ҫ̫��ȷ�����������ظ����������ж��Ƿ���Ҫ����
                    //�ϴμ���ʱ��ת��
					CTime strTimelast(atoi(m_strTestTimeTemp.Mid(0,4)),atoi(m_strTestTimeTemp.Mid(6,2)),atoi(m_strTestTimeTemp.Mid(10,2))
						,atoi(m_strTestTimeTemp.Mid(14,2)),atoi(m_strTestTimeTemp.Mid(18,2)),atoi(m_strTestTimeTemp.Mid(22,2)));
   					//��ȡ��ǰʱ��
                	SYSTEMTIME st;
                	GetLocalTime(&st);
                    CTime strTime(st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); 
                    CTimeSpan tspan=strTime-strTimelast;
					long m_timeTemp=tspan.GetDays();
                    if(m_timeTemp<=15)
					{
                    CString strTemp;
					strTemp.Format("�������Ѿ�����������\r\n \r\n�ϴμ���ʱ��Ϊ %s.\r\n \r\n�ϴμ������Ϊ %s.\r\n \r\n�Ƿ񸲸�֮ǰ�Ľ��?",m_strTestTimeTemp,m_strConclusionTemp);
					int messageOut=MessageBox(strTemp,"����",MB_ICONWARNING|MB_YESNO);
					//messageOut����ֵΪ6 ����ΪYES,����ֵΪ7����ΪNO,
                    if(messageOut==6)
					{  
					   //��ȡIDֵ
                       int testInfoIDTemp=vTestInfotemp[0].m_intID;
					   //����ID��ȡ��صĲ�����Ϣ
					   vector<stucTestResult>  m_testResultTemp;
					   Ctb_TestResult  m_ctbTestResultTemp;
					   m_ctbTestResultTemp.ReadTestResultList(&m_testResultTemp,testInfoIDTemp);
					   //��������ֵ���ж��Ƿ���Ҫ����
					   for(int j=0;j<m_vTestResult.size();j++)
						   for(int k=0;k<m_testResultTemp.size();k++)
						   {
							 if((m_vTestResult[j].m_strRow==m_testResultTemp[k].m_strRow)&&(m_vTestResult[j].m_strCol==m_testResultTemp[k].m_strCol)) //��������ȣ����������
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
						   //�жϸ��º�Ĳ��Խ���Ƿ����ϸ�
                        m_strConclusion="Pass";
				    	for(int i=0;i<m_testResultTemp.size();i++)
						{
				          if(m_testResultTemp[i].m_strConclusion=="0")
						  {   m_strConclusion="Fail";
				              break;
						  }
						}
					    dlg_TestEnd.m_strResult="��У׼���ʹ��";
				    	if(m_strConclusion=="Pass")
						{
					    	dlg_TestEnd.m_strResult="��У��Ŀ���ϼ���Ҫ��";
						} 
						//ɾ�����е�����
						
			        	testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,testInfoIDTemp);  //����ҳ����Ϣ�Լ����ս����Ϣ
			        	m_bll_TestResult.AddList(m_testResultTemp,testInfoID);  //������Խ����Ϣ
					}
				    else if(messageOut==7)  //�������Ҫ����
					{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //����ҳ����Ϣ�Լ����ս����Ϣ
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //������Խ����Ϣ
					}
					}
					else   //�������ʱ���Ѿ�����15��
					{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //����ҳ����Ϣ�Լ����ս����Ϣ
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //������Խ����Ϣ
					}

				}
			    else   //�����һ�μ���
				{
				    testInfoID=SaveTestInfoToAccess(dlg_TestEnd.m_strResult,m_strConclusion,0);  //����ҳ����Ϣ�Լ����ս����Ϣ
			    	m_bll_TestResult.AddList(m_vTestResult,testInfoID);  //������Խ����Ϣ
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
	m_List_Result.SetItemText(m_intTestLine,3,m_strResultIndicate);  //��ʾ���Խ��
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
    strTestTime.Format("%d ʱ%d ��%d ��",intHour,intMini,intRes);
	return strTestTime;	
}

void CAutoTest::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	
	WritePrivateProfileString("RunStatus","TP","1",m_strStartPath+"\\DeviceHandle.ini");//0���� 1=��ֹ 2=��ͣ
	m_isStop=TRUE;
	this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);  //��ֹ
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
	CPoint pt=GetCurrentMessage()->pt;  //��ȡ��ǰ�����Ϣ����
	UINT uFlags=0;
	m_List_Result.ScreenToClient(&pt);
	int intLine=m_List_Result.HitTest(pt,&uFlags);
	
    if(uFlags!=LVHT_ONITEMICON)
	{
	   if(uFlags!=LVHT_ONITEMSTATEICON) //�ж��Ƿ�Ϊ�򹳿�
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

void CAutoTest::UpdateControl(int intStatus)  //ˢ�¿ؼ�״̬ intStatus:0=��ʼ״̬ 1=����ǰ״̬ 2=����ʱ״̬
{
	if(intStatus==0)
	{
		this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);  //��ʼ
		this->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);  //��ֹ
		this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE); //��ͣ
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);  //����
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(FALSE);  //�ͺ�
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(FALSE);  //����
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(FALSE);  //���
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(FALSE); //ģ��
		this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(FALSE); //���Է���
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(FALSE); //У׼����
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(FALSE); //��Ч��
		this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(FALSE); //ί�з�	
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(FALSE); //������
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(FALSE);//�¶�
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(FALSE); //ʪ��
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(FALSE); //ί�з���ַ
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(FALSE); //У׼�ص�
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(FALSE); //�豸��;
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(TRUE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //��ȡSN��
        this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(FALSE);  //�豸����
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(FALSE);  //��ȡ����״̬����

		this->GetParent()->GetDlgItem(10001)->EnableWindow(FALSE);  //�Զ�����
		this->GetParent()->GetDlgItem(10003)->EnableWindow(FALSE); //�ֶ�����
		this->GetParent()->GetDlgItem(10004)->EnableWindow(FALSE); //ά�޽���
		this->GetParent()->GetDlgItem(10000)->EnableWindow(TRUE);
		m_strNumber = _T("");
        m_tree_tps.EnableWindow(TRUE);
		
	}
	else if(intStatus==1)
	{
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(TRUE);  //����
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(TRUE);  //�ͺ�
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(TRUE);  //����
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(TRUE);  //���
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(TRUE); //ģ��
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(TRUE); //У׼����
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(TRUE); //��Ч��
		this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(TRUE); //ί�з�
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(TRUE); //������
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(TRUE);//�¶�
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(TRUE); //ʪ��
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(TRUE); //ί�з���ַ
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(TRUE); //У׼�ص�
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(TRUE); //�豸��;
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(TRUE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //��ȡSN��
		this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(TRUE);  //�豸����
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(TRUE);  //��ȡ����״̬����

		//this->GetParent()->GetDlgItem(10003)->EnableWindow(TRUE);  //װ������
		//this->GetParent()->GetDlgItem(10002)->EnableWindow(TRUE); //�ֶ�����
		//this->GetParent()->GetDlgItem(10004)->EnableWindow(TRUE); //ά�޽���
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
		this->GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);  //����
		this->GetDlgItem(IDC_EDIT_MODEL)->EnableWindow(FALSE);  //�ͺ�
		this->GetDlgItem(IDC_EDIT_MANUFACTORY)->EnableWindow(FALSE);  //����
		this->GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(FALSE);  //���
		this->GetDlgItem(IDC_COMBO_MODULE)->EnableWindow(FALSE); //ģ��
		this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(FALSE); //���Է���
		this->GetDlgItem(IDC_DATETIME_CAL)->EnableWindow(FALSE); //У׼����
		this->GetDlgItem(IDC_COMBO_DUETIME)->EnableWindow(FALSE); //��Ч��
        this->GetDlgItem(IDC_EDIT_CUSTOMER)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_EDIT_NUMBER_M)->EnableWindow(FALSE); //������
		this->GetDlgItem(IDC_EDIT_TEMPER)->EnableWindow(FALSE);//�¶�
		this->GetDlgItem(IDC_EDIT_SHI)->EnableWindow(FALSE); //ʪ��
		this->GetDlgItem(IDC_EDIT_CUSTADD)->EnableWindow(FALSE); //ί�з���ַ
		this->GetDlgItem(IDC_COMBO_TESTSTATION)->EnableWindow(FALSE); //У׼�ص�
		this->GetDlgItem(IDC_COMBO_INSUSE)->EnableWindow(FALSE); //�豸��;
		this->GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(FALSE);

		this->GetDlgItem(IDC_BUTTON_GETSN)->EnableWindow(FALSE);  //��ȡSN��
		this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(FALSE);  //�豸����
		this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->EnableWindow(FALSE);  //��ȡ����״̬����
		
		//this->GetParent()->GetDlgItem(10003)->EnableWindow(FALSE); //װ������
		//this->GetParent()->GetDlgItem(10002)->EnableWindow(FALSE); //�ֶ�����
		//this->GetParent()->GetDlgItem(10004)->EnableWindow(FALSE); //ά�޽���
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
   // HWND hWnd=::FindWindow(NULL,"��Ļ����");
	//if(hWnd==NULL)
	//{
	WinExec("osk.exe",SW_SHOWNORMAL);
	HWND hWnd=::FindWindow(NULL,"��Ļ����");
	//}
	CRect rect,rect_hWnd;
	if(this->GetDlgItem(IDC_EDIT_NUMBER)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_NUMBER)->GetWindowRect(&rect); //��ȡ�ı��ؼ�λ��
	    ::GetWindowRect(hWnd,&rect_hWnd);  //��ȡ���̳����С
        ::MoveWindow(hWnd,rect.right,rect.top,rect_hWnd.Width(),rect_hWnd.Height(),TRUE); //��λ���̳���
	}
	else if(this->GetDlgItem(IDC_EDIT_NAME)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_NAME)->GetWindowRect(&rect); //��ȡ�ı��ؼ�λ��
		::GetWindowRect(hWnd,&rect_hWnd);  //��ȡ���̳���λ��
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()/2,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	else if(this->GetDlgItem(IDC_EDIT_MODEL)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_MODEL)->GetWindowRect(&rect); //��ȡ�ı��ؼ�λ��
		::GetWindowRect(hWnd,&rect_hWnd);  //��ȡ���̳���λ��
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()*3/4,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	else if(this->GetDlgItem(IDC_EDIT_MANUFACTORY)==this->GetFocus())
	{
		GetDlgItem(IDC_EDIT_MANUFACTORY)->GetWindowRect(&rect); //��ȡ�ı��ؼ�λ��
		::GetWindowRect(hWnd,&rect_hWnd);  //��ȡ���̳���λ��
		::MoveWindow(hWnd,rect.right,rect.top-rect_hWnd.Height()*3/4,rect_hWnd.Width(),rect_hWnd.Height(),TRUE);
	}
	*/

}

void CAutoTest::OnKillfocusEditNumber() 
{
	// TODO: Add your control notification handler code here
	/*
	HWND hWnd=::FindWindow(NULL,"��Ļ����");
	

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
	{ //���ľ�̬��͸��������ɫΪ��ɫ
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
//��������
void CAutoTest::OnButtonTestset() 
{
	// TODO: Add your control notification handler code here
	//CString str;   // �洢IP
	//GetDlgItemText(IDC_EDIT_IP, m_IpTest);    //��ȡIP
	//GetDlgItemText(IDC_CH_EDIT, m_CHTest);    //��ȡͨ��
	//GetDlgItemText(IDC_VSG_EDIT2, m_VSGTest);    //��ȡͨ��
	//GetDlgItemText(IDC_ROUT_EDIT3, m_ROUTTest);    //��ȡͨ��
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
	//	MessageBox(_T("IQ���ʼ�����!"));
	//}


///////////////////////////////////////////////////////////////
	//int ret3 = m_iqApi.tx->txMode = IQV_INPUT_MOD_DAC_RF;
	//ret3 = m_iqApi.tx->triggerType = IQV_VSG_TRIG_FREE_RUN;

	//ret3 = m_iqApi.tx->vsg[0]->source = IQV_SOURCE_SIGNAL_GENERATOR;   //���ӵ���ʱ������Ϊ�ź�Դ�ز����

	////�˿����ã�һ���˿ڲ�������ͬʱ���պͷ���
	//ret3 = m_iqApi.tx->vsg[0]->port = IQV_PORT_LEFT;                   //���źŷ������˿�����Ϊ���

	//ret3 = m_iqApi.rx->vsa[0]->port = IQV_PORT_RIGHT;                  //���źŷ����Ƕ˿�����Ϊ�ұ�

	//ret3 = m_iqApi.tx->vsg[0]->rfGainDb = -20;                         //����RF����

	////���÷������Ƶ�ʣ�RX��TXƵ����Ҫͬʱ����Ϊһ������ֵ
	//ret3 = m_iqApi.tx->rfFreqHz = 2414000000;
	////ret3 = iq.tx->freqShiftHz = 0;

	//ret3 = m_iqApi.rx->rfFreqHz = 2414000000;
	////ret3 = iq.rx->freqShiftHz = 0;

	//ret3 = m_iqApi.tx->vsg[0]->sineFreqHz = 0;                         //�˴�Ƶ����Ϊ0�����������Ĭ�ϵĻ��и�ƫ��

	//ret3 = m_iqApi.tx->vsg[0]->enabled = IQV_RF_ENABLED;               //�ź�Դ�����

	//ret3 = m_iqApi.SetTxRx();                                          //�������ã�ÿ���������޸Ķ�Ҫִ���������������޸�
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
		InitListView();	 //��ʼ��m_List_Result��
		m_List_Result.DeleteAllItems(); //ɾ����������
		CString strTem;//����ģ���ļ���
		int intSelLine=m_cbModule.GetCurSel();
		m_check_All.SetCheck(1);
		m_calibration_All.SetCheck(1);
		m_vKeyList.clear();
		if(intSelLine!=-1)
		{
			this->GetDlgItem(IDC_COMBO_SOLUTION)->EnableWindow(TRUE);
			UpdateSoluList("");
	    	m_cbModule.GetLBText(intSelLine,strTem);
	    	m_bll_UUTITem_tem.ReadUUTItemList(m_strThreadKind,m_strThreadModel,strTem,&vUUTItem);//��ȡITEMSET����KEY/CONTROL����Ϣ
		}
		else
		{
			UpdateControl(0);
			ThrowErr(�޲���ģ��);
		}
		for(int i=0;i<vUUTItem.size();i++)
		{
			if(vUUTItem[i].m_strMarkName=="Control") 
			{
				//m_List_Result.SetItem()
				strtemp.Format("%d",intline+1);
				m_List_Result.InsertItem(intline,strtemp,1);  //������Ե����
				m_List_Result.SetCheck(intline,TRUE); //�趨Ϊѡ��״̬
				m_List_Result.SetItemText(intline,1,vUUTItem[i].m_strItemName);  //������Ŀ����
				m_List_Result.SetItemText(intline,2,"Control");
				m_vKeyList.push_back(vUUTItem[i].m_strKey);		//�洢У׼��Ŀ�ؼ���

				intline++;
			}
			else
			{
				m_bll_UUTPointInfo.ReadUUTPointList(m_bll_UUTITem_tem.m_pNode,vUUTItem[i].m_strKey,&vUUTPoint);
				//����KEYֵ�ҵ�����POINT���Ը�vUUTPoint
				for(int j=0;j<vUUTPoint.size();j++)
				{
					m_vKeyList.push_back(vUUTItem[i].m_strKey);  //�洢���Ե��в�����Ŀ�ؼ���
					strtemp.Format("%d",intline+1);
					m_List_Result.InsertItem(intline,strtemp,1);  //������Ե����
					m_List_Result.SetCheck(intline,TRUE); //�趨Ϊѡ��״̬
					m_List_Result.SetItemText(intline,1,vUUTItem[i].m_strItemName);  //������Ŀ����
					m_List_Result.SetItemData(intline,vUUTPoint[j].m_intID);  //������Ե�IDֵ
					pEle=m_bll_UUTPointInfo.GetPointNode(vUUTPoint[j].m_intID)->ToElement(); //��ȡPOINT�µ�IDֵ
					strSetString=m_bll_UUTPointVar.GetPtVarSetString(pEle); //��ȡ��������
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

void CAutoTest::UpdateListBox(int mark) //mark=0 ��ʼ�� ��� mark=1 ����
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
//////////////////////////////////ˢ�²���ģ���б�////////////////////////////////////////
void CAutoTest::UpdateModuleList(CString strTemplete)
{	
		vector<CString> vModuleList;
		m_file_UUTInfo.GetModuleList(m_strThreadKind,m_strThreadModel,&vModuleList);  //ģ���б�
		//CComboBox* pCom_Module=(CComboBox*)(this->GetDlgItem(IDC_COMBO_MODULE));
		while(m_cbModule.DeleteString(0)!=CB_ERR);   //ɾ��ģ����Ͽ��е��ַ���

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
/////////////////////////ˢ�½�������б�////////////////////////////////////
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
	m_strNumber = _T("");  //���к����
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
	this->GetDlgItem(IDC_BUTTON_PAUSE)->GetWindowText(strPauseText);  //��ȡPause��ť���ı���
	if(strPauseText=="��ͣ")
	{
		WritePrivateProfileString("RunStatus","TP","2",m_strStartPath+"\\DeviceHandle.ini");//0���� 1=��ֹ 2=��ͣ
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText("����");
	}
	else
	{
		WritePrivateProfileString("RunStatus","TP","0",m_strStartPath+"\\DeviceHandle.ini");//0���� 1=��ֹ 2=��ͣ
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText("��ͣ");
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

int CAutoTest::SaveTestInfoToAccess(CString strResult,CString strConclusion,int m_intIDTemp)  //���ؼ�¼ID
{
	stucTestInfo testInfo;
	//Ctb_TestInfo tb_testInfo;
	testInfo.m_strCustomer=m_strCustomer;
	testInfo.m_strAddress=m_strAddress_Customer;
	testInfo.m_strInsName=m_strName;
	testInfo.m_strModel=m_strModel;
	testInfo.m_strFactory=m_strManu;
	testInfo.m_strSNumber=m_strNumber;
	testInfo.m_strInsUse.Format("%d",m_intInsUse); //�豸��; 0 1ѡ��
	testInfo.m_strNumber_Mana=m_strNumber_Mana;
	testInfo.m_strCalDate=m_DateTime.Format(_T("%Y-%m-%d"));
	testInfo.m_strDueCalDate="1"; //��Ҫ����
	testInfo.m_strResult=strResult; //��Ҫ���ݲ��Խ����ѡ����д���
	testInfo.m_strConclusion=strConclusion; // Pass Failѡ��
	testInfo.m_strCalStation.Format("%d",m_intTestStation); //У׼�ص� 0 1ѡ��
	testInfo.m_strTemperature=m_strTemperature;
	testInfo.m_strHumidity=m_strHumity;
	testInfo.m_strTester=""; //��Ҫ����

	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strTime.Format("%4d��%2d��%2d��%2dʱ%2d��%2d��",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	testInfo.m_strTestTime=strTime; //��Ҫ����
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
        //ɾ�����е�����
		testInfo.m_intID=m_intIDTemp;
		m_bll_TestInfo.UpdateTestInfo(testInfo);
		m_bll_TestResult.DeleteResult(m_intIDTemp);
	}
   return testInfo.m_intID;
}

int CAutoTest::SaveTestResultToAccess(vector<stucTestResult> vTestResult,int intTestInfoID)
{//���㸴���ʹ�ã� ���н���Ĳ������ݽ��б���
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
	//////////////////��ʼ���б�////////////////////////////////////////////////////////
	this->GetDlgItem(IDC_BUTTON_TESTSET)->EnableWindow(TRUE); 
	this->GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
	RECT rRect;
	m_list_Ins.GetClientRect(&rRect);
	int width=(rRect.right-rRect.left);	
	m_list_Ins.InsertColumn(0,"���",LVCFMT_LEFT,width/9);
	m_list_Ins.InsertColumn(1,"�豸����",LVCFMT_LEFT,width*3/13);
	m_list_Ins.InsertColumn(2,"�豸�ͺ�",LVCFMT_LEFT,width*3/13);
	m_list_Ins.InsertColumn(3,"�����ַ",LVCFMT_LEFT,width*3/11);
	m_list_Ins.InsertColumn(4,"�߼�����",LVCFMT_LEFT,width/6);
	
	
	m_cb_Solution.GetLBText(intSel,m_strSoluName);
	CString strFilePath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"
		+m_strThreadKind+"\\TPS\\"+m_strThreadModel+"\\Solution\\"+m_strSoluName+"\\TestConfig\\"
		+m_strThreadModel+" testConfig.ini";
	m_iniOpe.SetINIPth(strFilePath); //���������ļ�·��
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
		strTemp=strInput.Left(intPos);  //��ȡ�ָ��ַ���
		strInput=strInput.Right(strInput.GetLength()-intPos-1);
		stringArray->push_back(strTemp);
	}
    stringArray->push_back(strInput);
}

void CAutoTest::OnStaticNum() 
{
	// TODO: Add your control notification handler code here
	
}
//��ȡ�����豸��SN��
void CAutoTest::OnButtonGetsn() 
{
	// TODO: Add your control notification handler code here
    this->GetDlgItem(IDC_BUTTON_GETSN)->SetWindowText("��ȡ��");
	CStringArray strArr_Sec;
    CString strInsAddress,funcname;
	char result[255] = {""};
	char errorout[2] = {""};
	int k;
	char j = 0;
	//��ȡ�����ֶ�ֵ
	m_iniOpe.GetSections(strArr_Sec);
	for(int i=0;i<strArr_Sec.GetSize();i++)
	{
		//��ȡstrArr_Sec�ֶ��µ�ReadSN��ֵ
		funcname=m_iniOpe.GetKeyValue(strArr_Sec[i],"ReadSN");
		if( funcname.IsEmpty())
		{
			if("UUT" == strArr_Sec[i])
				MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
		}
		else 
		{
			k=funcname.Find(">");
			strInsAddress=m_iniOpe.GetKeyValue(strArr_Sec[i],"Address");
			CString strdllPath=funcname.Left(k-1); //��ȡ��������
			strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
				m_iniOpe.GetKeyValue(strArr_Sec[i],"DriverName")+"\\"+strdllPath;
			//MessageBox(strdllPath);
			//funcname.Right(funcname.GetLength()-i);
			//��ȡdll��ַ
			CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-k-1),result,errorout);
			if((CString) errorout=="1")
			{
				MessageBox("��ȡS/N�쳣!\r\n����������ַ�����Ƿ�������!\r\n��������ͨ�����������Ƿ�������!");
			}
			else if((CString) result=="0")
			{
				MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
			}
			else    //ִ�гɹ�
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
	//	MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
	//}
	//else
	//{
	//	i=funcname.Find(">");
	//	strInsAddress=m_iniOpe.GetKeyValue("UUT","Address");
	//	CString strdllPath=funcname.Left(i-1); //��ȡ��������
	//	strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
	//				m_iniOpe.GetKeyValue("UUT","DriverName")+"\\"+strdllPath;
	//	//MessageBox(strdllPath);
	//	//funcname.Right(funcname.GetLength()-i);
	//	//��ȡdll��ַ
	//	CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-i-1),result,errorout);
	//	if((CString) errorout=="1")
	//	{
	//		MessageBox("��ȡS/N�쳣!\r\n����������ַ�����Ƿ�������!\r\n��������ͨ�����������Ƿ�������!");
	//	}
	//	else if((CString) result=="0")
	//	{
	//	 MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
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
	//	MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
	//}
	//else
	//{
	//	j=funcname1.Find(">");
	//	strInsAddress=m_iniOpe.GetKeyValue("DigSource","Address");
	//	CString strdllPath=funcname1.Left(j-1); //��ȡ��������
	//	strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
	//		m_iniOpe.GetKeyValue("DigSource","DriverName")+"\\"+strdllPath ;
	//	//MessageBox(strdllPath);
	//	//funcname.Right(funcname.GetLength()-i);
	//	//��ȡdll��ַ
	//	CLoadTP::MyLoadSN(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-i-1),result,errorout);
	//	StandardNum = result ;
	//	StandardName = m_iniOpe.GetKeyValue("DigSource","InsName");
	//	if((CString) errorout=="1")
	//	{
	//		MessageBox("��ȡS/N�쳣!\r\n����������ַ�����Ƿ�������!\r\n��������ͨ�����������Ƿ�������!");
	//	}
	//	else if((CString) result=="0")
	//	{
	//		MessageBox("�ܱ�Ǹ�����������ܶ�ȡS/N��!���ֹ�¼��!");
	//	}
	//	else 
	//	{
	//		m_strNumber=(CString) result;
	//		//this->GetDlgItem(IDC_EDIT_NUMBER)->SetWindowText(m_strNumber);
	//		//UpdateData(FALSE);
	//	}

	//}

	this->GetDlgItem(IDC_BUTTON_GETSN)->SetWindowText("���");
}

void CAutoTest::OnButtonInstrstate() 
{
	// TODO: Add your control notification handler code here
	//�ð�ť����
	this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->SetWindowText("״̬��ȡ��");
	CStringArray strArr_Sec,strArr_Key;
    CString strInsAddress,funcname,strdllPath;
	char handleout[50];
	char errorout[2];

	//��ȡ�����ֶ�ֵ
	m_iniOpe.GetSections(strArr_Sec);
	for(int i=0;i<strArr_Sec.GetSize();i++)
	{
		//��ȡ���м�ֵ
		m_iniOpe.GetKeys(strArr_Key,strArr_Sec[i]);
        //������ֵ�����λ��Init�ļ��� ���Ӧ��һ���ǳ�ʼ������������Ҳ�����������
		for(int j=0;j<strArr_Key.GetSize();j++)
		{
           if(strArr_Key[j].Right(4)=="Init")
		   {
		     //��ȡ��Ӧ�������Լ���������
		    funcname=m_iniOpe.GetKeyValue(strArr_Sec[i],strArr_Key[j]);
			int k=funcname.Find(">"); // >��ߵ����������ƣ��ұߵ��Ǻ�������
			//funcname.Left(k-1)   ��ߵ� ��������
            //funcname.Right(funcname.GetLength()-k-1)   �ұߵ�  ��������
            strdllPath=m_pathOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+
		        m_iniOpe.GetKeyValue(strArr_Sec[i],"DriverName")+"\\"+funcname.Left(k-1);
			strInsAddress=m_iniOpe.GetKeyValue(strArr_Sec[i],"Address");
            CLoadTP::MyLoadConnect(strInsAddress,strdllPath,funcname.Right(funcname.GetLength()-k-1),"0",handleout,errorout);
			//MessageBox((CString)errorout);
            if((CString)errorout=="0")
			{
				//�������ֵΪ0������ʼ���ɹ����������豸
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
	this->GetDlgItem(IDC_BUTTON_INSTRSTATE)->SetWindowText("�豸����״̬");
}

void CAutoTest::OnCalibrationAll() 
{
	// TODO: Add your control notification handler code here
	//��ȡУ׼CONTROL��

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
	CPoint pt=GetCurrentMessage()->pt;  //��ȡ��ǰ�����Ϣ����
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
