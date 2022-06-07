// AutoBackupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "AutoBackupDlg.h"
#include "CleanFilesDlg.h"
#include "MultiProjectDlg.h"
#include "Resource.h"
#include "ConfigDlg.h"
#include "CompressFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using jlib::win32::mfc::CFileOper;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
		//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoBackupDlg dialog

CAutoBackupDlg::CAutoBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoBackupDlg::IDD, pParent)
	, m_backupFolder(_T(""))
	, m_hWndGif(NULL)
	, m_pConfigDlg(NULL)
	, m_pass(FALSE)
{
	//{{AFX_DATA_INIT(CAutoBackupDlg)
	m_backupName = _T("");
	m_check1 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;
	m_check2 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strSrcPathList.RemoveAll();
}

void CAutoBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoBackupDlg)
	DDX_Control(pDX, IDC_COMBO2, m_combodst);
	DDX_Control(pDX, IDC_COMBO1, m_combosrc);
	DDX_Control(pDX, IDC_EDIT3, m_edit);
	DDX_Text(pDX, IDC_EDIT3, m_backupName);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	DDX_Check(pDX, IDC_CHECK4, m_check4);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAutoBackupDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoBackupDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_CLEAN, OnClean)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(IDM_CFG, OnCfg)
	ON_WM_DESTROY()
	ON_COMMAND(IDM_COMPRESS, OnCompress)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoBackupDlg message handlers

BOOL CAutoBackupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CenterWindow();

	m_check1 = TRUE;
	m_check2 = TRUE;
	m_check3 = TRUE;
#ifndef _DEBUG
	m_check4 = TRUE;
#else
	m_check4 = FALSE;
#endif
	UpdateData(0);

	m_combosrc.SetFolder(stdstrpath);
	m_combosrc.InitList();
	m_combodst.SetFolder(stddstpath);
	m_combodst.InitList();

	SetRadiosCheck(1);
	SetTopMost(m_check4);

	waitDlg = new CWaitDlg();
	waitDlg->Create(IDD_DIALOG5, this);

	m_pConfigDlg = new CConfigDlg();
	m_pConfigDlg->Create(IDD_DIALOG_CONFIG, this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoBackupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoBackupDlg::OnPaint()
{
	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoBackupDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CAutoBackupDlg::OnButton1()
{
	// TODO: Add your control notification handler code here

	//CString strpath = "";
	//strpath.Format("%s", szPath);
	//m_srcpath = strpath;
	CString path;
	if (CFileOper::BrowseGetPath(path, m_hWnd)) {
		m_combosrc.AddString(path);
		UpdateData(0);
	}
}

void CAutoBackupDlg::OnButton2()
{
	// TODO: Add your control notification handler code here
	CString path;
	if (CFileOper::BrowseGetPath(path, m_hWnd)) {
		m_combodst.AddString(path);
		UpdateData(0);
	}
}

void CAutoBackupDlg::OnOK()
{
	// TODO: Add extra validation here
	UpdateData();
	CString dstpath;
	BOOL pass = FALSE;
	if (m_combodst.GetCurString(dstpath)) {
		m_backupFolder = dstpath + "\\" + m_backupName;
		if (!PathIsDirectory(m_backupFolder))
			CreateDirectory(m_backupFolder, NULL);
		if (PathIsDirectory(m_backupFolder)) {
			//SetCurrentDirectory(m_backupFolder);
			CString srcpath;
			if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()) {
				if (m_combosrc.GetCurString(srcpath))
					pass = (CFileOper::CopyFolder(m_backupFolder, srcpath, m_hWnd));
			} else {
				POSITION pos = m_strSrcPathList.GetHeadPosition();
				while (pos != NULL) {
					srcpath = m_strSrcPathList.GetNext(pos);
					pass = CFileOper::CopyFolder(m_backupFolder, srcpath, m_hWnd);
					if (!pass)
						break;
				}
			}

			if (pass) {
				//CloseHandle(CreateThread(NULL, 0, ThreadClean, this, 0, NULL));

				//waitDlg->ShowWindow(1);
				if (m_check1) {
					cl.Clean(m_backupFolder);
				}
				if (m_check3) {
					//cl.Compress(m_backupFolder);
					pass = cl.CompressEx(m_backupFolder);
					if (m_check2)
						pass = CFileOper::DeleteFolderAndAllSubFolder_Files(m_backupFolder);
				}
				//waitDlg->ShowWindow(0);
			}
		}
		if (pass) {
			GetCapture();
			MessageBox(L"backup ok!");
			CDialog::OnOK();
		} else
			MessageBox(L"backup fail!");
	}
}

void CAutoBackupDlg::OnCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	//UpdateData(0);
}

void CAutoBackupDlg::OnAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	m_edit.Empty();
	m_edit += (_T("1.记录使用过的目录\r\n"));
	m_edit += (_T("2.双击编辑框\"name\"可清空内容\r\n"));
	m_edit += (_T("3.添加后缀名库的配置，可选择需要清理的文件类型\r\n"));
	m_edit += (_T("4.添加压缩功能，可压缩指定的文件夹或指定文件夹的各个子目录\r\n"));
	m_edit += (_T("5.清理文件时遇到小于1MB的txt文件不清理\r\n"));
	m_edit += (_T("6.添加选项，是否删除源文件夹\r\n"));
	m_edit += (_T("7.解除路径长度不得大于260的限制，限制为1024\r\n"));
	m_edit += (_T("8.BUG.当路径长度大于260时，获取不了完整的路径名\r\n"));
	UpdateData(FALSE);
}

void CAutoBackupDlg::OnClean()
{
	// TODO: Add your command handler code here
	CCleanFilesDlg clean;
	clean.DoModal();
}

void CAutoBackupDlg::SetRadiosCheck(BOOL b1Check)
{
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(b1Check);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(!b1Check);


	m_combosrc.EnableWindow(b1Check);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(b1Check);
}

void CAutoBackupDlg::OnRadio2()
{
	// TODO: Add your control notification handler code here
	SetRadiosCheck(0);
	CMultiProjectDlg mpdlg;
	if (IDOK == mpdlg.DoModal()) {
		mpdlg.GetSelectedPath(m_strSrcPathList);
	}
}

void CAutoBackupDlg::OnRadio1()
{
	// TODO: Add your control notification handler code here
	SetRadiosCheck(1);
}

void CAutoBackupDlg::OnCheck4()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	SetTopMost(m_check4);
}

void CAutoBackupDlg::SetTopMost(BOOL bTop)
{
	CRect rc;
	GetWindowRect(&rc);
	::SetWindowPos(m_hWnd, bTop ? wndTopMost : wndNoTopMost,
				   rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
}

void CAutoBackupDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if (bShow)// && nStatus == SW_SHOW)
	{

	}
}

void CAutoBackupDlg::OnCfg()
{
	// TODO: Add your command handler code here
	//CConfigDlg cfg;
	//cfg.DoModal();
	m_pConfigDlg->ShowWindow(SW_SHOW);
}

DWORD WINAPI CAutoBackupDlg::ThreadClean(LPVOID lp)
{
	CAutoBackupDlg *dlg = (CAutoBackupDlg*)lp;
	dlg->cl.Clean(dlg->m_backupFolder);
	::PostMessage(dlg->m_hWndGif, WM_CLOSE, 0, 0);
	return 0;
}

void CAutoBackupDlg::OnDestroy()
{
	CDialog::OnDestroy();

	//SAFEDELETEDLG(waitDlg);	
	//SAFEDELETEDLG(m_pConfigDlg);	
}

void CAutoBackupDlg::OnCompress()
{
	CCompressFolderDlg cfd;
	cfd.DoModal();
}

void CAutoBackupDlg::OnCheck3()
{
	UpdateData();
	((CButton*)GetDlgItem(IDC_CHECK2))->EnableWindow(m_check3);
	m_check2 = m_check3;
	UpdateData(0);
}
