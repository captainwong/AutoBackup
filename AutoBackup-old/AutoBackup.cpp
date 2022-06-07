// AutoBackup.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "AutoBackupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoBackupApp

BEGIN_MESSAGE_MAP(CAutoBackupApp, CWinApp)
	//{{AFX_MSG_MAP(CAutoBackupApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoBackupApp construction

CAutoBackupApp::CAutoBackupApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAutoBackupApp object

CAutoBackupApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAutoBackupApp initialization

BOOL CAutoBackupApp::InitInstance()
{
	AfxEnableControlContainer();

	SetRegistryKey(_T("AutoBackup"));

#ifndef _DEBUG
	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);
	XTPSkinManager()->LoadSkin( _T("Vista.cjstyles")); 
#endif

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	::SetCurrentDirectory(GetModuleFilePath());

	CAutoBackupDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	//CLog::Release();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
