// Tool.h: interface for the CTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOL_H__C868F76A_88D5_4470_84A1_244593848A25__INCLUDED_)
#define AFX_TOOL_H__C868F76A_88D5_4470_84A1_244593848A25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTool  
{
public:
	CTool();
	virtual ~CTool();
	void TraverseTree(CTreeCtrl* pWndTree, CStringArray &strFatherArray, CStringArray &strChildArray);//������
	BOOL CopyDirectory(CString strSrcPath, CString strDesPath, BOOL bFailIfExists =FALSE);//�����ļ���
	void DeleteDirectorye(CString strPath);//ɾ������·��
	void DeleteDirectorye1(CString strPath);//ɾ��·���������ļ�
	void ReplacePartNameInDirectorye(CString strPath, CString strOldPart, CString strNewPart);//�޸�·���������ļ������ļ���
	void changeXMLRootName(CString strPath, CString strRootName);//�޸�XML���ڵ���
	void ChangeSolutionIni(CString strDirPath, CString strKind, CString strModel);//�޸Ľ�������ļ���
	void CreateLua(CString strKind, CString strModel, CString strLua);//����Lua�ű�
	CString CStrTorHex(CString strMsg);//�ַ���תHEX�ַ���
	char CharToHexChar(unsigned char ch);
	CString Hex(unsigned char *pData, int nLength);
	BOOL CreateMultyDir(CString strPath);//��������·��
	CString UINTtoString(UINT nUint);//�޷�������ת�����ַ���
};

#endif // !defined(AFX_TOOL_H__C868F76A_88D5_4470_84A1_244593848A25__INCLUDED_)
