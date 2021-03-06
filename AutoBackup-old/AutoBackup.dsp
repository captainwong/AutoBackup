# Microsoft Developer Studio Project File - Name="AutoBackup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AutoBackup - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AutoBackup.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AutoBackup.mak" CFG="AutoBackup - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AutoBackup - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AutoBackup - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AutoBackup - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Release/AutoBackup.exe"

!ELSEIF  "$(CFG)" == "AutoBackup - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../Debug/AutoBackup.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AutoBackup - Win32 Release"
# Name "AutoBackup - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AutoBackup.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoBackup.rc
# End Source File
# Begin Source File

SOURCE=.\AutoBackupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cleaner.cpp
# End Source File
# Begin Source File

SOURCE=.\CleanFilesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CleanInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CompressFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputExtDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LastTasks.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiProjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PathEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AutoBackup.h
# End Source File
# Begin Source File

SOURCE=.\AutoBackupDlg.h
# End Source File
# Begin Source File

SOURCE=.\Cleaner.h
# End Source File
# Begin Source File

SOURCE=.\CleanFilesDlg.h
# End Source File
# Begin Source File

SOURCE=.\CleanInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\CompressFolder.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileOper.h
# End Source File
# Begin Source File

SOURCE=.\InputExtDlg.h
# End Source File
# Begin Source File

SOURCE=.\LastTasks.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\MultiProjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\PathEdit.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\RecordList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\autobackup.ico
# End Source File
# Begin Source File

SOURCE=.\res\AutoBackup.ico
# End Source File
# Begin Source File

SOURCE=.\res\AutoBackup.rc2
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\loading.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\xpStyle.manifest
# End Source File
# End Target
# End Project
