// StrategoSquare.h: interface for the StrategoSquare class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRATEGOSQUARE_H__91DC1A02_7F29_4932_8F54_65539E930DB1__INCLUDED_)
#define AFX_STRATEGOSQUARE_H__91DC1A02_7F29_4932_8F54_65539E930DB1__INCLUDED_

#include "StrategoDefinitions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class StrategoPiece  
{
public:
	bool m_Redraw;
	StrategoPiece( StrategoPieceType = NoPiece, int initOwner = 0 );
	virtual ~StrategoPiece();
	int m_Owner;
	StrategoPieceType m_Piece;
	bool operator==( const StrategoPiece & rhs ) const;
};

#endif // !defined(AFX_STRATEGOSQUARE_H__91DC1A02_7F29_4932_8F54_65539E930DB1__INCLUDED_)
