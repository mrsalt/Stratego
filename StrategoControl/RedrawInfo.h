// RedrawInfo.h: interface for the CRedrawInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REDRAWINFO_H__2008D077_8EDA_47FE_BC64_4EEED8CCAC61__INCLUDED_)
#define AFX_REDRAWINFO_H__2008D077_8EDA_47FE_BC64_4EEED8CCAC61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRedrawInfo  
{
public:
	bool m_SetupPieces;
	bool m_HighlightPossibleMoves;
	int m_AnimateFrameCount;
	bool m_MovingPiece;
	bool mPlacePiece;
	bool m_DrawEffects;
	bool m_Scrolling;
	CPoint m_LastSquareAnimated;
	CPoint m_AnimatingSquare;
	void ResetAll();
	bool m_All;
	bool m_Sizing;
	CRedrawInfo();
	virtual ~CRedrawInfo();

	bool m_RefreshPieces;
	int m_ShowBattleResults;
	bool ResetState(void);
};

#endif // !defined(AFX_REDRAWINFO_H__2008D077_8EDA_47FE_BC64_4EEED8CCAC61__INCLUDED_)
