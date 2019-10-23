#pragma once
#include "afxwin.h"
#include <icm.h>

/*
3.0146 seconds 
3.00971 seconds 
2.9736 seconds 
3.09496 seconds 
3.00765 seconds 
*/

//#define RECORD_PERFORMANCE

struct RGBcolor {
    int    red;
    int    green;
    int    blue;
};

class CMorphBMP
{
public:
	enum BlendActionType { FADE, PIXELATE };
	enum DrawActionType { DrawFirst, DrawLast, FirstToLast, DrawNext, Complete };

	CMorphBMP(CDC * dc1, CDC * dc2, CPoint p1, CPoint p2, CSize s, BlendActionType Action, double seconds, double percent_to_complete = 100.0);
	CMorphBMP(CBitmap * ptrFirst, CBitmap * ptrSecond, BlendActionType Action, double seconds, double percent_to_complete = 100.0);
	~CMorphBMP(void);

private:
	bool Initialize(CBitmap * ptrFirst, CBitmap * ptrSecond );
	CDC m_MemDC;
	bool m_DCSelected;

	unsigned char * m_bits;
	RGBcolor * m_pixelDiffs;
	RGBcolor * m_pixels;
	int * m_pixel_list;

	BITMAP bmp1;
	BITMAP bmp2;
	int m_index;
	int m_target_amount;
	int Blt(CDC * pDestDC, CPoint p);
	int RenderBits();
	COLORREF GetFinalPixelColor(int x, int y);
	CBitmap m_BMP;
	BlendActionType m_Action;
	int m_bpp;
	double m_draw_time;
public:
	int m_FadeStep;
	bool Draw(CDC * pDestDC, CPoint p, DrawActionType action);
	
	const CSize & GetDimensions(void);
};
