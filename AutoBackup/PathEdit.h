#if !defined(AFX_PATHEDIT_H__A23E7650_06A8_41A1_A6DB_1E07A0471F66__INCLUDED_)
#define AFX_PATHEDIT_H__A23E7650_06A8_41A1_A6DB_1E07A0471F66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPathEdit window

class CPathEdit : public CEdit
{
// Construction
public:
	CPathEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathEdit)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPathEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPathEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHEDIT_H__A23E7650_06A8_41A1_A6DB_1E07A0471F66__INCLUDED_)
