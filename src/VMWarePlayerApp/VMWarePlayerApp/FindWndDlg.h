#pragma once


// CFindWndDlg dialog

class CFindWndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindWndDlg)

public:
	CFindWndDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFindWndDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FINDWND };
#endif

protected:
	HICON m_hIcon = NULL;
	HCURSOR m_hCursorNull = NULL;
	HCURSOR m_hCursorFind = NULL;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() {
		CDialogEx::OnInitDialog();

		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		SetWindowText(TEXT("������Ϣ�鿴����"));
		SetDlgItemText(IDC_STATIC_LABEL, TEXT("���ڱ���"));
		SetDlgItemText(IDC_STATIC_CLASS, TEXT("��������"));
		SetDlgItemText(IDC_STATIC_IMAGE, TEXT("����·��"));
		SetDlgItemText(IDC_STATIC_PARAM, TEXT("ִ�в���"));
		SetDlgItemText(IDOK, TEXT("ȷ��"));
		SetDlgItemText(IDCANCEL, TEXT("�ر�"));

		m_hCursorNull = ((CStatic*)GetDlgItem(IDC_STATIC_FINDWND))->SetIcon(m_hCursorFind);

		return TRUE;  // return TRUE  unless you set the focus to a control
	}
	virtual void OnCancel() {
		Hide();
	}
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
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
	static CFindWndDlg& Inst() {
		static CFindWndDlg CFindWndDlgInstance = {};
		if (CFindWndDlgInstance.GetSafeHwnd() == NULL)
		{
			CFindWndDlgInstance.Create(IDD_DIALOG_FINDWND);
		}
		return CFindWndDlgInstance;
	}
};
