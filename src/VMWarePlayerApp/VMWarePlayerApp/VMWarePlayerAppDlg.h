
// VMWarePlayerAppDlg.h : header file
//

#pragma once

class CVMWarePlayerAppDlgAutoProxy;


// CVMWarePlayerAppDlg dialog
class CVMWarePlayerAppDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVMWarePlayerAppDlg);
	friend class CVMWarePlayerAppDlgAutoProxy;

// Construction
public:
	CVMWarePlayerAppDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CVMWarePlayerAppDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VMWAREPLAYERAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CVMWarePlayerAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;
	HWND m_hWndVmp;
	CListCtrl m_myListCtrl;
	NOTIFYICONDATA m_nidNotifyIcon = { 0 };

	const std::vector<TSTRING> m_vBtnText = { TEXT("后台运行"), TEXT("前台运行"), };

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg LRESULT OnSystemtray(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRestartExplorer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonRun();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRightClickListData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
