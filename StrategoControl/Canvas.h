// Canvas.h: interface for the CCanvas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CANVAS_H__7B0821B6_ACC0_4DDD_96DD_7178468FA1BE__INCLUDED_)
#define AFX_CANVAS_H__7B0821B6_ACC0_4DDD_96DD_7178468FA1BE__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCanvas  
{
public:
	CPoint m_board_top_left_corner;
	CBitmap m_drawBMP;
	CBitmap m_frontBMP;
	CDC m_backOutlineDC;
	CPicture m_image_outline;
	CPicture m_image_highlight;
	CDC m_backHighlightDC;
	CPicture m_image;
	void CreateDCS( CDC * pSrcDC );
	CDC m_drawDC;
	CDC m_frontDC;
	CDC m_backDC;
	CSize m_image_size;
	CCanvas();
	virtual ~CCanvas();

	void WipeImageDCs(void);
};

#endif // !defined(AFX_CANVAS_H__7B0821B6_ACC0_4DDD_96DD_7178468FA1BE__INCLUDED_)
