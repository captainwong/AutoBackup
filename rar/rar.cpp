// rar.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "rar.h"
#include "RarManager.h"

HINSTANCE hInst_rar;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hInst_rar = (HINSTANCE)hModule;
			CLog::SetOutputConsole(1);
			//CLog::SetOutputLogFileName("rardll.log");
			//CLog::SetOutputLogFile(1);
			CLog::WriteLog("DLL_PROCESS_ATTACH\n");
			break;
		case DLL_THREAD_ATTACH:
			CLog::WriteLog("DLL_THREAD_ATTACH\n");
			break;
		case DLL_THREAD_DETACH:
			CLog::WriteLog("DLL_THREAD_DETACH\n");
			break;
		case DLL_PROCESS_DETACH:
			CRarManager::Unload_Exe();
			CLog::WriteLog("DLL_PROCESS_DETACH\n");
			break;
    }
	
    return TRUE;
}

RAR_API bool Compress(LPCTSTR srcPath, LPCTSTR dstFolder, LPCTSTR dstName)
{
	BOOL bRet = CRarManager::Compress(srcPath, dstFolder, dstName);
	return bRet ? true : false;
}

RAR_API bool Decompress(LPCTSTR srcRarPath, LPCTSTR dstFolder)
{
	BOOL bRet = CRarManager::Decompress(srcRarPath, dstFolder);
	return bRet ? true : false;
}