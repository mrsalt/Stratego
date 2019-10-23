// BoardState.h: interface for the CBoardState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOARDSTATE_H__BE245526_1A71_41F0_A598_2107F3129315__INCLUDED_)
#define AFX_BOARDSTATE_H__BE245526_1A71_41F0_A598_2107F3129315__INCLUDED_

#include "StrategoSquare.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoardState  
{
public:
	void RedrawAllPieces();
	class Move
	{
	public:
		Move() {};
		Move(CPoint initFrom, CPoint initTo) : from(initFrom), to(initTo) {};
		CPoint from;
		CPoint to;
	};
	void RecordMove( int PlayerID, CPoint from, CPoint to );
	BattleResolutionType Battle( StrategoPieceType attacker, StrategoPieceType defender );
	bool PotentialMoveExists( int who, StrategoPiece piece, CPoint p );
	bool IsJumpingPieceOrLake( CPoint fromSquare, CPoint toSquare );
	int SquareDistance( CPoint p1, CPoint p2 );
	int PieceMovement( StrategoPieceType p );
	bool IsMoveLegal( int who, StrategoPiece piece, CPoint fromSquare, CPoint toSquare );
	bool ClearPiece( CPoint location );
	
	CBoardState();
	virtual ~CBoardState();
	
	bool IsLocationInLake(CPoint location);
	bool PlacePiece(int Owner, CPoint location, StrategoPieceType piece);

	StrategoPiece m_square[BOARD_COLUMNS][BOARD_ROWS];
private:
	Move lastMove1[NUM_COLORS];
	Move lastMove2[NUM_COLORS];
	
public:
	void ClearBoard(void);
};

#endif // !defined(AFX_BOARDSTATE_H__BE245526_1A71_41F0_A598_2107F3129315__INCLUDED_)
