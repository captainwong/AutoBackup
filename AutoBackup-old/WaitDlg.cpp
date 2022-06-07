// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "WaitDlg.h"
#include "AutoBackupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitDlg dialog


CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitDlg)
	DDX_Control(pDX, IDC_GIF, m_gif);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialog)
	//{{AFX_MSG_MAP(CWaitDlg)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDlg message handlers

void CWaitDlg::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

BOOL CWaitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CAutoBackupDlg* dlg = (CAutoBackupDlg*)AfxGetMainWnd();
	dlg->m_hWndGif = m_hWnd;
	m_gif.ShowWindow(SW_SHOW);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaitDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CWaitDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(bShow)
	{
		m_gif.Load(MAKEINTRESOURCE(IDR_IMAGE1), _T("IMAGE"));
		m_gif.Draw();
	}
	else
	{
		m_gif.Stop();
		m_gif.UnLoad();
	}
}
