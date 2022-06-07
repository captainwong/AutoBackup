// CleanFiles.h: interface for the CCleaner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLEANFILES_H__CF1D1124_503E_4FD0_9557_A2C6BAF60ACE__INCLUDED_)
#define AFX_CLEANFILES_H__CF1D1124_503E_4FD0_9557_A2C6BAF60ACE__INCLUDED_
#include "CleanInfoDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCleaner  
{
public:	
	BOOL CompressEx(const CString& srcFolder);
	void ShowInfo();
	void StartShowInfo();
	DWORD GetCleandCount();
	DWORD GetCleandLength();
	
	
	CCleaner();
	virtual ~CCleaner();
	
	void Clean(const CString& folder);
	void Compress(CString strpath);
protected:
	void StartCount();
	void AddInfo(CString info);
	static DWORD WINAPI ThreadInfo(LPVOID lp);
	void CleanFiles(CString filePath);
	

private:
	//static CStringList extList;
	DWORD m_dwCleandLength;
	DWORD m_dwCleandCount;
	BOOL m_bCount;
	//CCleanInfoDlg *m_pInfoDlg;
	CCleanInfoDlg m_InfoDlg;
	HANDLE m_hThread;
};

#endif // !defined(AFX_CLEANFILES_H__CF1D1124_503E_4FD0_9557_A2C6BAF60ACE__INCLUDED_)
