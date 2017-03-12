// PathOperate.h: interface for the CPathOperate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHOPERATE_H__BD18D763_921F_4672_9528_FE53B6807584__INCLUDED_)
#define AFX_PATHOPERATE_H__BD18D763_921F_4672_9528_FE53B6807584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ThrowErr(err) throw TEXT(#err)

class CPathOperate  
{
public:
	CString GetStartPath();
	CString GetAppPath();
	CPathOperate();
	virtual ~CPathOperate();

};

#endif // !defined(AFX_PATHOPERATE_H__BD18D763_921F_4672_9528_FE53B6807584__INCLUDED_)
