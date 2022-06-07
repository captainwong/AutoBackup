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


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//LPCTSTR CRarManager::m_lpszRarExe = _T("rar.exe");
char CRarManager::m_szRarExe[1024] = {0};
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
			char msg[128];
			sprintf(msg, _T("File %s page %d, %s is not a valid directory."), __FILE__, __LINE__, dstFolder);
			MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
			return FALSE;
		}

		LPCTSTR lpszRar = LoadRar_Exe();
		if(lpszRar == NULL)
		{
			return FALSE;
		}

		char cmd[1024];
		sprintf(cmd, "\"%s\" a -s -m5 -ep1 -ilog\"%s\\%s\" \"%s%s\" \"%s\"", 
			lpszRar, GetModuleFilePath(), "rar.log", dstFolder , dstName , srcPath);

		CLog::WriteLog(_T("Compress() cmd: %s"), cmd);

		STARTUPINFO si = {sizeof(si)};
		si.dwFlags |= STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOWNORMAL;
		PROCESS_INFORMATION pi;

		BOOL bRet=CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);  
		DWORD dwExit = -1;
		char msg[1024];
		if(bRet)
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			::GetExitCodeProcess(pi.hProcess, &dwExit);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			sprintf(msg, "compress %s to %s%s success!\n", srcPath, dstFolder , dstName);
			CLog::WriteLog(msg);
			return TRUE;

		}
		else
		{
			sprintf(msg, "compress %s to %s%s failed!\n", srcPath, dstFolder , dstName);
			CLog::WriteLog(msg);
			return FALSE;
		}
	}
	catch(...)
	{
		AfxMessageBox("CRarManager::Compress");
	}
	return FALSE;
}

BOOL CRarManager::Decompress(LPCTSTR srcRarPath, LPCTSTR dstFolder)
{
	if(!PathIsDirectory(dstFolder))
	{
		char msg[128];
		sprintf(msg, _T("File %s page %d, %s is not a valid directory."), __FILE__, __LINE__, dstFolder);
		MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if(!PathFileExists(srcRarPath))
	{
		char msg[128];
		sprintf(msg, _T("File %s page %d, %s is not a valid file path."), __FILE__, __LINE__, srcRarPath);
		MessageBox(NULL, msg, _T("rar.dll"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	LPCTSTR lpszRar = LoadRar_Exe();
	if(lpszRar == NULL)
	{
		return FALSE;
	}

	char cmd[1024];
	sprintf(cmd, _T("%s e -o+ -ilog %s %s"), lpszRar, srcRarPath , dstFolder);

	STARTUPINFO si = {sizeof(si)};
	si.dwFlags |= STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	PROCESS_INFORMATION pi;

    BOOL bRet=CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);  
    DWORD dwExit = -1;
	char msg[1024];
    if(bRet)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        ::GetExitCodeProcess(pi.hProcess, &dwExit);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
		sprintf(msg, "decompress %s to %s success!\n", srcRarPath , dstFolder);
		CLog::WriteLog(msg);
		return TRUE;

    }
	else
	{
		sprintf(msg, "decompress %s to %s success!\n", srcRarPath , dstFolder);
		CLog::WriteLog(msg);
		return FALSE;
	}
}

extern HINSTANCE hInst_rar;

LPCTSTR CRarManager::LoadRar_Exe()
{
	sprintf(m_szRarExe, "%s\\%s", GetModuleFilePath(), RAR_EXE);
	if(PathFileExists(m_szRarExe))
		return m_szRarExe;

	HRSRC hRsrcInfo = NULL;
	//HINSTANCE hInst = GetModuleHandle("rar.dll");
	hRsrcInfo = FindResource(hInst_rar, MAKEINTRESOURCE(IDR_IMP_EXE1), TEXT("IMP_EXE"));//�õ���Դ��Ϣ�ľ��
    if (NULL==hRsrcInfo)
    {
			//PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
		SHOWERROR("LoadRar_Exe");
            return NULL; // ʧ��
    }
    DWORD dwSize = SizeofResource(hInst_rar, hRsrcInfo); 
    if (0 == dwSize)
    {
        //AfxMessageBox(TEXT("��Դ��С����"));
		PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // ʧ��
    }
    // ������Դ
    HGLOBAL hGlobal = LoadResource(hInst_rar, hRsrcInfo);  
    if (NULL == hGlobal)
    {
        //AfxMessageBox(TEXT("��Դ��ȡ����"));
		PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // ʧ��
    }
    // ������Դ 
    LPVOID pBuffer = LockResource(hGlobal); 
    if (NULL == pBuffer)
    {
        //AfxMessageBox(TEXT("��Դ��������"));
		PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // ʧ��
    }
    // д�뵽Ӳ���ļ����������Ǽ򵥵�д�뵽Ӳ���ļ�
    HANDLE hFileNew = CreateFile(m_szRarExe,
        GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if(INVALID_HANDLE_VALUE == hFileNew) 
    {
        //AfxMessageBox(TEXT("�ļ���������"));
		PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // ʧ��
    }
    
    // д�ļ�
    DWORD dwlen=0;
    BOOL bRet = WriteFile(hFileNew, pBuffer, dwSize, &dwlen, NULL);
    if(!bRet ||dwSize!=dwlen)
    {
        //AfxMessageBox(TEXT("�ļ�д�����"));
		PrintError("LoadRar_Exe", __FILE__, __LINE__, GetLastError());
        return NULL; // ʧ��
    }
    // �ر��ļ�
    CloseHandle(hFileNew);
    
    // �ͷ���Դ
    FreeResource(hGlobal);

	char out[1024] = {0};
	sprintf(out, "LoadRar_Exe() path %s\n", m_szRarExe);
	CLog::WriteLog(out);

	return m_szRarExe;
}

void CRarManager::Unload_Exe()
{
	BOOL ret = FALSE;
	char out[MAX_PATH];
	//sprintf(m_szRarExe, "%s\\%s", GetModuleFilePath(), RAR_EXE);
	if(PathFileExists(m_szRarExe))
	{
		ret = DeleteFile(m_szRarExe);
	}
	sprintf(out, "Unload_Exe %s\n", ret ? "success" : "failed");
	CLog::WriteLog(out);
}
