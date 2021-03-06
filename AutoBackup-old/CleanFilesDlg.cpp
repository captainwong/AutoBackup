// CleanFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "CleanFilesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCleanFilesDlg dialog


CCleanFilesDlg::CCleanFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCleanFilesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCleanFilesDlg)
	m_path = _T("");
	//}}AFX_DATA_INIT
}


void CCleanFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCleanFilesDlg)
	DDX_Text(pDX, IDC_EDIT1, m_path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCleanFilesDlg, CDialog)
	//{{AFX_MSG_MAP(CCleanFilesDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCleanFilesDlg message handlers

void CCleanFilesDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH_EX];
	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.hwndOwner = GetSafeHwnd();
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpszTitle = "select folder";

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
	{
		return;
	}

	SHGetPathFromIDList(idl, szPath);
	m_path.Format("%s", szPath);
	UpdateData(0);
}

void CCleanFilesDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString filePath = m_path;
	if(PathIsDirectory(m_path))
	{
		cl.StartShowInfo();
		cl.Clean(filePath);
		

		CString msg;
		DWORD dwLen = cl.GetCleandLength();
		DWORD dwCnt = cl.GetCleandCount();
		msg.Format(_T("clean ok, %d files cleand, total %dMb %dKb"), dwCnt, dwLen / 1024 / 1024, dwLen % 1024);
		if(IDYES == ::MessageBox(m_hWnd, msg, _T(""), MB_YESNO | MB_ICONQUESTION))
		{
			cl.ShowInfo();
		}
	}
}
