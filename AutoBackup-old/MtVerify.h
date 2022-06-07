#pragma comment( lib, "USER32" )
#include <crtdbg.h>
#ifdef DEBUG
#define MTASSERT(a) _ASSERTE(a)
#define MTVERIFY(a) if (!(a)) PrintError(#a,__FILE__,__LINE__,GetLastError())
#else
#define MTASSERT(a) (a)
#define MTVERIFY(a) (a)
#endif
__inline void PrintError(LPTSTR linedesc, LPTSTR filename, int lineno, DWORD errnum)
{
	LPTSTR lpBuffer;
	TCHAR errbuf[256];
#ifdef _WINDOWS_
	TCHAR modulename[MAX_PATH];
#else
	DWORD numread;
#endif
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errnum,
		LANG_NEUTRAL,
		(LPTSTR)&lpBuffer,
		0,
		NULL
		);
	wsprintf(errbuf, "\nThe following call failed at line %d in %s:\n\n %s\n\nReason: %s\n", lineno, filename, linedesc, lpBuffer);
#ifndef _WINDOWS_
	WriteFile(GetStdHandle(STD_ERROR_HANDLE), errbuf, lstrlen(errbuf), &numread, FALSE );
	Sleep(3000);
#else
	GetModuleFileName(NULL, modulename, MAX_PATH);
	MessageBox(NULL, errbuf, modulename, MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);
#endif
	LocalFree(lpBuffer);
	exit(EXIT_FAILURE);
}

__inline void WaitTillThreadActive(HANDLE &handle)
{
	if(handle != INVALID_HANDLE_VALUE)
	{
		BOOL rc = FALSE;
		DWORD ec = 0;
		for(;;)
		{
			rc = GetExitCodeThread(handle, &ec);
			if(rc && (ec == STILL_ACTIVE))
				break;
			Sleep(500);
		}
	}
}

__inline void WaitTillThreadExited(HANDLE &handle)
{
	if(handle != INVALID_HANDLE_VALUE)
	{
		BOOL rc = FALSE;
		DWORD ec = 0;
		for(;;)
		{
			rc = GetExitCodeThread(handle, &ec);
			if(rc && (ec != STILL_ACTIVE))
			{
				CloseHandle(handle);
				handle = INVALID_HANDLE_VALUE;
				break;
			}
			Sleep(500);
		}
	}
}

__inline LPTSTR GetModuleFilePath()
{
	static char szPath[MAX_PATH] = {'\0'};
	if(lstrlen(szPath) != 0)
		return szPath;
	
	char szExe[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), szExe, MAX_PATH);
	int len = lstrlen(szExe);
	for(int i = len; i > 0; i--)
	{
		if(szExe[i] == '\\')
		{
			szExe[i] = '\0';
			lstrcpy(szPath, szExe);
			break;
		}
	}
	return szPath;
}

