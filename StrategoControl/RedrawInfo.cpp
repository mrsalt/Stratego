// RedrawInfo.cpp: implementation of the CRedrawInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrategoControl.h"
#include "RedrawInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRedrawInfo::CRedrawInfo()
: m_RefreshPieces(false)
, m_ShowBattleResults(false)
{
	m_AnimateFrameCount = 0;

	mPlacePiece = false;
	m_All = true;
	m_Sizing = false;
	m_Scrolling = false;
	m_DrawEffects = true;
	m_MovingPiece = false;
	m_RefreshPieces = false;

	m_AnimatingSquare = CPoint(-1,-1);
	m_LastSquareAnimated = CPoint(-1,-1);
	m_HighlightPossibleMoves = false;
	m_SetupPieces = false;
	m_ShowBattleResults = 0;
}

CRedrawInfo::~CRedrawInfo()
{

}

void CRedrawInfo::ResetAll()
{
	m_All = false;
	m_Sizing = false;
	m_Scrolling = false;
	m_DrawEffects = false;
	mPlacePiece = false;
	m_HighlightPossibleMoves = false;
	m_SetupPieces = false;
	m_RefreshPieces= false;
	// m_MovingPiece does not change here... only with mouse events
}

bool CRedrawInfo::ResetState(void)
{
	if (m_All == false && m_Sizing == false && m_Scrolling == false && m_MovingPiece == false)
		return true;
}
