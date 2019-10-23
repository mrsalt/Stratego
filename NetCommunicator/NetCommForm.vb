Public Class NetCommForm
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
    Friend WithEvents winsoc As AxMSWinsockLib.AxWinsock
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents ConnectionStatus As System.Windows.Forms.Label
    Friend WithEvents ConnectButton As System.Windows.Forms.Button
    Friend WithEvents LocalPort As System.Windows.Forms.TextBox
    Friend WithEvents RemoteIP As System.Windows.Forms.TextBox
    Friend WithEvents RemotePort As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(NetCommForm))
        Me.winsoc = New AxMSWinsockLib.AxWinsock()
        Me.LocalPort = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.RemoteIP = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.RemotePort = New System.Windows.Forms.TextBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.ConnectionStatus = New System.Windows.Forms.Label()
        Me.ConnectButton = New System.Windows.Forms.Button()
        CType(Me.winsoc, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'winsoc
        '
        Me.winsoc.Enabled = True
        Me.winsoc.Location = New System.Drawing.Point(192, 16)
        Me.winsoc.Name = "winsoc"
        Me.winsoc.OcxState = CType(resources.GetObject("winsoc.OcxState"), System.Windows.Forms.AxHost.State)
        Me.winsoc.Size = New System.Drawing.Size(28, 28)
        Me.winsoc.TabIndex = 0
        '
        'LocalPort
        '
        Me.LocalPort.Location = New System.Drawing.Point(104, 24)
        Me.LocalPort.Name = "LocalPort"
        Me.LocalPort.Size = New System.Drawing.Size(72, 20)
        Me.LocalPort.TabIndex = 1
        Me.LocalPort.Text = ""
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(16, 24)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(80, 16)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Local Port"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(16, 56)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 20)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "Remote IP"
        '
        'RemoteIP
        '
        Me.RemoteIP.Location = New System.Drawing.Point(104, 56)
        Me.RemoteIP.Name = "RemoteIP"
        Me.RemoteIP.Size = New System.Drawing.Size(72, 20)
        Me.RemoteIP.TabIndex = 4
        Me.RemoteIP.Text = ""
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 88)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(72, 16)
        Me.Label3.TabIndex = 5
        Me.Label3.Text = "Remote Port"
        '
        'RemotePort
        '
        Me.RemotePort.Location = New System.Drawing.Point(104, 88)
        Me.RemotePort.Name = "RemotePort"
        Me.RemotePort.Size = New System.Drawing.Size(72, 20)
        Me.RemotePort.TabIndex = 6
        Me.RemotePort.Text = ""
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(16, 120)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(72, 16)
        Me.Label5.TabIndex = 10
        Me.Label5.Text = "Status"
        '
        'ConnectionStatus
        '
        Me.ConnectionStatus.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.ConnectionStatus.Location = New System.Drawing.Point(104, 120)
        Me.ConnectionStatus.Name = "ConnectionStatus"
        Me.ConnectionStatus.Size = New System.Drawing.Size(120, 16)
        Me.ConnectionStatus.TabIndex = 11
        Me.ConnectionStatus.Text = "No Connection"
        '
        'ConnectButton
        '
        Me.ConnectButton.Location = New System.Drawing.Point(72, 152)
        Me.ConnectButton.Name = "ConnectButton"
        Me.ConnectButton.Size = New System.Drawing.Size(96, 24)
        Me.ConnectButton.TabIndex = 12
        Me.ConnectButton.Text = "Connect"
        '
        'NetCommForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.AutoScroll = True
        Me.ClientSize = New System.Drawing.Size(240, 190)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.ConnectButton, Me.ConnectionStatus, Me.Label5, Me.RemotePort, Me.Label3, Me.RemoteIP, Me.Label2, Me.Label1, Me.LocalPort, Me.winsoc})
        Me.Name = "NetCommForm"
        Me.Text = "Net Communicator"
        CType(Me.winsoc, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub ConnectButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ConnectButton.Click
        winsoc.RemoteHost = RemoteIP.Text
        winsoc.RemotePort = RemotePort.Text
        ConnectionStatus.Text = "Connecting..."
        winsoc.Connect()
    End Sub

    Private Sub winsoc_ConnectEvent(ByVal sender As Object, ByVal e As System.EventArgs) Handles winsoc.ConnectEvent
        winsoc.con()
    End Sub

    Private Sub winsoc_CloseEvent(ByVal sender As Object, ByVal e As System.EventArgs) Handles winsoc.CloseEvent

    End Sub

    Private Sub winsoc_ConnectionRequest(ByVal sender As Object, ByVal e As AxMSWinsockLib.DMSWinsockControlEvents_ConnectionRequestEvent) Handles winsoc.ConnectionRequest

    End Sub

    Private Sub winsoc_DataArrival(ByVal sender As Object, ByVal e As AxMSWinsockLib.DMSWinsockControlEvents_DataArrivalEvent) Handles winsoc.DataArrival

    End Sub

End Class
