// ModifyAdvise.cpp : implementation file
//

#include "stdafx.h"
#include "ATE_TEST.h"
#include "ModifyAdvise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyAdvise dialog


CModifyAdvise::CModifyAdvise(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyAdvise::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyAdvise)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModifyAdvise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyAdvise)
	DDX_Control(pDX, IDC_LIST_Reason, m_list_reason);
	DDX_Control(pDX, IDC_TREE_TPS, m_tree_tps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyAdvise, CDialog)
	//{{AFX_MSG_MAP(CModifyAdvise)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_TREE_TPS, OnClickTreeTps)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_EASYSIZE_MAP(CModifyAdvise)

EASYSIZE(IDC_TREE_TPS,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_BORDER,0)
EASYSIZE(IDC_LIST1,ES_BORDER,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0)
EASYSIZE(IDC_EDIT1,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)

END_EASYSIZE_MAP

/////////////////////////////////////////////////////////////////////////////
// CModifyAdvise message handlers

BOOL CModifyAdvise::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
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
	InitTreeList();

	m_hItem=NULL;



	INIT_EASYSIZE;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifyAdvise::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	UPDATE_EASYSIZE;
	
}

void CModifyAdvise::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	EASYSIZE_MINSIZE(150,100,fwSide,pRect);	
	
}

BOOL CModifyAdvise::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	if(m_imageList)
		m_imageList.DeleteImageList();
	
	return CDialog::DestroyWindow();
}

HBRUSH CModifyAdvise::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CModifyAdvise::InitTreeList()
{
	try
	{
		HTREEITEM hItem,hItem2,hItem3;
		vector <UUTKindList> vKindList;
		vector <FileInfo> vUUTList;
		CString strKindName,strModel;
		vector<stuFaultInfo> vFltList;
		
		
		m_bll_UUTKind.GetKindList(&vKindList);  //读取型号列表
		for(int i=0;i<vKindList.size();i++)
		{
			strKindName=vKindList[i].m_strKindName;
			hItem=m_tree_tps.InsertItem(strKindName,2,2);
			m_tree_tps.SetItemData(hItem,vKindList[i].m_intID);
			m_UUTInfo.GetUUTList(strKindName,&vUUTList);
			for(int j=0;j<vUUTList.size();j++)
			{
				strModel=vUUTList[j].m_strFileName;
				hItem2=m_tree_tps.InsertItem(vUUTList[j].m_strFileName,1,1,hItem);	
				m_bll_FaultInfo.GetFaultList(strKindName,strModel,&vFltList);
				for(int k=0;k<vFltList.size();k++)
				{
				    hItem3=m_tree_tps.InsertItem(vFltList[k].m_strName,3,3,hItem2);
					m_tree_tps.SetItemData(hItem3,vFltList[k].m_intID);
				}
				vFltList.clear();
			}
			vUUTList.clear();
		}
	}
	catch(char* e)
	{
		MessageBox(e);
	}
}

void CModifyAdvise::OnClickTreeTps(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POINT pt=GetCurrentMessage()->pt;
	m_tree_tps.ScreenToClient(&pt);
	UINT uFlags=0;
	HTREEITEM hItem=m_tree_tps.HitTest(pt,&uFlags);
	CString strKind,strModel;
	int intFltID;
	vector<stuFaultReason> vReasonList;
	CString strID;

	if((hItem!=NULL)&&(TVHT_ONITEM&uFlags))
	{
		if(hItem!=NULL&&m_tree_tps.GetParentItem(hItem)!=NULL&&m_tree_tps.GetParentItem(m_tree_tps.GetParentItem(hItem))!=NULL)
		{
			//如果选中第三层，即故障层
			if(hItem==m_hItem)
				return;
			try
			{
				InitListView();
				m_list_reason.DeleteAllItems();
				intFltID=m_tree_tps.GetItemData(hItem);
				strModel=m_tree_tps.GetItemText(m_tree_tps.GetParentItem(hItem));
				strKind=m_tree_tps.GetItemText(m_tree_tps.GetParentItem(m_tree_tps.GetParentItem(hItem)));
				m_bll_FaultReason.GetModifyReasonList(m_bll_FaultInfo.GetFaultNode(strKind,strModel,intFltID),&vReasonList);
				m_bll_FaultReason.SortReasonList(&vReasonList);
				for(int i=0;i<vReasonList.size();i++)
				{
					strID.Format("%d",i+1);
					m_list_reason.InsertItem(i,strID);
					m_list_reason.SetItemText(i,1,vReasonList[i].m_strCardName);  //插入板卡名称
					m_list_reason.SetItemText(i,2,vReasonList[i].m_strFactor);
					m_list_reason.SetItemText(i,3,vReasonList[i].m_strDescription);
				}
				m_hItem=hItem;
			}
			catch(char* e)
			{
				MessageBox(e);
			}
		}
	}
	*pResult = 0;
}

void CModifyAdvise::InitListView()
{
	int intRefWidth=800;
	while(m_list_reason.DeleteColumn(0)); //删除列表空间的列
	m_list_reason.InsertColumn(0,"序号",LVCFMT_LEFT,intRefWidth/15);
	m_list_reason.InsertColumn(1,"故障模块",LVCFMT_LEFT,intRefWidth/7);
	m_list_reason.InsertColumn(2,"故障概率(%)",LVCFMT_LEFT,intRefWidth/8);
	m_list_reason.InsertColumn(3,"故障描述",LVCFMT_LEFT,intRefWidth/3);
}


void CModifyAdvise::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CSetUser dlg_User(this);
	dlg_User.DoModal();
	
}
