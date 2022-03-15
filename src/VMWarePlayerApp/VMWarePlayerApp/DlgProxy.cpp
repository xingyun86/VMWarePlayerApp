
// DlgProxy.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VMWarePlayerApp.h"
#include "DlgProxy.h"
#include "VMWarePlayerAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVMWarePlayerAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CVMWarePlayerAppDlgAutoProxy, CCmdTarget)

CVMWarePlayerAppDlgAutoProxy::CVMWarePlayerAppDlgAutoProxy()
{
	EnableAutomation();

	// To keep the application running as long as an automation
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CVMWarePlayerAppDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CVMWarePlayerAppDlg)))
		{
			m_pDialog = reinterpret_cast<CVMWarePlayerAppDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CVMWarePlayerAppDlgAutoProxy::~CVMWarePlayerAppDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CVMWarePlayerAppDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CVMWarePlayerAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVMWarePlayerAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IVMWarePlayerApp to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {a3cf2a27-f0a2-4b97-b7a1-82c4c3f28aff}
static const IID IID_IVMWarePlayerApp =
{0xa3cf2a27,0xf0a2,0x4b97,{0xb7,0xa1,0x82,0xc4,0xc3,0xf2,0x8a,0xff}};

BEGIN_INTERFACE_MAP(CVMWarePlayerAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CVMWarePlayerAppDlgAutoProxy, IID_IVMWarePlayerApp, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in pch.h of this project
// {21963cac-29f9-4f6b-b907-11002ba7a2d7}
IMPLEMENT_OLECREATE2(CVMWarePlayerAppDlgAutoProxy, "VMWarePlayerApp.Application", 0x21963cac,0x29f9,0x4f6b,0xb9,0x07,0x11,0x00,0x2b,0xa7,0xa2,0xd7)


// CVMWarePlayerAppDlgAutoProxy message handlers
