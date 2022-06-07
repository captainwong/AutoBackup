// CleanFiles.cpp: implementation of the CCleaner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoBackup.h"
#include "Cleaner.h"
//#include "rar/rar.h"
//#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
//CStringList CCleaner::extList;
//CStringList CCleaner::exceptList;

typedef  bool(*lpfnCompress)(LPCTSTR srcPath, LPCTSTR dstFolder, LPCTSTR dstName);
typedef  bool(*lpfnDecompress)(LPCTSTR srcRarPath, LPCTSTR dstFolder);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCleaner::CCleaner()
	: m_dwCleandLength(0), m_bCount(FALSE), m_dwCleandCount(0)
	, m_hThread(INVALID_HANDLE_VALUE)
	//,m_pInfoDlg(NULL)
{
	/*
	if(extList.IsEmpty())
	{
		extList.AddTail("OBJ");
		extList.AddTail("ILK");
		extList.AddTail("PCH");
		extList.AddTail("PDB");
		extList.AddTail("RES");
		extList.AddTail("IDB");
		extList.AddTail("TLB");
		extList.AddTail("TMP");
		extList.AddTail("LOG");
		extList.AddTail("LDB");
		extList.AddTail("SBR");
		//extList.AddTail("TLH");
		//extList.AddTail("TLI");
		extList.AddTail("BSC");
		extList.AddTail("SUP");
		extList.AddTail("EXE");
		extList.AddTail("DLL");
		extList.AddTail("LIB");
	}
	*/
	/*
	if(exceptList.IsEmpty())
	{
		exceptList.AddTail("EXE");
		exceptList.AddTail("DLL");
		exceptList.AddTail("LIB");
	}
	*/
	/*
	if(m_pInfoDlg == NULL)
	{
		m_pInfoDlg = new CCleanInfoDlg();
		m_pInfoDlg->Create(IDD_DIALOG3, NULL);
	}
	*/
}

CCleaner::~CCleaner()
{
	/*
	if(m_pInfoDlg != NULL)
	{
		m_pInfoDlg->DestroyWindow();
		delete m_pInfoDlg;
		m_pInfoDlg = NULL;
	}
	*/
}

void CCleaner::Clean(const CString& folder)
{
	//TRACE("clean folder %s\n", folder);

	//if(folder.GetAt(0) == 'E'
	//	|| folder.GetAt(0) == 'e')
	if (PathIsDirectory(folder)) {
		CString findtarget = folder + "\\*.*";
		//if(findtarget.GetLength() >= MAX_PATH_EX)
		//	return;


		CFileFind find;
		BOOL rc = find.FindFile(findtarget);

		while (rc) {
			rc = find.FindNextFile();

			if (find.IsDots())
				continue;

			if (find.IsDirectory()) {
				Clean(find.GetFilePath());
			} else {
				CleanFiles(find.GetFilePath());
			}
		}
	}


}

void CCleaner::CleanFiles(CString filePath)
{
	CString ext = CFileOper::GetFileExt(filePath);

	if (!ext.IsEmpty()) {
		POSITION pos = NULL;
		CAutoBackupApp *afxApp = (CAutoBackupApp*)AfxGetApp();
		ASSERT(afxApp);
		if ((pos = afxApp->m_extList.Find(ext)) == NULL) {
			return;
		}

		if (ext.CompareNoCase(_T("TXT")) == 0) {
			int size = CFileOper::GetFileSize(filePath);
			if (size < 1024 * 1024)
				return;
		}

		if (m_bCount) {
			m_dwCleandLength += CFileOper::GetFileSize(filePath);
			m_dwCleandCount++;
		}
		DeleteFile(filePath);
		CString trace;
		trace.Format(_T("delete file %s\n"), filePath);
		TRACE(trace);
		if (m_bCount)
			AddInfo(trace);

	}
}

void CCleaner::Compress(CString strpath)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	CString cmd = "";
	cmd.Format("C:\\Program Files\\WinRar\\rar.exe a %s.rar %s", strpath, strpath);
	LPTSTR lpszCmd = cmd.GetBuffer(cmd.GetLength());
	cmd.ReleaseBuffer();
	BOOL bRet = CreateProcess(NULL, lpszCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	DWORD dwExit = -1;
	if (bRet) {
		//这个地方将导致该函数为阻塞状态  
		WaitForSingleObject(pi.hProcess, INFINITE);
		::GetExitCodeProcess(pi.hProcess, &dwExit);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
}

void CCleaner::StartCount()
{
	m_dwCleandLength = 0;
	m_dwCleandCount = 0;
	m_bCount = TRUE;
}

DWORD CCleaner::GetCleandLength()
{
	return m_dwCleandLength;
}

DWORD CCleaner::GetCleandCount()
{
	return m_dwCleandCount;
}

void CCleaner::StartShowInfo()
{
	StartCount();


	if (m_hThread == INVALID_HANDLE_VALUE) {
		m_hThread = CreateThread(NULL, 0, ThreadInfo, this, 0, NULL);
		WaitTillThreadActive(m_hThread);
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
}

DWORD WINAPI CCleaner::ThreadInfo(LPVOID lp)
{
	CCleaner *pcl = (CCleaner*)lp;
	//if(pcl->m_bCount)
	{
		//pcl->m_pInfoDlg->ShowWindow(SW_SHOW);
		//Sleep(1000);
		//pcl->m_pInfoDlg->DoModal();
		//delete pcl->m_pInfoDlg;
		//pcl->m_pInfoDlg = NULL;
		//pcl->m_InfoDlg.DoModal();
	}
	//pcl->m_pInfoDlg->ShowWindow(SW_HIDE);
	return 0;
}

void CCleaner::AddInfo(CString info)
{
	/*
	if(m_pInfoDlg != NULL)
	{
		m_pInfoDlg->AddInfo(info);
		m_pInfoDlg->Invalidate(0);
	}*/
	m_InfoDlg.AddInfo(info);
}

void CCleaner::ShowInfo()
{
	/*if(m_pInfoDlg != NULL && IsWindow(m_pInfoDlg->m_hWnd))
	{
		m_pInfoDlg->ShowWindow(SW_SHOW);
	}*/
	m_InfoDlg.DoModal();
}

BOOL CCleaner::CompressEx(const CString& srcFolder)
{
	HINSTANCE hRar = NULL;
	MTVERIFY(hRar = ::LoadLibrary("rar.dll"));
	if (hRar == NULL) {
		AfxMessageBox("LoadLibrary fail");
		return 0;
	}
	lpfnCompress compress = NULL;
	MTVERIFY(compress = (lpfnCompress)::GetProcAddress(hRar, "Compress"));

	char src[MAX_PATH_EX], dst[MAX_PATH_EX], name[MAX_PATH_EX];
	lstrcpy(src, srcFolder);
	CString folder, rest;
	int pos = srcFolder.ReverseFind('\\');
	if (pos == -1) return 0;
	folder = srcFolder.Left(pos + 1);
	rest = srcFolder.Right(srcFolder.GetLength() - pos - 1);
	lstrcpy(dst, folder);
	lstrcpy(name, rest);
	BOOL ret = compress(src, folder, name);
	::FreeLibrary(hRar);
	return ret;
}
