
// DlgProxy.h: header file
//

#pragma once

class CVMWarePlayerAppDlg;


// CVMWarePlayerAppDlgAutoProxy command target

class CVMWarePlayerAppDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CVMWarePlayerAppDlgAutoProxy)

	CVMWarePlayerAppDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CVMWarePlayerAppDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CVMWarePlayerAppDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CVMWarePlayerAppDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

