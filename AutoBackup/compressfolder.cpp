// CompressFolder.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "CompressFolder.h"
#include "Cleaner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using jlib::win32::mfc::CFileOper;

/////////////////////////////////////////////////////////////////////////////
// CCompressFolderDlg dialog
static BOOL bSingleFolderOrSubFolders = TRUE;
static BOOL bDeleteFolder = TRUE;
static CString lastFolderPath = _T("");

CCompressFolderDlg::CCompressFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompressFolderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompressFolderDlg)
	m_path = _T("");
	m_check1 = FALSE;
	//}}AFX_DATA_INIT
}


void CCompressFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompressFolderDlg)
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Text(pDX, IDC_EDIT1, m_path);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompressFolderDlg, CDialog)
	//{{AFX_MSG_MAP(CCompressFolderDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO_SINGLE_FOLDER, OnRadioSingleFolder)
	ON_BN_CLICKED(IDC_RADIO_SUB_FOLDERS, OnRadioSubFolders)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressFolderDlg message handlers

BOOL CCompressFolderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_RADIO_SINGLE_FOLDER))->SetCheck(bSingleFolderOrSubFolders);
	((CButton*)GetDlgItem(IDC_RADIO_SUB_FOLDERS))->SetCheck(!bSingleFolderOrSubFolders);
	m_check1 = bDeleteFolder;
//	m_path = lastFolderPath;
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompressFolderDlg::OnButton1() 
{
	UpdateData();
	CString path = _T("");
	path = lastFolderPath;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{	
		m_path = path;
		lastFolderPath = path;
		UpdateData(0);
	}
}

void CCompressFolderDlg::OnOK() 
{
	UpdateData();
	bDeleteFolder = m_check1;
	CCleaner cl;
	if(!PathIsDirectory(m_path))
	{
		m_path.Empty();
		UpdateData(0);
		return;
	}
	
	if(bSingleFolderOrSubFolders)
	{
		cl.CompressEx(m_path);
		if(m_check1)
		{
			CFileOper::DeleteFolderAndAllSubFolder_Files(m_path);
		}
	}
	else
	{
		CString findtarget = m_path + "\\*.*";
		if(findtarget.GetLength() >= MAX_PATH_EX)
			return;
		
		CFileFind find;
		BOOL rc = find.FindFile(findtarget);
		
		while(rc)
		{
			rc = find.FindNextFile();

			if(find.IsDots())
				continue;

			if(find.IsDirectory())
			{
				CString folder = find.GetFilePath();
				cl.Clean(folder);
				cl.CompressEx(folder);
				if(m_check1)
				{
					CFileOper::DeleteFolderAndAllSubFolder_Files(folder);
				}
			}
		}
	}

	
	CDialog::OnOK();
}

void CCompressFolderDlg::OnRadioSingleFolder() 
{
	bSingleFolderOrSubFolders = TRUE;
}

void CCompressFolderDlg::OnRadioSubFolders() 
{
	bSingleFolderOrSubFolders = FALSE;
}
