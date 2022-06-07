// LastTasks.h: interface for the CLastTasks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASTTASKS_H__84FF8557_89C2_4F34_B266_91B4B19A0AE9__INCLUDED_)
#define AFX_LASTTASKS_H__84FF8557_89C2_4F34_B266_91B4B19A0AE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLastTasks  
{
public:
	BOOL AddRecord(CString record);
	void GetLastRecord(CStringList &record);
	void SetRecordFolderPath(CString strpath);
	void InitLastRecord();
	CLastTasks();
	virtual ~CLastTasks();

private:
	CStringList m_LastRecord;
	CString m_folder;
protected:
	CString GetTargetFromLnk(CString link);
	CString GetNameFromPath(CString path);
	BOOL CreateLink(LPCTSTR szPath, LPCTSTR szLink);
	
};

#endif // !defined(AFX_LASTTASKS_H__84FF8557_89C2_4F34_B266_91B4B19A0AE9__INCLUDED_)
