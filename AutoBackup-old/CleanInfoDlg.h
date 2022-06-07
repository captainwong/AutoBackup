#if !defined(AFX_CLEANINFODLG_H__BCB2F7F9_CF9F_4C23_9778_DCE65BA086A2__INCLUDED_)
#define AFX_CLEANINFODLG_H__BCB2F7F9_CF9F_4C23_9778_DCE65BA086A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CleanInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCleanInfoDlg dialog

class CCleanInfoDlg : public CDialog
{
// Construction
public:
	void AddInfo(CString info);
	CCleanInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCleanInfoDlg)
	enum { IDD = IDD_DIALOG3 };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCleanInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCleanInfoDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CStringList m_InfoList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEANINFODLG_H__BCB2F7F9_CF9F_4C23_9778_DCE65BA086A2__INCLUDED_)
