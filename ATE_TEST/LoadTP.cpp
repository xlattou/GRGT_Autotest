// LoadTP.cpp: implementation of the CLoadTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "LoadTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadTP::CLoadTP()
{

}

CLoadTP::~CLoadTP()
{

}

//int CLoadTP::MyLoadTP(CString hgPath,CString luaFilePath, CString uutCom, CString inputVar,CString testConfigFilePath, int serial, int testMode, char *result)
//{
//	try
//	{
//		HINSTANCE hLibrary=LoadLibraryA(hgPath);
//    	LoadTP lpFunc=NULL;
//		if(hLibrary)
//		{
//			lpFunc=(LoadTP)GetProcAddress(hLibrary,"TestFunction");//CarrierPower,FreqError,Scatter_Freq,ModuleSensity,CWPowerTest,IOI_USB,SWScatter_Freq
//			if(lpFunc)
//			{
//				lpFunc(luaFilePath,uutCom,inputVar,testConfigFilePath,serial,testMode,result,50);//USBSensity,AudioResponse_R_USB
//			}
//			FreeLibrary(hLibrary);
//		}
//	}
//	catch (CException* )
//	{
//		MessageBox(0,"����ʧ��","",0);
//	}
//	catch (char* e)
//	{
//		MessageBox(0,e,"",0);
//	}
//
//	return 1;
//}
int CLoadTP::MyLoadTP(CString hgPath,CString luaFilePath, CString uutCom, CString inputVar,CString testConfigFilePath, int serial, int testMode, char *result, CString iqApi, CString CH, CString VSG, CString ROUT)
{
	//hgPath = "E:\\�������ñ�_Engine.dll";
	try
	{
		HINSTANCE hLibrary=LoadLibraryA(hgPath);  //�������涯̬��
		LoadTP lpFunc=NULL;
		if(hLibrary)
		{
			lpFunc=(LoadTP)GetProcAddress(hLibrary,"TestFunction");//��ȡ��̬�������һ��������ָ��CarrierPower,FreqError,Scatter_Freq,ModuleSensity,CWPowerTest,IOI_USB,SWScatter_Freq
			if(lpFunc)
			{
				lpFunc(luaFilePath,uutCom,inputVar,testConfigFilePath,serial,testMode,result,50,iqApi,CH,VSG,ROUT);//���øú���USBSensity,AudioResponse_R_USB
			}
		}
		FreeLibrary(hLibrary);  //�ͷ����涯̬��
	}
	catch (CException* )
	{
		MessageBox(0,"����ʧ��","",0);
	}
	catch (char* e)
	{
		MessageBox(0,e,"",0);
	}

	return 1;
}

int CLoadTP::MyLoadSN(CString uutCom,CString dllPath,CString funcName, char* result, char* errorout)
{
	try
	{
		HINSTANCE hLibrary=LoadLibraryA(dllPath);
    	LoadSN lpFunc=NULL;
		if(hLibrary)
		{
			lpFunc=(LoadSN)GetProcAddress(hLibrary,funcName);
			if(lpFunc)
			{
				lpFunc(uutCom,result,errorout,50);
			}
			FreeLibrary(hLibrary);
		}
	}
	catch (CException* )
	{
		MessageBox(0,"����ʧ��","",0);
	}
	catch (char* e)
	{
		MessageBox(0,e,"",0);
	}

	return 1;
}

int CLoadTP::MyLoadConnect(CString uutCom,CString dllPath,CString funcName, CString isReset, char* handleOut,char* errorout)
{
	try
	{
		HINSTANCE hLibrary=LoadLibraryA(dllPath);
    	LoadConnect lpFunc=NULL;
		if(hLibrary)
		{
			lpFunc=(LoadConnect)GetProcAddress(hLibrary,funcName);
			if(lpFunc)
			{
				int m=lpFunc(uutCom,isReset,handleOut,50);
				itoa(m,errorout,2);
				//MessageBox("1");
			}
			FreeLibrary(hLibrary);
		}
	}
	catch (CException* )
	{
		MessageBox(0,"����ʧ��","",0);
	}
	catch (char* e)
	{
		MessageBox(0,e,"",0);
	}

	return 1;
}