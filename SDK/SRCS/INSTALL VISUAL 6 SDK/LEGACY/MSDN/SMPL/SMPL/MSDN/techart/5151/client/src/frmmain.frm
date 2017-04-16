VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Generator"
   ClientHeight    =   2835
   ClientLeft      =   1110
   ClientTop       =   1380
   ClientWidth     =   6525
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2835
   ScaleWidth      =   6525
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.ProgressBar pbMain 
      Height          =   255
      Left            =   4560
      TabIndex        =   7
      Top             =   2575
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   450
      _Version        =   327680
      Appearance      =   1
      MouseIcon       =   "frmmain.frx":0000
      Max             =   1000
   End
   Begin ComctlLib.StatusBar sbMain 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   8
      Top             =   2580
      Width           =   6525
      _ExtentX        =   11509
      _ExtentY        =   450
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   7056
            MinWidth        =   7056
            Text            =   "Ready"
            TextSave        =   "Ready"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      MouseIcon       =   "frmmain.frx":001C
   End
   Begin VB.TextBox txtTpl 
      Height          =   285
      Left            =   120
      TabIndex        =   2
      Text            =   "c:\intgen\client\res"
      Top             =   1800
      Width           =   4485
   End
   Begin VB.TextBox txtIn 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Text            =   "c:\intgen\db\intgen.mdb"
      Top             =   270
      Width           =   4485
   End
   Begin VB.CommandButton btGen 
      Caption         =   "Generate"
      Height          =   465
      Left            =   5400
      TabIndex        =   4
      Top             =   240
      Width           =   1035
   End
   Begin VB.TextBox txtOut 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Text            =   "c:\intgen\output"
      Top             =   990
      Width           =   4485
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Template Root Path"
      Height          =   195
      Index           =   2
      Left            =   135
      TabIndex        =   6
      Top             =   1560
      Width           =   1425
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Input File"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   5
      Top             =   45
      Width           =   645
   End
   Begin VB.Label lblMain 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Output Path"
      Height          =   195
      Index           =   0
      Left            =   90
      TabIndex        =   3
      Top             =   765
      Width           =   855
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Check txtOut Path and MDB File
Private Function CheckPath(sDBPath As String, sOutPath As String, sTplPath) As Boolean
On Error Resume Next

CheckPath = False
If CBool(Len(Dir$(sOutPath, vbDirectory))) And _
   CBool(Len(Dir$(sTplPath, vbDirectory))) And _
   CBool(Len(Dir$(sDBPath))) Then CheckPath = True
End Function

'Ensure path ends with a slash
Private Function HasSlash(ByVal sPath As String) As String
On Error Resume Next
If Right$(sPath, 1) <> "\" Then
    sPath = sPath & "\"
End If
HasSlash = sPath
End Function

Private Sub btGen_Click()
Dim oAdmin      As CAdmin
Dim oEntity     As CEntity
Dim oTGroup     As CTGroup
Dim oTpl        As CTemplate
Dim fBarLoc     As Double
Dim fBarMove    As Double
Dim fBarSect    As Double
Dim iEntCnt     As Integer
Dim iTplCnt     As Integer
Dim lEntId      As Long
Dim lLangId     As Long
Dim sDBPath     As String
Dim sGroupPath  As String
Dim sTplPath    As String
Dim sOutPath    As String
Dim sOutFile    As String
Dim sOutText    As String

On Error Resume Next
sbMain.Panels(1).Text = "Initializing..."

pbMain.Value = pbMain.Min
iEntCnt = 0
iTplCnt = 0
fBarSect = 0
fBarMove = 0
fBarLoc = 0

sDBPath = Trim$(txtIn)
sTplPath = Trim$(txtTpl)
sOutPath = Trim$(txtOut)

sTplPath = HasSlash(sTplPath)
sOutPath = HasSlash(sOutPath)

'Be sure path and file exist
If Not CheckPath(sDBPath, sOutPath, sTplPath) Then
    MsgBox "Output Paths or MDB not found."
    Exit Sub
End If

MousePointer = vbHourglass

Set oAdmin = New CAdmin
If Not oAdmin.Init(sDBPath) Then
    MsgBox "Couldn't Init"
    Set oAdmin = Nothing
    Exit Sub
End If

oAdmin.FillListTGroups
oAdmin.FillListEntities
'Tell Admin the template location
oAdmin.TemplatePath = sTplPath

'Math for status bar
iEntCnt = 0
iTplCnt = 0
fBarSect = 0
fBarMove = 0
For Each oTGroup In oAdmin.TGroups
    iTplCnt = iTplCnt + oTGroup.Templates.Count
Next oTGroup
iEntCnt = oAdmin.Entities.Count
fBarSect = pbMain.Max / iTplCnt
fBarMove = fBarSect / iEntCnt
Set oTGroup = Nothing

'Generate something
For Each oTGroup In oAdmin.TGroups
    lLangId = oTGroup.LangId
    sGroupPath = sOutPath & oTGroup.ShortName
    sGroupPath = HasSlash(sGroupPath)
    MkDir sGroupPath
    For Each oTpl In oTGroup.Templates
        sbMain.Panels(1).Text = "Generating " & oTpl.LongName & "..."
        For Each oEntity In oAdmin.Entities
            lEntId = oEntity.PKId
            sOutText = oAdmin.GenCode(oTpl, lEntId, lLangId)
            sOutFile = sGroupPath & oTpl.FilePre & oEntity.Name & oTpl.FilePost
            oAdmin.WriteFile sOutText, sOutFile
            fBarLoc = fBarLoc + fBarMove
            pbMain.Value = fBarLoc
        Next oEntity
    Next oTpl
Next oTGroup

sbMain.Panels(1).Text = "Ready"
MousePointer = vbDefault

Set oEntity = Nothing
Set oTpl = Nothing
Set oTGroup = Nothing
Set oAdmin = Nothing
End Sub

