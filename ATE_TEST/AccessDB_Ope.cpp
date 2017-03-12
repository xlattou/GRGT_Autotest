// AccessDB_Ope.cpp: implementation of the CAccessDB_Ope class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ATE_TEST.h"
#include "AccessDB_Ope.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define ThrowErr(err) throw TEXT(#err);
#endif

extern CATE_TESTApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccessDB_Ope::CAccessDB_Ope()
{

}

CAccessDB_Ope::~CAccessDB_Ope()
{
	RecordClose();

}

int CAccessDB_Ope::GenerateID()
{
	int myID=0;
	_variant_t var;
	try
	{
		m_Recordset->MoveLast();
		if(!m_Recordset->adoEOF)
		{
			var=m_Recordset->GetCollect("ID");
			if(var.vt!=VT_NULL)
				myID=atoi((LPCSTR)_bstr_t(var))+1;
		}
	}
	catch(_com_error &)
	{
	//	ThrowErr(e->ErrorMessage());
	//	AfxMessageBox();
	}
	return myID;
}

BOOL CAccessDB_Ope::RecordOpen(char* table)
{
	char strConn[255];
    m_Recordset.CreateInstance(__uuidof(Recordset));
	sprintf(strConn,"select * from %s",table);
	try
	{
		m_Recordset->Open(strConn,
			theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);	
		return 1;
	}
	catch(_com_error &)
	{
		//ThrowErr(e->ErrorMessage());
		return 0;
	}
}

BOOL CAccessDB_Ope::RecordClose()
{
  return RecordClose(m_Recordset);
}

BOOL CAccessDB_Ope::RunDatabase(CString strCommand)
{
	bstr_t s = strCommand.AllocSysString();
	_variant_t RecordsAffected; 
	int ret=0;
	try
	{
		m_Recordset=theApp.m_pConnection->Execute(s,&RecordsAffected,adCmdText);
		ret=1;
	}
	catch(_com_error &)
	{
//		ThrowErr(e->ErrorMessage());
	}
	return ret;
}

BOOL CAccessDB_Ope::RecordClose(_RecordsetPtr pRecord)
{
	try
	{
    	if(pRecord!=NULL)
		{
			if(pRecord->GetState()==adStateOpen)
			{
            	pRecord->Close();
			}
	    	pRecord=NULL;
		}
	    return 1;
	}
	catch(_com_error &)
	{
//		ThrowErr(e->ErrorMessage());
		return 0;
	}

}
