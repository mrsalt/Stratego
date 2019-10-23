Imports System.Net.Sockets
Imports System.IO
Imports System.Threading
Imports System.Runtime.Serialization.Formatters

Public Class DirectConnection
    Inherits gameConnection

    Private RemoteIP As String
    Private RemotePort As Integer
    Private LocalPort As Integer

    Private thdListener As Thread
    Private objListener As TcpListener
    Private objClient As TcpClient
    Private isConnected As Boolean = False

    Private executing = True
    Private BinFormatter As New Binary.BinaryFormatter()

    Private IsClient As Boolean

    Protected Overrides Function Send(ByVal msgData() As Object)
        Dim result As Boolean = True
        Try
            If IsClient Then
                If Not isConnected Then
                    objClient = New TcpClient(RemoteIP, RemotePort)
                    isConnected = True
                    thdListener = New Thread(AddressOf Me.Listen)
                    thdListener.Start()
                End If
            ElseIf Not isConnected Then
                Return False
            End If

            BinFormatter.Serialize(objClient.GetStream(), msgData)

        Catch socketException As System.Net.Sockets.SocketException
            Dim errorc As Integer = socketException.ErrorCode
            'Console.WriteLine(socketException.ToString())
            If IsClient Then
                isConnected = False
            Else ' I am a server - my client has gone away

            End If
            result = False
        End Try
        Return result
    End Function

    Public Sub New(ByVal ReceiveFunction As ReceiveMessageFunction, ByVal _localPort As Integer)
        ' we are the server
        IsClient = False
        ReceiveMessage = ReceiveFunction
        LocalPort = _localPort

        thdListener = New Thread(AddressOf Me.Listen)
        thdListener.Start()
    End Sub

    Public Sub New(ByVal ReceiveFunction As ReceiveMessageFunction, ByVal _remoteIP As String, ByVal _remotePort As Integer)
        ' we are the client
        IsClient = True
        ReceiveMessage = ReceiveFunction
        RemoteIP = _remoteIP
        RemotePort = _remotePort
    End Sub

    Private Sub Listen() ' run on separate thread

        Dim receiveParams() As Object
        Try
            If Not IsClient Then
                objListener = New TcpListener(LocalPort)
                objListener.Start()
                objClient = objListener.AcceptTcpClient()
                isConnected = True
            End If

            Do
                receiveParams = BinFormatter.Deserialize(objClient.GetStream())
                'Console.WriteLine("PeerToPeerConnection.Listen(), data received")
                ProcessReceiveData(receiveParams)
            Loop While executing

            objClient.Close()
        Catch e As Exception
            Console.Write(e.ToString())
        End Try
    End Sub

    Protected Overrides Sub Finalize()
        'Console.Write("Stopping listener")
        executing = False
        If isConnected Then
            If Not IsClient Then objListener.Stop()
            objClient.Close()
        End If
        MyBase.Finalize()
    End Sub

End Class
