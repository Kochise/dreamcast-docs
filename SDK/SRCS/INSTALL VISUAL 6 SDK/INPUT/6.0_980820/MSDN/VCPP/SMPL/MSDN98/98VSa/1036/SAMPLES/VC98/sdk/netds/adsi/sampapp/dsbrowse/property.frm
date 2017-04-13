VERSION 4.00
Begin VB.Form frmProp 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Properties"
   ClientHeight    =   4710
   ClientLeft      =   5955
   ClientTop       =   4245
   ClientWidth     =   7080
   Height          =   5115
   Left            =   5895
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4710
   ScaleWidth      =   7080
   Top             =   3900
   Width           =   7200
   Begin VB.CommandButton cmdSet 
      Caption         =   "Set"
      Height          =   375
      Left            =   5760
      TabIndex        =   13
      Top             =   4080
      Width           =   1215
   End
   Begin VB.TextBox txtValue 
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   840
      TabIndex        =   12
      Top             =   4080
      Width           =   4815
   End
   Begin VB.ListBox lstProperties 
      Appearance      =   0  'Flat
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   1950
      ItemData        =   "property.frx":0000
      Left            =   120
      List            =   "property.frx":0002
      Sorted          =   -1  'True
      TabIndex        =   9
      Top             =   1920
      Width           =   6735
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "Close"
      Height          =   375
      Left            =   5760
      TabIndex        =   8
      Top             =   480
      Width           =   975
   End
   Begin VB.Label Label8 
      Caption         =   "Value:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   4200
      Width           =   735
   End
   Begin VB.Label Label5 
      Caption         =   "Properties"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   1560
      Width           =   3255
   End
   Begin VB.Label lblIsContainer 
      BackColor       =   &H00C0C0C0&
      Height          =   255
      Left            =   1200
      TabIndex        =   7
      Top             =   1200
      Width           =   1935
   End
   Begin VB.Label lblClass 
      BackColor       =   &H00C0C0C0&
      Height          =   255
      Left            =   1200
      TabIndex        =   6
      Top             =   840
      Width           =   4575
   End
   Begin VB.Label lblPath 
      BackColor       =   &H00C0C0C0&
      Height          =   255
      Left            =   1200
      TabIndex        =   5
      Top             =   480
      Width           =   4575
   End
   Begin VB.Label lblName 
      BackColor       =   &H00C0C0C0&
      Height          =   255
      Left            =   1200
      TabIndex        =   4
      Top             =   120
      Width           =   1935
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      Caption         =   "IsContainer:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
      Caption         =   "Class:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   855
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      Caption         =   "ADsPath:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   855
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      Caption         =   "Name:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "frmProp"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Private Sub cmdCancel_Click()
'
' Allow user to cancel
'

    Unload Me
End Sub

Private Sub cmdOK_Click()
'
' Allow user to close form
'
    
    Unload Me
End Sub


Private Sub cmdSet_Click()
'
' Process Set Property command
'
    Dim strProp As String
    Dim strSyntax As String
    Dim strOld As String
    Dim Val As Variant
    Dim I As Integer
    Dim pos1 As Integer  'Finds "(" in string to locate syntax
    Dim pos2 As Integer  'Finds ")" in string to locate syntax
    '
    ' Set error handling
    '
    On Error Resume Next
    
    I = lstProperties.ListIndex
    If currentADsObj Is Nothing Then
        '
        ' There is no object associated with this interface.
        ' Do nothing.
        '
        GoTo finish
        
    End If
    '
    'Need to strip Prop off Prop(SYNTAX):Value
    '
    strOld = lstProperties.Text
    pos1 = InStr(strOld, "(")
    pos2 = InStr(pos1, strOld, ")")
    strSyntax = Right(strOld, (Len(strOld) - pos1))
    strSyntax = Left(strSyntax, ((pos2 - pos1) - 1))
    strProp = Left(strOld, (pos1 - 1))
    If (strSyntax = "ADsPath") Or (strSyntax = "String") Or (strSyntax = "DirectoryString") Then
        Val = txtValue.Text
    ElseIf (strSyntax = "Counter") Or (strSyntax = "Integer") _
            Or (strSyntax = "Interval") Then
        Val = CLng(txtValue.Text)
    ElseIf (strSyntax = "SmallInterval") Then
        Val = CLng(txtValue.Text)
    ElseIf (strSyntax = "List") Or (strSyntax = "OctetString") Then
        Val = CVar(txtValue.Text)
    ElseIf (strSyntax = "PhoneNumber") Or (strSyntax = "PostalAddress") Then
        Val = txtValue.Text
    ElseIf strSyntax = "Boolean" Then
        Val = CBool(txtValue.Text)
    ElseIf (strSyntax = "EmailAddress") Or (strSyntax = "FaxNumber") Then
        Val = txtValue.Text
    ElseIf strSyntax = "NetAddress" Or strSyntax = "Path" Then
        Val = txtValue.Text
    ElseIf strSyntax = "Time" Then
        Val = CDate(txtValue.Text)
    Else
        '
        ' If none of the syntax cases above are found we bail out silently
        '
        GoTo finish
    End If
    strOld = Left(strOld, (pos2 + 1)) & txtValue.Text
    currentADsObj.Put strProp, Val
    Err = 0
    currentADsObj.SetInfo
    If Err Then
        MsgBox "Could not Set Property, check access "
        GoTo finish
    End If
    lstProperties.RemoveItem I
    lstProperties.AddItem strOld, I
    
finish:
End Sub

Private Sub Form_Load()
    
    '
    ' User cannot bring up second properties dialog box
    '
        frmBrwsTree.cmdProperties.Enabled = False
End Sub

Private Sub Form_Unload(Cancel As Integer)

    '
    ' Enable properties command
    '
    frmBrwsTree.cmdProperties.Enabled = True
End Sub


Private Sub lstProperties_Click()
'
'Do on Properties command
'
    Dim pos1 As Integer
    Dim pos2 As Integer
    Dim strVal As String
    Dim strTemp As String
    
    On Error GoTo finish
    
    strTemp = lstProperties.List(lstProperties.ListIndex)
    pos1 = InStr(strTemp, "(")
    pos2 = InStr(pos1, strTemp, ")")
    pos1 = InStr(pos2, strTemp, ":")
    strVal = Right(strTemp, (Len(strTemp) - pos1))
    
    txtValue.Text = strVal
    frmProp.Refresh
finish:
End Sub
