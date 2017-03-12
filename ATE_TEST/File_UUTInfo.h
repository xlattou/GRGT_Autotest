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
//UUT�ļ���Ϣ
struct FileInfo
{
	CString m_strFileName;
	CString m_strFilePath;
	CString m_strFileName_Set;
};


class CFile_UUTInfo  
{
public:
	int GetFileList(CString strFoldName,CString strKind,CString strModel,vector<CString> *vFileList); //��ȡ�����豸��ĳһ���ļ��е��б�
	int GetSolutionList(CString strKind, CString strModel, vector<FileInfo> *vSolutionFileList); //��ò��Է����б�
	int GetModuleList(CString strKind,CString strModel,vector<CString> *vModuleList); //��ȡ�����豸��ģ���б�//��������.xml�ļ�������
	int GetConfigList(CString strKind,CString strModel,vector<CString> *vConfigList); //��ȡ�����豸�������б�
	int GetDriverList(CString strKind, CString strModel, vector<FileInfo> *vDriverPathList, int nType);//��������ļ����б�,0:UUT����,1:���Թ�������

	CString GetUUTStartPath(); //��ȡ�����豸��ʼ��ַ

	int IsXmlFileExist(CFileFind* pff);
	int GetUUTList(CString strKind,vector<FileInfo> *vUUTFileList); //��ȡ�����豸�б�
	CFile_UUTInfo();
	virtual ~CFile_UUTInfo();

};

#endif // !defined(AFX_FILE_UUTINFO_H__AF980DC3_C717_43E6_A201_591ADA8EE6EB__INCLUDED_)
