// LastTasks.cpp: implementation of the CLastTasks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoBackup.h"
#include "LastTasks.h"

#include "Cleaner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLastTasks::CLastTasks()
:m_folder(_T(""))
{

}

CLastTasks::~CLastTasks()
{

}

void CLastTasks::SetRecordFolderPath(CString strpath)
{
	m_folder = strpath;
}

void CLastTasks::InitLastRecord()
{
	if(m_folder.IsEmpty())
		return;

	char szFolder[MAX_PATH_EX];
	lstrcpy(szFolder, m_folder.GetBuffer(m_folder.GetLength()));
	//AfxMessageBox(szFolder);
	if(!CreateDirectory(szFolder, NULL))
	{
		//AfxMessageBox("创建最近使用文件夹记录失败");
		//return;
	}
	m_folder.ReleaseBuffer();
	m_LastRecord.RemoveAll();
	CString findtarget = m_folder + "\\*.*";
	CFileFind find;
	BOOL bfind = find.FindFile(findtarget);
	findtarget.ReleaseBuffer();

	CString task, target;
	while(bfind)
	{
		bfind = find.FindNextFile();
		if(find.IsDots())
			continue;
		if((CFileOper::GetFileExt(find.GetFilePath())).CompareNoCase("lnk") != 0)
			continue;
		task = find.GetFilePath();
		target = GetTargetFromLnk(task);
		m_LastRecord.AddTail(target);
	}
}

void CLastTasks::GetLastRecord(CStringList &record)
{
	POSITION pos = NULL;
	pos = m_LastRecord.GetHeadPosition();
	CString task = "";
	while(pos != NULL)
	{
		task = m_LastRecord.GetNext(pos);
		record.AddTail(task);
	}
}

BOOL CLastTasks::AddRecord(CString record)
{
	if(m_LastRecord.Find(record))
		return FALSE;
	m_LastRecord.AddTail(record);
	CString strpath, link;
	strpath = record;
	CString name = GetNameFromPath(record);
	record.Replace(':', '-');
	record.Replace('\\', '-');
	name = record;
	link = m_folder + '\\' + name + ".lnk";
	char szPath[MAX_PATH_EX], szLink[MAX_PATH_EX];
	lstrcpy(szPath, strpath.GetBuffer(strpath.GetLength()));
	strpath.ReleaseBuffer();
	
	lstrcpy(szLink, link.GetBuffer(link.GetLength()));
	link.ReleaseBuffer();
	CreateLink(szPath, szLink);
	return TRUE;
}

BOOL CLastTasks::CreateLink(LPSTR szPath, LPSTR szLink)
{
	CString trace;
	trace.Format(_T("CLastTasks::CreateLink path %s, name %s\n"), szPath, szLink);
	OutputDebugString(trace);
	HRESULT hres ;
	IShellLink * psl ;
	IPersistFile* ppf ;
	WORD wsz[MAX_PATH_EX] ;
    //创建一个IShellLink实例
    hres = CoCreateInstance( CLSID_ShellLink, NULL,
        CLSCTX_INPROC_SERVER, IID_IShellLink,
        (void **)&psl) ;
	if( FAILED( hres))
        return FALSE ;
    //设置目标应用程序
    psl -> SetPath( szPath) ;
    //设置快捷键(此处设为Shift+Ctrl+'R')
    psl -> SetHotkey( MAKEWORD( 'R',
		HOTKEYF_SHIFT |HOTKEYF_CONTROL)) ;
    //从IShellLink获取其IPersistFile接口
    //用于保存快捷方式的数据文件 (*.lnk)
    hres = psl -> QueryInterface( IID_IPersistFile,
		(void**)&ppf) ;
	if( FAILED( hres))
        return FALSE ;
	// 确保数据文件名为ANSI格式
	MultiByteToWideChar( CP_ACP, 0, szLink, -1, 
		wsz, MAX_PATH_EX) ;
    //调用IPersistFile::Save
    //保存快捷方式的数据文件 (*.lnk)
	hres = ppf -> Save( wsz, STGM_READWRITE) ;
    //释放IPersistFile和IShellLink接口
	ppf -> Release( ) ;
	psl -> Release( ) ;
	return TRUE;
}

CString CLastTasks::GetNameFromPath(CString path)
{
	CString name = _T("");
	int pos = path.ReverseFind('\\');
	if(pos != -1)
	{
		name = path.Right(path.GetLength() - pos - 1);
	}
	return name;
}

CString CLastTasks::GetTargetFromLnk(CString link)
{
	HRESULT hres;
	CString LinkFileName = link;
	CString Link, Temp = LinkFileName;
	Temp.MakeLower();
	if (Temp.Find(".lnk")==-1)           //Check if the name ends with .lnk
		Link = LinkFileName + ".lnk";   //if not, append it
	else
		Link = LinkFileName;
	
	CString Info;
	Info.Empty();
	
	IShellLink* psl;
	
	//Create the ShellLink object
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (LPVOID*) &psl);
	
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		//Bind the ShellLink object to the Persistent File
		hres = psl->QueryInterface( IID_IPersistFile, (LPVOID *) &ppf);
		if (SUCCEEDED(hres))
		{
			WORD wsz[MAX_PATH_EX];
			//Get a UNICODE wide string wsz from the Link path
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Link, -1, wsz,      MAX_PATH_EX);
			
			//Read the link into the persistent file
			hres = ppf->Load(wsz, 0);
			
			if (SUCCEEDED(hres))
			{
				//Read the target information from the link object
				//UNC paths are supported (SLGP_UNCPRIORITY)
				psl->GetPath(Temp.GetBuffer(MAX_PATH_EX), MAX_PATH_EX, NULL,               SLGP_UNCPRIORITY);
				Temp.ReleaseBuffer();
				Info = Temp;
				
				//Read the arguments from the link object
				//psl->GetArguments(Temp.GetBuffer(MAX_PATH_EX), MAX_PATH_EX);
				//Temp.ReleaseBuffer();
				//Info += " " + Temp;
			}
		}
	}
	psl->Release();
	//Return the Target and the Argument as a CString
	return Info;
}
