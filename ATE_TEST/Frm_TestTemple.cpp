// Frm_TestTemple.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "Frm_TestTemple.h"
#include "EditListCtrl.h"
#include "ReadXML.h"
#include "Xml_PointVarSet.h"
//#include "Xml_UUTItemSet.h"
#include "Xml_TestPointSet.h"
#include "ReadXML.h"
#include "XML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestTemple dialog


CFrm_TestTemple::CFrm_TestTemple(CWnd* pParent /*=NULL*/)
	: CDialog(CFrm_TestTemple::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrm_TestTemple)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFrm_TestTemple::CFrm_TestTemple(CString strKind,CString strModel,CWnd* pParent)
: CDialog(CFrm_TestTemple::IDD, pParent)
{
	m_strKind=strKind;
	m_strModel=strModel;
}

void CFrm_TestTemple::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrm_TestTemple)
	DDX_Control(pDX, IDC_TAB_TEM, m_tab_Tem);
	DDX_Control(pDX, IDC_TREE_TEMP, m_tree_temp);
//	DDX_Control(pDX, IDC_LIST2, m_testList);
//	DDX_Control(pDX, IDC_LIST3, m_testPoint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrm_TestTemple, CDialog)
	//{{AFX_MSG_MAP(CFrm_TestTemple)
//	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickListPoint)
//	ON_BN_CLICKED(IDC_BUTTON4, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON7, OnReturn)
//	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickTestItem)
//	ON_BN_CLICKED(IDC_BUTTON6, OnSave)
//	ON_BN_CLICKED(IDC_BUTTON3, OnAddUnit)
//	ON_BN_CLICKED(IDC_BUTTON1, OnNewTemp)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrm_TestTemple message handlers
BOOL CFrm_TestTemple::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_SUBFORM);
	m_brush.CreatePatternBrush(&bmp);


	m_state = NEDIT;

	CRect rs;
	m_tab_Tem.GetClientRect(&rs);
	rs.top+=20;
	rs.bottom-=1;
	rs.left+=1;
	rs.right-=2;

	m_tab_Tem.InsertItem(0,"����",0);
	m_tab_Tem.InsertItem(1,"��ҳ",1);
	m_tab_Tem.SetItemSize(CSize(130,20));

	
	m_frmFirst.Create(IDD_TEM_FIRST,&m_tab_Tem);
	m_frmContent.Create(IDD_TEM_CONTENT,&m_tab_Tem);

	m_frmFirst.MoveWindow(&rs);
	m_frmContent.MoveWindow(&rs);

	m_frmFirst.ShowWindow(TRUE);
//	m_frmContent.ShowWindow(FALSE);






	m_tab_Tem.SetCurSel(0);	





	//��ȡģ����
	InitTreeView();

	//��ȡ��ǰ�����豸���ļ���
	CPathOperate paOpe;
	CString strFilePath=paOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\"+m_strKind;
	m_pthFile = strFilePath+"\\TPS\\"+m_strModel;
	

	/*
	CRect itemRC1;
	m_testList.GetClientRect(itemRC1);
	m_testList.InsertColumn(0,"������Ŀ",LVCFMT_LEFT,itemRC1.Width());
	vector<CString> m_testCol;
	CReadXML m_readXML;
	CString strlist;
*/
	/*
	CString UUIPath = "D://ck//Agilent 34401A.xml";
	
	m_readXML.ReadXMLList(UUIPath,"ItemSet",&m_testCol);
	for(int i=0; i<m_testCol.size();i++)
	{	strlist = m_testCol[i];
		m_testList.InsertItem(i,strlist);
	}
	*/
	return true;
}

void CFrm_TestTemple::InitTreeView()
{
	
	vector <CString> vConfigList;
	m_file_UUTInfo.GetModuleList(m_strKind,m_strModel,&vConfigList);
	for(int i=0;i<vConfigList.size();i++)
	{
		m_tree_temp.InsertItem(vConfigList[i]);
	}
	
}
//void CFrm_TestTemple::OnClickListPoint(NMHDR* pNMHDR, LRESULT* pResult) 
//{
	/*
	// TODO: Add your control notification handler code here
	int n = m_testPoint.GetItemCount() -1;		//��ȡlist�����һ���к�
	int ncol = m_testPoint.GetHeaderCtrl()->GetItemCount();
	int nReady = 0;								//not Ready,û��д�� nReady =1,ûд�꣬nReady=0,��д��
	CString strlist;
	

    for(int i=0; i<ncol;i++)
	{
		strlist=m_testPoint.GetItemText(n,i);
		if(strlist=="")
			nReady=1;				//���пգ���ûд��
	}
	
	if(nReady == 0)
	{
		int j=n+1;
		m_testPoint.InsertItem(j,"");
		for(i =0; i<m_colID.nVarSet;i++)
		{	
			CString tunit =  m_testPoint.GetItemText(n,2*i+1);
			m_testPoint.SetItemText(j,2*i+1,tunit);
		}
				
		CString tUnit = m_testPoint.GetItemText(n,m_colID.Unit);
		CString tSpan = m_testPoint.GetItemText(n,m_colID.nRange);
		CString tColumn = m_testPoint.GetItemText(n,m_colID.Column);
		CString tRow = m_testPoint.GetItemText(n,m_colID.LineNum);
		CString tID = m_testPoint.GetItemText(n,m_colID.Point_ID);
		int iRow = atoi(tRow);
		iRow++;
		tRow.Format("%d",iRow);
		int iID = atoi(tID);
		iID++;
		tID.Format("%d",iID);    
		m_testPoint.SetItemText(j,m_colID.Point_ID,tID);
		m_testPoint.SetItemText(j,m_colID.Unit,tUnit);
		m_testPoint.SetItemText(j,m_colID.nRange,tSpan);	
		m_testPoint.SetItemText(j,m_colID.Column,tColumn);
	    m_testPoint.SetItemText(j,m_colID.LineNum,tRow);
	}
	//MessageBox(tListPoint);
	
	*pResult = 0;
}

void CFrm_TestTemple::OnDelete() 
{
	/*
	// TODO: Add your control notification handler code here
	POSITION pos=m_testPoint.GetFirstSelectedItemPosition();
	int n=m_testPoint.GetNextSelectedItem(pos); 
	if(n==-1)
	{
		AfxMessageBox("�����б���ѡ����Ҫɾ�����û���Ϣ");
		return;
	}
	if(AfxMessageBox("ȷ��ɾ��?",MB_OKCANCEL)==2)
		return;

	//ɾ�����б�����һ��
	int nListPoint = m_testPoint.GetItemCount() -1 ;		//��ȡlist�����һ���к�
	int nColNum = m_testPoint.GetHeaderCtrl()->GetItemCount();	//��ȡ����
	if(n == nListPoint)
	{
		CString tListPoint;
		for(int i=0;i<nColNum;i++)
			m_testPoint.SetItemText(n,i,"");
	}
	*/
//}

void CFrm_TestTemple::OnReturn() 
{
	CDialog::OnCancel();
	/*TODO: Add your control notification handler code here
	vector<TestItem> m_testCol;
	CReadXML m_readXML;
	CString strlist;
	CString UUIPath = "D://ck//Agilent 34401A.xml";
	
	m_readXML.ReadXMLThdList(UUIPath,"ItemSet","ֱ����ѹ","LogicName",&m_testCol);
	m_testList.DeleteAllItems();
	for(int i=0; i<m_testCol.size();i++)
	{	strlist = m_testCol[i].chiName;
		m_testList.InsertItem(i,strlist);
	}
	UpdateData(FALSE);*/
}

//void CFrm_TestTemple::OnOK() 
//{
	// TODO: Add extra validation here
	//MessageBox(m_testPoint.GetItemText(0,0));
	//CDialog::OnOK();

	/*

	CString val = "1";
	int lnum = m_testPoint.GetItemCount();		//��ȡlist�ؼ�������
	int pnum = 0;

	//�ж����һ���Ƿ�Ϊ�գ�
	int nColNum = m_testPoint.GetHeaderCtrl()->GetItemCount();	//��ȡ����
	int lastnull = 0;
	CString str;
	for(int i=0;i<nColNum;i++)
	{
		str = m_testPoint.GetItemText(lnum-1,i);
		if(str !="")
			lastnull = 1;
	}
	if(lastnull == 1)
		pnum = lnum;			//���һ�в�Ϊ�գ�������Ϊlist����
	else
		pnum = lnum -1 ;		//���һ��Ϊ�գ�������Ϊlist������1
		

	//��list�ؼ��еĵ���Ϣ����pset������	
	vector<TestPoint> m_pArr;
	TestPoint pset;
	CString cstand,cerror,cupper,clower;
	float flower,fstand,ferror,fupper;

	for(i=0;i<pnum;i++)
	{
		if(m_colID.nError == 1)
		{
			pset.m_Col=m_testPoint.GetItemText(i,m_colID.Column);
			pset.m_ID=m_testPoint.GetItemText(i,m_colID.Point_ID);
			pset.m_Line=m_testPoint.GetItemText(i,m_colID.LineNum);	
			pset.m_Unit=m_testPoint.GetItemText(i,m_colID.Unit);
			
			cstand = m_testPoint.GetItemText(i,m_colID.Set);
			cerror = m_testPoint.GetItemText(i,m_colID.nError);
			fstand = atof(cstand);
			ferror = atof(cerror);
			fupper = fstand + ferror;
			flower = fstand - ferror;
			cupper.Format("%f",fupper);
			clower.Format("%f",flower);
			pset.m_Upper = cupper;
			pset.m_Lower = clower;
			m_pArr.push_back(pset);
		}
	}
		
	//��list�ؼ��ж�ȡVarSet����Ϣ
	CReadXML m_readXML;
	vector<VarItem> m_vArr;
	VarItem m_vItem;				
	CString sID;
	int nVar = m_colID.nVarSet;				//��ȡVarset������
	for(int j = 0;j<pnum;j++)				//����ȡ
	{
		for(i=0; i<m_colID.nVarSet; i++)	//ÿ��ȡnVarSet��
		{
			sID.Format("%d",i+1);
			m_vItem.ID = sID;
			m_vItem.logicName = m_testCol[i].logicName;
			m_vItem.Name = m_testCol[i].chiName;
			
			m_vItem.Value = m_testPoint.GetItemText(j,2*i);
			m_vItem.Unit = m_testPoint.GetItemText(j,2*i+1);			
			m_vArr.push_back(m_vItem);
		}
	}
	
	
	//��������д��XML�ļ���
	m_pointXML.WriteXMLPoint(m_vArr,m_pArr,pnum,nVar);

  
}

void CFrm_TestTemple::OnClickTestItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	/*
	// TODO: Add your control notification handler code here
	m_state = NEDIT;

	int n = m_testList.GetSelectionMark();
	
	BOOL res=FALSE;
	CString itemNow;
	if(n>=0)
		itemNow= m_testList.GetItemText(n,0);
	else
		return;

	m_selItem = itemNow;		//��ȡѡ���Ĳ�����Ŀ

	CRect itemRC;
	m_testPoint.GetClientRect(itemRC);

	CReadXML m_readXML;
	CString strlist;
	CString UUIPath = "D://ck//Agilent 34401A.xml";

	//��ȡUUI.XML�е���Ϣ
	m_readXML.ReadXMLThdList(UUIPath,"ItemSet",itemNow,"LogicName",&m_testCol);
	int nVarSet = m_testCol.size();			//varSet�ĸ���
	m_colID.nVarSet = nVarSet;
	int otherCol = 3;
	int otherFir = nVarSet*2;

	int j=0;
	//ȷ��Ĭ������������
	for(int i=0; i<nVarSet;i++)
	{	
		strlist = m_testCol[i].chiName;
		if(strlist == "����")
			m_colID.nRange = 2*i;

		if(strlist == "���ֵ")
		{	
			m_colID.Set = 2*i;
			m_colID.error = 2*nVarSet +1;
			m_colID.Unit = m_colID.Set +1;
			m_colID.nError = 1;
			otherCol = 4;
			otherFir++;
		}
	}

	m_colID.Point_ID = otherFir;
	m_colID.Column = otherFir+1;
	m_colID.LineNum =otherFir+2;

	int nColNum = nVarSet*2+otherCol;
	int colWidth = itemRC.Width()/nColNum;
	for(i=0; i<nVarSet;i++)
	{	strlist = m_testCol[i].chiName;
		j=2*i;
		m_testPoint.InsertColumn(j++,strlist,LVCFMT_CENTER,colWidth);
		m_testPoint.InsertColumn(j++,"��λ",LVCFMT_CENTER,colWidth);
	}

	if(m_colID.nError= 1)
	{
		m_testPoint.InsertColumn(m_colID.error,"���",LVCFMT_CENTER,colWidth);
		m_testPoint.InsertColumn(m_colID.Point_ID,"���",LVCFMT_CENTER,colWidth);
		m_testPoint.InsertColumn(m_colID.Column,"�к�",LVCFMT_CENTER,colWidth);
		m_testPoint.InsertColumn(m_colID.LineNum,"�к�",LVCFMT_CENTER,colWidth);
	}

    m_testPoint.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	//��ӿ���
	m_testPoint.InsertItem(0,"");	
	//ȷ��Ĭ������������
	for(i=0; i<nVarSet;i++)
	{	strlist = m_testCol[i].chiName;
		if(strlist == "����")
			m_colID.nRange = i;
		if(strlist == "���ֵ")
		{	
			m_colID.Set = i;
			m_colID.nError = 1;
		}
	}

	m_testPoint.ShowWindow(SW_SHOW);

	int ncol = m_testPoint.GetHeaderCtrl()->GetItemCount();

	for(i=0; i<ncol;i++)
	{
		strlist=m_testPoint.SetItemText(0,i,"1");
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CFrm_TestTemple::OnSave() 
{
	// TODO: Add your control notification handler code here
/*	CXml_PointVarSet m_Xml;
	int n = m_testPoint.GetItemCount();		
	PointVarSet m_set[n];

	for(int i=0;i<n;i++)
	{
		m_set[i].m_intID=i;
		m_set[i].m_strLogicName="logicname";
		m_set[i].m_strName="����";
		m_set[i].m_strUnit="mV";
		m_set[i].m_strValue="1";
	}

	m_Xml.PointVar_Add()
}

void CFrm_TestTemple::OnAddUnit() 
{
	// TODO: Add your control notification handler code here
	
}

void CFrm_TestTemple::OnNewTemp() 
{
	/*
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	m_newTempNameDialog.DoModal();
	CString name = m_strModel +" " + m_newTempNameDialog.m_newTempName;	//��ȡINI��
	CString pth = m_pthFile + "\\Document" + "\\"+ name + ".XML" ;			//��ȡINI·��
	m_pointXML.SetXMLPth(pth);												//����INI��·��
	m_pointXML.SetXMLname(name);												//����INI������
	m_tree_temp.InsertItem(name);

	CFile file(_T(pth),CFile::modeCreate);	//����XML�ļ�*/
	//file.Close();
//}

HBRUSH CFrm_TestTemple::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return (HBRUSH)m_brush;
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
BOOL CFrm_TestTemple::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_brush.DeleteObject();
	
	if(m_frmFirst)
		m_frmFirst.DestroyWindow();
	if(m_frmContent)
		m_frmContent.DestroyWindow();
	
	
	return CDialog::DestroyWindow();
}
