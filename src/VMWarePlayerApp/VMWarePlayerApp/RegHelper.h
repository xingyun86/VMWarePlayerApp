// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include <string>
#include <vector>
#include <WinSock2.h>

#define STRINGVECTOR std::vector<std::string>
#define WSTRINGVECTOR std::vector<std::wstring>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
class RegHelper
{
#define MY_SUCCEEDED(X) ((X) == ERROR_SUCCESS)
public:
    static BOOL RegEnumKeys(STRINGVECTOR& vKey, LPCSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;

        CHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string 
        CHAR    achClass[MAX_PATH] = ("");  // buffer for class name 
        DWORD    cchClassName = MAX_PATH;  // size of class string 
        DWORD    cSubKeys = 0;               // number of subkeys 
        DWORD    cbMaxSubKey;              // longest subkey size 
        DWORD    cchMaxClass;              // longest class string 
        DWORD    cValues;              // number of values for key 
        DWORD    cchMaxValue;          // longest value name 
        DWORD    cbMaxValueData;       // longest value data 
        DWORD    cbSecurityDescriptor; // size of security descriptor 
        FILETIME ftLastWriteTime;      // last write time 

        CHAR  achValue[MAX_VALUE_NAME];
        DWORD cchValue = MAX_VALUE_NAME;

        if (MY_SUCCEEDED(lStatus = RegOpenKeyA(hKey, lpSubKey, &hKeyOpen)))
        {
            // Get the class name and the value count. 
            if (MY_SUCCEEDED(lStatus = RegQueryInfoKeyA(
                hKeyOpen,                    // key handle 
                achClass,                // buffer for class name 
                &cchClassName,           // size of class string 
                NULL,                    // reserved 
                &cSubKeys,               // number of subkeys 
                &cbMaxSubKey,            // longest subkey size 
                &cchMaxClass,            // longest class string 
                &cValues,                // number of values for this key 
                &cchMaxValue,            // longest value name 
                &cbMaxValueData,         // longest value data 
                &cbSecurityDescriptor,   // security descriptor 
                &ftLastWriteTime)))      // last write time 
            {
                // Enumerate the subkeys, until RegEnumKeyEx fails.
                if (cSubKeys > 0)
                {
                    for (DWORD i = 0; i < cSubKeys; i++)
                    {
                        cbName = MAX_KEY_LENGTH;
                        if (MY_SUCCEEDED(lStatus = RegEnumKeyExA(hKeyOpen, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime)))
                        {
                            vKey.emplace_back(achKey);
                        }
                    }
                }
                bRet = TRUE;
            }
            RegCloseKey(hKeyOpen);
        }

        return bRet;
    }
    static BOOL RegEnumKeys(WSTRINGVECTOR& vKey, LPCWSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;

        WCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string 
        WCHAR    achClass[MAX_PATH] = (L"");  // buffer for class name 
        DWORD    cchClassName = MAX_PATH;  // size of class string 
        DWORD    cSubKeys = 0;               // number of subkeys 
        DWORD    cbMaxSubKey;              // longest subkey size 
        DWORD    cchMaxClass;              // longest class string 
        DWORD    cValues;              // number of values for key 
        DWORD    cchMaxValue;          // longest value name 
        DWORD    cbMaxValueData;       // longest value data 
        DWORD    cbSecurityDescriptor; // size of security descriptor 
        FILETIME ftLastWriteTime;      // last write time 

        WCHAR  achValue[MAX_VALUE_NAME];
        DWORD cchValue = MAX_VALUE_NAME;

        if (MY_SUCCEEDED(lStatus = RegOpenKeyW(hKey, lpSubKey, &hKeyOpen)))
        {
            // Get the class name and the value count. 
            if (MY_SUCCEEDED(lStatus = RegQueryInfoKeyW(
                hKeyOpen,                    // key handle 
                achClass,                // buffer for class name 
                &cchClassName,           // size of class string 
                NULL,                    // reserved 
                &cSubKeys,               // number of subkeys 
                &cbMaxSubKey,            // longest subkey size 
                &cchMaxClass,            // longest class string 
                &cValues,                // number of values for this key 
                &cchMaxValue,            // longest value name 
                &cbMaxValueData,         // longest value data 
                &cbSecurityDescriptor,   // security descriptor 
                &ftLastWriteTime)))      // last write time 
            {
                // Enumerate the subkeys, until RegEnumKeyEx fails.
                if (cSubKeys > 0)
                {
                    for (DWORD i = 0; i < cSubKeys; i++)
                    {
                        cbName = MAX_KEY_LENGTH;
                        if (MY_SUCCEEDED(lStatus = RegEnumKeyExW(hKeyOpen, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime)))
                        {
                            vKey.emplace_back(achKey);
                        }
                    }
                }
                bRet = TRUE;
            }
            RegCloseKey(hKeyOpen);
        }

        return bRet;
    }
    static BOOL RegEnumValues(STRINGVECTOR& vValue, LPCSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;

        CHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string 
        CHAR    achClass[MAX_PATH] = ("");  // buffer for class name 
        DWORD    cchClassName = MAX_PATH;  // size of class string 
        DWORD    cSubKeys = 0;               // number of subkeys 
        DWORD    cbMaxSubKey;              // longest subkey size 
        DWORD    cchMaxClass;              // longest class string 
        DWORD    cValues;              // number of values for key 
        DWORD    cchMaxValue;          // longest value name 
        DWORD    cbMaxValueData;       // longest value data 
        DWORD    cbSecurityDescriptor; // size of security descriptor 
        FILETIME ftLastWriteTime;      // last write time 

        CHAR  achValue[MAX_VALUE_NAME];
        DWORD cchValue = MAX_VALUE_NAME;

        if (MY_SUCCEEDED(lStatus = RegOpenKeyA(hKey, lpSubKey, &hKeyOpen)))
        {
            // Get the class name and the value count. 
            if (MY_SUCCEEDED(lStatus = RegQueryInfoKeyA(
                hKeyOpen,                    // key handle 
                achClass,                // buffer for class name 
                &cchClassName,           // size of class string 
                NULL,                    // reserved 
                &cSubKeys,               // number of subkeys 
                &cbMaxSubKey,            // longest subkey size 
                &cchMaxClass,            // longest class string 
                &cValues,                // number of values for this key 
                &cchMaxValue,            // longest value name 
                &cbMaxValueData,         // longest value data 
                &cbSecurityDescriptor,   // security descriptor 
                &ftLastWriteTime)))      // last write time 
            {
                // Enumerate the subkeys, until RegEnumKeyEx fails.
                if (cSubKeys > 0)
                {
                    for (DWORD i = 0; i < cSubKeys; i++)
                    {
                        cchValue = MAX_VALUE_NAME;
                        achValue[0] = '\0';
                        if (MY_SUCCEEDED(lStatus = RegEnumValueA(hKeyOpen, i, achValue, &cchValue, NULL, NULL, NULL, NULL)))
                        {
                            vValue.emplace_back(achKey);
                        }
                    }
                }
                bRet = TRUE;
            }
            RegCloseKey(hKeyOpen);
        }

        return bRet;
    }
    static BOOL RegEnumValues(WSTRINGVECTOR& vValue, LPCWSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;

        WCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string 
        WCHAR    achClass[MAX_PATH] = (L"");  // buffer for class name 
        DWORD    cchClassName = MAX_PATH;  // size of class string 
        DWORD    cSubKeys = 0;               // number of subkeys 
        DWORD    cbMaxSubKey;              // longest subkey size 
        DWORD    cchMaxClass;              // longest class string 
        DWORD    cValues;              // number of values for key 
        DWORD    cchMaxValue;          // longest value name 
        DWORD    cbMaxValueData;       // longest value data 
        DWORD    cbSecurityDescriptor; // size of security descriptor 
        FILETIME ftLastWriteTime;      // last write time 

        WCHAR  achValue[MAX_VALUE_NAME];
        DWORD cchValue = MAX_VALUE_NAME;

        if (MY_SUCCEEDED(lStatus = RegOpenKeyW(hKey, lpSubKey, &hKeyOpen)))
        {
            // Get the class name and the value count. 
            if (MY_SUCCEEDED(lStatus = RegQueryInfoKeyW(
                hKeyOpen,                    // key handle 
                achClass,                // buffer for class name 
                &cchClassName,           // size of class string 
                NULL,                    // reserved 
                &cSubKeys,               // number of subkeys 
                &cbMaxSubKey,            // longest subkey size 
                &cchMaxClass,            // longest class string 
                &cValues,                // number of values for this key 
                &cchMaxValue,            // longest value name 
                &cbMaxValueData,         // longest value data 
                &cbSecurityDescriptor,   // security descriptor 
                &ftLastWriteTime)))      // last write time 
            {
                if (cValues > 0)
                {
                    for (DWORD i = 0; i < cValues; i++)
                    {
                        cchValue = MAX_VALUE_NAME;
                        achValue[0] = L'\0';
                        if (MY_SUCCEEDED(lStatus = RegEnumValueW(hKeyOpen, i, achValue, &cchValue, NULL, NULL, NULL, NULL)))
                        {
                            vValue.emplace_back(achKey);
                        }
                    }
                }
                bRet = TRUE;
            }
            RegCloseKey(hKeyOpen);
        }

        return bRet;
    }
    static BOOL RegRemoveKey(LPCSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        LSTATUS lStatus = NO_ERROR;
        bRet = MY_SUCCEEDED(lStatus = RegDeleteKeyA(hKey, lpSubKey));
        return bRet;
    }    
    static BOOL RegRemoveKey(LPCWSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        LSTATUS lStatus = NO_ERROR;
        bRet = MY_SUCCEEDED(lStatus = RegDeleteKeyW(hKey, lpSubKey));
        return bRet;
    }
    // 配置应用程序参数设置
    static BOOL RegSetKey(LPCSTR lpValue, DWORD cbValueSize, DWORD dwType, LPCSTR lpKey, LPCSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;
        if (MY_SUCCEEDED(lStatus = RegOpenKeyA(hKey, lpSubKey, &hKeyOpen))
            || MY_SUCCEEDED(lStatus = RegCreateKeyA(hKey, lpSubKey, &hKeyOpen)))
        {
            bRet = MY_SUCCEEDED(lStatus = RegSetValueExA(hKeyOpen, lpKey, 0, dwType, (LPBYTE)lpValue, cbValueSize * sizeof(CHAR)));
            lStatus = RegCloseKey(hKeyOpen);
        }
        return bRet;
    }
    static BOOL RegSetKey(LPCWSTR lpValue, DWORD cbValueSize, DWORD dwType, LPCWSTR lpKey, LPCWSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;
        if (MY_SUCCEEDED(lStatus = RegOpenKeyW(hKey, lpSubKey, &hKeyOpen))
            || MY_SUCCEEDED(lStatus = RegCreateKeyW(hKey, lpSubKey, &hKeyOpen)))
        {
            bRet = MY_SUCCEEDED(lStatus = RegSetValueExW(hKeyOpen, lpKey, 0, dwType, (LPBYTE)lpValue, cbValueSize * sizeof(WCHAR)));
            lStatus = RegCloseKey(hKeyOpen);
        }
        return bRet;
    }
    static BOOL RegGetKey(LPSTR lpValue, DWORD *pcbValueSize, DWORD *dwType, LPCSTR lpKey, LPCSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;
        if (MY_SUCCEEDED(lStatus = RegOpenKeyA(hKey, lpSubKey, &hKeyOpen))
            || MY_SUCCEEDED(lStatus = RegCreateKeyA(hKey, lpSubKey, &hKeyOpen)))
        {
            bRet = MY_SUCCEEDED(lStatus = RegQueryValueExA(hKeyOpen, lpKey, NULL, dwType, (LPBYTE)lpValue, pcbValueSize));
            lStatus = RegCloseKey(hKeyOpen);
        }
        return bRet;
    }
    static BOOL RegGetKey(LPWSTR lpValue, DWORD* pcbValueSize, DWORD* dwType, LPCWSTR lpKey, LPCWSTR lpSubKey, HKEY hKey)
    {
        BOOL bRet = FALSE;
        HKEY hKeyOpen = NULL;
        LSTATUS lStatus = NO_ERROR;
        if (MY_SUCCEEDED(lStatus = RegOpenKeyW(hKey, lpSubKey, &hKeyOpen))
            || MY_SUCCEEDED(lStatus = RegCreateKeyW(hKey, lpSubKey, &hKeyOpen)))
        {
            bRet = MY_SUCCEEDED(lStatus = RegQueryValueExW(hKeyOpen, lpKey, NULL, dwType, (LPBYTE)lpValue, pcbValueSize));
            lStatus = RegCloseKey(hKeyOpen);
        }
        return bRet;
    }
    // 配置应用程序参数设置
    static BOOL RegSetString(LPCSTR lpValue, LPCSTR lpKey, LPCSTR lpSubKey, HKEY hKey = HKEY_CURRENT_USER)
    {
        return RegSetKey(lpValue, lstrlenA(lpValue), REG_SZ, lpKey, lpSubKey, hKey);
    }
    static BOOL RegSetString(LPCWSTR lpValue, LPCWSTR lpKey, LPCWSTR lpSubKey, HKEY hKey = HKEY_CURRENT_USER)
    {
        return RegSetKey(lpValue, lstrlenW(lpValue), REG_SZ, lpKey, lpSubKey, hKey);
    }
    static BOOL RegGetString(LPSTR lpValue, DWORD * pcbValueSize, LPCSTR lpKey, LPCSTR lpSubKey, HKEY hKey = HKEY_CURRENT_USER)
    {
        return RegGetKey(lpValue, pcbValueSize, NULL, lpKey, lpSubKey, hKey);
    }
    static BOOL RegGetString(LPWSTR lpValue, DWORD* pcbValueSize, LPCWSTR lpKey, LPCWSTR lpSubKey, HKEY hKey = HKEY_CURRENT_USER)
    {
        return RegGetKey(lpValue, pcbValueSize, NULL, lpKey, lpSubKey, hKey);
    }
};
