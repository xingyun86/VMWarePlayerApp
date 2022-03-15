
// VMWarePlayerAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VMWarePlayerApp.h"
#include "VMWarePlayerAppDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "FindWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	WM_SYSTEMTRAY	(WM_USER + WM_COMMAND + 1)
const UINT WMEX_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg(CWnd* pParent = NULL) : CDialogEx(IDD_ABOUTBOX, pParent)
	{
		EnableActiveAccessibility();
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	HICON m_hIcon = NULL;

	virtual void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		CDialogEx::DoDataExchange(pDX);
	}
	virtual BOOL OnInitDialog() {
		CDialogEx::OnInitDialog();

		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		SetWindowText(TEXT("关于软件窗口管理工具"));
		SetDlgItemText(IDOK, TEXT("确定"));

		return TRUE;  // return TRUE  unless you set the focus to a control
	}
	virtual void OnCancel() {
		ShowWindow(SW_HIDE);
	}

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Show(CWnd* pParent = NULL)
	{
		CenterWindow(pParent);
		ShowWindow(SW_SHOWNORMAL);
	}
	void Hide()
	{
		ShowWindow(SW_HIDE);
	}
	static CAboutDlg& Inst() {
		static CAboutDlg CAboutDlgInstance;
		if (CAboutDlgInstance.GetSafeHwnd() == NULL)
		{
			CAboutDlgInstance.Create(IDD_ABOUTBOX);
		}
		return CAboutDlgInstance;
	}
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVMWarePlayerAppDlg dialog


IMPLEMENT_DYNAMIC(CVMWarePlayerAppDlg, CDialogEx);

CVMWarePlayerAppDlg::CVMWarePlayerAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VMWAREPLAYERAPP_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CVMWarePlayerAppDlg::~CVMWarePlayerAppDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to null, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CVMWarePlayerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_myListCtrl);
}

BEGIN_MESSAGE_MAP(CVMWarePlayerAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SYSTEMTRAY, &CVMWarePlayerAppDlg::OnSystemtray)
	ON_REGISTERED_MESSAGE(WMEX_TASKBARCREATED, OnRestartExplorer)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CVMWarePlayerAppDlg::OnBnClickedButtonRun)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DATA, &CVMWarePlayerAppDlg::OnRightClickListData)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVMWarePlayerAppDlg message handlers

BOOL CVMWarePlayerAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		strAboutMenu = TEXT("关于软件窗口管理工具");
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//ShowWindow(SW_MAXIMIZE);

	//ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here
	{
		SetWindowText(TEXT("软件窗口管理工具"));
		SetDlgItemText(IDC_BUTTON_RUN, TEXT("启动VMPlayer"));
		SetDlgItemText(IDCANCEL, TEXT("关闭软件"));
	}
	{
		m_nidNotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
		m_nidNotifyIcon.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		m_nidNotifyIcon.hIcon = m_hIcon;
		m_nidNotifyIcon.hWnd = m_hWnd;
		lstrcpy(m_nidNotifyIcon.szTip, TEXT("VMWarePlayer"));
		m_nidNotifyIcon.uCallbackMessage = WM_SYSTEMTRAY;
		m_nidNotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		Shell_NotifyIcon(NIM_ADD, &m_nidNotifyIcon);
	}
	{
		m_myListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER | LVS_EX_LABELTIP);
		m_myListCtrl.InsertColumn(m_myListCtrl.GetHeaderCtrl()->GetItemCount(), TEXT("窗口标题"), LVCFMT_LEFT, 100);
		m_myListCtrl.InsertColumn(m_myListCtrl.GetHeaderCtrl()->GetItemCount(), TEXT("窗口类名"), LVCFMT_LEFT, 120);
		m_myListCtrl.InsertColumn(m_myListCtrl.GetHeaderCtrl()->GetItemCount(), TEXT("镜像路径"), LVCFMT_LEFT, 200);
		theApp.InitConfig(&m_myListCtrl);
	}
	{
		m_hWndVmp = ::FindWindowEx(NULL, NULL, TEXT("VMPlayerFrame"), NULL);
		SetDlgItemText(IDOK, m_vBtnText.at(((::GetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW)).c_str());
	}
	{
		PostMessage(WM_SIZE, 0, 0);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVMWarePlayerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg::Inst().Show(this);
	}
	else
	{
		switch (nID)
		{
		case SC_CLOSE:
		case SC_MINIMIZE:
		{
			::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | (WS_EX_TOOLWINDOW)) & (~WS_EX_APPWINDOW));
			::ShowWindow(m_hWnd, SW_HIDE);
			CAboutDlg::Inst().Hide();
		}
		break;
		default:
		{
			CDialogEx::OnSysCommand(nID, lParam);
		}
			break;
		}		
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVMWarePlayerAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVMWarePlayerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CVMWarePlayerAppDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CVMWarePlayerAppDlg::OnOK()
{
	if (m_hWndVmp == NULL)
	{
		m_hWndVmp = ::FindWindowEx(NULL, NULL, TEXT("VMPlayerFrame"), NULL);
		SetDlgItemText(IDOK, m_vBtnText.at(((::GetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW)).c_str());
	}
	if (m_hWndVmp != NULL)
	{
		BOOL bIsWindowVisible = ((::GetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW);
		this->SetDlgItemText(IDOK, m_vBtnText.at(!bIsWindowVisible).c_str());
		if (bIsWindowVisible)
		{
			::SetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE) | (WS_EX_APPWINDOW)) & (~WS_EX_TOOLWINDOW));
			::ShowWindow(m_hWndVmp, SW_SHOWNORMAL);
		}
		else
		{
			::SetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWndVmp, GWL_EXSTYLE) | (WS_EX_TOOLWINDOW)) & (~WS_EX_APPWINDOW));
			::ShowWindow(m_hWndVmp, SW_HIDE);
		}
	}
	//if (CanExit())
	//	CDialogEx::OnOK();
}

void CVMWarePlayerAppDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CVMWarePlayerAppDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	Shell_NotifyIcon(NIM_DELETE, &m_nidNotifyIcon);

	return TRUE;
}

afx_msg LRESULT CVMWarePlayerAppDlg::OnSystemtray(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case  WM_RBUTTONDOWN:
	{
		enum MenuEnumType {
			METYPE_SHOWHIDE = 10001,
			METYPE_FINDER,
			METYPE_ABOUT,
			METYPE_EXIT,
		};
		CMenu menu = {};
		CPoint pt = { 0 };
		GetCursorPos(&pt);
		SetForegroundWindow();
		if (menu.CreatePopupMenu() == TRUE)
		{
			menu.AppendMenu(MF_STRING, METYPE_SHOWHIDE, (IsWindowVisible() == TRUE) ? TEXT("后台运行") : TEXT("前台运行"));
			menu.AppendMenu(MF_STRING, METYPE_FINDER, TEXT("查找窗口"));
			menu.AppendMenu(MF_STRING, METYPE_ABOUT, TEXT("关于软件"));
			menu.AppendMenu(MF_STRING, METYPE_EXIT, TEXT("退出软件"));
			switch ((enum MenuEnumType)menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this))
			{
			case METYPE_SHOWHIDE:
			{
				if (((::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW) == TRUE)
				{
					::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | (WS_EX_APPWINDOW)) & (~WS_EX_TOOLWINDOW));
					::ShowWindow(m_hWnd, SW_SHOWNORMAL);
				}
				else
				{
					::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | (WS_EX_TOOLWINDOW)) & (~WS_EX_APPWINDOW));
					::ShowWindow(m_hWnd, SW_HIDE);
					CAboutDlg::Inst().Hide();
				}
			}
			break;
			case METYPE_FINDER:
			{
				CFindWndDlg::Inst().Show(this);
			}
			break;
			case METYPE_ABOUT:
			{
				CAboutDlg::Inst().Show(this);
			}
			break;
			case METYPE_EXIT:
			{
				PostQuitMessage(IDCLOSE);
			}
			break;
			default:
				break;
			};
			menu.DestroyMenu();
		}
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		if (((::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW) == TRUE)
		{
			::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | (WS_EX_APPWINDOW)) & (~WS_EX_TOOLWINDOW));
			::ShowWindow(m_hWnd, SW_SHOWNORMAL);
		}
		else
		{
			::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE) | (WS_EX_TOOLWINDOW)) & (~WS_EX_APPWINDOW));
			::ShowWindow(m_hWnd, SW_HIDE);
			CAboutDlg::Inst().Hide();
		}
	}
	break;
	case  WM_LBUTTONDOWN:     
	{
	}
	break;
	}
	return 0;
}

LRESULT CVMWarePlayerAppDlg::OnRestartExplorer(WPARAM wParam, LPARAM lParam)
{
	Shell_NotifyIcon(NIM_ADD, &m_nidNotifyIcon);
	return TRUE;
}

void CVMWarePlayerAppDlg::OnBnClickedButtonRun()
{
	// TODO: Add your control notification handler code here{
	m_hWndVmp = ::FindWindowEx(NULL, NULL, TEXT("VMPlayerFrame"), NULL);
	if (m_hWndVmp == NULL)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		si.cb = sizeof(si);
		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&pi, sizeof(pi));
		si.wShowWindow = STARTF_USESHOWWINDOW;
		// Start the child process. 
		if (!CreateProcess(
			TEXT("C:\\Program Files (x86)\\VMware\\VMware Player\\vmplayer.exe"),   // No module name (use command line)
			NULL,			// Command line
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
			return;
		}

		// Wait until child process exits.
		//WaitForSingleObject(pi.hProcess, INFINITE);
		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		m_hWndVmp = ::FindWindowEx(NULL, NULL, TEXT("VMPlayerFrame"), NULL);
	}
}


void CVMWarePlayerAppDlg::OnRightClickListData(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	enum MenuEnumType {
		METYPE_STARTAPP = 10001,
		METYPE_SHOWHIDE,
		METYPE_DELETE,
		METYPE_ADDNEW,
	};
	CMenu menu = {};
	CPoint pt = { 0 };
	GetCursorPos(&pt);
	SetForegroundWindow();
	if (menu.CreatePopupMenu() == TRUE)
	{
		HWND hWndTmp = NULL;
		CString strClass = TEXT("");
		CString strImage = TEXT("");
		if (pNMItemActivate->iItem != (-1))
		{
			strClass = m_myListCtrl.GetItemText(pNMItemActivate->iItem, 1);
			strImage = m_myListCtrl.GetItemText(pNMItemActivate->iItem, 2);
			if (strClass.IsEmpty() == FALSE)
			{
				hWndTmp = ::FindWindowEx(NULL, NULL, strClass, NULL);
			}
			if (strImage.IsEmpty() == FALSE)
			{
				menu.AppendMenu(MF_STRING, METYPE_STARTAPP, TEXT("启动应用"));
			}
			menu.AppendMenu(MF_STRING, METYPE_SHOWHIDE, (((::GetWindowLongPtr(hWndTmp, GWL_EXSTYLE)& (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW) == TRUE) ? TEXT("前台运行") : TEXT("后台运行"));
			menu.AppendMenu(MF_STRING, METYPE_DELETE, TEXT("删除选项"));
		}
		menu.AppendMenu(MF_STRING, METYPE_ADDNEW, TEXT("添加新项"));
		switch ((enum MenuEnumType)menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this))
		{
		case METYPE_STARTAPP:
		{
			if (strImage.IsEmpty() == FALSE)
			{
				StartupProgram(strImage);
			}
		}
		break;
		case METYPE_SHOWHIDE:
		{
			if (hWndTmp != NULL)
			{
				if (((::GetWindowLongPtr(hWndTmp, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW)) == WS_EX_TOOLWINDOW) == TRUE)
				{
					::SetWindowLongPtr(hWndTmp, GWL_EXSTYLE, (::GetWindowLongPtr(hWndTmp, GWL_EXSTYLE) | (WS_EX_APPWINDOW)) & (~WS_EX_TOOLWINDOW));
					::ShowWindow(hWndTmp, SW_SHOWNORMAL);
				}
				else
				{
					::SetWindowLongPtr(hWndTmp, GWL_EXSTYLE, (::GetWindowLongPtr(hWndTmp, GWL_EXSTYLE) | (WS_EX_TOOLWINDOW)) & (~WS_EX_APPWINDOW));
					::ShowWindow(hWndTmp, SW_HIDE);
				}
			}
		}
		break;
		case METYPE_DELETE:
		{
			theApp.DelConfig(pNMItemActivate->iItem, (LPCTSTR)strClass, (LPCTSTR)strImage);
		}
		break;
		case METYPE_ADDNEW:
		{
			CFindWndDlg::Inst().Show(this);
		}
		break;
		default:
			break;
		};
		menu.DestroyMenu();
	}
	*pResult = 0;
}


void CVMWarePlayerAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_myListCtrl.GetSafeHwnd() != NULL)
	{
		CRect rcWindow = { 0 };
		CRect rcListCtrl = { 0 };
		this->GetWindowRect(&rcWindow);
		m_myListCtrl.GetWindowRect(&rcListCtrl);
		m_myListCtrl.MoveWindow(18, 72, rcWindow.Width() - 48, rcWindow.Height() - 72 - 56);
	}
}
