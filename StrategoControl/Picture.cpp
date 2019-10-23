////////////////////////////////////////////////////////////////
// MSDN Magazine -- October 2001
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 too.
// Set tabsize = 3 in your editor.
//
#include "StdAfx.h"
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// CPicture implementation
//

CPicture::CPicture()
{
	m_imageLoaded = false;
}

CPicture::~CPicture()
{
}

//////////////////
// Load from resource. Looks for "IMAGE" type.
//
BOOL CPicture::Load(UINT nIDRes)
{
	// find resource in resource file
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,
		MAKEINTRESOURCE(nIDRes),
		"IMAGE"); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// create memory file and load it
	CMemFile file(lpRsrc, len);
	BOOL bRet = Load(file);
	FreeResource(hRsrc);
	GlobalFree(lpRsrc);
	return bRet;
}

//////////////////
// Load from path name.
//
BOOL CPicture::Load(LPCTSTR pszPathName)
{
	CFile file;
	if (!file.Open(pszPathName, CFile::modeRead|CFile::shareDenyWrite))
		return FALSE;
	BOOL bRet = Load(file);
	file.Close();
	m_imageLoaded = true;
	return bRet;
}

//////////////////
// Load from CFile
//
BOOL CPicture::Load(CFile& file)
{
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	return Load(ar);
}

//////////////////
// Load from archive--create stream and load from stream.
//
BOOL CPicture::Load(CArchive& ar)
{
	CArchiveStream arcstream(&ar);
	return Load((IStream*)&arcstream);
}

//////////////////
// Load from stream (IStream). This is the one that really does it: call
// OleLoadPicture to do the work.
//
BOOL CPicture::Load(IStream* pstm)
{
	Free();
	HRESULT hr = OleLoadPicture(pstm, 0, FALSE,
		IID_IPicture, (void**)&m_spIPicture);
	ASSERT(SUCCEEDED(hr) && m_spIPicture);	
	return TRUE;
}

//////////////////
// Render to device context. Covert to HIMETRIC for IPicture.
//
BOOL CPicture::Render(CDC* pDC, CRect rc, LPCRECT prcMFBounds) const
{
	ASSERT(pDC);

	if (rc.IsRectNull()) {
		CSize sz = GetImageSize(pDC);
		rc.right = sz.cx;
		rc.bottom = sz.cy;
	}
	long hmWidth,hmHeight; // HIMETRIC units
	GetHIMETRICSize(hmWidth, hmHeight);
	m_spIPicture->Render(*pDC, rc.left, rc.top, rc.Width(), rc.Height(),
		0, hmHeight, hmWidth, -hmHeight, prcMFBounds);

	return TRUE;
}

//////////////////
// Get image size in pixels. Converts from HIMETRIC to device coords.
//
CSize CPicture::GetImageSize(CDC* pDC) const
{
	if (!m_spIPicture)
		return CSize(0,0);
	
	LONG hmWidth, hmHeight; // HIMETRIC units
	m_spIPicture->get_Width(&hmWidth);
	m_spIPicture->get_Height(&hmHeight);
	CSize sz(hmWidth,hmHeight);
	if (pDC==NULL) {
		CWindowDC dc(NULL);
		dc.HIMETRICtoDP(&sz); // convert to pixels
	} else {
		pDC->HIMETRICtoDP(&sz);
	}
	return sz;
}


BOOL CPicture::SelectPicture( CDC * ptrDC,  HDC * oldHDC, OLE_HANDLE * phbmpOut )
{
	HRESULT result = m_spIPicture->SelectPicture(ptrDC->m_hDC,  //New device context
		oldHDC,//Receives a pointer to the previous device context
		phbmpOut);//Receives a pointer to GDI handle of the picture
	//HRESULT result = m_spIPicture->SelectPicture(ptrDC->m_hDC,  //New device context
	//	NULL,//Receives a pointer to the previous device context
	//	NULL);//Receives a pointer to GDI handle of the picture
	return ( result == S_OK );
}