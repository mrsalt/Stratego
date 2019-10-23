Imports System.Threading
Imports StrategoNET.StrategoDefinitions

Public Class StrategoForm
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call
        Dim currentDomain As AppDomain = AppDomain.CurrentDomain
        AddHandler currentDomain.UnhandledException, AddressOf HandleException
    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents StrategoBoard As AxStrategoControlLib.AxStrategoControl
    Friend WithEvents status_label As System.Windows.Forms.Label
    Friend WithEvents status_label_2 As System.Windows.Forms.Label
    Friend WithEvents SendTextBox As System.Windows.Forms.TextBox
    Friend WithEvents ReceiveTextBox As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(StrategoForm))
        Me.StrategoBoard = New AxStrategoControlLib.AxStrategoControl()
        Me.status_label = New System.Windows.Forms.Label()
        Me.status_label_2 = New System.Windows.Forms.Label()
        Me.SendTextBox = New System.Windows.Forms.TextBox()
        Me.ReceiveTextBox = New System.Windows.Forms.TextBox()
        CType(Me.StrategoBoard, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'StrategoBoard
        '
        Me.StrategoBoard.Enabled = True
        Me.StrategoBoard.Location = New System.Drawing.Point(144, 0)
        Me.StrategoBoard.Name = "StrategoBoard"
        Me.StrategoBoard.OcxState = CType(resources.GetObject("StrategoBoard.OcxState"), System.Windows.Forms.AxHost.State)
        Me.StrategoBoard.Size = New System.Drawing.Size(416, 456)
        Me.StrategoBoard.TabIndex = 12
        '
        'status_label
        '
        Me.status_label.Location = New System.Drawing.Point(8, 16)
        Me.status_label.Name = "status_label"
        Me.status_label.Size = New System.Drawing.Size(128, 24)
        Me.status_label.TabIndex = 13
        Me.status_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'status_label_2
        '
        Me.status_label_2.Location = New System.Drawing.Point(8, 48)
        Me.status_label_2.Name = "status_label_2"
        Me.status_label_2.Size = New System.Drawing.Size(128, 24)
        Me.status_label_2.TabIndex = 14
        Me.status_label_2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'SendTextBox
        '
        Me.SendTextBox.Location = New System.Drawing.Point(8, 104)
        Me.SendTextBox.Multiline = True
        Me.SendTextBox.Name = "SendTextBox"
        Me.SendTextBox.Size = New System.Drawing.Size(128, 112)
        Me.SendTextBox.TabIndex = 15
        Me.SendTextBox.Text = ""
        '
        'ReceiveTextBox
        '
        Me.ReceiveTextBox.Location = New System.Drawing.Point(8, 248)
        Me.ReceiveTextBox.Multiline = True
        Me.ReceiveTextBox.Name = "ReceiveTextBox"
        Me.ReceiveTextBox.Size = New System.Drawing.Size(128, 112)
        Me.ReceiveTextBox.TabIndex = 16
        Me.ReceiveTextBox.Text = ""
        '
        'StrategoForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(560, 454)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.ReceiveTextBox, Me.SendTextBox, Me.status_label_2, Me.status_label, Me.StrategoBoard})
        Me.Name = "StrategoForm"
        Me.Text = "Stratego"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        CType(Me.StrategoBoard, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private GameInitialized As Boolean
    Private myColor As ColorEnum, opponentColor As ColorEnum
    Private myRank As Integer, opponentRank As Integer
    Private myName As String, opponentName As String
    Private opponentJoined As Boolean = False
    Private mySetupDone = False
    Private opponentSetupDone = False
    'Private opponentPiecesLeft = 40
    Private opponentSetup(9, 9) As PieceType

    Private gameForm As GameTypeForm
    Private networkForm As NetworkOptionsForm
    Private colorForm As SelectColorDialog
    Private waitConnectForm As WaitingForResponseForm
    Private gameReadyDialog As GameReadyForm
    Private rulesDialog As strategoRulesForm
    Private opponent As OpponentType

    Private initializeConnectionThread As Thread
    Private networkConnection As gameConnection

    Private Sub ClearSetupBoard()
        Dim rx As Integer, ry As Integer
        For rx = 0 To 9
            For ry = 0 To 9
                opponentSetup(rx, ry) = PieceType.Unknown
            Next
        Next
    End Sub

    Private Sub SetupOpponentBoard()
        Dim rx As Integer, ry As Integer
        For rx = 0 To 9
            For ry = 0 To 9
                If (opponentSetup(rx, ry) <> PieceType.Unknown) Then
                    StrategoBoard.PlacePiece(2, rx, ry, opponentSetup(rx, ry))
                End If
            Next
        Next
    End Sub

    Sub HandleException(ByVal sender As Object, ByVal args As UnhandledExceptionEventArgs)
        Dim e As Exception = DirectCast(args.ExceptionObject, Exception)
        MsgBox("Unhandled exception: " & e.ToString)
        Console.WriteLine("Unhandled exception : " + e.Message)
        Console.WriteLine("exception info: " + e.ToString)
    End Sub

    Protected Overrides Sub OnSizeChanged(ByVal e As System.EventArgs)
        StrategoBoard.Size = New System.Drawing.Size(Me.Size.Width - 160, Me.Size.Height - 32)
    End Sub

    Protected Overrides Sub OnLoad(ByVal e As System.EventArgs)

    End Sub

    Protected Overrides Sub OnActivated(ByVal e As System.EventArgs)
        If GameInitialized = False Then
            GameInitialized = True
            InitializeConstants()
            colorForm = New SelectColorDialog()
            gameForm = New GameTypeForm()
            networkForm = New NetworkOptionsForm()
            waitConnectForm = New WaitingForResponseForm()
            gameReadyDialog = New GameReadyForm()
            rulesDialog = New StrategoRulesForm()
            gameForm.NameBox.Text = GetSetting("Stratego.NET", "UserData", "Name")

            StartGame()
        End If
    End Sub

    Public Sub HandleMessage(ByVal messageType As StrategoMessageType, ByVal mParams() As Object)

        Select Case messageType
            Case StrategoMessageType.Ack
                Dim ackMessageId As Integer
                ackMessageId = mParams(0)
                'Console.WriteLine("StrategoForm.HandleMessage() Ack received")
            Case StrategoMessageType.MovePiece
                If StrategoBoard.MovePiece(9 - mParams(0), 9 - mParams(1), 9 - mParams(2), 9 - mParams(3)) = 0 Then
                    MsgBox("Error, message resulted in movepiece failure")
                End If
                HandleMove()
                'Console.WriteLine("StrategoForm.HandleMessage() MovePiece received")
            Case StrategoMessageType.PlacePiece
                'opponentPiecesLeft = opponentPiecesLeft - 1
                'status_label_2.Text = opponentName & " has " & opponentPiecesLeft & " piece(s) left"
                'Console.WriteLine("StrategoForm.HandleMessage() PlacePiece received")
                If StrategoBoard.BoardState = BoardState.Setup Then
                    StrategoBoard.PlacePiece(2, 9 - mParams(1), 9 - mParams(2), mParams(0))
                Else
                    opponentSetup(9 - mParams(1), 9 - mParams(2)) = mParams(0)
                End If

            Case StrategoMessageType.RemovePiece
                'opponentPiecesLeft = opponentPiecesLeft + 1
                'status_label_2.Text = opponentName & " has " & opponentPiecesLeft & " piece(s) left"
                'Console.WriteLine("StrategoForm.HandleMessage() RemovePiece received")
                If StrategoBoard.BoardState = BoardState.Setup Then
                    StrategoBoard.RemovePiece(9 - mParams(1), 9 - mParams(2))
                End If
            Case StrategoMessageType.SetupDone
                Console.WriteLine("Setup done event received")
                'If opponentPiecesLeft <> 0 Then
                'MsgBox("Stratego Error: setup done event received and opponent pieces left != 0")
                'End
                'End If
                opponentSetupDone = True
                SetupDoneEvent()
            Case StrategoMessageType.StartGame
                opponentName = mParams(0)
                opponentRank = mParams(1)
                opponentJoined = True
                'debug_label_1.Text = "opponent joined = true"
                'Console.WriteLine("StrategoForm.HandleMessage() StartGame received")
            Case StrategoMessageType.LeavingGame
                MsgBox(opponentName & " has left Stratego.", MsgBoxStyle.Information)
                waitConnectForm.Close()
                networkConnection.connectionState = gameConnection.connectionStateType.not_connected
                networkConnection = Nothing
        End Select
    End Sub

    Private Sub WaitForConnection()
        ' runs on separate thread
        Dim messageId As Integer
        'Console.WriteLine("dialog result = " & waitConnectForm.DialogResult)

        Do
            messageId = networkConnection.SendMessage(StrategoMessageType.StartGame, myName, myRank)
            If (messageId = 0) Then
                ' wait for a couple of seconds
                'debug_label_1.Text = "SendMessage failed"
                Thread.Sleep(2000)
            Else
                'debug_label_1.Text = "SendMessage success"
                'Console.WriteLine("exiting do, start sent successfully")
                Exit Do
            End If

            'Console.WriteLine("dialog result = " & waitConnectForm.DialogResult)

        Loop While waitConnectForm.DialogResult = DialogResult.None

        Do While opponentJoined = False
            'debug_label_1.Text = "opponent joined = false"
            Thread.Sleep(5)
            If waitConnectForm.DialogResult = DialogResult.Cancel Then
                'MsgBox("Wait for connection thread exiting (DialogResult = Cancel), messageId=" & messageId & ", opponentJoined=" & opponentJoined)
                Exit Sub
            End If
        Loop
        'MsgBox("Wait for connection thread exiting, messageId=" & messageId & ", opponentJoined=" & opponentJoined)
        waitConnectForm.Close()

    End Sub

    Private Sub ExitStratego(ByVal msgText As String)
        'MsgBox("Thank you for playing stratego! - " & msgText)
        If Not (networkConnection Is Nothing) Then
            If networkConnection.connectionState = gameConnection.connectionStateType.connected Then
                networkConnection.SendMessage(StrategoMessageType.LeavingGame)
            End If
        End If
        MsgBox("Thank you for playing stratego!")
        End
    End Sub

    Private Sub StartGame()
        Dim d As DateTime = Now
        Dim rSeed As Int32 = d.Ticks Mod Int32.MaxValue
        Dim randGenerator As New Random(rSeed)
        myRank = randGenerator.Next(Int32.MaxValue)

        PlayGame(ConfigureStep.GameType)
    End Sub

    Private Function ConfigureGame(ByVal currentStep As StrategoDefinitions.ConfigureStep) As StrategoDefinitions.ConfigureStep

        Select Case currentStep
            Case ConfigureStep.GameType
                If gameForm.ShowDialog(Me) = DialogResult.Cancel Then
                    ExitStratego("gameForm.ShowDialog(Me) = DialogResult.Cancel")
                End If

                myName = gameForm.NameBox.Text
                SaveSetting("Stratego.NET", "UserData", "Name", myName)

                If gameForm.networkRadio.Checked Then
                    Return ConfigureGame(ConfigureStep.NetworkSettings)
                Else
                    Return ConfigureGame(ConfigureStep.ComputerSettings)
                End If
            Case ConfigureStep.ComputerSettings
                MsgBox("computer opponent not yet supported")
                Return ConfigureGame(ConfigureStep.GameType)
            Case ConfigureStep.NetworkSettings
                networkForm.server_name.Text = GetSetting("Stratego.NET", "NetConfig", "GameServer")
                networkForm.local_port.Text = GetSetting("Stratego.NET", "NetConfig", "LocalPort", "5829")
                networkForm.remote_ip.Text = GetSetting("Stratego.NET", "NetConfig", "RemoteIP", "127.0.0.1")
                networkForm.remote_port.Text = GetSetting("Stratego.NET", "NetConfig", "RemotePort", "5829")

                If networkForm.ShowDialog(Me) = DialogResult.Cancel Then
                    Return ConfigureGame(ConfigureStep.GameType)
                    'ExitStratego("networkForm.ShowDialog(Me) = DialogResult.Cancel")
                End If

                SaveSetting("Stratego.NET", "NetConfig", "GameServer", networkForm.server_name.Text)
                SaveSetting("Stratego.NET", "NetConfig", "LocalPort", networkForm.local_port.Text)
                SaveSetting("Stratego.NET", "NetConfig", "RemoteIP", networkForm.remote_ip.Text)
                SaveSetting("Stratego.NET", "NetConfig", "RemotePort", networkForm.remote_port.Text)

                'MsgBox("creating network connection object")
                If networkForm.PeerToPeer.Checked Then
                    networkConnection = New PeerToPeerConnection(AddressOf HandleMessage, networkForm.remote_ip.Text, networkForm.remote_port.Text, networkForm.local_port.Text)
                ElseIf networkForm.DirectClient.Checked Then
                    networkConnection = New DirectConnection(AddressOf HandleMessage, networkForm.remote_ip.Text, networkForm.remote_port.Text)
                ElseIf networkForm.DirectHost.Checked Then
                    networkConnection = New DirectConnection(AddressOf HandleMessage, networkForm.local_port.Text)
                Else 'game server not yet supported

                End If
                networkConnection.SendBox = Me.SendTextBox
                networkConnection.ReceiveBox = Me.ReceiveTextBox
                opponentJoined = False
                Return ConfigureGame(ConfigureStep.ReadyToStart)
            Case ConfigureStep.ReadyToStart
                StrategoBoard.BoardState = BoardState.Waiting
                ClearSetupBoard()
                mySetupDone = False
                opponentSetupDone = False

                If gameForm.networkRadio.Checked Then
                    'MsgBox("networkRadio checked, starting listen thread")
                    ' start connect thread

                    initializeConnectionThread = New Thread(AddressOf Me.WaitForConnection)
                    initializeConnectionThread.Start()
                    ' show dialog
                    waitConnectForm.ShowDialog(Me)

                    ' if connection is OK, continue
                    If networkConnection.connectionState = gameConnection.connectionStateType.not_connected Or opponentJoined = False Then
                        networkConnection = Nothing
                        Return ConfigureGame(ConfigureStep.NetworkSettings)
                        'ExitStratego("connection not OK")
                    End If
                End If
                Swap(myRank, opponentRank)
                Return ConfigureGame(ConfigureStep.SetRules)
            Case ConfigureStep.SetRules
                'rulesDialog()
                'If myRank > opponentRank Then

                'End If
                Return ConfigureStep.GameStarted
        End Select

    End Function

    Private Sub PlayGame(ByVal ConfigStartStep As StrategoDefinitions.ConfigureStep)

        If ConfigureGame(ConfigStartStep) <> ConfigureStep.GameStarted Then
            MsgBox("Error, PlayGame(), call to ConfigureGame() returned something besides GameStarted")
            ExitStratego("")
        End If

        gameReadyDialog.player1_label.Text = myName
        gameReadyDialog.player2_label.Text = opponentName

        If myRank > opponentRank Then ' I go first
            gameReadyDialog.player1_color.BackColor = Drawing.Color.Red
            gameReadyDialog.player2_color.BackColor = Drawing.Color.Blue
            gameReadyDialog.info_label.Text = myName & " will go first."
            myColor = ColorEnum.Red
            opponentColor = ColorEnum.Blue
        ElseIf myRank < opponentRank Then
            gameReadyDialog.player1_color.BackColor = Drawing.Color.Blue
            gameReadyDialog.player2_color.BackColor = Drawing.Color.Red
            gameReadyDialog.info_label.Text = opponentName & " will go first."
            myColor = ColorEnum.Blue
            opponentColor = ColorEnum.Red
        Else
            'MsgBox("Game Over - both computers picked the same random number")
            ExitStratego("Game Over - both computers picked the same random number")
        End If

        StrategoBoard.SetPlayerData(1, PlayerTypeEnum.Human, myColor)
        StrategoBoard.SetPlayerData(2, PlayerTypeEnum.Other, opponentColor)
        StrategoBoard.SetStateAndPlayer(BoardState.Setup, 1)
        SetupOpponentBoard()
        status_label.Text = "Placing pieces"

        gameReadyDialog.ShowDialog(Me)
        opponentJoined = False
        'If colorForm.ShowDialog(Me) = DialogResult.Cancel Then
        'End
        'End If

        'myColor = colorForm.Color
        'If myColor = ColorEnum.Red Then
        'opponentColor = ColorEnum.Blue
        'Else
        '    opponentColor = ColorEnum.Red
        'End If

        'networkConnection.SendMessage(StrategoMessageType.SetupDone)
        'PlacePieces(StrategoBoard) <-- this function places pieces for player 2
    End Sub

    Private Sub HandleMove()
        If StrategoBoard.CurrentPlayer = 1 Then
            status_label.Text = myName & "'s turn"
        Else
            status_label.Text = opponentName & "'s turn"
        End If
    End Sub

    Private Sub SetupDoneEvent()
        If mySetupDone And opponentSetupDone Then
            If myColor = ColorEnum.Red Then
                StrategoBoard.SetStateAndPlayer(BoardState.PlayingGame, 1)
            Else
                StrategoBoard.SetStateAndPlayer(BoardState.PlayingGame, 2)
            End If
            HandleMove()
            status_label_2.Text = ""
        ElseIf mySetupDone Then
            status_label.Text = "Done placing pieces"
            status_label_2.Text = "Waiting for " & opponentName & " to place all pieces"
        ElseIf opponentSetupDone Then
            status_label_2.Text = opponentName & " has placed all pieces"
        End If
    End Sub

    Private Sub StrategoBoard_PiecePlaced(ByVal sender As Object, ByVal e As AxStrategoControlLib._DStrategoControlEvents_PiecePlacedEvent) Handles StrategoBoard.PiecePlaced
        If e.playerID = 1 Then
            networkConnection.SendMessage(StrategoMessageType.PlacePiece, e.type, e.x1, e.y1)
        End If
    End Sub

    Private Sub StrategoBoard_PieceRemoved(ByVal sender As Object, ByVal e As AxStrategoControlLib._DStrategoControlEvents_PieceRemovedEvent) Handles StrategoBoard.PieceRemoved
        If e.playerID = 1 Then
            networkConnection.SendMessage(StrategoMessageType.RemovePiece, e.type, e.x, e.y)
        End If
    End Sub

    Private Sub StrategoBoard_SetupDone(ByVal sender As Object, ByVal e As System.EventArgs) Handles StrategoBoard.SetupDone
        StrategoBoard.SetStateAndPlayer(BoardState.Waiting, 1)
        'Console.WriteLine("Board event: setup done")
        networkConnection.SendMessage(StrategoMessageType.SetupDone)
        mySetupDone = True
        SetupDoneEvent()
    End Sub

    Private Sub StrategoBoard_PieceMoved(ByVal sender As Object, ByVal e As AxStrategoControlLib._DStrategoControlEvents_PieceMovedEvent) Handles StrategoBoard.PieceMoved
        If e.playerID = 1 Then
            HandleMove()
            networkConnection.SendMessage(StrategoMessageType.MovePiece, e.x1, e.y1, e.x2, e.y2)
        End If
    End Sub

    Private Sub StrategoBoard_GameOver(ByVal sender As Object, ByVal e As AxStrategoControlLib._DStrategoControlEvents_GameOverEvent) Handles StrategoBoard.GameOver
        Dim playAgain As MsgBoxResult
        status_label.Text = "Game Over"

        If e.playerID = 1 Then
            status_label_2.Text = opponentName & " Won!"
        Else
            status_label_2.Text = myName & " Won!"
        End If

        playAgain = MsgBox("Would you like to play again?", MsgBoxStyle.YesNo, "Game Over")

        If playAgain = MsgBoxResult.Yes Then
            status_label.Text = ""
            status_label_2.Text = ""
            StrategoBoard.RestartGame()
            waitConnectForm.Label1.Text = "Waiting for " & opponentName & " to join..."
            PlayGame(ConfigureStep.ReadyToStart)
        Else
            ExitStratego("")
        End If

    End Sub

    'Private Sub ShowAllPiecesCB_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs)
    '    StrategoBoard.ShowAllPieces = ShowAllPiecesCB.Checked
    'End Sub

    Private Sub HandleDoMove() ' test mode (make computer move)
        Dim x1 As Short, y1 As Short, x2 As Short, y2 As Short
        'x1 = TextBox1.Text
        'y1 = TextBox2.Text
        'x2 = TextBox3.Text
        'y2 = TextBox4.Text

        Dim makeMoveRet As Boolean = StrategoBoard.MovePiece(x1, y1, x2, y2)
        If makeMoveRet Then
            'TextBox1.Text = TextBox3.Text
            'TextBox2.Text = TextBox4.Text
            'MakeMoveButton.Visible = False
            'StrategoBoard.boardState = BoardState.MakingMove
            'StrategoBoard.SetStateAndPlayer(BoardState.MakingMove, 1)
        End If
    End Sub
    Private Sub MakeMoveButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        HandleDoMove()
    End Sub
    Private Sub MakeMoveButton_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs)
        HandleDoMove()
    End Sub
    Private Sub TextBox_ChangeUICues(ByVal sender As System.Object, ByVal e As System.Windows.Forms.UICuesEventArgs)
        Dim box As TextBox = sender
        box.SelectAll()
    End Sub


    Protected Overrides Sub Finalize()
        MyBase.Finalize()
    End Sub

    Private Sub StrategoForm_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        ExitStratego("")
    End Sub
End Class
