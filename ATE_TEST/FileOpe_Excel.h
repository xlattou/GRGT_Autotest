// FileOpe_Excel.h: interface for the CFileOpe_Excel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_)
#define AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "excel.h"
#include "Xml_Bll_UUTItem_Tem.h"
using namespace MyExcel;
#define ThrowErr(err) throw TEXT(#err)
using namespace std;

//�ַ���������Ϣ�ṹ
struct StringStruct
{
	CString m_strName; //���Խ��
	CString m_strRow; //��
	CString m_strColumn; //��
	CString m_strConclusion; //����
	CString m_strItemKey; //��Ŀ�ؼ���
};
//���Ͳ�����Ϣ�ṹ
struct INTStruct
{
	int m_intSel; //����ѡ��
	CString m_strRow; //��
	CString m_strColumn; //��
};


//������Ϣ
struct FirstPaper
{
	StringStruct m_stucCustomer; //ί�з�
	StringStruct m_stucAddress_Customer; //ί�з���ַ
	StringStruct m_stucInsName; //������������ 
	StringStruct m_stucInsModel; //�����ͺ�
	StringStruct m_stucFactory; //���쳧
	StringStruct m_stucSNumber; //���߱��
	INTStruct m_stucInsUse; //������;
	StringStruct m_stucNumber_Mana; //������
	StringStruct m_stucCalDate; //У׼����
	StringStruct m_stucDueCalDate; //������У׼����
	StringStruct m_StandardName0;  //��׼��������
	StringStruct m_StandardNum0;  //��׼�������
	StringStruct m_StandardName1;  //��׼��������
	StringStruct m_StandardNum1;  //��׼�������
	StringStruct m_StandardName2;  //��׼��������
	StringStruct m_StandardNum2;  //��׼�������
	StringStruct m_StandardName3;  //��׼��������
	StringStruct m_StandardNum3;  //��׼�������
	StringStruct m_stucResult; //У׼����,����˵��
	INTStruct m_stucConclusion; //У׼���ۣ��Ƿ�ϸ� 0=���ϸ� 1=�ϸ�
	INTStruct m_stucCalStation; //У׼�ص� 0=ʵ���� 1=ί�з��ֳ� -1 = �Զ����ַ
	StringStruct m_stucTestAdrress;  //���Եص�
	StringStruct m_stucTemperature; //�¶�
	StringStruct m_stucHumidity; //ʪ��
	StringStruct m_stucTester;  //У׼��
	int m_intSheetNumber; //Excel�е�д��ҳ��
	vector<StringStruct> vstucResult; //���Խ���б�
	CString m_strTemplete; //�������õ�xml֤��ģ��·��
};



class CFileOpe_Excel  
{
public:
	int WriteResultToExcel(CString strTemFilePath,CString strSavefilePath,FirstPaper stucFirstPaper);
	int ReadExcel();
	void CreateExcel();
	CXml_Bll_UUTItem_Tem m_xml_tem;
	CFileOpe_Excel();
	virtual ~CFileOpe_Excel();

private:
	void StringToArray(CString strInput,CString key,vector<CString>* stringArray); //�ַ����ָ�
};

#endif // !defined(AFX_FILEOPE_EXCEL_H__6460BC71_C9E6_4BE6_AD1E_60AD2810FB7C__INCLUDED_)
