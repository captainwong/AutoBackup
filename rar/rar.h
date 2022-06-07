
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RAR_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RAR_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#include "resource.h"

#define RAR_API extern "C" __declspec(dllexport)

namespace RAR
{
RAR_API bool Compress(LPCTSTR srcPath, LPCTSTR dstFolder, LPCTSTR dstName);
RAR_API bool Decompress(LPCTSTR srcRarPath, LPCTSTR dstFolder);
};