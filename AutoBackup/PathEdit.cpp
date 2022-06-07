// PathEdit.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "PathEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathEdit

CPathEdit::CPathEdit()
{
}

CPathEdit::~CPathEdit()
{
}


BEGIN_MESSAGE_MAP(CPathEdit, CEdit)
	//{{AFX_MSG_MAP(CPathEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathEdit message handlers

void CPathEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int i = 0;
	switch(nChar)
	{
	case ' ':
	case ':':
	case '/':
	case '\\':
	case '*':
	case '?':
	case '\"':
	case '<':
	case '>':
	case '|':
		{
			return;
		}
	default:
		break;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CPathEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetLimitText(MAX_PATH_EX);
	CEdit::PreSubclassWindow();
}

void CPathEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetWindowText("");
	CEdit::OnLButtonDblClk(nFlags, point);
}
