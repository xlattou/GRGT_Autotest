// Tool.cpp: implementation of the CTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "Tool.h"
#include "XmlFile_Ope.h"
#include "Ini.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTool::CTool()
{

}

CTool::~CTool()
{

}

void CTool::TraverseTree(CTreeCtrl* pWndTree, CStringArray &strFatherArray, CStringArray &strChildArray)
{
	HTREEITEM hTreeItem = pWndTree->GetFirstVisibleItem();
	if(hTreeItem != NULL)
	{
		CString str1 = "";
		HTREEITEM hFatherItem = pWndTree->GetChildItem(hTreeItem);
		while(hFatherItem != NULL)
		{
			str1 = pWndTree->GetItemText(hFatherItem);
			HTREEITEM hChildItem = pWndTree->GetChildItem(hFatherItem);
			while(hChildItem != NULL)
			{
				strFatherArray.Add(str1);
				strChildArray.Add(pWndTree->GetItemText(hChildItem));
				hChildItem = pWndTree->GetNextSiblingItem(hChildItem);
			}
			hFatherItem = pWndTree->GetNextSiblingItem(hFatherItem);
		}
	}
}

// 将pc中的文件夹从一个目录拷贝到另外的一个目录
BOOL CTool::CopyDirectory(CString strSrcPath, CString strDesPath, BOOL bFailIfExists/*=FALSE*/)
{
	if( strSrcPath.IsEmpty())
		return FALSE;

	CFileFind ff;
	BOOL bFound = ff.FindFile(strDesPath);
	if(!bFound)
	{
		if (!CreateDirectory( strDesPath, FALSE) )
			return FALSE;
	}
	else
	{
		bFound = ff.FindNextFile();		
		if(!ff.IsDirectory())
		{
			if (!CreateDirectory( strDesPath, FALSE) )
				return FALSE;
		}
	}

	if ( strSrcPath.GetAt(strSrcPath.GetLength()-1) != '\\' )
		strSrcPath += '\\';
	if ( strDesPath.GetAt(strDesPath.GetLength()-1) != '\\' )
		strDesPath += '\\';

	BOOL bRet = FALSE; // 因为源目录不可能为空，所以该值一定会被修改
	bFound = ff.FindFile(strSrcPath+"*",   0);  
	while(bFound)  	// 递归拷贝
	{  
		bFound = ff.FindNextFile();  
		if( ff.GetFileName() == "." || ff.GetFileName() == ".." )  
			continue;

		CString strSubSrcPath = ff.GetFilePath();
		CString strSubDespath = strSubSrcPath;
		strSubDespath.Replace(strSrcPath, strDesPath);

		if( ff.IsDirectory() )
			bRet = CopyDirectory(strSubSrcPath, strSubDespath, bFailIfExists);     // 递归拷贝文件夹
		else
			bRet = CopyFile(strSubSrcPath, strSubDespath, bFailIfExists);   // 拷贝文件
		if ( !bRet )
			break;
	}  
	ff.Close();
	return bRet;
}

void CTool::DeleteDirectorye(CString strPath)//删除路径下所有文件
{
	DeleteDirectorye1(strPath);
	RemoveDirectory(strPath);
}

void CTool::DeleteDirectorye1(CString strPath)//删除路径下所有文件
{
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
		else if (ff.IsDirectory())
		{
			DeleteDirectorye(ff.GetFilePath());
			RemoveDirectory(ff.GetFilePath());
		}
		else
			DeleteFile(ff.GetFilePath());
	}
	ff.Close();
}

//修改路径下所有文件部分文件名
void CTool::ReplacePartNameInDirectorye(CString strPath, CString strOldPart, CString strNewPart)
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
		else
		{
			strFilePath = ff.GetFilePath();
			strFileName = ff.GetFileName();
			strFileName.Replace(strOldPart, strNewPart);
			CFile::Rename(strFilePath, strPath + strFileName);
		}
	}
	ff.Close();
}

void CTool::changeXMLRootName(CString strPath, CString strRootName)
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

void CTool::ChangeSolutionIni(CString strDirPath, CString strKind, CString strModel)
{
	int nI;
	CString str1;
	CFileFind ff;
	BOOL bF1;
	bF1 = ff.FindFile(strDirPath + "\\TestConfig\\*");
	while(bF1)
	{
		bF1 = ff.FindNextFile();
		if(ff.IsDots())
			continue;
		else if(ff.IsDirectory())
			continue;
		else
		{
			str1 = ff.GetFileName();
			if(str1.GetLength() > 15)
			{
				if(str1.Right(14) == "testConfig.ini")
				{
					CIni ini1;
					ini1.SetINIPth(ff.GetFilePath());
					CStringArray saIns;
					CStringArray saKeys;
					ini1.WriteKeyValue("UUT", "InsName", strKind);
					ini1.WriteKeyValue("UUT", "Model", strModel);

					ini1.GetSections(saIns);//获得字段列表
					for(int i = 0; i < saIns.GetSize(); i++)
					{
						str1 = ini1.GetKeyValue(saIns[i], "DriverName");//获得DriverName
						if(str1 != "")
						{
							nI = str1.ReverseFind('\\');
							if(nI >= 0)
								str1 = str1.Right(str1.GetLength() - nI -1);
							if(saIns[i] == "UUT")
								str1 = strKind + "\\TPS\\" + strModel + "\\Driver\\" + str1;
							else
								str1 = strKind + "\\InstrDriver\\" + str1;
							ini1.WriteKeyValue(saIns[i], "DriverName", str1);
						}
					}
				}
			}
		}
	}
}

void CTool::CreateLua(CString strKind, CString strModel, CString strLua)//创建Lua脚本
{
	//
}

CString CTool::CStrTorHex(CString strMsg)
{
	  CString strHex;  
	  int len=strMsg.GetLength();
	  int hexdata,lowhexdata;
	  int j=0;
	  for(int i=0;i<len;i++)
	  {
		char lstr,hstr=strMsg.GetAt(i);
		i++;
		if(i>=len)
		break;
		lstr=strMsg.GetAt(i);//取第二个值(9)

		hexdata    = CharToHexChar(hstr);//1
		lowhexdata = CharToHexChar(lstr);//2

		if((hexdata==16)||(lowhexdata==16))
		  break;
		else 
		hexdata=hexdata*16+lowhexdata;//整合1*十位+2个位
		j++;
		strHex.Insert(j,(char)hexdata);
	  }
	 
	  return strHex;
}

char CTool:: CharToHexChar(unsigned char ch)
{
   if((ch>='0')&&(ch<='9'))
	  return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
	  return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
	  return ch-'a'+10;
	else return (-1);
}

CString CTool::Hex(unsigned char *pData, int nLength)
{
	CString str,THex;
	str="";
    for(int i=0;i<nLength;i++)
	{
		if(pData[i]<16)
			THex.Format(_T("0%X"),pData[i]);
		else
			THex.Format(_T("%2X"),pData[i]);

		str+=THex;
	}
	return str;
}

BOOL CTool::CreateMultyDir(CString strPath)//创建多重路径
{
	CStringArray strPathArray;
	CString str="";
	if(strPath.Right(1) != '\\')
		strPath += "\\";

	int nI = 1;
	while(nI > 0)
	{
		nI = strPath.ReverseFind('\\');
		if(nI > 0)
		{
			strPath = strPath.Left(nI);
			strPathArray.Add(strPath);
		}
	}

	CFileFind ff;
	BOOL bFound = FALSE;
	
    for(int i = strPathArray.GetSize() - 1; i >= 0; i--)
	{
		bFound = ff.FindFile(strPathArray[i]);
		if(!bFound)
		{
			if (!CreateDirectory(strPathArray[i], FALSE) )
				return FALSE;
		}
		else
		{
			bFound = ff.FindNextFile();		
			if(!ff.IsDirectory())
			{
				if (!CreateDirectory(strPathArray[i], FALSE) )
					return FALSE;
			}
		}
	}
	return TRUE;
}

CString CTool::UINTtoString(UINT nUint)//无符号整形转换成字符串
{
	CString str1 = "";
	char ch1;
	while(nUint > 0)
	{
		ch1 = nUint % 0x100;
		str1.Insert(0, ch1);
		nUint /= 0x100;
	}
	return str1;
}
