// MultiProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "MultiProjectDlg.h"
#include "Cleaner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString stdstrpath0 = stdstrpath + "\\src0";
CString stdstrpath1 = stdstrpath + "\\src1";
CString stdstrpath2 = stdstrpath + "\\src2";
CString stdstrpath3 = stdstrpath + "\\src3";
CString stdstrpath4 = stdstrpath + "\\src4";
CString stdstrpath5 = stdstrpath + "\\src5";
CString stdstrpath6 = stdstrpath + "\\src6";
CString stdstrpath7 = stdstrpath + "\\src7";
CString stdstrpath8 = stdstrpath + "\\src8";
CString stdstrpath9 = stdstrpath + "\\src9";

/////////////////////////////////////////////////////////////////////////////
// CMultiProjectDlg dialog
CStringList CMultiProjectDlg::m_pathList;

CMultiProjectDlg::CMultiProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiProjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiProjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pathList.RemoveAll();
}


void CMultiProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiProjectDlg)
	DDX_Control(pDX, IDC_COMBO8, m_combo8);
	DDX_Control(pDX, IDC_COMBO9, m_combo9);
	DDX_Control(pDX, IDC_COMBO7, m_combo7);
	DDX_Control(pDX, IDC_COMBO6, m_combo6);
	DDX_Control(pDX, IDC_COMBO5, m_combo5);
	DDX_Control(pDX, IDC_COMBO4, m_combo4);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO10, m_combo10);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiProjectDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiProjectDlg message handlers

void CMultiProjectDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo1.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo2.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo3.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo4.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo5.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo6.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo7.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo8.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo9.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	CString path;
	if(CFileOper::BrowseGetPath(path, m_hWnd))
	{
		m_combo10.AddString(path);
		UpdateData(0);
	}
}

void CMultiProjectDlg::InitCombos()
{
	m_combo1.SetFolder(stdstrpath1);
	m_combo1.InitList();

	m_combo2.SetFolder(stdstrpath2);
	m_combo2.InitList();

	m_combo3.SetFolder(stdstrpath3);
	m_combo3.InitList();

	m_combo4.SetFolder(stdstrpath4);
	m_combo4.InitList();

	m_combo5.SetFolder(stdstrpath5);
	m_combo5.InitList();

	m_combo6.SetFolder(stdstrpath6);
	m_combo6.InitList();

	m_combo7.SetFolder(stdstrpath7);
	m_combo7.InitList();

	m_combo8.SetFolder(stdstrpath8);
	m_combo8.InitList();

	m_combo9.SetFolder(stdstrpath9);
	m_combo9.InitList();

	m_combo10.SetFolder(stdstrpath0);
	m_combo10.InitList();
}

BOOL CMultiProjectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	InitCombos();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CMultiProjectDlg::GetSelectedPath(CStringList &list)
{
	try
	{
		list.RemoveAll();
		POSITION pos = m_pathList.GetHeadPosition();
		CString path = "";
		while(pos != NULL)
		{
			path = m_pathList.GetNext(pos);
			if((list.Find(path)) == NULL)
			{
				list.AddTail(path);
			}
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMultiProjectDlg::InerGetSelectedPath(CStringList &list)
{
	try
	{
		CString path = "";
		list.RemoveAll();
		if(m_combo1.GetCurString(path))
			list.AddTail(path);
		if(m_combo2.GetCurString(path))
			list.AddTail(path);
		if(m_combo3.GetCurString(path))
			list.AddTail(path);
		if(m_combo4.GetCurString(path))
			list.AddTail(path);
		if(m_combo5.GetCurString(path))
			list.AddTail(path);
		if(m_combo6.GetCurString(path))
			list.AddTail(path);
		if(m_combo7.GetCurString(path))
			list.AddTail(path);
		if(m_combo8.GetCurString(path))
			list.AddTail(path);
		if(m_combo9.GetCurString(path))
			list.AddTail(path);
		if(m_combo10.GetCurString(path))
			list.AddTail(path);
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

void CMultiProjectDlg::OnOK() 
{
	// TODO: Add extra validation here
	InerGetSelectedPath(m_pathList);
	CDialog::OnOK();
}
