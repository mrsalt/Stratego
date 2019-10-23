Public Class StrategoRulesForm
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
    Friend WithEvents MemoryChallenged As System.Windows.Forms.CheckBox
    Friend WithEvents UseRulesButton As System.Windows.Forms.Button
    Friend WithEvents ShowCapturedPieces As System.Windows.Forms.CheckBox
    Friend WithEvents AgressorAdvantadge As System.Windows.Forms.CheckBox
    Friend WithEvents SilentDefense As System.Windows.Forms.CheckBox
    Friend WithEvents Rescue As System.Windows.Forms.CheckBox
    Friend WithEvents ToolTip1 As System.Windows.Forms.ToolTip
    Friend WithEvents status_message As System.Windows.Forms.Label
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(StrategoRulesForm))
        Me.Label1 = New System.Windows.Forms.Label()
        Me.MemoryChallenged = New System.Windows.Forms.CheckBox()
        Me.ShowCapturedPieces = New System.Windows.Forms.CheckBox()
        Me.AgressorAdvantadge = New System.Windows.Forms.CheckBox()
        Me.SilentDefense = New System.Windows.Forms.CheckBox()
        Me.Rescue = New System.Windows.Forms.CheckBox()
        Me.UseRulesButton = New System.Windows.Forms.Button()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.status_message = New System.Windows.Forms.Label()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.Color.Transparent
        Me.Label1.Font = New System.Drawing.Font("Herald", 24.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(76, 96)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(280, 40)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Rules"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'MemoryChallenged
        '
        Me.MemoryChallenged.BackColor = System.Drawing.Color.Transparent
        Me.MemoryChallenged.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.MemoryChallenged.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.MemoryChallenged.Location = New System.Drawing.Point(88, 160)
        Me.MemoryChallenged.Name = "MemoryChallenged"
        Me.MemoryChallenged.Size = New System.Drawing.Size(256, 24)
        Me.MemoryChallenged.TabIndex = 1
        Me.MemoryChallenged.Text = "Memory Challenged"
        Me.ToolTip1.SetToolTip(Me.MemoryChallenged, "After pieces battle, rank of enemy piece will remain visible")
        '
        'ShowCapturedPieces
        '
        Me.ShowCapturedPieces.BackColor = System.Drawing.Color.Transparent
        Me.ShowCapturedPieces.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.ShowCapturedPieces.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ShowCapturedPieces.Location = New System.Drawing.Point(88, 200)
        Me.ShowCapturedPieces.Name = "ShowCapturedPieces"
        Me.ShowCapturedPieces.Size = New System.Drawing.Size(256, 24)
        Me.ShowCapturedPieces.TabIndex = 2
        Me.ShowCapturedPieces.Text = "Show Captured Pieces"
        Me.ToolTip1.SetToolTip(Me.ShowCapturedPieces, "All captured pieces will be displayed")
        '
        'AgressorAdvantadge
        '
        Me.AgressorAdvantadge.BackColor = System.Drawing.Color.Transparent
        Me.AgressorAdvantadge.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.AgressorAdvantadge.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.AgressorAdvantadge.Location = New System.Drawing.Point(88, 240)
        Me.AgressorAdvantadge.Name = "AgressorAdvantadge"
        Me.AgressorAdvantadge.Size = New System.Drawing.Size(256, 24)
        Me.AgressorAdvantadge.TabIndex = 3
        Me.AgressorAdvantadge.Text = "Aggressor Advantadge"
        Me.ToolTip1.SetToolTip(Me.AgressorAdvantadge, "When pieces of the same rank battle, the attacking piece wins")
        '
        'SilentDefense
        '
        Me.SilentDefense.BackColor = System.Drawing.Color.Transparent
        Me.SilentDefense.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.SilentDefense.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.SilentDefense.Location = New System.Drawing.Point(88, 280)
        Me.SilentDefense.Name = "SilentDefense"
        Me.SilentDefense.Size = New System.Drawing.Size(256, 24)
        Me.SilentDefense.TabIndex = 4
        Me.SilentDefense.Text = "Silent Defense"
        Me.ToolTip1.SetToolTip(Me.SilentDefense, "During battle, defender does not reveal rank.  Exception: when a Scout strikes, t" & _
        "he defender's rank is revealed")
        '
        'Rescue
        '
        Me.Rescue.BackColor = System.Drawing.Color.Transparent
        Me.Rescue.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.Rescue.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Rescue.Location = New System.Drawing.Point(88, 320)
        Me.Rescue.Name = "Rescue"
        Me.Rescue.Size = New System.Drawing.Size(256, 24)
        Me.Rescue.TabIndex = 5
        Me.Rescue.Text = "Rescue"
        Me.ToolTip1.SetToolTip(Me.Rescue, "When you move onto a square in your opponent's back row you may rescue one of you" & _
        "r captured pieces. Your rescued piece goes on any unoccupied space on your half " & _
        "of the gameboard and your turn is over.  Restrictions:  Scouts cannot make a res" & _
        "cue.  You cannot rescue a bomb.  Each player can make only two rescues.  The sam" & _
        "e piece cannot make both rescues.")
        '
        'UseRulesButton
        '
        Me.UseRulesButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup
        Me.UseRulesButton.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.UseRulesButton.Location = New System.Drawing.Point(132, 352)
        Me.UseRulesButton.Name = "UseRulesButton"
        Me.UseRulesButton.Size = New System.Drawing.Size(168, 32)
        Me.UseRulesButton.TabIndex = 6
        Me.UseRulesButton.Text = "Use Default Rules"
        '
        'status_message
        '
        Me.status_message.BackColor = System.Drawing.Color.Transparent
        Me.status_message.Font = New System.Drawing.Font("Arial", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.status_message.Location = New System.Drawing.Point(104, 360)
        Me.status_message.Name = "status_message"
        Me.status_message.Size = New System.Drawing.Size(288, 32)
        Me.status_message.TabIndex = 7
        Me.status_message.Text = "Mark is setting rules"
        Me.status_message.Visible = False
        '
        'PictureBox1
        '
        Me.PictureBox1.Location = New System.Drawing.Point(16, 344)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(56, 48)
        Me.PictureBox1.TabIndex = 8
        Me.PictureBox1.TabStop = False
        '
        'StrategoRulesForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Bitmap)
        Me.ClientSize = New System.Drawing.Size(432, 406)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.PictureBox1, Me.status_message, Me.UseRulesButton, Me.Rescue, Me.SilentDefense, Me.AgressorAdvantadge, Me.ShowCapturedPieces, Me.MemoryChallenged, Me.Label1})
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "StrategoRulesForm"
        Me.Text = "StrategoRules"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub UseRulesButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UseRulesButton.Click
        Close()
    End Sub

    Private Sub CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MemoryChallenged.CheckedChanged, AgressorAdvantadge.CheckedChanged, ShowCapturedPieces.CheckedChanged, SilentDefense.CheckedChanged, Rescue.CheckedChanged
        If MemoryChallenged.Checked Or AgressorAdvantadge.Checked Or ShowCapturedPieces.Checked Or SilentDefense.Checked Or Rescue.Checked Then  'CType(sender, Windows.Forms.CheckBox).Checked
            UseRulesButton.Text = "Use Custom Rules"
        Else
            UseRulesButton.Text = "Use Default Rules"
        End If
    End Sub

    Public Sub AllowRulesChange(ByVal enableChange As Boolean)
        MemoryChallenged.Enabled = enableChange
        AgressorAdvantadge.Enabled = enableChange
        ShowCapturedPieces.Enabled = enableChange
        SilentDefense.Enabled = enableChange
        Rescue.Enabled = enableChange

        MemoryChallenged.Checked = False
        AgressorAdvantadge.Checked = False
        ShowCapturedPieces.Checked = False
        SilentDefense.Checked = False
        Rescue.Checked = False

        UseRulesButton.Enabled = False
        'CType(sender, Windows.Forms.CheckBox).Checked
    End Sub
End Class
