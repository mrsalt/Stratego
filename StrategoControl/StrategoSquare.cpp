// StrategoSquare.cpp: implementation of the StrategoSquare class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrategoControl.h"
#include "StrategoSquare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StrategoPiece::StrategoPiece( StrategoPieceType initPiece, int initOwner )
{
	m_Owner = initOwner;
	m_Piece = initPiece;
	m_Redraw = false;
}

StrategoPiece::~StrategoPiece()
{

}

bool StrategoPiece::operator==( const StrategoPiece & rhs ) const
{
	return m_Owner == rhs.m_Owner && m_Piece == rhs.m_Piece;
}

