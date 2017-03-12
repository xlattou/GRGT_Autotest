// InsDocument.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "InsDocument.h"
#include "AddKind.h"
#include "InputFileName.h"
#include "ModelList.h"
#include "Tool.h"
#include "InputModelName_Factury.h"
#include "ATE_TESTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsDocument dialog


CInsDocument::CInsDocument(CWnd* pParent /*=NULL*/)
	: CDialog(CInsDocument::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsDocument)
	m_CurSelTab = -1;
	//}}AFX_DATA_INIT
}


void CInsDocument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsDocument)
	DDX_Control(pDX, IDC_PIC_TEMPLETE, m_pic_Templete);
	DDX_Control(pDX, IDC_PIC_SOLUTION, m_pic_Solution);
	DDX_Control(pDX, IDC_PIC_BASIC, m_pic_Basic);
	DDX_Control(pDX, IDC_TREE_TPS, m_tree_tps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsDocument, CDialog)
	//{{AFX_MSG_MAP(CInsDocument)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_TREE_TPS, OnClickTreeTps)
	ON_BN_CLICKED(IDC_PIC_BASIC, OnPicBasic)
	ON_BN_CLICKED(IDC_PIC_TEMPLETE, OnPicTemplete)
	ON_BN_CLICKED(IDC_PIC_SOLUTION, OnPicSolution)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDD_ADD_KIND, OnAddKind)
	ON_COMMAND(IDD_ADD_MODEL, OnAddModel)
	ON_COMMAND(IDD_DEL_KIND, OnDelKind)
	ON_COMMAND(IDD_DEL_MODEL, OnDelModel)
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*BEGIN_EASYSIZE_MAP(CInsDocument)

EASYSIZE(IDC_TREE_TPS,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_BORDER,0)


END_EASYSIZE_MAP*/

/////////////////////////////////////////////////////////////////////////////
// CInsDocument message handlers

BOOL CInsDocument::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//初始化界面背景
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&bmp);

	//设定数控件图表
	HICON hIcon[4];
	
	m_imageList.Create(32,32,ILC_COLOR32|ILC_MASK,4,4);
	hIcon[0]=AfxGetApp()->LoadIcon(IDI_ICON5);
	hIcon[1]=AfxGetApp()->LoadIcon(IDI_ICON6);
	hIcon[2]=AfxGetApp()->LoadIcon(IDI_ICON7);
	hIcon[3]=AfxGetApp()->LoadIcon(IDI_ICON3);
	
	for(int i=0;i<4;i++)
	{
		m_imageList.Add(hIcon[i]);
	}
	m_tree_tps.SetImageList(&m_imageList,TVSIL_NORMAL);
//	DWORD dwStyle=m_listCtrl.GetExtendedStyle();
//	m_listCtrl.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT);

	//填充树列表
	InitTreeList();
//	m_listCtrl.SetImageList(&m_imageList,LVSIL_NORMAL);

	//DWORD dStyle = m_tab.GetExStyle();
	//m_tab.SetExtendedStyle(dStyle & ~TCS_TABS);

	//设置TAB控件	
	m_dlg_Basic.Create(IDD_INSDOC_BASIC, this);
	m_dlg_Templete.Create(IDD_INSDOC_TEMPLETE, this);
	m_dlg_Solution.Create(IDD_INSDOC_SOLUTION, this);
	ChildWindowShow(0);
	//INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsDocument::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect1;
	GetClientRect(&rect1);
	int nWide, nHeight = rect1.Height() - 35;

	if(IsWindow(m_tree_tps))
		m_tree_tps.MoveWindow(12, 25, 220, nHeight);
	
	nWide = rect1.Width() - 252;
	nHeight -= 30;
	if(IsWindow(m_dlg_Basic))
		m_dlg_Basic.MoveWindow(242, 55, nWide, nHeight);
	if(IsWindow(m_pic_Templete))
		m_dlg_Templete.MoveWindow(242, 55, nWide, nHeight);
	if(IsWindow(m_pic_Solution))
		m_dlg_Solution.MoveWindow(242, 55, nWide, nHeight);
}

/*void CInsDocument::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(150,100,fwSide,pRect);	
}*/

BOOL CInsDocument::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	if(m_imageList)
	  m_imageList.DeleteImageList();
	
	if(m_dlg_Basic)
		m_dlg_Basic.DestroyWindow();
	if(m_dlg_Templete)
		m_dlg_Templete.DestroyWindow();
	if(m_dlg_Solution)
		m_dlg_Solution.DestroyWindow();

	return CDialog::DestroyWindow();
}

HBRUSH CInsDocument::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
	}	
	
	if(nCtlColor==CTLCOLOR_STATIC)
	{ //更改静态框透明，字颜色为白色
    	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));	
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CInsDocument::InitTreeList()
{
	try
	{
		HTREEITEM hItem;
		vector <UUTKindList> vKindList;
		vector <FileInfo> vUUTList;
		m_tree_tps.DeleteAllItems();
		m_strThreadKind = m_strThreadModel = "";
		
		
		m_bll_UUTKind.GetKindList(&vKindList);  //读取型号列表
		for(int i=0;i<vKindList.size();i++)
		{
			hItem=m_tree_tps.InsertItem(vKindList[i].m_strKindName,2,2);
			m_tree_tps.SetItemData(hItem,vKindList[i].m_intID);
			m_UUTInfo.GetUUTList(vKindList[i].m_strKindName,&vUUTList);
			for(int j=0;j<vUUTList.size();j++)
			{
				m_tree_tps.InsertItem(vUUTList[j].m_strFileName,1,1,hItem);	
			}
			vUUTList.clear();
		}
	}
	catch (CMemoryException* )
	{
		
	}
	catch (CFileException* )
	{
	}
	catch (CException* )
	{
	}
	catch(char* e)
	{
		MessageBox(e);
	}

}

void CInsDocument::OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_tree_tps;
	ASSERT_VALID(pWndTree);

	CString strKind,strModel;
	strKind = m_strThreadKind;
	strModel = m_strThreadModel;

	CPoint point;
	point.x = -1;
	point.y = -1;
	GetCursorPos(&point);
	CString str1;

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);
		//pWndTree->ClientToScreen(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			if (hTreeItem != NULL)
			{
				str1 = pWndTree->GetItemText(hTreeItem);
				hTreeItem = pWndTree->GetParentItem(hTreeItem);
				
				if (hTreeItem != NULL)
				{
					m_strThreadKind  = pWndTree->GetItemText(hTreeItem);
					m_strThreadModel = str1;
				}
				else
				{
					m_strThreadKind  = str1;
					m_strThreadModel = "";
				}
			}
			else
			{
				m_strThreadKind  = "";
				m_strThreadModel = "";
			}
		}
	}

	if(m_strThreadKind != strKind || m_strThreadModel != strModel)
	{
		m_dlg_Basic.UpdateBasicInfo(m_strThreadKind, m_strThreadModel);
		m_dlg_Templete.UpdataTempleteCom(m_strThreadKind, m_strThreadModel);
		m_dlg_Solution.initAll(m_strThreadKind, m_strThreadModel);
	}
	*pResult = 0;
}

void CInsDocument::OnPicBasic() 
{
	ChildWindowShow(0);
}

void CInsDocument::OnPicTemplete() 
{
	ChildWindowShow(1);
}

void CInsDocument::OnPicSolution() 
{
	ChildWindowShow(2);
}

void CInsDocument::ChildWindowShow(int nIChild)
{
	HBITMAP hbmp[3];// = (HBITMAP)//::LoadImage(AfxGetInstanceHandle(), 

         //"c:\\aaa.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	switch(nIChild)
	{
	case 0:
		hbmp[0] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_BASIC1);
		hbmp[1] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_TEMPLETE);
		hbmp[2] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION);
		m_pic_Basic.SetBitmap(hbmp[0]);
		m_pic_Templete.SetBitmap(hbmp[1]);
		m_pic_Solution.SetBitmap(hbmp[2]);
		m_dlg_Basic.ShowWindow(SW_SHOW);
		m_dlg_Templete.ShowWindow(SW_HIDE);
		m_dlg_Solution.ShowWindow(SW_HIDE);
		break;
	case 1:
		hbmp[0] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_BASIC);
		hbmp[1] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_TEMPLETE1);
		hbmp[2] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION);
		m_pic_Basic.SetBitmap(hbmp[0]);
		m_pic_Templete.SetBitmap(hbmp[1]);
		m_pic_Solution.SetBitmap(hbmp[2]);
		m_dlg_Basic.ShowWindow(SW_HIDE);
		m_dlg_Templete.ShowWindow(SW_SHOW);
		m_dlg_Solution.ShowWindow(SW_HIDE);
		break;
	case 2:
		hbmp[0] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_BASIC);
		hbmp[1] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_TEMPLETE);
		hbmp[2] = (HBITMAP)::LoadBitmap(AfxGetInstanceHandle(),(LPSTR)IDB_PIC_SOLUTION1);
		m_pic_Basic.SetBitmap(hbmp[0]);
		m_pic_Templete.SetBitmap(hbmp[1]);
		m_pic_Solution.SetBitmap(hbmp[2]);
		m_dlg_Basic.ShowWindow(SW_HIDE);
		m_dlg_Templete.ShowWindow(SW_HIDE);
		m_dlg_Solution.ShowWindow(SW_SHOW);
		break;
	}
}

BOOL CInsDocument::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CInsDocument::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_tree_tps;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
		return;

	DWORD dw=2;
	CString str1, str2;
	str2 = str1 = "";

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			if (hTreeItem != NULL)
			{
				str1 = pWndTree->GetItemText(hTreeItem);
				hTreeItem = pWndTree->GetParentItem(hTreeItem);
				
				if (hTreeItem != NULL)
				{
					m_strThreadKind  = pWndTree->GetItemText(hTreeItem);
					m_strThreadModel = str1;
					dw = 1;
				}
				else
				{
					m_strThreadKind  = str1;
					m_strThreadModel = "";
					dw = 0;
				}
			}
			else
			{
				m_strThreadKind  = "";
				m_strThreadModel = "";
			}
		}
	}
	pWndTree->SetFocus();

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_CONTEXTMENU));

	CMenu* pPopup = menu.GetSubMenu(dw);
	ASSERT(pPopup != NULL);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this/*pWndPopupOwner*/);
}

void CInsDocument::OnAddKind() //添加设备类型
{
	CString sEngineFilePath = "";	//引擎路径
	CString sKindName		= "";	//类型名称

	CAddKind addkinddlg;
	addkinddlg.DoModal();

	if(addkinddlg.m_nHasEngine == 1)//有引擎方式添加
	{
		CFileDialog dlg(TRUE, "_testConfig.ini,  _Engine.dll", NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "引擎配置文件(*_testConfig.ini)|*_testConfig.ini|引擎文件(*_Engine.dll)|*_Engine.dll||");
		if(dlg.DoModal()==IDOK)
		{
			sEngineFilePath = dlg.GetPathName();//获得引擎名称
			sKindName		= dlg.GetFileTitle();//获得类型名称
			if(sKindName.Right(7) == "_Engine")
			{
				sKindName = sKindName.Left(sKindName.GetLength() - 7);
				sEngineFilePath = sEngineFilePath.Left(sEngineFilePath.GetLength() - 11);
			}
			else
			{
				sKindName = sKindName.Left(sKindName.GetLength() - 11);
				sEngineFilePath = sEngineFilePath.Left(sEngineFilePath.GetLength() - 15);
			}
		} 
	}
	else if(addkinddlg.m_nHasEngine == 0)//无引擎方式直接填写装置类型名字
	{
		CInputFileName input1;
		input1.m_strTile = "请输入设备类型名称";
		input1.DoModal();
		sKindName = input1.m_configFileName;
	}
	if(sKindName == "")
		return;
	char cFirst = sKindName[0];
	if((cFirst >= 0 && cFirst <= 64) || (cFirst >= 91 && cFirst <= 96) || (cFirst >= 123 && cFirst <= 127))
	{
		AfxMessageBox("设备类型首字符不能为符号、数字及空格!");
		return;
	}
	CreatModelKind(sKindName, sEngineFilePath);//添加装置类型
	
	InitTreeList();
	m_strThreadKind  = "";
	m_strThreadModel = "";
	m_dlg_Basic.UpdateBasicInfo(m_strThreadKind, m_strThreadModel);
	m_dlg_Templete.UpdataTempleteCom(m_strThreadKind, m_strThreadModel);
	m_dlg_Solution.initAll(m_strThreadKind, m_strThreadModel);
}

void CInsDocument::OnAddModel() 
{
	if(m_strThreadKind == "")
		return;

	CString  strReferModelPath = "";
	CAddKind addkind1;
	bool bStartAdd = true;
	bool bSameKind = false;
	addkind1.m_strTitle = "添加设备型号";
	addkind1.m_strHasEngine = "以现有型号为模板添加";
	addkind1.DoModal();
	if(addkind1.m_nHasEngine < 0)
		return;
	if(addkind1.m_nHasEngine)//以现有型号为模板添加
	{
		CModelList modlist;
		modlist.m_strKind = m_strThreadKind;
		modlist.DoModal();
		if(modlist.m_strReferModelPath == "")
			bStartAdd = false;
		else
		{
			strReferModelPath = modlist.m_strReferModelPath;
			bSameKind = modlist.m_bReferSameKind;
		}
	}

	if(bStartAdd)
	{
		CInputModelName_Factury input1;
		input1.DoModal();
		CString strName, strFactory, strModel;
		strName = input1.strName;
		strFactory = input1.strFactory;
		if(strName.GetLength() < 1)
			return;
		CreatModel(strFactory, strName, strReferModelPath, bSameKind);
	}
	m_strThreadKind  = "";
	m_strThreadModel = "";

	InitTreeList();
	m_dlg_Basic.UpdateBasicInfo(m_strThreadKind, m_strThreadModel);
	m_dlg_Templete.UpdataTempleteCom(m_strThreadKind, m_strThreadModel);
	m_dlg_Solution.initAll(m_strThreadKind, m_strThreadModel);
}

void CInsDocument::OnDelKind()
{
	DWORD dAfxRtn = IDNO;
	if(AfxMessageBox("确定要删除[" + m_strThreadKind + "]设备类型吗?",MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)==IDYES)
	{
		CPathOperate paOpe; //路径操作对象
		CString strPath_Kind=paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + m_strThreadKind;
		CTool tool1;
		tool1.DeleteDirectorye(strPath_Kind);
		CXml_UUTInfo xmlUUTInfo;
		m_bll_UUTKind.DeleteKind(m_strThreadKind);
		InitTreeList();
		m_strThreadKind  = "";
		m_strThreadModel = "";
		m_dlg_Basic.UpdateBasicInfo(m_strThreadKind, m_strThreadModel);
		m_dlg_Templete.UpdataTempleteCom(m_strThreadKind, m_strThreadModel);
		m_dlg_Solution.initAll(m_strThreadKind, m_strThreadModel);
	}
}

void CInsDocument::CreatModelKind(CString strKindName, CString sEngineFilePath)
{
	//将类型添加到XML
	if(m_bll_UUTKind.CreatKind(strKindName) == 0)
	{
		AfxMessageBox("类型名" + strKindName + "与其他类型重复!");
		return;
	}
	//创建装置类型所需要的文件夹
	CPathOperate paOpe; //路径操作对象
	CString strPath_Kind=paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + strKindName;
	CreateDirectory(strPath_Kind, NULL);
	CreateDirectory(strPath_Kind + "\\InsPortDriver", NULL);
	CreateDirectory(strPath_Kind + "\\InstrDriver", NULL);
	CreateDirectory(strPath_Kind + "\\TPS", NULL);

	
	if(sEngineFilePath != "")
	{
		CopyFile(sEngineFilePath + "_Engine.dll", strPath_Kind + "\\InsPortDriver\\" + strKindName + "_Engine.dll", FALSE);//拷贝引擎到引擎路径
		CopyFile(sEngineFilePath + "_testConfig.ini", strPath_Kind + "\\InsPortDriver\\" + strKindName + "_testConfig.ini", FALSE);//拷贝引擎配置文件
	}
}

void CInsDocument::CreatModel(CString strFactory, CString strModelType, CString strReferModelPath, bool bSameKind)
{
	CPathOperate paOpe; //路径操作对象
	CString strPath_Kind=paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + m_strThreadKind + "\\TPS\\" + strFactory + " " + strModelType;
	if(strReferModelPath == "")
	{
		CreateDirectory(strPath_Kind, NULL);
		CreateDirectory(strPath_Kind + "\\Document", NULL);
		CreateDirectory(strPath_Kind + "\\Driver", NULL);
		CreateDirectory(strPath_Kind + "\\Driver\\DigMeter", NULL);
		CreateDirectory(strPath_Kind + "\\Solution", NULL);
		CreateDirectory(strPath_Kind + "\\UUTInfo", NULL);
		CXml_UUTInfo xmlUUTInfo;
		xmlUUTInfo.CreatModelInfo(m_strThreadKind, strFactory, strModelType);
	}
	else
	{
		CTool tool1;
		tool1.CopyDirectory(strReferModelPath, strPath_Kind);//拷贝文件夹
		/****修改Document****/
		//修改文件夹内所有文件的部分文件名
		CString strPath1, str1 = strReferModelPath.Right(strReferModelPath.GetLength() - strReferModelPath.ReverseFind('\\') - 1);
		strPath1 = strPath_Kind + "\\Document";
		tool1.ReplacePartNameInDirectorye(strPath1, str1, strFactory + " " + strModelType);
		//修改xml文件的根节点
		changeXMLRootName(strPath1, strFactory + "_" + strModelType);
		//修改Excel文件内的名字,是否可行?
		/******修改UUTInfo文件夹********/
		//修改文件夹内所有文件的部分文件名
		strPath1 = strPath_Kind + "\\UUTInfo";
		tool1.ReplacePartNameInDirectorye(strPath1, str1, strFactory + " " + strModelType);
		//修改xml文件根节点
		changeXMLRootName(strPath1, strFactory + "_" + strModelType);
		//修改xml文件基本信息的类型、厂商、型号
		UUTInfoSet structInfo;
		structInfo.m_strUUTKind = m_strThreadKind;
		structInfo.m_strName = m_strThreadKind;
		structInfo.m_strModel = strModelType;
		structInfo.m_strFactory = strFactory;
		CXml_UUTInfo uutinfo;
		uutinfo.WriteUUTBasicInfo(m_strThreadKind, strFactory + " " + strModelType, &structInfo);
		/***********修改Solution文件夹***************/
		//修改解决方案下TestConfig文件夹下内所有文件的部分文件名
		strPath1 = strPath_Kind + "\\Solution\\*";
		CString strPath2, str2;
		CFileFind ff, ff1, ff2;
		BOOL bF1, bFind = ff.FindFile(strPath1);
		
		CIni ini1;
		while(bFind)
		{
			bFind = ff.FindNextFile();
		
			if (ff.IsDots())
				continue;
			else if(ff.IsDirectory())
			{
				strPath2 = ff.GetFilePath() + "\\";
				bF1 = ff1.FindFile(strPath2 + "\\*");
				strPath2 += "TestConfig";

				while(bF1)
				{
					bF1 = ff1.FindNextFile();

					if(ff1.IsDots())
						continue;
					else if(ff1.IsDirectory())
					{
						if(ff1.GetFileName() == "TestConfig")
						{
							//修改解决方案下TestConfig文件夹下内所有文件的部分文件名
							tool1.ReplacePartNameInDirectorye(strPath2, str1, strFactory + " " + strModelType);
							tool1.changeXMLRootName(strPath2, strFactory + "_" + strModelType);//修改修改xml文件根节点
							tool1.ChangeSolutionIni(ff.GetFilePath(), m_strThreadKind, strFactory + " " + strModelType);//修改INI文件
							
							/*bF2 = ff2.FindFile(ff1.GetFilePath() + "\\*testConfig.ini");
							while(bF2)
							{
								bF2 = ff2.FindNextFile();
			
								if (ff2.IsDots())
									continue;
								else if(ff2.IsDirectory())
									continue;		
								else
								{
									ini1.SetINIPth(ff2.GetFilePath());
									ini1.WriteKeyValue("UUT", "InsName", m_strThreadKind);
									ini1.WriteKeyValue("UUT", "Model", strFactory + "_" + strModelType);
								}
							}*/
						}
					}
				}
			}
		}
	}
}


void CInsDocument::OnDelModel()
{
	DWORD dAfxRtn = IDNO;
	if(AfxMessageBox("确定要删除[" + m_strThreadModel + "]设备吗?",MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)==IDYES)
	{
		CPathOperate paOpe; //路径操作对象
		CString strPath_Kind=paOpe.GetStartPath() + "DataInfo\\UUTTestInfo\\" + m_strThreadKind + "\\TPS\\" + m_strThreadModel;
		CTool tool1;
		tool1.DeleteDirectorye(strPath_Kind);		
		InitTreeList();
		m_strThreadKind  = "";
		m_strThreadModel = "";
		m_dlg_Basic.UpdateBasicInfo(m_strThreadKind, m_strThreadModel);
		m_dlg_Templete.UpdataTempleteCom(m_strThreadKind, m_strThreadModel);
		m_dlg_Solution.initAll(m_strThreadKind, m_strThreadModel);
	}
}

void CInsDocument::changeXMLRootName(CString strPath, CString strRootName)
{
	CString strFileName, strFilePath;
	if ( strPath.GetAt(strPath.GetLength()-1) != '\\' )
		strPath += '\\';
	CFileFind ff;
	BOOL bFinded = ff.FindFile(strPath + "*");
	int nDirTime = 0;
	while (bFinded)
	{
		bFinded = ff.FindNextFile();
		
		if (ff.IsDots())
			continue;
		if (ff.IsDirectory())
			continue;
		else
		{
			strFilePath = ff.GetFilePath();
			if(strFilePath.Right(4) == ".xml")
			{
				CXmlFile_Ope xmlope;
				xmlope.LoadXmlFile(strFilePath);
				if(xmlope.pRootEle != NULL)
					xmlope.pRootEle->SetValue(strRootName);
				xmlope.SaveFile();
			}
		}
	}
	ff.Close();
}