#if !defined(AFX_WAITDLG_H__111B0AE2_C527_43D8_AC14_68F3CE0FF4AE__INCLUDED_)
#define AFX_WAITDLG_H__111B0AE2_C527_43D8_AC14_68F3CE0FF4AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaitDlg dialog
#include "PictureEx.h"
class CWaitDlg : public CDialog
{
// Construction
public:
	CWaitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaitDlg)
	enum { IDD = IDD_DIALOG5 };
	CPictureEx	m_gif;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaitDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDLG_H__111B0AE2_C527_43D8_AC14_68F3CE0FF4AE__INCLUDED_)
