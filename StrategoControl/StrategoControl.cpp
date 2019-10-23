// StrategoControl.cpp : Implementation of CStrategoControlApp and DLL registration.

#include "stdafx.h"
#include "StrategoControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStrategoControlApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xEC11A29C, 0xD3E0, 0x4BC9, { 0xA7, 0x2F, 0xBB, 0x6C, 0x22, 0x94, 0x68, 0xFF } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CStrategoControlApp::InitInstance - DLL initialization

BOOL CStrategoControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CStrategoControlApp::ExitInstance - DLL termination

int CStrategoControlApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
