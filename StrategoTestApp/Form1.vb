Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

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
    Friend WithEvents StrategoControl As AxStrategoControlLib.AxStrategoControl
    Friend WithEvents place_player As System.Windows.Forms.Label
    Friend WithEvents place_piece As System.Windows.Forms.Label
    Friend WithEvents place_x1 As System.Windows.Forms.Label
    Friend WithEvents place_y1 As System.Windows.Forms.Label
    Friend WithEvents place_x2 As System.Windows.Forms.Label
    Friend WithEvents place_y2 As System.Windows.Forms.Label
    Friend WithEvents _placePlayer As System.Windows.Forms.TextBox
    Friend WithEvents _placePiece As System.Windows.Forms.TextBox
    Friend WithEvents x1 As System.Windows.Forms.TextBox
    Friend WithEvents y1 As System.Windows.Forms.TextBox
    Friend WithEvents x2 As System.Windows.Forms.TextBox
    Friend WithEvents y2 As System.Windows.Forms.TextBox
    Friend WithEvents PlaceButton As System.Windows.Forms.Button
    Friend WithEvents MoveButton As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.StrategoControl = New AxStrategoControlLib.AxStrategoControl()
        Me.place_player = New System.Windows.Forms.Label()
        Me.place_piece = New System.Windows.Forms.Label()
        Me.place_x1 = New System.Windows.Forms.Label()
        Me.place_y1 = New System.Windows.Forms.Label()
        Me.place_x2 = New System.Windows.Forms.Label()
        Me.place_y2 = New System.Windows.Forms.Label()
        Me._placePlayer = New System.Windows.Forms.TextBox()
        Me._placePiece = New System.Windows.Forms.TextBox()
        Me.x1 = New System.Windows.Forms.TextBox()
        Me.y1 = New System.Windows.Forms.TextBox()
        Me.x2 = New System.Windows.Forms.TextBox()
        Me.y2 = New System.Windows.Forms.TextBox()
        Me.PlaceButton = New System.Windows.Forms.Button()
        Me.MoveButton = New System.Windows.Forms.Button()
        CType(Me.StrategoControl, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'StrategoControl
        '
        Me.StrategoControl.Enabled = True
        Me.StrategoControl.Location = New System.Drawing.Point(168, 8)
        Me.StrategoControl.Name = "StrategoControl"
        Me.StrategoControl.OcxState = CType(resources.GetObject("StrategoControl.OcxState"), System.Windows.Forms.AxHost.State)
        Me.StrategoControl.Size = New System.Drawing.Size(440, 408)
        Me.StrategoControl.TabIndex = 0
        '
        'place_player
        '
        Me.place_player.Location = New System.Drawing.Point(16, 16)
        Me.place_player.Name = "place_player"
        Me.place_player.Size = New System.Drawing.Size(48, 16)
        Me.place_player.TabIndex = 1
        Me.place_player.Text = "Player"
        '
        'place_piece
        '
        Me.place_piece.Location = New System.Drawing.Point(16, 48)
        Me.place_piece.Name = "place_piece"
        Me.place_piece.Size = New System.Drawing.Size(48, 16)
        Me.place_piece.TabIndex = 2
        Me.place_piece.Text = "Piece"
        '
        'place_x1
        '
        Me.place_x1.Location = New System.Drawing.Point(16, 80)
        Me.place_x1.Name = "place_x1"
        Me.place_x1.Size = New System.Drawing.Size(48, 16)
        Me.place_x1.TabIndex = 3
        Me.place_x1.Text = "x1"
        '
        'place_y1
        '
        Me.place_y1.Location = New System.Drawing.Point(16, 112)
        Me.place_y1.Name = "place_y1"
        Me.place_y1.Size = New System.Drawing.Size(48, 16)
        Me.place_y1.TabIndex = 4
        Me.place_y1.Text = "y1"
        '
        'place_x2
        '
        Me.place_x2.Location = New System.Drawing.Point(16, 144)
        Me.place_x2.Name = "place_x2"
        Me.place_x2.Size = New System.Drawing.Size(48, 16)
        Me.place_x2.TabIndex = 5
        Me.place_x2.Text = "x2"
        '
        'place_y2
        '
        Me.place_y2.Location = New System.Drawing.Point(16, 176)
        Me.place_y2.Name = "place_y2"
        Me.place_y2.Size = New System.Drawing.Size(48, 16)
        Me.place_y2.TabIndex = 6
        Me.place_y2.Text = "y2"
        '
        '_placePlayer
        '
        Me._placePlayer.Location = New System.Drawing.Point(64, 16)
        Me._placePlayer.Name = "_placePlayer"
        Me._placePlayer.Size = New System.Drawing.Size(56, 20)
        Me._placePlayer.TabIndex = 7
        Me._placePlayer.Text = ""
        '
        '_placePiece
        '
        Me._placePiece.Location = New System.Drawing.Point(64, 48)
        Me._placePiece.Name = "_placePiece"
        Me._placePiece.Size = New System.Drawing.Size(56, 20)
        Me._placePiece.TabIndex = 8
        Me._placePiece.Text = ""
        '
        'x1
        '
        Me.x1.Location = New System.Drawing.Point(64, 80)
        Me.x1.Name = "x1"
        Me.x1.Size = New System.Drawing.Size(56, 20)
        Me.x1.TabIndex = 9
        Me.x1.Text = ""
        '
        'y1
        '
        Me.y1.Location = New System.Drawing.Point(64, 112)
        Me.y1.Name = "y1"
        Me.y1.Size = New System.Drawing.Size(56, 20)
        Me.y1.TabIndex = 10
        Me.y1.Text = ""
        '
        'x2
        '
        Me.x2.Location = New System.Drawing.Point(64, 144)
        Me.x2.Name = "x2"
        Me.x2.Size = New System.Drawing.Size(56, 20)
        Me.x2.TabIndex = 11
        Me.x2.Text = ""
        '
        'y2
        '
        Me.y2.Location = New System.Drawing.Point(64, 176)
        Me.y2.Name = "y2"
        Me.y2.Size = New System.Drawing.Size(56, 20)
        Me.y2.TabIndex = 12
        Me.y2.Text = ""
        '
        'PlaceButton
        '
        Me.PlaceButton.Location = New System.Drawing.Point(16, 216)
        Me.PlaceButton.Name = "PlaceButton"
        Me.PlaceButton.Size = New System.Drawing.Size(56, 24)
        Me.PlaceButton.TabIndex = 13
        Me.PlaceButton.Text = "Place"
        '
        'MoveButton
        '
        Me.MoveButton.Location = New System.Drawing.Point(88, 216)
        Me.MoveButton.Name = "MoveButton"
        Me.MoveButton.Size = New System.Drawing.Size(56, 24)
        Me.MoveButton.TabIndex = 14
        Me.MoveButton.Text = "Move"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(616, 422)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.MoveButton, Me.PlaceButton, Me.y2, Me.x2, Me.y1, Me.x1, Me._placePiece, Me._placePlayer, Me.place_y2, Me.place_x2, Me.place_y1, Me.place_x1, Me.place_piece, Me.place_player, Me.StrategoControl})
        Me.Name = "Form1"
        Me.Text = "Form1"
        CType(Me.StrategoControl, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Protected Overrides Sub OnSizeChanged(ByVal e As System.EventArgs)
        StrategoControl.Size = New System.Drawing.Size(Me.Size.Width - 184, Me.Size.Height - 48)
    End Sub


    Private Sub PlaceButton_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles PlaceButton.Click
        Dim playerID As Short = _placePlayer.Text
        Dim piece_type As Short = _placePiece.Text
        Dim x As Short = x1.Text
        Dim y As Short = y1.Text
        StrategoControl.PlacePiece(playerID, x, y, piece_type)
        StrategoControl.SetStateAndPlayer(2, 1)
    End Sub


    Private Sub MoveButton_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles MoveButton.Click
        Dim x_1 As Short = x1.Text
        Dim y_1 As Short = y1.Text
        Dim x_2 As Short = x2.Text
        Dim y_2 As Short = y2.Text
        StrategoControl.MovePiece(x_1, y_1, x_2, y_2)
    End Sub

    Protected Overrides Sub OnLoad(ByVal e As System.EventArgs)

    End Sub
End Class
