VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmDatabase 
   Caption         =   "Base de données"
   ClientHeight    =   3540
   ClientLeft      =   3405
   ClientTop       =   2910
   ClientWidth     =   3690
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016146
   Icon            =   "Database.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   3540
   ScaleWidth      =   3690
   ShowInTaskbar   =   0   'False
   Begin MSComCtlLib.TreeView tvDatabase 
      Height          =   3465
      Left            =   30
      TabIndex        =   0
      Top             =   30
      Width           =   3600
      _ExtentX        =   6350
      _ExtentY        =   6112
      _Version        =   393217
      Indentation     =   353
      LineStyle       =   1
      Style           =   7
      ImageList       =   "imlTreePics"
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSComCtlLib.ImageList imlTreePics 
      Left            =   1215
      Top             =   1560
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":014A
            Key             =   "Table"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":025C
            Key             =   "Query"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":036E
            Key             =   "Index"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":0480
            Key             =   "Property"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":0592
            Key             =   "Attached"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "Database.frx":06A4
            Key             =   "Field"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmDatabase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Base de données"
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim mnodEditNode As Node

' Pour une utilisation autonome, cette méthode doit être appelée
' à partir de l'opération qui charge cette feuille.
Public Sub LoadDatabase()
  On Error GoTo ADErr

  Dim nodX As Node    ' Crée une variable.
  Dim sTBLName As String
  Dim sQRYName As String
  Dim sPropName As String
  Dim tblObj As DAO.TableDef
  Dim qdfObj As DAO.QueryDef
  Dim prpObj As DAO.Property
  Dim bAttached As Boolean
  Dim sTmp As String
  Dim qryObj As QueryDef
  Dim bTablesFound As Boolean
  Dim bIncludeSysTables As Boolean

  Me.MousePointer = vbHourglass
    
  tvDatabase.Nodes.Clear
    
  If gdbCurrentDB Is Nothing Then Exit Sub
  
  ' Ajoute le nœud des propriétés.
  Set nodX = tvDatabase.Nodes.Add(, , ">" & PROPERTIES_STR, PROPERTIES_STR, PROPERTY_STR)
  nodX.Tag = PROPERTIES_STR
  tvDatabase_NodeClick nodX
  nodX.Expanded = False
  
  bIncludeSysTables = frmMDI.mnuPAllowSys.Checked
  
  ' Ajoute les tables.
  For Each tblObj In gdbCurrentDB.TableDefs
    If (tblObj.Attributes And dbSystemObject) = 0 Or bIncludeSysTables Then
      sTBLName = tblObj.Name
      bTablesFound = True
      If (tblObj.Attributes And dbAttachedTable) = dbAttachedTable Then
        bAttached = True
      ElseIf (tblObj.Attributes And dbAttachedODBC) = dbAttachedODBC Then
        bAttached = True
      Else
        bAttached = False
      End If
      
      If bAttached Then
        Set nodX = tvDatabase.Nodes.Add(, , "T" & tblObj.Name, tblObj.Name, ATTACHED_STR)
      Else
        Set nodX = tvDatabase.Nodes.Add(, , "T" & tblObj.Name, tblObj.Name, TABLE_STR)
      End If
      nodX.Tag = TABLE_STR
      Set nodX = tvDatabase.Nodes.Add("T" & sTBLName, tvwChild, _
                                      sTBLName & ">Fields", _
                                      FIELDS_STR, FIELD_STR)
      nodX.Tag = FIELDS_STR
      Set nodX = tvDatabase.Nodes.Add("T" & sTBLName, tvwChild, _
                                      sTBLName & ">Indexes", _
                                      INDEXES_STR, INDEX_STR)
      nodX.Tag = INDEXES_STR
      Set nodX = tvDatabase.Nodes.Add("T" & sTBLName, tvwChild, _
                                      sTBLName & ">" & PROPERTIES_STR, _
                                      PROPERTIES_STR, PROPERTY_STR)
      nodX.Tag = PROPERTIES_STR
      If bAttached Then
        ' Ajoute deux nœuds pour afficher les détails de la pièce jointe.
        sTmp = gdbCurrentDB.TableDefs(sTBLName).Connect
        sTmp = Left(sTmp, InStr(sTmp, ";") - 1)
        If Len(sTmp) = 0 Then
          sTmp = gsMSACCESS
        End If
        Set nodX = tvDatabase.Nodes.Add("T" & sTBLName, tvwChild, _
                                        sTBLName & ">AttachType", _
                                        sTmp & " Table", ATTACHED_STR)
      End If
    End If
  Next


  ' Ajoute les propriétés Querydefs.
  For Each qryObj In gdbCurrentDB.QueryDefs
    sQRYName = qryObj.Name
    Set nodX = tvDatabase.Nodes.Add(, , sQRYName, sQRYName, QUERY_STR)
    nodX.Tag = QUERY_STR
    Set nodX = tvDatabase.Nodes.Add(sQRYName, tvwChild, _
                                   sQRYName & ">" & PROPERTIES_STR, _
                                   PROPERTIES_STR, PROPERTY_STR)
    nodX.Tag = PROPERTIES_STR
  Next

  ' Active les menus dépendant des tables présentes.
  If bTablesFound Then
    frmMDI.mnuUQuery.Enabled = True
    frmMDI.mnuDBPUNewQuery.Visible = True
  Else
    ' Pas de table disponible.
    frmMDI.mnuUQuery.Enabled = False
    frmMDI.mnuDBPUNewQuery.Visible = False
  End If

  Me.MousePointer = vbDefault
  Exit Sub
  
ADErr:
  ShowError
End Sub


Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016146
  End If
End Sub

Private Sub Form_Load()
  On Error Resume Next

  Me.Caption = FORMCAPTION

  Me.Height = Val(GetRegistryString("DBWindowHeight", "3870"))
  Me.Width = Val(GetRegistryString("DBWindowWidth", "3835"))
  Me.Top = Val(GetRegistryString("DBWindowTop", "0"))
  Me.Left = Val(GetRegistryString("DBWindowLeft", "0"))

  Err.Clear
End Sub

Private Sub Form_Resize()
  On Error Resume Next
  tvDatabase.Width = Me.ScaleWidth - (tvDatabase.Left * 2)
  tvDatabase.Height = Me.ScaleHeight - (tvDatabase.Top * 2)
End Sub

Private Sub Form_Unload(Cancel As Integer)
  CloseCurrentDB
  If Me.WindowState = vbNormal Then
    SaveSetting APP_CATEGORY, APPNAME, "DBWindowTop", Me.Top
    SaveSetting APP_CATEGORY, APPNAME, "DBWindowLeft", Me.Left
    SaveSetting APP_CATEGORY, APPNAME, "DBWindowWidth", Me.Width
    SaveSetting APP_CATEGORY, APPNAME, "DBWindowHeight", Me.Height
  End If
End Sub

Private Sub tvDatabase_AfterLabelEdit(Cancel As Integer, NewString As String)
  On Error Resume Next
  
  ' Modifie le nom dans la base de données.
  Select Case mnodEditNode.Tag
    Case TABLE_STR
      gdbCurrentDB.TableDefs(mnodEditNode.Text).Name = NewString
    Case QUERY_STR
      gdbCurrentDB.QueryDefs(mnodEditNode.Text).Name = NewString
    Case INDEX_STR
      gdbCurrentDB.TableDefs(mnodEditNode.Parent.Parent.Text).Indexes(mnodEditNode.Text).Name = NewString
    Case FIELD_STR
      gdbCurrentDB.TableDefs(mnodEditNode.Parent.Parent.Text).Fields(mnodEditNode.Text).Name = NewString
  End Select
  
  If Err Then
    MsgBox Err.Description
    ' Une erreur est survenue; revenir en arrière.
    Cancel = True
  End If
  
  ' Revient en arrière
  If Not gnodDBNode Is Nothing Then
    Set frmDatabase.tvDatabase.SelectedItem = gnodDBNode
  End If

  Err.Clear
End Sub

Private Sub tvDatabase_BeforeLabelEdit(Cancel As Integer)
  Dim sTmp As String
  
  sTmp = tvDatabase.SelectedItem.Tag
  
  If sTmp = FIELDS_STR Or _
     sTmp = INDEXES_STR Or _
     sTmp = PROPERTIES_STR Or _
     sTmp = PROPERTY_STR Then
     
    Cancel = True
  Else
    Set mnodEditNode = gnodDBNode
  End If
End Sub

Private Sub tvDatabase_DblClick()
  If gnodDBNode Is Nothing Then Exit Sub
  
  ' Inverse le changement de l'expansion automatique
  ' du déclic de la sourie
  gnodDBNode.Expanded = Not gnodDBNode.Expanded
  
  Set gnodDBNode2 = gnodDBNode
  If gnodDBNode2.Tag = PROPERTY_STR Then
    frmMDI.mnuDBPUEdit_Click
  Else
    frmMDI.mnuDBPUOpen_Click
  End If
  
End Sub

Private Sub tvDatabase_MouseUp(BUTTON As Integer, Shift As Integer, x As Single, y As Single)
  On Error Resume Next
  If BUTTON = vbRightButton Then
    ' Fait une tentative pour obtenir le nœud sur lequel
    ' un clic droit a eu lieu.
    Set gnodDBNode2 = tvDatabase.HitTest(x, y)
    If gnodDBNode2 Is Nothing Then
      Set gnodDBNode2 = tvDatabase.HitTest(800, y)
    End If
    If gnodDBNode2 Is Nothing Then
      ' Refait une tentative plus tard.
      Set gnodDBNode2 = tvDatabase.HitTest(1200, y)
    End If
    If gnodDBNode2 Is Nothing Then
      frmMDI.mnuDBPUCopyStruct.Visible = False
      frmMDI.mnuDBPURename.Visible = False
      frmMDI.mnuDBPUDelete.Visible = False
      frmMDI.mnuDBPUDesign.Visible = False
      frmMDI.mnuDBPUOpen.Visible = False
      frmMDI.mnuDBPUEdit.Visible = False
      frmMDI.mnuDBPUBar1.Visible = False
    Else
      frmMDI.mnuDBPURename.Visible = True
      frmMDI.mnuDBPUDelete.Visible = True
      frmMDI.mnuDBPUBar1.Visible = True
      If gnodDBNode2.Tag = TABLE_STR Then
        frmMDI.mnuDBPUOpen.Visible = True
        frmMDI.mnuDBPUEdit.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = True
        frmMDI.mnuDBPUDesign.Visible = True
        frmMDI.mnuDBPURename.Enabled = True
        frmMDI.mnuDBPUDelete.Enabled = True
      ElseIf gnodDBNode2.Tag = QUERY_STR Then
        frmMDI.mnuDBPUOpen.Visible = True
        frmMDI.mnuDBPUEdit.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = True
        frmMDI.mnuDBPURename.Enabled = True
        frmMDI.mnuDBPUDelete.Enabled = True
      ElseIf gnodDBNode2.Tag = INDEX_STR Then
        frmMDI.mnuDBPUOpen.Visible = False
        frmMDI.mnuDBPUEdit.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = False
        frmMDI.mnuDBPURename.Enabled = True
        frmMDI.mnuDBPUDelete.Enabled = True
      ElseIf gnodDBNode2.Tag = FIELD_STR Then
        frmMDI.mnuDBPUOpen.Visible = False
        frmMDI.mnuDBPUEdit.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = False
        frmMDI.mnuDBPURename.Enabled = True
        frmMDI.mnuDBPUDelete.Enabled = True
      ElseIf gnodDBNode2.Tag = PROPERTY_STR Then
        frmMDI.mnuDBPUOpen.Visible = False
        frmMDI.mnuDBPUEdit.Visible = True
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = False
        frmMDI.mnuDBPURename.Enabled = False
        frmMDI.mnuDBPUDelete.Enabled = False
      ElseIf gnodDBNode2.Tag = PROPERTIES_STR Then
        frmMDI.mnuDBPUOpen.Visible = False
        frmMDI.mnuDBPUEdit.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = False
        frmMDI.mnuDBPURename.Enabled = False
        frmMDI.mnuDBPUDelete.Enabled = False
      Else
        frmMDI.mnuDBPUOpen.Visible = False
        frmMDI.mnuDBPUCopyStruct.Visible = False
        frmMDI.mnuDBPUDesign.Visible = False
        frmMDI.mnuDBPURename.Enabled = False
        frmMDI.mnuDBPUDelete.Enabled = False
      End If
    End If
  
    PopupMenu frmMDI.mnuDBPopUp
  End If
End Sub

Private Sub tvDatabase_NodeClick(ByVal Node As Node)
  On Error GoTo tvDatabase_NodeClickErr
  
  Dim nod As Node
  Dim nodX As Node
  Dim fldObj As DAO.Field
  Dim idxObj As DAO.Index
  Dim prpObj As DAO.Property
  Dim colTmp As Object
  Dim vTmp As Variant

  Set gnodDBNode = Node

  Select Case Node.Tag
    Case FIELDS_STR
      If Node.Children > 0 Then Exit Sub
      ' Ajoute les champs.
      For Each fldObj In gdbCurrentDB.TableDefs(Node.Parent.Text).Fields
        Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                       tvwChild, _
                                       Node.Parent.Key & ">" & FIELDS_STR & ">" & fldObj.Name, _
                                       fldObj.Name, FIELD_STR)
        nodX.Tag = FIELD_STR
      Next
      Node.Expanded = True
      
    Case FIELD_STR
      If Node.Children > 0 Then Exit Sub
      For Each prpObj In gdbCurrentDB.TableDefs(Node.Parent.Parent.Text).Fields(Node.Text).Properties
        ' Cas pour la propriété Value car non disponible
        ' à partir de l'objet field d'un objet tabledef
        If prpObj.Name <> "Value" Then
          vTmp = GetPropertyValue(prpObj)
          Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                         tvwChild, _
                                         Node.Parent.Key & Node.Key & ">" & prpObj.Name, _
                                         prpObj.Name & "=" & vTmp, PROPERTY_STR)
          nodX.Tag = PROPERTY_STR
        End If
      Next
      Node.Expanded = True
      Set tvDatabase.SelectedItem = Node
        
    Case INDEXES_STR
      If Node.Children > 0 Then Exit Sub
      ' Ajoute les index.
      For Each idxObj In gdbCurrentDB.TableDefs(Node.Parent.Text).Indexes
        Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                       tvwChild, _
                                       Node.Parent.Key & ">" & INDEXES_STR & ">" & idxObj.Name, _
                                       idxObj.Name, INDEX_STR)
        nodX.Tag = INDEX_STR
      Next
      Node.Expanded = True
      
    Case INDEX_STR
      If Node.Children > 0 Then Exit Sub
      For Each prpObj In gdbCurrentDB.TableDefs(Node.Parent.Parent.Text).Indexes(Node.Text).Properties
        vTmp = GetPropertyValue(prpObj)
        Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                       tvwChild, _
                                       Node.Parent.Key & Node.Key & ">" & prpObj.Name, _
                                       prpObj.Name & "=" & vTmp, PROPERTY_STR)
        nodX.Tag = PROPERTY_STR
      Next
      Node.Expanded = True
      Set tvDatabase.SelectedItem = Node
    
    Case PROPERTIES_STR
      If Node.Children > 0 Then Exit Sub
      ' Ajoute les propriétés.
      If Node.Parent Is Nothing Then
        Set colTmp = gdbCurrentDB.Properties
      Else
        Select Case Node.Parent.Tag
          Case TABLE_STR
            Set colTmp = gdbCurrentDB.TableDefs(Node.Parent.Text).Properties
          Case QUERY_STR
            Set colTmp = gdbCurrentDB.QueryDefs(Node.Parent.Text).Properties
          Case PROPERTY_STR
            Exit Sub  ' Non effectué: il faut obtenir l'objet parent.
        End Select
      End If
      For Each prpObj In colTmp
        vTmp = GetPropertyValue(prpObj)
        If VarType(vTmp) = vbString Then
          ' Le limiter à 50 caractères.
          vTmp = Left$(vTmp, 50)
        End If
        If Node.Parent Is Nothing Then
          Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                         tvwChild, _
                                         Node.Key & ">" & prpObj.Name, _
                                         prpObj.Name & "=" & vTmp, PROPERTY_STR)
        Else
          Set nodX = tvDatabase.Nodes.Add(Node.Key, _
                                         tvwChild, _
                                         Node.Parent.Key & ">" & prpObj.Name, _
                                         prpObj.Name & "=" & vTmp, PROPERTY_STR)
        End If
        nodX.Tag = PROPERTY_STR
      Next
      Node.Expanded = True
    
  End Select
  
  Exit Sub
tvDatabase_NodeClickErr:
  If Err = 35602 Then Resume Next
  ShowError
End Sub

Function GetPropertyValue(prpObj As DAO.Property) As Variant
  On Error Resume Next
  
  Dim vTmp As Variant
  
  vTmp = prpObj.Value
  If Err Then
    Err.Clear
    GetPropertyValue = "NC"
  Else
    GetPropertyValue = vTmp
  End If
  
End Function
