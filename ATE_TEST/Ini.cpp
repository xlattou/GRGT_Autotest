// Ini.cpp: implementation of the CIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ate_test.h"
#include "Ini.h"

#define MAX_ALLSECTIONS 250
#define MAX_SECTION 100
#define MAX_PROFILE_SECTION 500
#define MAX_KEY 20

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIni::CIni()
{
}

CIni::~CIni()
{

}

int CIni::GetSections(CStringArray& arrSection)
{
	int i;
	int iPos = 0;
	int iMaxCount=0;

	TCHAR chSectionNames[MAX_ALLSECTIONS] = {0};
	TCHAR chSection[MAX_SECTION] = {0};
	GetPrivateProfileSectionNames(chSectionNames,MAX_ALLSECTIONS,m_pthINI); //读取所有字段

	//////////////////////////////计算字符数////////////////////////////////////////////
	for(i=0;i<MAX_ALLSECTIONS;i++)
	{
		if(chSectionNames[i] == 0)
		if(chSectionNames[i+1] == 0)
		{
			break;
		}
	}

	iMaxCount = i+1;
	///////////////////////判断字符串是否为空///////////////////////////////////////////////////
	if(chSectionNames[0]==0 && chSectionNames[1]==0)
	{
		return 0;
	}
	//////////////////////生成字段数组////////////////////////////////////////////////////
	int cnrtrtttrt = 0;
	for(int i=0;i<iMaxCount;i++)
	{
		chSection[iPos++] = chSectionNames[i];  
		if(chSectionNames[i] == 0)
		{//遇到字符为0，进行字符串截取保存
			arrSection.Add(chSection);
			memset(chSection,0,i);
			iPos = 0;
		}

		/***************************************************
		调试使用	
		****************************************************/
		cnrtrtttrt++;
		CString str;
 		str.Format(_T(" %d "),cnrtrtttrt);
		OutputDebugString(str);
		/****************************************************/
	}
	return (int)arrSection.GetSize();

}

int CIni::GetKeys(CStringArray& arrKeys,CString section)
{
	int i,j;
				//记录=的个数
	int iPos = 0;
	int pos = 0;
	int len;
	
	char chProfileSection[MAX_PROFILE_SECTION] = {0};
	char chKeyName[MAX_SECTION] = {0};
	GetPrivateProfileSection(section,chProfileSection,MAX_PROFILE_SECTION,m_pthINI);

	int num=0;	
	for(i=0;i<MAX_PROFILE_SECTION;i++)
	{
		if(chProfileSection[i] == '=')
			num++;
	}

	char*ptemp = chProfileSection;
	char*cmp = "=";
	for(j=0;j<num;j++)
	{
		pos = strcspn(ptemp,cmp);
		strncpy(chKeyName,ptemp,pos); 
		ptemp = ptemp + pos +1;
		arrKeys.Add(chKeyName);
		memset(chKeyName,0,pos);		
		len = strlen(ptemp);
		ptemp = ptemp + len +1;
	}
	
	return (int)arrKeys.GetSize();			//返回keyname的个数
}

CString CIni::GetKeyValue(CString section,CString key)
{
	char ckey[100]={0};
	GetPrivateProfileString(section,key,0,ckey,255,m_pthINI);//将长度从30位修改为255位
	CString keyValue = ckey;
	return keyValue;
	//GetPrivateProfileString(m_session,"Address",0,port,30,m_openFile);
}

BOOL CIni::WriteKeyValue(CString section,CString key, CString strValue)
{
	ASSERT(m_pthINI != _T(""));	
	return WritePrivateProfileString(section, key, strValue, m_pthINI);
}	

CString CIni::GetDriverName(CString section)
{
	char driverName[100] = {0};		//driver的地址最长不超过100
	GetPrivateProfileString(section,"DriverName",0,driverName,100,m_pthINI);

	int pos = 0;
	for(int i=0;i<100;i++)
	{
		if(driverName[i] == '\\')
			pos = i;				//获取最后一个'\'的位置
	}

	char *ptemp = driverName+pos+1;
	CString ctemp = ptemp;
	return ctemp;
	
}

int CIni::IsNULL()
{
	CFile INIFile(m_pthINI,CFile::modeRead);
	return INIFile.GetLength();
}

void CIni::SetINIname(CString fName)
{
	m_nameINI = fName;
}

void CIni::SetINIPth(CString pth)
{
	m_pthINI = pth;
}

//保存configINI文件
void CIni::SaveConfiguerINI(CString section,CString port,CString channel,CString pthDriverName,CString driverName,vector<CString> m_fun)
{
	CString keyName,keyValue;

	WritePrivateProfileString(section,"Address",port,m_pthINI);
	WritePrivateProfileString(section,"Channel",channel,m_pthINI);
	WritePrivateProfileString(section,"DriverName",pthDriverName,m_pthINI);
		
	for(int i=0; i<m_fun.size();i++)
	{	
		keyName = m_fun[i];
		keyValue = driverName  + ".dll->" + keyName ;
		WritePrivateProfileString(section,keyName,keyValue,m_pthINI);
	}
}
