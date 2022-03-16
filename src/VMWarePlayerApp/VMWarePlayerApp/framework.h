#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars


#include <afxsock.h>            // MFC socket extensions

#include <RegHelper.h>
#include <string>
#include <vector>
#if !defined(_UNICODE) && !defined(UNICODE)
#define TSTRING std::string
#define TO_TSTRING std::to_string
#define TSTRINGVECTOR std::vector<std::string>
#else
#define TSTRING std::wstring
#define TO_TSTRING std::to_wstring
#define TSTRINGVECTOR std::vector<std::wstring>
#endif

__inline static
void RegisterDropFilesEvent(HWND hWnd)
{
#ifndef WM_COPYGLOBALDATA
#define WM_COPYGLOBALDAYA	0x0049
#endif
#ifndef MSGFLT_ADD
#define MSGFLT_ADD 1
#endif
#ifndef MSGFLT_REMOVE
#define MSGFLT_REMOVE 2
#endif
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_ACCEPTFILES);
	typedef BOOL(WINAPI* LPFN_ChangeWindowMessageFilter)(__in UINT message, __in DWORD dwFlag);
	LPFN_ChangeWindowMessageFilter pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter)GetProcAddress(GetModuleHandle(TEXT("USER32.DLL")), ("ChangeWindowMessageFilter"));
	if (pfnChangeWindowMessageFilter)
	{
		pfnChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
		pfnChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
		pfnChangeWindowMessageFilter(WM_COPYGLOBALDAYA, MSGFLT_ADD);// 0x0049 == WM_COPYGLOBALDATA
	}
}
//#include <Psapi.h>
//#pragma comment(lib, "psapi")
__inline static
int WINAPI GetWindowProcessImageFilePath(HWND hWnd, LPSTR lpString, int nMaxCount)
{
	typedef DWORD(WINAPI*PFN_GetProcessImageFileNameA)(HANDLE hProcess, LPSTR lpFilename, DWORD nSize);
	int nLength = (-1);
	DWORD dwProcessId = 0;
	HANDLE hProcess = NULL;
	HMODULE hModulePSAPI = NULL;
	CHAR szModuleFileName[MAX_PATH] = { 0 };
	PFN_GetProcessImageFileNameA pfnGetProcessImageFileNameA = NULL;
	if (::GetWindowThreadProcessId(hWnd, &dwProcessId) > 0 && dwProcessId > 0)
	{
		pfnGetProcessImageFileNameA = (PFN_GetProcessImageFileNameA)GetProcAddress(GetModuleHandleA("KERNEL32"), ("GetProcessImageFileNameA"));
		if (pfnGetProcessImageFileNameA == NULL)
		{
			pfnGetProcessImageFileNameA = (PFN_GetProcessImageFileNameA)GetProcAddress(GetModuleHandleA("PSAPI"), ("GetProcessImageFileNameA"));
			if (pfnGetProcessImageFileNameA == NULL)
			{
				pfnGetProcessImageFileNameA = (PFN_GetProcessImageFileNameA)GetProcAddress((hModulePSAPI = LoadLibraryA("PSAPI")), ("GetProcessImageFileNameA"));
			}
		}
		if (pfnGetProcessImageFileNameA != NULL)
		{
			hProcess = ::OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, TRUE, dwProcessId);
			if (hProcess != NULL)
			{
				nLength = pfnGetProcessImageFileNameA(hProcess, lpString, nMaxCount);
				::CloseHandle(hProcess);
				hProcess = NULL;
			}
		}
		if (hModulePSAPI != NULL)
		{
			::FreeLibrary(hModulePSAPI);
			hModulePSAPI = NULL;
		}
	}
	return nLength;
}
__inline static
int WINAPI GetWindowProcessImageFilePath(HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	typedef DWORD(WINAPI*PFN_GetProcessImageFileNameW)(HANDLE hProcess, LPWSTR lpFilename, DWORD nSize);
	int nLength = (-1);
	DWORD dwProcessId = 0;
	HANDLE hProcess = NULL;
	HMODULE hModulePSAPI = NULL;
	WCHAR szModuleFileName[MAX_PATH] = { 0 };
	PFN_GetProcessImageFileNameW pfnGetProcessImageFileNameW = NULL;
	if (::GetWindowThreadProcessId(hWnd, &dwProcessId) > 0 && dwProcessId > 0)
	{
		pfnGetProcessImageFileNameW = (PFN_GetProcessImageFileNameW)GetProcAddress(GetModuleHandleW(L"KERNEL32"), ("GetProcessImageFileNameW"));
		if (pfnGetProcessImageFileNameW == NULL)
		{
			pfnGetProcessImageFileNameW = (PFN_GetProcessImageFileNameW)GetProcAddress(GetModuleHandleW(L"PSAPI"), ("GetProcessImageFileNameW"));
			if (pfnGetProcessImageFileNameW == NULL)
			{
				pfnGetProcessImageFileNameW = (PFN_GetProcessImageFileNameW)GetProcAddress((hModulePSAPI = LoadLibraryW(L"PSAPI")), ("GetProcessImageFileNameW"));
			}
		}
		if (pfnGetProcessImageFileNameW != NULL)
		{
			hProcess = ::OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, TRUE, dwProcessId);
			if (hProcess != NULL)
			{
				nLength = pfnGetProcessImageFileNameW(hProcess, lpString, nMaxCount);
				::CloseHandle(hProcess);
				hProcess = NULL;
			}
		}
		if (hModulePSAPI != NULL)
		{
			::FreeLibrary(hModulePSAPI);
			hModulePSAPI = NULL;
		}
	}
	return nLength;
}
__inline static
int WINAPI GetWindowProcessModuleImageFilePath(HWND hWnd, LPSTR lpString, int nMaxCount)
{
	typedef DWORD(WINAPI*PFN_GetModuleFileNameExA)(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);
	int nLength = (-1);
	DWORD dwProcessId = 0;
	HANDLE hProcess = NULL;
	HMODULE hModulePSAPI = NULL;
	CHAR szModuleFileName[MAX_PATH] = { 0 };
	PFN_GetModuleFileNameExA pfnGetModuleFileNameExA = NULL;
	if (::GetWindowThreadProcessId(hWnd, &dwProcessId) > 0 && dwProcessId > 0)
	{
		pfnGetModuleFileNameExA = (PFN_GetModuleFileNameExA)GetProcAddress(GetModuleHandleA("KERNEL32"), ("GetModuleFileNameExA"));
		if (pfnGetModuleFileNameExA == NULL)
		{
			pfnGetModuleFileNameExA = (PFN_GetModuleFileNameExA)GetProcAddress(GetModuleHandleA("PSAPI"), ("GetModuleFileNameExA"));
			if (pfnGetModuleFileNameExA == NULL)
			{
				pfnGetModuleFileNameExA = (PFN_GetModuleFileNameExA)GetProcAddress((hModulePSAPI = LoadLibraryA("PSAPI")), ("GetModuleFileNameExA"));
			}
		}
		if (pfnGetModuleFileNameExA != NULL)
		{
			hProcess = ::OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, TRUE, dwProcessId);
			if (hProcess != NULL)
			{
				nLength = pfnGetModuleFileNameExA(hProcess, NULL, lpString, nMaxCount);
				::CloseHandle(hProcess);
				hProcess = NULL;
			}
		}
		if (hModulePSAPI != NULL)
		{
			::FreeLibrary(hModulePSAPI);
			hModulePSAPI = NULL;
		}
	}
	return nLength;
}
__inline static
int WINAPI GetWindowProcessModuleImageFilePath(HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	typedef DWORD(WINAPI*PFN_GetModuleFileNameExW)(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize0);
	int nLength = (-1);
	DWORD dwProcessId = 0;
	HANDLE hProcess = NULL;
	HMODULE hModulePSAPI = NULL;
	WCHAR wzModuleFileName[MAX_PATH] = { 0 };
	PFN_GetModuleFileNameExW pfnGetModuleFileNameExW = NULL;
	if (::GetWindowThreadProcessId(hWnd, &dwProcessId) > 0 && dwProcessId > 0)
	{
		pfnGetModuleFileNameExW = (PFN_GetModuleFileNameExW)GetProcAddress(GetModuleHandleW(L"KERNEL32"), ("GetModuleFileNameExW"));
		if (pfnGetModuleFileNameExW == NULL)
		{
			pfnGetModuleFileNameExW = (PFN_GetModuleFileNameExW)GetProcAddress(GetModuleHandleW(L"PSAPI"), ("GetModuleFileNameExW"));
			if (pfnGetModuleFileNameExW == NULL)
			{
				pfnGetModuleFileNameExW = (PFN_GetModuleFileNameExW)GetProcAddress((hModulePSAPI = LoadLibraryW(L"PSAPI")), ("GetModuleFileNameExW"));
			}
		}
		if (pfnGetModuleFileNameExW != NULL)
		{
			hProcess = ::OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, TRUE, dwProcessId);
			if (hProcess != NULL)
			{
				nLength = pfnGetModuleFileNameExW(hProcess, NULL, lpString, nMaxCount);
				::CloseHandle(hProcess);
				hProcess = NULL;
			}
		}
		if (hModulePSAPI != NULL)
		{
			::FreeLibrary(hModulePSAPI);
			hModulePSAPI = NULL;
		}
	}
	return nLength;
}

__inline static
BOOL WINAPI StartupProgram(LPCSTR lpApplicationName, LPSTR lpCommandLine = NULL)
{
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.wShowWindow = STARTF_USESHOWWINDOW;
	// Start the child process. 
	if (!CreateProcessA(
		lpApplicationName,   // No module name (use command line)
		lpCommandLine,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, WAIT_TIMEOUT);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return TRUE;
}

__inline static
BOOL WINAPI StartupProgram(LPCWSTR lpApplicationName, LPWSTR lpCommandLine = NULL)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.wShowWindow = STARTF_USESHOWWINDOW;
	// Start the child process. 
	if (!CreateProcessW(
		lpApplicationName,   // No module name (use command line)
		lpCommandLine,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, WAIT_TIMEOUT);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return TRUE;
}

// This macro is the same as IMPLEMENT_OLECREATE, except it passes TRUE
// for the bMultiInstance parameter to the COleObjectFactory constructor.
// We want a separate instance of this application to be launched for
// each automation proxy object requested by automation controllers.
#ifndef IMPLEMENT_OLECREATE2
#define IMPLEMENT_OLECREATE2(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
                RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
        const AFX_DATADEF GUID class_name::guid = \
                { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE2

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


