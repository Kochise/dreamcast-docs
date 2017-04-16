VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmAddIn 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Expert Agent"
   ClientHeight    =   7065
   ClientLeft      =   255
   ClientTop       =   480
   ClientWidth     =   8685
   Icon            =   "frmAddIn.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7065
   ScaleWidth      =   8685
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdPattern 
      Caption         =   "&Pattern Finder"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6780
      TabIndex        =   5
      Top             =   6630
      Width           =   1845
   End
   Begin VB.TextBox txtMethod 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3420
      Left            =   75
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   3105
      Width           =   8535
   End
   Begin VB.CommandButton cmdAnalyze 
      Caption         =   "&Get Procs"
      Default         =   -1  'True
      Height          =   375
      Left            =   6780
      TabIndex        =   4
      Top             =   165
      Width           =   1845
   End
   Begin ComctlLib.ListView lvwProcs 
      Height          =   2160
      Left            =   75
      TabIndex        =   1
      Top             =   570
      Width           =   8535
      _ExtentX        =   15055
      _ExtentY        =   3810
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327680
      SmallIcons      =   "ImageList"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      MouseIcon       =   "frmAddIn.frx":0442
      NumItems        =   4
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Name"
         Object.Width           =   4233
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Type"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Start Row"
         Object.Width           =   1764
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Number Rows"
         Object.Width           =   1764
      EndProperty
   End
   Begin VB.Label lblMethod 
      AutoSize        =   -1  'True
      Caption         =   "Method Name"
      Height          =   195
      Left            =   135
      TabIndex        =   2
      Top             =   2880
      Width           =   1005
   End
   Begin VB.Label lblCodeModule 
      AutoSize        =   -1  'True
      Caption         =   "CodeModule Name"
      Height          =   195
      Left            =   135
      TabIndex        =   0
      Top             =   345
      Width           =   1365
   End
   Begin ComctlLib.ImageList ImageList 
      Left            =   5745
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   5
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmAddIn.frx":045E
            Key             =   "Method"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmAddIn.frx":0778
            Key             =   "Property"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmAddIn.frx":0A92
            Key             =   "Variable"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmAddIn.frx":0DAC
            Key             =   "Event"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmAddIn.frx":10C6
            Key             =   "Constant"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmAddIn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'------------------------------------------------------
' ExpertAgent
'-------------------
' Author:
'   Valor Whisler
'   highest quality UI and applications development
'   valorw@ix.netcom.com
'------------------------------------------------------

Option Explicit

'<Public>----------------------------------------------
Public PressedOK        As Boolean
Public VBInstance       As VBIDE.VBE
Public ThisConnection   As Connect
'</Public>---------------------------------------------

'<Private>---------------------------------------------
Private ThisCodeModule  As VBIDE.CodeModule
Private ThisItem        As ListItem
'</Private>--------------------------------------------


Private Sub cmdPattern_Click()
    
    frmPatternFinder.CodeToAnalyze = txtMethod
    frmPatternFinder.Show
    
End Sub

Private Sub Form_Activate()
    Dim ThisCodePane As VBIDE.CodePane

    On Error GoTo InvalidObject
    
    '---- destroy previous CodeModule object
    Set ThisCodeModule = Nothing
    
    '---- get the active pane and its module
    Set ThisCodePane = VBInstance.ActiveCodePane
    Set ThisCodeModule = ThisCodePane.CodeModule

    lblCodeModule = ThisCodeModule.Name & ":"
    cmdAnalyze.Enabled = True
    
Cleanup:
    Set ThisCodePane = Nothing
    
    Exit Sub

InvalidObject:
    
    lblCodeModule = "Activate a code module before activating this form."
    cmdAnalyze.Enabled = False
    
End Sub

Private Sub Form_Load()

    lblCodeModule = ""
    lblMethod = ""

End Sub

Private Sub Form_Terminate()
    
    Set ThisCodeModule = Nothing
    Set ThisItem = Nothing
    
End Sub

'-------------------------------------------------------
'<Purpose> shows all the procedures in a CodeModule
'-------------------------------------------------------
Private Sub cmdAnalyze_Click()
    Dim TheseMembers    As VBIDE.Members
    Dim InstanceMember  As VBIDE.Member
    Dim WorkingItem     As ListItem
    Dim NumberLines     As Long
    Dim ThisType        As String

    '---- clear the lists
    lvwProcs.ListItems.Clear
    
    '---- get the Members collection
    Set TheseMembers = ThisCodeModule.Members
    
    On Error Resume Next
    '---- list each member
    For Each InstanceMember In TheseMembers
        
        Select Case InstanceMember.Type
            Case vbext_mt_Event
                NumberLines = 1
                ThisType = "Event"
            Case vbext_mt_Property
                '---- this example only retrieves the "_Get" property procedure
                '---- there may also be "_Set" and "_Let" procedures
                NumberLines = ThisCodeModule.ProcCountLines(InstanceMember.Name, vbext_pk_Get)
                ThisType = "Property"
            Case vbext_mt_Const
                NumberLines = 1
                ThisType = "Constant"
            Case vbext_mt_Variable
                NumberLines = 1
                ThisType = "Variable"
            Case vbext_mt_Method
                NumberLines = ThisCodeModule.ProcCountLines(InstanceMember.Name, vbext_pk_Proc)
                ThisType = "Method"
        End Select
    
        '---- add the member information to the list
        Set WorkingItem = lvwProcs.ListItems.Add(, , InstanceMember.Name, , InstanceMember.Type)
        WorkingItem.SubItems(1) = ThisType
        WorkingItem.SubItems(2) = InstanceMember.CodeLocation
        WorkingItem.SubItems(3) = NumberLines
    
    Next
    
    '---- reset form
    txtMethod = ""
    cmdPattern.Enabled = False
    lblMethod = "Click on a proc in the above list to display it here:"
    
Cleanup:
    Set InstanceMember = Nothing
    Set TheseMembers = Nothing
    Set WorkingItem = Nothing
    
    Exit Sub
    
InvalidObject:
    MsgBox "Unable to get a required object." & vbCrLf & Err.Description, vbOKOnly + vbInformation
    GoTo Cleanup

End Sub

'-------------------------------------------------------
'<Purpose> shows the selected procedure
'-------------------------------------------------------
Private Sub lvwProcs_ItemClick(ByVal Item As ComctlLib.ListItem)
    Dim StartLine   As Long
    Dim EndLine     As Long

    Set ThisItem = Item
    lblMethod = ThisItem.Text & ":"
    
    StartLine = Val(ThisItem.SubItems(2))
    EndLine = Val(ThisItem.SubItems(3))

    txtMethod = RetrieveCode(StartLine, EndLine)
    
    '---- check Sub Main for patterns, it is optimized for this demo
    cmdPattern.Enabled = (txtMethod <> "") And (ThisItem.Text = "Main")

End Sub

'-------------------------------------------------------
'<Purpose> retrieves lines of code
'-------------------------------------------------------
Private Function RetrieveCode(StartLine As Long, EndLine As Long) As String

    RetrieveCode = ThisCodeModule.Lines(StartLine, EndLine)

End Function
