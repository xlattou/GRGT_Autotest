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
		MessageBox("��ѡ�������Ϣ","��ʾ");
		return;
	}
	int nItem=m_ListV_TestInfo.GetNextSelectedItem(pos);
	int intSelID=m_ListV_TestInfo.GetItemData(nItem);

	//m_strStatus="��������֤�飬���Ժ�...";
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��������֤�飬���Ժ�...");

	GetDlgItem(IDC_BUTTON_SEARCHINFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RETURN)->EnableWindow(FALSE);
	GenerateReport(intSelID);   //���ɱ���
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
	m_ListV_TestInfo.InsertColumn(0,"���",LVCFMT_LEFT,width/13);
	m_ListV_TestInfo.InsertColumn(1,"����ʱ��",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(2,"ί�з�",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(3,"ί�з���ַ",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(4,"�豸����",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(5,"�豸�ͺ�",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(6,"���쳧",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(7,"�豸���",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(8,"�豸��;",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(9,"������",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(10,"У׼����",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(11,"��Ч��",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(12,"У׼���",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(13,"У׼����",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(14,"У׼�ص�",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(15,"�¶�",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(16,"ʪ��",LVCFMT_LEFT,width/4);
	m_ListV_TestInfo.InsertColumn(17,"������Ա",LVCFMT_LEFT,width/4);

}

void CReport::GenerateReport(int nTestInfoID)
{
	CXml_Bll_UUTItem_Tem fP1;

	FirstPaper stucPaper;
	stucTestInfo stuTestInfo;
	m_tbTestInfo.ReadTestInfo(&stuTestInfo,nTestInfoID);  //�����ݿ��ȡ������Ϣ

	CString strTemPath=m_pathOpe.GetStartPath()+stuTestInfo.m_strTemplete+".xml"; //ģ��·��
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("�Ҳ���ģ�������ļ�","����");
		return;
	}
	
	CString strPageIndex;
	CArray<FrontPage, FrontPage> ftpg;
	fP1.ReadFrontPageList(strTemPath, strPageIndex, ftpg);
	////////////////////�����Է�����Ϣת��Ϊ�������////////////////////////////////////////////
	stucPaper.m_intSheetNumber = -1;
	stucPaper.m_stucCustomer.m_strName=stuTestInfo.m_strCustomer;  //ί�з�
	stucPaper.m_stucAddress_Customer.m_strName=stuTestInfo.m_strAddress; //ί�з���ַ
	stucPaper.m_stucInsName.m_strName=stuTestInfo.m_strInsName; //������������
	stucPaper.m_stucInsModel.m_strName=stuTestInfo.m_strModel; //�����ͺ�
	stucPaper.m_stucFactory.m_strName=stuTestInfo.m_strFactory;//���쳧
	stucPaper.m_stucSNumber.m_strName=stuTestInfo.m_strSNumber; //���߱��
	stucPaper.m_stucInsUse.m_intSel=atoi(stuTestInfo.m_strInsUse); //������;
	stucPaper.m_stucNumber_Mana.m_strName=stuTestInfo.m_strNumber_Mana; //������
	stucPaper.m_stucCalDate.m_strName=stuTestInfo.m_strCalDate; //У׼����
	stucPaper.m_stucDueCalDate.m_strName=stuTestInfo.m_strDueCalDate; //У׼����/������У׼����
	stucPaper.m_StandardName0.m_strName = StandardName[0]; //У׼��������
	stucPaper.m_StandardNum0.m_strName = StandardNum[0];  //У׼�������
	stucPaper.m_StandardName1.m_strName = StandardName[1]; //У׼��������
	stucPaper.m_StandardNum1.m_strName = StandardNum[1];  //У׼�������
	stucPaper.m_StandardName2.m_strName = StandardName[2]; //У׼��������
	stucPaper.m_StandardNum2.m_strName = StandardNum[2];  //У׼�������
	stucPaper.m_StandardName3.m_strName = StandardName[3]; //У׼��������
	stucPaper.m_StandardNum3.m_strName = StandardNum[3];  //У׼�������

	stucPaper.m_stucResult.m_strName=stuTestInfo.m_strResult; //У׼���ۣ�����˵��
	stucPaper.m_stucConclusion.m_intSel=(stuTestInfo.m_strConclusion=="pass"?1:0); //У׼���� �Ƿ�ϸ�
	stucPaper.m_stucCalStation.m_intSel=atoi(stuTestInfo.m_strCalStation); //У׼�ص�:0=ʵ���� 1=ί�з��ֳ� -1=�Զ���  atoi() ���ַ���ת������������һ������
	stucPaper.m_stucTestAdrress.m_strName = m_TestAddress1;//У׼�ص�
	stucPaper.m_stucTemperature.m_strName=stuTestInfo.m_strTemperature; //�¶�
	stucPaper.m_stucHumidity.m_strName=stuTestInfo.m_strHumidity;//ʪ��
	stucPaper.m_stucTester.m_strName=stuTestInfo.m_strTester; //У׼��Ա

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
	stucPaper.m_strTemplete=stuTestInfo.m_strTemplete; //ģ��·��
	//	MessageBox(stucPaper.m_stucAddress_Customer.m_strName);
    //////////////////////�����ݿ��ȡ��������////////////////////////////////////////////////////
	vector<stucTestResult> vTestResult;
	m_tbTestResult.ReadTestResultList(&vTestResult,nTestInfoID);

	//////////////////////�����Խ����Ϣת��Ϊ�������////////////////////////////////////////////////////
	vector<StringStruct> vstucResult; //���Խ���б�
	strTemPath=m_pathOpe.GetStartPath()+stuTestInfo.m_strTemplete+".xls"; //ģ��·��
	if(GetFileAttributes(strTemPath)==-1)
	{
		MessageBox("�Ҳ�����׼�ļ�ģ��","����");
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
		+"_"+stuTestInfo.m_strSNumber+"_"+stuTestInfo.m_strNumber_Mana+".xls"; //�洢·��

	if(GetFileAttributes(strSavePath)!=-1)
	{
		if(MessageBox("�����Ѿ����ڣ��Ƿ񸲸�","��ʾ",MB_OKCANCEL)==1)
		{	
     		if(!DeleteFile(strSavePath))
			{
				MessageBox("֤��Ϊֻ��״̬���޷�����","����");
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
	m_Excel_Ope.WriteResultToExcel(strTemPath,strSavePath,stucPaper);   //������д��Excelģ��
}

void CReport::UpdateTestResultList(int intTestInfoID)
{
	m_ListV_TestResult.DeleteAllItems();
	//�����ݿ��ȡ��������
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
	m_ListV_TestResult.InsertColumn(0,"���",LVCFMT_LEFT,width/13);
	m_ListV_TestResult.InsertColumn(1,"��Ŀ����",LVCFMT_LEFT,width/4);
	m_ListV_TestResult.InsertColumn(2,"��������",LVCFMT_LEFT,width/4);
	m_ListV_TestResult.InsertColumn(3,"���Խ��",LVCFMT_LEFT,width/8);
	m_ListV_TestResult.InsertColumn(4,"����ֵ",LVCFMT_LEFT,width/10);
	m_ListV_TestResult.InsertColumn(5,"����ֵ",LVCFMT_LEFT,width/10);
	m_ListV_TestResult.InsertColumn(6,"��λ",LVCFMT_LEFT,width/10);
}

void CReport::OnClickListTestinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CPoint pt=GetCurrentMessage()->pt;//��ȡ��ǰ�����Ϣ����
	m_ListV_TestInfo.ScreenToClient(&pt);//ת��Ϊ���ؼ��еĿͻ�����
	UINT uFlags=0;
	int intHitLine=m_ListV_TestInfo.HitTest(pt,&uFlags); //�������
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
	UpdateData(); //�����ѯ����
	vector<stucTestInfo> vTestInfo;
	m_strSearchKey.TrimLeft(" ");  //ȥ���ַ���ǰ�Ŀ��ַ���
	m_strSearchKey.TrimRight(" "); //ȥ���ַ�����Ŀ��ַ���
	m_tbTestInfo.SearchTestInfoList(&vTestInfo,strContent,m_strSearchKey); //ִ�в�ѯ����
	UpdateListView_Info(vTestInfo);  //ˢ�²��Խ���б�
}

void CReport::UpdateListView_Info(vector<stucTestInfo> vTestInfo)
{
	m_ListV_TestInfo.DeleteAllItems(); //��ղ�����Ϣ�б�
	CString strID("");
	for(int i=0;i<vTestInfo.size();i++)
	{		
		strID.Format("%d",i+1);
		m_ListV_TestInfo.InsertItem(i,strID);
		//m_ListV_TestInfo.SetItemText(i,0,strID);
		m_ListV_TestInfo.SetItemText(i,1,vTestInfo[i].m_strTestTime); //����ʱ��
		m_ListV_TestInfo.SetItemText(i,2,vTestInfo[i].m_strCustomer);//ί�з�
		m_ListV_TestInfo.SetItemData(i,vTestInfo[i].m_intID); //������ϢID
		m_ListV_TestInfo.SetItemText(i,3,vTestInfo[i].m_strAddress); //ί�з���ַ
		m_ListV_TestInfo.SetItemText(i,4,vTestInfo[i].m_strInsName); //�豸����
        m_ListV_TestInfo.SetItemText(i,5,vTestInfo[i].m_strModel); //�豸�ͺ�
        m_ListV_TestInfo.SetItemText(i,6,vTestInfo[i].m_strFactory); //���쳧
        m_ListV_TestInfo.SetItemText(i,7,vTestInfo[i].m_strSNumber); //�������
        m_ListV_TestInfo.SetItemText(i,8,vTestInfo[i].m_strInsUse); //�豸��;
        m_ListV_TestInfo.SetItemText(i,9,vTestInfo[i].m_strNumber_Mana); //������
		m_ListV_TestInfo.SetItemText(i,10,vTestInfo[i].m_strCalDate); //У׼����
		m_ListV_TestInfo.SetItemText(i,11,vTestInfo[i].m_strDueCalDate); //������У׼����
		m_ListV_TestInfo.SetItemText(i,12,vTestInfo[i].m_strResult); //У׼����
		m_ListV_TestInfo.SetItemText(i,13,vTestInfo[i].m_strConclusion); //�Ƿ�ϸ�
		m_ListV_TestInfo.SetItemText(i,14,vTestInfo[i].m_strCalStation); //У׼�ص�
		m_ListV_TestInfo.SetItemText(i,15,vTestInfo[i].m_strTemperature); //�¶�
		m_ListV_TestInfo.SetItemText(i,16,vTestInfo[i].m_strHumidity); //ʪ��
        m_ListV_TestInfo.SetItemText(i,17,vTestInfo[i].m_strTester); //������Ա
		
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
