#pragma once
#include "strategodefinitions.h"

class CPlayerData
{
public:
	CPlayerData(void);
	~CPlayerData(void);

	PlayerType    m_PlayerType;
	StrategoColor m_Color;
};
