Option Explicit On 

Public Module StrategoDefinitions

    Enum ColorEnum
        Blue = 0
        Red = 1
    End Enum

    Enum BoardState
        Setup = 1
        Waiting = 2
        PlayingGame = 3
        Finished = 4
    End Enum

    Enum PieceType
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

    Enum OpponentType
        Network = 0
        LocalComputer = 1
    End Enum

    Enum StrategoMessageType
        Ack
        StartGame      ' Name, Random Number       
        PlacePiece
        RemovePiece
        SetupDone
        MovePiece
        LeavingGame
        CustomMessage1
    End Enum

    Enum ConfigureStep
        GameType
        ComputerSettings
        NetworkSettings
        ReadyToStart
        SetRules
        GameStarted
    End Enum

    Public piecesAvailable(12) As Integer

    Sub Swap(ByRef piece_a As PieceType, ByRef piece_b As PieceType)
        Dim piece_temp As PieceType
        piece_temp = piece_a
        piece_a = piece_b
        piece_b = piece_temp
    End Sub

    Sub InitializeConstants()
        piecesAvailable(PieceType.Bomb) = 6
        piecesAvailable(PieceType.Marshal) = 1
        piecesAvailable(PieceType.General) = 1
        piecesAvailable(PieceType.Colonel) = 2
        piecesAvailable(PieceType.Major) = 3
        piecesAvailable(PieceType.Captain) = 4
        piecesAvailable(PieceType.Lieutenant) = 4
        piecesAvailable(PieceType.Sergeant) = 4
        piecesAvailable(PieceType.Miner) = 5
        piecesAvailable(PieceType.Scout) = 8
        piecesAvailable(PieceType.Spy) = 1
        piecesAvailable(PieceType.Flag) = 1
    End Sub

    Public Sub PlacePieces(ByRef StrategoBoard As AxStrategoControlLib.AxStrategoControl)
        Dim piece(40) As PieceType
        Dim u As Integer, p As Integer, i As Integer, a As Integer, b As Integer
        u = 0
        For p = PieceType.Bomb To PieceType.Flag
            For i = 1 To piecesAvailable(p)
                piece(u) = p
                u = u + 1
            Next i
        Next p

        For i = 1 To 2048
            a = Int(40 * Rnd())
            b = Int(40 * Rnd())
            Swap(piece(a), piece(b))
        Next i

        u = 0
        For a = 0 To 9
            For b = 0 To 3
                StrategoBoard.PlacePiece(2, a, b, piece(u))
                u = u + 1
            Next
        Next

    End Sub


End Module
