// RecordList.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "RecordList.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordList

CRecordList::CRecordList()
: m_nIndex(-1), m_pRecord(NULL)
{
	
}
void CRecordList::SetFolder(CString folder)
{
	if(folder.IsEmpty())
	{
		AfxMessageBox(L"");
		return;
	}
	if(m_pRecord == NULL)
	{
		m_pRecord = new CLastTasks();
		m_pRecord->SetRecordFolderPath(folder);
	}
}


CRecordList::~CRecordList()
{
	if(m_pRecord != NULL)
	{
		delete m_pRecord;
		m_pRecord = NULL;
	}
}


BEGIN_MESSAGE_MAP(CRecordList, CComboBox)
	//{{AFX_MSG_MAP(CRecordList)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordList message handlers

void CRecordList::InitList()
{
	this->ResetContent();
	this->InsertString(++m_nIndex, L"--select--");
	m_pRecord->InitLastRecord();
	CStringList record;
	m_pRecord->GetLastRecord(record);

	POSITION pos = record.GetHeadPosition();
	CString task;
	while(pos)
	{
		task = record.GetNext(pos);
		InsertString(++m_nIndex, task);
		//CComboBox::AddString(task);
	}
	SetCurSel(0);
}

int CALLBACK CRecordList::SortList(LPARAM lp1, LPARAM lp2, LPARAM lpSort)
{
	return 0;
}

void CRecordList::Sort()
{
	
}

void CRecordList::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//DWORD dwStyleEx;
	//GetWindowLong(m_hWnd, GWL_STYLE);
	//dwStyleEx = dwStyleEx & ~CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_SORT;
	//SetWindowLong(m_hWnd, GWL_STYLE, dwStyleEx);
	//ModifyStyle(0, CBS_SORT);
	CoInitialize (NULL);
	CComboBox::PreSubclassWindow();
}

BOOL CRecordList::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CComboBox::PreCreateWindow(cs);
}

void CRecordList::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	CString text;
	GetWindowText(text);
	if(!PathIsDirectory(text))
	{
		//SetWindowText("--select--");
		SetCurSel(0);
		return;
	}
	text.ReleaseBuffer();
	//GetLBText(GetCurSel(), text);
	if(m_pRecord->AddRecord(text))
	{
		InsertString(++m_nIndex, text);
		text.ReleaseBuffer();
	}
}

int CRecordList::AddString(LPCTSTR lpszString)
{
	if(m_pRecord->AddRecord(lpszString))
	{
		int ret = InsertString(++m_nIndex, lpszString);
		SetCurSel(m_nIndex);
		return ret;
	}
	return 0;
}

BOOL CRecordList::GetCurString(CString &path)
{
	int cursel = this->GetCurSel();
	if(cursel != 0)
	{
		wchar_t szText[MAX_PATH_EX];
		GetLBText(cursel, szText);
		path.Format(L"%s", szText);
		return TRUE;
	}
	return FALSE;
}
