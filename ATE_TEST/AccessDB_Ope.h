// AccessDB_Ope.h: interface for the CAccessDB_Ope class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSDB_OPE_H__9408A96F_884C_4078_9B78_2972623FAF9A__INCLUDED_)
#define AFX_ACCESSDB_OPE_H__9408A96F_884C_4078_9B78_2972623FAF9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAccessDB_Ope  
{
public:
	BOOL RecordClose(_RecordsetPtr pRecord);
	BOOL RunDatabase(CString strCommand);
	BOOL RecordClose();
	_RecordsetPtr m_Recordset;
	BOOL RecordOpen(char* table);
	CAccessDB_Ope();
	
	virtual ~CAccessDB_Ope();
	int GenerateID();
};

#endif // !defined(AFX_ACCESSDB_OPE_H__9408A96F_884C_4078_9B78_2972623FAF9A__INCLUDED_)
