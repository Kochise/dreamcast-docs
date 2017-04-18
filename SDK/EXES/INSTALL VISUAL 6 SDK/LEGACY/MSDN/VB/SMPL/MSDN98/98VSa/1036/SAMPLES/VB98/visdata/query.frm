VERSION 5.00
Begin VB.Form frmQuery 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Créateur de requêtes"
   ClientHeight    =   5100
   ClientLeft      =   2430
   ClientTop       =   2595
   ClientWidth     =   7410
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016115
   Icon            =   "QUERY.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   4651.655
   ScaleMode       =   0  'User
   ScaleWidth      =   7314.2
   ShowInTaskbar   =   0   'False
   Begin VB.OptionButton optOrder 
      Caption         =   "Desc"
      Height          =   225
      Index           =   1
      Left            =   6480
      MaskColor       =   &H00000000&
      TabIndex        =   10
      Top             =   1560
      Width           =   855
   End
   Begin VB.OptionButton optOrder 
      Caption         =   "Asc"
      Height          =   221
      Index           =   0
      Left            =   5760
      MaskColor       =   &H00000000&
      TabIndex        =   9
      Top             =   1560
      Value           =   -1  'True
      Width           =   615
   End
   Begin VB.CheckBox chkTopPercent 
      Caption         =   "Top Percent"
      Height          =   360
      Left            =   2640
      MaskColor       =   &H00000000&
      TabIndex        =   15
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox txtTopNValue 
      Height          =   285
      Left            =   1680
      TabIndex        =   14
      Top             =   2760
      Width           =   735
   End
   Begin VB.CommandButton cmdGetValues 
      Caption         =   "&Liste des valeurs possibles"
      Height          =   315
      Left            =   4560
      MaskColor       =   &H00000000&
      TabIndex        =   5
      Top             =   600
      Width           =   2775
   End
   Begin VB.CommandButton cmdOr 
      Caption         =   "&Or"
      Height          =   315
      Left            =   2280
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   600
      Width           =   2175
   End
   Begin VB.CommandButton cmdAnd 
      Caption         =   "&And"
      Height          =   315
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   600
      Width           =   2160
   End
   Begin VB.ComboBox cboValue 
      Height          =   315
      Left            =   4560
      Sorted          =   -1  'True
      TabIndex        =   2
      Text            =   "cValue"
      Top             =   240
      Width           =   2775
   End
   Begin VB.ComboBox cboOperator 
      Height          =   315
      ItemData        =   "QUERY.frx":030A
      Left            =   3120
      List            =   "QUERY.frx":030C
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   240
      Width           =   1335
   End
   Begin VB.ComboBox cboField 
      Height          =   315
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   240
      Width           =   2895
   End
   Begin VB.CommandButton cmdSaveQDF 
      Caption         =   "Enregi&strer"
      Height          =   375
      Left            =   3720
      MaskColor       =   &H00000000&
      TabIndex        =   20
      Top             =   4680
      Width           =   1200
   End
   Begin VB.CommandButton cmdJoin 
      Caption         =   "&Définir la jointure des tables"
      Height          =   360
      Left            =   4560
      MaskColor       =   &H00000000&
      TabIndex        =   12
      Top             =   2160
      Width           =   2775
   End
   Begin VB.ListBox lstJoinFields 
      Height          =   645
      Left            =   4560
      TabIndex        =   13
      Top             =   2610
      Width           =   2775
   End
   Begin VB.CommandButton cmdCopySQL 
      Caption         =   "Cop&ier"
      Height          =   375
      Left            =   2520
      MaskColor       =   &H00000000&
      TabIndex        =   19
      Top             =   4680
      Width           =   1200
   End
   Begin VB.ComboBox cboOrderByField 
      Height          =   315
      Left            =   4560
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   1800
      Width           =   2775
   End
   Begin VB.ComboBox cboGroupByField 
      Height          =   315
      Left            =   4560
      Style           =   2  'Dropdown List
      TabIndex        =   8
      Top             =   1200
      Width           =   2775
   End
   Begin VB.ListBox lstTables 
      Height          =   1425
      Left            =   120
      MultiSelect     =   1  'Simple
      TabIndex        =   6
      Top             =   1200
      Width           =   1815
   End
   Begin VB.CommandButton cmdShowSQL 
      Caption         =   "Afficher S&QL"
      Height          =   375
      Left            =   1320
      MaskColor       =   &H00000000&
      TabIndex        =   18
      Top             =   4680
      Width           =   1200
   End
   Begin VB.ListBox lstShowFields 
      Height          =   1425
      Left            =   2040
      MultiSelect     =   1  'Simple
      TabIndex        =   7
      Top             =   1200
      Width           =   2295
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   375
      Left            =   6120
      MaskColor       =   &H00000000&
      TabIndex        =   22
      Top             =   4680
      Width           =   1200
   End
   Begin VB.CommandButton cmdRunQuery 
      Caption         =   "&Exécuter"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   17
      Top             =   4680
      Width           =   1200
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Eff&acer"
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00000000&
      TabIndex        =   21
      Top             =   4680
      Width           =   1200
   End
   Begin VB.TextBox txtCriteria 
      Height          =   1215
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   16
      Top             =   3360
      Width           =   7215
   End
   Begin VB.Label lblLabels 
      Caption         =   "N premières valeurs:"
      Height          =   195
      Index           =   7
      Left            =   120
      TabIndex        =   31
      Top             =   2790
      Width           =   1575
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Opérateur:"
      Height          =   195
      Index           =   1
      Left            =   3120
      TabIndex        =   30
      Top             =   0
      Width           =   720
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Valeur:"
      Height          =   195
      Index           =   2
      Left            =   4560
      TabIndex        =   29
      Top             =   0
      Width           =   450
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Nom du champ:"
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   28
      Top             =   0
      Width           =   840
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Trier par: "
      Height          =   195
      Index           =   6
      Left            =   4560
      TabIndex        =   27
      Top             =   1560
      Width           =   750
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Grouper par: "
      Height          =   195
      Index           =   5
      Left            =   4560
      TabIndex        =   26
      Top             =   960
      Width           =   765
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Tables: "
      Height          =   195
      Index           =   3
      Left            =   120
      TabIndex        =   25
      Top             =   960
      Width           =   570
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Champs sélectionnés: "
      Height          =   195
      Index           =   4
      Left            =   2040
      TabIndex        =   24
      Top             =   960
      Width           =   1140
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Critère: "
      Height          =   195
      Index           =   8
      Left            =   120
      TabIndex        =   23
      Top             =   3120
      Width           =   630
   End
End
Attribute VB_Name = "frmQuery"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Créateur de requêtes"
Const BUTTON1 = "&And"
Const BUTTON2 = "&Or"
Const BUTTON3 = "&Liste des valeurs possibles"
Const BUTTON4 = "&Définir la jointure des tables"
Const BUTTON5 = "&Exécuter"
Const BUTTON6 = "Afficher S&QL"
Const BUTTON7 = "Cop&ier"
Const BUTTON8 = "Enregi&strer"
Const BUTTON9 = "E&ffacer"
Const BUTTON10 = "Fer&mer"
Const Label1 = "Nom du champ:"
Const Label2 = "Opérateur:"
Const LABEL3 = "Valeur:"
Const LABEL4 = "Tables:"
Const LABEL5 = "Champs sélectionnés:"
Const LABEL6 = "Grouper par:"
Const LABEL7 = "Trier par:"
Const LABEL8 = "N premières valeurs:"
Const LABEL9 = "Critère:"
Const CHECK1 = "Top Percent"
Const MSG1 = "Mise à jour des champs de la feuille"
Const MSG2 = "(aucun)"
Const MSG3 = "2 tables au moins doivent être sélectionnées!"
Const MSG4 = "Choisir les jointures"
Const MSG5 = "Aucune requête n'a été entrée!"
Const MSG6 = "Création de la requête"
Const MSG7 = "Exécution de la requête"
Const MSG8 = "Entrez le nom de la requête:"
'>>>>>>>>>>>>>>>>>>>>>>>>


Dim mbShowSQL As Integer
Dim mbCopySQL As Integer
Dim mbSaveSQL As Integer

Private Sub cmdAnd_Click()
  Dim nFldType As Integer
  Dim sFieldName As String
  Dim sTableName As String

  If Len(cboField.Text) = 0 Then Exit Sub

  sTableName = stSTF((cboField), 0)
  sFieldName = stSTF((cboField), 1)
  nFldType = gdbCurrentDB.TableDefs(StripBrackets(sTableName)).Fields(StripBrackets(sFieldName)).Type
  
  If Len(txtCriteria.Text) > 0 Then
    txtCriteria.Text = txtCriteria.Text & vbCrLf & "And "
  End If
  If nFldType = dbText Or nFldType = dbMemo Or nFldType = dbDate Then
    txtCriteria.Text = txtCriteria.Text & cboField.Text & " " & cboOperator.Text & " '" & cboValue.Text & "'"
  Else
    txtCriteria.Text = txtCriteria.Text & cboField.Text & " " & cboOperator.Text & " " & cboValue.Text
  End If
  cboField.SetFocus
End Sub

Private Sub cboField_Click()
  cboValue.Clear
End Sub

Private Sub cmdClear_Click()
  On Error Resume Next
  Dim i As Integer
  
  For i = 0 To lstTables.ListCount - 1
    lstTables.Selected(i) = False
  Next
  txtCriteria.Text = vbNullString
  txtTopNValue.Text = vbNullString
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdCopySQL_Click()
  mbCopySQL = True
  Call cmdRunQuery_Click
  mbCopySQL = False
End Sub

Private Sub cmdSaveQDF_Click()
  mbSaveSQL = True
  Call cmdRunQuery_Click
  mbSaveSQL = False
End Sub

Private Sub lstTables_Click()
  On Error GoTo LTErr

  Dim i As Integer, ii As Integer
  Dim tdf As TableDef
  Dim qdf As QueryDef
  Dim sTmp As String
  Dim fld As Field

  MsgBar MSG1, True
  cboField.Clear
  lstShowFields.Clear
  cboGroupByField.Clear
  cboOrderByField.Clear
  cboValue.Clear

  cboGroupByField.AddItem MSG2
  cboOrderByField.AddItem MSG2

  For ii = 0 To lstTables.ListCount - 1
    If lstTables.Selected(ii) Then
      If lstTables.ItemData(ii) = 0 Then
        ' Ceci doit être une table.
        Set tdf = gdbCurrentDB.TableDefs(lstTables.List(ii))
        For Each fld In tdf.Fields
          sTmp = AddBrackets((lstTables.List(ii))) & "." & AddBrackets((fld.Name))
          cboField.AddItem sTmp
          lstShowFields.AddItem sTmp
          cboGroupByField.AddItem sTmp
          cboOrderByField.AddItem sTmp
        Next
      Else
        ' Ceci doit être une requête.
        Set qdf = gdbCurrentDB.QueryDefs(lstTables.List(ii))
        For Each fld In qdf.Fields
          sTmp = AddBrackets((lstTables.List(ii))) & "." & AddBrackets((fld.Name))
          cboField.AddItem sTmp
          lstShowFields.AddItem sTmp
          cboGroupByField.AddItem sTmp
          cboOrderByField.AddItem sTmp
        Next
      End If
    End If
  Next
  If Len(cboField.List(0)) > 0 Then
    cboField.ListIndex = 0
    cboGroupByField.ListIndex = 0
    cboOrderByField.ListIndex = 0
  End If
  MsgBar vbNullString, False
  Exit Sub
  
LTErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016115
  End If
End Sub

Private Sub Form_Load()
  On Local Error GoTo FLErr

  Dim rec As Recordset
  Dim i As Integer

  Me.Caption = FORMCAPTION
  cmdAnd.Caption = BUTTON1
  cmdOr.Caption = BUTTON2
  cmdGetValues.Caption = BUTTON3
  cmdJoin.Caption = BUTTON4
  cmdRunQuery.Caption = BUTTON5
  cmdShowSQL.Caption = BUTTON6
  cmdCopySQL.Caption = BUTTON7
  cmdSaveQDF.Caption = BUTTON8
  cmdClear.Caption = BUTTON9
  cmdClose.Caption = BUTTON10
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  lblLabels(3).Caption = LABEL4
  lblLabels(4).Caption = LABEL5
  lblLabels(5).Caption = LABEL6
  lblLabels(6).Caption = LABEL7
  lblLabels(7).Caption = LABEL8
  lblLabels(8).Caption = LABEL9
  chkTopPercent.Caption = CHECK1
  
  ' Efface la liste.
  txtCriteria.Text = vbNullString

  cboOperator.AddItem "="
  cboOperator.AddItem "<>"
  cboOperator.AddItem ">"
  cboOperator.AddItem ">="
  cboOperator.AddItem "<"
  cboOperator.AddItem "<="
  cboOperator.AddItem "Like"
  cboOperator.ListIndex = 0

  ' Remplit la liste de la table.
  GetTableList lstTables, False, False, True
  lstTables.ListIndex = 0

  cboValue.Text = vbNullString

  Height = 5520
  Width = 7224
  Left = (frmMDI.Width - Width) / 2
  Top = 0
  Exit Sub

FLErr:
  ShowError
End Sub

Private Sub Form_Resize()
  On Error Resume Next

  If WindowState <> 1 Then
    Me.Height = 5430
    Me.Width = 7575
  End If
End Sub

Private Sub cmdGetValues_Click()
  On Error GoTo GVErr

  Dim rec As Recordset

  MsgBar "Obtention des valeurs possibles", True
  Screen.MousePointer = vbHourglass
  Set rec = gdbCurrentDB.OpenRecordset("select Distinct " & StripOwner(cboField) & " from " & stSTF((cboField), 0))
  Do While rec.EOF = False
    If Len(Trim(rec(0))) > 0 Then
      cboValue.AddItem rec(0).Value
    End If
    rec.MoveNext
  Loop
  rec.Close
  cboValue.Text = cboValue.List(0)
  cboValue.SetFocus

  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

GVErr:
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  cboValue.Text = vbNullString
  Exit Sub

End Sub

Private Sub cmdJoin_Click()
  Dim i As Integer
  Dim c As Integer

  For i = 0 To lstTables.ListCount - 1
    If lstTables.Selected(i) Then
      c = c + 1
    End If
  Next
  If c < 2 Then
    Beep
    MsgBox MSG3, 48
  Else
    MsgBar MSG4, False
    frmJoin.Show vbModal
    MsgBar vbNullString, False
  End If
End Sub

Private Sub cmdOr_Click()
  Dim nType As Integer
  Dim sFieldName As String
  Dim sTableName As String

  If Len(cboField.Text) = 0 Then Exit Sub

  sTableName = stSTF((cboField), 0)
  sFieldName = stSTF((cboField), 1)
  nType = gdbCurrentDB.TableDefs(StripBrackets(sTableName)).Fields(StripBrackets(sFieldName)).Type

  If Len(txtCriteria.Text) > 0 Then
    txtCriteria.Text = txtCriteria.Text & vbCrLf & " Or "
  End If
  If nType = dbText Or nType = dbMemo Or nType = dbDate Then
    txtCriteria.Text = txtCriteria.Text & cboField.Text & " " & cboOperator.Text & " '" & cboValue.Text & "'"
  Else
    txtCriteria.Text = txtCriteria.Text & cboField.Text & " " & cboOperator.Text & " " & cboValue.Text
  End If
  cboField.SetFocus

End Sub

Private Sub cmdRunQuery_Click()

  On Error GoTo OKErr

  Dim rsTmp As Recordset
  Dim frmTmp As Form
  Dim fs As String
  Dim ts As String
  Dim i As Integer
  Dim sWhere As String
  Dim sWhere2 As String
  Dim sNewWhere As String
  Dim sTmp As String
  Dim bMatchParen As Integer
  Dim sQueryName As String
  Dim qdfTmp As QueryDef
  Dim sSQLString As String

  If lstShowFields.ListCount = 0 Then
    MsgBox MSG5, vbExclamation
    Exit Sub
  End If

  MsgBar MSG6, True
  If Len(txtCriteria.Text) > 0 Then
    sWhere = "AND " & LTrim(txtCriteria.Text)
    ' enlève les vbcrlfs
    For i = 1 To Len(sWhere)
      If Mid(sWhere, i, 1) = Chr(13) Then
        sTmp = sTmp & " "
      ElseIf Mid(sWhere, i, 1) = Chr(10) Then
        ' Ne rien faire
      Else
        sTmp = sTmp + Mid(sWhere, i, 1)
      End If
    Next
    sWhere = sTmp

    sWhere = RTrim(sWhere)

    ' Ajoute des parents à sWhere
     sWhere2 = sWhere
     Do
       sTmp = stGetToken(sWhere2, " ")
       sTmp = sTmp & " "
        If bMatchParen = False And UCase(sTmp) = "AND " Then
         sNewWhere = sNewWhere + sTmp & "("
         bMatchParen = True
       ElseIf bMatchParen And UCase(sTmp) = "AND " Then
         sNewWhere = sNewWhere & ") " & sTmp & "("
         ' bMatchParen = False
       Else
         If UCase(sTmp) = "OR" Or UCase(sTmp) = "IN " Or UCase(sTmp) = "LIKE" Then
           sNewWhere = sNewWhere & " " & sTmp
         Else
           sNewWhere = sNewWhere + sTmp
         End If
       End If

     Loop Until sWhere2 = vbNullString
     sWhere = sNewWhere & ")"

    ' Crée une chaîne DynaSet:
    ' Abandonne les opérateurs AND/OR.
    If Mid(sWhere, 2, 2) = "OR" Then
      sWhere = Mid(sWhere, 5, Len(sWhere) - 5)
    Else
      sTmp = stGetToken(sWhere, " ")
    End If

    If Len(sWhere) > 0 Then
      sWhere = " Where " & sWhere
    End If

  End If

  ' Vérifie les conditions de la jointure.
  If lstJoinFields.ListCount > 0 Then
    If Len(sWhere) = 0 Then
      sWhere = sWhere & " Where "
    Else
      sWhere = sWhere & " And "
    End If
    For i = 0 To lstJoinFields.ListCount - 1
      sWhere = sWhere + lstJoinFields.List(i) & " And "
    Next
    sWhere = Mid(sWhere, 1, Len(sWhere) - 5)
  End If

  ' Vérifie le groupe par champ.
  If cboGroupByField <> MSG2 Then
    sWhere = sWhere & " Group By " & cboGroupByField
  End If

  ' Vérifie l'ordre par champ.
  If cboOrderByField <> MSG2 Then
    sWhere = sWhere & " Order By " & cboOrderByField
    If optOrder(1).Value Then
      sWhere = sWhere & " Desc "
    End If
  End If

  ' Affiche le nom des champs
  For i% = 0 To lstShowFields.ListCount - 1
    If lstShowFields.Selected(i%) Then
      fs = fs + lstShowFields.List(i%) & ","
    End If
  Next
  If Len(fs) = 0 Then
    For i% = 0 To lstTables.ListCount - 1
      If lstTables.Selected(i%) Then
        fs = fs + AddBrackets((lstTables.List(i%))) & ".*,"
      End If
    Next
    If Len(fs) = 0 Then
      fs = "*"
    Else
      fs = Mid(fs, 1, Len(fs) - 1)     ' Retire le dernier","
    End If
  Else
    fs = Mid(fs, 1, Len(fs) - 1)
  End If

  ' Lit les noms des tables.
  For i% = 0 To lstTables.ListCount - 1
    If lstTables.Selected(i%) Then
      ts = ts + AddBrackets((lstTables.List(i%))) & ","
    End If
  Next
  ts = Mid(ts, 1, Len(ts) - 1)

  sSQLString = "Select "
  
  ' Définit N premières valeurs si elles existent.
  If Len(txtTopNValue.Text) > 0 Then
    sSQLString = sSQLString & " TOP " & txtTopNValue.Text & " "
    If chkTopPercent.Value = vbChecked Then
      sSQLString = sSQLString & " PERCENT "
    End If
  End If
  
  sSQLString = sSQLString & fs & " From " & ts + sWhere
  
  If mbShowSQL = False And mbCopySQL = False And mbSaveSQL = False Then
    MsgBar MSG7, True
    OpenQuery sSQLString, True
    
  ElseIf mbShowSQL Then
    MsgBar vbNullString, False
    MsgBox sSQLString, 0, "Requête SQL"
  
  ElseIf mbCopySQL Then
    frmSQL.txtSQLStatement.Text = sSQLString
  
  ElseIf mbSaveSQL Then
    MsgBar vbNullString, False
    sQueryName = InputBox(MSG8)
    If Len(sQueryName) = 0 Then Exit Sub
  
    ' Vérifie l'existence d'un doublon et quitter si l'utilisateur ne l'écrase pas.
    If DupeTableName(sQueryName) Then
      Exit Sub
    End If
    ' Ajoute la nouvelle requête.
    Set qdfTmp = gdbCurrentDB.CreateQueryDef(sQueryName, sSQLString)
    RefreshTables Nothing
  End If

  MsgBar vbNullString, False
  Exit Sub

OKErr:
  If Err = 364 Then Exit Sub   ' Capture la feuille non chargée.
  ShowError
End Sub

Private Sub cmdShowSQL_Click()
  mbShowSQL = True
  Call cmdRunQuery_Click
  mbShowSQL = False
End Sub

Private Function stGetToken(rsLine As String, rsDelim As String) As String
  On Error GoTo GetTokenError
  
  Dim iOpenQuote As Integer
  Dim iCloseQuote As Integer
  Dim iDelim As Integer
  Dim stToken As String

  iOpenQuote = InStr(1, rsLine, """")
  iDelim = InStr(1, rsLine, rsDelim)

  If (iOpenQuote > 0) And (iOpenQuote < iDelim) Then
    iCloseQuote = InStr(iOpenQuote + 1, rsLine, """")
    iDelim = InStr(iCloseQuote + 1, rsLine, rsDelim)
  End If

  If (iDelim% <> 0) Then
    stToken = LTrim(RTrim(Mid(rsLine, 1, iDelim - 1)))
    rsLine = Mid(rsLine, iDelim + 1)
  Else
    stToken = LTrim(RTrim(Mid(rsLine, 1)))
    rsLine = vbNullString
  End If

  If (Len(stToken) > 0) Then
    If (Mid(stToken, 1, 1) = """") Then
      stToken = Mid(stToken, 2)
    End If
    If (Mid(stToken, Len(stToken), 1) = """") Then
      stToken = Mid(stToken, 1, Len(stToken) - 1)
    End If
  End If
  stGetToken = stToken
  Exit Function

GetTokenError:
  Exit Function

End Function

' Fonction de séparation de la table et du champ à partir d'une paire tbl.fld.
Private Function stSTF(rsName As String, rnPart As Integer) As String
  If InStr(InStr(1, rsName, ".") + 1, rsName, ".") > 1 Then
    rsName = StripOwner(rsName)
  End If
  If rnPart = 0 Then
    stSTF = Mid(rsName, 1, InStr(1, rsName, ".") - 1)
  Else
    stSTF = Mid(rsName, InStr(1, rsName, ".") + 1, Len(rsName))
  End If
End Function
