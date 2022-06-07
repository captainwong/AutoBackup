// CleanInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "CleanInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCleanInfoDlg dialog

CCleanInfoDlg::CCleanInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCleanInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCleanInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_InfoList.RemoveAll();
}


void CCleanInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCleanInfoDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCleanInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CCleanInfoDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCleanInfoDlg message handlers

void CCleanInfoDlg::AddInfo(CString info)
{
	//m_list.AddString(info);
	//info.ReleaseBuffer();
	m_InfoList.AddTail(info);
}

void CCleanInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	POSITION pos = m_InfoList.GetHeadPosition();
	while(pos)
	{
		m_list.AddString(m_InfoList.GetNext(pos));
	}
}
