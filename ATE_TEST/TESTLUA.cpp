// TESTLUA.cpp : implementation file
//

#include "stdafx.h"
#include "ate_test.h"
#include "TESTLUA.h"
#include "Edt_Lua_Pic.h"
#include "ImeHelper.h"
#include "PathOperate.h"
#include "Ini.h"
#include "XmlFile_Ope.h"
#include "TestLuaAddFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TESTLUA dialog

TESTLUA::TESTLUA(CWnd* pParent /*=NULL*/)
	: CDialog(TESTLUA::IDD, pParent)
{
	m_bDebug = false;
	m_nVScroll = 1;
	m_nHScroll = 1;
	m_strSoluDirPath = "";
	m_strSolution = "";
	m_strKind = "";
	m_strModel = "";
	m_nInsType = -1;
	m_strLuaFun = "";
}

TESTLUA::~TESTLUA()
{
	m_imageList.DeleteImageList();
	for(int i = 0; i < m_CodeInfo_Array.GetSize(); i++)
		m_CodeInfo_Array[i].strCode = "";
	m_CodeInfo_Array.RemoveAll();
}


void TESTLUA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TESTLUA)
	DDX_Control(pDX, IDC_BUTTON_TEST_LUA_INST_FUN, m_btn_Test_Lua_Ins_Fun);
	DDX_Control(pDX, IDC_EDIT_TEST_LUA_PARA, m_edt_Test_Lua_Para);
	DDX_Control(pDX, IDC_EDIT_TEST_LUA_ADDR, m_edt_Test_Lua_Addr);
	DDX_Control(pDX, IDC_COMBO_TEST_LUA_SERI, m_com_Test_Lua_Seri);
	DDX_Control(pDX, IDC_COMBO_TEST_LUA_MODE, m_com_Test_Lua_Mode);
	DDX_Control(pDX, IDC_STATIC_LUA_NAME, m_stc_Lua_Name);
	DDX_Control(pDX, IDC_EDIT_LUA_FUNC_DISC, m_edt_Lua_Fun_Disc);
	DDX_Control(pDX, IDC_STATIC_ENGINE_FUNC, m_stc_Engine_Func);
	DDX_Control(pDX, IDC_STATIC_OUTPUT, m_group_Output);
	DDX_Control(pDX, IDC_TREE_LUA_FUNC, m_tree_Lua_Func);
	DDX_Control(pDX, IDC_STATIC_VATIANT, m_stc_Variant);
	DDX_Control(pDX, IDC_STATIC_DEBUG, m_stc_Debug);
	DDX_Control(pDX, IDC_LIST_VARIANT, m_list_Variant);
	DDX_Control(pDX, IDC_EDIT_OUT_PUT, m_edt_Lua_Output);
	DDX_Control(pDX, IDC_STATIC_LUA_TEXT, m_Lua_Text);
	DDX_Control(pDX, IDC_STATIC_LUA_SYMBOL, m_Lua_Symbol);
	DDX_Control(pDX, IDC_SCROLLBAR_LUA_VSCROLL, m_scroll_V);
	DDX_Control(pDX, IDC_SCROLLBAR_LUA_HSCROLL, m_scroll_H);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TESTLUA, CDialog)
	//{{AFX_MSG_MAP(TESTLUA)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_COMMAND(IDR_LUA_SAVE, OnLuaSave)
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(NM_CLICK, IDC_TREE_LUA_FUNC, OnClickTreeLuaFunc)
	ON_BN_CLICKED(IDC_BUTTON_TEST_LUA_INST_FUN, OnButtonTestLuaInstFun)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TESTLUA message handlers

void TESTLUA::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect1;
	GetClientRect(rect1);
	bool bResize = false;
	if(rect1.Height() < 300)
	{
		bResize = true;
		rect1.bottom = rect1.top + 300;
	}
	if(rect1.Width() < 400)
	{
		bResize = true;
		rect1.right = rect1.left + 300;
	}
	if(bResize)
	{
		int nXScreen = GetSystemMetrics(SM_CXSCREEN); //��Ļ�ֱ���X��ֵ
		int nYScreen = GetSystemMetrics(SM_CYSCREEN); //Y��ֵ
		nXScreen = (nXScreen - rect1.Width()) / 2;
		nYScreen = (nYScreen - rect1.Height()) / 2;
		MoveWindow(rect1.left + nXScreen, rect1.top + nYScreen, rect1.Width(), rect1.Height(), TRUE);
		Invalidate(TRUE);
		GetClientRect(rect1);
	}
	int nX = rect1.Width() - 15;
	int nY = rect1.Height() - 158;
	if(IsWindow(m_tree_Lua_Func))
		m_tree_Lua_Func.MoveWindow(1, 182, 200, nY - 267);
	if(IsWindow(m_edt_Lua_Fun_Disc))
		m_edt_Lua_Fun_Disc.MoveWindow(1, nY - 85, 200, 99);


	if(IsWindow(m_Lua_Symbol))
		m_Lua_Symbol.MoveWindow(205, 18, 50, nY - 18);
	if(IsWindow(m_Lua_Text))
		m_Lua_Text.MoveWindow(255, 18, nX - 255, nY - 18);
	if(IsWindow(m_scroll_V))
		m_scroll_V.MoveWindow(nX, 18, 15, nY - 18);
	if(IsWindow(m_scroll_H))
		m_scroll_H.MoveWindow(205, nY, nX - 205, 15);

	nX = rect1.Width() / 2 - 3;
	nY += 18;
	if(IsWindow(m_group_Output))
		m_group_Output.MoveWindow(0, nY- 10, rect1.Width(), 150);
	if(IsWindow(m_stc_Variant))
		m_stc_Variant.MoveWindow(5, nY, 80, 16);
	if(IsWindow(m_stc_Debug))
		m_stc_Debug.MoveWindow(nX + 6, nY, 120, 16);
	nY += 16;
	if(IsWindow(m_edt_Lua_Output))
		m_edt_Lua_Output.MoveWindow(nX + 3, nY, nX, 121);
	if(IsWindow(m_list_Variant))
	{
		m_list_Variant.MoveWindow(2, nY, nX, 121);
		nX -= 21;
		nX /= 3;
		m_list_Variant.SetColumnWidth(0, 200);
		m_list_Variant.SetColumnWidth(1, 200);
		m_list_Variant.SetColumnWidth(2, 200);
	}
}

BOOL TESTLUA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ShowWindow(SW_SHOWMAXIMIZED);
	
	ModifyStyle(NULL, WS_THICKFRAME);
	m_scroll_H.SetScrollRange(1, m_nHScroll);
	m_scroll_V.SetScrollRange(1, m_nVScroll);

	m_list_Variant.InsertColumn(0, "����", LVCFMT_LEFT, 100);
	m_list_Variant.InsertColumn(1, "ֵ", LVCFMT_LEFT, 100);
	m_list_Variant.InsertColumn(2, "����", LVCFMT_LEFT, 100);
	int nI = m_strPath.ReverseFind('\\');
	if(nI > 0)
		m_stc_Lua_Name.SetWindowText(m_strPath.Right(m_strPath.GetLength() - nI - 1));
	m_edt_Test_Lua_Addr.SetWindowText("GPIB0::22::INSTR");
	m_edt_Test_Lua_Para.SetWindowText("LevelSet=0_V;LevelRange=100_mV;Freq=1_kHz;Result=��V");
	m_com_Test_Lua_Seri.SetCurSel(0);
	m_com_Test_Lua_Mode.SetCurSel(0);
	
	//ͼ���б�
	HICON hIcon[2];
	m_imageList.Create(16,16,ILC_COLOR32|ILC_MASK,2,2);
	hIcon[0]=AfxGetApp()->LoadIcon(IDI_ICON11);
	hIcon[1]=AfxGetApp()->LoadIcon(IDI_ICON10);
	m_imageList.Add(hIcon[0]);
	m_imageList.Add(hIcon[1]);

	ReadLua();
	ReadEngineFun();//��ȡ���溯��
	initEngineFunTree();//��ʼ�����溯�����ؼ�

	SetTimer(1, 50, NULL);
	SetTimer(2, 600000, NULL);
	
	return TRUE;
}

BOOL TESTLUA::ReadLua()
{
	CFileStatus status;
	if(!CFile::GetStatus(m_strPath, status))
		return FALSE;
	CFile file1;
	file1.Open(m_strPath, CFile::modeRead);
	file1.GetStatus(status);
	long nL = status.m_size;
	
	char* charLua = new char[nL + 1];
	char  charTemp[1000];

	file1.SeekToBegin();
	file1.Read(charLua, nL);
	file1.Close();

	if(*(charLua + nL - 1) != 10)//�����ļ��޻��н�β����ӻ��н�β
	{
		*(charLua + nL) = 10;
		nL += 1;
	}

	codeinfo codeinfo1;
	codeinfo1.bIsDebug = false;
	codeinfo1.bIsBreak = false;
	long nI = 0;
	m_CodeInfo_Array.RemoveAll();
	for(long i = 0; i < nL; i++)
	{
		if(*(charLua + i) == 10)
		{
			for(int j = 0; j < 1000; j++)
				charTemp[j] = 0;
			memcpy(charTemp, charLua + nI, i - nI);
			codeinfo1.strCode = charTemp;
			codeinfo1.strCode.Remove('\n');			
			codeinfo1.strCode.Replace("\t", "    ");
			m_CodeInfo_Array.Add(codeinfo1);
			nI = i + 1;
		}
	}

	return TRUE;
}

BOOL TESTLUA::WriteLua()
{
	return TRUE;
	
}

void TESTLUA::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int pos1, pos = m_scroll_V.GetScrollPos();    // ��ȡˮƽ��������ǰλ��
	pos1 = pos;
  
    switch (nSBCode)    
    { 
        case SB_LINEUP:// ������Ϲ���һ�У���pos��1
            pos -= 1;    
            break;
        case SB_LINEDOWN:// ������¹���һ�У���pos��1      
            pos  += 1;    
            break;
        case SB_PAGEUP:// ������Ϲ���һҳ����pos��10      
            pos -= 10;    
            break; 
        case SB_PAGEDOWN:// ������¹���һҳ����pos��10     
            pos  += 10;    
            break;
        case SB_TOP:// ������������϶ˣ���posΪ1    
            pos = 1;    
            break;
        case SB_BOTTOM:// ������������¶�   
            pos = m_nVScroll;    
            break;
        case SB_THUMBPOSITION:// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ    
            pos = nPos;
            break;    
        default:   
            return;    
    }
	if(pos < 1)
		pos = 1;
	if(pos > m_nVScroll)
		pos = m_nVScroll;
    m_scroll_V.SetScrollPos(pos);
	if(pos != pos1)
	{
		m_Lua_Symbol.setScreenPoseV(pos);
		m_Lua_Text.setScreenPoseV(pos);
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void TESTLUA::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int pos1, pos = m_scroll_H.GetScrollPos();    // ��ȡˮƽ��������ǰλ��
	pos1 = pos;
  
    switch (nSBCode)    
    { 
        case SB_LINEUP:// ����������һ�У���pos��1
            pos -= 1;    
            break;
        case SB_LINEDOWN:// ������ҹ���һ�У���pos��1      
            pos  += 1;    
            break;
        case SB_PAGEUP:// ����������һҳ����pos��10      
            pos -= 10;    
            break; 
        case SB_PAGEDOWN:// ������ҹ���һҳ����pos��10     
            pos  += 10;    
            break;
        case SB_TOP:// �������������ˣ���posΪ1    
            pos = 1;    
            break;
        case SB_BOTTOM:// ������������Ҷ�    
            pos = m_nHScroll;    
            break;
        case SB_THUMBPOSITION:// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ    
            pos = nPos;    
            break;    
        default:   
            return;    
    }
	if(pos < 1)
		pos = 1;
	if(pos > m_nHScroll)
		pos = m_nHScroll;
    m_scroll_H.SetScrollPos(pos);
	if(pos != pos1)
		m_Lua_Text.setScreenPoseH(pos);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void TESTLUA::OnVScrollCus(int nSBCode)
{
	int pos1, pos = m_scroll_V.GetScrollPos();    // ��ȡˮƽ��������ǰλ��
	pos1 = pos;
	pos += nSBCode;
	
	if(pos < 1)
		pos = 1;
	if(pos > m_nVScroll)
		pos = m_nVScroll;
    m_scroll_V.SetScrollPos(pos);
	
	if(pos != pos1)
	{
		m_Lua_Symbol.setScreenPoseV(pos);
		m_Lua_Text.setScreenPoseV(pos);
	}
}

void TESTLUA::OnHScrollCus(int nSBCode)
{
	int pos1, pos = m_scroll_H.GetScrollPos();    // ��ȡˮƽ��������ǰλ��
	pos1 = pos;
	pos += nSBCode;
	
	if(pos < 1)
		pos = 1;
	if(pos > m_nHScroll)
		pos = m_nHScroll;
    m_scroll_H.SetScrollPos(pos);
	if(pos != pos1)
		m_Lua_Text.setScreenPoseH(pos);

}

void TESTLUA::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		static int nTimes = 0;
		m_Lua_Text.Invalidate(TRUE);
		m_Lua_Symbol.Invalidate(TRUE);
		nTimes++;
		if(nTimes >= 20)
		{
			m_Lua_Text.ChangeCursorFlashState();
			nTimes = 0;
		}
	}
	if(nIDEvent == 2)
	{
		KillTimer(2);
		if(MessageBox("���ڱ���ѡ���ǡ�����ʱ������ѡ����","10���ӱ���Lua�ű���ʾ",MB_YESNO)==IDYES)
			OnLuaSave();
		else
			SetTimer(2, 600000, NULL);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void TESTLUA::OnLuaSave() 
{
	KillTimer(2);
	CString strDir;
	int nI = m_strPath.ReverseFind('\\');
	if(nI <= 0)
	{
		AfxMessageBox("����Lua�ű�ʧ��, ·������ȷ, �븴�����޸ĵ�����, �����´򿪸�Lua�ű�!");
		return;
	}
	CFile file1;
	if(!file1.Open(m_strPath, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("����Lua�ű�ʧ��, ����������Զ���ʽ��, �رո����!");
		return;
	}
	
	file1.SeekToBegin();
	int nLen;
	const char chReturn[1] = {10};
	for(int i = 0; i < m_CodeInfo_Array.GetSize(); i++)
	{
		nLen = m_CodeInfo_Array[i].strCode.GetLength();
		file1.Write(m_CodeInfo_Array[i].strCode, nLen);
		//file1.Seek(nLen, CFile::current);
		file1.Write(chReturn, 1);
		//file1.Seek(1, CFile::current);
	}
	file1.Close();
	AfxMessageBox("�ű�����ɹ�");
	SetTimer(2, 600000, NULL);
}

BOOL TESTLUA::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_CHAR )
		return FALSE;
	if (pMsg->message == WM_KEYDOWN)
    {
		if(pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
		else if(pMsg->wParam == VK_F3)
		{
			OnLuaSave();//F3�����±���
			return TRUE;
		}
		else if(pMsg->wParam == VK_F5)
		{
			//F5�����µ���
			return TRUE;
		}
		else if(pMsg->wParam == VK_F10)
		{
			//F10��������������
			return TRUE;
		}
		if(GetDlgItem(IDC_STATIC_LUA_TEXT) != GetFocus())
			return FALSE;
		if(GetKeyState(VK_CONTROL) < 0)
		{
			if(GetKeyState(VK_SHIFT) < 0)//���뷨�л�
			{
				ImeHelper imee;
				int i = imee.CurrentIndex();
				i = imee.RollTypeWriting();
				return TRUE;//����,��������
			}
			else if(pMsg->wParam == 'C' || pMsg->wParam == 'c')
			{
				m_Lua_Text.CodeCopy();//����
				return TRUE;//����,��������
			}
			else if(pMsg->wParam == 'V' || pMsg->wParam == 'v')
			{
				m_Lua_Text.CodePaste();//����
				return TRUE;//����,��������
			}
			else if(pMsg->wParam == 'X' || pMsg->wParam == 'x')
			{
				m_Lua_Text.CodeCut();//����
				return TRUE;//����,��������
			}
		}
		if(pMsg->wParam == VK_BACK)
		{
			m_Lua_Text.BackspaceText();//�˸������
			return TRUE;
		}
		else if(pMsg->wParam == VK_DELETE)
		{
			m_Lua_Text.DeleteText();//ɾ��������
			return TRUE;
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			m_Lua_Text.ReturnText();//�س�������
			return TRUE;
		}
		else if(pMsg->wParam == VK_TAB)
		{
			m_Lua_Text.InsertText("    ");//Tab��
			return TRUE;
		}
		else if(pMsg->wParam == VK_HOME)
		{
			m_Lua_Text.HomeText();//Home������
			return TRUE;
		}		
		else if(pMsg->wParam == VK_END)
		{
			m_Lua_Text.EndText();//End������
			return TRUE;
		}
		else if (pMsg->wParam == VK_DOWN)
		{
			m_Lua_Text.DownText();//���¼�����
			return TRUE;
		}
		else if (pMsg->wParam == VK_RIGHT)
		{
			m_Lua_Text.RightText();//���Ҽ�����
			return TRUE;
		}
		else if (pMsg->wParam == VK_LEFT)
		{
			m_Lua_Text.LeftText();//���������
			return TRUE;
		}
		else if (pMsg->wParam == VK_UP)
		{
			m_Lua_Text.UpText();//���ϼ�����
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL TESTLUA::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	zDelta /= - 100;
	int n1, nV = m_scroll_V.GetScrollPos();
	if(zDelta > 0)
	{
		if(nV >= m_nVScroll)
			return TRUE;
		n1 = nV + zDelta;
		if(n1 > m_nVScroll)
			n1 = m_nVScroll;
	}
	else if(zDelta < 0)
	{
		if(nV <= 1)
			return TRUE;
		n1 = nV + zDelta;
		if(n1 < 1)
			n1 = 1;
	}
	else
		return TRUE;
	m_scroll_V.SetScrollPos(n1);
	m_Lua_Symbol.setScreenPoseV(n1);
	m_Lua_Text.setScreenPoseV(n1);

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void TESTLUA::ReadEngineFun()
{
	CPathOperate pathope;
	m_strUUInfoPath = pathope.GetStartPath() + "DataInfo\\UUTTestInfo";
	//��ȡ�����ļ�
	CString m_strEngineINIPath = m_strUUInfoPath + "\\" + m_strKind + "\\InsPortDriver\\" + m_strKind + "_testConfig.ini";
	CString m_strTestConfigINIPath = m_strUUInfoPath + "\\" + m_strKind + "\\TPS\\" + m_strModel + "\\Solution\\" + m_strSolution + "\\TestConfig\\" + m_strModel + " testConfig.ini";
	CFileFind findfile;
	if(!findfile.FindFile(m_strEngineINIPath))//��������������ļ��Ƿ����,���������,����
	{
		AfxMessageBox("��������������ļ�������,�����!\r\n�ļ�·��:" + m_strEngineINIPath);
		return;
	}
	if(!findfile.FindFile(m_strTestConfigINIPath))//���������������ļ��Ƿ����,���������,�����ļ�
	{
		AfxMessageBox("���������ļ�������,�����!\r\n�ļ�·��:" + m_strEngineINIPath);
		return;
	}

	CIni ini1, ini2;
	ini1.SetINIPth(m_strEngineINIPath);//��ʼ���������豸
	ini2.SetINIPth(m_strTestConfigINIPath);//��ʼ�������豸
	CStringArray saIns;
	CStringArray saKeys;
	CString strPath, str1, str2;
	ini1.GetSections(saIns);//����ֶ��б�

	for(int i = 0; i < saIns.GetSize(); i++)//�������溯���ؼ���,д�����溯��
	{
		TestLuaInstr testluainst;
		saKeys.RemoveAll();
		ini1.GetKeys(saKeys, saIns[i]);
		testluainst.strInsType = saIns[i];
		testluainst.strInsName = ini1.GetKeyValue(saIns[i], "InsName");
		testluainst.strInsName += " " + ini2.GetKeyValue(saIns[i], "Model");
		testluainst.strDriverName = ini2.GetKeyValue(saIns[i], "DriverName");
		testluainst.testLuaFun = NULL;
		strPath = "";
		if(testluainst.strDriverName != "")
		{
			str1 = m_strUUInfoPath + "\\" + testluainst.strDriverName + testluainst.strDriverName.Right(testluainst.strDriverName.GetLength() - testluainst.strDriverName.ReverseFind('\\')) + ".xml";
			CFileFind ff;
			BOOL bFind = ff.FindFile(str1);
			if(bFind)
			{
				CXmlFile_Ope xmlope;//����dll�Ĺ����б��ļ�
				xmlope.LoadXmlFile(str1);
				if(xmlope.pRootEle != NULL)
				{
					TiXmlElement *EleTemp = xmlope.pRootEle->FirstChildElement("dllName");//���dll�ļ�
					if(EleTemp != NULL)
						EleTemp = EleTemp->FirstChildElement();
					else
						return;
					if(EleTemp != NULL)
					{
						strPath = EleTemp->Value();
						strPath.Replace(".dll", ".h");
					}
				}
			}
			else
				AfxMessageBox("δ�ҵ����������ļ�,���������!\r\n�ļ�·��:" + str1);
		}
		CStringArray strFunArray;
		CStringArray strDiscribArray;
		CStringArray strParaArray;
		int n1, n2;
		if(strPath.Right(2) == ".h")//���ͷ�ļ��ڵĺ���
		{
			strPath = str1.Left(str1.ReverseFind('\\') + 1) + strPath;//���ͷ�ļ�·��
			CFileStatus status;
			if(CFile::GetStatus(strPath, status))
			{
				CFile file1;
				file1.Open(strPath, CFile::modeRead);
				file1.GetStatus(status);
				long nL = status.m_size;
				
				char* charLua = new char[nL + 1];
				char  charTemp[1000];
				
				file1.SeekToBegin();
				file1.Read(charLua, nL);				
				file1.Close();
				if(*(charLua + nL - 1) != 10)//�����ļ��޻��н�β����ӻ��н�β
				{
					*(charLua + nL) = 10;
					nL += 1;
				}
				
				long nI = 0;
				for(long l = 0; l < nL; l++)
				{
					if(*(charLua + l) == 10)
					{
						for(int m = 0; m < 1000; m++)
							charTemp[m] = 0;
						memcpy(charTemp, charLua + nI, l - nI);
						str1 = charTemp;
						str1.Remove('\n');			
						str1.Replace("\t", "    ");
						n1 = str1.Find(" __stdcall ");
						if(n1 >= 0)
						{
							n1 += 11;
							n2 = str1.Find("(", n1);
							if(n2 >= 0)
							{
								strDiscribArray.Add(str1);
								strParaArray.Add(str1.Mid(n2 + 1));
								str1 = str1.Mid(n1).Left(n2 - n1);
								str1.Remove(' ');
								strFunArray.Add(str1);
							}
						}
						nI = l + 1;
					}
				}
			}
			else
				AfxMessageBox("δ�ҵ���������ͷ�ļ�,���������!\r\n�ļ�·��:" + str1);
		}
		for(int j = 0; j < saKeys.GetSize(); j++)
		{
			if(saKeys[j] == "InsName" || saKeys[j] == "Model" || saKeys[j] == "Address" || saKeys[j] == "Channel" || saKeys[j] == "DriverName")
				continue;
			TestLuaFun *Fun = NULL;
			Fun = testluainst.testLuaFun;
			if(Fun == NULL)
			{
				testluainst.testLuaFun = new TestLuaFun;
				Fun = testluainst.testLuaFun;
				Fun->next = NULL;
			}
			else
			{
				while(Fun->next != NULL)
					Fun = Fun->next;
				Fun->next = new TestLuaFun;
				Fun = Fun->next;
				Fun->next = NULL;
			}
			Fun->strEngineFunName = saKeys[j];
			Fun->strParaArray = new CStringArray;
			str1 = ini2.GetKeyValue(saIns[i], saKeys[j]);
			str1 = str1.Right(str1.GetLength() - str1.ReverseFind('>') - 1);
			Fun->strTestFunName = str1;
			if(str1 != "")
			{
				for(int k = 0; k < strFunArray.GetSize(); k++)
				{
					if(str1 == strFunArray[k])
					{	
						Fun->strTestFunDescibe = strDiscribArray[k];
						str1 = strParaArray[k];
						while(str1 != "")
						{
							n1 = str1.Find(",");
							if(n1 >= 0)
							{
								Fun->strParaArray->Add(str1.Left(n1));
								str1 = str1.Mid(n1 + 1);
							}
							else
							{
								n1 = str1.Find(")");
								if(n1 >= 0)
								{
									str2 = str1.Left(n1);
									/*int nn = 0;
									for(int t1 = 0; t1 < str2.GetLength(); t1++)
									{
										if(str2[t1] != ' ')
											break;
										nn++;
									}
									str2.Delete(0, nn);*/
									Fun->strParaArray->Add(str2);
								}
								str1 = "";
							}
						}
						break;
					}
				}
			}
		}
		if(saIns[i] == "UUT")//�����ֶ�UUT
			m_TestInstructionArray.InsertAt(0, testluainst);
		else
			m_TestInstructionArray.Add(testluainst);
	}
}

void TESTLUA::initEngineFunTree()
{
	m_tree_Lua_Func.DeleteAllItems();
	m_tree_Lua_Func.SetImageList(&m_imageList, TVSIL_NORMAL);
	HTREEITEM hItem;
	for(int i = 0; i < m_TestInstructionArray.GetSize(); i++)
	{
		hItem = m_tree_Lua_Func.InsertItem(m_TestInstructionArray[i].strInsName,0,0);
		TestLuaFun* testfun = m_TestInstructionArray[i].testLuaFun;
		while(testfun != NULL)
		{
			m_tree_Lua_Func.InsertItem(testfun->strEngineFunName, 1, 1, hItem);
			testfun = testfun->next;
		}
	}
}

void TESTLUA::OnClickTreeLuaFunc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_tree_Lua_Func;
	ASSERT_VALID(pWndTree);

	CString strIns,strFun;

	CPoint point;
	point.x = -1;
	point.y = -1;
	GetCursorPos(&point);
	CString str1;
	CString strDisc = "";

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);
		//pWndTree->ClientToScreen(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		HTREEITEM hTreeItemParent = NULL;
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			if (hTreeItem != NULL)
			{
				str1 = pWndTree->GetItemText(hTreeItem);
				hTreeItemParent = pWndTree->GetParentItem(hTreeItem);
				
				if (hTreeItemParent != NULL)
				{
					strIns  = pWndTree->GetItemText(hTreeItemParent);
					strFun = str1;
					hTreeItem = hTreeItemParent;
					m_btn_Test_Lua_Ins_Fun.SetWindowText("��Ӻ������ű�");
				}
				else
				{
					strIns  = str1;
					strFun = "";
					m_btn_Test_Lua_Ins_Fun.SetWindowText("װ��ʵ�������ű�");
				}
			}
			else
			{
				strIns  = "";
				strFun = "";
			}
			int n1 = 0;
			while(hTreeItem != NULL)
			{
				hTreeItem = m_tree_Lua_Func.GetNextSiblingItem(hTreeItem);
				n1++;
			}
			n1 = m_TestInstructionArray.GetSize() - n1;
			strDisc = "����:" + m_TestInstructionArray[n1].strInsType + ";\r\n�ͺ�:" + m_TestInstructionArray[n1].strInsName;
			m_nInsType = n1;
			m_strLuaFun = strFun;
			if(strFun != "")
			{
				CString m_strLuaFun;
				TestLuaFun *testfun = m_TestInstructionArray[n1].testLuaFun;
				while(testfun != NULL)
				{
					if(strFun == testfun->strEngineFunName)
					{
						strDisc += ";\r\n�⺯��:" + testfun->strTestFunDescibe;
						break;
					}
					testfun = testfun->next;
				}
			}
			m_edt_Lua_Fun_Disc.SetWindowText(strDisc);
		}
	}
	*pResult = 0;
}

void TESTLUA::OnButtonTestLuaInstFun() 
{
	if(m_nInsType < 0)
	{
		AfxMessageBox("��ѡ��һ���豸���豸��һ������!");
		return;
	}

	CString str1 = "";

	if(m_strLuaFun == "")//�豸ʵ�������ű�
	{
		str1 = "    local my" + m_TestInstructionArray[m_nInsType].strInsType + "="
			+ m_TestInstructionArray[m_nInsType].strDriverName.Right(m_TestInstructionArray[m_nInsType].strDriverName.GetLength() - m_TestInstructionArray[m_nInsType].strDriverName.ReverseFind('\\') - 1)
			+ "(" + '"' + m_TestInstructionArray[m_nInsType].strInsType + '"' + "," + "myShare)"
			+ "--ʵ����" + m_TestInstructionArray[m_nInsType].strInsName + "�����";
	}
	else//��Ӻ�����
	{
		TestLuaFun* luaFun = m_TestInstructionArray[m_nInsType].testLuaFun;
		while(luaFun != NULL)
		{
			if(luaFun->strEngineFunName == m_strLuaFun)
			{
				TestLuaAddFun addfun;
				addfun.m_strInsType = m_TestInstructionArray[m_nInsType].strInsType;//�豸����
				addfun.m_strEngineFunName = luaFun->strEngineFunName;//���溯������
				addfun.m_strTestFunDescibe = luaFun->strTestFunDescibe;//��������
				addfun.m_strParaArray.RemoveAll();//�����б�
				for(int i = 0; i < luaFun->strParaArray->GetSize(); i++)
					addfun.m_strParaArray.Add(luaFun->strParaArray->GetAt(i));
				addfun.DoModal();
				if(addfun.m_bGetPara)
				{
					str1 =  "my" + m_TestInstructionArray[m_nInsType].strInsType + ":" + luaFun->strEngineFunName +"(";
					for(int i = 0; i < addfun.m_strGetParaArray.GetSize(); i++)
						str1 += addfun.m_strGetParaArray[i] + ",";
					if(str1.Right(1) == ",")
						str1 = str1.Left(str1.GetLength() - 1);
					str1 += ")";
					str1 += "--";
					str1 += luaFun->strTestFunDescibe;
				}
				break;
			}
		}
	}
	if(str1 != "")
		m_Lua_Text.InsertText(str1);
}

void TESTLUA::OnClose() 
{
	KillTimer(2);
	int nRtn = MessageBox("�����˳�ѡ���ǡ���������ֱ���˳�ѡ����","Lua�ű��رձ�����ʾ",MB_YESNOCANCEL);
	if(nRtn == IDYES)
		OnLuaSave();
	else if(nRtn == IDCANCEL)
	{
		SetTimer(2, 600000, NULL);
		return;
	}
	
	CDialog::OnClose();
}
