// LoadTP.h: interface for the CLoadTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADTP_H__73BFF486_4F3C_45C8_9FC6_D85298922CC5__INCLUDED_)
#define AFX_LOADTP_H__73BFF486_4F3C_45C8_9FC6_D85298922CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "iqapi.h"                               //IQ项目
#include "IQ2010Ext.h"

//typedef int (WINAPI * LoadTP)(CString luaFilePath, //Lua文件路径
//							  CString uutCom,  //被测设备遥控地址
//							  CString inputVar, //测试参数
//							  CString testConfigFilePath,//测试配置文件路径
//							  int serial,  //测试顺序
//							  int testMode, //测试模式
//							  char* result, //测试结果
//							  int num //结果长度
//							  );

typedef int (WINAPI * LoadTP)(CString luaFilePath, //Lua文件路径
							  CString uutCom,  //被测设备遥控地址
	                          CString inputVar, //测试参数
	                          CString testConfigFilePath,//测试配置文件路径
	                          int serial,  //测试顺序
	                          int testMode, //测试模式
	                          char* result, //测试结果
	                          int num, //结果长度
							  CString iqApi, //传递连接仪器的类对象
							  CString ch ,  //WLAN综测仪连接的通道号
							  CString vsg,  //WLAN综测仪连接的通道号
							  CString rout   //WLAN综测仪连接的通道号
	);

typedef int (WINAPI * LoadSN)(CString uutCom,  //被测设备遥控地址
							  char* result, //测试结果
							  char* errorout,//读取指令是否有异常
							  int num //结果长度
							  );

typedef int (WINAPI * LoadConnect)(CString uutCom,  //被测设备?？氐刂?
							       CString isReset, //是否硂始化
							       char* handleOut,//返回地址值
							       int num //结果长度
							      );
class CLoadTP  
{
public:
    static int MyLoadConnect(CString uutCom,CString dllPath,CString funcName, CString isReset, char* handleOut,char* errorout);
	static int MyLoadSN(CString uutCom,CString dllPath,CString funcName, char* result, char* errorout);
	//static int MyLoadTP(CString hgPath,CString luaFilePath, CString uutCom, CString inputVar,CString testConfigFilePath, int serial, int testMode, char *result);
	static int MyLoadTP(CString hgPath,CString luaFilePath, CString uutCom, CString inputVar,CString testConfigFilePath, int serial, int testMode, char *result,CString iqApi, CString CH, CString VSG, CString ROUT);
	CLoadTP();
	virtual ~CLoadTP();

};

#endif // !defined(AFX_LOADTP_H__73BFF486_4F3C_45C8_9FC6_D85298922CC5__INCLUDED_)
