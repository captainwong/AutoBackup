// RarManager.h: interface for the CRarManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RARMANAGER_H__9441C171_FE17_4B22_AECF_90C139BB9FD3__INCLUDED_)
#define AFX_RARMANAGER_H__9441C171_FE17_4B22_AECF_90C139BB9FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRarManager  
{
public:
	static void Unload_Exe();
	static BOOL Decompress(LPCTSTR srcRarPath, LPCTSTR dstFolder);
	static BOOL Compress(LPCTSTR srcPath, LPCTSTR dstFolder, LPCTSTR dstName);
private:
	CRarManager();
	virtual ~CRarManager();
	//static LPCTSTR m_lpszRarExe;
	static char m_szRarExe[1024];
protected:
	static LPCTSTR LoadRar_Exe();
};

#endif // !defined(AFX_RARMANAGER_H__9441C171_FE17_4B22_AECF_90C139BB9FD3__INCLUDED_)
