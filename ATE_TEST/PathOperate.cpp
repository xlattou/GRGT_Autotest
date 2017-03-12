// PathOperate.cpp: implementation of the CPathOperate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "PathOperate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPathOperate::CPathOperate()
{

}

CPathOperate::~CPathOperate()
{

}

//��ȡ����·������һ��Ŀ¼
CString CPathOperate::GetStartPath()
{	
	char* s=new char[MAX_PATH];    
	if(!GetModuleFileName(NULL,s,MAX_PATH))
	{
		ThrowErr(��ȡ����·��ʧ��);
		delete []s;
		return "";
	}
    (_tcsrchr(s,_T('\\')))[0] = 0;  //ȥ��ATE_TEST.exe
	(_tcsrchr(s,_T('\\')))[1] = 0;//ȥ��\\Debug
	CString startPath(s);
	delete[] s;
	return startPath;
}

//��ȡ����·��Ŀ¼
CString CPathOperate::GetAppPath()
{	
	char* s=new char[MAX_PATH];    
	if(!GetModuleFileName(NULL,s,MAX_PATH))
	{
		ThrowErr(��ȡ����·��ʧ��);
		delete []s;
		return "";
	}
    (_tcsrchr(s,_T('\\')))[0] = 0;  //ȥ��ATE_TEST.exe
	CString startPath(s);
	delete[] s;
	return startPath;
}