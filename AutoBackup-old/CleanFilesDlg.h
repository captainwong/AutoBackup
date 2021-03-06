#if !defined(AFX_CLEANFILESDLG_H__B407FDD2_983C_42C2_9191_1A71AEF5F94D__INCLUDED_)
#define AFX_CLEANFILESDLG_H__B407FDD2_983C_42C2_9191_1A71AEF5F94D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CleanFilesDlg.h : header file
//
#include "Cleaner.h"
#include "CleanInfoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CCleanFilesDlg dialog

class CCleanFilesDlg : public CDialog
{
// Construction
public:
	CCleanFilesDlg(CWnd* pParent = NULL);   // standard constructor
	CCleaner cl;
// Dialog Data
	//{{AFX_DATA(CCleanFilesDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCleanFilesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCleanInfoDlg dlg;
	// Generated message map functions
	//{{AFX_MSG(CCleanFilesDlg)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEANFILESDLG_H__B407FDD2_983C_42C2_9191_1A71AEF5F94D__INCLUDED_)
