#if !defined(TEST_LUA_STRUCT__INCLUDE_)
#define TEST_LUA_STRUCT__INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct TESTLUAFUN
{
	CString strEngineFunName;//���溯������
	CString strTestFunName;//�⺯������
	CString strTestFunDescibe;//��������
	CStringArray *strParaArray;//�����б�
	TESTLUAFUN *next;
}TestLuaFun;

typedef struct TESTLUAINSTR
{
	CString strInsType;//�豸����:uut,�����豸
	CString strInsName;//�豸����_�ͺ�
	CString strDriverName;//��������
	TestLuaFun *testLuaFun;
}TestLuaInstr;

#endif