// LocalLock.h: interface for the CLocalLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALLOCK_H__FD10F2F9_1DF2_46A6_8261_1FA9E2AB061C__INCLUDED_)
#define AFX_LOCALLOCK_H__FD10F2F9_1DF2_46A6_8261_1FA9E2AB061C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLocalLock  
{
public:
	CLocalLock(LPCRITICAL_SECTION lpCriticalSection)
		:m_lpCriticalSection(lpCriticalSection)
	{
		EnterCriticalSection(m_lpCriticalSection);
	}
	~CLocalLock()
	{
		LeaveCriticalSection(m_lpCriticalSection);
	}
private:
	LPCRITICAL_SECTION m_lpCriticalSection;
};

#endif // !defined(AFX_LOCALLOCK_H__FD10F2F9_1DF2_46A6_8261_1FA9E2AB061C__INCLUDED_)
