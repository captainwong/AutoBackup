// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBackup.h"
#include "ConfigDlg.h"
#include "InputExtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR INI_SECTION = L"ext";
/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_MOVL, OnButtonMovl)
	ON_BN_CLICKED(IDC_BUTTON_MOVR, OnButtonMovr)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

void CConfigDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CConfigDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitCfg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::InitCfg()
{
	CAutoBackupApp *afxApp = (CAutoBackupApp*)AfxGetApp();
	ASSERT(afxApp);
	HKEY hKey = NULL;
	LONG lRet = ::RegOpenKey(HKEY_CURRENT_USER, _T("SoftWare\\AutoBackup\\AutoBackup\\Exts"), &hKey);
	if(lRet != ERROR_SUCCESS)	//子键不存在，创建之，创建多个键值
	{
		lRet = ::RegCreateKey(HKEY_CURRENT_USER, _T("SoftWare\\AutoBackup\\AutoBackup\\Exts"), &hKey);
		if(lRet != ERROR_SUCCESS)
			return;

		// 初始化 后缀名列表
		afxApp->m_extList.AddTail(_T("BSC"));
		afxApp->WriteProfileInt(_T("Exts"), _T("BSC"), 1);
		afxApp->m_extList.AddTail(_T("DLL"));
		afxApp->WriteProfileInt(_T("Exts"), _T("DLL"), 1);
		afxApp->m_extList.AddTail(_T("EXE"));
		afxApp->WriteProfileInt(_T("Exts"), _T("EXE"), 1);
		afxApp->m_extList.AddTail(_T("IDB"));
		afxApp->WriteProfileInt(_T("Exts"), _T("IDB"), 1);
		afxApp->m_extList.AddTail(_T("ILK"));
		afxApp->WriteProfileInt(_T("Exts"), _T("ILK"), 1);
		afxApp->m_extList.AddTail(_T("LIB"));
		afxApp->WriteProfileInt(_T("Exts"), _T("LIB"), 1);
		afxApp->m_extList.AddTail(_T("LDB"));
		afxApp->WriteProfileInt(_T("Exts"), _T("LDB"), 1);
		afxApp->m_extList.AddTail(_T("OBJ"));
		afxApp->WriteProfileInt(_T("Exts"), _T("OBJ"), 1);
		afxApp->m_extList.AddTail(_T("PCH"));
		afxApp->WriteProfileInt(_T("Exts"), _T("PCH"), 1);
		afxApp->m_extList.AddTail(_T("PDB"));
		afxApp->WriteProfileInt(_T("Exts"), _T("PDB"), 1);
		afxApp->m_extList.AddTail(_T("RES"));
		afxApp->WriteProfileInt(_T("Exts"), _T("RES"), 1);
		afxApp->m_extList.AddTail(_T("SUP"));
		afxApp->WriteProfileInt(_T("Exts"), _T("SUP"), 1);
		afxApp->m_extList.AddTail(_T("TLB"));
		afxApp->WriteProfileInt(_T("Exts"), _T("TLB"), 1);
		afxApp->m_extList.AddTail(_T("TMP"));
		afxApp->WriteProfileInt(_T("Exts"), _T("TMP"), 1);
		afxApp->m_extList.AddTail(_T("SBR"));
		afxApp->WriteProfileInt(_T("Exts"), _T("SBR"), 1);

		POSITION pos = afxApp->m_extList.GetHeadPosition();
		while(pos)
		{
			m_list1.AddString(afxApp->m_extList.GetNext(pos));
		}
	}
	else		// 子键存在，读取所有键值
	{
		DWORD dwSubValues, dwMaxValueNameLen, dwMaxValueLen;
		lRet = ::RegQueryInfoKey(hKey, NULL, NULL, NULL, 
			NULL, NULL, NULL, &dwSubValues, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		if(lRet == ERROR_SUCCESS)
		{
			DWORD cMaxValueNameLen = dwMaxValueNameLen + 1;
			DWORD dwType = REG_DWORD;
			for(DWORD i = 0; lRet == ERROR_SUCCESS, i < dwSubValues; i++)
			{
				dwMaxValueNameLen = cMaxValueNameLen;	// for nul
				unsigned char* lpData = new unsigned char[dwMaxValueLen];
				TCHAR *szSubValueName = new TCHAR[cMaxValueNameLen];
				memset(szSubValueName, 0, sizeof(szSubValueName));
				lRet = RegEnumValue(hKey, i, szSubValueName, &dwMaxValueNameLen, NULL, &dwType, lpData, &dwMaxValueLen); 
				CString str = _T("");
				str.Format(_T("%s %d\n"), szSubValueName, *lpData);
				TRACE(str);
				int value = *(int*)lpData;
				if(value == 1)
				{
					afxApp->m_extList.AddTail(CString(szSubValueName));
					m_list2.AddString(szSubValueName);
				}
				else
				{
					m_list1.AddString(szSubValueName);
				}
				SAFEDELETEARR(lpData);
				SAFEDELETEARR(szSubValueName);
			}
		}
	}
}

void CConfigDlg::OnButtonMovl() 
{
	int index = m_list2.GetCurSel();
	if(index < 0)	return;

	CString ext = _T("");
	m_list2.GetText(index, ext);

	do
	{
		if(LB_ERR == m_list2.DeleteString(index))
			break;
		if(LB_ERR == m_list1.AddString(ext))
			break;
		if(!SetKeyValue(ext, 0))
			break;
	
		m_list2.SetCurSel(index);
	}
	while(0);
}

void CConfigDlg::OnButtonMovr() 
{
	int index = m_list1.GetCurSel();
	if(index < 0)	return;

	CString ext = _T("");
	m_list1.GetText(index, ext);

	do
	{
		if(LB_ERR == m_list1.DeleteString(index))
			break;
		if(LB_ERR == m_list2.AddString(ext))
			break;
		if(!SetKeyValue(ext, 1))
			break;

		m_list1.SetCurSel(index);
	}
	while(0);
}

BOOL CConfigDlg::SetKeyValue(LPCTSTR lpszValueName, DWORD dwValueData)
{
	CAutoBackupApp *afxApp = (CAutoBackupApp*)AfxGetApp();
	ASSERT(afxApp);

	if(afxApp->WriteProfileInt(_T("Exts"), lpszValueName, dwValueData))
	{
		if(dwValueData == 0)
			afxApp->m_extList.RemoveAt(afxApp->m_extList.Find(lpszValueName));
		else
			afxApp->m_extList.AddTail(lpszValueName);
		return TRUE;
	}
	return FALSE;
}



void CConfigDlg::OnButtonAdd() 
{
	CInputExtDlg ie;
	if(IDOK == ie.DoModal())
	{
		CString ext = ie.m_ext;
		ext.MakeUpper();
		do
		{
			if(LB_ERR == m_list2.AddString(ext))
				break;
			if(!SetKeyValue(ext, 1))
				break;
		}
		while(0);
	}
}
