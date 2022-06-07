// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////
/*
��־��CLog
��������������־����࣬ʹ��ʱ���Զ����죬����ΪҪ��֤��־�����һ����������Ҫ�ֶ��ͷ�
���ܣ�д��־�����TRACE���ݵ�dbgview,console��
ʹ�ã�
	ʹ�ú���
		static void SetOutputLogFileName(LPCTSTR szFileName);
		static void SetOutputConsole(BOOL bFlag);
		static void SetOutputDbgView(BOOL bFlag);
		static void SetOutputLogFile(BOOL bFlag);
		�����������־�ķ�ʽ
	ʹ��TRACE��ʹ�ú���static void WriteLog(const char* format, ...);д��־���ɽ��ܿɱ����
�ͷţ��ڳ����˳�ʱ��ExitInstance()��������󣩵���CLog::Release()�ͷ����ü���
*/
#if !defined(AFX_ERRORLOG_H__46D664F1_E737_46B7_9813_2EF1415FF884__INCLUDED_)
#define AFX_ERRORLOG_H__46D664F1_E737_46B7_9813_2EF1415FF884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#ifndef TRACE
#else
#undef TRACE
#define TRACE(a) CLog::WriteLog(a)
#endif



class CLog  
{
private:
	CLog();
	~CLog();
	double exe_time; 
	LARGE_INTEGER freq; 
	LARGE_INTEGER start_t, stop_t; 
	TCHAR m_szFileName[MAX_PATH];
	BOOL m_bOutputLogFile;
	BOOL m_bOutputDbgView;
	BOOL m_bOutputConsole;
	BOOL m_bConsoleOpened, m_bDbgviewOpened, m_bLogFileOpened;
	BOOL m_bRunning;
	FILE *m_pLogFile;
	FILE* OpenLogFile();	
	PROCESS_INFORMATION pi;
	static HANDLE m_hMutex;
	static CLog *m_pInst;
	static CRITICAL_SECTION m_cs;
	int m_nRef;
	void CreateFileName();
	void CloseLogFile();
	BOOL OpenConsole(BOOL bOpen);
	LPCTSTR GetLastTimeLogFileName();
	static CLog* GetInstance();
public:
	static ULONG Release();
	static void SetOutputLogFileName(LPCTSTR szLastName);
	static void SetOutputConsole(BOOL bFlag);
	static void SetOutputDbgView(BOOL bFlag);
	static void SetOutputLogFile(BOOL bFlag);
	static void WriteLog(const char* format, ...);	
protected:
	LPCTSTR GetAppRunTime();
	void Output(const char *out, WORD out_len);
	WORD FormatBuf(const char *oldBuf, char *newBuf, WORD max_new_buff_len = 4096);
	void OutputFile(const char *buf, WORD buf_len);
	BOOL OpenDbgview(BOOL bOpen);
};

#endif // !defined(AFX_ERRORLOG_H__46D664F1_E737_46B7_9813_2EF1415FF884__INCLUDED_)
