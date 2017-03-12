#include "stdafx.h"
#include "ShareMemory.h"

ShareMemory::ShareMemory(int n)
{
	nSize=n;
}
ShareMemory::ShareMemory()
{
}
int ShareMemory::CreatSharedMemory()
{
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,"ATSSharedMemory");// ���������ڴ��
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// ��������
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// �����ڴ��Ѿ�����
		return 1;
	return 2;
}

int ShareMemory::CreatSharedMemory_Any(char* shareName)
{
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,shareName);// ���������ڴ��
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// ��������
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// �����ڴ��Ѿ�����
		return 1;
	return 2;
}


int ShareMemory::ReadSharedMemory(char* shareName,char* shareValue)
{
    hFileMap=OpenFileMapping(FILE_MAP_READ,false,shareName);
	if(hFileMap==NULL)
	{
		return 0;
	}

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_READ,0,0,0);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
	if(lpMap==NULL)
	{
		return 0;
	}
	memset(shareValue,0,nSize);
	memcpy(shareValue,lpMap,nSize);
	Sleep(100);
	UnmapViewOfFile(lpMap);
	lpMap=NULL;
	return 1;
}


int ShareMemory::WriteToSharedMemory(const char *szFormat,...)
{
	char *szBuffer=new char[nSize];
	va_list pArgs;
    va_start(pArgs, szFormat);      
    _vsnprintf(szBuffer,nSize,szFormat,pArgs);       
    va_end(pArgs) ;

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
	if(lpMap==NULL)				// ӳ�����
		return 0;
	memset(lpMap, 0, nSize);	// ��չ����ڴ�
	memcpy(lpMap,szBuffer,nSize);	// ������д�빲���ڴ�
	Sleep(100);
	UnmapViewOfFile(lpMap);		//��ӳ��������ڴ��ļ�ӳ�������ͼж��
	delete[] szBuffer;
	return 1;
}

int ShareMemory::WriteToSharedMemory_1(char* pData)
{
	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
	if(lpMap==NULL)				// ӳ�����
		return 0;
	memset(lpMap, 0, nSize);	// ��չ����ڴ�
	memcpy(lpMap,pData,nSize);	// ������д�빲���ڴ�
	Sleep(100);
	UnmapViewOfFile(lpMap);		//��ӳ��������ڴ��ļ�ӳ�������ͼж��
	return 1;
}

int ShareMemory::ReleaseSharedMemory()
{

	if(hFileMap!=NULL)
    	CloseHandle(hFileMap);		// �رչ����ڴ�
	return 1;
}
ShareMemory::~ShareMemory(void)
{
}