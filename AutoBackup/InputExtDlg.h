#if !defined(AFX_INPUTEXTDLG_H__C0AB3D6F_61FE_4453_A119_1F8E81D804AE__INCLUDED_)
#define AFX_INPUTEXTDLG_H__C0AB3D6F_61FE_4453_A119_1F8E81D804AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputExtDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputExtDlg dialog

class CInputExtDlg : public CDialog
{
// Construction
public:
	CInputExtDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputExtDlg)
	enum { IDD = IDD_DIALOG_EXT_STRING_INPUT };
	CString	m_ext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputExtDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputExtDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTEXTDLG_H__C0AB3D6F_61FE_4453_A119_1F8E81D804AE__INCLUDED_)
