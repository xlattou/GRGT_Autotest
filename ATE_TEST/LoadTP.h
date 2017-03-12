// LoadTP.h: interface for the CLoadTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADTP_H__73BFF486_4F3C_45C8_9FC6_D85298922CC5__INCLUDED_)
#define AFX_LOADTP_H__73BFF486_4F3C_45C8_9FC6_D85298922CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "iqapi.h"                               //IQ��Ŀ
#include "IQ2010Ext.h"

//typedef int (WINAPI * LoadTP)(CString luaFilePath, //Lua�ļ�·��
//							  CString uutCom,  //�����豸ң�ص�ַ
//							  CString inputVar, //���Բ���
//							  CString testConfigFilePath,//���������ļ�·��
//							  int serial,  //����˳��
//							  int testMode, //����ģʽ
//							  char* result, //���Խ��
//							  int num //�������
//							  );

typedef int (WINAPI * LoadTP)(CString luaFilePath, //Lua�ļ�·��
							  CString uutCom,  //�����豸ң�ص�ַ
	                          CString inputVar, //���Բ���
	                          CString testConfigFilePath,//���������ļ�·��
	                          int serial,  //����˳��
	                          int testMode, //����ģʽ
	                          char* result, //���Խ��
	                          int num, //�������
							  CString iqApi, //�������������������
							  CString ch ,  //WLAN�۲������ӵ�ͨ����
							  CString vsg,  //WLAN�۲������ӵ�ͨ����
							  CString rout   //WLAN�۲������ӵ�ͨ����
	);

typedef int (WINAPI * LoadSN)(CString uutCom,  //�����豸ң�ص�ַ
							  char* result, //���Խ��
							  char* errorout,//��ȡָ���Ƿ����쳣
							  int num //�������
							  );

typedef int (WINAPI * LoadConnect)(CString uutCom,  //�����豸?��ص��?
							       CString isReset, //�Ƿ�oʼ��
							       char* handleOut,//���ص�ֵַ
							       int num //�������
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
