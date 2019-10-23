#ifndef STRATEGO_DEFINITIONS_H
#define STRATEGO_DEFINITIONS_H

#define NUM_PIECES		12
#define NUM_COLORS      2

enum BoardStateType { Unintialized = 0, Setup, Waiting, PlayingGame, Finished };

enum GameOverConditions { FlagCaptured = 1 };

enum StrategoPieceType { NoPiece = -1,
						 Bomb = 0, 
                         Marshal = 1, 
						 General = 2, 
						 Colonel = 3, 
						 Major = 4, 
						 Captain = 5, 
						 Lieutenant = 6, 
						 Sergeant = 7, 
						 Miner = 8, 
						 Scout = 9, 
						 Spy = 10,
						 Flag = 11,
						 Unknown = 12};

enum StrategoColor  { Blue = 0, Red = 1 };

enum BattleResolutionType { Win, Lose, Tie, WinGame };
enum DirectionType { All, Up, Down, Left, Right };

enum PlayerType { Human, Other };

#define NO_OWNER				0

//const char * PieceNames[] = { "Bomb", "Marshal", "General", "Colonel", "Major", "Captain", "Lieutenant", "Sergeant", "Miner", "Scout", "Spy", "Flag"

#define BOARD_ROWS				10
#define BOARD_COLUMNS			10

#define BOARD_BORDER_LEFT		20
#define BOARD_BORDER_TOP        20

#define SETUP_BORDER_LEFT       20
#define SETUP_BORDER_TOP        78

#define SETUP_PIECE_PANEL_LEFT  0    // relative to upper left corner of where board starts
#define SETUP_PIECE_PANEL_TOP   339

#define PIECE_WIDTH				69
#define PIECE_HEIGHT			100

const int minScrollAmount = 2;
const int maxScrollAmount = 40;
const int BorderScrollArea = 50;
const int borderOffset = 2;
const int panelBorderWidth = 4;


#endif