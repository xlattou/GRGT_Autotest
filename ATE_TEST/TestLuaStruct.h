#if !defined(TEST_LUA_STRUCT__INCLUDE_)
#define TEST_LUA_STRUCT__INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct TESTLUAFUN
{
	CString strEngineFunName;//引擎函数名字
	CString strTestFunName;//库函数名字
	CString strTestFunDescibe;//函数描述
	CStringArray *strParaArray;//参数列表
	TESTLUAFUN *next;
}TestLuaFun;

typedef struct TESTLUAINSTR
{
	CString strInsType;//设备类型:uut,被测设备
	CString strInsName;//设备名称_型号
	CString strDriverName;//驱动名称
	TestLuaFun *testLuaFun;
}TestLuaInstr;

#endif