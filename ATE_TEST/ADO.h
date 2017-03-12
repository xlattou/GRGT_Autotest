// ADO.h: interface for the CADO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADO_H__EE0962C4_DC53_489D_981F_B112A39F9C1B__INCLUDED_)
#define AFX_ADO_H__EE0962C4_DC53_489D_981F_B112A39F9C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CADOConnection
{
private:
	static void InitADO();
	static void UnInitADO();
protected:
	_ConnectionPtr m_Connection;
public:
	BOOL IsOpen();
	_ConnectionPtr GetConnection();
	CString GetSQLConStr(CString IP,CString DBName);
	BOOL Open(CString ConStr);
	CADOConnection();
	virtual ~CADOConnection();

};

class CADODataSet
{
protected:

	CADOConnection *m_Connection;
public:
	_RecordsetPtr m_DataSet;
	BOOL Open(CString SQLStr,int LockType);
	void Delete();
	int GetRecordNo();
	void move(int nIndex);
	void moveNext();
	void Save();
	void SetFieldValue(CString FieldName,_variant_t Value);
	void AddNew();
	BOOL Next();
	FieldsPtr GetFields();
	int GetRecordCount();
	void SetConnection(CADOConnection *pCon);
	BOOL Open(CString SQLStr);
	BOOL IsOpen();
	int GenerateID();

	CADODataSet();
	virtual ~CADODataSet();
	
};


CADOConnection * GetConnection();
#endif // !defined(AFX_ADO_H__EE0962C4_DC53_489D_981F_B112A39F9C1B__INCLUDED_)
