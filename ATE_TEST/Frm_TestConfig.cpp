// Frm_TestConfig.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frm_TestConfig.h"
#include "File_UUTInfo.h"
#include "ReadXML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestConfig dialog


CFrm_TestConfig::CFrm_TestConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CFrm_TestConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrm_TestConfig)
	m_port = _T("");
	m_chanel = _T("");
	//}}AFX_DATA_INIT
}

CFrm_TestConfig::CFrm_TestConfig(CString strKind,CString strModel,CWnd* pParent)
: CDialog(CFrm_TestConfig::IDD, pParent)
{
	m_strKind=strKind;
	m_strModel=strModel;
}


void CFrm_TestConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrm_TestConfig)
	DDX_Control(pDX, IDC_EDIT_INSCHANNEL, m_edit_channel);
	DDX_Control(pDX, IDC_EDIT_INSADDRESS, m_edit_port);
	DDX_Control(pDX, IDC_LIST_FUNCTION, m_funList);
	DDX_Control(pDX, IDC_LIST_INSREQUIRED, m_list_Required);
	DDX_Control(pDX, IDC_TREE_CONFIG, m_tree_Config);
	DDX_Control(pDX, IDC_COMBO_DRIVER, m_comboDriver);
	DDX_Text(pDX, IDC_EDIT_INSADDRESS, m_port);
	DDX_Text(pDX, IDC_EDIT_INSCHANNEL, m_chanel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrm_TestConfig, CDialog)
	//{{AFX_MSG_MAP(CFrm_TestConfig)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_TREE_CONFIG, OnClickTreeConfig)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVER, OnSelchangeComboDriver)
	ON_BN_CLICKED(IDOK2, On_NewINI)
	ON_BN_CLICKED(IDOK, OnSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INSREQUIRED, OnClickListInsrequired)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDOK6, OnEDIT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CFrm_TestConfig)

//EASYSIZE(IDC_TREE_CONFIG,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_BORDER,0)
//EASYSIZE(IDC_TREE_TPS,ES_BORDER,ES_BORDER,ES_KEEPSIZE,IDC_EDIT_NAME,0)
END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestConfig message handlers

BOOL CFrm_TestConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_state = NEDIT;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_SUBFORM);
	m_Brush.CreatePatternBrush(&bmp);

	CRect itemRC1,itemRC2;
	m_funList.GetClientRect(itemRC1);
	m_list_Required.GetClientRect(itemRC2);

	InitTreeView();
	//m_list_Required.InsertColumn()
	m_list_Required.InsertColumn(0,"设备逻辑名",LVCFMT_LEFT,itemRC2.Width());
	m_funList.InsertColumn(0,"函数",LVCFMT_RIGHT,itemRC1.Width());

	//获取driver文件夹下的文件名
	vector <CString> vConfigList;
	CPathOperate paOpe;

	CString strFilePath=paOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+m_strKind;
	m_pthInstrDriver = strFilePath + "\\InstrDriver";
	m_pthFile = strFilePath+"\\TPS\\"+m_strModel;

	m_edit_channel.SetReadOnly();
	m_edit_port.SetReadOnly();
	m_comboDriver.EnableWindow(false);
	UpdateData(FALSE);
	
	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFrm_TestConfig::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	UPDATE_EASYSIZE;	
}

void CFrm_TestConfig::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(150,100,fwSide,pRect);	
}

HBRUSH CFrm_TestConfig::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_Brush;
	}	
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CFrm_TestConfig::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Brush.DeleteObject();
	
	return CDialog::DestroyWindow();
}

void CFrm_TestConfig::InitTreeView()
{
	vector <CString> vConfigList;
	m_file_UUTInfo.GetConfigList(m_strKind,m_strModel,&vConfigList);
	for(int i=0;i<vConfigList.size();i++)
	{
		m_tree_Config.InsertItem(vConfigList[i]);
	}
}

void CFrm_TestConfig::OnClickTreeConfig(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_state = NEDIT;

	CPoint pt=GetCurrentMessage()->pt;
	m_tree_Config.ScreenToClient(&pt);
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_Config.HitTest(pt,&uFlags);
	
	try
	{
		if((hItem!=NULL)&&(TVHT_ONITEM&uFlags)) //如果点击项目有效
		{
			m_configName = m_tree_Config.GetItemText(hItem);
			m_openFile = m_pthFile + "\\UUTInfo\\" + m_configName + ".ini";
			m_INIFile.SetINIPth(m_openFile);
			m_list_Required.DeleteAllItems();
			

			/*
			//获取所有的section名
			if(m_INIFile.IsNULL()!=0)				//判断INI文件是否为空
			{
				CStringArray sectionNames;
				int secCount = m_INIFile.GetSections(sectionNames);
				
				for(int i=0;i<secCount;i++)
					m_list_Required.InsertItem(i,sectionNames[i]);
			}
			else											//INI文件为空
			{
			*/
				vector<CString> vInsList;
				m_xml_UUTInfo.GetInsList(m_strKind,m_strModel,&vInsList);
				for(int i=0;i<vInsList.size();i++)
				{
					m_list_Required.InsertItem(i,vInsList[i]);		
				}
			//}
		}
	}
	catch (char* e)
	{
		MessageBox(e);		
	}

	*pResult = 0;

	m_comboDriver.ResetContent();				//清空combo里的内容
	m_funList.DeleteAllItems();
	m_edit_channel.Clear();
	m_edit_channel.Clear();
	m_edit_channel.SetReadOnly();
	m_edit_port.SetReadOnly();
	m_comboDriver.EnableWindow(false);
	UpdateData(FALSE);
}

void CFrm_TestConfig::OnSelchangeComboDriver() 
{
	// TODO: Add your control notification handler code here
	CString strlist;
	int pos = m_comboDriver.GetCurSel();
	CString str;
	CString pthFunXML;
	vector<CString> m_fun;

	m_comboDriver.GetLBText(pos,str);
	m_DriverName = str;

	pthFunXML = m_pthFileXML + "\\" + str + "\\" + str + ".xml";
	m_pthFunXML = pthFunXML;
 
	try
	{
		CReadXML m_readXML;
		m_readXML.ReadXMLList(pthFunXML,"funList",&m_fun);
		
		m_funList.DeleteAllItems();
		
		UpdateData(false);
		
		for(int i=0; i<m_fun.size();i++)
		{	strlist = m_fun[i];
		m_funList.InsertItem(i,strlist);
		}
	}
	catch (char* e)
	{
		MessageBox(e,"错误");
		
	}
}

void CFrm_TestConfig::On_NewINI() 
{
	// TODO: Add your control notification handler code here
	m_NewFileNameDialog.DoModal();
	CString nameINI = m_strModel +" " + m_NewFileNameDialog.m_configFileName;	//获取INI名
	CString pthINI = m_pthFile + "\\UUTInfo" + "\\"+ nameINI + ".ini" ;			//获取INI路径
	m_INIFile.SetINIPth(pthINI);												//设置INI的路径
	m_INIFile.SetINIname(nameINI);												//设置INI的名字
	m_tree_Config.InsertItem(nameINI);

	CFile file(_T(pthINI),CFile::modeCreate);	//创建文件*/
	file.Close();
}

void CFrm_TestConfig::OnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	vector<CString> m_fun;

	//如果选项为空，返回
	if(m_session == "")
	{
		AfxMessageBox("请选择设备逻辑名");
		return;
	}

	if(m_chanel==""||m_port=="")
	{
		AfxMessageBox("驱动，端口，通道不能为空!");
		return;
	}

	if(m_comboDriver.GetCurSel() == -1)
	{
		AfxMessageBox("驱动不能为空!");
		return;
	}


	CReadXML m_readXML;
	MessageBox(m_pthINI);
	MessageBox(m_pthFunXML);

	m_readXML.ReadXMLList(m_pthFunXML,"funList",&m_fun);

	CString keyName, keyValue,key_DrvierName;

	key_DrvierName =  m_driverFile + m_DriverName;

	m_INIFile.SaveConfiguerINI(m_session,m_port,m_chanel,key_DrvierName,m_DriverName,m_fun);

}

void CFrm_TestConfig::OnClickListInsrequired(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int n = m_list_Required.GetSelectionMark();

	BOOL res=FALSE;
	CString sectionNOW;
	CFileFind ff;
	if(n>=0)
	{
		m_comboDriver.ResetContent();				//清空combo里的内容
		//m_comboDriver.InsertString(0,"选择驱动");
		sectionNOW = m_list_Required.GetItemText(n,0);

		if(sectionNOW != m_session)					//判断当前选择的段名与之前选择的段名是否一致，若不一致，则状态为非编辑
		{
			m_state = NEDIT;
		}
		m_session = sectionNOW;

		if(m_session =="UUT")
		{	
			m_pthFileXML = m_pthFile + "\\Driver";
			m_driverFile = m_strKind + "\\" + "TPS" + "\\" + m_strModel + "\\" + "Driver\\";
			m_pthDriver = m_pthFileXML + "\\*.*";
		}
		else
		{
			m_pthFileXML = m_pthInstrDriver;
			m_driverFile = m_strKind + "\\InstrDriver\\";
			m_pthDriver = m_pthInstrDriver + "\\*.*";	
		}

		if(m_INIFile.IsNULL()!=0 && m_state == NEDIT)						//当INI文件不为空时，将INI文件中的数据读出来
		{
			m_port = m_INIFile.GetKeyValue(m_session,"Address");
			m_chanel = m_INIFile.GetKeyValue(m_session,"channel");		
			CString driverName = m_INIFile.GetDriverName(m_session);
			m_DriverName = driverName;
			
			UpdateData(FALSE);
			Invalidate();
			m_comboDriver.InsertString(0,driverName);
			m_comboDriver.SetCurSel(0);

			CStringArray KeyNames;
			int keyNum = m_INIFile.GetKeys(KeyNames,m_session);
			m_funList.DeleteAllItems();
			for(int i=3;i<keyNum;i++)			//function是从第三个开始的
				m_funList.InsertItem(i,KeyNames[i]);	
			
			m_edit_channel.SetReadOnly();
			m_edit_port.SetReadOnly();
			m_comboDriver.EnableWindow(FALSE);
		}
		else									//当INI文件为空时，读取配置信息
		{		

			res=ff.FindFile(m_pthDriver);
			while(res)
			{
				res=ff.FindNextFile();
				if(!ff.IsDots())
				{
					m_comboDriver.AddString(ff.GetFileTitle());
				}
			}

			int selShow = 0;
			CString comboText;
			for(int i=0; i<m_comboDriver.GetCount();i++)
			{
				m_comboDriver.GetLBText(i,comboText);		//显示之前选中的driver
				if(comboText == m_DriverName)
				{
					m_comboDriver.SetCurSel(i);
					selShow = 1;
				}
			}

			if(selShow == 0)
			{
				m_comboDriver.InsertString(0,"选择驱动");
				m_comboDriver.SetCurSel(0);
			}

			m_edit_channel.SetReadOnly(false);
			m_edit_port.SetReadOnly(false);
			m_comboDriver.EnableWindow(true);
		}
	}


	*pResult = 0;
}

void CFrm_TestConfig::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_comboDriver.ResetContent();

}

void CFrm_TestConfig::OnEDIT() 
{
	// TODO: Add your control notification handler code here
	//POSITION pos=m_list_Required.GetFirstSelectedItemPosition();
	//int n=m_list_Required.GetNextSelectedItem(pos); 
	m_state = EDIT;

	m_funList.DeleteAllItems();

	int n = m_list_Required.GetSelectionMark();
	if(n==-1)
	{
		AfxMessageBox("请选择驱动列表");
		return;
	}

	m_pthINI = m_pthFile + "\\UUTInfo" + "\\"+ m_configName + ".ini" ;			//获取INI配置文件的路径

	m_list_Required.DeleteAllItems();			//清空list控件

	vector<CString> vInsList;
	m_xml_UUTInfo.GetInsList(m_strKind,m_strModel,&vInsList);
	for(int i=0;i<vInsList.size();i++)
	{
		m_list_Required.InsertItem(i,vInsList[i]);		
	}

	m_edit_channel.SetReadOnly(FALSE);
	m_edit_port.SetReadOnly(FALSE);
	m_comboDriver.EnableWindow(true);

	m_list_Required.SetItemState(0,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);

	BOOL res=FALSE;
	CFileFind ff;
	res=ff.FindFile(m_pthDriver);
	m_comboDriver.ResetContent();				//清空combo里的内容
//	m_comboDriver.InsertString(0,"选择驱动");	
	m_comboDriver.SetCurSel(0);

	while(res)
	{
		res=ff.FindNextFile();
		if(!ff.IsDots())
		{
				m_comboDriver.AddString(ff.GetFileTitle());
		}
	}

	int selShow = 0;
	CString comboText;
	for(i=0; i<m_comboDriver.GetCount();i++)
	{
		m_comboDriver.GetLBText(i,comboText);		//显示之前选中的driver
		if(comboText == m_DriverName)
		{
			m_comboDriver.SetCurSel(i);
			selShow = 1;
		}
	}
				
	if(selShow == 0)
	{
	//	m_comboDriver.InsertString(0,"选择驱动");
	//	m_comboDriver.SetCurSel(0);
	}
}

void CFrm_TestConfig::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
