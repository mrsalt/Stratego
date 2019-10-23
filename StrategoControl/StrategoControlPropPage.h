#pragma once

// StrategoControlPropPage.h : Declaration of the CStrategoControlPropPage property page class.


// CStrategoControlPropPage : See StrategoControlPropPage.cpp.cpp for implementation.

class CStrategoControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CStrategoControlPropPage)
	DECLARE_OLECREATE_EX(CStrategoControlPropPage)

// Constructor
public:
	CStrategoControlPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_STRATEGOCONTROL };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

