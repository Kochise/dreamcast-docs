VERSION 4.00
Begin VB.Form frmBrwsTree 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Active Directory VB Browser"
   ClientHeight    =   7065
   ClientLeft      =   4125
   ClientTop       =   2790
   ClientWidth     =   7575
   FillStyle       =   0  'Solid
   ForeColor       =   &H00000000&
   Height          =   7470
   Left            =   4065
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7065
   ScaleWidth      =   7575
   Top             =   2445
   Width           =   7695
   Begin VB.CommandButton cmdAbort 
      Caption         =   "Stop"
      Height          =   375
      Left            =   6360
      TabIndex        =   4
      Top             =   720
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.CommandButton cmdProperties 
      Caption         =   "Properties..."
      Height          =   375
      Left            =   6360
      TabIndex        =   3
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   6360
      TabIndex        =   2
      Top             =   1200
      Width           =   1095
   End
   Begin VB.Label txtPath 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Path"
      BeginProperty Font 
         name            =   "Times New Roman"
         charset         =   0
         weight          =   400
         size            =   11.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   6720
      Width           =   405
   End
   Begin VB.Label txtName 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      Caption         =   "ADS:"
      BeginProperty Font 
         name            =   "Times New Roman"
         charset         =   0
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   360
      TabIndex        =   6
      Top             =   6000
      Width           =   6255
   End
   Begin VB.Label Label3 
      Caption         =   "Path:"
      BeginProperty Font 
         name            =   "Times New Roman"
         charset         =   0
         weight          =   400
         size            =   11.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   6360
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "Name:"
      BeginProperty Font 
         name            =   "Times New Roman"
         charset         =   0
         weight          =   400
         size            =   12
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   5640
      Width           =   855
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   11160
      Top             =   6960
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      BackColor       =   -2147483643
      MaskColor       =   12632256
   End
   Begin ComctlLib.TreeView TreeView1 
      Height          =   5535
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6135
      _Version        =   65536
      _ExtentX        =   10821
      _ExtentY        =   9763
      _StockProps     =   196
      Appearance      =   1
      ImageList       =   ""
      MousePointer    =   1
      PathSeparator   =   "\"
      Sorted          =   -1  'True
      Style           =   7
   End
End
Attribute VB_Name = "frmBrwsTree"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Private Sub cmdAbort_Click()
'
' Allows the user to cancel a tree expand
'
    bAbort = True
End Sub



Private Sub cmdExit_Click()
'
' Allows user to end program
'
    End
End Sub








Private Sub cmdProperties_Click()
'
' Allows viewing of Active Directory object properties
'
    Dim Class As IADsClass
    Dim Property As IADsProperty
    Dim v As Variant
    Dim Value As Variant
    Dim EmptyVar As Variant
    
    '
    ' Set Error handler
    '
    On Error Resume Next
    
    '
    ' Don't allow exit while getting properties
    '
    cmdExit.Visible = False
    
    '
    ' Set cursor to wait/arrow
    '
    Screen.MousePointer = 13
    
    '
    ' Get the object and its properties
    '
    Set currentADsObj = GetObject(TreeView1.SelectedItem.Key)
    If Err Then
        MsgBox "Could not get object"
        GoTo skip
    End If
    frmProp.lblName.Caption = currentADsObj.Name
    frmProp.lblPath.Caption = currentADsObj.ADsPath
    frmProp.lblClass.Caption = currentADsObj.Class
    '
    ' Namespaces object and Schema object are the only two objects that
    ' do not have an associated schema
    '
    If currentADsObj.Class = "Schema" Or _
            currentADsObj.Class = "NameSpaces" Then
        MsgBox "Please chose non schema object"
        GoTo skip
    End If
    
    '
    ' Load the form
    '
    Load frmProp
    Set Class = GetObject(currentADsObj.Schema)
    If Err Then
        MsgBox "Could not get schema object"
        GoTo skip
    End If
    If Class.Container Then
        frmProp.lblIsContainer.Caption = "Yes"
    Else
        frmProp.lblIsContainer.Caption = "No"
    End If
    For Each v In Class.MandatoryProperties
        Set Property = GetObject(Class.Parent + "\" + v)
        Value = EmptyVar
        Value = currentADsObj.Get(Property.Name)
        If VarType(Value) = vbEmpty Then
            frmProp.lstProperties.AddItem Property.Name & "(" & Property.Syntax & _
            "):" & "<Empty>"
        Else
            frmProp.lstProperties.AddItem Property.Name & "(" & Property.Syntax & _
            "):" & Value
        End If
    Next v
    
    '
    'Make form visible
    '
    frmProp.Visible = True
    
skip:
    cmdExit.Visible = True
    '
    'Set cursor to default
    '
    Screen.MousePointer = 0
End Sub

Private Sub Form_Load()
'
' Sets up the application main form
'

    '
    ' Define indexs for LoadResPicture API
    '
    Const idxComputer = 101
    Const idxUser = 102
    Const idxDomain = 103
    Const idxSyntax = 104
    Const idxService = 105
    Const idxGroup = 106
    Const idxPrintQueue = 107
    Const idxOU = 108
    Const idxFileShare = 109
    Const idxOrganization = 110
    Const idxCountry = 111
    Const idxTop = 112
    Const idxNamespace = 113
    Const idxDefault = 114
    Const idxNamespaces = 115
    ' App icon index
    Const idxApp = 101
    
    '
    ' Create temp Node variable
    '
    Dim nodX As Node

    '
    ' Load pictures into ImageList control.
    '
    'Dim pic As Picture
    '
    'Create Image variable
    '
    Dim imgI As ListImage
    
    '
    ' Set Error handler
    '
    On Error GoTo ErrorHandler

    '
    ' Each image/icon is loaded from the resource file.  If the image
    ' is not present, the default image is used.
    '
    Set imgI = ImageList1.ListImages.Add(, _
        "imgComputer", LoadResPicture(idxComputer, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgUser", LoadResPicture(idxUser, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgDomain", LoadResPicture(idxDomain, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgSchema", LoadResPicture(idxSyntax, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgService", LoadResPicture(idxService, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgGroup", LoadResPicture(idxGroup, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgPrintQueue", LoadResPicture(idxPrintQueue, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgFileShare", LoadResPicture(idxFileShare, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgOrganization", LoadResPicture(idxOrganization, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgCountry", LoadResPicture(idxCountry, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgNameSpace", LoadResPicture(idxNamespace, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgNamespaces", LoadResPicture(idxNamespaces, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgFileService", LoadResPicture(idxDefault, vbResBitmap))
    Set imgI = ImageList1.ListImages.Add(, _
        "imgDefault", LoadResPicture(idxDefault, vbResBitmap))
    
    frmBrwsTree.Icon = LoadResPicture(idxApp, vbResIcon)
    
    '
    ' Set TreeView control properties.
    '
    TreeView1.ImageList = ImageList1    ' Initialize ImageList
    TreeView1.Style = tvwTreelinesPlusMinusPictureText ' Style 7
    TreeView1.LineStyle = tvwRootLines
    TreeView1.Indentation = 50
    strPath = "ADS:" ' Default start of browse

    Call enumerate_path(nodX)
    
    GoTo finish
    
ErrorHandler:
    errstring = "Had an error:" & Err.Number
    ERRNUMB = Err.Number
    MsgBox errstring
    Resume Next
finish:

End Sub

Private Sub TreeView1_Collapse(ByVal Node As Node)
'
' To do when collapsing a node
'
    txtName.Caption = Node.Text
    txtPath.Caption = Node.Key
End Sub

Private Sub TreeView1_Expand(ByVal Node As Node)
'
' Process a node expand
'
    Dim ChildNode As Node
    On Error GoTo ErrorHandler
    
    TreeView1.MousePointer = 13
    ' Only expand once so check for "Dummy" child
    If Node.Child = "Dummy" Then

        Node.Sorted = True
        If bStartup = False Then
        
            cmdExit.Visible = False
            txtName.Caption = Node.Text
            txtPath.Caption = Node.Key
        
            Set ChildNode = Node.Child
            If ChildNode.Text = "Dummy" Then
                TreeView1.Nodes.Remove (ChildNode.Key)
            End If
            cmdAbort.Visible = True
            cmdAbort.SetFocus
            DoEvents
            
            strPath = Node.Key
        
            Call enumerate_path(Node)
            
        End If
    End If

GoTo finish

ErrorHandler:
    errstring = "Had an error:" & Err.Number
    ERRNUMB = Err.Number
    MsgBox errstring

finish:
    cmdExit.Visible = True
    Node.Sorted = True
    cmdAbort.Visible = False
    TreeView1.MousePointer = 0

End Sub

Private Sub TreeView1_NodeClick(ByVal Node As Node)
'
' Process a node click
'
    txtName.Caption = Node.Text
    txtPath.Caption = Node.Key
End Sub

