// StrategoControlPropPage.cpp : Implementation of the CStrategoControlPropPage property page class.

#include "stdafx.h"
#include "StrategoControl.h"
#include "StrategoControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CStrategoControlPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CStrategoControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CStrategoControlPropPage, "STRATEGO.StrategoClassicPropPage.1",
	0x2a091e0a, 0xf83, 0x4193, 0xa0, 0x54, 0x1a, 0xd2, 0x51, 0xf1, 0x2c, 0xb4)



// CStrategoControlPropPage::CStrategoControlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CStrategoControlPropPage

BOOL CStrategoControlPropPage::CStrategoControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_STRATEGOCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CStrategoControlPropPage::CStrategoControlPropPage - Constructor

CStrategoControlPropPage::CStrategoControlPropPage() :
	COlePropertyPage(IDD, IDS_STRATEGOCONTROL_PPG_CAPTION)
{
}



// CStrategoControlPropPage::DoDataExchange - Moves data between page and properties

void CStrategoControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CStrategoControlPropPage message handlers
