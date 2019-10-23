Public Class MessageForm
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
    Friend WithEvents SendButton As System.Windows.Forms.Button
    Friend WithEvents DataLine As System.Windows.Forms.TextBox
    Friend WithEvents LogWindow As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.SendButton = New System.Windows.Forms.Button()
        Me.DataLine = New System.Windows.Forms.TextBox()
        Me.LogWindow = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'SendButton
        '
        Me.SendButton.Location = New System.Drawing.Point(104, 232)
        Me.SendButton.Name = "SendButton"
        Me.SendButton.Size = New System.Drawing.Size(72, 24)
        Me.SendButton.TabIndex = 15
        Me.SendButton.Text = "Send"
        '
        'DataLine
        '
        Me.DataLine.Location = New System.Drawing.Point(8, 200)
        Me.DataLine.Name = "DataLine"
        Me.DataLine.Size = New System.Drawing.Size(272, 20)
        Me.DataLine.TabIndex = 14
        Me.DataLine.Text = ""
        '
        'LogWindow
        '
        Me.LogWindow.BackColor = System.Drawing.SystemColors.Window
        Me.LogWindow.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.LogWindow.Location = New System.Drawing.Point(8, 16)
        Me.LogWindow.Name = "LogWindow"
        Me.LogWindow.Size = New System.Drawing.Size(272, 168)
        Me.LogWindow.TabIndex = 13
        '
        'MessageForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(292, 266)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.SendButton, Me.DataLine, Me.LogWindow})
        Me.Name = "MessageForm"
        Me.Text = "Message History"
        Me.ResumeLayout(False)

    End Sub

#End Region

End Class
