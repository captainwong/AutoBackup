#if !defined(AFX_RECORDLIST_H__639E488B_4D87_4D72_8A4E_627B5C0538E5__INCLUDED_)
#define AFX_RECORDLIST_H__639E488B_4D87_4D72_8A4E_627B5C0538E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordList.h : header file
//
#include "LastTasks.h"
/////////////////////////////////////////////////////////////////////////////
// CRecordList window

class CRecordList : public CComboBox
{
private:
	CLastTasks *m_pRecord;
	int m_nIndex;
// Construction
public:
	CRecordList();

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordList)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GetCurString(CString &path);
	virtual int AddString(LPCTSTR lpszString);
	void SetFolder(CString folder);
	virtual ~CRecordList();
	void InitList();
	// Generated message map functions
protected:
	void Sort();
	static int CALLBACK SortList(LPARAM lp1, LPARAM lp2, LPARAM lpSort);
	
	//{{AFX_MSG(CRecordList)
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDLIST_H__639E488B_4D87_4D72_8A4E_627B5C0538E5__INCLUDED_)
