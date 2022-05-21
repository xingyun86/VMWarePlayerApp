// FindWndDlg.cpp : implementation file
//

#include "pch.h"
#include "VMWarePlayerApp.h"
#include "FindWndDlg.h"
#include "afxdialogex.h"


// CFindWndDlg dialog

IMPLEMENT_DYNAMIC(CFindWndDlg, CDialogEx)

CFindWndDlg::CFindWndDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FINDWND, pParent)
{
	m_hCursorNull = NULL;
	m_hCursorFind = LoadCursor(NULL, IDC_CROSS);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFindWndDlg::~CFindWndDlg()
{
}

void CFindWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFindWndDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CFindWndDlg message handlers


void CFindWndDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect = { 0 };
	ClientToScreen(&point);
	GetDlgItem(IDC_STATIC_FINDWND)->GetWindowRect(&rect);
	if (PtInRect(&rect, point))
	{
		SetCapture();
		::SetCursor(m_hCursorFind);
		((CStatic*)GetDlgItem(IDC_STATIC_FINDWND))->SetIcon(m_hCursorNull);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CFindWndDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	::SetCursor(m_hCursorNull);
	m_hCursorNull = ((CStatic*)GetDlgItem(IDC_STATIC_FINDWND))->SetIcon(m_hCursorFind);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CFindWndDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetCapture())
	{
		HWND hWnd = NULL;
		ClientToScreen(&point);
		hWnd = ::WindowFromPoint(point);
		if (hWnd != NULL)
		{
			TCHAR tzLabelName[MAX_CLASS_NAME] = { 0 };
			TCHAR tzClassName[MAX_CLASS_NAME] = { 0 };
			TCHAR tzImagePath[MAX_PATH] = { 0 };
			::GetWindowText(hWnd, tzLabelName, sizeof(tzLabelName) / sizeof(*tzLabelName));
			::GetClassName(hWnd, tzClassName, sizeof(tzClassName) / sizeof(*tzClassName));
			GetWindowProcessModuleImageFilePath(hWnd, tzImagePath, sizeof(tzImagePath) / sizeof(*tzImagePath));
			SetDlgItemText(IDC_EDIT_LABEL, tzLabelName);
			SetDlgItemText(IDC_EDIT_CLASS, tzClassName);
			SetDlgItemText(IDC_EDIT_IMAGE, tzImagePath);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
void CFindWndDlg::OnOK()
{
	CString strLabel = TEXT("");
	CString strClass = TEXT("");
	CString strImage = TEXT("");
	CString strParam = TEXT("");
	GetDlgItemText(IDC_EDIT_LABEL, strLabel);
	GetDlgItemText(IDC_EDIT_CLASS, strClass);
	GetDlgItemText(IDC_EDIT_IMAGE, strImage);
	GetDlgItemText(IDC_EDIT_PARAM, strParam);
	theApp.AddConfig((LPCTSTR)strLabel, (LPCTSTR)strClass, (LPCTSTR)strImage, (LPCTSTR)strParam);
	CDialogEx::OnOK();
}