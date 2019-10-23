Imports System.Net.Sockets
Imports System.IO
Imports System.Threading
Imports System.Runtime.Serialization.Formatters


Public Class PeerToPeerConnection
    Inherits gameConnection

    Private RemoteIP As String
    Private RemotePort As Integer
    Private LocalPort As Integer

    Private thdListener As Thread
    Private objListener As TcpListener
    Private objClient As TcpClient
    Private clientConnected As Boolean = False

    Private executing = True
    Private BinFormatter As New Binary.BinaryFormatter()

    Protected Overrides Function Send(ByVal msgData() As Object)
        Dim result As Boolean = True
        Try            
            If Not clientConnected Then
                objClient.Connect(RemoteIP, RemotePort)
                clientConnected = True
            End If

            BinFormatter.Serialize(objClient.GetStream(), msgData)

        Catch socketException As System.Net.Sockets.SocketException
            Dim errorc As Integer = socketException.ErrorCode
            'Console.WriteLine(socketException.ToString())
            clientConnected = False
            result = False
        End Try
        Return result
    End Function

    Public Sub New(ByVal ReceiveFunction As ReceiveMessageFunction, ByVal _remoteIP As String, ByVal _remotePort As Integer, ByVal _localPort As Integer)
        ReceiveMessage = ReceiveFunction
        RemoteIP = _remoteIP
        RemotePort = _remotePort
        LocalPort = _localPort

        thdListener = New Thread(AddressOf Me.Listen)
        thdListener.Start()

        objClient = New TcpClient()
    End Sub

    Private Sub Listen() ' run on separate thread
        Dim tid As Int32 = Thread.CurrentThread.GetDomainID()
        Dim strTemp As String
        objListener = New TcpListener(LocalPort)
        objListener.Start()
        Dim receiveParams() As Object
        Try
            Dim objClient As TcpClient = objListener.AcceptTcpClient()
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
        objListener.Stop()
        'objClient.Close()
        MyBase.Finalize()
    End Sub
End Class
