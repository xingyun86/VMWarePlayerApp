
// VMWarePlayerApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVMWarePlayerAppApp:
// See VMWarePlayerApp.cpp for the implementation of this class
//

class CVMWarePlayerAppApp : public CWinApp
{
public:
	CVMWarePlayerAppApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
#define VMWAREPLAYER_HKEY					HKEY_CURRENT_USER
#define VMWAREPLAYER_SUBKEY					"SOFTWARE\\VMWarePlayer"
#define VMWAREPLAYER_SUBKEY_LIST			VMWAREPLAYER_SUBKEY"\\List"
#define VMWAREPLAYER_KEY_LABEL				"Label"
#define VMWAREPLAYER_KEY_CLASS				"Class"
#define VMWAREPLAYER_KEY_IMAGE				"Image"
#define VMWAREPLAYER_KEY_PARAM				"Param"
	CListCtrl* m_pListCtrl = NULL;
	HKEY m_hCurrentKey = VMWAREPLAYER_HKEY;
	LPCTSTR m_lpszSubKey = TEXT(VMWAREPLAYER_SUBKEY);
	LPCTSTR m_lpszSubKeyList = TEXT(VMWAREPLAYER_SUBKEY_LIST);
	const std::vector<TSTRING> m_vKeys = { TEXT(VMWAREPLAYER_KEY_LABEL), TEXT(VMWAREPLAYER_KEY_CLASS), TEXT(VMWAREPLAYER_KEY_IMAGE), TEXT(VMWAREPLAYER_KEY_PARAM), };

	TSTRING GetNextItemId()
	{
		TSTRINGVECTOR tsvKey = {};
		RegHelper::RegEnumKeys(tsvKey, m_lpszSubKeyList, m_hCurrentKey);
		for (size_t i = 0; i < tsvKey.size(); i++)
		{
			if (tsvKey.at(i).compare(TO_TSTRING(i)) != 0)
			{
				return TO_TSTRING(i);
			}
		}
		return TO_TSTRING(tsvKey.size());
	}
	BOOL FindSame(const TSTRING& strLabel, const TSTRING& strClass, const TSTRING& strImage, const TSTRING& strParam)
	{
		TSTRINGVECTOR tsvKey = {};
		RegHelper::RegEnumKeys(tsvKey, m_lpszSubKeyList, m_hCurrentKey);
		for (auto & it : tsvKey)
		{
			TCHAR tzLabel[MAX_PATH] = { 0 };
			TCHAR tzClass[MAX_PATH] = { 0 };
			TCHAR tzImage[MAX_PATH] = { 0 };
			TCHAR tzParam[MAX_PATH] = { 0 };
			DWORD dwLabelSize = sizeof(tzLabel) / sizeof(*tzLabel);
			DWORD dwClassSize = sizeof(tzClass) / sizeof(*tzClass);
			DWORD dwImageSize = sizeof(tzImage) / sizeof(*tzImage);
			DWORD dwParamSize = sizeof(tzParam) / sizeof(*tzParam);
			RegHelper::RegGetString(tzLabel, &dwLabelSize, TEXT(VMWAREPLAYER_KEY_LABEL), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzClass, &dwClassSize, TEXT(VMWAREPLAYER_KEY_CLASS), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzImage, &dwImageSize, TEXT(VMWAREPLAYER_KEY_IMAGE), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzParam, &dwParamSize, TEXT(VMWAREPLAYER_KEY_PARAM), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			if ((strLabel.compare(tzLabel) == 0) && (strClass.compare(tzClass) == 0) && (strImage.compare(tzImage) == 0) && (strParam.compare(tzParam) == 0))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	TSTRING FindConfig(const TSTRING& strLabel, const TSTRING& strClass, const TSTRING& strImage, const TSTRING& strParam)
	{
		TSTRINGVECTOR tsvKey = {};
		RegHelper::RegEnumKeys(tsvKey, m_lpszSubKeyList, m_hCurrentKey);
		for (auto& it : tsvKey)
		{
			TCHAR tzLabel[MAX_PATH] = { 0 };
			TCHAR tzClass[MAX_PATH] = { 0 };
			TCHAR tzImage[MAX_PATH] = { 0 };
			TCHAR tzParam[MAX_PATH] = { 0 };
			DWORD dwLabelSize = sizeof(tzLabel) / sizeof(*tzLabel);
			DWORD dwClassSize = sizeof(tzClass) / sizeof(*tzClass);
			DWORD dwImageSize = sizeof(tzImage) / sizeof(*tzImage);
			DWORD dwParamSize = sizeof(tzParam) / sizeof(*tzParam);
			RegHelper::RegGetString(tzLabel, &dwLabelSize, TEXT(VMWAREPLAYER_KEY_LABEL), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzClass, &dwClassSize, TEXT(VMWAREPLAYER_KEY_CLASS), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzImage, &dwImageSize, TEXT(VMWAREPLAYER_KEY_IMAGE), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzParam, &dwParamSize, TEXT(VMWAREPLAYER_KEY_PARAM), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			if ((strLabel.compare(tzLabel) == 0) && (strClass.compare(tzClass) == 0) && (strImage.compare(tzImage) == 0) && (strParam.compare(tzParam) == 0))
			{
				return it;
			}
		}
		return TEXT("");
	}
	BOOL AddConfig(const TSTRING& strLabel, const TSTRING& strClass, const TSTRING& strImage, const TSTRING& strParam)
	{
		if (FindSame(strLabel, strClass, strImage, strParam) == FALSE)
		{
			TSTRING tNextItemId = m_lpszSubKeyList + TSTRING(TEXT("\\")) + GetNextItemId();
			if (m_pListCtrl && m_pListCtrl->GetSafeHwnd())
			{
				int nItem = m_pListCtrl->GetItemCount();
				m_pListCtrl->InsertItem(nItem, strLabel.c_str());
				m_pListCtrl->SetItemText(nItem, 1, strClass.c_str());
				m_pListCtrl->SetItemText(nItem, 2, strImage.c_str());
				m_pListCtrl->SetItemText(nItem, 3, strParam.c_str());
			}
			return (RegHelper::RegSetString(strLabel.c_str(), m_vKeys.at(0).c_str(), tNextItemId.c_str(), m_hCurrentKey)
				&& RegHelper::RegSetString(strClass.c_str(), m_vKeys.at(1).c_str(), tNextItemId.c_str(), m_hCurrentKey)
				&& RegHelper::RegSetString(strImage.c_str(), m_vKeys.at(2).c_str(), tNextItemId.c_str(), m_hCurrentKey)
				&& RegHelper::RegSetString(strParam.c_str(), m_vKeys.at(3).c_str(), tNextItemId.c_str(), m_hCurrentKey));
		}
		return FALSE;
	}
	BOOL DelConfig(int nItem, const TSTRING& strLabel, const TSTRING& strClass, const TSTRING& strImage, const TSTRING& strParam)
	{
		if (m_pListCtrl && m_pListCtrl->GetSafeHwnd())
		{
			TSTRING strKey = FindConfig(strLabel, strClass, strImage, strParam);
			if (strKey.empty() == false)
			{
				return (m_pListCtrl->DeleteItem(nItem) && RegHelper::RegRemoveKey((m_lpszSubKeyList + TSTRING(TEXT("\\")) + strKey).c_str(), m_hCurrentKey));
			}
		}
		return FALSE;
	}
	void InitConfig(CListCtrl * pListCtrl)
	{
		TSTRINGVECTOR tsvKey = {};
		m_pListCtrl = pListCtrl;
		RegHelper::RegEnumKeys(tsvKey, m_lpszSubKeyList, m_hCurrentKey);
		for (auto& it : tsvKey)
		{
			TCHAR tzLabel[MAX_CLASS_NAME] = { 0 };
			TCHAR tzClass[MAX_CLASS_NAME] = { 0 };
			TCHAR tzImage[MAX_PATH] = { 0 };
			TCHAR tzParam[MAX_PATH] = { 0 };
			DWORD dwLabelSize = sizeof(tzLabel) / sizeof(*tzLabel);
			DWORD dwClassSize = sizeof(tzClass) / sizeof(*tzClass);
			DWORD dwImageSize = sizeof(tzImage) / sizeof(*tzImage);
			DWORD dwParamSize = sizeof(tzParam) / sizeof(*tzParam);
			RegHelper::RegGetString(tzLabel, &dwLabelSize, TEXT(VMWAREPLAYER_KEY_LABEL), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzClass, &dwClassSize, TEXT(VMWAREPLAYER_KEY_CLASS), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzImage, &dwImageSize, TEXT(VMWAREPLAYER_KEY_IMAGE), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);
			RegHelper::RegGetString(tzParam, &dwParamSize, TEXT(VMWAREPLAYER_KEY_PARAM), (m_lpszSubKeyList + TSTRING(TEXT("\\")) + it).c_str(), m_hCurrentKey);

			int nItem = m_pListCtrl->GetItemCount();
			m_pListCtrl->InsertItem(nItem, tzLabel);
			m_pListCtrl->SetItemText(nItem, 1, tzClass);
			m_pListCtrl->SetItemText(nItem, 2, tzImage);
			m_pListCtrl->SetItemText(nItem, 3, tzParam);
		}
	}
};

extern CVMWarePlayerAppApp theApp;
