Public Class GameTypeForm
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
    Friend WithEvents NameBox As System.Windows.Forms.TextBox
    Friend WithEvents computerRadio As System.Windows.Forms.RadioButton
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents networkRadio As System.Windows.Forms.RadioButton
    Friend WithEvents Label3 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.NameBox = New System.Windows.Forms.TextBox()
        Me.computerRadio = New System.Windows.Forms.RadioButton()
        Me.networkRadio = New System.Windows.Forms.RadioButton()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 48)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(56, 24)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "My Name"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'NameBox
        '
        Me.NameBox.Location = New System.Drawing.Point(80, 48)
        Me.NameBox.Name = "NameBox"
        Me.NameBox.Size = New System.Drawing.Size(96, 20)
        Me.NameBox.TabIndex = 1
        Me.NameBox.Text = ""
        '
        'computerRadio
        '
        Me.computerRadio.Location = New System.Drawing.Point(32, 144)
        Me.computerRadio.Name = "computerRadio"
        Me.computerRadio.TabIndex = 2
        Me.computerRadio.Text = "vs. Computer"
        '
        'networkRadio
        '
        Me.networkRadio.Checked = True
        Me.networkRadio.Location = New System.Drawing.Point(32, 112)
        Me.networkRadio.Name = "networkRadio"
        Me.networkRadio.Size = New System.Drawing.Size(136, 24)
        Me.networkRadio.TabIndex = 3
        Me.networkRadio.TabStop = True
        Me.networkRadio.Text = "vs. Human (network)"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 88)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(104, 24)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Game Type:"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(72, 184)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 5
        Me.Button1.Text = "OK"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 16)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(120, 16)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "New Game"
        '
        'GameTypeForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(216, 222)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label3, Me.Button1, Me.Label2, Me.networkRadio, Me.computerRadio, Me.NameBox, Me.Label1})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "GameTypeForm"
        Me.ShowInTaskbar = False
        Me.Text = "Stratego.NET"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click

        If (NameBox.TextLength = 0) Then
            MsgBox("You must have a name!  Please enter your name.", MsgBoxStyle.OKOnly, "Error")
            Exit Sub
        End If

        If computerRadio.Checked Then
            MsgBox("Computer game is not yet supported.", MsgBoxStyle.OKOnly, "Error")
            Exit Sub
        End If

        DialogResult = DialogResult.OK
        Close()

    End Sub

    'Private Sub NameBox_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles NameBox.KeyPress

    'End Sub

    Private Sub GameTypeForm_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles MyBase.KeyPress, NameBox.KeyPress
        If e.KeyChar = Chr(13) Then
            Button1_Click(Me, New System.EventArgs())
        End If
    End Sub
End Class
