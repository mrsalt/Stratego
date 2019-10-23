Public Class Form1
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
    Friend WithEvents function_a As System.Windows.Forms.RadioButton
    Friend WithEvents function_b As System.Windows.Forms.RadioButton
    Friend WithEvents Button1 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.function_a = New System.Windows.Forms.RadioButton()
        Me.function_b = New System.Windows.Forms.RadioButton()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'function_a
        '
        Me.function_a.Checked = True
        Me.function_a.Location = New System.Drawing.Point(24, 24)
        Me.function_a.Name = "function_a"
        Me.function_a.TabIndex = 0
        Me.function_a.TabStop = True
        Me.function_a.Text = "Red Function"
        '
        'function_b
        '
        Me.function_b.Location = New System.Drawing.Point(24, 64)
        Me.function_b.Name = "function_b"
        Me.function_b.TabIndex = 1
        Me.function_b.Text = "Blue Function"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(32, 104)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(112, 23)
        Me.Button1.TabIndex = 2
        Me.Button1.Text = "Call Function"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(176, 158)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button1, Me.function_b, Me.function_a})
        Me.Name = "Form1"
        Me.Text = "VB Learn"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Delegate Sub ReceiveMessage()
    Private fp As ReceiveMessage

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If function_a.Checked Then
            fp = AddressOf red_function
        Else
            fp = AddressOf blue_function
        End If
        fp()
    End Sub

    Private Sub red_function()
        MsgBox("red function")
    End Sub

    Private Sub blue_function()
        MsgBox("blue function")
    End Sub

End Class
