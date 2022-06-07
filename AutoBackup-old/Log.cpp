// ErrorLog.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
///#include "hbclient.h"
#include "Log.h"
//#include "OutputDebugString.h"
#include "LocalLock.h"
//#include "GenericBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog *CLog::m_pInst = NULL;//new CLog();
HANDLE CLog::m_hMutex = INVALID_HANDLE_VALUE;
CRITICAL_SECTION CLog::m_cs;
//int CLog::m_nRef = 0;

CLog::CLog()
: m_pLogFile(NULL), m_bOutputLogFile(FALSE), m_bOutputDbgView(FALSE), m_bOutputConsole(FALSE),
m_bConsoleOpened(FALSE), m_bDbgviewOpened(FALSE), m_bLogFileOpened(FALSE), m_bRunning(TRUE)
{	
	QueryPerformanceFrequency(&freq); 
	//fprintf(stdout, "The frequency of your pc is 0x%X.\n", freq.QuadPart); 
	QueryPerformanceCounter(&start_t); 

	m_nRef = 0;
	m_nRef++;
	memset(m_szFileName, 0, sizeof(m_szFileName));
	//TRACE("CLog construction\n");
	memset(&pi, 0, sizeof(pi));
	//m_handle = CreateThread(NULL, 0, ThreadWriteLog, this, 0, NULL);
	//WaitTillThreadActive(m_handle);
	InitializeCriticalSection(&m_cs);
}

CLog::~CLog()
{
	CLocalLock lock(&m_cs);
	m_bRunning = FALSE;
	//WaitTillThreadExited(m_handle);
	if(m_hMutex != INVALID_HANDLE_VALUE)
	{
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
		m_hMutex = INVALID_HANDLE_VALUE;
	}
	if(m_bConsoleOpened)
	{
		OpenConsole(FALSE);
	}
	if(m_bDbgviewOpened)
	{
		OpenDbgview(FALSE);
	}
	if(m_bLogFileOpened)
	{
		CloseLogFile();
	}
	
	DeleteCriticalSection(&m_cs);
	//TRACE("CLog destruction\n");
}

void CLog::CreateFileName()
{
	CString strTime;
	CTime time = CTime::GetCurrentTime();
	strTime = time.Format(_T("%Y-%m-%d %H时%M分%S秒.log"));
	int len = strTime.GetLength();
	memcpy(m_szFileName, strTime.GetBuffer(len), len);
	strTime.ReleaseBuffer();
	m_szFileName[len] = _T('\0');
	//CConfig::WriteLogFileName(m_szFileName);
}

FILE * CLog::OpenLogFile()
{
	FILE *pfile = fopen(m_szFileName, "r");
	//文件不存在
	if(pfile == NULL)
	{
		pfile = fopen(m_szFileName, "wb");
		if(pfile == NULL)
		{
			AfxMessageBox("新创建日志文件失败");
			//return NULL;
		}
	}
	//文件存在，以附加写入方式打开
	else
	{
		fclose(pfile);
		pfile = fopen(m_szFileName, "ab");
		if(pfile == NULL)
		{
			AfxMessageBox("打开日志文件失败");
			//return NULL;
		}
	}
	if(pfile != NULL)
	{
		m_bLogFileOpened = TRUE;
	}
	return pfile;
}

void CLog::CloseLogFile()
{
	if(m_pLogFile != NULL)
	{
		fflush(m_pLogFile);
		fclose(m_pLogFile);
		m_pLogFile = NULL;
	}
}

void CLog::WriteLog(const char *format, ...)
{
	
	try
	{
		CLog* plog = CLog::GetInstance();
		if(plog == NULL)
			return;

		CLocalLock lock(&m_cs);
		if(plog->m_bOutputLogFile || plog->m_bOutputDbgView || plog->m_bOutputConsole)
		{
			static char buf[4096], output[4096], *p;
			p = buf;

			va_list args;
			va_start(args, format);
			p += _vsnprintf(p, sizeof buf - 1, format, args);
			va_end(args);
			while ( (p > buf) && iswspace(*(p-1)) )
				*--p = '\0';
			*p++ = '\r';
			*p++ = '\n';
			*p = '\0';

			WORD out_len = plog->FormatBuf(buf, output);
			//buff.Write(buf, p-buf);
			//OutputDebugString(output);
			plog->Output(output, out_len);
		}
	}
	catch(...)
	{
		AfxMessageBox(_T("CLog::WriteLog"));
	}
}

void CLog::SetOutputLogFile(BOOL bFlag)
{
	CLog* plog = CLog::GetInstance();
	plog->m_bOutputLogFile = bFlag;
	if(plog->m_bOutputLogFile && lstrlen(plog->m_szFileName) == 0)
		plog->CreateFileName();
}

void CLog::SetOutputDbgView(BOOL bFlag)
{
	CLog* plog = CLog::GetInstance();
	plog->m_bOutputDbgView = bFlag;
	try
	{
		//plog->OpenDbgview(bFlag);
	}
	catch(...)
	{

	}
}

void CLog::SetOutputConsole(BOOL bFlag)
{
	CLog* plog = CLog::GetInstance();
	plog->m_bOutputConsole = bFlag;
	try
	{
		plog->OpenConsole(bFlag);
	}
	catch(...)
	{
		
	}
}

void CLog::SetOutputLogFileName(LPCTSTR szFileName)
{
	CLog* plog = CLog::GetInstance();
	
	memcpy(plog->m_szFileName, szFileName, lstrlen(szFileName));
}

CLog* CLog::GetInstance()
{
	if(m_pInst == NULL)
	{
		if((m_hMutex = CreateMutex(NULL, TRUE, NULL)) != INVALID_HANDLE_VALUE
				&& ERROR_ALREADY_EXISTS != GetLastError())
		{
			if(m_pInst == NULL)
			{
				m_pInst = new CLog();
				
			}
			
		}
	}
	return m_pInst;
}

BOOL CLog::OpenConsole(BOOL bOpen)
{
	if(bOpen)
	{
		if(!m_bConsoleOpened)
		{
			if(AllocConsole())
			{
				SetConsoleTitle(_T("HBClient output"));
				COORD coord;
				coord.X = 120;
				coord.Y = 60;
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				FillConsoleOutputAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
					120, coord, NULL);
				SetConsoleScreenBufferSize(hStdOut, coord);
				SMALL_RECT se;
				se.Left = 0;
				se.Top = 0;
				se.Right = 100;
				se.Bottom = 100;
				SetConsoleWindowInfo(hStdOut, FALSE, &se);
				freopen("CONOUT$", "w", stdout);
				m_bConsoleOpened = TRUE;
			}
		}
		return m_bConsoleOpened;
	}
	else
	{
		if(m_bConsoleOpened)
		{
			if(FreeConsole())
			{
				m_bConsoleOpened = FALSE;
			}
		}
		return !m_bConsoleOpened;
	}
}

BOOL CLog::OpenDbgview(BOOL bOpen)
{
	static STARTUPINFO si;
	//static PROCESS_INFORMATION pi;
	static LPCTSTR lpszAppName = "dbgview.exe";
	
	if(bOpen)
	{
		if(!m_bDbgviewOpened)
		{
			memset(&si,0,sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_SHOW;
			if(CreateProcess(lpszAppName,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
			{
				m_bDbgviewOpened = TRUE;
			}
		}
	}
	else
	{
		if(m_bDbgviewOpened)
		{
			//TerminateThread(pi.hThread, 0);
			//TerminateProcess(pi.hProcess, 0);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			m_bDbgviewOpened = FALSE;
		}
	}
	return bOpen ? m_bDbgviewOpened : !m_bDbgviewOpened;
}

WORD CLog::FormatBuf(const char *oldBuf, char *newBuf, WORD max_new_buff_len)
{
	try
	{
		static SYSTEMTIME st;
		static char sztime[128];
		memset(sztime, 0, sizeof sztime);
		GetLocalTime(&st);
		
		sprintf(sztime, "HB %04d-%02d-%02d week-%d %02d:%02d:%02d.%03d  %s  ", 
			st.wYear, st.wMonth, st.wDay, st.wDayOfWeek, 
			st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, GetAppRunTime());
		lstrcpy(newBuf, sztime);
		if(lstrlen(sztime) + lstrlen(oldBuf) < max_new_buff_len)
		{
			lstrcat(newBuf, oldBuf);
		}
		else
		{}
	}
	catch(...)
	{
		AfxMessageBox("CLog::FormatBuf");
	}
	return lstrlen(newBuf);
}

void CLog::Output(const char *out, WORD out_len)
{
	try
	{
		if(m_pInst == NULL)
			return;

		if(m_bOutputLogFile)
		{
			OutputFile(out, out_len);
		}

#ifdef _DEBUG
		OutputDebugString(out);
#else
		if(m_bOutputDbgView)
		{
			OutputDebugString(out);
		}
#endif

		if(m_bOutputConsole)
		{
			printf(out);
		}

	}
	catch(...)
	{
		AfxMessageBox("CLog::Output");
	}
}

void CLog::OutputFile(const char *buf, WORD buf_len)
{
	if(m_pLogFile == NULL)
		m_pLogFile = OpenLogFile();
	if(m_pLogFile != NULL)
	{
		fseek(m_pLogFile, 0, SEEK_END);
		long filelen = ftell(m_pLogFile);
		if(filelen >= 1024 * 1024 * 10)
		{
			fclose(m_pLogFile);
			CreateFileName();
			m_pLogFile = OpenLogFile();
		}
	}
	if(m_pLogFile != NULL)
	{
		fseek(m_pLogFile, 0, SEEK_END);
		fwrite(buf, 1, buf_len, m_pLogFile);
		fflush(m_pLogFile);
	}
}

LPCTSTR CLog::GetLastTimeLogFileName()
{
	return m_szFileName;
}

ULONG CLog::Release()
{
	CLog* plog = CLog::GetInstance();
	plog->m_nRef--;
	if(plog->m_nRef == 0)
	{
		delete plog;
		return 0;
	}
	return (ULONG)plog->m_nRef;
}

LPCTSTR CLog::GetAppRunTime()
{
	static char szTime[128];
	memset(szTime, 0, sizeof szTime);

	QueryPerformanceCounter(&stop_t);
	exe_time = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
	WORD day, hour, min, sec;

	sec = (int)(exe_time / 1000) % 60;
	min = (int)(exe_time / 1000 / 60) % 60;
	hour = (int)(exe_time / 1000 / 60) / 60;
	day = (int)(exe_time / 1000.0 / 60.0 / 60.0 / 24);

	double ms = exe_time - (int)(exe_time) + ((int)(exe_time) % 1000);
	sprintf(szTime, "%dday%02d:%02d:%02d.%06f", day, hour, min, sec, ms);
	return szTime;
}
