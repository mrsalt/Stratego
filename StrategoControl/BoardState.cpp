// BoardState.cpp: implementation of the CBoardState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrategoControl.h"
#include "BoardState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoardState::CBoardState()
//CBoardState::CBoardState()
{
	//m_BoardControl = NULL;//pCtrl;
	//IllegalMove = CPoint(-1,-1);
	//lastSquareMoved1 = CPoint(-1,-1);
	//lastSquareMoved2 = CPoint(-1,-1);

}

CBoardState::~CBoardState()
{

}

bool CBoardState::PlacePiece(int Owner, CPoint location, StrategoPieceType piece)
{
	//if (location == CPoint(
	if (!IsLocationInLake(location) && m_square[location.x][location.y].m_Owner == NO_OWNER)
	{
		m_square[location.x][location.y].m_Owner = Owner;
		m_square[location.x][location.y].m_Piece = piece;
		m_square[location.x][location.y].m_Redraw = true;
		return true;
	}
	return false;
}

bool CBoardState::IsLocationInLake(CPoint location)
{
	return ((location.x >= 2 && location.x <= 3 && location.y >= 4 && location.y <= 5) ||
		    (location.x >= 6 && location.x <= 7 && location.y >= 4 && location.y <= 5));
}


bool CBoardState::ClearPiece(CPoint location)
{
	if ( m_square[location.x][location.y].m_Owner )
	{
		m_square[location.x][location.y].m_Piece = NoPiece;
		m_square[location.x][location.y].m_Owner = NO_OWNER;
		m_square[location.x][location.y].m_Redraw = true;
		return true;
	}
	return false;
}

bool CBoardState::IsMoveLegal(int PlayerID, StrategoPiece piece, CPoint fromSquare, CPoint toSquare)
{
	// assume that the person moving the piece owns the piece
	
	return (piece.m_Owner == PlayerID && // have to own piece to move it
		//piece == m_square[fromSquare.x][fromSquare.y] &&  - we may have already lifted the piece... this check becomes invalid then
		fromSquare != toSquare &&
		SquareDistance( fromSquare, toSquare) <= PieceMovement( piece.m_Piece ) &&
		(toSquare.x - fromSquare.x == 0  || toSquare.y - fromSquare.y == 0) && // direction is valid (diagonal moves not allowed
		!IsLocationInLake( toSquare ) &&
		toSquare.x >= 0 && toSquare.x < BOARD_COLUMNS &&
		toSquare.y >= 0 && toSquare.y < BOARD_ROWS &&
		m_square[toSquare.x][toSquare.y].m_Owner != piece.m_Owner &&  // can't move a piece onto a square occupied by myself...
		!IsJumpingPieceOrLake(fromSquare, toSquare) &&
		(SquareDistance( fromSquare, toSquare ) < 2 || !m_square[toSquare.x][toSquare.y].m_Owner) &&
		!(toSquare == lastMove2[piece.m_Owner].to && fromSquare == lastMove2[piece.m_Owner].from )); // can't go back and forth between 2 squares in 3 consecutive turns
}

int CBoardState::PieceMovement(StrategoPieceType p)
{
	switch (p)
	{
	case NoPiece: 
	case Bomb:
	case Flag:
		return 0;
	case Marshal:
	case General:
	case Colonel:
    case Major:
	case Captain:
	case Lieutenant:
	case Sergeant:
	case Miner:
	case Spy:
		return 1;
	case Scout:
		return 9;
	}
	return 0;
}

int CBoardState::SquareDistance(CPoint p1, CPoint p2)
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool CBoardState::IsJumpingPieceOrLake(CPoint fromSquare, CPoint toSquare)
{
	int dist = SquareDistance( fromSquare, toSquare );
	CPoint dP = CPoint( (toSquare.x - fromSquare.x) / dist, (toSquare.y - fromSquare.y) / dist ); // movement vector
	
	for (CPoint pos = fromSquare + dP; pos != toSquare; pos += dP)
	{
		if ( IsLocationInLake(pos) )
			return true;
		if ( m_square[pos.x][pos.y].m_Owner )
			return true;
	}
	return false;
}

bool CBoardState::PotentialMoveExists(int who, StrategoPiece piece, CPoint p)
{
	return (PieceMovement(piece.m_Piece) &&
		   (IsMoveLegal(who, piece, p, p + CPoint(1,0)) ||
		    IsMoveLegal(who, piece, p, p + CPoint(0,1)) ||
			IsMoveLegal(who, piece, p, p + CPoint(-1,0)) ||
			IsMoveLegal(who, piece, p, p + CPoint(0,-1))));
}

BattleResolutionType CBoardState::Battle(StrategoPieceType attacker, StrategoPieceType defender)
{
	ASSERT(PieceMovement(attacker));

	if (defender == Flag)
		return WinGame;

	if (defender == Bomb)
	{
		if (attacker == Miner)
			return Win;
		else
			return Lose;
	}

	if (attacker == Spy && defender == Marshal)
		return Win;

	if (attacker < defender)
		return Win;
	else if (attacker > defender)
		return Lose;
	else
		return Tie;
}

void CBoardState::RecordMove(int PlayerID, CPoint from, CPoint to)
{	
	lastMove2[PlayerID - 1] = lastMove1[PlayerID - 1];
	lastMove1[PlayerID - 1] = Move(from, to);	
}

void CBoardState::RedrawAllPieces()
{
	for (int j = 0; j < BOARD_ROWS; j++)
	{
		for (int i = 0; i < BOARD_COLUMNS; i++)
		{
			m_square[i][j].m_Redraw = true;
		}
	}
}

void CBoardState::ClearBoard(void)
{
	for (int j = 0; j < BOARD_ROWS; j++)
	{
		for (int i = 0; i < BOARD_COLUMNS; i++)
		{
			ClearPiece(CPoint(i,j));
		}
	}
}
