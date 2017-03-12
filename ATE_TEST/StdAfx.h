
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C01867C0_8045_47AA_A52B_61B6299047D3__INCLUDED_)
#define AFX_STDAFX_H__C01867C0_8045_47AA_A52B_61B6299047D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#undef WINVER
#define WINVER 0x500//为了使用AnimateWindow函数，必须这样定义

//#define _WIN32_WINNT 0x0500


#include <string>
#include <stdio.h>
using std::string;
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <vector>
#include "Easysize.h"

//导入文件

#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
no_namespace\
 rename("EOF","adoEOF")


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C01867C0_8045_47AA_A52B_61B6299047D3__INCLUDED_)

