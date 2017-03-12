#pragma once

class ShareMemory
{
public:
	ShareMemory(int n);
	ShareMemory();
	int CreatSharedMemory();								// 创建共享内存块
	int CreatSharedMemory_Any(char* shareName);								// 创建共享内存块
	int ReadSharedMemory(char* shareName,char* shareValue);								// 创建共享内存块
	int WriteToSharedMemory(const char *szFormat,...);	// 将数据写入共享内存
	int WriteToSharedMemory_1(char* pData);	// 将数据写入共享内存
	int ReleaseSharedMemory();						// 关闭共享内存
	~ShareMemory(void);
	HANDLE hFileMap;
	int nSize;
};