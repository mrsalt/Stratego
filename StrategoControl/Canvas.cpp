// Canvas.cpp: implementation of the CCanvas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrategoControl.h"
#include "Canvas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCanvas::CCanvas()
{

}

CCanvas::~CCanvas()
{

}

void CCanvas::CreateDCS(CDC *pSrcDC)
{
	ASSERT(m_image.m_imageLoaded);

	m_backDC.CreateCompatibleDC( pSrcDC );

	m_image_size = m_image.GetImageSize();
	m_image.SelectPicture( &m_backDC );

	if (m_image_highlight.m_imageLoaded)
	{
		m_backHighlightDC.CreateCompatibleDC( pSrcDC );
		m_image_highlight.SelectPicture( &m_backHighlightDC );
	}

	if (m_image_outline.m_imageLoaded)
	{
		m_backOutlineDC.CreateCompatibleDC( pSrcDC );
		m_image_outline.SelectPicture( &m_backOutlineDC );
	}

	m_frontDC.CreateCompatibleDC( pSrcDC );
	m_frontBMP.CreateCompatibleBitmap( pSrcDC, m_image_size.cx, m_image_size.cy );
	m_frontDC.SelectObject( m_frontBMP );

	m_drawDC.CreateCompatibleDC( pSrcDC );
	m_drawBMP.CreateCompatibleBitmap( pSrcDC, m_image_size.cx, m_image_size.cy );
	m_drawDC.SelectObject( m_drawBMP );
	WipeImageDCs();
}

void CCanvas::WipeImageDCs(void)
{
	BOOL success = FALSE;
	success = m_frontDC.BitBlt(0, 0, m_image_size.cx, m_image_size.cy, &m_backDC, 0, 0, SRCCOPY);
	ASSERT(success);
	success = m_drawDC.BitBlt(0, 0, m_image_size.cx, m_image_size.cy, &m_backDC, 0, 0, SRCCOPY);
	ASSERT(success);	
}
