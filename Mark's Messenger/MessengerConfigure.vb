Imports System.Net
Imports System.Net.Sockets
Imports System.Threading
Imports System.IO
Imports System.ComponentModel

Public Class MessengerConfigForm
    Inherits System.Windows.Forms.Form

    Private mySock As Socket
    Private chatForm As Chat

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
    Friend WithEvents TextBox3 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents ConnectButton As System.Windows.Forms.Button
    Friend WithEvents listenPort As System.Windows.Forms.TextBox
    Friend WithEvents remoteIP As System.Windows.Forms.TextBox
    Friend WithEvents remotePort As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.listenPort = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.TextBox3 = New System.Windows.Forms.TextBox()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.ConnectButton = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.remoteIP = New System.Windows.Forms.TextBox()
        Me.remotePort = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 16)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(96, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "My IP Address is:"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 48)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(96, 16)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Listen on port:"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'listenPort
        '
        Me.listenPort.Location = New System.Drawing.Point(120, 48)
        Me.listenPort.Name = "listenPort"
        Me.listenPort.Size = New System.Drawing.Size(64, 20)
        Me.listenPort.TabIndex = 1
        Me.listenPort.Text = "1570"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(32, 144)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(72, 16)
        Me.Label3.TabIndex = 4
        Me.Label3.Text = "Status:"
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'TextBox3
        '
        Me.TextBox3.Location = New System.Drawing.Point(120, 144)
        Me.TextBox3.Name = "TextBox3"
        Me.TextBox3.ReadOnly = True
        Me.TextBox3.Size = New System.Drawing.Size(120, 20)
        Me.TextBox3.TabIndex = 5
        Me.TextBox3.TabStop = False
        Me.TextBox3.Text = ""
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(120, 16)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ReadOnly = True
        Me.TextBox1.Size = New System.Drawing.Size(120, 20)
        Me.TextBox1.TabIndex = 6
        Me.TextBox1.TabStop = False
        Me.TextBox1.Text = ""
        '
        'ConnectButton
        '
        Me.ConnectButton.Location = New System.Drawing.Point(96, 184)
        Me.ConnectButton.Name = "ConnectButton"
        Me.ConnectButton.Size = New System.Drawing.Size(96, 24)
        Me.ConnectButton.TabIndex = 4
        Me.ConnectButton.Text = "Connect"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 112)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(96, 16)
        Me.Label4.TabIndex = 8
        Me.Label4.Text = "Remote Port:"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(16, 80)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(96, 16)
        Me.Label5.TabIndex = 9
        Me.Label5.Text = "Remote IP:"
        Me.Label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'remoteIP
        '
        Me.remoteIP.Location = New System.Drawing.Point(120, 80)
        Me.remoteIP.Name = "remoteIP"
        Me.remoteIP.Size = New System.Drawing.Size(116, 20)
        Me.remoteIP.TabIndex = 2
        Me.remoteIP.Text = "127.0.0.1"
        '
        'remotePort
        '
        Me.remotePort.Location = New System.Drawing.Point(120, 112)
        Me.remotePort.Name = "remotePort"
        Me.remotePort.Size = New System.Drawing.Size(64, 20)
        Me.remotePort.TabIndex = 3
        Me.remotePort.Text = "1570"
        '
        'MessengerConfigForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(288, 230)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.remotePort, Me.remoteIP, Me.Label5, Me.Label4, Me.ConnectButton, Me.TextBox1, Me.TextBox3, Me.Label3, Me.listenPort, Me.Label2, Me.Label1})
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "MessengerConfigForm"
        Me.Text = "Mark's Messenger Configuration"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub ConnectButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ConnectButton.Click
        chatForm = New Chat(Me)
        chatForm.ShowDialog(Me)
    End Sub

    Public Function GetRemoteIP() As String
        Return remoteIP.Text
    End Function

    Public Function GetRemotePort() As Int16
        Return remotePort.Text
    End Function

    Public Function GetLocalPort() As Int16
        Return listenPort.Text
    End Function

    Private Sub MessengerConfigForm_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub
End Class
