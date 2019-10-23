#include "StdAfx.h"
#include "morphbmp.h"

#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#else
#define WriteDebug() // undefine WriteDebug
#endif

extern void WriteDebug(char * filename, long line_number, char * additional_text);

#ifdef RECORD_PERFORMANCE
extern ofstream fout;
#endif

template <class T> 
void swap( T & left, T & right )
{
	T temp = left;
	left = right;
	right = temp;
}

#define FINAL_STEP 1000000
#define RED_MASK_32   0x000000FF
#define GREEN_MASK_32 0x0000FF00
#define BLUE_MASK_32  0x00FF0000

#define R32(x) (WORD)((x & RED_MASK_32))
#define G32(x) (WORD)((x & GREEN_MASK_32) >> 8)
#define B32(x) (WORD)((x & BLUE_MASK_32)>> 16) 

//#define RED_MASK_16   0x7C00
//#define GREEN_MASK_16 0x03E0
//#define BLUE_MASK_16  0x001F

#define RED_MASK_16   0x0000f800
#define GREEN_MASK_16 0x000007e0
#define BLUE_MASK_16  0x0000001f

#define R16(x) (WORD)((x & RED_MASK_16) >> 11)
#define G16(x) (WORD)((x & GREEN_MASK_16) >> 5)
#define B16(x) (WORD)((x & BLUE_MASK_16)) 

#define RGB16(r,g,b)  ((unsigned short)( ((BYTE)b) | (((BYTE)g) <<5) | (((WORD)(BYTE)r) <<11) ))

//#define iRGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

CMorphBMP::CMorphBMP(CDC * dc1, CDC * dc2, CPoint p1, CPoint p2, CSize s, BlendActionType Action, double time, double percent_to_complete)
: 
	m_Action(Action),
	m_bits(NULL),
	m_pixels(NULL),
	m_pixelDiffs(NULL),
	m_pixel_list(NULL),
	m_index(0),
	m_DCSelected(false),
	m_FadeStep(1),
	m_bpp(0),
	m_draw_time(time),
	m_target_amount(FINAL_STEP * percent_to_complete / 100)
{
	WriteDebug(__FILE__,__LINE__,NULL);
	CBitmap bmp1;
	CBitmap bmp2;
	bmp1.CreateCompatibleBitmap( dc1, s.cx, s.cy);
	bmp2.CreateCompatibleBitmap( dc2, s.cx, s.cy);
	CDC memDC1;
	CDC memDC2;
	WriteDebug(__FILE__,__LINE__,NULL);
	memDC1.CreateCompatibleDC( dc1 );
	memDC2.CreateCompatibleDC( dc2 );
	memDC1.SelectObject( &bmp1 );
	memDC2.SelectObject( &bmp2 );
    WriteDebug(__FILE__,__LINE__,NULL);
	memDC1.BitBlt(0,0, s.cx, s.cy, dc1, p1.x, p1.y, SRCCOPY);
	memDC2.BitBlt(0,0, s.cx, s.cy, dc2, p2.x, p2.y, SRCCOPY);
	WriteDebug(__FILE__,__LINE__,NULL);
	Initialize(&bmp1, &bmp2);
	WriteDebug(__FILE__,__LINE__,NULL);
}

CMorphBMP::CMorphBMP(CBitmap * ptrFirst, CBitmap * ptrSecond, BlendActionType Action, double time, double percent_to_complete) : 
	m_Action(Action),
	m_bits(NULL),
	m_pixels(NULL),
	m_pixelDiffs(NULL),
	m_pixel_list(NULL),
	m_index(0),
	m_DCSelected(false),
	m_FadeStep(1),
	m_bpp(0),
	m_draw_time(time),
	m_target_amount(FINAL_STEP * percent_to_complete / 100)
{
	Initialize(ptrFirst,ptrSecond);
}

CMorphBMP::~CMorphBMP(void)
{
	delete [] m_bits;
	delete [] m_pixels;
	delete [] m_pixelDiffs;
	delete [] m_pixel_list;
}

bool CMorphBMP::Initialize(CBitmap * ptrFirst, CBitmap * ptrSecond)
{
	WriteDebug(__FILE__,__LINE__,NULL);
	ptrFirst->GetBitmap( &bmp1 );
	ptrSecond->GetBitmap( &bmp2 );
	WriteDebug(__FILE__,__LINE__,NULL);
	if ( bmp1.bmHeight != bmp2.bmHeight || bmp1.bmWidth != bmp2.bmWidth ||
		 bmp1.bmType != bmp2.bmType )
		return false;
	
	m_bpp = bmp1.bmBitsPixel;
	DWORD size = bmp1.bmWidthBytes * bmp1.bmHeight;	
	WriteDebug(__FILE__,__LINE__,NULL);
	m_bits = new unsigned char[size];
	unsigned char * m_bits2 = new unsigned char[size];
	m_pixels = new RGBcolor[bmp1.bmWidth * bmp1.bmHeight];     
	m_pixelDiffs = new RGBcolor[bmp1.bmWidth * bmp1.bmHeight]; 
	
	WriteDebug(__FILE__,__LINE__,NULL);
	if (m_Action == CMorphBMP::PIXELATE)
	{
		int plistsize = (bmp1.bmWidth / 2) * (bmp1.bmHeight / 2);
		m_pixel_list = new int[plistsize];
		for (int i = 0; i < plistsize; i++)
			m_pixel_list[i] = i;
		for (int i = 0; i < plistsize * 6; i++)
		{
			swap(m_pixel_list[ ((rand() << 16) + rand()) % plistsize ], m_pixel_list[ ((rand() << 16) + rand()) % plistsize ]);
		}
	}
	WriteDebug(__FILE__,__LINE__,NULL);
	
	ptrFirst->GetBitmapBits( size, m_bits );
	m_BMP.CreateBitmap( bmp1.bmWidth, bmp1.bmHeight, 1, bmp1.bmBitsPixel, m_bits);
	m_BMP.SetBitmapDimension( bmp1.bmWidth, bmp1.bmHeight);
	WriteDebug(__FILE__,__LINE__,NULL);
	/*  bmWidthBytes
	Specifies the number of bytes in each raster line. This value must be an 
	even number since the graphics device interface (GDI) assumes that the 
	bit values of a bitmap form an array of integer (2-byte) values. In other 
	words, bmWidthBytes * 8 must be the next multiple of 16 greater than or 
	equal to the value obtained when the bmWidth member is multiplied by the 
	bmBitsPixel member. */

	ptrSecond->GetBitmapBits( size, m_bits2 );
	
	if (m_bpp == 32)
	{
		DWORD * ptrPixel1;// = &m_bits;
		DWORD * ptrPixel2;// = &m_bitDiffs;
		
		char msg[1000];
		wsprintf(msg,"bmp1.bmHeight=%i,bmp1.bmWidth=%i,bmp1.bmWidthBytes=%i",bmp1.bmHeight,bmp1.bmWidth,bmp1.bmWidthBytes);
		WriteDebug(__FILE__,__LINE__,msg);

		for ( int r = 0; r < bmp1.bmHeight; r++)
		{
			int index = r * bmp1.bmWidth;

			ptrPixel1 = (DWORD *) &m_bits[r * bmp1.bmWidthBytes];
			ptrPixel2 = (DWORD *) &m_bits2[r * bmp1.bmWidthBytes];
			
			for (int c = 0; c < bmp1.bmWidth; c++)
			{
				m_pixels[index].red = R32(*ptrPixel1);
				m_pixels[index].green = G32(*ptrPixel1);
				m_pixels[index].blue = B32(*ptrPixel1);
				m_pixelDiffs[index].red    = R32(*ptrPixel2) - R32(*ptrPixel1);
				m_pixelDiffs[index].green  = G32(*ptrPixel2) - G32(*ptrPixel1);
				m_pixelDiffs[index].blue   = B32(*ptrPixel2) - B32(*ptrPixel1);
				
				index++;
				ptrPixel1++;
				ptrPixel2++;
			}
		}
	}
	else if (m_bpp == 16)
	{
		unsigned short * ptrPixel1;// = &m_bits;
		unsigned short * ptrPixel2;// = &m_bitDiffs;
		
		//unsigned short val;

		char msg[1000];
		wsprintf(msg,"bmp1.bmHeight=%i,bmp1.bmWidth=%i,bmp1.bmWidthBytes=%i",bmp1.bmHeight,bmp1.bmWidth,bmp1.bmWidthBytes);
		WriteDebug(__FILE__,__LINE__,msg);

		for ( int r = 0; r < bmp1.bmHeight; r++)
		{
			int index = r * bmp1.bmWidth;

			ptrPixel1 = (unsigned short *) &m_bits[r * bmp1.bmWidthBytes];
			ptrPixel2 = (unsigned short *) &m_bits2[r * bmp1.bmWidthBytes];
			
			for (int c = 0; c < bmp1.bmWidth; c++)
			{
				m_pixels[index].red = R16(*ptrPixel1);
				m_pixels[index].green = G16(*ptrPixel1);
				m_pixels[index].blue = B16(*ptrPixel1);
				m_pixelDiffs[index].red    = R16(*ptrPixel2) - R16(*ptrPixel1);
				m_pixelDiffs[index].green  = G16(*ptrPixel2) - G16(*ptrPixel1);
				m_pixelDiffs[index].blue   = B16(*ptrPixel2) - B16(*ptrPixel1);
				
				//val = RGB16(m_pixels[index].red, m_pixels[index].green, m_pixels[index].blue);
				index++;
				ptrPixel1++;
				ptrPixel2++;
			}
		}

	}
	WriteDebug(__FILE__,__LINE__,NULL);
	delete [] m_bits2;
	
	return true;
}


int CMorphBMP::Blt(CDC * pDestDC, CPoint p)
{
	if (!m_DCSelected)
	{
		m_MemDC.CreateCompatibleDC( pDestDC );
		m_MemDC.SelectObject( m_BMP );	
		m_DCSelected = true;
	}
	//CBitmap * ptrOld = (CBitmap *) m_MemDC.SelectObject( m_BMP );	

	pDestDC->BitBlt( p.x, 
			            p.y, 
						m_BMP.GetBitmapDimension().cx, 
						m_BMP.GetBitmapDimension().cy, 
			            &m_MemDC, 
						0, 
						0, 
						SRCCOPY);
	//m_MemDC.SelectObject( ptrOld );
	return 0;
}

int CMorphBMP::RenderBits()
{
	int size = bmp1.bmHeight * bmp1.bmWidth;
	if (m_bpp == 32)
	{
		DWORD * ptrPixel;
		ptrPixel = (DWORD *) &m_bits[0];
		for ( int p = 0; p < size; p++)	
			*ptrPixel++ =      RGB(	m_pixels[p].red + m_index * m_pixelDiffs[p].red / FINAL_STEP,
									m_pixels[p].green + m_index * m_pixelDiffs[p].green / FINAL_STEP,
									m_pixels[p].blue + m_index * m_pixelDiffs[p].blue / FINAL_STEP );
	}
	else if (m_bpp == 16)
	{
		unsigned short * ptrPixel;
		ptrPixel = (unsigned short *) &m_bits[0];
		for ( int p = 0; p < size; p++)	
			*ptrPixel++ =      RGB16(m_pixels[p].red + m_index * m_pixelDiffs[p].red / FINAL_STEP,
									m_pixels[p].green + m_index * m_pixelDiffs[p].green / FINAL_STEP,
									m_pixels[p].blue + m_index * m_pixelDiffs[p].blue / FINAL_STEP );
	}
	m_BMP.SetBitmapBits(bmp1.bmWidthBytes * bmp1.bmHeight, m_bits);
	return 0;
}

bool CMorphBMP::Draw(CDC * pDestDC, CPoint p, DrawActionType action)
{
#ifdef RECORD_PERFORMANCE
	if (action == DrawFirst || action == FirstToLast ) // complete means draw from start to finish
		m_index = 0;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;
	LARGE_INTEGER render;
	LARGE_INTEGER blt;
	render.QuadPart = 0;
	blt.QuadPart = 0;
	QueryPerformanceFrequency(&freq); // cycles / second
	double seconds;

	if (m_Action == CMorphBMP::FADE)
	{
		if (action == DrawLast)
			m_index = m_target_amount;

		QueryPerformanceCounter(&start);

		while ( m_index < m_target_amount )
		{
			RenderBits();

			QueryPerformanceCounter(&end);
			render.QuadPart += end.QuadPart - start.QuadPart;

			Blt(pDestDC, p);
			QueryPerformanceCounter(&start);
			blt.QuadPart += start.QuadPart - end.QuadPart;

			m_index += m_FadeStep;
			if (m_index >= m_target_amount)
			{
				m_index = m_target_amount;
				break;
			}
			else if ( action == DrawFirst || action == DrawLast || action == DrawNext )
				break;
		}

		if (m_index == m_target_amount)
		{
			RenderBits();
			Blt(pDestDC, p);
			m_index = 0; // reset back to zero
			return true;
		}
		seconds = double(blt.QuadPart) / double(freq.QuadPart);
		fout << "blt: " << seconds << " seconds " << endl;
		seconds = double(render.QuadPart) / double(freq.QuadPart);
		fout << "render: " << seconds << " seconds " << endl;
#else

	if (action == DrawFirst || action == FirstToLast ) // complete means draw from start to finish
		m_index = 0;

	if (m_Action == CMorphBMP::FADE)
	{
		double target_steps_per_second = 0;
		double time_spent_seconds = 0;
		double last_cycle_seconds = 0;

		if (action == DrawLast)
			m_index = m_target_amount;

		LARGE_INTEGER start;
		LARGE_INTEGER end;
		LARGE_INTEGER freq;
		
		QueryPerformanceFrequency(&freq); // cycles / second
		QueryPerformanceCounter(&start);

		while ( m_index < m_target_amount )
		{	
			RenderBits();
			Blt(pDestDC, p);
			QueryPerformanceCounter(&end);
		
			last_cycle_seconds = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);
			time_spent_seconds += last_cycle_seconds;

			if (time_spent_seconds > m_draw_time)
			{
				m_index = m_target_amount;
			}
			else
			{
				target_steps_per_second = (m_target_amount - m_index) / (m_draw_time - time_spent_seconds);
				m_index += target_steps_per_second * last_cycle_seconds;
			}

			if (m_index >= m_target_amount)
			{
				m_index = m_target_amount;
				break;
			}
			else if ( action == DrawFirst || action == DrawLast || action == DrawNext )
				break;

			start = end;
		}

		if (m_index == m_target_amount)
		{
			RenderBits();
			Blt(pDestDC, p);
			m_index = 0; // reset back to zero
			return true;
		}
#endif
	}
	else if (m_Action == CMorphBMP::PIXELATE )  // pixelate does not currently work for 16bpp
	{
		if (m_index == 0)
			Blt(pDestDC, p);

		int plistsize = (bmp1.bmWidth / 2) * (bmp1.bmHeight / 2);
		int row;
		int col;
		while ( m_index < plistsize )
		{
			row = (m_pixel_list[m_index] / (bmp1.bmWidth / 2)) * 2;
			col = (m_pixel_list[m_index] % (bmp1.bmWidth / 2)) * 2;
			
			pDestDC->SetPixelV( p + CPoint(col, row), GetFinalPixelColor( col, row ) );
			pDestDC->SetPixelV( p + CPoint(col + 1, row), GetFinalPixelColor( col + 1, row ) );
			pDestDC->SetPixelV( p + CPoint(col, row + 1), GetFinalPixelColor( col, row + 1 ) );
			pDestDC->SetPixelV( p + CPoint(col + 1, row + 1), GetFinalPixelColor( col + 1, row + 1) );

			m_index++;

			if (action == DrawFirst || action == DrawNext)
				break;
			else if (action == FirstToLast)
				for (int t = 0; t < 10000; t++);
		}
		
		if (m_index == plistsize)
		{
			m_index = 0;
			return true;
		}
	}
	return false;
}

COLORREF CMorphBMP::GetFinalPixelColor(int x, int y)
{
	//TODO: return statement
	int index = bmp1.bmWidth * y + x;
	return RGB( m_pixels[index].blue + m_pixelDiffs[index].blue,
				m_pixels[index].green + m_pixelDiffs[index].green,
				m_pixels[index].red + m_pixelDiffs[index].red );
}

const CSize & CMorphBMP::GetDimensions(void)
{
	return m_BMP.GetBitmapDimension();
}
