Public Class NetworkOptionsForm
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
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents PeerToPeer As System.Windows.Forms.RadioButton
    Friend WithEvents local_port As System.Windows.Forms.TextBox
    Friend WithEvents remote_ip As System.Windows.Forms.TextBox
    Friend WithEvents remote_port As System.Windows.Forms.TextBox
    Friend WithEvents GameServer As System.Windows.Forms.RadioButton
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents server_name As System.Windows.Forms.TextBox
    Friend WithEvents OKButton As System.Windows.Forms.Button
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents DirectHost As System.Windows.Forms.RadioButton
    Friend WithEvents DirectClient As System.Windows.Forms.RadioButton
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.PeerToPeer = New System.Windows.Forms.RadioButton()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.local_port = New System.Windows.Forms.TextBox()
        Me.remote_ip = New System.Windows.Forms.TextBox()
        Me.remote_port = New System.Windows.Forms.TextBox()
        Me.GameServer = New System.Windows.Forms.RadioButton()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.server_name = New System.Windows.Forms.TextBox()
        Me.OKButton = New System.Windows.Forms.Button()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.DirectHost = New System.Windows.Forms.RadioButton()
        Me.DirectClient = New System.Windows.Forms.RadioButton()
        Me.SuspendLayout()
        '
        'PeerToPeer
        '
        Me.PeerToPeer.Location = New System.Drawing.Point(24, 104)
        Me.PeerToPeer.Name = "PeerToPeer"
        Me.PeerToPeer.Size = New System.Drawing.Size(224, 24)
        Me.PeerToPeer.TabIndex = 0
        Me.PeerToPeer.Text = "Use Peer To Peer Connection"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(32, 176)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(64, 23)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Local Port"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(32, 208)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(64, 23)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Remote IP"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(32, 240)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(72, 23)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "Remote Port"
        '
        'local_port
        '
        Me.local_port.Location = New System.Drawing.Point(104, 176)
        Me.local_port.Name = "local_port"
        Me.local_port.TabIndex = 4
        Me.local_port.Text = "5829"
        '
        'remote_ip
        '
        Me.remote_ip.Location = New System.Drawing.Point(104, 208)
        Me.remote_ip.Name = "remote_ip"
        Me.remote_ip.TabIndex = 5
        Me.remote_ip.Text = "192.168.0.10"
        '
        'remote_port
        '
        Me.remote_port.Location = New System.Drawing.Point(104, 240)
        Me.remote_port.Name = "remote_port"
        Me.remote_port.TabIndex = 6
        Me.remote_port.Text = "5829"
        '
        'GameServer
        '
        Me.GameServer.Location = New System.Drawing.Point(24, 136)
        Me.GameServer.Name = "GameServer"
        Me.GameServer.Size = New System.Drawing.Size(168, 24)
        Me.GameServer.TabIndex = 7
        Me.GameServer.Text = "Use Game Server"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(32, 272)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(72, 23)
        Me.Label4.TabIndex = 8
        Me.Label4.Text = "Game Server"
        '
        'server_name
        '
        Me.server_name.Location = New System.Drawing.Point(104, 272)
        Me.server_name.Name = "server_name"
        Me.server_name.TabIndex = 9
        Me.server_name.Text = ""
        '
        'OKButton
        '
        Me.OKButton.Location = New System.Drawing.Point(96, 304)
        Me.OKButton.Name = "OKButton"
        Me.OKButton.TabIndex = 10
        Me.OKButton.Text = "OK"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(16, 16)
        Me.Label5.Name = "Label5"
        Me.Label5.TabIndex = 11
        Me.Label5.Text = "Network Options"
        '
        'DirectHost
        '
        Me.DirectHost.Checked = True
        Me.DirectHost.Location = New System.Drawing.Point(24, 40)
        Me.DirectHost.Name = "DirectHost"
        Me.DirectHost.Size = New System.Drawing.Size(152, 24)
        Me.DirectHost.TabIndex = 12
        Me.DirectHost.TabStop = True
        Me.DirectHost.Text = "Host direct game"
        '
        'DirectClient
        '
        Me.DirectClient.Location = New System.Drawing.Point(24, 72)
        Me.DirectClient.Name = "DirectClient"
        Me.DirectClient.Size = New System.Drawing.Size(168, 24)
        Me.DirectClient.TabIndex = 13
        Me.DirectClient.Text = "Join direct game"
        '
        'NetworkOptionsForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(266, 344)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.DirectClient, Me.DirectHost, Me.Label5, Me.OKButton, Me.server_name, Me.Label4, Me.GameServer, Me.remote_port, Me.remote_ip, Me.local_port, Me.Label3, Me.Label2, Me.Label1, Me.PeerToPeer})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "NetworkOptionsForm"
        Me.ShowInTaskbar = False
        Me.Text = "Stratego.NET"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub NetworkOptions_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ClickOptionBox(Me, New System.EventArgs())
    End Sub

    Private Sub OKButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OKButton.Click
        If PeerToPeer.Checked Then
            If local_port.TextLength > 0 And remote_port.TextLength > 0 And remote_ip.TextLength > 0 Then

            Else
                MsgBox("Local Port, Remote IP, and Remote Port values are all required.", MsgBoxStyle.OKOnly, "Error")
                Exit Sub
            End If
        ElseIf DirectClient.Checked Then
            If remote_port.TextLength = 0 Or remote_ip.TextLength = 0 Then
                MsgBox("Remote IP and Remote Port values are required.", MsgBoxStyle.OKOnly, "Error")
                Exit Sub
            End If
        ElseIf DirectHost.Checked Then
            If local_port.TextLength = 0 Then
                MsgBox("Local Port is required.", MsgBoxStyle.OKOnly, "Error")
                Exit Sub
            End If
        Else ' game server
            MsgBox("Game server is not currently supported.  Please choose peer to peer connection.", MsgBoxStyle.OKOnly, "Error")
            Exit Sub
        End If

        DialogResult = DialogResult.OK
        Close()

    End Sub

    Private Sub NetworkOptionsForm_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles MyBase.KeyPress, local_port.KeyPress, remote_ip.KeyPress, remote_port.KeyPress, server_name.KeyPress
        If e.KeyChar = Chr(13) Then
            OKButton_Click(Me, New System.EventArgs())
        End If
    End Sub

    Private Sub ClickOptionBox(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GameServer.Click, PeerToPeer.Click, DirectHost.Click, DirectClient.Click
        local_port.Enabled = DirectHost.Checked Or PeerToPeer.Checked
        remote_ip.Enabled = DirectClient.Checked Or PeerToPeer.Checked
        remote_port.Enabled = DirectClient.Checked Or PeerToPeer.Checked
        server_name.Enabled = GameServer.Checked
    End Sub
End Class
