// BitmapRendererDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "morphbmp.h"


// CBitmapRendererDlg dialog
class CBitmapRendererDlg : public CDialog
{
// Construction
public:
	CBitmapRendererDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CBitmapRendererDlg();

// Dialog Data
	enum { IDD = IDD_BITMAPRENDERER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	
	HICON m_hIcon;
	HBRUSH m_brush;        // Handle of background brush

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CBitmap m_bmp1;
	CBitmap m_bmp2;
	CMorphBMP * m_morph;
	afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CStatic m_image;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
