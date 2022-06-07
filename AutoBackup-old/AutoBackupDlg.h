// AutoBackupDlg.h : header file
//

#if !defined(AFX_AUTOBACKUPDLG_H__5709BEB5_0C46_4F05_AE3D_5E978E1896AC__INCLUDED_)
#define AFX_AUTOBACKUPDLG_H__5709BEB5_0C46_4F05_AE3D_5E978E1896AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PathEdit.h"
#include "RecordList.h"
/////////////////////////////////////////////////////////////////////////////
// CAutoBackupDlg dialog
//const char *path = 
#include "Cleaner.h"
#include "WaitDlg.h"
class CConfigDlg;
class CAutoBackupDlg : public CDialog
{
// Construction
public:
	CAutoBackupDlg(CWnd* pParent = NULL);	// standard constructor
	CCleaner cl;
	HWND m_hWndGif;
	CStringList m_strSrcPathList;
// Dialog Data
	//{{AFX_DATA(CAutoBackupDlg)
	enum { IDD = IDD_AUTOBACKUP_DIALOG };
	CRecordList	m_combodst;
	CRecordList m_combosrc;
	CPathEdit	m_edit;
	CString	m_backupName;
	BOOL	m_check1;
	BOOL	m_check3;
	BOOL	m_check4;
	BOOL	m_check2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoBackupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static DWORD WINAPI ThreadClean(LPVOID lp);
	void SetTopMost(BOOL bTop);
	void SetRadiosCheck(BOOL b1Check);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAutoBackupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual void OnOK();
	afx_msg void OnCheck1();
	afx_msg void OnAbout();
	afx_msg void OnClean();
	afx_msg void OnRadio2();
	afx_msg void OnRadio1();
	afx_msg void OnCheck4();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCfg();
	afx_msg void OnDestroy();
	afx_msg void OnCompress();
	afx_msg void OnCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_backupFolder;
	CWaitDlg *waitDlg;
	CConfigDlg *m_pConfigDlg;
	BOOL m_pass;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOBACKUPDLG_H__5709BEB5_0C46_4F05_AE3D_5E978E1896AC__INCLUDED_)
