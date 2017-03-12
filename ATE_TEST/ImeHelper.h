#pragma once

#include "imm.h"

#pragma comment(lib, "imm32")

//////////////////////////////////////////////
// Input method helper class
class ImeHelper
{
private:
	HKL  m_hkls[100];
	int  m_nCount;
public:
	ImeHelper(void)
	{
		m_nCount = ::GetKeyboardLayoutList(100, m_hkls);
	}

	~ImeHelper(void)
	{
	}

	int GetCount()
	{
		return m_nCount;
	}

	HKL GetHKL(int nIndex)
	{
		if (nIndex<0 || nIndex>m_nCount)
		return NULL;

		return m_hkls[nIndex];
	}

	void ActivateIme(HKL hkl)
	{
		if (hkl != NULL)
		::ActivateKeyboardLayout(hkl, 0);
	}

	void DoMenu(HWND hwnd, int x, int y)
	{
		HMENU hMenu = CreatePopupMenu();
		int nCmd = ::TrackPopupMenuEx(hMenu, TPM_LEFTBUTTON | TPM_RETURNCMD, x, y, hwnd, NULL);
  
		if (nCmd>=0 && nCmd<m_nCount)
			ActivateIme(GetHKL(nCmd));

		::DestroyMenu(hMenu);
	}

	CString GetDescription(HKL hkl)
	{
		char szDesc[200];
		memset(szDesc, 0, 200);
		::ImmGetDescription(hkl, szDesc, 200);
		if (strlen(szDesc)==0)
		{
			//sprintf(szDesc, "0x%x", (UINT)hkl);
			WORD wLang = LOWORD(hkl);
			switch (wLang)
			{
				case 0x0804:
				printf(szDesc, "ÖÐÎÄ");
				break;
				case 0x0409:
				sprintf(szDesc, "Ó¢Óï");
				break;
				default:
				break;
			}
		}
		return szDesc;
	}

	LPCTSTR GetImeFile(HKL hkl)
	{
		static char szFile[256];
		memset(szFile, 0, 256);
		::ImmGetIMEFileName(hkl, szFile, 255);
		return szFile;
	}

	int CurrentIndex()
	{
		HKL hkl = ::GetKeyboardLayout(::GetCurrentThreadId());
		for (int i=0; i<m_nCount; i++)
		{
			if (hkl == m_hkls[i])
			return i;
		}
		return -1;
	}

	int RollTypeWriting()
	{
		int nI = CurrentIndex();
		nI++;
		if(nI >= m_nCount)
			nI = 0;
		ActivateIme(GetHKL(nI));
		return CurrentIndex();
	}

	HICON GetIcon(HKL hkl)
	{
		HICON hIcon = NULL;
		LPCTSTR szImeFile = GetImeFile(hkl);
		if (strlen(szImeFile)==0)
		{
			//return a default icon
			}
			else
			{
			HMODULE hModule = ::LoadLibrary(szImeFile);
			if (hModule)
			{
			hIcon = ::ExtractIcon(hModule, szImeFile, 0);
			::FreeLibrary(hModule);
			}
		}
		return hIcon;
	}
private:
	 //Create a popup menu of all input method
	HMENU CreatePopupMenu()
	{
		HMENU hMenu = ::CreatePopupMenu();
		for (int i=0; i<m_nCount; i++)
		{
			::AppendMenu(hMenu, (CurrentIndex()==i)?MF_CHECKED:0, i, GetDescription(GetHKL(i)));
		}
		return hMenu;
	}

};