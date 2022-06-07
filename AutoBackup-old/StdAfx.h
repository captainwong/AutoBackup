// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6A8569EB_4F54_4002_ABE0_FDEA5E622427__INCLUDED_)
#define AFX_STDAFX_H__6A8569EB_4F54_4002_ABE0_FDEA5E622427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
//#include <Afxcoll.h>
#include "D:/global/MtVerify.h"
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")

const CString stdstrpath = "C:\\Documents and Settings\\All Users\\src";
const CString stddstpath = "C:\\Documents and Settings\\All Users\\dst";
#include "FileOper.h"

#ifndef _DEBUG
#include "XTToolkitPro.h"
#endif

#define MAX_PATH_EX 4096
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6A8569EB_4F54_4002_ABE0_FDEA5E622427__INCLUDED_)
