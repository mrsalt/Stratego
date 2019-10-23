Public Class SelectColorDialog
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
    Friend WithEvents OKButton As System.Windows.Forms.Button
    Friend WithEvents Cancel As System.Windows.Forms.Button
    Friend WithEvents RedSelection As System.Windows.Forms.RadioButton
    Friend WithEvents BlueSelection As System.Windows.Forms.RadioButton
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.RedSelection = New System.Windows.Forms.RadioButton()
        Me.BlueSelection = New System.Windows.Forms.RadioButton()
        Me.OKButton = New System.Windows.Forms.Button()
        Me.Cancel = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'RedSelection
        '
        Me.RedSelection.Checked = True
        Me.RedSelection.Location = New System.Drawing.Point(16, 16)
        Me.RedSelection.Name = "RedSelection"
        Me.RedSelection.Size = New System.Drawing.Size(120, 24)
        Me.RedSelection.TabIndex = 0
        Me.RedSelection.TabStop = True
        Me.RedSelection.Text = "Red"
        '
        'BlueSelection
        '
        Me.BlueSelection.Location = New System.Drawing.Point(16, 48)
        Me.BlueSelection.Name = "BlueSelection"
        Me.BlueSelection.Size = New System.Drawing.Size(120, 24)
        Me.BlueSelection.TabIndex = 1
        Me.BlueSelection.Text = "Blue"
        '
        'OKButton
        '
        Me.OKButton.Location = New System.Drawing.Point(184, 16)
        Me.OKButton.Name = "OKButton"
        Me.OKButton.Size = New System.Drawing.Size(88, 24)
        Me.OKButton.TabIndex = 2
        Me.OKButton.Text = "OK"
        '
        'Cancel
        '
        Me.Cancel.Location = New System.Drawing.Point(184, 56)
        Me.Cancel.Name = "Cancel"
        Me.Cancel.Size = New System.Drawing.Size(88, 24)
        Me.Cancel.TabIndex = 3
        Me.Cancel.Text = "Cancel"
        '
        'SelectColorDialog
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(288, 102)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Cancel, Me.OKButton, Me.BlueSelection, Me.RedSelection})
        Me.Name = "SelectColorDialog"
        Me.Text = "Select Color"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub OKButton_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles OKButton.Click
        DialogResult = DialogResult.OK
        Close()
    End Sub

    Private Sub Cancel_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles Cancel.Click
        DialogResult = DialogResult.Cancel
        Close()
    End Sub

    Public Property Color()
        Get
            If Me.RedSelection.Checked = True Then
                Return ColorEnum.Red
            End If
        End Get
        Set(ByVal Value)
            If Value = ColorEnum.Red Then
                RedSelection.Checked = True
            ElseIf Value = ColorEnum.Blue Then
                BlueSelection.Checked = True
            End If
        End Set
    End Property

End Class
