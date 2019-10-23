Option Explicit On 

Public MustInherit Class gameConnection
    Public SendBox As TextBox
    Public ReceiveBox As TextBox

    Delegate Sub ReceiveMessageFunction(ByVal messageType As StrategoMessageType, ByVal mParams() As Object)
    Protected ReceiveMessage As ReceiveMessageFunction
    Private messageId As Integer = 0
    Public connectionState As connectionStateType = connectionStateType.not_connected

    Public Enum connectionStateType
        not_connected
        connected
    End Enum

    Function SendMessage(ByVal messageType As StrategoMessageType, ByVal ParamArray params() As Object) As Integer
        Dim ackRequired As Boolean = False
        Dim messageParams(3) As Object

        messageId = messageId + 1

        'If (messageType = StrategoMessageType.StartGame) Then
        'ackRequired = True
        'End If

        messageParams(0) = messageId
        messageParams(1) = messageType
        messageParams(2) = ackRequired
        messageParams(3) = params

        'Console.WriteLine("Sending Message, id=" & messageId & ", type=" & messageType & ", ackRequired=" & ackRequired)
        If Not (SendBox Is Nothing And SendBox.Visible) Then
            Dim sendmsg As String = "sent: message id=" & messageId & ", type=" & messageType & ", param count=" & params.Length
            SendBox.AppendText(sendmsg & Chr(13) & Chr(10))
        End If

        If (Send(messageParams)) Then
            Return messageId
        Else
            Return 0
        End If
    End Function

    Protected Sub ProcessReceiveData(ByVal params() As Object)
        Dim messageId As Integer
        Dim messageType As StrategoDefinitions.StrategoMessageType
        Dim ackRequired As Boolean
        Dim messageParams() As Object

        messageId = params(0)
        messageType = params(1)
        ackRequired = params(2)
        messageParams = params(3)

        If connectionState = connectionStateType.not_connected Then
            connectionState = connectionStateType.connected
        End If

        'If (ackRequired) Then
        'SendMessage(StrategoDefinitions.StrategoMessageType.Ack, False, New Object() {messageId})
        'End If
        Dim receiveMsg As String = "received: message id=" & messageId & ", mType=" & messageType & ", param count=" & params.Length
        Console.WriteLine(receiveMsg)
        If Not (ReceiveBox Is Nothing And ReceiveBox.Visible) Then
            ReceiveBox.AppendText(receiveMsg & Chr(13) & Chr(10))
        End If
        ReceiveMessage.Invoke(messageType, messageParams)

    End Sub

    Protected MustOverride Function Send(ByVal msgData() As Object)

End Class
