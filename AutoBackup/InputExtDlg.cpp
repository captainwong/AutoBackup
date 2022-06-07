// InputExtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "InputExtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputExtDlg dialog


CInputExtDlg::CInputExtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputExtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputExtDlg)
	m_ext = _T("");
	//}}AFX_DATA_INIT
}


void CInputExtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputExtDlg)
	DDX_Text(pDX, IDC_EDIT1, m_ext);
	DDV_MaxChars(pDX, m_ext, 12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputExtDlg, CDialog)
	//{{AFX_MSG_MAP(CInputExtDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputExtDlg message handlers

void CInputExtDlg::OnOK() 
{
	UpdateData();
	CDialog::OnOK();
}
