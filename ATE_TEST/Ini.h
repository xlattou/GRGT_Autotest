// Ini.h: interface for the CIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INI_H__EF3FE723_B4DD_4BA0_8605_BDF0921BD960__INCLUDED_)
#define AFX_INI_H__EF3FE723_B4DD_4BA0_8605_BDF0921BD960__INCLUDED_
#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIni  
{
public:
	int GetSections(CStringArray& );		//��ȡ�����ֶ���
	int GetKeys(CStringArray&,CString);		//��ȡ����
	int IsNULL();							//�ж�INI�ļ��Ƿ�Ϊ��
	CString GetDriverName(CString);			//��ȡ������
	void SetINIname(CString);
	void SetINIPth(CString);
	CIni();
	virtual ~CIni();
	CString GetKeyValue(CString,CString);		//��ȡ��ֵ
	BOOL WriteKeyValue(CString section,CString key, CString strValue);
	void SaveConfiguerINI(CString,CString,CString,CString,CString,vector<CString>);

private:
	CString m_nameINI;
	CString m_pthINI;
};

#endif // !defined(AFX_INI_H__EF3FE723_B4DD_4BA0_8605_BDF0921BD960__INCLUDED_)
