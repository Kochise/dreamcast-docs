VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5730
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   5010
   BeginProperty Font 
      name            =   "Arial"
      charset         =   0
      weight          =   400
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   6135
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   5730
   ScaleWidth      =   5010
   Top             =   1170
   Width           =   5130
   Begin VB.CommandButton Reset 
      Caption         =   "Reset"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3600
      TabIndex        =   8
      Top             =   5040
      Width           =   1095
   End
   Begin VB.CommandButton AutoAggregateBlind 
      Caption         =   "COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND"
      Height          =   375
      Left            =   240
      TabIndex        =   7
      Top             =   4440
      Width           =   4455
   End
   Begin VB.CommandButton AggregateBlind 
      Caption         =   "COM_INTERFACE_ENTRY_AGGREGATE_BLIND"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   3840
      Width           =   4455
   End
   Begin VB.CommandButton AutoAggregate 
      Caption         =   "COM_INTERFACE_ENTRY_AUTOAGGREGATE"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   3240
      Width           =   4455
   End
   Begin VB.CommandButton Aggregate 
      Caption         =   "COM_INTERFACE_ENTRY_AGGREGATE"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   2640
      Width           =   4455
   End
   Begin VB.CommandButton Chain 
      Caption         =   "COM_INTERFACE_ENTRY_CHAIN"
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   2040
      Width           =   4455
   End
   Begin VB.CommandButton CachedTearOff 
      Caption         =   "COM_INTERFACE_ENTRY_CACHED_TEAR_OFF"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   4455
   End
   Begin VB.CommandButton TearOff 
      Caption         =   "COM_INTERFACE_ENTRY_TEAR_OFF"
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   840
      Width           =   4455
   End
   Begin VB.CommandButton BtnOffset 
      Caption         =   "COM_INTERFACE_ENTRY"
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   4455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim x As New COuter

Private Sub Command1_Click()

End Sub


Private Sub BtnReset_Click()

End Sub

Private Sub Offset_Click()

End Sub


Private Sub Label1_Click()

End Sub


Private Sub Aggregate_Click()
Aggregate.Caption = x.GetName(4)
End Sub

Private Sub AggregateBlind_Click()
AggregateBlind.Caption = x.GetName(6)
End Sub

Private Sub AutoAggregate_Click()
AutoAggregate.Caption = x.GetName(5)
End Sub

Private Sub AutoAggregateBlind_Click()
AutoAggregateBlind.Caption = x.GetName(7)
End Sub

Private Sub BtnOffset_Click()
BtnOffset.Caption = x.GetName(0)
End Sub


Private Sub CachedTearOff_Click()
CachedTearOff.Caption = x.GetName(2)
End Sub

Private Sub Chain_Click()
Chain.Caption = x.GetName(3)
End Sub

Private Sub Reset_Click()
BtnOffset.Caption = "COM_INTERFACE_ENTRY"
TearOff.Caption = "COM_INTERFACE_ENTRY_TEAR_OFF"
CachedTearOff.Caption = "COM_INTERFACE_ENTRY_CACHED_TEAR_OFF"
Chain.Caption = "COM_INTERFACE_ENTRY_CHAIN"
Aggregate.Caption = "COM_INTERFACE_ENTRY_AGGREGATE"
AutoAggregate.Caption = "COM_INTERFACE_ENTRY_AUTOAGGREGATE"
AggregateBlind.Caption = "COM_INTERFACE_ENTRY_AGGREGATE_BLIND"
AutoAggregateBlind.Caption = "COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND"
End Sub

Private Sub TearOff_Click()
TearOff.Caption = x.GetName(1)
End Sub


