#if !defined(AFX_CONFIGDLG_H__30B44706_5108_4763_9B4C_A866E042EC61__INCLUDED_)
#define AFX_CONFIGDLG_H__30B44706_5108_4763_9B4C_A866E042EC61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_DIALOG_CONFIG };
	CListBox	m_list2;
	CListBox	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL SetKeyValue(LPCTSTR lpszValueName, DWORD dwValueData);
	void InitCfg();

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMovl();
	afx_msg void OnButtonMovr();
	afx_msg void OnButtonAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__30B44706_5108_4763_9B4C_A866E042EC61__INCLUDED_)
