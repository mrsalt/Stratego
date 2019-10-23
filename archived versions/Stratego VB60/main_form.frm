VERSION 5.00
Object = "{CB66B265-39BB-475E-82F1-B063D8DC2269}#1.0#0"; "StrategoBoardControl.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6330
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   10695
   LinkTopic       =   "Form1"
   ScaleHeight     =   6330
   ScaleWidth      =   10695
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin STRATEGOBOARDCONTROLLib.StrategoBoardControl StrategoBoardControl1 
      Height          =   5895
      Left            =   2640
      TabIndex        =   11
      Top             =   120
      Width           =   7815
      _Version        =   65536
      _ExtentX        =   13785
      _ExtentY        =   10398
      _StockProps     =   0
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   2040
      TabIndex        =   6
      Top             =   1200
      Width           =   375
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   1200
      TabIndex        =   5
      Top             =   1200
      Width           =   375
   End
   Begin VB.CommandButton MakeMoveButton 
      Caption         =   "Make Move"
      Height          =   375
      Left            =   960
      TabIndex        =   4
      Top             =   1800
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   720
      Width           =   375
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1200
      TabIndex        =   0
      Top             =   720
      Width           =   375
   End
   Begin VB.Label Label6 
      Caption         =   "To"
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   1200
      Width           =   615
   End
   Begin VB.Label Label5 
      Caption         =   "From"
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   720
      Width           =   495
   End
   Begin VB.Label Label4 
      Caption         =   "y"
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Top             =   1200
      Width           =   255
   End
   Begin VB.Label Label3 
      Caption         =   "x"
      Height          =   375
      Left            =   840
      TabIndex        =   7
      Top             =   1200
      Width           =   255
   End
   Begin VB.Label Label2 
      Caption         =   "y"
      Height          =   375
      Left            =   1680
      TabIndex        =   3
      Top             =   720
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "x"
      Height          =   375
      Left            =   840
      TabIndex        =   2
      Top             =   720
      Width           =   255
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim GameInitialized As Boolean

Private Sub PlacePieces()
    Dim piece(0 To 39) As PieceTypeEnum
    Dim u As Integer, p As Integer, i As Integer, a As Integer, b As Integer
    u = 0
    For p = Bomb To Flag
        For i = 1 To piecesAvailable(p)
            piece(u) = p
            u = u + 1
        Next i
    Next p
    
    For i = 1 To 2048
        a = Int(40 * Rnd())
        b = Int(40 * Rnd())
        Swap piece(a), piece(b)
    Next i
    
    u = 0
    For a = 0 To 9
      For b = 0 To 3
        StrategoBoardControl1.PlacePiece 2, a, b, piece(u)
        u = u + 1
      Next
    Next
    
End Sub

Private Sub Form_Activate()
    If GameInitialized = False Then
        SelectColorForm.Show vbModal, Me
        If SelectColorForm.Result = False Then
            End
        End If
            
        Dim myColor As ColorEnum, opponentColor As ColorEnum
        If SelectColorForm.ColorSelection(0).Value Then
            myColor = Red
            opponentColor = Blue
        Else
            myColor = Blue
            opponentColor = Red
        End If
        
        StrategoBoardControl1.SetPlayerData 1, PlayerTypeEnum.Human, myColor
        StrategoBoardControl1.SetPlayerData 2, PlayerTypeEnum.Other, opponentColor
        
        GameInitialized = True
        StrategoBoardControl1.SetStateAndPlayer BoardState.Setup, 1
        PlacePieces
        
    End If
End Sub

Private Sub Form_Initialize()
    GameInitialized = False
    InitializeConstants
End Sub

Private Sub Form_Resize()
  If Form1.Width > 2760 Then StrategoBoardControl1.Width = Form1.Width - 2760
  If Form1.Height > 465 Then StrategoBoardControl1.Height = Form1.Height - 465
End Sub

Private Sub MakeMoveButton_Click()
    If StrategoBoardControl1.MovePiece(Text1, Text2, Text3, Text4) Then
        Text1 = Text3
        Text2 = Text4
        MakeMoveButton.Visible = False
        StrategoBoardControl1.BoardState = BoardState.MakingMove
    End If
End Sub

Private Sub StrategoBoardControl1_MovePiece(ByVal x1 As Integer, ByVal y1 As Integer, ByVal x2 As Integer, ByVal y2 As Integer)
    MakeMoveButton.Visible = True
End Sub

Private Sub StrategoBoardControl1_SetupDone()
    If StrategoBoardControl1.myColor = ColorEnum.Red Then
        StrategoBoardControl1.BoardState = BoardState.MakingMove
    Else
        MakeMoveButton.Visible = True
    End If
End Sub
