VERSION 5.00
Begin VB.Form SelectColorForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Select Color"
   ClientHeight    =   1620
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   4635
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1620
   ScaleWidth      =   4635
   ShowInTaskbar   =   0   'False
   Begin VB.OptionButton ColorSelection 
      Caption         =   "Blue"
      Height          =   495
      Index           =   1
      Left            =   360
      TabIndex        =   3
      Top             =   720
      Width           =   1575
   End
   Begin VB.OptionButton ColorSelection 
      Caption         =   "Red"
      Height          =   495
      Index           =   0
      Left            =   360
      TabIndex        =   2
      Top             =   240
      Value           =   -1  'True
      Width           =   1695
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3240
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   3240
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "SelectColorForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Public Result As Boolean

Private Sub CancelButton_Click()
    Result = False
    Me.Hide
End Sub

Private Sub OKButton_Click()
    Result = True
    Me.Hide
End Sub
