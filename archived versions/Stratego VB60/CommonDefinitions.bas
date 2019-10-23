Attribute VB_Name = "Module1"
Option Explicit

Enum ColorEnum
    Blue = 0
    Red = 1
End Enum

Enum BoardState
    Setup = 1
    MakingMove = 2
    Waiting = 3
    Finished = 4
End Enum

Enum PieceTypeEnum
    Bomb = 0
    Marshal = 1
    General = 2
    Colonel = 3
    Major = 4
    Captain = 5
    Lieutenant = 6
    Sergeant = 7
    Miner = 8
    Scout = 9
    Spy = 10
    Flag = 11
    Unknown = 12
End Enum

Enum PlayerTypeEnum
    Human = 0
    Other = 1
End Enum

Public piecesAvailable(0 To 11) As Integer

Sub Swap(ByRef piece_a As PieceTypeEnum, ByRef piece_b As PieceTypeEnum)
    Dim piece_temp As PieceTypeEnum
    piece_temp = piece_a
    piece_a = piece_b
    piece_b = piece_temp
End Sub

Sub InitializeConstants()
    piecesAvailable(Bomb) = 6
    piecesAvailable(Marshal) = 1
    piecesAvailable(General) = 1
    piecesAvailable(Colonel) = 2
    piecesAvailable(Major) = 3
    piecesAvailable(Captain) = 4
    piecesAvailable(Lieutenant) = 4
    piecesAvailable(Sergeant) = 4
    piecesAvailable(Miner) = 5
    piecesAvailable(Scout) = 8
    piecesAvailable(Spy) = 1
    piecesAvailable(Flag) = 1
End Sub
