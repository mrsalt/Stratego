// StrategoControlCtrl.cpp : Implementation of the CStrategoControlCtrl ActiveX Control class.

#include "stdafx.h"
#include "StrategoControl.h"
#include "StrategoControlCtrl.h"
#include "StrategoControlPropPage.h"
#include <Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <stdio.h>

void WriteDebug(char * filename, long line_number, char * additional_text)
{
#if 0
	static FILE * debug_file_ptr = NULL;
	if (!debug_file_ptr)
	{
		debug_file_ptr = fopen("C:\\stratego_debug.txt", "w");
	}

	if (debug_file_ptr)
	{
		fprintf(debug_file_ptr, "%s:%i %s\n", filename, line_number, additional_text ? additional_text : "");
		fflush(debug_file_ptr);
	}
#endif
}


IMPLEMENT_DYNCREATE(CStrategoControlCtrl, COleControl)

char * StrategoPieceNames[] = { "Bomb", "Marshal", "General", "Colonel", "Major", "Captain", "Lieutenant", "Sergeant", "Miner", "Scout", "Spy", "Flag" };

// Message map

BEGIN_MESSAGE_MAP(CStrategoControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDC_OK_PRESSED, OnOK)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// Dispatch map

BEGIN_DISPATCH_MAP(CStrategoControlCtrl, COleControl)
	DISP_PROPERTY_EX_ID(CStrategoControlCtrl, "ShowPiecesPanel", dispidShowPiecesPanel, GetShowPiecesPanel, SetShowPiecesPanel, VT_I2)
	DISP_PROPERTY_EX_ID(CStrategoControlCtrl, "BoardState", dispidBoardState, GetBoardState, SetBoardState, VT_I2)
	DISP_PROPERTY_EX_ID(CStrategoControlCtrl, "ShowAllPieces", dispidShowAllPieces, GetShowAllPieces, SetShowAllPieces, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CStrategoControlCtrl, "AllowScrolling", dispidAllowScrolling, m_AllowScrolling, OnAllowScrollingChanged, VT_I4)
	DISP_PROPERTY_EX_ID(CStrategoControlCtrl, "CurrentPlayer", dispidCurrentPlayer, GetCurrentPlayer, SetCurrentPlayer, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CStrategoControlCtrl, "PlaceUnitsAtStart", dispidPlaceUnitsAtStart, m_PlaceUnitsAtStart, OnPlaceUnitsAtStartChanged, VT_I4)	
	DISP_FUNCTION_ID(CStrategoControlCtrl, "SetPlayerData", dispidSetPlayerData, SetPlayerData, VT_I4, VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CStrategoControlCtrl, "SetStateAndPlayer", dispidSetStateAndPlayer, SetStateAndPlayer, VT_I4, VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CStrategoControlCtrl, "PlacePiece", dispidPlacePiece, PlacePiece, VT_I4, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CStrategoControlCtrl, "MovePiece", dispidMovePiece, MovePiece, VT_I4, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CStrategoControlCtrl, "RemovePiece", dispidRemovePiece, RemovePiece, VT_I4, VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CStrategoControlCtrl, "RestartGame", dispidRestartGame, RestartGame, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CStrategoControlCtrl, COleControl)
	EVENT_CUSTOM_ID("SetupDone", eventidSetupDone, SetupDone, VTS_NONE)
	EVENT_CUSTOM_ID("PiecePlaced", eventidPiecePlaced, PiecePlaced, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	EVENT_CUSTOM_ID("GameOver", eventidGameOver, GameOver, VTS_I2 VTS_I2)
	EVENT_CUSTOM_ID("PieceMoved", eventidPieceMoved, PieceMoved, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	EVENT_CUSTOM_ID("PieceRemoved", eventidPieceRemoved, PieceRemoved, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	EVENT_CUSTOM_ID("BattleOccured", eventidBattleOccured, BattleOccured, VTS_I2 VTS_I2 VTS_I2)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CStrategoControlCtrl, 1)
	PROPPAGEID(CStrategoControlPropPage::guid)
END_PROPPAGEIDS(CStrategoControlCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CStrategoControlCtrl, "STRATEGO.StrategoClassicCtrl.1",
	0x9ccb537e, 0x5273, 0x43cb, 0xbe, 0xa9, 0x75, 0xd9, 0xe7, 0x16, 0xaa, 0x46)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CStrategoControlCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DStrategoControl =
		{ 0xA1A0215D, 0x3505, 0x4748, { 0xAE, 0x90, 0xC2, 0x31, 0x8, 0x1B, 0x5B, 0x93 } };
const IID BASED_CODE IID_DStrategoControlEvents =
		{ 0xDA56CC2C, 0x8811, 0x4831, { 0x92, 0x22, 0x29, 0x33, 0x3D, 0xF9, 0x4, 0x74 } };



// Control type information

static const DWORD BASED_CODE _dwStrategoControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CStrategoControlCtrl, IDS_STRATEGOCONTROL, _dwStrategoControlOleMisc)



// CStrategoControlCtrl::CStrategoControlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CStrategoControlCtrl

BOOL CStrategoControlCtrl::CStrategoControlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_STRATEGOCONTROL,
			IDB_STRATEGOCONTROL,
			afxRegApartmentThreading,
			_dwStrategoControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CStrategoControlCtrl::CStrategoControlCtrl - Constructor

CStrategoControlCtrl::CStrategoControlCtrl()
: m_DialogShowing(false)
{
WriteDebug(__FILE__,__LINE__,NULL);
	InitializeIIDs(&IID_DStrategoControl, &IID_DStrategoControlEvents);
	// TODO: Initialize your control's instance data here.
	m_HideEnemyPieces = true;
	m_showPiecesPanel = false;
	m_GraphicsInitialized = false;
    m_imagesLoaded = false;
	m_ScrollingTimerEnabled = false;
	m_ScrollOutOfWindow = true;
	m_BattleMBMP = NULL;
	m_missingImage = NULL;
	m_PlaceUnitsAtStart = false;

	m_imagesLoaded = LoadPicture(m_BoardCanvas.m_image, "images\\stratego_board.jpg") && 
		                 LoadPicture(m_BoardCanvas.m_image_highlight, "images\\stratego_board_light.jpg") &&
						 LoadPicture(m_BoardCanvas.m_image_outline, "images\\stratego_board_outline.jpg") &&
						 LoadPicture(unknownPiece[Blue], "images\\blueunknown.jpg") &&
						 LoadPicture(unknownPiece[Red], "images\\redunknown.jpg") &&
						 LoadPicture(piecesPanel, "images\\pieces.jpg") &&
						 LoadPicture(m_SetupCanvas.m_image, "images\\setup.jpg") &&
						 LoadPicture(m_DialogCanvas.m_image, "images\\messagebackground.jpg");



	for (int c = 0; c < NUM_COLORS; c++)
	{
		for (int p = 0; p < NUM_PIECES; p++)
		{
			const char * imagename = getPieceFileName( StrategoPieceType(p), StrategoColor(c) );
			char filename[32] = "images\\";
			strcat( filename, imagename ); 
			m_imagesLoaded == m_imagesLoaded && LoadPicture( pieces[c][p], filename );
		}
	}

	if (!m_imagesLoaded)
	{
		char message[255];
		wsprintf(message,"Could not load %s.  Make sure all image files are in image directory.",m_missingImage);
		MessageBox(message,"Error",MB_ICONSTOP);
	}

	m_MaskBMP.LoadBitmap(IDB_STRATEGO_MASK);	
	m_Button = NULL;

	InitializeGame();
}



// CStrategoControlCtrl::~CStrategoControlCtrl - Destructor

CStrategoControlCtrl::~CStrategoControlCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if (m_Button)
		delete m_Button;
	if (m_BattleMBMP)
		delete m_BattleMBMP;
}



// CStrategoControlCtrl::OnDraw - Drawing function

void CStrategoControlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
WriteDebug(__FILE__,__LINE__,NULL);
	if ( m_RedrawInfo.ResetState())
		m_RedrawInfo.m_All = true;

	if (!m_GraphicsInitialized)
	{
		DoInitialization(pdc, rcBounds);
	}
	
	if (m_GraphicsInitialized)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		CDC *currentDC = pdc;

		
		if ( m_DialogShowing )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			CSize battleSize = m_BattleMBMP->GetDimensions();
			CPoint drawPoint = rcBounds.CenterPoint() - CSize(battleSize.cx / 2, battleSize.cy / 2);
			if ( m_RedrawInfo.m_ShowBattleResults == 1)
			{
WriteDebug(__FILE__,__LINE__,NULL);
				m_BattleMBMP->Draw( currentDC, drawPoint, CMorphBMP::DrawFirst );
				SetTimer( ID_DRAW_BATTLE_TIMER, 200, NULL);
				m_RedrawInfo.m_ShowBattleResults = 0;
			}
			else if ( m_RedrawInfo.m_ShowBattleResults == 2)
			{
WriteDebug(__FILE__,__LINE__,NULL);
				m_BattleMBMP->Draw( currentDC, drawPoint, CMorphBMP::DrawActionType::Complete );
				// show the OK button
				RepositionControls();
				m_Button->ShowWindow(SW_SHOW);
				m_RedrawInfo.m_ShowBattleResults = 3;
			}
			else if ( m_RedrawInfo.m_ShowBattleResults == 3)
			{
				if ( m_RedrawInfo.m_Sizing || m_RedrawInfo.m_All )
				{
WriteDebug(__FILE__,__LINE__,NULL);
					DrawBoard(currentDC, rcBounds);
					m_BattleMBMP->Draw( currentDC, drawPoint, CMorphBMP::DrawActionType::DrawLast );
					m_RedrawInfo.m_Sizing = false;
					m_RedrawInfo.m_All = false;
				}
			}
			return;
		}
		/*
		*/
		// Drawing to MenBoardDC starts here:
		m_DrawingDC_List.RemoveAll();
		
		if (m_RedrawInfo.mPlacePiece || m_RedrawInfo.m_RefreshPieces || m_RedrawInfo.m_All)
		{
WriteDebug(__FILE__,__LINE__,NULL);
			int column, row;
			// clear pieces off of squares
			for ( column = 0; column < BOARD_COLUMNS; column++)
			{
				for ( row = 0; row < BOARD_ROWS; row++)
				{
					if (m_Board.m_square[column][row].m_Redraw && !m_Board.m_square[column][row].m_Owner)
					{
						m_Board.m_square[column][row].m_Redraw = false;
						// clear a piece off of this square
						m_DrawingDC_List.AddHead( UndrawPiece(&m_ptrCanvas->m_frontDC, CPoint(column, row)) );
					}
				}
			}
			// place pieces in squares
			for ( column = 0; column < BOARD_COLUMNS; column++)
			{
				for ( row = 0; row < BOARD_ROWS; row++)
				{
					if ((m_Board.m_square[column][row].m_Redraw || m_RedrawInfo.m_RefreshPieces) && m_Board.m_square[column][row].m_Owner)
					{
						m_Board.m_square[column][row].m_Redraw = false;
						// draw a piece in this square
						m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, CPoint(column,row)) );
						//DrawPiece(&DrawingDC, CPoint(column,row));
					}
				}
			}
		}
		/*
		*/
		if ( m_RedrawInfo.m_SetupPieces )
		{
			for (StrategoPieceType p = Bomb; p <= Flag; p = StrategoPieceType ( p + 1) )
			{
				m_DrawingDC_List.AddHead( DrawSetupPiece( &m_ptrCanvas->m_frontDC, StrategoPiece(p, m_CurrentID), m_piecesAvailable[p] ) );
			}
		}
		
		if ( m_RedrawInfo.m_HighlightPossibleMoves )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			if ( m_RedrawInfo.m_MovingPiece && Player(m_CurrentID).m_PlayerType == Human )
			{
				m_HighlightedSquares.RemoveAll();
				HighlightMoves( m_MoveStartSquare, All );
			}
			else
			{
				POSITION pos = m_HighlightedSquares.GetHeadPosition();
				CPoint s;
				while ( pos )
				{
					s = m_HighlightedSquares.GetNext( pos );
					m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, s, 0, 1 ) ); // un-highlight this square
				}
			}
		}
		
		if ( (m_MovePotentialDest != m_MoveHighlightSquare || !m_RedrawInfo.m_MovingPiece) && m_MoveHighlightSquare != CPoint(-1, -1)) 
		{
WriteDebug(__FILE__,__LINE__,NULL);
			// either the highlight has changed and we need to erase the previous highlight
			// or we are no longer dragging a piece
			if (!m_RedrawInfo.m_MovingPiece)
				m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, m_MoveHighlightSquare, 0, 1 ) );
			else
				m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, m_MoveHighlightSquare, 0, 2 ) );
		}
		
		if ( m_RedrawInfo.m_MovingPiece && m_MovePotentialDest != m_MoveHighlightSquare )
		{	
			// this block of code creates the red outline on a square as you drag 
			// the piece around to different possible moves
			m_MoveHighlightSquare = m_MovePotentialDest;
			if (m_MovePotentialDest != CPoint(-1, -1))
				m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, m_MoveHighlightSquare, 0, 3 ) );
		}
		
		if (m_RedrawInfo.m_DrawEffects)
		{
			// this code highlights a square with a piece that could be moved
			if (m_RedrawInfo.m_LastSquareAnimated != CPoint(-1,-1) && m_RedrawInfo.m_LastSquareAnimated != m_RedrawInfo.m_AnimatingSquare)
			{
				// determine piece to copy based on who owns the square
				m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, m_RedrawInfo.m_LastSquareAnimated, 0, 1)); // wipe it away
				m_RedrawInfo.m_LastSquareAnimated = CPoint(-1, -1);
			}
            
			if (m_RedrawInfo.m_AnimatingSquare != CPoint(-1,-1))
			{
				m_RedrawInfo.m_LastSquareAnimated = m_RedrawInfo.m_AnimatingSquare; 
				m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC,m_RedrawInfo.m_AnimatingSquare, 0, 3));
			}
			//m_RedrawInfo.m_All = true;
		}

		// Drawing to MenBoardDC is complete!!

		// Begin drawing to DrawingDC
		POSITION pos = m_DrawingDC_List.GetHeadPosition();
		CRect drawing_area;
		while ( pos )
		{
			// copy from MenBoardDC to DrawingDC
			drawing_area = m_DrawingDC_List.GetNext( pos );
			m_ptrCanvas->m_drawDC.BitBlt(drawing_area.left,
			        drawing_area.top,
					drawing_area.Width(),
					drawing_area.Height(),
					&m_ptrCanvas->m_frontDC,
					drawing_area.left,
					drawing_area.top,
					SRCCOPY);
		}
/*
		if (m_RedrawInfo.m_DrawEffects)
		{
WriteDebug(__FILE__,__LINE__,NULL);
			if (m_RedrawInfo.m_LastSquareAnimated != CPoint(-1,-1) && m_RedrawInfo.m_LastSquareAnimated != m_RedrawInfo.m_AnimatingSquare)
			{
				// determine piece to copy based on who owns the square
				DrawPiece(&m_ptrCanvas->m_drawDC,m_RedrawInfo.m_LastSquareAnimated);
				m_RedrawInfo.m_LastSquareAnimated = CPoint(-1, -1);
			}
            
			if (m_RedrawInfo.m_AnimatingSquare != CPoint(-1,-1))
			{
				m_RedrawInfo.m_LastSquareAnimated = m_RedrawInfo.m_AnimatingSquare; 
				DrawPiece(&m_ptrCanvas->m_drawDC,m_RedrawInfo.m_AnimatingSquare, 1);
			}
			m_RedrawInfo.m_All = true;
		}
*/
		if ( m_MoveLastPos != CPoint(-1,-1) )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			// wipe out area where piece was
			m_ptrCanvas->m_drawDC.BitBlt( m_MoveLastPos.x, m_MoveLastPos.y, PIECE_WIDTH, PIECE_HEIGHT, &m_ptrCanvas->m_frontDC, m_MoveLastPos.x, m_MoveLastPos.y, SRCCOPY);
			m_MoveLastPos = CPoint(-1,-1);
		}

		if ( m_RedrawInfo.m_MovingPiece )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			CRect bRect;
			if (m_MoveFromSetup)
			{
				CPoint pieceCenter = PiecePanelGetPieceLocation( m_MovePiece.m_Piece ) + m_ptrCanvas->m_board_top_left_corner + CPoint(SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP);
				CPoint pieceTopLeft = pieceCenter - CPoint(PIECE_WIDTH / 2, PIECE_HEIGHT / 2);
				bRect = CRect( pieceTopLeft.x, pieceTopLeft.y, pieceTopLeft.x + PIECE_WIDTH, pieceTopLeft.y + PIECE_HEIGHT );
			}
			else
				bRect = GetAbsolutePieceCoordinates(m_MoveStartSquare);

			bRect.OffsetRect( m_DragPosition - m_MoveStart );
			m_MoveLastPos = bRect.TopLeft();
			CopyPiece(m_MovePiece, &m_ptrCanvas->m_drawDC, bRect);
		}

		// Drawing to DrawingDC is complete!!

		DrawBoard(currentDC, rcBounds);

 		CRect bRect = rcBounds;
		currentDC->DrawEdge(&bRect,EDGE_SUNKEN,BF_RECT);
		
		m_RedrawInfo.ResetAll();
        
		DrawDebug(currentDC, rcBounds);
	
	}
	else
	{
WriteDebug(__FILE__,__LINE__,NULL);
		CBrush blackBrush(RGB(0,0,0,));
		//oldObject = pdc->SelectObject(&blackBrush);
		CRect area = rcBounds;
		area.DeflateRect(2, 2, 2, 2);
		pdc->FillRect(area, &blackBrush);
		CRect bRect = rcBounds;
		pdc->DrawEdge(&bRect,EDGE_SUNKEN,BF_RECT);
	}
WriteDebug(__FILE__,__LINE__,NULL);
}

void CStrategoControlCtrl::DrawBoard(CDC * currentDC, CRect rcBounds)
{
WriteDebug(__FILE__,__LINE__,NULL);
	CGdiObject * oldObject;
	if (m_RedrawInfo.m_Sizing || m_RedrawInfo.m_All)
	{
		CBrush blackBrush(RGB(0,0,0,));
		oldObject = currentDC->SelectObject(&blackBrush);
		if	(m_BoardClientSize.cx > m_ptrCanvas->m_image_size.cx ) 
		{
			currentDC->FillRect(CRect(borderOffset,borderOffset,m_imageOffset.x, m_BoardClientSize.cy+borderOffset),NULL);
			currentDC->FillRect(CRect(m_BoardClientSize.cx - m_imageOffset.x,borderOffset,m_BoardClientSize.cx+borderOffset, m_BoardClientSize.cy+borderOffset),NULL);
		}
		if (m_BoardClientSize.cy > m_ptrCanvas->m_image_size.cy )
		{
			currentDC->FillRect(CRect(borderOffset,borderOffset,m_BoardClientSize.cx, m_imageOffset.y),NULL);
			currentDC->FillRect(CRect(borderOffset,m_BoardClientSize.cy - m_imageOffset.y,m_BoardClientSize.cx+borderOffset, m_BoardClientSize.cy+borderOffset),NULL);
		}
		currentDC->SelectObject(oldObject);
	}
WriteDebug(__FILE__,__LINE__,NULL);
	// copy DrawingDC to currentDC, which is either the screen or a buffer shared with the setup panel (during setup)
	if (m_RedrawInfo.m_Sizing || m_RedrawInfo.m_All || m_RedrawInfo.m_Scrolling)
	{
		currentDC->BitBlt(m_imageOffset.x,
			    m_imageOffset.y,
				m_imageSize.cx,
				m_imageSize.cy,
				&m_ptrCanvas->m_drawDC,
				(m_BoardPosition.x >= 0 ? m_BoardPosition.x : 0),
				(m_BoardPosition.y >= 0 ? m_BoardPosition.y : 0),
				SRCCOPY);
			//MessageBox("BitBlt failed from DrawingDC!");
	}
	
	if ( ShowPiecesPanel() )
	{
		CSize copySize = CSize( m_ClientSize.cx, m_piecesPanelSize.cy);

		if ( m_ClientSize.cx > m_piecesPanelSize.cx )
			copySize.cx = m_piecesPanelSize.cx;

		currentDC->BitBlt(m_piecesPanelOffset.x,
			    m_piecesPanelOffset.y,
				copySize.cx,
				copySize.cy,
				&piecesPanel_dc,
				0,
				0,
				SRCCOPY);
				
		CRect bRect;
		bRect.top = m_BoardClientSize.cy + borderOffset;
		bRect.bottom = m_BoardClientSize.cy + borderOffset + panelBorderWidth;
		bRect.left = borderOffset;
		bRect.right = borderOffset + m_ClientSize.cx;
		currentDC->DrawEdge(&bRect,EDGE_RAISED,BF_RECT);
		if (m_RedrawInfo.m_Sizing || m_RedrawInfo.m_All)
		{
			if	(m_ClientSize.cx > m_piecesPanelSize.cx) 
			{
				CBrush blackBrush(RGB(0,0,0,));
				oldObject = currentDC->SelectObject(&blackBrush);
				currentDC->FillRect(CRect(borderOffset,m_piecesPanelOffset.y,m_piecesPanelOffset.x, m_ClientSize.cy + borderOffset),NULL);
				currentDC->FillRect(CRect(m_piecesPanelOffset.x + copySize.cx,m_piecesPanelOffset.y,m_ClientSize.cx + borderOffset, m_ClientSize.cy + borderOffset),NULL);
				currentDC->SelectObject(oldObject);
			}
		}
		//pdc->BitBlt(0,0,rcBounds.Width(), rcBounds.Height(), currentDC, 0, 0, SRCCOPY);
	}
WriteDebug(__FILE__,__LINE__,NULL);
}

void CStrategoControlCtrl::DrawDebug(CDC * currentDC, CRect rcBounds)
{
	if (0) // DRAW YELLOW GRID LINES OVER BOARD
	{
		CPen yellowPen( PS_SOLID, 1, RGB(255,255,0));
		CGdiObject * oldPen = currentDC->SelectObject(&yellowPen);
	
		CPoint p = - m_BoardPosition;// - m_imageOffset;

		for (int i = 0; i <= BOARD_COLUMNS; i++){
			currentDC->MoveTo(p.x + i * m_SquareSize.cx, p.y);
			currentDC->LineTo(p.x + i * m_SquareSize.cx,p.y + m_ptrCanvas->m_image_size.cy);		
		
			currentDC->MoveTo(p.x,p.y + i * m_SquareSize.cy);
			currentDC->LineTo(p.x + m_ptrCanvas->m_image_size.cx,p.y + i * m_SquareSize.cy);		
		}
		currentDC->SelectObject(oldPen);
	}
	
	if (1)
	{
		CString m;
		/*
		m.Format("m_imageOffset.x = %i  ",m_imageOffset.x);
		currentDC->TextOut(5,5,m);
		m.Format("m_imageOffset.y = %i  ",m_imageOffset.y);
		currentDC->TextOut(5,21,m);
		m.Format("m_imageSize.cx = %i  ",m_imageSize.cx);
		currentDC->TextOut(5,37,m);
		m.Format("m_imageSize.cy = %i  ",m_imageSize.cy);
		currentDC->TextOut(5,53,m);
		m.Format("m_BoardPosition.x = %i  ",m_BoardPosition.x);
		currentDC->TextOut(5,69,m);
		m.Format("m_BoardPosition.y = %i  ",m_BoardPosition.y);
		currentDC->TextOut(5,82,m);
		
		m.Format("m_AnimatingSquare.x = %i  ",m_RedrawInfo.m_AnimatingSquare.x);
		currentDC->TextOut(5,98,m);
		m.Format("m_AnimatingSquare.y = %i  ",m_RedrawInfo.m_AnimatingSquare.y);
		currentDC->TextOut(5,114,m);

		m.Format("m_Mouse.x = %i  ",m_Mouse.x);
		currentDC->TextOut(5,130,m);
		m.Format("m_Mouse.y = %i  ",m_Mouse.y);
		currentDC->TextOut(5,146,m);

		m.Format("m_MouseSquare.x = %i  ",m_MouseSquare.x);
		currentDC->TextOut(5,162,m);
		m.Format("m_MouseSquare.y = %i  ",m_MouseSquare.y);
		currentDC->TextOut(5,178,m);
		*/
	}
}

// CStrategoControlCtrl::DoPropExchange - Persistence support

void CStrategoControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CStrategoControlCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
// For information on using these flags, please see MFC technical note
// #nnn, "Optimizing an ActiveX Control".
DWORD CStrategoControlCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control will not be redrawn when making the transition
	// between the active and inactivate state.
	dwFlags |= noFlickerActivate;
	return dwFlags;
}



// CStrategoControlCtrl::OnResetState - Reset control to default state

void CStrategoControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CStrategoControlCtrl message handlers

SHORT CStrategoControlCtrl::GetShowPiecesPanel(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	return m_showPiecesPanel;
}

void CStrategoControlCtrl::SetShowPiecesPanel(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_showPiecesPanel = (newVal == 0 ? false : true);
	CalculateDimensions();
	InvalidateControl();
	SetModifiedFlag();
}

LONG CStrategoControlCtrl::SetPlayerData(SHORT PlayerID, SHORT Type, SHORT Color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	Player(PlayerID).m_Color = StrategoColor(Color);
	Player(PlayerID).m_PlayerType = PlayerType(Type);
	return TRUE;
}

LONG CStrategoControlCtrl::SetStateAndPlayer(SHORT State, SHORT PlayerID)
{
WriteDebug(__FILE__,__LINE__,NULL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if (PlayerID == 1 || PlayerID == 2)
	{
		m_CurrentID = PlayerID;
		SetBoardState( State );
	}
	return TRUE;
}

LONG CStrategoControlCtrl::PlacePiece(SHORT PlayerID, SHORT x, SHORT y, SHORT Type)
{
WriteDebug(__FILE__,__LINE__,NULL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here
	
	return _PlacePiece(PlayerID, CPoint(x,y), StrategoPieceType(Type));
}

bool CStrategoControlCtrl::_PlacePiece(int PlayerID, CPoint point, StrategoPieceType piece)
{
	if (m_Board.PlacePiece(PlayerID, point, piece))
	{
		m_RedrawInfo.mPlacePiece = true;
		InvalidateControl();
		return true;
	}
	return false;
}

LONG CStrategoControlCtrl::MovePiece(SHORT x1, SHORT y1, SHORT x2, SHORT y2)
{
WriteDebug(__FILE__,__LINE__,NULL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!m_AutoMove)
	{
		StrategoPiece s = m_Board.m_square[x1][y1];
		
		if ( !s.m_Owner )
			return FALSE;

		if ( Player( s.m_Owner ).m_PlayerType != Other )
		{
			MessageBox("Only non-human pieces can be moved automatically");
			return FALSE;
		}
		

		if ( m_Board.IsMoveLegal( m_CurrentID, s, CPoint(x1, y1), CPoint(x2, y2)) )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			if ( m_DialogShowing )
			{
				m_lastAutoMove.execute = true;
				m_lastAutoMove.from = CPoint(x1,y1);
				m_lastAutoMove.to = CPoint(x2,y2);
				return TRUE;
			}

			ClearPiece( CPoint(x1, y1) );
			m_AutoMove = true;
			m_AutoMoveStart = GetSquareCenter(CPoint (x1, y1));			
			m_AutoMoveDistance = Distance( GetSquareCenter( CPoint(x2, y2) ) - m_AutoMoveStart );
			m_DragPosition = m_MoveStart = m_AutoMoveStart;
			m_AutoMoveEndSquare = CPoint(x2, y2);
			m_RedrawInfo.m_MovingPiece = true;
			m_AutoMoveDelta = CPoint(x2, y2) - CPoint(x1, y1);
			m_AutoMoveDelta.x = sqrt(abs(m_AutoMoveDelta.x)) * (m_AutoMoveDelta.x >= 0 ? 1 : -1);
			m_AutoMoveDelta.y = sqrt(abs(m_AutoMoveDelta.y)) * (m_AutoMoveDelta.y >= 0 ? 1 : -1);
			m_RedrawInfo.m_HighlightPossibleMoves = true;
		//	m_MoveStart = GetAbsoluteCoordinates( m_AutoMoveStart );
			m_MoveStartSquare = CPoint(x1, y1);
			m_MovePiece = StrategoPiece(s.m_Piece, m_CurrentID); //m_Board.m_square[ m_MouseSquare.x ][ m_MouseSquare.y ].m_Piece;
			//m_MoveLastPos = CPoint(-1,-1);
			m_MoveHighlightSquare = CPoint(-1,-1);
			m_MovePotentialDest = CPoint(-1,-1);
			ClearPiece( m_MoveStartSquare );

			SetTimer(ID_MOVE_PIECE_TIMER, 40, NULL);
			return TRUE;
		}
	}

	return FALSE;
}

void CStrategoControlCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CStrategoControlCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_DialogShowing)
		return;

	m_Mouse = point;
	
	if (!m_AutoMove)
		m_DragPosition = ScreenToBoard( m_Mouse );

	CalculateBoardPosition();
	//CalculatePieceAnimation();

    if (!m_ScrollingTimerEnabled)
	{
        DoScrolling();
	}
				
	if ( m_BoardState == PlayingGame && Player(m_CurrentID).m_PlayerType == Human )
	{
		CalculatePieceAnimation();
		if ( m_RedrawInfo.m_MovingPiece )
		{
			if ( m_Board.IsMoveLegal( m_CurrentID, m_MovePiece, m_MoveStartSquare, m_MouseSquare ) )
				m_MovePotentialDest = m_MouseSquare;
			else
				m_MovePotentialDest = CPoint(-1,-1);
		}
	}		
	if ( m_RedrawInfo.m_MovingPiece )
		InvalidateControl();
}

void CStrategoControlCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_DialogShowing)
		return;

	// m_MouseSquare has probably already been updated by the most recent mouse move call...
	if (Player(m_CurrentID).m_PlayerType == Human)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		m_Mouse = point;
		if (!m_AutoMove)
			m_DragPosition = ScreenToBoard(m_Mouse);

		CalculateBoardPosition();
		bool onBoard = false;

		StrategoPiece s;
		if ( m_MouseSquare.x >= 0 && m_MouseSquare.x < BOARD_COLUMNS &&
			m_MouseSquare.y >= 0 && m_MouseSquare.y < BOARD_ROWS )
		{
			onBoard = true;
			s = m_Board.m_square[ m_MouseSquare.x ][ m_MouseSquare.y ];
		}

		if ( m_MouseSquare.y < 6)
			onBoard = false;

		if ( m_BoardState == Setup )
		{
			if ( onBoard && s.m_Owner == m_CurrentID )
			{
				m_RedrawInfo.m_MovingPiece = true;
				m_MoveFromSetup = false;
				m_MoveStart = ScreenToBoard(point);
				m_MoveStartSquare = m_MouseSquare;
				m_MovePiece = StrategoPiece(s.m_Piece, m_CurrentID);
				m_MoveLastPos = CPoint(-1,-1);
				m_MoveHighlightSquare = CPoint(-1,-1);
				m_MovePotentialDest = CPoint(-1,-1);
				ClearPiece( m_MouseSquare );
			}
			else
			{
				CPoint p = point;
				if ( ScreenToPiecePanelCoordinates( p ) )
				{
					StrategoPieceType pieceType = PiecePanelGetStrategoPiece( p );
					
					if (pieceType != NoPiece && m_piecesAvailable[pieceType])
					{
						m_RedrawInfo.m_MovingPiece = true;
						m_MoveStart = ScreenToBoard(point);
						m_MoveFromSetup = true;
						m_MovePiece = StrategoPiece(pieceType, m_CurrentID);
						m_MoveLastPos = CPoint(-1,-1);
						m_MoveHighlightSquare = CPoint(-1,-1);
						m_MovePotentialDest = CPoint(-1,-1);
						m_piecesAvailable[pieceType]--;
						if (m_piecesAvailable[pieceType] == 0)
							m_RedrawInfo.m_SetupPieces = true;
						// possible clear piece here... update count (if count is showing)
					}
				}
				else if (onBoard)
				{
					if (m_SetupPiecesLeft && !m_piecesAvailable[m_MovePiece.m_Piece])
					{
						for (m_MovePiece = StrategoPiece(Bomb, m_CurrentID); !m_piecesAvailable[m_MovePiece.m_Piece]; m_MovePiece.m_Piece = StrategoPieceType(int(m_MovePiece.m_Piece) + 1) );
					}

					if ( m_piecesAvailable[m_MovePiece.m_Piece] )
					{
						_PlacePiece(m_CurrentID, m_MouseSquare, m_MovePiece.m_Piece);
						PiecePlaced(m_CurrentID, m_MouseSquare.x, m_MouseSquare.y, m_MovePiece.m_Piece);
						m_piecesAvailable[m_MovePiece.m_Piece]--;
						if (m_piecesAvailable[m_MovePiece.m_Piece] == 0)
							m_RedrawInfo.m_SetupPieces = true;
						m_SetupPiecesLeft--;
						((CWnd *)m_Button)->EnableWindow( !m_SetupPiecesLeft );
					}

				}
			}

		}
		else if ( m_BoardState == PlayingGame )
		{
WriteDebug(__FILE__,__LINE__,NULL);
			if ( s.m_Owner == m_CurrentID && m_Board.PotentialMoveExists(m_CurrentID, s, m_MouseSquare)  )
			{
				m_RedrawInfo.m_MovingPiece = true;
				m_RedrawInfo.m_HighlightPossibleMoves = true;

				m_MoveStart = ScreenToBoard(point);
				m_MoveStartSquare = m_MouseSquare;
				m_MovePiece = m_Board.m_square[ m_MouseSquare.x ][ m_MouseSquare.y ];
				m_MoveLastPos = CPoint(-1,-1);
				m_MoveHighlightSquare = CPoint(-1,-1);
				m_MovePotentialDest = CPoint(-1,-1);
				CancelAnimatingSquare();
				ClearPiece( m_MouseSquare );
			}
		}
	}
}

void CStrategoControlCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_DialogShowing)
		return;

	// TODO: Add your message handler code here and/or call default
	if (Player(m_CurrentID).m_PlayerType == Human)
	{
		// TODO: Add your message handler code here and/or call default
		if ( m_RedrawInfo.m_MovingPiece )
		{
			if ( m_BoardState == Setup )
			{
				StrategoPiece s;
				if ( m_MouseSquare.x >= 0 && m_MouseSquare.x < BOARD_COLUMNS &&
					m_MouseSquare.y >= 6 && m_MouseSquare.y < BOARD_ROWS )
				{
					s = m_Board.m_square[ m_MouseSquare.x ][ m_MouseSquare.y ];
					//StrategoPieceType tempPiece = ;
					if ( s.m_Owner == m_CurrentID )  // remove or swap from this location...
					{
						ClearPiece(m_MouseSquare);
						PieceRemoved( m_CurrentID, m_MouseSquare.x, m_MouseSquare.y, s.m_Piece ); // piece removed at m_MouseSquare
						if ( m_MoveFromSetup )
						{
							if (m_piecesAvailable[s.m_Piece] == 0)
								m_RedrawInfo.m_SetupPieces = true;
							m_piecesAvailable[s.m_Piece]++;
						}
						else
						{
							_PlacePiece(m_CurrentID, m_MoveStartSquare, s.m_Piece);
							PiecePlaced( m_CurrentID, m_MoveStartSquare.x, m_MoveStartSquare.y, s.m_Piece ); // piece placed at m_MoveStartSquare
						}
					}
					
					if ( m_MoveFromSetup )
					{
						m_SetupPiecesLeft--;
						((CWnd *)m_Button)->EnableWindow( !m_SetupPiecesLeft );
					}
					_PlacePiece(m_CurrentID, m_MouseSquare, m_MovePiece.m_Piece);
					PiecePlaced( m_CurrentID, m_MouseSquare.x, m_MouseSquare.y, m_MovePiece.m_Piece ); // piece placed at m_MouseSquare
				}
				else
				{
					if (m_piecesAvailable[m_MovePiece.m_Piece] == 0)
						m_RedrawInfo.m_SetupPieces = true;

					if ( m_MoveFromSetup )
						m_piecesAvailable[m_MovePiece.m_Piece]++;
					else
					{
						if ( ScreenToPiecePanelCoordinates( point ) )
						{
							PieceRemoved( m_CurrentID, m_MoveStartSquare.x, m_MoveStartSquare.y, m_MovePiece.m_Piece ); // piece placed at m_MoveStartSquare
							m_piecesAvailable[m_MovePiece.m_Piece]++;
							m_SetupPiecesLeft++;
							((CWnd *)m_Button)->EnableWindow( !m_SetupPiecesLeft );
						}
						else
							_PlacePiece(m_CurrentID, m_MoveStartSquare, m_MovePiece.m_Piece); // piece didn't actually go anywhere so don't notify...
					}
				}
				m_MoveFromSetup = false;
				InvalidateControl();
			}
			else if ( m_BoardState == PlayingGame )
			{
WriteDebug(__FILE__,__LINE__,NULL);
				if ( m_Board.IsMoveLegal( m_CurrentID, m_MovePiece, m_MoveStartSquare, m_MouseSquare ) )
				{
					ASSERT( m_Board.m_square[m_MouseSquare.x][m_MouseSquare.y].m_Owner != m_CurrentID );
					m_Board.RecordMove(m_CurrentID, m_MoveStartSquare, m_MouseSquare);
					if ( m_Board.m_square[m_MouseSquare.x][m_MouseSquare.y].m_Owner )
					{
WriteDebug(__FILE__,__LINE__,NULL);
						DoBattle(m_MoveStartSquare, m_MouseSquare, m_MovePiece, m_Board.m_square[m_MouseSquare.x][m_MouseSquare.y] );
					}
					else
					{
						_PlacePiece(m_CurrentID, m_MouseSquare, m_MovePiece.m_Piece);
					}
WriteDebug(__FILE__,__LINE__,NULL);
char m[256];
sprintf(m,"PieceMoved(m_CurrentID=%i, m_MoveStartSquare.x=%i, m_MoveStartSquare.y=%i, m_MouseSquare.x=%i, m_MouseSquare.y=%i, m_MovePiece.m_Piece=%i )", m_CurrentID, m_MoveStartSquare.x, m_MoveStartSquare.y, m_MouseSquare.x, m_MouseSquare.y, m_MovePiece.m_Piece);
WriteDebug(__FILE__,__LINE__,m);
					PieceMoved(m_CurrentID, m_MoveStartSquare.x, m_MoveStartSquare.y, m_MouseSquare.x, m_MouseSquare.y, m_MovePiece.m_Piece ); // let opponent know about move	
WriteDebug(__FILE__,__LINE__,NULL);
					TurnOver();
WriteDebug(__FILE__,__LINE__,NULL);
				}
				else  // return piece to original position
				{
					_PlacePiece(m_CurrentID, m_MoveStartSquare, m_MovePiece.m_Piece);
				}
				m_RedrawInfo.m_HighlightPossibleMoves = true;
			}
			m_RedrawInfo.m_MovingPiece = false;
			m_MovePotentialDest = CPoint(-1,-1);
			
		}
		
		COleControl::OnLButtonUp(nFlags, point);
	}
}

void CStrategoControlCtrl::OnTimer(UINT nIDEvent)
{
	if ( nIDEvent == ID_DO_SCROLLING_EVENT )
	{
		GetMousePos(m_Mouse);
		CalculateBoardPosition();
		CalculatePieceAnimation();

		DoScrolling();
	}
	else if ( nIDEvent == ID_TIMER_DO_EFFECTS )
	{
		m_RedrawInfo.m_DrawEffects = true;
		m_RedrawInfo.m_AnimateFrameCount++;
		InvalidateControl();
	}
	else if ( nIDEvent == ID_MOVE_PIECE_TIMER )
	{
		double fracDone = Distance(m_DragPosition - m_AutoMoveStart) / m_AutoMoveDistance;
		int pieceSpeed = getPieceSpeed(fracDone, 5, 20);
		m_DragPosition += CPoint( m_AutoMoveDelta.x * pieceSpeed, m_AutoMoveDelta.y * pieceSpeed);
		fracDone = Distance(m_DragPosition - m_AutoMoveStart) / m_AutoMoveDistance;
		if (fracDone >= 1.0)
		{
			m_RedrawInfo.m_MovingPiece = false;
			m_MovePotentialDest = CPoint(-1,-1);
			KillTimer( ID_MOVE_PIECE_TIMER );
			m_AutoMove = false;
			if ( m_Board.m_square[m_AutoMoveEndSquare.x][m_AutoMoveEndSquare.y].m_Owner )
			{
				DoBattle( m_MoveStartSquare, m_AutoMoveEndSquare, m_MovePiece, m_Board.m_square[m_AutoMoveEndSquare.x][m_AutoMoveEndSquare.y] );
			}
			else
			{
				_PlacePiece( m_MovePiece.m_Owner, m_AutoMoveEndSquare, m_MovePiece.m_Piece);
			}
			PieceMoved( m_MovePiece.m_Owner, m_MoveStartSquare.x, m_MoveStartSquare.y, m_AutoMoveEndSquare.x, m_AutoMoveEndSquare.y, m_MovePiece.m_Piece );
			TurnOver();
		}
		
		InvalidateControl();
	}
	else if ( nIDEvent == ID_DRAW_BATTLE_TIMER )
	{
		KillTimer(ID_DRAW_BATTLE_TIMER);
		m_RedrawInfo.m_ShowBattleResults = 2;
		Invalidate();
	}
	else
		COleControl::OnTimer(nIDEvent);
}

void CStrategoControlCtrl::OnSize(UINT nType, int cx, int cy)
{
	//COleControl::OnSize(nType, cx, cy);
	if (nType == SIZE_RESTORED)
	{
        m_ClientSize.cx = (cx > borderOffset * 2 ? cx - borderOffset * 2 : 0);
		m_ClientSize.cy = (cy > borderOffset * 2 ? cy - borderOffset * 2 : 0);

		if (m_GraphicsInitialized)
			CalculateDimensions();
		m_RedrawInfo.m_Sizing = true;
		RepositionControls();
		InvalidateControl();
	}
}

void CStrategoControlCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	//COleControl::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	m_RedrawInfo.m_All = true;
	InvalidateControl();
}

void CStrategoControlCtrl::OnSetFocus(CWnd* pOldWnd)
{
	COleControl::OnSetFocus(pOldWnd);
	m_RedrawInfo.m_All = true;
	InvalidateControl();
}

void CStrategoControlCtrl::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	COleControl::OnActivate(nState, pWndOther, bMinimized);
	m_RedrawInfo.m_All = true;
	InvalidateControl();
	// TODO: Add your message handler code here
}


/////////////////////////////////////////////////////////
// Class Functions
////////////////////////////////////////////////////////

void CStrategoControlCtrl::HighlightMoves(CPoint s, DirectionType direction)
{
	if (direction != All)
	{
		if (!m_Board.IsMoveLegal( m_MovePiece.m_Owner, m_MovePiece, m_MoveStartSquare, s))
			return;
		else
		{
			m_HighlightedSquares.AddHead( s );
			m_DrawingDC_List.AddHead( DrawPiece(&m_ptrCanvas->m_frontDC, s, 0, 2 ) ); // highlight this square
		}
	}
	

	if (direction == All || direction == Up)
		HighlightMoves(s + CPoint(0,1), Up);
	if (direction == All || direction == Down)
		HighlightMoves(s + CPoint(0,-1), Down);
	if (direction == All || direction == Left)
		HighlightMoves(s + CPoint(-1,0), Left);
	if (direction == All || direction == Right)
		HighlightMoves(s + CPoint(1,0), Right);
}
SHORT CStrategoControlCtrl::GetBoardState(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_BoardState;
}

void CStrategoControlCtrl::SetBoardState(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if (newVal >= Unintialized && newVal <= Finished)
	{
		//char message [128];
		//wsprintf(message,"state changed to %i", nNewValue);
		//MessageBox(message,"message",MB_OK);

		// Unintialized = 0, Setup, Waiting, PlayingGame, Finished

		
		if ( newVal == Setup )
		{
			//CBackDlg MyDlg;
			//MyDlg.DoModal();
			//CPoint textCenter = BoardToScreen(CPoint(SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP - 1) + CPoint(m_piecesPanelSize.cx / 2, m_piecesPanelSize.cy / 4));
			//CSize textSize(m_piecesPanelSize.cx / 4, m_piecesPanelSize.cy / 4 - 2);
			//CRect textPos( textCenter.x - textSize.cx -2, textCenter.y - textSize.cy - 1, textCenter.x + textSize.cx, textCenter.y + textSize.cy );

			//m_TextArea = new CEdit();
			//m_TextArea->Create( WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_BORDER|ES_CENTER|ES_READONLY, textPos, this,ID_TEXT_AREA);
			//m_TextArea->SetWindowText("\r\n\r\nPress OK when you have placed all your pieces");
			
			m_ptrCanvas = &m_SetupCanvas;
			m_Board.RedrawAllPieces();
			m_RedrawInfo.m_SetupPieces = true;
			m_BoardState = BoardStateType(newVal);//make sure state is set before calling placepieces
			if (m_PlaceUnitsAtStart)
				PlaceAllRemainingPieces();

			CPoint buttonCenter =  BoardToScreen(CPoint(SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP + 30) + CPoint(m_piecesPanelSize.cx / 2, m_piecesPanelSize.cy / 4));
			CSize buttonSize(120, 30);
			CRect buttonPos( buttonCenter.x - buttonSize.cx / 2, buttonCenter.y - buttonSize.cy / 2, buttonCenter.x + buttonSize.cx / 2, buttonCenter.y + buttonSize.cy / 2);
			
			m_Button->MoveWindow(buttonPos);
			m_Button->ShowWindow(SW_SHOW);
			m_AllowScrolling = TRUE;
		}
		else if (newVal == PlayingGame)
		{
			m_BoardState = BoardStateType(newVal);
			m_MoveFromSetup = false;
			m_ptrCanvas = &m_BoardCanvas;
			m_Board.RedrawAllPieces();
		}
		else
		{
			m_BoardState = BoardStateType(newVal);
		}
		//if ( m_BoardState 

		m_RedrawInfo.m_All = true;
		CalculateDimensions();
		InvalidateControl();
		SetModifiedFlag();
	}
}

void CStrategoControlCtrl::DoInitialization(CDC *pSrcDC, const CRect &rcBounds)
{
	//mySmallFont.CreateFont(17,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,0,0,PROOF_QUALITY ,0,"Arial");
	//myLargeFont.CreateFont(18,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,0,0,PROOF_QUALITY ,0,"Arial");
	
	if (m_imagesLoaded)
	{
		// load main board and setup images
		m_BoardCanvas.CreateDCS( pSrcDC );
		m_SetupCanvas.CreateDCS( pSrcDC );
		m_DialogCanvas.CreateDCS( pSrcDC );

		m_piecesPanelSize = piecesPanel.GetImageSize();
		m_SquareSize = CSize((m_BoardCanvas.m_image_size.cx - BOARD_BORDER_LEFT * 2) / BOARD_COLUMNS, (m_BoardCanvas.m_image_size.cy - BOARD_BORDER_TOP * 2) / BOARD_ROWS);

		piecesPanel_dc.CreateCompatibleDC( pSrcDC );
		piecesPanel.SelectPicture( &piecesPanel_dc );
		piecesPanelPieces_dc.CreateCompatibleDC( pSrcDC );
		piecesPanelBitmap.CreateCompatibleBitmap( pSrcDC, m_piecesPanelSize.cx, m_piecesPanelSize.cy );
		piecesPanelPieces_dc.SelectObject(piecesPanelBitmap);
		piecesPanelPieces_dc.BitBlt(0,0,m_piecesPanelSize.cx, m_piecesPanelSize.cy, &piecesPanel_dc, 0, 0, SRCCOPY);		

		// load piece images
		unknownPiece_dc[Blue].CreateCompatibleDC( pSrcDC );
		unknownPiece[Blue].SelectPicture( &unknownPiece_dc[Blue] );
		unknownPiece_dc[Red].CreateCompatibleDC( pSrcDC );
		unknownPiece[Red].SelectPicture( &unknownPiece_dc[Red] );
		for (int c = 0; c < NUM_COLORS; c++)
		{
			for (int p = 0; p < NUM_PIECES; p++)
			{
				piece_dc[c][p].CreateCompatibleDC( pSrcDC );
				pieces[c][p].SelectPicture( &piece_dc[c][p] );
			}
		}		
		TempDC.CreateCompatibleDC( pSrcDC );

		// initialize metric variables
		m_ClientSize.cx = rcBounds.Width() - borderOffset * 2;
		m_ClientSize.cy = rcBounds.Height() - borderOffset * 2;
		m_BoardPosition = CPoint(0,0);
		
		m_SetupCanvas.m_board_top_left_corner = CPoint(SETUP_BORDER_LEFT,SETUP_BORDER_TOP);
		m_BoardCanvas.m_board_top_left_corner = CPoint(BOARD_BORDER_LEFT,BOARD_BORDER_TOP);

		m_ptrCanvas = &m_SetupCanvas;//m_BoardCanvas;
		CalculateDimensions();
		srand(time(0));
		//SetTimer(ID_TIMER_DO_EFFECTS,40,NULL);	    
		m_Button = new CButton();
		m_Button->Create("OK",WS_CHILD|BS_PUSHBUTTON|WS_DISABLED,CRect(0,0,0,0), this, IDC_OK_PRESSED);//WS_VISIBLE
		m_GraphicsInitialized = true;
	}
}


void CStrategoControlCtrl::DoScrolling()
{
	if (!m_AllowScrolling)
		return;

	BOOL needRedraw = FALSE;
    CSize scrollingWindowSize = m_BoardClientSize;

	if (m_ScrollOutOfWindow == false && (m_Mouse.x < 0 || m_Mouse.y < 0 || m_Mouse.x > scrollingWindowSize.cx || m_Mouse.y > scrollingWindowSize.cy))
	{
		m_ScrollingTimerEnabled = FALSE;
		KillTimer(ID_DO_SCROLLING_EVENT);
		return;
	}

    if ( m_Mouse.x < BorderScrollArea )
	{
        if ( m_BoardPosition.x > 0 )
		{
            m_BoardPosition.x -= GetScrollAmount(BorderScrollArea - m_Mouse.x);
			if ( m_BoardPosition.x < 0 )
				m_BoardPosition.x = 0;
            needRedraw = TRUE;
		}
    }
    else if ( m_Mouse.x > scrollingWindowSize.cx - BorderScrollArea )
	{
        if ( m_BoardPosition.x < m_ptrCanvas->m_image_size.cx - scrollingWindowSize.cx )
		{
            m_BoardPosition.x += GetScrollAmount(m_Mouse.x - (scrollingWindowSize.cx - BorderScrollArea));
            if (m_BoardPosition.x > m_ptrCanvas->m_image_size.cx - scrollingWindowSize.cx)
				m_BoardPosition.x = m_ptrCanvas->m_image_size.cx - scrollingWindowSize.cx;
			needRedraw = TRUE;
		}
	}
 
    if ( m_Mouse.y < BorderScrollArea )
	{
        if ( m_BoardPosition.y > 0 )
		{
            m_BoardPosition.y -= GetScrollAmount(BorderScrollArea - m_Mouse.y);
			if (m_BoardPosition.y < 0)
				m_BoardPosition.y = 0;
            needRedraw = TRUE;
        }
    }
	else if ( m_Mouse.y > scrollingWindowSize.cy - BorderScrollArea )
	{
        if ( m_BoardPosition.y < m_ptrCanvas->m_image_size.cy - scrollingWindowSize.cy )
		{
            m_BoardPosition.y += GetScrollAmount(m_Mouse.y - (scrollingWindowSize.cy - BorderScrollArea));
			if (m_BoardPosition.y > m_ptrCanvas->m_image_size.cy - scrollingWindowSize.cy)
				m_BoardPosition.y = m_ptrCanvas->m_image_size.cy - scrollingWindowSize.cy;
            needRedraw = TRUE;
        }
    }

    if ( needRedraw )
	{
        if ( m_ScrollingTimerEnabled == FALSE )
		{
            m_ScrollingTimerEnabled = TRUE;
			SetTimer(ID_DO_SCROLLING_EVENT,40,NULL);
            
		}
		m_RedrawInfo.m_Scrolling = true;
        InvalidateControl();//Invalidate(FALSE);
	}
    else
	{
        m_ScrollingTimerEnabled = FALSE;
		KillTimer(ID_DO_SCROLLING_EVENT);
	}

	RepositionControls();
}

int CStrategoControlCtrl::GetScrollAmount(int position)
{
	if (position < 0)
		position = 0;
	if (position > BorderScrollArea)
		position = BorderScrollArea;
	return position * (maxScrollAmount - minScrollAmount) / BorderScrollArea + minScrollAmount;
}

void CStrategoControlCtrl::GetMousePos(CPoint & point)
{
    //POINT pos;
    GetCursorPos(&point);
    ScreenToClient(&point);

    //x = pos.x;
    //y = pos.y;
}


void CStrategoControlCtrl::CalculateDimensions()
{
WriteDebug(__FILE__,__LINE__,NULL);
	// m_ptrCanvas->m_image_size stays constant
	m_BoardClientSize = m_ClientSize; // m_clientsize is the size of the entire drawing area (minus the area used by the raised edge)

	if ( ShowPiecesPanel() )
	{
		m_BoardClientSize.cy -= (m_piecesPanelSize.cy + panelBorderWidth);
		
		if (m_BoardClientSize.cy < 0)
			m_BoardClientSize.cy = 0;
	}

	m_imageSize = m_BoardClientSize;

	CSize BoardDiff(m_ptrCanvas->m_image_size.cx - m_BoardClientSize.cx, m_ptrCanvas->m_image_size.cy - m_BoardClientSize.cy);
		
	if (m_BoardPosition.x  > BoardDiff.cx ||  m_BoardPosition.x < 0)
		m_BoardPosition.x = BoardDiff.cx / 2 - borderOffset;//(BoardDiff.cx >= 0 ? BoardDiff.cx : 0);
		
	if (m_BoardPosition.y > BoardDiff.cy || m_BoardPosition.y < 0)
		m_BoardPosition.y = BoardDiff.cy / 2 - borderOffset;//(BoardDiff.cy >= 0 ? BoardDiff.cy : 0);

    m_imageOffset = CPoint(borderOffset,borderOffset); 
	// borderOffset = border due to raised edge (value is 2)
	// imageOffset can move beyond that point if the client area is larger than the board

	if (m_BoardClientSize.cx > m_ptrCanvas->m_image_size.cx){
		m_imageOffset.x = borderOffset + (m_BoardClientSize.cx - m_ptrCanvas->m_image_size.cx) / 2;
        m_imageSize.cx = m_ptrCanvas->m_image_size.cx - 2;
	}

	if (m_BoardClientSize.cy > m_ptrCanvas->m_image_size.cy){
		m_imageOffset.y = borderOffset + (m_BoardClientSize.cy - m_ptrCanvas->m_image_size.cy) / 2;
        m_imageSize.cy = m_ptrCanvas->m_image_size.cy - 2;
	}

	m_piecesPanelOffset = CPoint(borderOffset, m_BoardClientSize.cy + borderOffset + panelBorderWidth);
	if (m_ClientSize.cx > m_piecesPanelSize.cx){
		m_piecesPanelOffset.x = borderOffset + (m_ClientSize.cx - m_piecesPanelSize.cx) / 2;
	}
	
}

CRect CStrategoControlCtrl::GetAbsolutePieceCoordinates(CPoint square)
{
	CRect SquareBoundaries = GetAbsoluteCoordinates(square);
	int left = (SquareBoundaries.left + SquareBoundaries.right - PIECE_WIDTH) / 2;
	int top = (SquareBoundaries.top + SquareBoundaries.bottom - PIECE_HEIGHT) / 2;
	return CRect(left, top, left + PIECE_WIDTH, top + PIECE_HEIGHT);

}

CRect CStrategoControlCtrl::GetScreenCoordinates(CPoint square)
{
	return GetAbsoluteCoordinates(square) - m_BoardPosition;
	
}

CRect CStrategoControlCtrl::GetAbsoluteCoordinates(CPoint square)
{
	int ySquare = square.y - (m_BoardState == Setup ? 6 : 0);
	
	return CRect(square.x * m_SquareSize.cx,
		          ySquare * m_SquareSize.cy,
				 (square.x + 1) * m_SquareSize.cx - 1,
		         (ySquare + 1) * m_SquareSize.cy - 1) + m_ptrCanvas->m_board_top_left_corner;
}

CPoint CStrategoControlCtrl::GetSquareCenter(CPoint square)
{
	int ySquare = square.y - (m_BoardState == Setup ? 6 : 0);
	
	return CPoint( (square.x * m_SquareSize.cx + (square.x + 1) * m_SquareSize.cx - 1 ) / 2,
		           (ySquare  * m_SquareSize.cy + (ySquare + 1)  * m_SquareSize.cy - 1 ) / 2) + m_ptrCanvas->m_board_top_left_corner;
}

void CStrategoControlCtrl::CalculateBoardPosition()
{
	CPoint boardPoint = ScreenToBoard( m_Mouse );

	m_MouseSquare.x = int(floor(double(boardPoint.x) / double(m_SquareSize.cx)));
	m_MouseSquare.y = int(floor(double(boardPoint.y) / double(m_SquareSize.cy)));

	if (m_BoardState == Setup)
		m_MouseSquare.y += 6;
}

void CStrategoControlCtrl::CancelAnimatingSquare()
{
	if (m_RedrawInfo.m_AnimatingSquare != CPoint(-1, -1))
	{
		m_RedrawInfo.m_AnimatingSquare = CPoint(-1, -1); // if we are animating a square, stop it...
		m_RedrawInfo.m_DrawEffects = true;
		//KillTimer(ID_TIMER_DO_EFFECTS);
		InvalidateControl();
	}
}

void CStrategoControlCtrl::SetAnimatingSquare( CPoint square )
{
	m_RedrawInfo.m_AnimatingSquare = square;
	m_RedrawInfo.m_DrawEffects = true;
	//m_RedrawInfo.m_AnimateFrameCount = 0;
	//SetTimer(ID_TIMER_DO_EFFECTS,40,NULL);
	InvalidateControl();
}

void CStrategoControlCtrl::CalculatePieceAnimation()
{
	// this function is called as the mouse moves to determine if a piece needs to be visually identified
	// to the user as the mouse moves over that piece

	if ( m_MouseSquare != m_RedrawInfo.m_AnimatingSquare )//&& m_RedrawInfo.m_LastSquareAnimated == CPoint(-1, -1))
	{
WriteDebug(__FILE__,__LINE__,NULL);
		CancelAnimatingSquare();

		if (m_MouseSquare.x >= 0 && m_MouseSquare.y >= 0 &&
			m_MouseSquare.x < BOARD_COLUMNS && m_MouseSquare.y < BOARD_ROWS &&
			!m_RedrawInfo.m_MovingPiece )
		{
			
			StrategoPiece s = m_Board.m_square[ m_MouseSquare.x ][ m_MouseSquare.y ];
			if ( s.m_Owner == m_CurrentID && m_Board.PotentialMoveExists(m_CurrentID, s, m_MouseSquare)  )
				SetAnimatingSquare( m_MouseSquare );
		}
	}
}

//void CStrategoControlCtrl::CopyPiece(CBitmap *pSrcBMP, CDC *pDestDC, const CRect &coords, int xSrc, int ySrc)

void CStrategoControlCtrl::CopyPiece(StrategoPiece s, CDC *pDestDC, const CRect &coords, int xSrc, int ySrc)
{
WriteDebug(__FILE__,__LINE__,NULL);
	if ( Player(s.m_Owner).m_PlayerType == Other && m_HideEnemyPieces) // if this piece is not owned by a human player...
		CopyPiece(&unknownPiece_dc[GetPlayerColor(s.m_Owner)], pDestDC, coords, xSrc, ySrc );
	else
		CopyPiece(&piece_dc[GetPlayerColor(s.m_Owner)][s.m_Piece], pDestDC, coords, xSrc, ySrc );

	
}

void CStrategoControlCtrl::CopyPiece(CDC * pieceDC, CDC *pDestDC, const CRect &coords, int xSrc, int ySrc)
{
	pDestDC->SetBkMode(TRANSPARENT);
				
	CGdiObject * oldObject = TempDC.SelectObject(&m_MaskBMP);
	pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), &TempDC, xSrc, ySrc, SRCPAINT);
	TempDC.SelectObject(oldObject);
			
	//oldObject = TempDC.SelectObject(pSrcBMP);
	//OLE_HANDLE pBMPout;
	//HDC oldHDC;
	//oldObject = TempDC.GetCurrentBitmap();
	//pieces[color][piece].SelectPicture( &TempDC, &oldHDC, &pBMPout );
	//pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), &TempDC, xSrc, ySrc, SRCAND);
	//TempDC.SelectObject( pBMPout );
	//SelectObject(
	//	TempDC.m_hDC,          // handle to DC
	//	HGDIOBJ(pBMPout)   // handle to object
	//);
	//TempDC.SelectObject(oldObject);
	//SelectObject( oldHDC, oldObject );//pBMPout
	pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), pieceDC, xSrc, ySrc, SRCAND );// );//);
	//NOTSRCCOPY
}

void CStrategoControlCtrl::AnimatePiece(StrategoPiece s, CDC *pDestDC, const CRect &coords, int xSrc, int ySrc)
{
	AnimatePiece(&piece_dc[GetPlayerColor(s.m_Owner)][s.m_Piece], pDestDC, coords, xSrc, ySrc );
}

void CStrategoControlCtrl::AnimatePiece(CDC * pieceDC, CDC *pDestDC, const CRect &coords, int xSrc, int ySrc)
{
	pDestDC->SetBkMode(TRANSPARENT);
				
	CGdiObject * oldObject = TempDC.SelectObject(&m_MaskBMP);
	pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), &TempDC, xSrc, ySrc, SRCINVERT);////SRCPAINT);
	TempDC.SelectObject(oldObject);
			
	pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), NULL, xSrc, ySrc, DSTINVERT );
	pDestDC->BitBlt(coords.left, coords.top, coords.Width(), coords.Height(), pieceDC, xSrc, ySrc, SRCINVERT );
	//SRCINVERT
}

BOOL CStrategoControlCtrl::ClearPiece(CPoint pos) 
{
WriteDebug(__FILE__,__LINE__,NULL);
	// TODO: Add your dispatch handler code here
	m_Board.ClearPiece( pos );
	m_RedrawInfo.mPlacePiece = true;
	InvalidateControl();
	return TRUE;
}

CRect CStrategoControlCtrl::DrawPiece(CDC *pDC, CPoint location, int animate, int background)
{
	//if (!m_Board.m_square[location.x][location.y].m_Owner)
	//{
		//ASSERT(0);
		//return CRect(0,0,0,0);
	//}

	CRect coords = GetAbsolutePieceCoordinates(location);
	CRect affectedArea = coords;

	if (background)
	{
		CRect activeSquare = GetAbsoluteCoordinates( location );
		CDC * ptrBackDC = &m_ptrCanvas->m_backDC;

		if (background == 2 && m_ptrCanvas->m_image_highlight.m_imageLoaded )
		{
			ptrBackDC = &m_ptrCanvas->m_backHighlightDC;
		}
		else if (background == 3 && m_ptrCanvas->m_image_outline.m_imageLoaded )
		{
			ptrBackDC = &m_ptrCanvas->m_backOutlineDC;
		}
		
		pDC->BitBlt( activeSquare.left, 
			             activeSquare.top, 
						 activeSquare.Width(), 
						 activeSquare.Height(), 
						 ptrBackDC, 
						 activeSquare.left, 
						 activeSquare.top, 
						 SRCCOPY);	
		affectedArea.UnionRect( affectedArea, activeSquare );
	}
	
	// clean up piece above
	if ( location.y > 0 && background )
	{
		if (m_Board.m_square[location.x][location.y - 1].m_Owner)
		{
			CRect upperCoords = GetAbsolutePieceCoordinates( CPoint(location.x, location.y - 1) );
			CRect intersect;
			
			if ( intersect.IntersectRect( coords, upperCoords ))
			{
				affectedArea.UnionRect( affectedArea, intersect );
				CopyPiece(m_Board.m_square[location.x][location.y - 1], pDC, intersect, 0, intersect.top - upperCoords.top);
			}
			else
			{
				MessageBox("Error: rectangles should intersect!","Error",MB_ICONSTOP);
				exit(0);
			}
		}
	}

	if ( m_Board.m_square[location.x][location.y].m_Owner )
	{
		if (animate)
		{
			if ( m_RedrawInfo.m_AnimateFrameCount % 2 == 0 )
				AnimatePiece( m_Board.m_square[location.x][location.y], pDC, coords);
			else if ( m_RedrawInfo.m_AnimateFrameCount % 2 == 1 )
				CopyPiece( m_Board.m_square[location.x][location.y], pDC, coords);
			else if ( m_RedrawInfo.m_AnimateFrameCount % 3 == 2 )
				CopyPiece( m_Board.m_square[location.x][location.y], pDC, coords);
		}
		else
		{
			CopyPiece( m_Board.m_square[location.x][location.y], pDC, coords);
		}
	}

	// clean up piece below
	if ( location.y < (BOARD_ROWS - 1) )
	{
		if (m_Board.m_square[location.x][location.y + 1].m_Owner)
		{
			CRect lowerCoords = GetAbsolutePieceCoordinates( CPoint(location.x, location.y + 1) );
			CRect intersect;
			
			if ( intersect.IntersectRect( coords, lowerCoords ))
			{
				affectedArea.UnionRect( affectedArea, intersect );
				CopyPiece( m_Board.m_square[location.x][location.y + 1], pDC, intersect);
			}
			else
			{
				MessageBox("Error: rectangles should intersect!","Error",MB_ICONSTOP);
				exit(0);
			}
		}
	}

	
	return affectedArea;
}

CRect CStrategoControlCtrl::DrawSetupPiece(CDC *pDC, StrategoPiece piece, int count)
{
	CPoint pieceCenter = PiecePanelGetPieceLocation( piece.m_Piece ) + m_ptrCanvas->m_board_top_left_corner + CPoint(SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP);
	CPoint pieceTopLeft = pieceCenter - CPoint(PIECE_WIDTH / 2, PIECE_HEIGHT / 2);
	CRect pieceRect( pieceTopLeft.x, pieceTopLeft.y, pieceTopLeft.x + PIECE_WIDTH, pieceTopLeft.y + PIECE_HEIGHT );

	if ( count )
		CopyPiece( piece, pDC, pieceRect);
	else
		pDC->BitBlt(pieceRect.left,pieceRect.top,pieceRect.Width(),pieceRect.Height(),&m_ptrCanvas->m_backDC,pieceRect.left,pieceRect.top,SRCCOPY);

	return pieceRect;
}


CRect CStrategoControlCtrl::UndrawPiece(CDC *pDC, CPoint location)
{
	CRect coords = GetAbsolutePieceCoordinates(location);
	CRect affectedArea = coords;

	pDC->BitBlt(coords.left,coords.top,coords.Width(),coords.Height(),&m_ptrCanvas->m_backDC,coords.left,coords.top,SRCCOPY);

	// clean up piece below
	if ( location.y < (BOARD_ROWS - 1) )
	{
		if (m_Board.m_square[location.x][location.y + 1].m_Owner)
		{
			CRect lowerCoords = GetAbsolutePieceCoordinates( CPoint(location.x, location.y + 1) );
			CRect intersect;
			
			if ( intersect.IntersectRect( coords, lowerCoords ))
			{
				affectedArea.UnionRect( affectedArea, intersect );
				CopyPiece(m_Board.m_square[location.x][location.y + 1], pDC, intersect);
			}
			else
			{
				MessageBox("Error: rectangles should intersect!","Error",MB_ICONSTOP);
				exit(0);
			}
		}
	}
	// clean up piece above
	if ( location.y > 0 )
	{
		if (m_Board.m_square[location.x][location.y - 1].m_Owner)
		{
			CRect upperCoords = GetAbsolutePieceCoordinates( CPoint(location.x, location.y - 1) );
			CRect intersect;
			
			if ( intersect.IntersectRect( coords, upperCoords ))
			{
				affectedArea.UnionRect( affectedArea, intersect );
				CopyPiece(m_Board.m_square[location.x][location.y - 1], pDC, intersect, 0, intersect.top - upperCoords.top);
			}
			else
			{
				MessageBox("Error: rectangles should intersect!","Error",MB_ICONSTOP);
				exit(0);
			}
		}
	}
	return affectedArea;
}





const char * CStrategoControlCtrl::getPieceFileName(StrategoPieceType piece, StrategoColor color)
{
	if ( color == Red )
	{
		switch (piece)
		{
			case Bomb:    return "redbomb.jpg";
			case Marshal: return "red1.jpg";
			case General: return "red2.jpg";
			case Colonel: return "red3.jpg";
			case Major:   return "red4.jpg";
			case Captain: return "red5.jpg";
			case Lieutenant: return "red6.jpg";
			case Sergeant: return "red7.jpg";
			case Miner:   return "red8.jpg";
			case Scout:   return "red9.jpg";
			case Spy:     return "redspy.jpg";
			case Flag:    return "redflag.jpg";
		}
	}
	else
	{
		switch (piece)
		{
			case Bomb:    return "bluebomb.jpg";
			case Marshal: return "blue1.jpg";
			case General: return "blue2.jpg";
			case Colonel: return "blue3.jpg";
			case Major:   return "blue4.jpg";
			case Captain: return "blue5.jpg";
			case Lieutenant: return "blue6.jpg";
			case Sergeant: return "blue7.jpg";
			case Miner:   return "blue8.jpg";
			case Scout:   return "blue9.jpg";
			case Spy:     return "bluespy.jpg";
			case Flag:    return "blueflag.jpg";
		}
	}
	return "error";
}

StrategoColor CStrategoControlCtrl::GetPlayerColor(int playerID)
{
	return Player(playerID).m_Color;
}

CPoint CStrategoControlCtrl::ScreenToBoard(CPoint clientPoint)
{
	return CPoint (clientPoint.x + m_BoardPosition.x - borderOffset - m_ptrCanvas->m_board_top_left_corner.x, clientPoint.y + m_BoardPosition.y - borderOffset - m_ptrCanvas->m_board_top_left_corner.y );
}

CPoint CStrategoControlCtrl::BoardToScreen(CPoint boardPoint)
{
	return CPoint (boardPoint.x - m_BoardPosition.x + borderOffset + m_ptrCanvas->m_board_top_left_corner.x, boardPoint.y - m_BoardPosition.y + borderOffset + m_ptrCanvas->m_board_top_left_corner.y);
}

bool CStrategoControlCtrl::LoadPicture(CPicture &picture, const char *filename)
{
	char directory[255];
	GetCurrentDirectory( 255, directory );

	if (picture.Load(filename) == 0)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		if (m_missingImage)
			delete [] m_missingImage;
		m_missingImage = new char[strlen(directory) + strlen(filename) + 2];
		strcpy(m_missingImage, directory);
		strcat(m_missingImage, "\\");
		strcat(m_missingImage, filename);
		return false;
	}
	return true;
}
/*
void CStrategoControlCtrl::SetColor(short PlayerID, short nNewValue) 
{
	// TODO: Add your property handler here
	if ( m_BoardState != Unintialized )
	{
		char message[128];
		wsprintf(message,"Critical Error, SetMyColor called when m_BoardState != Unitialized, state = %i", m_BoardState );
		MessageBox(message,"ERROR",MB_ICONSTOP);
	}
	else
	{
	
		if ( nNewValue == Red || nNewValue == Blue )
		{
			Player( PlayerID ).m_Color = nNewValue;
			SetModifiedFlag();
		}
	}
}
*/
const int piecesPanelWidth = 8;
const int piecesPanelHeight = 2;
StrategoPieceType piecesPanelPieces[piecesPanelHeight][piecesPanelWidth] = {{Flag,  Marshal, NoPiece,    NoPiece,  NoPiece, NoPiece, General, Colonel},
/*                                                              */ {Major, Captain, Lieutenant, Sergeant, Miner,   Scout,   Spy,     Bomb}};

bool CStrategoControlCtrl::ScreenToPiecePanelCoordinates( CPoint &p ) // takes client coordinates
{
	p = ScreenToBoard( p );
	p -= CPoint( SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP );
	return p.x >= 0 && p.x <= m_piecesPanelSize.cx && p.y >= 0 && p.y <= m_piecesPanelSize.cy;
}

StrategoPieceType CStrategoControlCtrl::PiecePanelGetStrategoPiece(CPoint p)
{
	int x = p.x * piecesPanelWidth / m_piecesPanelSize.cx;
	int y = p.y * piecesPanelHeight / m_piecesPanelSize.cy;
	ASSERT( x >= 0 && x < piecesPanelWidth);
	ASSERT( y >= 0 && y < piecesPanelHeight);
	return piecesPanelPieces[y][x];
}

CPoint CStrategoControlCtrl::PiecePanelGetPieceLocation(StrategoPieceType piece)
{
	for (int r = 0; r < piecesPanelHeight; r++)
	{
		for (int c = 0; c < piecesPanelWidth; c++)
		{
			if (piecesPanelPieces[r][c] == piece)
			{
				return CPoint( (0.5 + double(c)) * double(m_piecesPanelSize.cx) / double(piecesPanelWidth),
					           (0.5 + double(r)) * double(m_piecesPanelSize.cy) / double(piecesPanelHeight) );
			}
		}
	}
	return CPoint(-1,-1);
}

bool CStrategoControlCtrl::ShowPiecesPanel()
{
	return m_BoardState != Unintialized && m_BoardState != Setup && m_showPiecesPanel;
}


void CStrategoControlCtrl::OnOK()
{
	if (m_BoardState == Setup)
	{
		((CWnd *)m_Button)->ShowWindow(SW_HIDE);
		SetBoardState( Waiting ); // game will notify us when it is time to make a move...
		SetupDone();
	}
	else
	{
		m_AllowScrolling = TRUE;
		m_RedrawInfo.m_ShowBattleResults = 0;
		m_Button->ShowWindow(SW_HIDE);
		m_DialogShowing = false;
		if (m_lastAutoMove.execute)
		{
			m_lastAutoMove.execute = false;
			if (m_last_battle_outcome != WinGame)
				MovePiece( m_lastAutoMove.from.x, m_lastAutoMove.from.y, m_lastAutoMove.to.x, m_lastAutoMove.to.y );
		}
		if (m_last_battle_outcome == WinGame)
		{
			SetShowAllPieces( TRUE );
			GameOver( m_MovePiece.m_Owner, FlagCaptured );
		}
		Invalidate();
	}
}

int CStrategoControlCtrl::GetSetupPiecesRemaining()
{
	return m_SetupPiecesLeft;	
}

void CStrategoControlCtrl::RepositionControls()
{
WriteDebug(__FILE__,__LINE__,NULL);
	if (m_Button && (m_BoardState == Setup || m_DialogShowing))
	{
		CPoint buttonCenter;
		CSize buttonSize(120, 30);
		if (m_BoardState == Setup)
		{
			buttonCenter = BoardToScreen(CPoint(SETUP_PIECE_PANEL_LEFT, SETUP_PIECE_PANEL_TOP + 30) + CPoint(m_piecesPanelSize.cx / 2, m_piecesPanelSize.cy / 4));
		}
		else if (m_DialogShowing)
		{
			CSize battleSize = m_BattleMBMP->GetDimensions();
			CRect rcBounds;
			GetClientRect(&rcBounds);
			CPoint drawPoint = rcBounds.CenterPoint() - CSize(battleSize.cx / 2, battleSize.cy / 2);
			buttonCenter = drawPoint + CSize(battleSize.cx / 2, battleSize.cy - 30);
		}
		CRect buttonPos( buttonCenter.x - buttonSize.cx / 2, buttonCenter.y - buttonSize.cy / 2, buttonCenter.x + buttonSize.cx / 2, buttonCenter.y + buttonSize.cy / 2);
		m_Button->MoveWindow( &buttonPos, TRUE );
	}
}

int CStrategoControlCtrl::getPieceSpeed(double fracDone, int minSpeed, int maxSpeed)
{
	return maxSpeed - ( .5 - fracDone ) * ( .5 - fracDone ) * 4 * ( maxSpeed - minSpeed );
}

double CStrategoControlCtrl::Distance(CPoint p)
{
	return sqrt(p.x * p.x + p.y * p.y);
}



void CStrategoControlCtrl::DoBattle(CPoint p1, CPoint p2, StrategoPiece attacker, StrategoPiece defender )
{
WriteDebug(__FILE__,__LINE__,NULL);
	m_last_battle_outcome = m_Board.Battle( attacker.m_Piece, defender.m_Piece );
	if ( m_last_battle_outcome == Win || m_last_battle_outcome == WinGame)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		ClearPiece(p2);
		_PlacePiece(attacker.m_Owner, p2, attacker.m_Piece );
	}
	else if ( m_last_battle_outcome == Lose )
	{
WriteDebug(__FILE__,__LINE__,NULL);

		// don't place current piece...  it just dissappears
	}
	else if ( m_last_battle_outcome == Tie )
	{
WriteDebug(__FILE__,__LINE__,NULL);
		ClearPiece(p2);
	}
	
	/*
	BattleOccured(p1.x, 
		          p1.y, 
				  p2.x, 
				  p2.y, 
				  attacker.m_Piece, 
				  defender.m_Piece, 
				  (m_last_battle_outcome == Win || m_last_battle_outcome == WinGame ?  TRUE : FALSE),
				  (m_last_battle_outcome != WinGame ?  TRUE : FALSE));
	*/
	BattleOccured(attacker.m_Piece, defender.m_Piece, m_last_battle_outcome);
	ShowBattleResults( attacker, defender, m_last_battle_outcome, false, false );

	if ( m_last_battle_outcome == WinGame )
	{
		// need to fire event...
		SetBoardState( Finished );
	}
}

void CStrategoControlCtrl::ShowBattleResults(StrategoPiece attackPiece, StrategoPiece defendPiece, BattleResolutionType outcome, bool HideAttack, bool HideDefend)
{
WriteDebug(__FILE__,__LINE__,NULL);
	CString text;
	COLORREF textColor;
	StrategoColor winColor;
	char redString[] = "Red";
	char blueString[] = "Blue";
	char * attackText;
	char * defendText;

	StrategoColor attackColor = Player(attackPiece.m_Owner).m_Color;
	StrategoColor defendColor = Player(defendPiece.m_Owner).m_Color;

	attackText = (attackColor == Red ? redString : blueString);
	defendText = (defendColor == Red ? redString : blueString);

	if (outcome == Win || outcome == WinGame)
		winColor = attackColor;
	else if (outcome == Lose)
		winColor = defendColor;
	
	if (outcome == Tie)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		textColor = 0;
		text.Format("Tie!");
	}
	else 
	{
WriteDebug(__FILE__,__LINE__,NULL);
		textColor = (winColor == Red ? RGB(225,0,0) : RGB(0,0,225));
		if (outcome == WinGame)
			text.Format("%s Wins the Game!", winColor == Red ? "Red" : "Blue");
		else
			text.Format("%s Wins!", winColor == Red ? "Red" : "Blue");
	}
	CRect attackRect( CPoint(m_DialogCanvas.m_image_size.cx * 1 / 4 - PIECE_WIDTH / 2, 130), CSize(PIECE_WIDTH, PIECE_HEIGHT) );
	CRect defendRect( CPoint(m_DialogCanvas.m_image_size.cx * 3 / 4 - PIECE_WIDTH / 2, 130), CSize(PIECE_WIDTH, PIECE_HEIGHT) );

	// start drawing!

	m_DialogCanvas.WipeImageDCs();

	CFont * oldFont;
	CFont LargeBoldFont;
	CFont LargeFont;
	CFont SmallFont;
	CFont * ptrFont;

	LargeBoldFont.CreateFont( 36, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial" );
	LargeFont.CreateFont(  32, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial" );
	SmallFont.CreateFont(  24, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial" );

	oldFont = (CFont *) m_DialogCanvas.m_frontDC.SelectObject( &LargeBoldFont );
	CSize stringSize;
	CPoint textPoint;
	stringSize = m_DialogCanvas.m_frontDC.GetTextExtent(text);
	int y = m_DialogCanvas.m_image_size.cy - (stringSize.cy + 45 + 15);
	textPoint = CPoint( (m_DialogCanvas.m_image_size.cx - stringSize.cx) / 2,  y);
	m_DialogCanvas.m_frontDC.SetTextColor(textColor);
	m_DialogCanvas.m_frontDC.TextOut(textPoint.x, textPoint.y, text);
	
	oldFont = (CFont *) m_DialogCanvas.m_frontDC.SelectObject( &LargeFont );
	text.Format("%s %s%sAttacks %s%s%s!",
		        attackText,
				(HideAttack ? "" : StrategoPieceNames[attackPiece.m_Piece]),
				(HideAttack ? "" : " "),
				defendText,
				(HideDefend ? "" : " "),
				(HideDefend ? "" : StrategoPieceNames[defendPiece.m_Piece]));

	stringSize = m_DialogCanvas.m_frontDC.GetTextExtent(text);
	if (stringSize.cx > m_DialogCanvas.m_image_size.cx - 40)
	{
WriteDebug(__FILE__,__LINE__,NULL);
		m_DialogCanvas.m_frontDC.SelectObject( oldFont );
		oldFont = (CFont *) m_DialogCanvas.m_frontDC.SelectObject( &SmallFont );
		ptrFont = &SmallFont;
		stringSize = m_DialogCanvas.m_frontDC.GetTextExtent(text);
	}
	else
		ptrFont = &LargeFont;
	
	y -= (stringSize.cy + 15);
	textPoint = CPoint( (m_DialogCanvas.m_image_size.cx - stringSize.cx) / 2,  y);
	m_DialogCanvas.m_frontDC.SetTextColor(0);
	m_DialogCanvas.m_frontDC.TextOut( textPoint.x, textPoint.y, text);	
	m_DialogCanvas.m_frontDC.SelectObject( oldFont );

	oldFont = (CFont *) m_DialogCanvas.m_drawDC.SelectObject( ptrFont );
	m_DialogCanvas.m_drawDC.SetTextColor(0);
	m_DialogCanvas.m_drawDC.TextOut( textPoint.x, textPoint.y, text);	
	m_DialogCanvas.m_drawDC.SelectObject( oldFont );
	// Crash -->
	CDC * attackPieceDC;
	CDC * defendPieceDC;
WriteDebug(__FILE__,__LINE__,NULL);
	if (HideAttack)
		attackPieceDC = &unknownPiece_dc[attackColor];
	else
		attackPieceDC = &piece_dc[attackColor][attackPiece.m_Piece];
	
	if (HideDefend)
		defendPieceDC = &unknownPiece_dc[defendColor];
	else
		defendPieceDC = &piece_dc[defendColor][defendPiece.m_Piece];

    // Crash -->	
WriteDebug(__FILE__,__LINE__,NULL);
	if (outcome == Win || outcome == WinGame)
		CopyPiece(attackPieceDC, &m_DialogCanvas.m_frontDC, attackRect, 0, 0 );
	CopyPiece(attackPieceDC, &m_DialogCanvas.m_drawDC, attackRect, 0, 0 );
WriteDebug(__FILE__,__LINE__,NULL);	
	if (outcome == Lose)
		CopyPiece(defendPieceDC, &m_DialogCanvas.m_frontDC, defendRect, 0, 0 );
	CopyPiece(defendPieceDC, &m_DialogCanvas.m_drawDC, defendRect, 0, 0 );
WriteDebug(__FILE__,__LINE__,NULL);	
    // crash -->
	if (m_BattleMBMP)
		delete m_BattleMBMP;
	char msg[1000];
	wsprintf(msg,"CMorphBMP( &m_DialogCanvas.m_drawDC = 0x%08x, &m_DialogCanvas.m_frontDC = 0x%08x, CPoint(0,0), CPoint(0,0), m_DialogCanvas.m_image_size = (%i, %i), CMorphBMP::FADE )", &m_DialogCanvas.m_drawDC, &m_DialogCanvas.m_frontDC, m_DialogCanvas.m_image_size.cx, m_DialogCanvas.m_image_size.cy );
	WriteDebug(__FILE__,__LINE__,msg);
	// crash -->
	m_BattleMBMP = new CMorphBMP( &m_DialogCanvas.m_drawDC, &m_DialogCanvas.m_frontDC, CPoint(0,0), CPoint(0,0), m_DialogCanvas.m_image_size, CMorphBMP::FADE, outcome == WinGame ? 5.0 : 1.0, 75.0 );
WriteDebug(__FILE__,__LINE__,NULL);	
	// Crash <---
    m_RedrawInfo.m_ShowBattleResults = 1;
	m_AllowScrolling = FALSE;
	m_DialogShowing = true;
	
	Invalidate();
}

CPlayerData & CStrategoControlCtrl::Player(int PlayerID)
{
	//TODO: return statement
	ASSERT(PlayerID == 1 || PlayerID == 2);
	return m_Players[PlayerID - 1];
}

void CStrategoControlCtrl::PlaceAllRemainingPieces(void)
{
	StrategoPieceType piece[40];
	int u, p, i, a, b;
	
    u = 0;
    
	for (p = Bomb; p <= Flag; p++)
	{
        for (i = 1; i <= m_piecesAvailable[p]; i++)
           piece[u++] = StrategoPieceType(p);
	}


    for (i = 1; i <= 2048; i++)
	{
       a = rand() % 40;
	   b = rand() % 40;
	   StrategoPieceType temp = piece[a];
	   piece[a] = piece[b];
	   piece[b] = temp;
	}
	
    u = 0;
    for (a = 0; a <= 9; a++)
	{
        for (b = 6; b <= 9; b++, u++)
		{
            PlacePiece(1, a, b, piece[u]);
			PiecePlaced(1, a, b, piece[u]); // piece placed
			m_SetupPiecesLeft--;
			((CWnd *)m_Button)->EnableWindow( !m_SetupPiecesLeft );
			m_piecesAvailable[piece[u]]--;
			if (m_piecesAvailable[piece[u]] == 0)
				m_RedrawInfo.m_SetupPieces = true;
		}
	}
	InvalidateControl();
}

LONG CStrategoControlCtrl::GetShowAllPieces(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return (m_HideEnemyPieces ? -1 : 0);
}

void CStrategoControlCtrl::SetShowAllPieces(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_HideEnemyPieces = (newVal ? false : true);
	m_RedrawInfo.m_RefreshPieces = true;
	InvalidateControl();
	SetModifiedFlag();
}

void CStrategoControlCtrl::OnAllowScrollingChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	SetModifiedFlag();
}

BOOL CStrategoControlCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return COleControl::PreTranslateMessage(pMsg);
}

LONG CStrategoControlCtrl::GetCurrentPlayer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	return m_CurrentID;
}

void CStrategoControlCtrl::SetCurrentPlayer(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if (newVal == 1 || newVal == 2)
	{
		m_CurrentID = newVal;
		SetModifiedFlag();	
	}
}

void CStrategoControlCtrl::RestartGame(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	InitializeGame();
	m_ptrCanvas = &m_SetupCanvas;//m_BoardCanvas;
	CalculateDimensions();
	Invalidate();
}

void CStrategoControlCtrl::InitializeGame(void)
{
	m_CurrentID = 0; // player IDs start at 1
	m_BoardState = Unintialized;
	m_MovePiece = StrategoPiece(Bomb, m_CurrentID);
	m_AutoMove = false;
	m_AllowScrolling = FALSE;
	m_lastAutoMove.execute = false;
	m_DialogShowing = false;
	m_HideEnemyPieces = true;
	m_MoveHighlightSquare = CPoint(-1,-1);

	m_piecesAvailable[Bomb]       = 6;
	m_piecesAvailable[Marshal]    = 1;
	m_piecesAvailable[General]    = 1;
	m_piecesAvailable[Colonel]    = 2;
	m_piecesAvailable[Major]      = 3;
	m_piecesAvailable[Captain]    = 4;
	m_piecesAvailable[Lieutenant] = 4;
	m_piecesAvailable[Sergeant]   = 4;
	m_piecesAvailable[Miner]      = 5;
	m_piecesAvailable[Scout]      = 8;
	m_piecesAvailable[Spy]        = 1;
	m_piecesAvailable[Flag]       = 1;
	m_SetupPiecesLeft             = 40;
	m_Board.ClearBoard();
	m_Board.RedrawAllPieces();
	m_RedrawInfo.m_RefreshPieces = true;

}

LONG CStrategoControlCtrl::RemovePiece(SHORT x, SHORT y)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	return m_Board.ClearPiece(CPoint(x,y));
}

void CStrategoControlCtrl::TurnOver(void)
{
	m_CurrentID = (m_CurrentID == 1 ? 2 : 1);
}

void CStrategoControlCtrl::OnPlaceUnitsAtStartChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}
