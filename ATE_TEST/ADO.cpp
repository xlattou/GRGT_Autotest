// ADO.cpp: implementation of the CADO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADO.h"
#include <comdef.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define ThrowErr(err) throw TEXT(#err)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int ConCount = 0;
CADOConnection g_Connection;//全局数据库连接对象

CADOConnection * GetConnection()
{
	return &g_Connection;
}

CADOConnection::CADOConnection()
{
	InitADO();
	m_Connection.CreateInstance("ADODB.Connection");
}

CADOConnection::~CADOConnection()
{
	if (IsOpen())
		m_Connection->Close();
	m_Connection = NULL;
	UnInitADO();
}

void CADOConnection::InitADO()
{
		if (ConCount++ == 0) 
			CoInitialize(NULL);
};
void CADOConnection::UnInitADO()
{
		if (--ConCount == 0)
			 CoUninitialize();
};

BOOL CADOConnection::Open(CString ConStr)
{
	if (IsOpen())
		m_Connection->Close();
	try
	{
		m_Connection->Open((_bstr_t)ConStr,"","",adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox("error");
	}
	
	return IsOpen();
}

CString CADOConnection::GetSQLConStr(CString IP, CString DBName)
{
	CString Str;
	Str.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=s%;JET OLEDB:DATABASE PASSWORD=''%s",DBName,IP);
	return Str;
}


_ConnectionPtr CADOConnection::GetConnection()
{
	return m_Connection;
}

BOOL CADOConnection::IsOpen()
{
	long State;
	m_Connection->get_State(&State);
	if (State == adStateOpen)
		return true;
	return false;
}

////////////////////////////////////////
CADODataSet::CADODataSet()
{
	m_DataSet.CreateInstance("ADODB.Recordset");
}

CADODataSet::~CADODataSet()
{
	if (IsOpen())
		m_DataSet->Close();
	m_DataSet = NULL;
	m_Connection = NULL;
}

void CADODataSet::SetConnection(CADOConnection *pCon)
{
	m_Connection = pCon;
}

int CADODataSet::GetRecordCount()
{
	if (IsOpen())
		return m_DataSet->GetRecordCount();
	else
		return 0;
}

BOOL CADODataSet::Open(CString SQLStr)
{
	if (IsOpen())
		m_DataSet->Close();
	//*/
	m_DataSet->Open(_bstr_t(SQLStr),
			_variant_t((IDispatch*)g_Connection.GetConnection(), true),
			adOpenKeyset, adLockOptimistic, adCmdText);
	return IsOpen();
	//*/

}

BOOL CADODataSet::IsOpen()
{
	long State;
	m_DataSet->get_State(&State);
	if (State == adStateOpen)
		return true;
	
	return false;
}

FieldsPtr CADODataSet::GetFields()
{
	return m_DataSet->GetFields();
}

BOOL CADODataSet::Next()
{
	if (m_DataSet->adoEOF)
		return false;
	m_DataSet->MoveNext();
	return true;
}

void CADODataSet::AddNew()
{
	m_DataSet->AddNew();
}

void CADODataSet::SetFieldValue(CString FieldName, _variant_t Value)
{
	m_DataSet->PutCollect((_bstr_t)FieldName,Value);
}

void CADODataSet::Save()
{
	m_DataSet->Update();
}

void CADODataSet::move(int nIndex)
{
	m_DataSet->MoveFirst();
	m_DataSet->Move(nIndex);
}
/*
void CADODataSet::moveNext()
{
	m_DataSet->MoveNext();
}
*/
int CADODataSet::GetRecordNo()
{
	return m_DataSet->AbsolutePosition;
}

void CADODataSet::Delete()
{
	m_DataSet->Delete(adAffectCurrent);
}

BOOL CADODataSet::Open(CString SQLStr, int LockType)
{
	if (IsOpen())
		m_DataSet->Close();
	//*/
	m_DataSet->Open(_bstr_t(SQLStr),
			_variant_t((IDispatch*)g_Connection.GetConnection(), true),
			adOpenKeyset,(LockTypeEnum) LockType, adCmdText);
	return IsOpen();
}
int CADODataSet::GenerateID()
{
	int myID=0;
	_variant_t var;
	try
	{
		if(!m_DataSet->adoEOF)
		{
			m_DataSet->MoveLast();
			var=m_DataSet->GetCollect("ID");
			if(var.vt!=VT_NULL)
				myID=atoi((LPCSTR)_bstr_t(var))+1;
		}
		else
		{
			myID=1;
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		//ThrowErr(产生ID编号出错);

	}
	return myID;
}