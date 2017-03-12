// SetResource.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "SetResource.h"
#include "PathOperate.h"
#include "AccessDB_Ope.h"
#include "SetIns.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ThrowErr(err) throw TEXT(#err)
extern CATE_TESTApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CSetResource dialog


CSetResource::CSetResource(CWnd* pParent /*=NULL*/)
	: CDialog(CSetResource::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetResource)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetResource::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetResource)
	DDX_Control(pDX, IDC_LIST_INFO, m_List_Info);
	DDX_Control(pDX, IDC_LIST_BASIC, m_List_Ins);
	DDX_Control(pDX, IDC_TREE_RES, m_tree_res);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetResource, CDialog)
	//{{AFX_MSG_MAP(CSetResource)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_NOTIFY(NM_CLICK, IDC_TREE_RES, OnClickTreeRes)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_RES, OnRclickTreeRes)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_MENU_CREATE, OnMenuCreate)
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_MODIFY, OnMenuModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_EASYSIZE_MAP(CSetResource)

EASYSIZE(IDC_TREE_RES,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_BORDER,0);
EASYSIZE(IDC_STATIC_SOURCE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_BORDER,0);
EASYSIZE(IDC_LIST_BASIC,ES_BORDER,ES_BORDER,ES_BORDER,IDC_LIST_INFO,0);
EASYSIZE(IDC_STATIC_INS,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0);
EASYSIZE(IDC_STATIC_INFO,ES_BORDER,IDC_STATIC_SOURCE,ES_BORDER,ES_BORDER,0);
EASYSIZE(IDC_LIST_INFO,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0);

END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CSetResource message handlers

BOOL CSetResource::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
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
	m_tree_res.SetImageList(&m_imageList,TVSIL_NORMAL);



	// TODO: Add extra initialization here
//	CXmlFile_Ope *xmp=new CXmlFile_Ope();
	CPathOperate xmp;
	//CString myStartPath;
	myStartPath=xmp.GetStartPath();
	CString  filePath_DB;        //系统数据库路径
	filePath_DB=myStartPath+"DataInfo\\系统信息库\\PavelDemo.mdb";

	CAccessDB_Ope *acc=new CAccessDB_Ope(); //资源数据处理对象
	_RecordsetPtr pRecord_Ins=NULL;

	if(!acc->RecordOpen("tb_Resource"))
		return 0;
	
	m_pRecordset=acc->m_Recordset;

	//基本信息列表设置
	m_List_Ins.InsertColumn(0,"设备名称",LVCFMT_CENTER,100);
	m_List_Ins.InsertColumn(1,"设备型号",LVCFMT_CENTER,100);
	m_List_Ins.InsertColumn(2,"设备编号",LVCFMT_CENTER,150);
	m_List_Ins.InsertColumn(3,"生产厂家",LVCFMT_CENTER,150);
	m_List_Ins.InsertColumn(4,"地址",LVCFMT_CENTER,100);
	m_List_Ins.InsertColumn(5,"通道",LVCFMT_CENTER,50);
	m_List_Ins.InsertColumn(6,"驱动",LVCFMT_CENTER,200);
	m_List_Ins.InsertColumn(7,"备注",LVCFMT_LEFT,150);
	m_List_Ins.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//详细信息列表设置
	m_List_Info.InsertColumn(0,"功能名称",LVCFMT_CENTER,100);
	m_List_Info.InsertColumn(1,"逻辑名称",LVCFMT_CENTER,100);
	m_List_Info.InsertColumn(2,"函数说明",LVCFMT_CENTER,100);
	m_List_Info.InsertColumn(3,"备注",LVCFMT_CENTER,100);
	m_List_Info.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	

	//打开资源数据表
	int intKindID=0; //编号
	CString strKindName="";  //分类名称
	CString strKindLogic=""; //分类逻辑名
	int intID_Ins=0;//仪器编号
	CString strAdd_Ins="";//仪器地址
	CString strModel_Ins="";//仪器型号
	CString strNumber_Ins="";//仪器编号
	CString strManu_Ins=""; //生产厂家
	CString strDriveName_Ins=""; //驱动程序名
	_variant_t var;
	HTREEITEM hKind=NULL;
	HTREEITEM hIns=NULL;
	char strSearch[255];

	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		
		while(!m_pRecordset->adoEOF)  //列举资源信息
		{
			var=m_pRecordset->GetCollect("ID");
			if(var.vt!=VT_NULL)
				intKindID=atoi((LPCSTR)_bstr_t(var));
			var=m_pRecordset->GetCollect("Name");
			if(var.vt!=VT_NULL)
				strKindName=(LPCSTR)_bstr_t(var);
			var=m_pRecordset->GetCollect("LogicName");
			if(var.vt!=VT_NULL)
				strKindLogic=(LPCSTR)_bstr_t(var);

			m_pRecordset->MoveNext();
			//--加入树节点--
		   hKind=m_tree_res.InsertItem(strKindName+"("+strKindLogic+")",2,2);
		   m_tree_res.SetItemData(hKind,intKindID); //ID存放

		   sprintf(strSearch,"tb_Instrument where ResourceID=%d",intKindID);
		   if(!acc->RecordOpen(strSearch))
			   return 0;
		   pRecord_Ins=acc->m_Recordset;
		    while(!pRecord_Ins->adoEOF) //列举设备信息
			{
				var=pRecord_Ins->GetCollect("ID");
				if(var.vt!=VT_NULL)
					intID_Ins=atoi((LPCSTR)_bstr_t(var));
				var=pRecord_Ins->GetCollect("Model");
				if(var.vt!=VT_NULL)
					strModel_Ins=(LPCSTR)_bstr_t(var);
				
				var=pRecord_Ins->GetCollect("Manufacture");
				if(var.vt!=VT_NULL)
					strManu_Ins=(LPCSTR)_bstr_t(var);
				var=pRecord_Ins->GetCollect("Address");
				if(var.vt!=VT_NULL)
					strAdd_Ins=(LPCSTR)_bstr_t(var);
				var=pRecord_Ins->GetCollect("DriveName");
				if(var.vt!=VT_NULL)
					strDriveName_Ins=(LPCSTR)_bstr_t(var);
				hIns=m_tree_res.InsertItem(strAdd_Ins+"("+strModel_Ins+")",1,1,hKind);  //添加到树列表中
				m_tree_res.SetItemData(hIns,intID_Ins);
				BrowsIns(hIns,strDriveName_Ins);
				pRecord_Ins->MoveNext();
			}
			m_tree_res.Expand(hKind,TVE_EXPAND);
			acc->RecordClose(pRecord_Ins);
			
			
		//	if(m_pRecordset
		}
		

	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	//acc->RecordClose();
	acc->RecordClose(m_pRecordset);
	m_tree_res.SelectItem(m_tree_res.GetFirstVisibleItem());
	m_List_Ins.EnableWindow(FALSE);
	m_List_Info.EnableWindow(FALSE);
	m_newMenu.LoadMenu(IDR_MENU_SOURCE);
	delete acc;

	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CSetResource::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	UPDATE_EASYSIZE;
	// TODO: Add your message handler code here
	
}


void CSetResource::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(150,100,fwSide,pRect);
}

void CSetResource::OnClickTreeRes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pt=GetCurrentMessage()->pt;
	m_tree_res.ScreenToClient(&pt);
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_res.HitTest(pt,&uFlags);
	if((hItem!=NULL)&&(TVHT_ONITEM&uFlags))
	{
		if(m_List_Ins.GetItemCount())
       	  m_List_Ins.DeleteAllItems();
	    if(m_List_Info.GetItemCount())
       	  m_List_Info.DeleteAllItems();
		m_tree_res.SelectItem(hItem);
		if(m_tree_res.GetParentItem(hItem)!=NULL && m_tree_res.GetParentItem(m_tree_res.GetParentItem(hItem))==NULL)
		{ //如果选中第二层
			m_List_Ins.EnableWindow(TRUE);
		    m_List_Info.EnableWindow(FALSE);
			ListInsBasic(m_tree_res.GetItemData(hItem));
		}
		else if(m_tree_res.GetParentItem(hItem)!=NULL && m_tree_res.GetParentItem(m_tree_res.GetParentItem(hItem))!=NULL)
		{//如果选中第三层
			m_List_Info.EnableWindow(TRUE);
			m_List_Ins.EnableWindow(TRUE);
			HTREEITEM hTreeItem_Ins=m_tree_res.GetParentItem(m_tree_res.GetParentItem(hItem));
			CString strXMLSourcePath=ListInsBasic(m_tree_res.GetItemData(hTreeItem_Ins));

		//	CString strLogic_Ins=m_tree_res.GetItemText(hTreeItem_Ins);
			CString strXMLTitle_Dll=m_tree_res.GetItemText(hItem);
			strXMLTitle_Dll=strXMLTitle_Dll.Left(strXMLTitle_Dll.Find("."));
		//	strLogic_Ins=strLogic_Ins.Right(strLogic_Ins.GetLength()-strLogic_Ins.Find("(")-1);
		//	strLogic_Ins=strLogic_Ins.Left(strLogic_Ins.Find(")"));
			
			strXMLSourcePath=myStartPath+"DataInfo\\仪器资源库\\InstrDriver\\"+strXMLSourcePath+"\\"
				+strXMLTitle_Dll+"\\"+strXMLTitle_Dll+".xml";


			if(GetFileAttributes(strXMLSourcePath)==-1)
			{
				AfxMessageBox("驱动配置文件不存在");
				return;
			}
		//	CString folderName="NI PXI-5660 RFAnalyzer";
		//	strXMLSourcePath=myStartPath+"DataInfo\\仪器资源库\\InstrDriver\\"+folderName+"\\SpecTest\\SpecTest.xml";
			BrowsFunc(strXMLSourcePath);
		}
		else
		{
			m_List_Ins.EnableWindow(FALSE);
		}

	}
	*pResult = 0;
}



//在树列表中增加设备驱动列表
int CSetResource::BrowsIns(HTREEITEM hMyTreeItem, //要插入的树节点
						   CString strMyDriveName//驱动名称
						   )
{
	//获取仪器XML文件路径
	CString strXMLSourcePath;
	CString folderName=strMyDriveName;
	
//	pDoc_Ins=new TiXmlDocument(); //XML文档对象
		//驱动搜索并添加
	CFileFind ff;
	CString strDir=myStartPath+"DataInfo\\仪器资源库\\InstrDriver\\"+folderName+"\\"+"*.*";
	BOOL res=ff.FindFile(strDir);
//	TiXmlNode *pNode_Ins=NULL;

	while(res)
	{
		res=ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			//如果是一个子目录，继续找子目录中的文件		
			CString strPath=ff.GetFilePath();
			CString strTitle=ff.GetFileTitle();
			strXMLSourcePath=strPath+"\\"+strTitle+".xml";
			CString strDllSourcePath=strPath+"\\"+strTitle+".dll";
			if(GetFileAttributes(strXMLSourcePath)!=-1 && GetFileAttributes(strDllSourcePath)!=-1)
			{
				m_tree_res.InsertItem(strTitle+".dll",1,1,hMyTreeItem);
			}	
		}
	}
	return 1;
}

//在基础信息表中列举设备的信息,返回制造厂+型号字符串
CString CSetResource::ListInsBasic(int intMyID)
{
	CAccessDB_Ope* acc=new CAccessDB_Ope();
	char strSearch[255];
	sprintf(strSearch,"tb_Instrument where ID=%d",intMyID);
	CString strModel_Ins="";//仪器型号
	CString strManu_Ins=""; //生产厂家
	CString strAdd_Ins="";//仪器地址
    CString strNumber_Ins="";//仪器编号

	CString strName_Ins="";//名称
	CString strChan_Ins="";//通道
	CString strDriveName_Ins=""; //驱动名称
	CString strNote_Ins="";//备注
	_variant_t var;
	CString strRet="";
	if(!acc->RecordOpen(strSearch))
	{
		return "";
	}
	m_pRecordset=acc->m_Recordset;
	if(!m_pRecordset->adoEOF)
	{
		var=m_pRecordset->GetCollect("Model");
		if(var.vt!=VT_NULL)
			strModel_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("Manufacture");
		if(var.vt!=VT_NULL)
			strManu_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("Address");
		if(var.vt!=VT_NULL)
			strAdd_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("SNumber");
		if(var.vt!=VT_NULL)
			strNumber_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("Name");
		if(var.vt!=VT_NULL)
			strName_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("Channel");
		if(var.vt!=VT_NULL)
			strChan_Ins=(LPCSTR)_bstr_t(var);
		var=m_pRecordset->GetCollect("DriveName");
		if(var.vt!=VT_NULL)
			strDriveName_Ins=(LPCSTR)_bstr_t(var);

		var=m_pRecordset->GetCollect("Note");
		if(var.vt!=VT_NULL)
			strNote_Ins=(LPCSTR)_bstr_t(var);

		//插入表
		m_List_Ins.InsertItem(0,strName_Ins);
		m_List_Ins.SetItemText(0,1,strModel_Ins);
		m_List_Ins.SetItemText(0,2,strNumber_Ins);
		m_List_Ins.SetItemText(0,3,strManu_Ins);
		m_List_Ins.SetItemText(0,4,strAdd_Ins);
		m_List_Ins.SetItemText(0,5,strChan_Ins);
		m_List_Ins.SetItemText(0,6,strDriveName_Ins);
		m_List_Ins.SetItemText(0,7,strNote_Ins);
		m_pRecordset->MoveNext();
		strRet=strDriveName_Ins;
	}
    acc->RecordClose();
	delete acc;

	return strRet;
}

//在详细信息列表中插入信息
int CSetResource::BrowsFunc(CString strMyFilePath)
{
	
	TiXmlDocument* pDoc=new TiXmlDocument();

	TiXmlNode* pNode=NULL;
	pDoc->LoadFile(strMyFilePath);
	if(NULL==pDoc)
		return 0;
	TiXmlElement* pRootEle=pDoc->RootElement();

	TiXmlElement *pEle=NULL;
	pNode=pRootEle->FirstChild("FuncList");
	int i=0;
	for(pNode=pNode->FirstChild();pNode;pNode=pNode->NextSibling())
	{
		pEle=pNode->ToElement();
		m_List_Info.InsertItem(i,pNode->Value());	
		i++;
	}	

	
	if(NULL!=pDoc)
	    delete pDoc;
		
	
	return 1;
}


BOOL CSetResource::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_imageList)
		m_imageList.DeleteImageList();
	

	if(m_pRecordset->State)
		m_pRecordset->Close();
	m_newMenu.Detach(); //切断菜单变量与实际窗口的联系.
	return CDialog::DestroyWindow();
}


void CSetResource::OnRclickTreeRes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pt=GetCurrentMessage()->pt;
	m_tree_res.ScreenToClient(&pt);
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_res.HitTest(pt,&uFlags);
	OnClickTreeRes(pNMHDR, pResult);
	if((hItem!=NULL)&&(TVHT_ONITEM&uFlags))
	{
		m_tree_res.SelectItem(hItem);
		if(m_tree_res.GetParentItem(hItem)!=NULL&&m_tree_res.GetParentItem(m_tree_res.GetParentItem(hItem))!=NULL)
			return;	
		CMenu menu,*pSubMenu;
		m_newMenu.ChangeMenuItem(&m_newMenu);
		//m_newMenu.ChangeMenuItem(m_newMenu.GetSubMenu(0));
		if(!m_newMenu)
			return;
		if(m_tree_res.GetParentItem(hItem)==NULL)
		    pSubMenu=m_newMenu.GetSubMenu(0);
		else
			pSubMenu=m_newMenu.GetSubMenu(1);
		//pSubMenu->MeasureItem(
		CPoint oPoint;
		GetCursorPos(&oPoint);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);

	}
	*pResult = 0;
}

void CSetResource::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if(lpMeasureItemStruct->CtlType==ODT_MENU)
		m_newMenu.MeasureItem(lpMeasureItemStruct);
	else	
	   CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSetResource::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if(lpDrawItemStruct->CtlType==ODT_MENU)
		m_newMenu.DrawItem(lpDrawItemStruct);
	else
	    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSetResource::OnMenuCreate() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem_Sel=m_tree_res.GetSelectedItem();
	CAccessDB_Ope* acc=new CAccessDB_Ope();
	CString s; 
	if(NULL==hItem_Sel)
		return;
	if(NULL==m_tree_res.GetParentItem(hItem_Sel))
	{
		//第一层
		int intKindID=m_tree_res.GetItemData(hItem_Sel);
		CSetIns mySetIns(0,intKindID,this);
		if(IDOK==mySetIns.DoModal())
		{
			acc->RunDatabase("select * from tb_Instrument where [Address]=\'"+mySetIns.m_strAddress+"\'");
			if(!acc->m_Recordset->adoEOF)
			{
			    MessageBox("物理地址重复");
				return;							
			}
			acc->RecordClose();
		    if(!acc->RecordOpen("tb_Instrument"))
			{
        		return;
			}
        	int intID_Ins=acc->GenerateID();
			acc->RecordClose();
	        s.Format("insert into tb_Instrument([ID],[ResourceID],[Name],[Model],[SNumber],[Manufacture],[Address],[Channel],[DriveName],[Note])values(%d,%d,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
				intID_Ins,mySetIns.m_intNodeID,mySetIns.m_strInsName,mySetIns.m_strModel,mySetIns.m_strSNumber,mySetIns.m_strManu,mySetIns.m_strAddress,mySetIns.m_strChann,mySetIns.m_strDriveName," ");
	        acc->RunDatabase(s);

	        if(NULL!=acc->m_Recordset)
		       MessageBox("操作成功");
	        else
		       MessageBox("操作失败");

		
        	acc->RecordClose();
			HTREEITEM hItem_Add=m_tree_res.InsertItem(mySetIns.m_strAddress+"("+mySetIns.m_strModel+")",1,1,hItem_Sel);
			if(hItem_Add!=NULL)
			{
				m_tree_res.SelectItem(hItem_Add);
			    BrowsIns(hItem_Add,mySetIns.m_strDriveName);
				m_tree_res.Expand(hItem_Add,TVE_EXPAND);
			}
		}
	}	
}

void CSetResource::OnMenuDelete() 
{
	// TODO: Add your command handler code here

	
}

void CSetResource::OnMenuModify() 
{
	// TODO: Add your command handler code here
	
}
