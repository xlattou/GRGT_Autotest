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
	void TraverseTree(CTreeCtrl* pWndTree, CStringArray &strFatherArray, CStringArray &strChildArray);//遍历树
	BOOL CopyDirectory(CString strSrcPath, CString strDesPath, BOOL bFailIfExists =FALSE);//复制文件夹
	void DeleteDirectorye(CString strPath);//删除整个路径
	void DeleteDirectorye1(CString strPath);//删除路径下所有文件
	void ReplacePartNameInDirectorye(CString strPath, CString strOldPart, CString strNewPart);//修改路径下所有文件部分文件名
	void changeXMLRootName(CString strPath, CString strRootName);//修改XML根节点名
	void ChangeSolutionIni(CString strDirPath, CString strKind, CString strModel);//修改解决方案文件夹
	void CreateLua(CString strKind, CString strModel, CString strLua);//创建Lua脚本
	CString CStrTorHex(CString strMsg);//字符串转HEX字符串
	char CharToHexChar(unsigned char ch);
	CString Hex(unsigned char *pData, int nLength);
	BOOL CreateMultyDir(CString strPath);//创建多重路径
	CString UINTtoString(UINT nUint);//无符号整形转换成字符串
};

#endif // !defined(AFX_TOOL_H__C868F76A_88D5_4470_84A1_244593848A25__INCLUDED_)
