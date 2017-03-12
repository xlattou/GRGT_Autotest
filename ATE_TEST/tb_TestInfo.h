// tb_TestInfo.h: interface for the Ctb_TestInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_)
#define AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ADO.h"
using namespace std;

struct stucTestInfo 
{
	int m_intID; //������ϢID
	CString m_strCustomer; //ί�з�
	CString m_strAddress; //ί�з���ַ
	CString m_strInsName; //�豸����
	CString m_strModel; //�豸�ͺ�
	CString m_strFactory; //���쳧
	CString m_strSNumber; //�������
	CString m_strInsUse; //�豸��;
	CString m_strNumber_Mana; //������
	CString m_strCalDate; //У׼����
	CString m_strDueCalDate; //������У׼����
	CString m_strResult; //У׼����  ����˵�� ��У׼���ʹ��/1���ϸ�/ 2���ϸ�
	CString m_strConclusion; //�Ƿ�ϸ�
	CString m_strCalStation;  //У׼�ص�
	CString m_strTemperature; //�¶�
	CString m_strHumidity; //ʪ��
	CString m_strTester; //������Ա
	CString m_strTestTime; //����ʱ��
	CString m_strTemplete; //����ģ��
};

class Ctb_TestInfo  
{
public:
	int SearchTestInfoList(vector<stucTestInfo>* vTestInfo //������Ϣ�б�
		,CString strSearchContent //��ѯ���ֶ�
		,CString strKey //�ؼ���
		);
	int SearchTestInfoList(vector<stucTestInfo>* vTestInfo //������Ϣ�б�
		,CString strSearchContent1 //��ѯ���ֶ�1
		,CString strKey1 //�ؼ���1
		,CString strSearchContent2 //��ѯ���ֶ�2
		,CString strKey2 //�ؼ���2
		);
	int ReadTestInfoList(vector<stucTestInfo>* vTestInfo);
	int ReadTestInfo(stucTestInfo *TestInfo,int intID);
	int GenerateID();
	int Add(stucTestInfo TestInfo);
	int UpdateTestInfo(stucTestInfo TestInfo);//������Ϣ
	CADODataSet m_DataSet;
	CString m_strTable;
	_ConnectionPtr m_pCon;



	Ctb_TestInfo();
	virtual ~Ctb_TestInfo();

};

#endif // !defined(AFX_TB_TESTINFO_H__D564FD5C_EA5D_41C3_9EA7_AFDFD676CF14__INCLUDED_)
