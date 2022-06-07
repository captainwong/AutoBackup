#if !defined(AFX_MULTIPROJECTDLG_H__754D4D4A_94AF_4897_8EC5_6222364EC734__INCLUDED_)
#define AFX_MULTIPROJECTDLG_H__754D4D4A_94AF_4897_8EC5_6222364EC734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiProjectDlg.h : header file
//
#include "RecordList.h"
/////////////////////////////////////////////////////////////////////////////
// CMultiProjectDlg dialog

class CMultiProjectDlg : public CDialog
{
// Construction
public:
	BOOL GetSelectedPath(CStringList &list);
	CMultiProjectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiProjectDlg)
	enum { IDD = IDD_DIALOG2 };
	CRecordList	m_combo8;
	CRecordList	m_combo9;
	CRecordList	m_combo7;
	CRecordList	m_combo6;
	CRecordList	m_combo5;
	CRecordList	m_combo4;
	CRecordList	m_combo3;
	CRecordList	m_combo2;
	CRecordList	m_combo10;
	CRecordList	m_combo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitCombos();
	BOOL InerGetSelectedPath(CStringList &list);
	// Generated message map functions
	//{{AFX_MSG(CMultiProjectDlg)
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static CStringList m_pathList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPROJECTDLG_H__754D4D4A_94AF_4897_8EC5_6222364EC734__INCLUDED_)
