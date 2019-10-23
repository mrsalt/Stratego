Imports System.Net.Sockets
Imports System.IO
Imports System.Threading

Public Class Chat
    Inherits System.Windows.Forms.Form

    Private config As MessengerConfigForm

    Private thdListener As Thread
    Private objListener As TcpListener
    Private executing = True

    'public delegate Invoker( t as String)
    'Public Delegate Sub ReceiveMessage(ByVal m As String)
    'Event ReceiveMessage(ByVal message As String)
    Delegate Sub ReceiveMessageDelegate(ByVal x As String)

    Public Sub ReceiveMessage(ByVal message As String)
        Dim threadID As Integer = Thread.CurrentThread.GetDomainID()
        Messages.Text += "Received: " + Chr(13) + "   " + message
    End Sub

    Public Sub Listen() ' run on separate thread
        Dim tid As Int32 = Thread.CurrentThread.GetDomainID()
        Dim strTemp As String
        Dim localPort As Int16 = config.GetLocalPort()
        objListener = New TcpListener(localPort)
        objListener.Start()

        Do
            Try
                Dim objClient As TcpClient = objListener.AcceptTcpClient()
                Dim objReader As StreamReader = New StreamReader(objClient.GetStream())

                Do While objReader.Peek() <> -1
                    strTemp += Convert.ToChar(objReader.Read()).ToString()
                Loop

                Dim rmd As ReceiveMessageDelegate = AddressOf Me.ReceiveMessage
                rmd.Invoke(strTemp)

                'object[] objParams = new object[] {strTemp};
                strTemp = ""
                objClient.Close()
            Catch

            End Try

            
            'this.Invoke(new Invoker(this.ShowMessage), objParams);
            'Me.Invoke(
            'Messages.Text += strTemp
        Loop While executing

    End Sub

#Region " Windows Form Designer generated code "

    Public Sub New(ByVal parentForm As MessengerConfigForm)

        MyBase.New()
        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call
        config = parentForm

        thdListener = New Thread(AddressOf Me.Listen)
        thdListener.Start()

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
    Friend WithEvents SendButton As System.Windows.Forms.Button
    Friend WithEvents Messages As System.Windows.Forms.RichTextBox
    Friend WithEvents Type As System.Windows.Forms.RichTextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.SendButton = New System.Windows.Forms.Button()
        Me.Messages = New System.Windows.Forms.RichTextBox()
        Me.Type = New System.Windows.Forms.RichTextBox()
        Me.SuspendLayout()
        '
        'SendButton
        '
        Me.SendButton.Location = New System.Drawing.Point(216, 240)
        Me.SendButton.Name = "SendButton"
        Me.SendButton.Size = New System.Drawing.Size(64, 72)
        Me.SendButton.TabIndex = 0
        Me.SendButton.Text = "Send"
        '
        'Messages
        '
        Me.Messages.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Messages.Location = New System.Drawing.Point(8, 8)
        Me.Messages.Name = "Messages"
        Me.Messages.Size = New System.Drawing.Size(272, 224)
        Me.Messages.TabIndex = 1
        Me.Messages.Text = ""
        '
        'Type
        '
        Me.Type.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Type.Location = New System.Drawing.Point(8, 240)
        Me.Type.Name = "Type"
        Me.Type.Size = New System.Drawing.Size(200, 72)
        Me.Type.TabIndex = 2
        Me.Type.Text = ""
        '
        'Chat
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(292, 318)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Type, Me.Messages, Me.SendButton})
        Me.Name = "Chat"
        Me.Text = "Chat"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub SendButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SendButton.Click
        Dim tid As Int32 = Thread.CurrentThread.GetDomainID()
        If (Type.TextLength > 0) Then
            Dim message As String
            message = Type.Text + Chr(13)
            Messages.Text = Messages.Text + "Sent: " + Chr(13) + "   " + message
            Dim remoteIP As String = config.GetRemoteIP()
            Dim remotePort As String = config.GetRemotePort()

            Dim objClient As TcpClient = New TcpClient(remoteIP, remotePort)
            Dim w As StreamWriter = New StreamWriter(objClient.GetStream())
            w.Write(message)
            w.Flush()
            objClient.Close()
            Type.Text = ""
        End If
    End Sub

    Private Sub Chat_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        executing = False
        objListener.Stop()
    End Sub

    Private Sub Type_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles Type.KeyPress
        If e.KeyChar = Chr(13) Then
            Type.Text = Type.Text.Remove(Type.Text.Length - 1, 1)
            SendButton_Click(Me, New System.EventArgs())
        End If
    End Sub

    Protected Overrides Sub OnSizeChanged(ByVal e As System.EventArgs)

        Messages.Size = New Size(Width - 28, Height - 128)
        Type.Top = Height - 112
        Type.Width = Width - 100
        SendButton.Location = New Point(Width - 84, Height - 112)
    End Sub
End Class
