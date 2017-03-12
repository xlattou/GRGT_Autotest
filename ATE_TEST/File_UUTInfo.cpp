// File_UUTInfo.cpp: implementation of the CFile_UUTInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "File_UUTInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFile_UUTInfo::CFile_UUTInfo()
{

}

CFile_UUTInfo::~CFile_UUTInfo()
{

}

int CFile_UUTInfo::GetUUTList(CString strKind,vector<FileInfo> *vUUTFileList)
{
	CFileFind ff;
	BOOL res=FALSE;
	FileInfo stucFileInfo;
	CString strPath_Model=GetUUTStartPath();
	strPath_Model+=strKind+"\\TPS\\*.*";
	
	res=ff.FindFile(strPath_Model);

	while(res)
	{
		res=ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots() && ff.IsDirectory())
		{
			stucFileInfo.m_strFileName=ff.GetFileTitle();
			stucFileInfo.m_strFilePath=ff.GetFilePath();
			vUUTFileList->push_back(stucFileInfo);
		}
	}
	return 1;
}

int CFile_UUTInfo::GetSolutionList(CString strKind, CString strModel, vector<FileInfo> *vSolutionFileList)
{
	CFileFind ff;
	BOOL res=FALSE;
	FileInfo stucFileInfo;
	CString strPath_Model=GetUUTStartPath();
	strPath_Model+=strKind+"\\TPS\\" + strModel + "\\Solution\\*.*";
	CString strPath1, strPath2;
	
	res=ff.FindFile(strPath_Model);

	while(res)
	{
		res=ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots() && ff.IsDirectory())
		{
			stucFileInfo.m_strFileName=ff.GetFileTitle();
			stucFileInfo.m_strFilePath=ff.GetFilePath();
			
			strPath1 = stucFileInfo.m_strFilePath + "\\TestConfig";
			strPath2 = stucFileInfo.m_strFilePath + "\\TestItem";
			if(GetFileAttributes(strPath1) == FILE_ATTRIBUTE_DIRECTORY && GetFileAttributes(strPath2) == FILE_ATTRIBUTE_DIRECTORY)
				vSolutionFileList->push_back(stucFileInfo);
		}
	}
	return 1;
}

int CFile_UUTInfo::GetDriverList(CString strKind, CString strModel, vector<FileInfo> *vDriverPathList, int nType)//获得驱动文件的列表,0:UUT驱动,1:测试工具驱动
{
	CFileFind ff, ff1;
	BOOL res=FALSE;
	FileInfo stucFileInfo;
	CString strPath_Model=GetUUTStartPath();
	if(nType)
		strPath_Model+=strKind+"\\InstrDriver\\*";
	else
		strPath_Model+=strKind+"\\TPS\\" +strModel + "\\Driver\\*";
	CString strPath1;
	
	res=ff.FindFile(strPath_Model);

	while(res)
	{
		res=ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			stucFileInfo.m_strFileName=ff.GetFileTitle();
			stucFileInfo.m_strFilePath=ff.GetFilePath();
			
			strPath1 = stucFileInfo.m_strFilePath + "\\" + stucFileInfo.m_strFileName + ".xml";
			if(ff1.FindFile(strPath1))
				vDriverPathList->push_back(stucFileInfo);
		}
	}
	return 1;
}

int CFile_UUTInfo::IsXmlFileExist(CFileFind *pff)
{
	CString strPath, //文件或文件夹所在路径
		strTitle,//文件名
		strPath_UUTXml,
		strPath_UUTXml_Set;
	int ret=0;
	if(pff->IsDirectory() && !pff->IsDots())
	{
		//如果类下的文件是一个子目录，继续找子目录中的文件		
		strPath=pff->GetFilePath();
		strTitle=pff->GetFileTitle();
		strPath_UUTXml=strPath+"\\UUTInfo\\"+strTitle+".xml";
		//strPath_UUTXml_Set=strPath+"\\UUTInfo\\"+strTitle+" 设置.xml";
		if(GetFileAttributes(strPath_UUTXml)!=-1)
		{
			ret=1;			
		}	
	}
	return ret;
}

CString CFile_UUTInfo::GetUUTStartPath()
{
		CPathOperate paOpe;
		return paOpe.GetStartPath()+"DataInfo\\UUTTestInfo\\";
}

int CFile_UUTInfo::GetFileList(CString strFoldName,CString strKind,CString strModel,vector<CString> *vFileList)
{
	CString strFilePath=GetUUTStartPath();
	strFilePath+=strKind+"\\TPS\\"+strModel+"\\"+strFoldName+"\\*.pdf";
	BOOL res=FALSE;
	CFileFind ff;
	res=ff.FindFile(strFilePath);
	while(res)
	{
		res=ff.FindNextFile();
		vFileList->push_back(ff.GetFileTitle());
	}
	return 1;
}
//搜索所有.xml文件并保存
int CFile_UUTInfo::GetModuleList(CString strKind,CString strModel,vector<CString> *vModuleList)
{
	CString strModel_Serach;
	strModel_Serach=strModel;
	strModel_Serach.Replace(" ","?");

	CString strFilePath=GetUUTStartPath();
	strFilePath+=strKind+"\\TPS\\"+strModel+"\\Document\\"+strModel_Serach+"*.xml";
	BOOL res=FALSE;
	CFileFind ff;
	res=ff.FindFile(strFilePath);
	while(res)
	{
		res=ff.FindNextFile();
		vModuleList->push_back(ff.GetFileTitle());
	}
	return 1;
}
//搜索所有.ini文件并保存
int CFile_UUTInfo::GetConfigList(CString strKind,CString strModel,vector<CString> *vConfigList)
{
	CString strModel_Serach;
	strModel_Serach=strModel;
	strModel_Serach.Replace(" ","?");
	
	CString strFilePath=GetUUTStartPath();
	strFilePath+=strKind+"\\TPS\\"+strModel+"\\UUTInfo\\"+strModel_Serach+"*.ini";
	BOOL res=FALSE;
	CFileFind ff;
	res=ff.FindFile(strFilePath);
	while(res)
	{
		res=ff.FindNextFile();
		vConfigList->push_back(ff.GetFileTitle());
	}
	return 1;
}