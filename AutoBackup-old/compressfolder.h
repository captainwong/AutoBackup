#if !defined(AFX_COMPRESSFOLDER_H__CCF0EF9F_3B98_476F_B9F0_829EB0F948AD__INCLUDED_)
#define AFX_COMPRESSFOLDER_H__CCF0EF9F_3B98_476F_B9F0_829EB0F948AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CompressFolder.h : header file
//
#include "PathEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CCompressFolderDlg dialog

class CCompressFolderDlg : public CDialog
{
// Construction
public:
	CCompressFolderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompressFolderDlg)
	enum { IDD = IDD_DIALOG_COMPRESS_FOLDER };
	CButton	m_btn;
	CString	m_path;
	BOOL	m_check1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressFolderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompressFolderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	virtual void OnOK();
	afx_msg void OnRadioSingleFolder();
	afx_msg void OnRadioSubFolders();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPRESSFOLDER_H__CCF0EF9F_3B98_476F_B9F0_829EB0F948AD__INCLUDED_)
