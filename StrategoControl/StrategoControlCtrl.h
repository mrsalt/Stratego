#pragma once

// StrategoControlCtrl.h : Declaration of the CStrategoControlCtrl ActiveX Control class.


// CStrategoControlCtrl : See StrategoControlCtrl.cpp for implementation.
#include "Picture.h"	// Added by ClassView
#include "StrategoDefinitions.h"
#include "RedrawInfo.h"	// Added by ClassView
#include "BoardState.h"
#include <afxtempl.h>
#include "StrategoSquare.h"	// Added by ClassView
#include "Canvas.h"	// Added by ClassView
#include "PlayerData.h"
#include "c:\source code\my projects\stratego\bitmaprenderer\morphbmp.h"

struct MoveCommand
{
	bool execute;
	CPoint from;
	CPoint to;
};
		
class CStrategoControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CStrategoControlCtrl)

// Constructor
public:
	CStrategoControlCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// Implementation
protected:
	~CStrategoControlCtrl();

	DECLARE_OLECREATE_EX(CStrategoControlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CStrategoControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CStrategoControlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CStrategoControlCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:

	enum {
		eventidBattleOccured = 6L,		dispidRestartGame = 12,
		dispidRemovePiece = 11,
		dispidMovePiece = 10,
		dispidPlacePiece = 9,
		dispidSetStateAndPlayer = 8,
		dispidSetPlayerData = 7,
		dispidPlaceUnitsAtStart = 6,
		dispidCurrentPlayer = 5,
		dispidAllowScrolling = 4,		
		dispidShowAllPieces = 3,
		dispidBoardState = 2,
		dispidShowPiecesPanel = 1,
		eventidPieceRemoved = 5L,
		eventidPieceMoved = 4L,
		eventidGameOver = 3L,
		eventidPiecePlaced = 2L,
		eventidSetupDone = 1L
	};
protected:
	// Get / Set Properties
	SHORT GetBoardState(void);
	void SetBoardState(SHORT newVal);
	SHORT GetShowPiecesPanel(void);
	void SetShowPiecesPanel(SHORT newVal);
	
	LONG SetPlayerData(SHORT PlayerID, SHORT Type, SHORT Color);
	LONG SetStateAndPlayer(SHORT State, SHORT PlayerID);
	LONG PlacePiece(SHORT PlayerID, SHORT x, SHORT y, SHORT Type);
	LONG MovePiece(SHORT x1, SHORT y1, SHORT x2, SHORT y2);

	void SetupDone(void)
	{
		FireEvent(eventidSetupDone, EVENT_PARAM(VTS_NONE));
	}

	void PiecePlaced(SHORT PlayerID, SHORT x1, SHORT y1, SHORT Type)
	{
		FireEvent(eventidPiecePlaced, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I2 VTS_I2), PlayerID, x1, y1, Type);
	}

	void GameOver(SHORT PlayerID, SHORT Reason)
	{
		FireEvent(eventidGameOver, EVENT_PARAM(VTS_I2 VTS_I2), PlayerID, Reason);
	}

	void PieceMoved(SHORT PlayerID, SHORT x1, SHORT y1, SHORT x2, SHORT y2, SHORT Type)
	{
		FireEvent(eventidPieceMoved, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2), PlayerID, x1, y1, x2, y2, Type);
	}

	void DoInitialization(CDC *pSrcDC, const CRect &rcBounds);
    
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

private:


// Logic Helper Functions	
	bool ShowPiecesPanel();

// Drawing Helper Functions
	BOOL ClearPiece(CPoint pos);
	void HighlightMoves( CPoint startSquare, DirectionType direction );
	void CancelAnimatingSquare();
	void SetAnimatingSquare( CPoint square );
	void CalculatePieceAnimation();  // determines if piece animation (highlighting) is necessary
	void CopyPiece(StrategoPiece s, CDC *pDestDC, const CRect &coords, int xSrc = 0, int ySrc = 0);
	void CopyPiece(CDC * pieceDC, CDC * pDestDC, const CRect & coords, int xSrc = 0, int ySrc = 0);
	void AnimatePiece(StrategoPiece s, CDC *pDestDC, const CRect &coords, int xSrc = 0, int ySrc = 0);
	void AnimatePiece(CDC * pieceDC, CDC * pDestDC, const CRect & coords, int xSrc = 0, int ySrc = 0);
	CRect UndrawPiece(CDC *pDC, CPoint location);
	CRect DrawPiece(CDC * pDC, CPoint location, int animate = 0, int background = 0);  // background: 0=no change, 1=normal, 2=highlight
	CRect DrawSetupPiece(CDC *pDC, StrategoPiece piece, int count);

// Initialization Functions	
	bool LoadPicture( CPicture & picture, const char * filename );
	const char * getPieceFileName( StrategoPieceType piece, StrategoColor color );

// Piece Setup Functions
	CPoint PiecePanelGetPieceLocation( StrategoPieceType piece );
	StrategoPieceType PiecePanelGetStrategoPiece( CPoint p );
	bool ScreenToPiecePanelCoordinates( CPoint &p );

// Metric Functions
	CRect GetAbsolutePieceCoordinates(CPoint square);	
	CRect GetAbsoluteCoordinates(CPoint square);
	CRect GetScreenCoordinates(CPoint square);
	void CalculateDimensions();
	void CalculateBoardPosition();
	void GetMousePos(CPoint & point);

// Scrolling Functions
	int GetScrollAmount(int);
	void DoScrolling();

// Logic Helper Data	
	bool m_showPiecesPanel;
// Drawing Helper Data
	CList<CPoint,CPoint> m_HighlightedSquares;
	CList<CRect, CRect> m_DrawingDC_List;
	CRedrawInfo m_RedrawInfo;	
// Initialization Data
	char * m_missingImage;
	bool m_imagesLoaded;
	bool m_GraphicsInitialized;
// Metric Data
	CPoint m_piecesPanelOffset;
	CSize m_BoardClientSize;
	CSize m_piecesPanelSize;
	CPoint m_imageOffset;
	CSize m_imageSize;
	CSize m_SquareSize;
	CPoint m_MouseSquare;
	CPoint m_Mouse;
	CSize m_ClientSize;
	//CSize m_BoardSize;
	CPoint m_BoardPosition;
	CSize m_SetupSize;

// Piece-Dragging Data	
	CPoint m_MoveLastPos;
	CPoint m_MoveStartSquare;
	StrategoPiece m_MovePiece;
	CPoint m_MoveStart;
	bool  m_MoveFromSetup;
// Game State Data	
	int m_CurrentID; // 1,2 are valid values
	StrategoColor m_MyColor; // Blue == 0, Red == 1
	CBoardState m_Board;
	BoardStateType m_BoardState;
	int m_piecesAvailable[12];
// Scrolling Data
	bool m_ScrollOutOfWindow;
	bool m_ScrollingTimerEnabled;
// Bitmaps and DCs	
	CCanvas * m_ptrCanvas;
	CCanvas m_SetupCanvas;
	CCanvas m_BoardCanvas;
    CCanvas m_DialogCanvas;

	CDC TempDC;
	CDC piece_dc[NUM_COLORS][NUM_PIECES];
	CDC piecesPanel_dc;
	CDC piecesPanelPieces_dc;
	CDC unknownPiece_dc[NUM_COLORS];
	
	CPicture pieces[NUM_COLORS][NUM_PIECES];
	CPicture piecesPanel;
	CPicture unknownPiece[NUM_COLORS];

	CBitmap m_MaskBMP;
	CBitmap piecesPanelBitmap;

protected:
// Uncategorized:
	void ShowBattleResults(StrategoPiece attackPiece, StrategoPiece defendPiece, BattleResolutionType outcome, bool HideAttack, bool HideDefend);
	CPlayerData m_Players[2];
	CPlayerData & Player(int PlayerID);
	void PlaceAllRemainingPieces(void);
	bool m_HideEnemyPieces;
	CPoint BoardToScreen( CPoint boardPoint );
	CPoint ScreenToBoard( CPoint clientPoint );
	StrategoColor GetPlayerColor( int playerID );
	CPoint m_MovePotentialDest;
	CPoint m_MoveHighlightSquare;

	void DoBattle( CPoint p1, CPoint p2, StrategoPiece attacker, StrategoPiece defender );
	CPoint m_AutoMoveEndSquare;
	CPoint GetSquareCenter( CPoint square );
	double Distance( CPoint p );
	int m_AutoMoveDistance;
	CPoint m_DragPosition;
	CPoint m_AutoMoveDelta;
	bool m_AutoMove;
	CPoint m_AutoMoveStart;
	int getPieceSpeed ( double fracDone, int minSpeed, int maxSpeed);
	void RepositionControls();
	CEdit * m_TextArea;
	int m_SetupPiecesLeft;
	int GetSetupPiecesRemaining();
	void OnOK();
	CButton * m_Button;


	void PieceRemoved(SHORT PlayerID, SHORT x, SHORT y, SHORT Type)
	{
		FireEvent(eventidPieceRemoved, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I2 VTS_I2), PlayerID, x, y, Type);
	}
public:
	bool _PlacePiece(int PlayerID, CPoint point, StrategoPieceType piece);
protected:
	LONG GetShowAllPieces(void);
	void SetShowAllPieces(LONG newVal);
	CMorphBMP * m_BattleMBMP;
	void OnAllowScrollingChanged(void);
	LONG m_AllowScrolling;
private:
	bool m_DialogShowing;
	MoveCommand m_lastAutoMove;
public:
	void DrawBoard(CDC * currentDC, CRect rcBounds);
	void DrawDebug(CDC * currentDC, CRect rcBounds);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	BattleResolutionType m_last_battle_outcome;
protected:
	LONG GetCurrentPlayer(void);
	void SetCurrentPlayer(LONG newVal);
private:
	void InitializeGame(void);
protected:
	LONG RemovePiece(SHORT x, SHORT y);
private:
	void TurnOver(void);
protected:
	void RestartGame(void);
	void OnPlaceUnitsAtStartChanged(void);
	LONG m_PlaceUnitsAtStart;

	void BattleOccured(SHORT AttackerPiece, SHORT DefenderPiece, SHORT BattleResult)
	{
		FireEvent(eventidBattleOccured, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I2), AttackerPiece, DefenderPiece, BattleResult);
	}
};

