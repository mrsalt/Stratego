Public Class GameReadyForm
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
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents player1_label As System.Windows.Forms.Label
    Friend WithEvents player2_label As System.Windows.Forms.Label
    Friend WithEvents player1_color As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents info_label As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents player2_color As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.player1_label = New System.Windows.Forms.Label()
        Me.player2_label = New System.Windows.Forms.Label()
        Me.player1_color = New System.Windows.Forms.Label()
        Me.player2_color = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.info_label = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(24, 48)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 23)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Player 1"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(24, 88)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(48, 23)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Player 2"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'player1_label
        '
        Me.player1_label.Location = New System.Drawing.Point(88, 48)
        Me.player1_label.Name = "player1_label"
        Me.player1_label.Size = New System.Drawing.Size(64, 23)
        Me.player1_label.TabIndex = 2
        Me.player1_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'player2_label
        '
        Me.player2_label.Location = New System.Drawing.Point(88, 88)
        Me.player2_label.Name = "player2_label"
        Me.player2_label.Size = New System.Drawing.Size(64, 23)
        Me.player2_label.TabIndex = 3
        Me.player2_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'player1_color
        '
        Me.player1_color.BackColor = System.Drawing.Color.Red
        Me.player1_color.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.player1_color.Location = New System.Drawing.Point(176, 48)
        Me.player1_color.Name = "player1_color"
        Me.player1_color.Size = New System.Drawing.Size(32, 23)
        Me.player1_color.TabIndex = 4
        '
        'player2_color
        '
        Me.player2_color.BackColor = System.Drawing.Color.Red
        Me.player2_color.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.player2_color.Location = New System.Drawing.Point(176, 88)
        Me.player2_color.Name = "player2_color"
        Me.player2_color.Size = New System.Drawing.Size(32, 23)
        Me.player2_color.TabIndex = 5
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(48, 16)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(112, 24)
        Me.Label4.TabIndex = 6
        Me.Label4.Text = "Name"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(176, 16)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(32, 23)
        Me.Label5.TabIndex = 7
        Me.Label5.Text = "Color"
        Me.Label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'info_label
        '
        Me.info_label.Location = New System.Drawing.Point(40, 128)
        Me.info_label.Name = "info_label"
        Me.info_label.Size = New System.Drawing.Size(192, 24)
        Me.info_label.TabIndex = 8
        Me.info_label.Text = "Bob will go first"
        Me.info_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(80, 168)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(104, 23)
        Me.Button1.TabIndex = 9
        Me.Button1.Text = "Place Units"
        '
        'GameReadyForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(250, 206)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button1, Me.info_label, Me.Label5, Me.Label4, Me.player2_color, Me.player1_color, Me.player2_label, Me.player1_label, Me.Label2, Me.Label1})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "GameReadyForm"
        Me.ShowInTaskbar = False
        Me.Text = "Stratego.NET"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Close()
    End Sub
End Class
