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
	int GetSections(CStringArray& );		//获取所有字段名
	int GetKeys(CStringArray&,CString);		//获取键名
	int IsNULL();							//判断INI文件是否为空
	CString GetDriverName(CString);			//获取驱动名
	void SetINIname(CString);
	void SetINIPth(CString);
	CIni();
	virtual ~CIni();
	CString GetKeyValue(CString,CString);		//获取键值
	BOOL WriteKeyValue(CString section,CString key, CString strValue);
	void SaveConfiguerINI(CString,CString,CString,CString,CString,vector<CString>);

private:
	CString m_nameINI;
	CString m_pthINI;
};

#endif // !defined(AFX_INI_H__EF3FE723_B4DD_4BA0_8605_BDF0921BD960__INCLUDED_)
