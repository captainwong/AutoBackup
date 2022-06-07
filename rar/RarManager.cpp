// RarManager.cpp: implementation of the CRarManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RarManager.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#include "Resource.h"
#include "rar.h"
#include <stdio.h>
#include <tchar.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <jlib/win32.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//LPCTSTR CRarManager::m_lpszRarExe = _T("rar.exe");
wchar_t CRarManager::m_szRarExe[1024] = {0};
LPCTSTR RAR_EXE = _T("rar.exe");
#define AfxMessageBox(a) MessageBox(NULL, a, _T("RAR.DLL"), MB_OK | MB_ICONERROR)

CRarManager::CRarManager()
{

}

CRarManager::~CRarManager()
{

}

BOOL CRarManager::Compress(LPCTSTR srcPath, LPCTSTR dstFolder, LPCTSTR dstName)
{
	try
	{
		if(!PathIsDirectory(dstFolder))
		{
			wchar_t msg[128];
			wsprintf(msg, _T("File %s page %d, %s is not a valid directory."), __FILE__, __LINE__, dstFolder);
			MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
			return FALSE;
		}

		LPCTSTR lpszRar = LoadRar_Exe();
		if(lpszRar == NULL)
		{
			return FALSE;
		}

		wchar_t cmd[1024];
		wsprintf(cmd, L"\"%s\" a -s -m5 -ep1 -ilog\"%s\\%s\" \"%s%s\" \"%s\"",
			lpszRar, jlib::win32::getExeFolderPath().c_str(), L"rar.log", dstFolder , dstName , srcPath);

		JLOG(_T("Compress() cmd: %s"), cmd);

		STARTUPINFO si = {sizeof(si)};
		si.dwFlags |= STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOWNORMAL;
		PROCESS_INFORMATION pi;

		BOOL bRet=CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);  
		DWORD dwExit = -1;
		wchar_t msg[1024];
		if(bRet)
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			::GetExitCodeProcess(pi.hProcess, &dwExit);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			wsprintf(msg, L"compress %s to %s%s success!\n", srcPath, dstFolder , dstName);
			JLOG(msg);
			return TRUE;

		}
		else
		{
			wsprintf(msg, L"compress %s to %s%s failed!\n", srcPath, dstFolder , dstName);
			JLOG(msg);
			return FALSE;
		}
	}
	catch(...)
	{
		AfxMessageBox(L"CRarManager::Compress");
	}
	return FALSE;
}

BOOL CRarManager::Decompress(LPCTSTR srcRarPath, LPCTSTR dstFolder)
{
	if(!PathIsDirectory(dstFolder))
	{
		wchar_t msg[128];
		wsprintf(msg, _T("File %s page %d, %s is not a valid directory."), __FILE__, __LINE__, dstFolder);
		MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if(!PathFileExists(srcRarPath))
	{
		wchar_t msg[128];
		wsprintf(msg, _T("File %s page %d, %s is not a valid file path."), __FILE__, __LINE__, srcRarPath);
		MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	LPCTSTR lpszRar = LoadRar_Exe();
	if(lpszRar == NULL)
	{
		return FALSE;
	}

	wchar_t cmd[1024];
	wsprintf(cmd, _T("%s e -o+ -ilog %s %s"), lpszRar, srcRarPath , dstFolder);

	STARTUPINFO si = {sizeof(si)};
	si.dwFlags |= STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	PROCESS_INFORMATION pi;

    BOOL bRet=CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);  
    DWORD dwExit = -1;
	wchar_t msg[1024];
    if(bRet)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        ::GetExitCodeProcess(pi.hProcess, &dwExit);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
		wsprintf(msg, L"decompress %s to %s success!\n", srcRarPath , dstFolder);
		JLOG(msg);
		return TRUE;

    }
	else
	{
		wsprintf(msg, L"decompress %s to %s success!\n", srcRarPath , dstFolder);
		JLOG(msg);
		return FALSE;
	}
}

extern HINSTANCE hInst_rar;

LPCTSTR CRarManager::LoadRar_Exe()
{
	wsprintf(m_szRarExe, L"%s\\%s", jlib::win32::getExeFolderPath().c_str(), RAR_EXE);
	if(PathFileExists(m_szRarExe))
		return m_szRarExe;

	HRSRC hRsrcInfo = NULL;
	//HINSTANCE hInst = GetModuleHandle("rar.dll");
	hRsrcInfo = FindResource(hInst_rar, MAKEINTRESOURCE(IDR_IMP_EXE1), TEXT("IMP_EXE"));//得到资源信息的句柄
    if (NULL==hRsrcInfo)
    {
			//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
		AfxMessageBox(L"LoadRar_Exe");
        return NULL; // 失败
    }
    DWORD dwSize = SizeofResource(hInst_rar, hRsrcInfo); 
    if (0 == dwSize)
    {
        //AfxMessageBox(TEXT("资源大小错误"));
		//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // 失败
    }
    // 加载资源
    HGLOBAL hGlobal = LoadResource(hInst_rar, hRsrcInfo);  
    if (NULL == hGlobal)
    {
        //AfxMessageBox(TEXT("资源读取错误"));
		//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // 失败
    }
    // 锁定资源 
    LPVOID pBuffer = LockResource(hGlobal); 
    if (NULL == pBuffer)
    {
        //AfxMessageBox(TEXT("资源锁定错误"));
		//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // 失败
    }
    // 写入到硬盘文件。这里我们简单的写入到硬盘文件
    HANDLE hFileNew = CreateFile(m_szRarExe,
        GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if(INVALID_HANDLE_VALUE == hFileNew) 
    {
        //AfxMessageBox(TEXT("文件创建错误"));
		//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // 失败
    }
    
    // 写文件
    DWORD dwlen=0;
    BOOL bRet = WriteFile(hFileNew, pBuffer, dwSize, &dwlen, NULL);
    if(!bRet ||dwSize!=dwlen)
    {
        //AfxMessageBox(TEXT("文件写入错误"));
		//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // 失败
    }
    // 关闭文件
    CloseHandle(hFileNew);
    
    // 释放资源
    FreeResource(hGlobal);

	wchar_t out[1024] = {0};
	wsprintf(out, L"LoadRar_Exe() path %s\n", m_szRarExe);
	JLOG(out);

	return m_szRarExe;
}

void CRarManager::Unload_Exe()
{
	BOOL ret = FALSE;
	wchar_t out[MAX_PATH];
	//sprintf(m_szRarExe, "%s\\%s", GetModuleFilePath(), RAR_EXE);
	if(PathFileExists(m_szRarExe))
	{
		ret = DeleteFile(m_szRarExe);
	}
	wsprintf(out, L"Unload_Exe %s\n", ret ? "success" : "failed");
	JLOG(out);
}
