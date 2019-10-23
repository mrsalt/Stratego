// BitmapRendererDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapRenderer.h"
#include "BitmapRendererDlg.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef RECORD_PERFORMANCE
ofstream fout("C:\\timing_data.txt");
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBitmapRendererDlg dialog



CBitmapRendererDlg::CBitmapRendererDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapRendererDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bmp1.LoadBitmap(IDB_BITMAP1);
	m_bmp2.LoadBitmap(IDB_BITMAP2);
	m_morph = NULL;
	if (!m_morph)
	{
		//m_morph = new CMorphBMP(&m_bmp1, &m_bmp2, CMorphBMP::BlendActionType::PIXELATE, 3 );
		m_morph = new CMorphBMP(&m_bmp1, &m_bmp2, CMorphBMP::FADE, 3 );
	}
}

CBitmapRendererDlg::~CBitmapRendererDlg()
{
	if (m_morph)
		delete m_morph;
}

void CBitmapRendererDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBitmapRendererDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
//	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_START_BUTTON, OnBnClickedStartButton)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CBitmapRendererDlg message handlers

BOOL CBitmapRendererDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//VERIFY( m_brush = (HBRUSH)GetStockObject( HOLLOW_BRUSH ) );

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	int cx = m_morph->GetDimensions().cx;
	int cy = m_morph->GetDimensions().cy;
	MoveWindow(0,0, cx,  cy);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBitmapRendererDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBitmapRendererDlg::OnPaint() 
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
		
		//CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBitmapRendererDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CBitmapRendererDlg::OnEraseBkgnd(CDC* pDC)
{
//WM_ERASEBKGND
//WM_PAINT	
	// TODO: Add your message handler code here and/or call default

//	return CDialog::OnEraseBkgnd(pDC);

	//CWnd * textPtr = GetDlgItem(IDC_TEXT1);
	//static int percent = 0;
	//if (textPtr && percent < 100)
	//{
	//	char p[10];
	//	wsprintf(p,"%i%%", percent++);
	//	textPtr->SetWindowText(p);
	//}
	m_morph->m_FadeStep = 1;
#ifdef RECORD_PERFORMANCE
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;
	QueryPerformanceCounter(&start);
#endif
	m_morph->Draw(pDC, CPoint(0,0), CMorphBMP::FirstToLast);
#ifdef RECORD_PERFORMANCE
	QueryPerformanceCounter(&end);
	QueryPerformanceFrequency(&freq); // cycles / second
	double seconds = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);
	fout << seconds << " seconds " << endl;
#endif
	return TRUE;

}

void CBitmapRendererDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
		Invalidate();
	//CDialog::OnTimer(nIDEvent);
}

/*
HBRUSH CBitmapRendererDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	//pDC->SetBkMode( TRANSPARENT );
    //return m_brush;
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  Return a different brush if the default is not desired
}
*/

void CBitmapRendererDlg::OnBnClickedStartButton()
{
	// TODO: Add your control notification handler code here
	CWnd::SetTimer(1, 1000, NULL);
}

void CBitmapRendererDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	/*
	if (nIDCtl == IDC_IMAGE)
	{
		CDC DC;
		DC.Attach(lpDrawItemStruct->hDC);
		m_morph->RenderNext();
		m_morph->Blt(&DC);
	}
	else
	*/
		CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
