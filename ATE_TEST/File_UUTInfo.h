// File_UUTInfo.h: interface for the CFile_UUTInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE_UUTINFO_H__AF980DC3_C717_43E6_A201_591ADA8EE6EB__INCLUDED_)
#define AFX_FILE_UUTINFO_H__AF980DC3_C717_43E6_A201_591ADA8EE6EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PathOperate.h"

using namespace std;
//UUT文件信息
struct FileInfo
{
	CString m_strFileName;
	CString m_strFilePath;
	CString m_strFileName_Set;
};


class CFile_UUTInfo  
{
public:
	int GetFileList(CString strFoldName,CString strKind,CString strModel,vector<CString> *vFileList); //获取被测设备中某一个文件中的列表
	int GetSolutionList(CString strKind, CString strModel, vector<FileInfo> *vSolutionFileList); //获得测试方案列表
	int GetModuleList(CString strKind,CString strModel,vector<CString> *vModuleList); //获取被测设备中模版列表//搜索所有.xml文件并保存
	int GetConfigList(CString strKind,CString strModel,vector<CString> *vConfigList); //获取被测设备中配置列表
	int GetDriverList(CString strKind, CString strModel, vector<FileInfo> *vDriverPathList, int nType);//获得驱动文件的列表,0:UUT驱动,1:测试工具驱动

	CString GetUUTStartPath(); //获取被测设备初始地址

	int IsXmlFileExist(CFileFind* pff);
	int GetUUTList(CString strKind,vector<FileInfo> *vUUTFileList); //获取被测设备列表
	CFile_UUTInfo();
	virtual ~CFile_UUTInfo();

};

#endif // !defined(AFX_FILE_UUTINFO_H__AF980DC3_C717_43E6_A201_591ADA8EE6EB__INCLUDED_)
