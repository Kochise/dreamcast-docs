Attribute VB_Name = "modVisData"
'------------------------------------------------------------
' VISDATA.BAS
' Fonctions de support pour l'exemple d'application Gestionnaire de données (Visdata).
'
' Généralités: cette application montre et met en pratique
'   l'ensemble des fonctionnalités du modèle d'objet d'accès
'   aux données (DAO, Data Access Objects) de Visual Basic 5.0.
'
'------------------------------------------------------------

Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const MSG1 = "Exécute d'abord Commit ou Rollback"
Const MSG2 = "Fermeture des jeux d'enregistrement"
Const MSG3 = "La table existe déjà, la supprimer?"
Const MSG4 = "Entrez un nouveau nom de table:"
Const MSG5 = "Prêt"
Const MSG6 = ", veuillez patienter..."
Const MSG7 = "Actualisation de la liste de la table"
Const MSG8 = "Numéro d'erreur: "
Const MSG9 = "Afficher la liste des erreurs d'accès aux données?"
Const MSG10 = "Impossible d'ouvrir un objet Table sur une table jointe; utiliser une feuille de réponses dynamique?"
Const MSG11 = "Ouverture d'une table attachée en tant qu'objetDynaset"
Const MSG12 = "Ouverture d'une table attachée en tant qu'objet Snapshot"
Const MSG13 = "Ouverture en tant que table"
Const MSG14 = "Ouverture d'une table unique d'une feuille de réponses dynamique"
Const MSG15 = "Ouverture d'une table unique d'un jeu d'enregistrements instantané"
Const MSG16 = "Ouverture d'une feuille de réponses dynamique PassThru"
Const MSG17 = "S'agit-il d'une requête SQL Direct (PassThrough)?"
Const MSG18 = "Entrer la valeur de la propriété Connect:"
Const MSG19 = " Impossible d'ouvrir un objet Table à partir d'une objet Querydef; utiliser un objet Snapshot?"
Const MSG20 = "Ouverture d'un jeu d'enregistrements instantané de requête"
Const MSG21 = "Ouverture d'une feuille de réponses dynamique de requête"
Const MSG22 = "Instruction SQL"
Const MSG23 = "Exécute "
Const MSG24 = " la requête?"
Const MSG25 = "Exécution de la requête"
Const MSG26 = "  [Mise à jour impossible]"
Const MSG27 = "La table existe déjà, la supprimer?"
Const MSG28 = "La requête existe déjà, la supprimmer?"
Const MSG29 = "Entrez une valeur pour un paramètre '"
Const MSG30 = "Il n'y a pas d'erreurs d'accès aux données en cours!"
Const MSG31 = "Impossible d'afficher les erreurs à ce stade!"
Const MSG32 = "Les données ont changé; les modifier?"
Const MSG33 = "Annuler toutes les modifications?"
Const MSG34 = "Impossible de fermer: transactions en attente!"
Const MSG35 = "Vous devez d'abord fermer!"
Const MSG36 = "Ouvrir une base de données Microsoft Access"
Const MSG37 = "Ouvrir une base de données Dbase"
Const MSG38 = "Ouvrir une base de données FoxPro"
Const MSG39 = "Ouvrir une base de données Paradox"
Const MSG40 = "Ouvrir un fichier Excel"
Const MSG41 = "Ouvrir une base de données Btrieve"
Const MSG42 = "Ouvrir une base de données Texte"
Const MSG43 = "Ouverture d'une base de données"
Const MSG44 = "NOTE: l'utilisation de tables attachées est recommandée"
Const MSG45 = "Réparation en cours "
Const MSG46 = "Essayer de réparer?"
Const MSG47 = "Entrez un nom de dossier pour la nouvelle base de données ISAM:"
Const MSG48 = "Sélectionnez une base de données Microsoft Access à compacter"
Const MSG49 = "Fichiers MDB de Microsoft Access (*.mdb)|*.mdb"
Const MSG50 = "|Tous les fichiers (*.*)|*.*"
Const MSG51 = "Sélectionnez une base de données Microsoft Access à compacter vers"
Const MSG52 = "Crypter une base de données compactée?"
Const MSG53 = "Compactage en cours "
Const MSG54 = "Ouvrir la dernière base de données compactée?"
Const MSG55 = "Sélectionnez la base de données Microsoft Access à créer"
Const MSG56 = "Exportation de la table: "
Const MSG57 = "Exporte "
Const MSG58 = "dans "
Const MSG59 = "Création d'index:"
Const MSG60 = "Exportation réussie:"
Const MSG61 = "Exportation réussie d'une instruction SQL"
Const MSG62 = "La table existe déjà - la remplacer?"
Const MSG63 = "Importation de la table: "
Const MSG64 = "Importation réussie:"
Const MSG65 = "Nom de dossier non valide!"
'>>>>>>>>>>>>>>>>>>>>>>>>


' Déclarations API
Declare Function SQLAllocEnv% Lib "ODBC32.DLL" (env&)
Declare Function SQLDataSources% Lib "ODBC32.DLL" (ByVal henv&, ByVal fdir%, ByVal szDSN$, ByVal cbDSNMax%, pcbDSN%, ByVal szDesc$, ByVal cbDescMax%, pcbDesc%)

' Variables objets publiques
Public gVDClass      As New VisDataClass
Public gnodDBNode    As Node        ' Noeud de la base de données en cours dans le contrôle Treeview
Public gnodDBNode2   As Node        ' Sauvegarde du noeud (objet Node) de la base de données en cours dans le contrôle Treeview
Public gwsMainWS     As Workspace   ' Objet Workspace principal
Public gdbCurrentDB  As Database    ' Objet Database principal
Public gbDBOpenFlag  As Integer     ' Indicateur signalant si une base de données est ouverte
Public gPropObject   As Object      ' Objet affichant les propriétés
Public gDataCtlObj   As Object      ' Objet contrôle Data public
Public gtdfTableDef  As TableDef    ' Objet Tabledef public utilisé par la feuille frmTblStruct
Public gnFormType    As Integer     ' Type de feuille choisi sur la feuille principale
                                    ' 0 = Utilise le contrôle Data
                                    ' 1 = N'utilise pas le contrôle Data
                                    ' 2 = Utilise le contrôle DBGrid
Public gnRSType      As Integer     ' Type de jeu d'enregistrements choisi sur la feuille principale
                                    ' 0 = table
                                    ' 1 = dynaset (feuille de réponses dynamique)
                                    ' 2 = snapshot (jeu d'enregistrements instantané)

' Variables publiques pour la base de données
Public Const APPNAME = "VisData6"
Public gsDataType       As String   ' Données d'arrière-plan = chaîne de connexion
                                    ' Pour tout ce qui accepte Access
Public gsDBName         As String   ' Nom de la base de données en cours
Public gsODBCDatasource As String   ' Valeurs ODBC publiques
Public gsODBCDatabase   As String   '       "
Public gsODBCUserName   As String   '       "
Public gsODBCPassword   As String   '       "
Public gsODBCDriver     As String   '       "
Public gsODBCServer     As String   '       "
Public gsTblName        As String   '
Public glQueryTimeout   As Long     '
Public glLoginTimeout   As Long     '
Public gsTableDynaFilter As String  '
Public gnReadOnly       As Integer  ' Indicateur de base de données en lecture seule

' Autres variables publiques
Public gsZoomData       As String   ' Passage d'informations à la feuille Zoom

' Variables multi-utilisateur
Public gnMURetryCnt     As Integer
Public gnMUDelay        As Integer
Public gnMULocking      As Integer  ' Indicateur pour le verrouillage pessimiste ou optimiste

' Valeurs de recherche publiques utilisées pour passer des informations entre
' la feuille de réponses dynamique et la boîte de dialogue Rechercher.
Public gbFindFailed     As Boolean
Public gsFindExpr       As String
Public gsFindOp         As String
Public gsFindField      As String
Public gnFindType       As Integer
Public gbFromTableView  As Boolean

' Valeurs de recherche publiques utilisées pour passer des informations entre
' la feuille de réponses dynamique et la boîte de dialogue Rechercher.
Public gsSeekOperator   As String
Public gsSeekValue      As String

' Indicateurs globaux
Public gbDBChanged      As Boolean   '
Public gbTransPending   As Boolean   ' Utilisé pour la gestion des transactions
Public gbFromSQL        As Boolean   ' Source de l'instruction SQL depuis la feuille SQL
Public gbAddTableFlag   As Boolean   ' Indicateur nouveau ou de création
Public gbSettingDataCtl As Boolean   ' Utilisé pour réinitialiser les propriétés du contrôle Data

' Variables publiques utilisées dans le code d'importation/exportation
Public gImpDB As Database
Public gExpDB As Database
Public gExpTable As String

' Types de données d'arrière-plan utilisés dans la chaîne de connexion
Public Const gsMSACCESS = "Microsoft Access"
Public Const gsDBASEIII = "Dbase III;"
Public Const gsDBASEIV = "Dbase IV;"
Public Const gsDBASE5 = "Dbase 5;"
Public Const gsFOXPRO20 = "FoxPro 2.0;"
Public Const gsFOXPRO25 = "FoxPro 2.5;"
Public Const gsFOXPRO26 = "FoxPro 2.6;"
Public Const gsFOXPRO30 = "FoxPro 3.0;"
Public Const gsPARADOX3X = "Paradox 3.X;"
Public Const gsPARADOX4X = "Paradox 4.X;"
Public Const gsPARADOX5X = "Paradox 5.X;"
Public Const gsBTRIEVE = "Btrieve;"
Public Const gsEXCEL30 = "Excel 3.0;"
Public Const gsEXCEL40 = "Excel 4.0;"
Public Const gsEXCEL50 = "Excel 5.0;"
Public Const gsTEXTFILES = "Text;"
Public Const gsSQLDB = "ODBC;"

' Types de données d'importation/exportation
Public gnDataType As gnDataTypes
Public Enum gnDataTypes
  gnDT_NONE = -1
  gnDT_MSACCESS = 0
  gnDT_DBASEIV = 1
  gnDT_DBASEIII = 2
  gnDT_FOXPRO26 = 3
  gnDT_FOXPRO25 = 4
  gnDT_FOXPRO20 = 5
  gnDT_PARADOX4X = 6
  gnDT_PARADOX3X = 7
  gnDT_BTRIEVE = 8
  gnDT_EXCEL50 = 9
  gnDT_EXCEL40 = 10
  gnDT_EXCEL30 = 11
  gnDT_TEXTFILE = 12
  gnDT_SQLDB = 13
End Enum

' Constantes publiques
Public Const gsDEFAULT_DRIVER = "SQL Server"  ' Utilisée pour la base de registres du système
Public Const gnEOF_ERR = 626                  '
Public Const gnFTBLS = 0                      '
Public Const gnFFLDS = 1                      '
Public Const gnFINDX = 2                      '
Public Const gnMAX_GRID_ROWS = 31999          '
Public Const gnMAX_MEMO_SIZE = 20000          '
Public Const gnGETCHUNK_CUTOFF = 50           '

Public Const gnFORM_DATACTL = 0               '
Public Const gnFORM_NODATACTL = 1             '
Public Const gnFORM_DATAGRID = 2              '

Public Const gnRS_TABLE = vbRSTypeTable
Public Const gnRS_DYNASET = vbRSTypeDynaset
Public Const gnRS_SNAPSHOT = vbRSTypeSnapShot
Public Const gnRS_PASSTHRU = 8

Public Const gnCTLARRAYHEIGHT = 340&          '
Public Const gnSCREEN = 0                     ' Utilisée pour centrer les feuille à l'écran
Public Const gnMDIFORM = 1                    ' Utilisée pour centrer les feuilles sur la feuille frmMDI

Public Const TABLE_STR = "Table"
Public Const ATTACHED_STR = "Attached"
Public Const QUERY_STR = "Query"
Public Const FIELD_STR = "Field"
Public Const FIELDS_STR = "Fields"
Public Const INDEX_STR = "Index"
Public Const INDEXES_STR = "Indexes"
Public Const PROPERTY_STR = "Property"
Public Const PROPERTIES_STR = "Properties"

Public Const APP_CATEGORY = "Microsoft Visual Basic AddIns"

Private Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Private Declare Function LoadStringA Lib "user32" (ByVal hInstance As Long, ByVal wID As Long, ByVal lpBuffer As String, ByVal nBufferMax As Long) As Long
Private Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long

'LoadLibrary constants
Public Const LOAD_LIBRARY_AS_DATAFILE As Long = &H2

'GetLocaleInfo constants
Public Const LOCALE_SLANGUAGE = &H2
Public Const LOCALE_SABBREVLANGNAME = &H3

Private m_HelpServices As VsHelpServices.VsHelpServices
Private m_lcid  As Long
Private m_sHelpFile As String


Sub Main()
  frmMDI.Show
End Sub


'------------------------------------------------------------
' Cette fonction retourne le type de querydef
' pour l'élément sélectionné dans la collection
' querydefs de la feuille frmTables.
'------------------------------------------------------------
Function ActionQueryType(qdf As QueryDef) As String
  
  ' Vérifie s'il s'agit d'une requête Action
  If (qdf.Type And dbQAction) = 0 Then
    ActionQueryType = vbNullString
    Exit Function
  End If
  
  ' Doit être une requête Action
  Select Case qdf.Type
    Case dbQCrosstab
      ActionQueryType = "Cross Tab"
    Case dbQDelete
      ActionQueryType = "Delete"
    Case dbQUpdate
      ActionQueryType = "Update"
    Case dbQAppend
      ActionQueryType = "Append"
    Case dbQMakeTable
      ActionQueryType = "Make Table"
    Case dbQDDL
      ActionQueryType = "DDL"
    Case dbQSQLPassThrough
      ActionQueryType = "SQLPassThrough"
    Case dbQSetOperation
      ActionQueryType = "Set Operation"
    Case dbQSPTBulk
      ActionQueryType = "SPT Bulk"
    Case Else
      ActionQueryType = vbNullString
  End Select

End Function

'------------------------------------------------------------
' Cette fonction ajoute les caractères [] à des noms d'objets
' qui peuvent en avoir besoin car ils contiennent des espaces.
'------------------------------------------------------------
Function AddBrackets(rObjName As String) As String
  ' Ajoute des crochets aux noms des objets contenant des espaces.
  If InStr(rObjName, " ") > 0 And Mid(rObjName, 1, 1) <> "[" Then
    AddBrackets = "[" & rObjName & "]"
  Else
    AddBrackets = rObjName
  End If
End Function

'------------------------------------------------------------
' Cette fonction vérifie si une transaction est en cours
' et affiche un message si c'est le cas.
'------------------------------------------------------------
Function CheckTransPending(MSG As String) As Integer

  If gbTransPending Then
    MsgBox MSG & vbCrLf & MSG1, 48
    CheckTransPending = True
  Else
    CheckTransPending = False
  End If

End Function

'------------------------------------------------------------
' Efface le contenu des champs de la table et des feuilles
' de type Dynaset ou Snapshot.
'------------------------------------------------------------
Sub ClearDataFields(frm As Form, nCnt As Integer)
  Dim i As Integer

  ' Efface le contenu des champs de la feuille principale.
  For i = 0 To nCnt - 1
    frm.txtFieldData(i).Text = vbNullString
  Next
End Sub

'------------------------------------------------------------
' Cette procédure ferme toutes les feuilles frmDynaSnap,
' frmTableObj et frmDataGrid et recherche les feuilles dont la
' propriété Tag contient la valeur Recordset.
'------------------------------------------------------------
Sub CloseAllRecordsets()
  Dim i As Integer

  MsgBar MSG2, True
  While i < Forms.Count
    If Forms(i).Tag = "Recordset" Then
      Unload Forms(i)
    Else
      i = i + 1
    End If
  Wend
  MsgBar vbNullString, False

End Sub

'------------------------------------------------------------
' Cette fonction copie les données d'une table vers une autre,
' à partir de la feuille frmCopyStruct.
' Elle montre l'utilisation des transactions pour accélérer
' ce type d'opération.
'------------------------------------------------------------
Function CopyData(rFromDB As Database, rToDB As Database, rFromName As String, rToName As String) As Integer
  On Error GoTo CopyErr

  Dim recRecordset1 As Recordset, recRecordset2 As Recordset
  Dim i As Integer
  Dim nRC As Integer
  Dim fld As Field

  ' Ouvre les deux jeux d'enregistrements.
  Set recRecordset1 = rFromDB.OpenRecordset(rFromName)
  Set recRecordset2 = rToDB.OpenRecordset(rToName)
  gwsMainWS.BeginTrans
  While recRecordset1.EOF = False
    recRecordset2.AddNew
    ' Cette boucle copie les données de chaque champ
    ' dans la nouvelle table.
'    For Each fld In recRecordset1.Fields
    For i = 0 To recRecordset1.Fields.Count - 1
      Set fld = recRecordset1.Fields(i)
      recRecordset2(fld.Name).Value = fld.Value
    Next
    recRecordset2.Update
    recRecordset1.MoveNext
    nRC = nRC + 1
    ' Ce test permet de valider les transactions pour chaque
    ' groupe de 1000 enregistrements.
    If nRC = 1000 Then
      gwsMainWS.CommitTrans
      gwsMainWS.BeginTrans
      nRC = 0
    End If
  Wend
  gwsMainWS.CommitTrans

  CopyData = True
  Exit Function

CopyErr:
  gwsMainWS.Rollback
  ShowError
  CopyData = False
End Function

'------------------------------------------------------------
' Cette fonction copie la structure d'une table vers une
' nouvelle table dans la même base de données ou dans une autre.
'------------------------------------------------------------
Function CopyStruct(vFromDB As Database, vToDB As Database, vFromName As String, vToName As String, bCreateIndex As Integer) As Integer
  On Error GoTo CSErr

  Dim i As Integer
  Dim tblTableDefObj As TableDef
  Dim fldFieldObj As Field
  Dim indIndexObj As Index
  Dim tdf As TableDef
  Dim fld As Field
  Dim idx As Index
  
  ' Recherche si la table existe.
NameSearch:
'  For Each tdf In vToDB.Tabledefs
  For i = 0 To vToDB.TableDefs.Count - 1
    Set tdf = vToDB.TableDefs(i)
    If UCase(tdf.Name) = UCase(vToName) Then
      If MsgBox(MSG3, 4) = vbYes Then
         vToDB.TableDefs.Delete tdf.Name
      Else
         vToName = InputBox(MSG4)
         If Len(vToName) = 0 Then
           Exit Function
         Else
           GoTo NameSearch
         End If
      End If
      Exit For
    End If
  Next
  
  Set tblTableDefObj = gdbCurrentDB.CreateTableDef()
    
  ' Ôte le propriétaire de la table si besoin.
  tblTableDefObj.Name = StripOwner(vToName)

  ' Crée les champs
'  For Each fld In vFromDB.Tabledefs(vFromName).Fields
  For i = 0 To vFromDB.TableDefs(vFromName).Fields.Count - 1
    Set fld = vFromDB.TableDefs(vFromName).Fields(i)
    Set fldFieldObj = vFromDB.TableDefs(vFromName).CreateField(fld.Name, fld.Type, fld.Size)
    tblTableDefObj.Fields.Append fldFieldObj
  Next

  ' Crée les index.
  If bCreateIndex <> False Then
'    For Each idx In vFromDB.Tabledefs(vFromName).Indexes
    For i = 0 To vFromDB.TableDefs(vFromName).Indexes.Count - 1
      Set idx = vFromDB.TableDefs(vFromName).Indexes(i)
      Set indIndexObj = vFromDB.TableDefs(vFromName).CreateIndex(idx.Name)
      With indIndexObj
        indIndexObj.Fields = idx.Fields
        indIndexObj.Unique = idx.Unique
        If gsDataType <> gsSQLDB Then
          indIndexObj.Primary = idx.Primary
        End If
      End With
      tblTableDefObj.Indexes.Append indIndexObj
    Next
  End If

  ' Ajoute la nouvelle table.
  vToDB.TableDefs.Append tblTableDefObj

  CopyStruct = True
  Exit Function

CSErr:
  ShowError
  CopyStruct = False
End Function

'------------------------------------------------------------
' Cette fonction remplit une liste ou une zone de liste
' déroulante avec les tables (et la collection Querydefs) à partir des
' feuilles pour tables.
' ItemData a la valeur 0 pour un objet Tabledef et 1
' pour un objet Querydef.
'------------------------------------------------------------
Sub GetTableList(rctl As Control, rbIncludeQDFs As Integer, rbIncludeSys As Integer, rbStripConnect As Integer)
  On Error GoTo FTLErr
  
  Dim i As Integer
  Dim sTmp As String
  Dim tbl As TableDef
  Dim qdf As QueryDef
  
  ' Ajoute le contenu de la collection Tabledefs.
  For Each tbl In gdbCurrentDB.TableDefs
    sTmp = tbl.Name
    If rbIncludeSys Then
      rctl.AddItem sTmp
      rctl.ItemData(rctl.NewIndex) = 0
    Else
      If (gdbCurrentDB.TableDefs(sTmp).Attributes And dbSystemObject) = 0 Then
        rctl.AddItem sTmp
        rctl.ItemData(rctl.NewIndex) = 0
      End If
    End If
  Next
  
  ' Ajoute le contenu de la collection Querydefs.
  If rbIncludeQDFs Then
    For Each qdf In gdbCurrentDB.QueryDefs
      rctl.AddItem qdf.Name
      rctl.ItemData(rctl.NewIndex) = 1
    Next
  End If
  
  Exit Sub
  
FTLErr:
  ShowError
End Sub

'------------------------------------------------------------
' Cette fonction renvoie le type de champ numérique
' pour la chaîne passée en paramètre.
'------------------------------------------------------------
Function GetFieldType(rFldType As String) As Integer
  ' Renvoie la longueur du champ.
  If rFldType = "Text" Then
    GetFieldType = dbText
  Else
    Select Case rFldType
      Case "Counter"
        GetFieldType = dbLong
      Case "Boolean"
        GetFieldType = dbBoolean
      Case "Byte"
        GetFieldType = dbByte
      Case "Integer"
        GetFieldType = dbInteger
      Case "Long"
        GetFieldType = dbLong
      Case "Currency"
        GetFieldType = dbCurrency
      Case "Single"
        GetFieldType = dbSingle
      Case "Double"
        GetFieldType = dbDouble
      Case "Date/Time"
        GetFieldType = dbDate
      Case "Binary"
        GetFieldType = dbLongBinary
      Case "Memo"
        GetFieldType = dbMemo
    End Select
  End If

End Function

'------------------------------------------------------------
' Cette fonction renvoie une largeur de champ appropriée pour
' le type de champ passé en paramètre.
' Doit être utilisée sur les feuilles 'frmDynaSnap et
' frmTableObj.
'------------------------------------------------------------
Function GetFieldWidth(rType As Integer)
  Select Case rType
    Case dbBoolean
      GetFieldWidth = 850
    Case dbByte
      GetFieldWidth = 650
    Case dbInteger
      GetFieldWidth = 900
    Case dbLong
      GetFieldWidth = 1100
    Case dbCurrency
      GetFieldWidth = 1800
    Case dbSingle
      GetFieldWidth = 1800
    Case dbDouble
      GetFieldWidth = 2200
    Case dbDate
      GetFieldWidth = 2000
    Case dbText
      GetFieldWidth = 3250
    Case dbLongBinary
      GetFieldWidth = 3250
    Case dbMemo
      GetFieldWidth = 3250
    Case Else
      GetFieldWidth = 3250
  End Select

End Function

'------------------------------------------------------------
' Cette fonction renvoie les paramètres du registre en
' passant comme paramètre la section et l'entrée à rechercher.
'------------------------------------------------------------
Function GetRegistryString(ByVal vsItem As String, ByVal vsDefault As String) As String
  GetRegistryString = GetSetting(APP_CATEGORY, APPNAME, vsItem, vsDefault)
End Function

'------------------------------------------------------------
' Cette procédure cache les menus et la barre d'outils
' visibles uniquement quand une base de données est ouverte.
'------------------------------------------------------------
Sub HideDBTools()
  frmMDI.mnuDBClose.Enabled = False
  frmMDI.mnuDBImpExp.Enabled = False
  frmMDI.mnuUtil.Enabled = False
  frmMDI.mnuUBar1.Visible = False
  frmMDI.mnuUAttachments.Visible = False
  frmMDI.mnuUGroupsUsers.Visible = False
  frmMDI.mnuUSystemDB.Visible = False
  frmMDI.tlbToolBar.Buttons("BeginTrans").Enabled = False
  frmMDI.tlbToolBar.Buttons("Commit").Enabled = False
  frmMDI.tlbToolBar.Buttons("Rollback").Enabled = False
End Sub

'------------------------------------------------------------
' Cette procédure affiche les messages passés en paramètre
' dans la barre d'état de la feuille MDI.
'------------------------------------------------------------
Sub MsgBar(rsMsg As String, rPauseFlag As Integer)
  If Len(rsMsg) = 0 Then
    Screen.MousePointer = vbDefault
    frmMDI.stsStatusBar.Panels(1).Text = MSG5
  Else
    If rPauseFlag Then
      frmMDI.stsStatusBar.Panels(1).Text = rsMsg & MSG6
    Else
      frmMDI.stsStatusBar.Panels(1).Text = rsMsg
    End If
  End If
  frmMDI.stsStatusBar.Refresh
End Sub

'==================================================
' Procédure: ObjectExists
'
' Objet: Détermine si un membre existe ou non.
'          identique à la procédure MemberExists,
'          sauf que le premier argument est déclaré
'          comme un objet. Cela autorise un passage
'          dans des collections telles que
'          VBComponents, VBProjects, etc.
' Arguments:
'   pColl: Nom de la collection à ajouter.
'   sMemName: Nom(touche) du membre à vérifier.
' Valeurs renvoyées:
'   True: le membre existe dans la collection.
'   False: le membre n'existe pas dans la collection.
' Maintenance: J$
'==================================================
Function ObjectExists(pColl As Object, sMemName As String) As Boolean
Dim pObj As Object
  
  On Error Resume Next
  Err = 0
  Set pObj = pColl(sMemName)
  ObjectExists = (Err = 0)
End Function


'------------------------------------------------------------
' Cette procédure actualise une liste passée comme un objet.
'------------------------------------------------------------
Sub RefreshTables(rListObject As Object)
  On Error GoTo TRefErr

  Dim tdf As TableDef
  Dim qdf As QueryDef
  Dim sTmp As String
    
  Dim i As Integer
    
  MsgBar MSG7, True
  Screen.MousePointer = vbHourglass

  ' Si cette méthode est appelée pour actualiser la
  ' fenêtre de la base de données, la méthode
  ' consistant à remplir la zone de liste avec les
  ' noms de la table est ignorée.
  If rListObject Is Nothing Then GoTo LoadTreeView

  rListObject.Clear
  If frmMDI.mnuPAllowSys.Checked Then
    ' Lister toutes les tables.
    For Each tdf In gdbCurrentDB.TableDefs
      If (tdf.Attributes And dbAttachedTable) = dbAttachedTable Then
        If Left(tdf.Connect, 1) = ";" Then
          ' Doit être une table attachée Microsoft Access.
          rListObject.AddItem tdf.Name & " -> Microsoft Access"
        Else
          ' Doit être une table attachée ISAM.
          rListObject.AddItem tdf.Name & " -> " & Left(tdf.Connect, InStr(tdf.Connect, ";") - 1)
        End If
      ElseIf (tdf.Attributes And dbAttachedODBC) = dbAttachedODBC Then
        rListObject.AddItem tdf.Name & " -> ODBC"
      Else
        rListObject.AddItem tdf.Name
      End If
    Next
  Else
    ' Ne pas lister toutes les tables du système.
    For Each tdf In gdbCurrentDB.TableDefs
      If (tdf.Attributes And dbSystemObject) = 0 Then
        If (tdf.Attributes And dbAttachedTable) = dbAttachedTable Then
          If Left(tdf.Connect, 1) = ";" Then
            ' Doit être une table attachée Microsoft Access.
            rListObject.AddItem tdf.Name & " -> Microsoft Access"
          Else
            ' Doit être une table attachée ISAM.
            rListObject.AddItem tdf.Name & " -> " & Left(tdf.Connect, InStr(tdf.Connect, ";") - 1)
          End If
        ElseIf (tdf.Attributes And dbAttachedODBC) = dbAttachedODBC Then
          rListObject.AddItem tdf.Name & " -> ODBC"
        Else
          rListObject.AddItem tdf.Name
        End If
      End If
    Next
  End If
  ' Sélectionne le premier élément s'il y en a un.
  If rListObject.ListCount > 0 Then
    rListObject.ListIndex = 0
  End If
  
LoadTreeView:
  frmDatabase.LoadDatabase
  
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  Exit Sub

TRefErr:
  ShowError
End Sub

'------------------------------------------------------------
' Cette fonction retourne la taille du type de champ
' passé en paramètre.
' Utilisée par la feuille frmAddField.
'------------------------------------------------------------
Function SetFldProperties(rnType As Integer) As Integer
  ' Renvoie la longueur du champ.
  Select Case rnType
    Case dbBoolean
      SetFldProperties = 1
    Case dbByte
      SetFldProperties = 1
    Case dbInteger
      SetFldProperties = 2
    Case dbLong
      SetFldProperties = 4
    Case dbCurrency
      SetFldProperties = 8
    Case dbSingle
      SetFldProperties = 4
    Case dbDouble
      SetFldProperties = 8
    Case dbDate
      SetFldProperties = 8
    Case dbText
      SetFldProperties = 50
    Case dbLongBinary
      SetFldProperties = 0
    Case dbMemo
      SetFldProperties = 0
  End Select
End Function

'------------------------------------------------------------
' Cette procédure affiche les menus et la barre d'outils
' visibles uniquement quand une base de données est ouverte.
'------------------------------------------------------------
Sub ShowDBTools()
  Dim sTmp As String

  frmMDI.mnuDBClose.Enabled = True
  frmMDI.mnuDBImpExp.Enabled = True
  frmMDI.mnuUtil.Enabled = True
  frmMDI.tlbToolBar.Buttons("BeginTrans").Enabled = True
  frmMDI.tlbToolBar.Buttons("Commit").Enabled = False
  frmMDI.tlbToolBar.Buttons("Rollback").Enabled = False
  frmMDI.tlbToolBar.Refresh

  ' Définit les éléments généraux qui s'appliquent ou ne s'appliquent pas aux fichiers MDB.
  If gsDataType = gsMSACCESS Then
    frmMDI.mnuUBar1.Visible = True
    frmMDI.mnuUAttachments.Visible = True
    frmMDI.mnuUGroupsUsers.Visible = True
    frmMDI.mnuUSystemDB.Visible = True
    frmSQL.cmdSaveQueryDef.Visible = True
    frmMDI.mnuDBPURename.Visible = True
  Else
    frmSQL.cmdSaveQueryDef.Visible = False
    frmMDI.mnuDBPURename.Visible = False
  End If

  ' Définit les éléments spécifiques à ODBC.
  If gsDataType = gsSQLDB Then
    If gnRSType = gnRS_TABLE Then
      frmMDI.tlbToolBar.Buttons("Dynaset").Value = tbrPressed
      gnRSType = gnRS_DYNASET
    End If
    frmMDI.tlbToolBar.Buttons("PassThrough").Visible = True
    frmMDI.tlbToolBar.Buttons("Table").Visible = False
  Else
    If gnRSType = gnRS_PASSTHRU Then
      frmMDI.tlbToolBar.Buttons("Dynaset").Value = tbrPressed
      gnRSType = gnRS_DYNASET
    End If
    frmMDI.tlbToolBar.Buttons("PassThrough").Visible = False
    frmMDI.tlbToolBar.Buttons("Table").Visible = True
  End If
  frmMDI.tlbToolBar.Refresh
  ' Affiche les deux feuilles fille principales.
  frmDatabase.Show
  frmSQL.Show
End Sub

'------------------------------------------------------------
' Cette procédure affiche le message d'erreur avec son code
' correspondant et demande à afficher la collection Errors s'il
' s'agit d'une erreur d'accès à la base de données.
'------------------------------------------------------------
Sub ShowError()
  Dim sTmp As String

  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False

  sTmp = "L'erreur suivante s'est produite:" & vbCrLf & vbCrLf
  ' Ajoute la chaîne d'erreur.
  sTmp = sTmp & Err.Description & vbCrLf
  ' Ajoute le numéro de l'erreur.
  sTmp = sTmp & MSG8 & Err
  
  Beep
  ' Vérifie si l'erreur provient de la collection des
  ' erreurs de la base de données.
  If DBEngine.Errors.Count > 0 Then
    If DBEngine.Errors(0).Number = Err Then
      ' Demande à afficher la collection des erreurs.
      sTmp = sTmp & vbCrLf & vbCrLf & MSG9
      ' Émet un signal sonore et affiche l'erreur.
      If MsgBox(sTmp, vbYesNo + vbQuestion) = vbYes Then
        RefreshErrors
      End If
    Else
      MsgBox sTmp
    End If
  Else
    MsgBox sTmp
  End If

End Sub

'------------------------------------------------------------
' Cette fonction enlève la chaîne de connexion de la table attachée.
'------------------------------------------------------------
Function StripConnect(rsTblName As String) As String
  If InStr(rsTblName, "->") > 0 Then
    StripConnect = Left(rsTblName, InStr(rsTblName, "->") - 2)
  Else
    StripConnect = rsTblName
  End If

End Function

'------------------------------------------------------------
' Cette fonction enlève les [] des objets de base de données.
'------------------------------------------------------------
Function StripBrackets(rsObjName As String) As String
  ' Enlève les crochets aux noms des objets contenant des espaces.
  If Mid(rsObjName, 1, 1) = "[" Then
    StripBrackets = Mid(rsObjName, 2, Len(rsObjName) - 2)
  Else
    StripBrackets = rsObjName
  End If

End Function

'------------------------------------------------------------
' Cette fonction enlève le nom du fichier d'une chaîne contenant
' le chemin et le nom de fichier.
'------------------------------------------------------------
Function StripFileName(rsFileName As String) As String
  On Error Resume Next
  Dim i As Integer

  For i = Len(rsFileName) To 1 Step -1
    If Mid(rsFileName, i, 1) = "\" Then
      Exit For
    End If
  Next

  StripFileName = Mid(rsFileName, 1, i - 1)

End Function

'------------------------------------------------------------
' Cette fonction ôte les caractères non ASCII des données
' d'un champ Memo avant de l'afficher (cela n'est pas
' toujours demandé).
'------------------------------------------------------------
Function StripNonAscii(rvntVal As Variant) As String
  Dim i As Integer
  Dim sTmp As String

  ' Écrasé pour activer les caractères DBCS.
  StripNonAscii = rvntVal
  Exit Function

  For i = 1 To Len(rvntVal)
    If Asc(Mid(rvntVal, i, 1)) < 32 Or Asc(Mid(rvntVal, i, 1)) > 126 Then
      sTmp = sTmp & " "
    Else
      sTmp = sTmp & Mid(rvntVal, i, 1)
    End If
  Next

  StripNonAscii = sTmp

End Function

'------------------------------------------------------------
' Extrait le propriétaire du nom des tables ODBC.
'------------------------------------------------------------
Function StripOwner(rsTblName As String) As String

  If InStr(rsTblName, ".") > 0 Then
    rsTblName = Mid(rsTblName, InStr(rsTblName, ".") + 1, Len(rsTblName))
  End If
  StripOwner = rsTblName

End Function

'------------------------------------------------------------
' Renvoie la chaîne True ou False.
'------------------------------------------------------------
Function stTrueFalse(rvntTF As Variant) As String
  If rvntTF Then
    stTrueFalse = "True"
  Else
    stTrueFalse = "False"
  End If
End Function

'------------------------------------------------------------
' Renvoie "" (chaîne vide) si le champ a la valeur Null.
'------------------------------------------------------------
Function vFieldVal(rvntFieldVal As Variant) As Variant
  If IsNull(rvntFieldVal) Then
    vFieldVal = vbNullString
  Else
    vFieldVal = CStr(rvntFieldVal)
  End If
End Function

'------------------------------------------------------------
' Charge tous les paramètres du Gestionnaire de données
' enregistrés dans le registre.
'------------------------------------------------------------
Sub LoadRegistrySettings()
  On Error Resume Next
  
  Dim sTmp As String
  Dim x As Integer

  glQueryTimeout = Val(GetRegistryString("QueryTimeout", "5"))
  glLoginTimeout = Val(GetRegistryString("LoginTimeout", "20"))
  
  
  frmMDI.mnuPOpenOnStartup.Checked = Val(GetRegistryString("OpenOnStartup", "0"))
  frmMDI.mnuPAllowSys.Checked = Val(GetRegistryString("AllowSys", "0"))

  ' Obtient les dernières bases de données ouvertes.
  For x = 1 To 8
    sTmp = GetRegistryString("MRUDatabase" & x, "")
    If Len(sTmp) > 0 Then
      frmMDI.mnuBarMRU.Visible = True
      frmMDI.mnuDBMRU(x).Caption = "&" & x & " " & sTmp
      frmMDI.mnuDBMRU(x).Visible = True
      sTmp = GetRegistryString("MRUConnect" & x, "")
      frmMDI.mnuDBMRU(x).Tag = sTmp
    End If
  Next

  ' Obtient la dernière base de données utilisée en dehors du registre.
  gsDataType = GetRegistryString("DataType", vbNullString)
  gsDBName = GetRegistryString("DatabaseName", vbNullString)
  gsODBCDatasource = GetRegistryString("ODBCDatasource", vbNullString)
  gsODBCDatabase = GetRegistryString("ODBCDatabase", vbNullString)
  gsODBCUserName = GetRegistryString("ODBCUserName", vbNullString)
  gsODBCPassword = GetRegistryString("ODBCPassword", vbNullString)
  gsODBCDriver = GetRegistryString("ODBCDriver", vbNullString)
  gsODBCServer = GetRegistryString("ODBCServer", vbNullString)

  sTmp = GetRegistryString("ViewMode", CStr(gnFORM_NODATACTL))
  Select Case Val(sTmp)
    Case gnFORM_NODATACTL
      gnFormType = gnFORM_NODATACTL
    Case gnFORM_DATACTL
      gnFormType = gnFORM_DATACTL
    Case gnFORM_DATAGRID
      gnFormType = gnFORM_DATAGRID
  End Select
  sTmp = GetRegistryString("RecordsetType", CStr(vbRSTypeDynaset))
  Select Case Val(sTmp)
    Case vbRSTypeTable
      gnRSType = gnRS_TABLE
    Case vbRSTypeDynaset
      gnRSType = gnRS_DYNASET
    Case vbRSTypeSnapShot
      gnRSType = gnRS_SNAPSHOT
    Case gnRS_PASSTHRU
      gnRSType = gnRS_PASSTHRU
  End Select
  
  DoEvents
  Select Case gnFormType
    Case gnFORM_NODATACTL
      frmMDI.tlbToolBar.Buttons("NoDataControl").Value = tbrPressed
    Case gnFORM_DATACTL
      frmMDI.tlbToolBar.Buttons("DataControl").Value = tbrPressed
    Case gnFORM_DATAGRID
      frmMDI.tlbToolBar.Buttons("DBGrid").Value = tbrPressed
  End Select
  Select Case gnRSType
    Case vbRSTypeDynaset
      frmMDI.tlbToolBar.Buttons("Dynaset").Value = tbrPressed
    Case vbRSTypeSnapShot
      frmMDI.tlbToolBar.Buttons("Snapshot").Value = tbrPressed
    Case vbRSTypeTable
      frmMDI.tlbToolBar.Buttons("Table").Value = tbrPressed
    Case gnRS_PASSTHRU
      frmMDI.tlbToolBar.Buttons("PassThrough").Value = tbrPressed
  End Select
  
End Sub

'------------------------------------------------------------
' Enregiste les valeurs en cours du Gestionnaire de données
' dans VISDATA.INI.
'------------------------------------------------------------
Sub SaveINISettings()
  On Error Resume Next

  Dim i As Integer
  
  SaveSetting APP_CATEGORY, APPNAME, "DataType", gsDataType
  SaveSetting APP_CATEGORY, APPNAME, "DatabaseName", gsDBName
  SaveSetting APP_CATEGORY, APPNAME, "ODBCDatasource", gsODBCDatasource
  SaveSetting APP_CATEGORY, APPNAME, "ODBCDatabase", gsODBCDatabase
  SaveSetting APP_CATEGORY, APPNAME, "ODBCUserName", gsODBCUserName
  SaveSetting APP_CATEGORY, APPNAME, "ODBCPassword", gsODBCPassword
  SaveSetting APP_CATEGORY, APPNAME, "ODBCDriver", gsODBCDriver
  SaveSetting APP_CATEGORY, APPNAME, "ODBCServer", gsODBCServer
  SaveSetting APP_CATEGORY, APPNAME, "QueryTimeout", glQueryTimeout
  SaveSetting APP_CATEGORY, APPNAME, "LoginTimeout", glLoginTimeout
  DBEngine.LoginTimeout = glLoginTimeout
  SaveSetting APP_CATEGORY, APPNAME, "ViewMode", gnFormType
  SaveSetting APP_CATEGORY, APPNAME, "RecordsetType", gnRSType
  
  SaveSetting APP_CATEGORY, APPNAME, "OpenOnStartup", IIf(frmMDI.mnuPOpenOnStartup.Checked, "-1", "0")
  SaveSetting APP_CATEGORY, APPNAME, "AllowSys", IIf(frmMDI.mnuPAllowSys.Checked, "-1", "0")

  For i = 1 To 8
    If frmMDI.mnuDBMRU(i).Visible Then
      SaveSetting APP_CATEGORY, APPNAME, "MRUDatabase" & i, Mid(frmMDI.mnuDBMRU(i).Caption, 4, Len(frmMDI.mnuDBMRU(i).Caption))
      SaveSetting APP_CATEGORY, APPNAME, "MRUConnect" & i, frmMDI.mnuDBMRU(i).Tag
    Else
      SaveSetting APP_CATEGORY, APPNAME, "MRUDatabase" & i, ""
      SaveSetting APP_CATEGORY, APPNAME, "MRUConnect" & i, ""
    End If
  Next

  SaveSetting APP_CATEGORY, APPNAME, "WindowState", frmMDI.WindowState
  If frmMDI.WindowState = vbNormal Then
    SaveSetting APP_CATEGORY, APPNAME, "WindowTop", frmMDI.Top
    SaveSetting APP_CATEGORY, APPNAME, "WindowLeft", frmMDI.Left
    SaveSetting APP_CATEGORY, APPNAME, "WindowWidth", frmMDI.Width
    SaveSetting APP_CATEGORY, APPNAME, "WindowHeight", frmMDI.Height
  End If
  SaveSetting APP_CATEGORY, APPNAME, "ViewMode", gnFormType
  SaveSetting APP_CATEGORY, APPNAME, "RecordsetType", gnRSType

End Sub

'------------------------------------------------------------
' Cette procédure ouvre la feuille de données et affiche le
' message approprié dans la barre d'état en fonction des
' sélections de l'utilisateur dans la feuille MDI principale.
'------------------------------------------------------------
Sub OpenTable(rName As String)
  On Error GoTo OpenTableErr

  Dim rsTmp As Recordset
  Dim rsADOTmp As ADODB.Recordset
  Dim conADOConn As ADODB.Connection
  Dim sTmp As String
  Dim nAttach As Integer
  Dim frmTmp As Form
  
  If gsDataType = gsMSACCESS Then   ' Vérifier s'il existe des tables attachées, s'il s'agit d'un fichier MDB.
    If (gdbCurrentDB.TableDefs(rName).Attributes And dbAttachedTable) = dbAttachedTable Then
      nAttach = 1
    ElseIf (gdbCurrentDB.TableDefs(rName).Attributes And dbAttachedODBC) = dbAttachedODBC Then
      nAttach = 2
    End If
    If nAttach > 0 And gnRSType = gnRS_TABLE Then
      Beep
      If MsgBox(MSG10, vbYesNo + vbQuestion) = vbYes Then
        frmMDI.tlbToolBar.Buttons("Dynaset").Value = tbrPressed  ' Réinitialiser la feuille de réponses dynamique.
      Else
        Exit Sub
      End If
    End If
  End If
  
  If nAttach > 0 Then
    If gnRSType = gnRS_DYNASET Then
      sTmp = MSG11
    ElseIf gnRSType = gnRS_SNAPSHOT Then
      sTmp = MSG12
    End If
  Else
    If gnRSType = gnRS_TABLE Then
      sTmp = MSG13
    ElseIf gnRSType = gnRS_DYNASET Then
      sTmp = MSG14
    ElseIf gnRSType = gnRS_SNAPSHOT Then
      sTmp = MSG15
    ElseIf gnRSType = gnRS_PASSTHRU Then
      sTmp = MSG16
    End If
  End If
  
  MsgBar sTmp, True
  
  Screen.MousePointer = vbHourglass
  If gnRSType = gnRS_TABLE Then
    Set rsTmp = gdbCurrentDB.OpenRecordset(rName, dbOpenTable)
    sTmp = "Table:"
  ElseIf gnRSType = gnRS_DYNASET Then
    Set rsTmp = gdbCurrentDB.OpenRecordset(rName, dbOpenDynaset)
    sTmp = "Dynaset:"
  ElseIf gnRSType = gnRS_SNAPSHOT Then
    Set rsTmp = gdbCurrentDB.OpenRecordset(rName, dbOpenSnapshot)
    sTmp = "Snapshot:"
  ElseIf gnRSType = gnRS_PASSTHRU Then
    Set rsTmp = gdbCurrentDB.OpenRecordset(rName, dbOpenSnapshot, dbSQLPassThrough)
    sTmp = "Passthrough Snapshot:"
  End If
  Screen.MousePointer = vbDefault
  
  If gnFormType = gnFORM_NODATACTL Then
    If gnRSType = gnRS_TABLE Then
      Set frmTmp = New frmTableObj
      sTmp = "Table:"
    Else
      Set frmTmp = New frmDynaSnap
    End If
    Set frmTmp.mrsFormRecordset = rsTmp
  ElseIf gnFormType = gnFORM_DATACTL Then
    Set frmTmp.mrsFormRecordset = rsTmp
    Set frmTmp = New frmDataControl
  ElseIf gnFormType = gnFORM_DATAGRID Then
    Set frmTmp = New frmDataGrid
    'convertir le jeu d'enregistrements en jeu d'enregistrements ADO
    Set conADOConn = New ADODB.Connection
    With conADOConn
      If Len(gsODBCDatasource) = 0 Then
        If gsDataType = gsMSACCESS Then
          .ConnectionString = "PROVIDER=Microsoft.Jet.OLEDB.3.51;Data Source=" & gsDBName
        Else
          .ConnectionString = "Provider=MSDASQL;Data Source=" & gsDBName
  End If
      Else
        .ConnectionString = "PROVIDER=MSDASQL;" & Mid$(gdbCurrentDB.Connect, 6)
      End If
      .Open
    End With
    Set rsADOTmp = New ADODB.Recordset
    With rsADOTmp
      .Open rsTmp.Name, conADOConn, adOpenStatic, adLockOptimistic, adCmdTable
    End With
  
  Set frmTmp.mrsFormRecordset = rsADOTmp
  End If
  

  frmTmp.Caption = sTmp & rName
  frmTmp.Show

  MsgBar vbNullString, False
  
  Exit Sub
OpenTableErr:
  ShowError
End Sub

'------------------------------------------------------------
' Ouvrir une requête avec le type de feuille défini par
' l'utilisateur.
'------------------------------------------------------------
Sub OpenQuery(rName As String, bTemp As Boolean)
  On Error GoTo OpenQueryErr

  Dim sTmp As String
  Dim rsTmp As Recordset
  Dim rsADOTmp As ADODB.Recordset
  Dim conADOConn As ADODB.Connection
  Dim qdfTmp As QueryDef
  Dim sQueryType As String
  Dim frmTmp As Form
  Dim nDoIt As Integer
  Dim bReturnsRows As Boolean
  Dim bTriedAlready As Boolean

  If bTemp Then
    Set qdfTmp = gdbCurrentDB.CreateQueryDef("", rName)
    If MsgBox(MSG17, vbYesNo + vbQuestion + vbDefaultButton2) = vbYes Then
      sTmp = InputBox(MSG18)
      If Len(sTmp) > 0 Then
        qdfTmp.Connect = sTmp
      End If
    End If
    ' Considèrer qu'il n'existe pas de ligne renvoyée
    ' avec laquelle commencer.
    qdfTmp.ReturnsRecords = False
  Else
    Set qdfTmp = gdbCurrentDB.QueryDefs(rName)
    sQueryType = ActionQueryType(qdfTmp)
    If qdfTmp.Type <> dbQSQLPassThrough Then
      ' Ceci n'est pas une requête SQL Direct (Passthrough);
      ' ReturnsRecords doit être défini.
      If qdfTmp.Type = 0 Or qdfTmp.Type = dbQCrosstab Then
        qdfTmp.ReturnsRecords = True
      Else
        qdfTmp.ReturnsRecords = False
      End If
    Else
      ' le prendre du qdf si c'est un passthrough
      bReturnsRows = qdfTmp.ReturnsRecords
    End If
  End If
  
  If qdfTmp.ReturnsRecords And (gnRSType = gnRS_TABLE) Then
    Beep
    If MsgBox(MSG19, vbYesNo + vbQuestion) = vbYes Then
      frmMDI.tlbToolBar.Buttons("Dynaset").Value = tbrPressed ' Réinitialiser le jeu d'enregistrements.
    Else
      Exit Sub
    End If
  End If
  
 If bReturnsRows Then
  SetQDFParams qdfTmp
MakeDynaset:
    Screen.MousePointer = vbHourglass
    If qdfTmp.Type = dbQSQLPassThrough Then
      MsgBar MSG16, True
      Set rsTmp = qdfTmp.OpenRecordset(dbOpenSnapshot, dbSQLPassThrough)
    ElseIf gnRSType = gnRS_SNAPSHOT Then
      MsgBar MSG20, True
      Set rsTmp = qdfTmp.OpenRecordset(dbOpenSnapshot)
    Else
      MsgBar MSG21, True
      Set rsTmp = qdfTmp.OpenRecordset(dbOpenDynaset)
    End If
    Screen.MousePointer = vbDefault
    
    If gnFormType = gnFORM_NODATACTL Then
      Set frmTmp = New frmDynaSnap
      Set frmTmp.mrsFormRecordset = rsTmp
    ElseIf gnFormType = gnFORM_DATACTL Then
      Set frmTmp = New frmDataControl
      If qdfTmp.Parameters.Count > 0 Then
        frmTmp.mbIsParameterized = True
      End If
      Set frmTmp.mrsFormRecordset = rsTmp
    ElseIf gnFormType = gnFORM_DATAGRID Then
      Set frmTmp = New frmDataGrid
    'convertir le jeu d'enregistrements en jeu d'enregistrements ADO
      Set conADOConn = New ADODB.Connection
      With conADOConn
        If Len(gsODBCDatasource) = 0 Then
          If gsDataType = gsMSACCESS Then
            .ConnectionString = "PROVIDER=Microsoft.Jet.OLEDB.3.51;Data Source=" & gsDBName
          Else
            .ConnectionString = "Provider=MSDASQL;Data Source=" & gsDBName
    End If
        Else
          .ConnectionString = "PROVIDER=MSDASQL;" & Mid$(gdbCurrentDB.Connect, 6)
        End If
        .Open
      End With
      Set rsADOTmp = New ADODB.Recordset
      With rsADOTmp
        .Open rName, conADOConn, adOpenStatic, adLockOptimistic
      End With
    Set frmTmp.mrsFormRecordset = rsADOTmp
    End If
    
    If Len(qdfTmp.SQL) > 50 Then
      frmTmp.Caption = MSG22
    Else
      frmTmp.Caption = qdfTmp.SQL
    End If
    frmTmp.Show
    
  Else
    Screen.MousePointer = vbDefault
    If Len(sQueryType) > 0 Then
      nDoIt = MsgBox(MSG23 & sQueryType & MSG24, vbYesNo + vbQuestion)
    Else
      'no name so just try to execute it
      nDoIt = vbYes
    End If
    If nDoIt = vbYes Then
      SetQDFParams qdfTmp
      Screen.MousePointer = vbHourglass
      MsgBar MSG25, True
      qdfTmp.Execute
      If gdbCurrentDB.RecordsAffected > 0 Then
        If gbTransPending Then gbDBChanged = True
      End If
    End If
  End If
  
  MsgBar vbNullString, False
  
  Exit Sub
OpenQueryErr:
  If Err = 3065 Or Err = 3078 And (Not bTriedAlready) Then
    bTriedAlready = True
    ' Renvoi d'une ligne; il faut essayer de créer
    ' un jeu d'enregistrements.
    Resume MakeDynaset
  ElseIf Not bTriedAlready Then
  ShowError
  End If
  Screen.MousePointer = vbHourglass
  MsgBar vbNullString, False
End Sub

'------------------------------------------------------------
' Cette procédure affiche toutes les données du champ dans
' la ligne en cours des tables et des feuilles de type
' Dynaset ou Snapshot.
'------------------------------------------------------------
Sub DisplayCurrentRecord(frm As Object, rec As Recordset, lCnt As Long, bNew As Integer)
  Dim i As Integer
  Dim sCurrStat As String
  Dim lCurrRec As Long
  Dim bNoInd As Integer

  On Error GoTo DCRErr

  Screen.MousePointer = vbHourglass

  sCurrStat = "Ligne "
   
  ' Vérifier si une table sans index est utilisée.
  If rec.Type = dbOpenTable Then
    If gdbCurrentDB(rec.Name).Indexes.Count = 0 Then
      bNoInd = True
    End If
  End If
   
  ' Vérifier s'il existe un jeu d'enregistrements vide.
  If rec.RecordCount > 0 Then
    lCurrRec = (lCnt * (rec.PercentPosition * 0.01)) + 1
  End If
     
  ' Vérifier s'il existe des indicateurs BOF/EOF indiquant
  ' qu'il s'agit d'un enregistrement valide.
  If bNew Then
    If bNoInd Then
      sCurrStat = lCnt & " Lignes"
    Else
      sCurrStat = lCurrRec & "/" & lCnt
    End If
  Else
    If rec.BOF Then
      sCurrStat = "(BOF)/" & lCnt
      ClearDataFields frm, rec.Fields.Count
    ElseIf rec.EOF Then
      sCurrStat = "(EOF)/" & lCnt
      ClearDataFields frm, rec.Fields.Count
    Else
      If bNoInd Then
        sCurrStat = lCnt & " Lignes"
      Else
        sCurrStat = lCurrRec & "/" & lCnt
      End If
      ' Placer les données dans les champs de la feuille.
      For i = 0 To rec.Fields.Count - 1
        If rec(i).Type = dbMemo Then
          If rec(i).FieldSize() < gnGETCHUNK_CUTOFF Then
            frm.txtFieldData(i).Text = StripNonAscii(vFieldVal(rec(i)))
          Else
            frm.txtFieldData(i).Text = StripNonAscii(vFieldVal(rec(i).GetChunk(0, gnGETCHUNK_CUTOFF)))
          End If
        ElseIf rec(i).Type = dbText Then
          frm.txtFieldData(i).Text = vFieldVal(rec(i))
        Else
          frm.txtFieldData(i).Text = vFieldVal(rec(i))
        End If
      Next
    End If
  End If
  If rec.Updatable = False Then sCurrStat = sCurrStat & MSG26
  frm.lblStatus.Caption = sCurrStat
  Screen.MousePointer = vbDefault
  Exit Sub

DCRErr:
  ShowError
  Resume Next    ' Il est donc possible d'essayer et d'afficher autant de données que possible.
End Sub

'------------------------------------------------------------
' Cette fonction vérifie si le nom de la table passée en
' paramètre existe dans la collection Tabledefs ou Querydefs.
' Si elle trouve le nom, elle demande de supprimer la table
' en renvoyant la valeur False si l'utilisateur décide de la
' supprimer, ou True dans le cas contraire.
' Si le nom n'est pas trouvé, la fonction renvoie la valeur False.
'------------------------------------------------------------
Function DupeTableName(rName As String) As Integer
  On Error GoTo DTNErr

  Dim tdf As TableDef
  Dim qdf As QueryDef
  Dim i As Integer

  For Each tdf In gdbCurrentDB.TableDefs
    If UCase(tdf.Name) = UCase(rName) Then
      If MsgBox(MSG27, vbYesNo + vbQuestion) = vbYes Then
        gdbCurrentDB.TableDefs.Delete rName
        DupeTableName = False
      Else
        DupeTableName = True
      End If
      Exit Function
    End If
  Next

  If gsDataType = gsMSACCESS Then
    For Each qdf In gdbCurrentDB.QueryDefs
      If UCase(qdf.Name) = UCase(rName) Then
        If MsgBox(MSG28, vbYesNo + vbQuestion) = vbYes Then
          gdbCurrentDB.QueryDefs.Delete rName
          DupeTableName = False
        Else
          DupeTableName = True
        End If
        Exit Function
      End If
    Next
  End If

  DupeTableName = False
  Exit Function

DTNErr:
  ShowError
  DupeTableName = False
End Function

'------------------------------------------------------------
' Cette procédure décharge toutes les feuilles, à l'exception
' des feuilles Tables, SQL et MDI.
'------------------------------------------------------------
Sub UnloadAllForms()
  On Error Resume Next
  
  Dim i As Integer
  
  ' Ferme toutes les feuilles à l'exception des feuilles
  ' Tables et SQL.
  For i = Forms.Count - 1 To 1 Step -1
    Unload Forms(i)
  Next
End Sub

'------------------------------------------------------------
' Cette procédure balaie la collection des paramètres dans
' une requête paramètrée et demande à l'utilisateur
' la valeur de chaque paramètre.
'------------------------------------------------------------
Sub SetQDFParams(rqdf As QueryDef)
  On Error GoTo SPErr
  
  Dim prm As Parameter
  Dim sTmp As String
  
  For Each prm In rqdf.Parameters
    ' Obtient la valeur de l'utilisateur.
    sTmp = InputBox(MSG29, "'" & prm.Name & "':")
    ' Stocke la valeur.
    prm.Value = CVar(sTmp)
  Next
  
  Exit Sub
    
SPErr:
  ShowError
End Sub

'------------------------------------------------------------
' Cette procédure actualise la feuille des erreurs avec les
'dernières erreurs.
'------------------------------------------------------------
Sub RefreshErrors()
  On Error GoTo RErr
  
  Dim errObj As Error
  Dim i As Integer

  If DBEngine.Errors.Count = 0 Then
    MsgBox MSG30, 48
    Unload frmErrors
    Exit Sub
  End If

  frmErrors.Show
  frmErrors.lstErrors.Clear
  For i = 0 To DBEngine.Errors.Count - 1
    Set errObj = DBEngine.Errors(i)
    frmErrors.lstErrors.AddItem errObj.Number & vbTab & errObj.Source & vbTab & errObj.Description
  Next
  frmErrors.SetFocus

  Exit Sub
  
RErr:
  MsgBox MSG31, 48
  Unload frmErrors
  Exit Sub
End Sub

'------------------------------------------------------------
' Cette procédure ajoute la dernière base de données ouverte
' dans la liste des bases de données ouvertes précédemment
' dans le menu Fichier.
'------------------------------------------------------------
Sub AddMRU()
  On Error GoTo AMErr

  Dim i As Integer, j As Integer

  ' Vérifie d'abord si elle y est déjà, et ignore
  ' l'opération si c'est le cas.
  For i = 1 To 8
    If UCase(Mid(frmMDI.mnuDBMRU(i).Caption, 4, Len(frmMDI.mnuDBMRU(i).Caption))) = UCase(gsDBName) Then
      For j = i To 2 Step -1
        frmMDI.mnuDBMRU(j).Caption = "&" & j & " " & Mid(frmMDI.mnuDBMRU(j - 1).Caption, 4, Len(frmMDI.mnuDBMRU(j - 1).Caption))
        frmMDI.mnuDBMRU(j).Tag = frmMDI.mnuDBMRU(j - 1).Tag
      Next
      GoTo Finish
    End If
  Next

  ' Elle n'y était pas: elle déplace donc les autres vers le bas.
  For i = 7 To 1 Step -1
    frmMDI.mnuDBMRU(i + 1).Caption = "&" & i + 1 & " " & Mid(frmMDI.mnuDBMRU(i).Caption, 4, Len(frmMDI.mnuDBMRU(i).Caption))
    frmMDI.mnuDBMRU(i + 1).Tag = frmMDI.mnuDBMRU(i).Tag
  Next

Finish:
  frmMDI.mnuDBMRU(1).Caption = "&1 " & gsDBName
  If Len(gdbCurrentDB.Connect) = 0 Then
    ' Cas d'Access pour laquelle il n'y a pas de
    ' chaîne de connexion.
    frmMDI.mnuDBMRU(1).Tag = gsMSACCESS
  Else
    frmMDI.mnuDBMRU(1).Tag = gdbCurrentDB.Connect
  End If
  frmMDI.mnuBarMRU.Visible = True
  For i = 1 To 8
    If Len(Mid(frmMDI.mnuDBMRU(i).Caption, 4, Len(frmMDI.mnuDBMRU(i).Caption))) > 0 Then
      frmMDI.mnuDBMRU(i).Visible = True
    End If
  Next

  Exit Sub

AMErr:
  ShowError
End Sub

'------------------------------------------------------------
' Cette procédure décompose une chaîne de connexion ODBC
' et affecte ses éléments à des variables publiques d'ODBC.
'------------------------------------------------------------
Sub GetODBCConnectParts(rsConnect As String)
  On Error Resume Next
  
  Dim i As Integer
  Dim sTmp As String
  
  ' Traiter la chaîne de connexion uniquement si les
  ' valeurs sont renvoyées par les boîtes de dialogue d'ODBC.
  If InStr(rsConnect, "=") Then
    i = 1
    While i <= Len(rsConnect) + 1
      If Mid(rsConnect, i, 1) = ";" Or i = Len(rsConnect) + 1 Then
        If Len(sTmp) > 0 And InStr(sTmp, "=") > 0 Then
          Select Case Mid(sTmp, 1, InStr(1, sTmp, "=") - 1)
            Case "DSN"
              gsODBCDatasource = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "DATABASE"
              gsODBCDatabase = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "DBQ"
              gsODBCDatabase = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "UID"
              gsODBCUserName = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "PWD"
              gsODBCPassword = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "Driver"
              gsODBCDriver = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
            Case "Server"
              gsODBCServer = Mid(sTmp, InStr(1, sTmp, "=") + 1, Len(sTmp))
             Case Else
              ' Ne rien faire.
          End Select
        End If
        sTmp = vbNullString
      Else
        sTmp = sTmp + Mid(rsConnect, i, 1)
      End If
      i = i + 1
    Wend
  End If
End Sub

'------------------------------------------------------------
' Ceci est une procédure générique qui ajoute le nom de chaque
' élément dans une collection passée dans un contrôle.
'------------------------------------------------------------
Sub ListItemNames(rcCollection As Object, rnCtl As Control, bClearList As Integer)
  On Error GoTo LINErr
  
  Dim objTmp As Object
  Dim i As Integer
  
  If bClearList Then
    rnCtl.Clear
  End If
  
  For Each objTmp In rcCollection
    rnCtl.AddItem objTmp.Name
  Next

  Exit Sub
  
LINErr:
  ShowError
End Sub

'------------------------------------------------------------
' Cette procédure ferme la base de données en cours,
' effectue diverses épurations et réinitialise les
' contrôles, les menus, etc...
'------------------------------------------------------------
Sub CloseCurrentDB()
  On Error GoTo DBCloseErr

  If gdbCurrentDB Is Nothing Then Exit Sub
    
  If gbDBChanged Then
    If MsgBox(MSG32, vbYesNo + vbQuestion) = vbYes Then
      gwsMainWS.CommitTrans
      gbDBChanged = False
    Else
      If MsgBox(MSG33, vbYesNo + vbQuestion) = vbYes Then
        gwsMainWS.Rollback
        gbDBChanged = False
      Else
        Beep
        MsgBox MSG34, 48
        Exit Sub
      End If
    End If
  End If

  frmMDI.Caption = "Gestionnaire de données"
  
  HideDBTools

  gbDBOpenFlag = False
  gbTransPending = False
  gsDBName = vbNullString
  gnReadOnly = False
  
  gdbCurrentDB.Close
  Set gdbCurrentDB = Nothing
  UnloadAllForms

  Exit Sub

DBCloseErr:
  ShowError
End Sub

'------------------------------------------------------------
'------------------------------------------------------------
Sub OpenLocalDB(bSilent As Boolean)
  On Error GoTo OpenError

  Dim sConnect As String
  Dim sDatabaseName As String
  Dim dbTemp As Database
  Dim sTmp As String

  sDatabaseName = gsDBName
  
  If Not bSilent Then
    Select Case gsDataType
      Case gsMSACCESS
        frmMDI.dlgCMD1.Filter = MSG49 & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG36
      Case gsDBASEIII, gsDBASEIV, gsDBASE5
        frmMDI.dlgCMD1.Filter = "Bases de données Dbase (*.dbf)|*.dbf" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG37
      Case gsFOXPRO20, gsFOXPRO25, gsFOXPRO26, gsFOXPRO30
        frmMDI.dlgCMD1.Filter = "Bases de données FoxPro (*.dbf)|*.dbf" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG38
      Case gsPARADOX3X, gsPARADOX4X, gsPARADOX5X
        frmMDI.dlgCMD1.Filter = "Bases de données Paradox (*.db)|*.db" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG39
      Case gsEXCEL50
        frmMDI.dlgCMD1.Filter = "Fichiers Excel (*.xls)|*.xls" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG40
      Case gsBTRIEVE
        frmMDI.dlgCMD1.Filter = "Bases de données Btrieve (FILE.DDF)|FILE.DDF" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG41
      Case gsTEXTFILES
        frmMDI.dlgCMD1.Filter = "Fichiers texte (*.txt)|*.txt" & MSG50
        frmMDI.dlgCMD1.DialogTitle = MSG42
    End Select

    frmMDI.dlgCMD1.FilterIndex = 1
    frmMDI.dlgCMD1.FileName = gsDBName  '""
    frmMDI.dlgCMD1.CancelError = True
    frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNFileMustExist
    frmMDI.dlgCMD1.ShowOpen

    If Len(frmMDI.dlgCMD1.FileName) > 0 Then
      gsDBName = frmMDI.dlgCMD1.FileName
    Else
      Exit Sub
    End If
  Else
    gsDBName = sDatabaseName
  End If
  
  If Len(gsDBName) = 0 Then
    MsgBar vbNullString, False
    Exit Sub
  End If

  MsgBar MSG43, True
  Screen.MousePointer = vbHourglass

  ' Définit la chaîne de connexion.
  If gsDataType = gsMSACCESS Then
    sConnect = vbNullString
  Else
    sConnect = gsDataType
  End If
  
  ' Définit le nom de la base de données pour les bases
  ' non Microsoft Access et Btrieve provenant de la boîte
  ' de dialogue commune.
  If gsDataType <> gsMSACCESS And gsDataType <> gsBTRIEVE And _
     gsDataType <> gsEXCEL50 And (Not bSilent) Then
    ' Doit retirer le nom de fichier de ces bases de données.
    sDatabaseName = StripFileName(gsDBName)
    gsDBName = sDatabaseName
  Else
    sDatabaseName = gsDBName
  End If

  gsODBCDatasource = vbNullString  'reset it

  GoTo OneMoreTry
  
GetPWD:
  Dim frmPWD As New frmDBPWD
  frmPWD.Show vbModal
  If Len(frmPWD.PWD) > 0 Then
    sConnect = ";pwd=" & frmPWD.PWD
    Unload frmPWD
    Set frmPWD = Nothing
    MsgBar MSG43, True
    Screen.MousePointer = vbHourglass
  Else
    ' La boîte de dialogue de mot de passe a été annulée; quitter.
    Unload frmPWD
    Set frmPWD = Nothing
    Exit Sub
  End If

OneMoreTry:
  If (frmMDI.dlgCMD1.Flags And FileOpenConstants.cdlOFNReadOnly) = FileOpenConstants.cdlOFNReadOnly Then
    gnReadOnly = True
  Else
    gnReadOnly = False
  End If
  Set dbTemp = gwsMainWS.OpenDatabase(sDatabaseName, False, gnReadOnly, sConnect)
  If gbDBOpenFlag Then
    ' Enregistre le nom de la base de données.
    sTmp = gsDBName
    ' Le restaure.
    CloseCurrentDB
    gsDBName = sTmp
    If gbDBOpenFlag Then
      Beep
      MsgBox MSG35, 48
      Exit Sub
    End If
  End If

  ' Réussit.
  frmMDI.Caption = "Gestionnaire de données:" & sDatabaseName
  Set gdbCurrentDB = dbTemp
  gbDBOpenFlag = True
  ShowDBTools
  RefreshTables Nothing
  gdbCurrentDB.QueryTimeout = glQueryTimeout

  AddMRU
  If gsDataType <> gsMSACCESS Then
    MsgBar MSG44, False
  End If
  Screen.MousePointer = vbDefault

  Exit Sub

AttemptRepair:
  Screen.MousePointer = vbHourglass
  MsgBar MSG45 & gsDBName, True
  DBEngine.RepairDatabase gsDBName
  Screen.MousePointer = vbDefault
  GoTo OneMoreTry

OpenError:
  Screen.MousePointer = vbDefault
  If Err = 3049 Then
    If MsgBox(Err.Description & vbCrLf & vbCrLf & MSG46, 4 + 48) = vbYes Then
      Resume AttemptRepair
    End If
  ElseIf Err = 3031 Then
    ' Base de données protégée par mot de passe.
    Resume GetPWD
  End If
  gbDBOpenFlag = False
  gsDBName = vbNullString
  gsDataType = vbNullString
  gsODBCDatabase = vbNullString
  gsODBCUserName = vbNullString
  gsODBCPassword = vbNullString
  gsODBCDriver = vbNullString
  gsODBCServer = vbNullString
  If Err <> 32755 And Err <> 3049 Then   ' Vérifie si la boîte de dialogue commune a été annulée.
    ShowError
  End If
End Sub

'------------------------------------------------------------
' Cette procédure est utilisée pour créer un nouveau dossier
' pour une des bases de données ISAM locales.
'------------------------------------------------------------
Sub NewLocalISAM()
   On Error GoTo NewISAMErr

   Dim sNewName As String
   Dim d As Database

GetNewDirName:
   sNewName = InputBox(MSG47, , sNewName)
   If Len(sNewName) = 0 Then Exit Sub

   If Mid(sNewName, Len(sNewName), 1) <> "\" Then sNewName = sNewName & "\"

   MkDir Mid(sNewName, 1, Len(sNewName) - 1)

   gsDBName = sNewName
   OpenLocalDB True

   If gbDBOpenFlag Then
     ShowDBTools
     RefreshTables Nothing
   End If

  Exit Sub

NewISAMErr:
  If Err = 75 Then Resume Next  ' Tient compte du fait que le dossier existe déjà.
  If Err = 76 Then
    MsgBox MSG65, vbExclamation
    ' Réessaie maintenant.
    Resume GetNewDirName
  End If
  ShowError
End Sub

'------------------------------------------------------------
' Cette procédure est appelée depuis l'option de compactage
' du menu Fichier sur la feuille MDI principale.
'------------------------------------------------------------
Sub CompactDB(rnCompactVersion As Integer)
  On Error GoTo CompactAccErr

  Dim sOldName As String
  Dim sNewName As String
  Dim sNewName2 As String
  Dim nEncrypt As Integer

  ' Obtient le nom du fichier à compacter.
  frmMDI.dlgCMD1.Filter = MSG49
  frmMDI.dlgCMD1.DialogTitle = MSG48
  frmMDI.dlgCMD1.FilterIndex = 1
  frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNHideReadOnly
  frmMDI.dlgCMD1.ShowOpen
  If Len(frmMDI.dlgCMD1.FileName) > 0 Then
    sOldName = frmMDI.dlgCMD1.FileName
  Else
    Exit Sub
  End If

  ' Obtient le nom du fichier vers lequel a été effectué
  ' le compactage.
  frmMDI.dlgCMD1.DialogTitle = MSG51
  frmMDI.dlgCMD1.FilterIndex = 1
  frmMDI.dlgCMD1.FileName = vbNullString
  frmMDI.dlgCMD1.CancelError = True
  frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNHideReadOnly
  frmMDI.dlgCMD1.ShowSave
  If Len(frmMDI.dlgCMD1.FileName) > 0 Then
    sNewName = frmMDI.dlgCMD1.FileName
    If Dir(sNewName) <> vbNullString And sOldName <> sNewName Then
      Kill sNewName
    End If
  Else
    Exit Sub
  End If

  If MsgBox(MSG52, vbYesNo + vbQuestion) = vbYes Then
    nEncrypt = dbEncrypt
  Else
    nEncrypt = dbDecrypt
  End If

  Screen.MousePointer = vbHourglass
  MsgBar MSG53 & sOldName & " -> " & sNewName, True
  ' Pour écraser le même fichier, vous devez créer
  ' un nouveau fichier MDB et le renommer après
  ' le compactage.
  If sOldName = sNewName Then
    sNewName2 = sNewName ' Enregistre le nouveau nom.
    sNewName = Left(sNewName, Len(sNewName) - 1) & "N"
  End If
  
  DBEngine.CompactDatabase sOldName, sNewName, dbLangGeneral, rnCompactVersion + nEncrypt
  
  ' Vérifie l'écrasement du fichier MDB de départ.
  If VBA.Right(sNewName, 1) = "N" Then
    Kill sNewName2             ' Vide l'ancien.
    Name sNewName As sNewName2 ' Renomme le nouveau avec le nom de celui de départ.
    sNewName = sNewName2       ' Replace le nom correct.
  End If
  
  MsgBar vbNullString, False
  Screen.MousePointer = vbDefault

  If MsgBox(MSG54, vbYesNo + vbQuestion) = vbYes Then
    If gbDBOpenFlag Then
      CloseCurrentDB
    End If
    gsDataType = gsMSACCESS
    gsDBName = sNewName
    OpenLocalDB True
  End If

  If gbDBOpenFlag Then
    ShowDBTools
    RefreshTables Nothing
  End If

  Exit Sub

CompactAccErr:
  If Err <> 32755 Then         ' Annulé par l'utilisateur.
    ShowError
  End If
End Sub

'------------------------------------------------------------
' Cette procédure fait des épurations et ferme le Gestionnaire de données.
'------------------------------------------------------------
Sub ShutDownVisData()
  On Error Resume Next

  Dim nRet As Integer

  ' Enregistre les paramètres en cours dans le fichier INI.
  SaveINISettings

  If gbDBChanged Then
    If MsgBox(MSG32, vbYesNo + vbQuestion) = vbYes Then
      gwsMainWS.CommitTrans
    End If
  End If

  UnloadAllForms
  gdbCurrentDB.Close
  ' Fermer le fichier d'aide.
  ReleaseHelp
  
  End

End Sub
Sub NewMDB(rnVersion As Integer)
  On Error GoTo NewAccErr

  Dim sNewName As String
  Dim db As Database

  ' Obtient le nom du fichier à compacter.
  frmMDI.dlgCMD1.DialogTitle = MSG55
  frmMDI.dlgCMD1.FilterIndex = 1
  frmMDI.dlgCMD1.Filter = MSG49
  frmMDI.dlgCMD1.FileName = vbNullString
  frmMDI.dlgCMD1.CancelError = True
  frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNOverwritePrompt + FileOpenConstants.cdlOFNHideReadOnly
  frmMDI.dlgCMD1.ShowSave
  If Len(frmMDI.dlgCMD1.FileName) > 0 Then
    sNewName = frmMDI.dlgCMD1.FileName
    If InStr(sNewName, ".") = 0 Then
      ' Ajoute une extension au fichier si nécessaire.
      sNewName = sNewName & ".MDB"
    End If
    If Dir(sNewName) <> vbNullString Then
      Kill sNewName
    End If
  Else
    Exit Sub
  End If
  If Len(sNewName) = 0 Then Exit Sub

  Set db = CreateDatabase(sNewName, dbLangGeneral, rnVersion)
  db.Close

  gsDataType = gsMSACCESS
  gsDBName = sNewName
  OpenLocalDB True
  Exit Sub

NewAccErr:
  If Err <> 32755 Then         ' Annulé par l'utilisateur.
    ShowError
  End If
End Sub

Sub Export(rsFromTbl As String, rsToDB As String)

  On Error GoTo ExpErr

  Dim sConnect As String
  Dim sNewTblName As String
  Dim sDBName As String
  Dim nErrState As Integer
  Dim idxFrom As Index
  Dim idxTo As Index
  Dim sSQL As String              ' Copie locale de la chaîne SQL.
  Dim sField As String
  Dim sFrom As String
  Dim sTmp As String
  Dim i As Integer

  If gnDataType = gnDT_SQLDB Then
    Set gExpDB = gwsMainWS.OpenDatabase(vbNullString, 0, 0, "odbc;")
    If gExpDB Is Nothing Then Exit Sub
  End If

  MsgBar MSG56 & "'" & rsFromTbl & "'", True

  nErrState = 1
  Select Case gnDataType
    Case gnDT_MSACCESS
      sConnect = "[;database=" & rsToDB & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(rsToDB)
    Case gnDT_PARADOX3X
      sDBName = StripFileName(rsToDB)
      sConnect = "[Paradox 3.X;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsPARADOX3X)
    Case gnDT_PARADOX4X
      sDBName = StripFileName(rsToDB)
      sConnect = "[Paradox 4.X;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsPARADOX4X)
    Case gnDT_FOXPRO26
      sDBName = StripFileName(rsToDB)
      sConnect = "[FoxPro 2.6;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsFOXPRO26)
    Case gnDT_FOXPRO25
      sDBName = StripFileName(rsToDB)
      sConnect = "[FoxPro 2.5;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsFOXPRO25)
    Case gnDT_FOXPRO20
      sDBName = StripFileName(rsToDB)
      sConnect = "[FoxPro 2.0;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsFOXPRO20)
    Case gnDT_DBASEIV
      sDBName = StripFileName(rsToDB)
      sConnect = "[dBase IV;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsDBASEIV)
    Case gnDT_DBASEIII
      sDBName = StripFileName(rsToDB)
      sConnect = "[dBase III;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsDBASEIII)
    Case gnDT_BTRIEVE
      sConnect = "[Btrieve;database=" & rsToDB & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(rsToDB, 0, 0, gsBTRIEVE)
    Case gnDT_EXCEL50, gnDT_EXCEL40, gnDT_EXCEL30
      sConnect = "[Excel 5.0;database=" & rsToDB & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(rsToDB, 0, 0, gsEXCEL50)
    Case gnDT_SQLDB
      sConnect = "[" & gExpDB.Connect & "]."
    Case gnDT_TEXTFILE
      sDBName = StripFileName(rsToDB)
      sConnect = "[Text;database=" & StripFileName(rsToDB) & "]."
      Set gExpDB = gwsMainWS.OpenDatabase(sDBName, 0, 0, gsTEXTFILES)
  End Select
  If gnDataType = gnDT_MSACCESS Or gnDataType = gnDT_BTRIEVE Or _
     gnDataType = gnDT_SQLDB Or gnDataType = gnDT_EXCEL50 Or _
     gnDataType = gnDT_EXCEL40 Or gnDataType = gnDT_EXCEL30 Then
    With frmExpName
      .Label1.Caption = MSG57 & rsFromTbl & " ->"
      .Label2.Caption = MSG58 & rsToDB
      .txtTable.Text = rsFromTbl
    End With
    frmExpName.Show vbModal
      
    If Len(gExpTable) = 0 Then
      MsgBar vbNullString, False
      Exit Sub
    Else
      sNewTblName = gExpTable
    End If
  Else
    ' Obtenir l'élément de la table du nom du fichier.
    ' Enlèver le chemin d'accès.
    For i = Len(rsToDB) To 1 Step -1
      If Mid(rsToDB, i, 1) = "\" Then
        Exit For
      End If
    Next
    sTmp = Mid(rsToDB, i + 1, Len(rsToDB))
    ' Enlèver l'extension.
    For i = 1 To Len(sTmp)
      If Mid(sTmp, i, 1) = "." Then
        Exit For
      End If
    Next
    sNewTblName = Left(sTmp, i - 1)
  End If
  Screen.MousePointer = vbHourglass
  If Len(rsFromTbl) > 0 Then
    gdbCurrentDB.Execute "select * into " & sConnect & StripOwner(sNewTblName) & " from " & StripOwner(rsFromTbl)

    If gnDataType <> gnDT_TEXTFILE Then
      nErrState = 2
      MsgBar MSG59 & " '" & sNewTblName & "'", True
      gExpDB.TableDefs.Refresh
      For Each idxFrom In gdbCurrentDB.TableDefs(rsFromTbl).Indexes
        Set idxTo = gExpDB.TableDefs(sNewTblName).CreateIndex(idxFrom.Name)
        With idxTo
          .Fields = idxFrom.Fields
          .Unique = idxFrom.Unique
          If gnDataType <> gnDT_SQLDB And gsDataType <> "ODBC" Then
            .Primary = idxFrom.Primary
          End If
        End With
        gExpDB.TableDefs(sNewTblName).Indexes.Append idxTo
      Next
    End If
    MsgBar vbNullString, False
    Screen.MousePointer = vbDefault
    MsgBox MSG60 & " '" & rsFromTbl & "'", 64
  Else
    sSQL = frmSQL.txtSQLStatement.Text
    sField = Mid(sSQL, 8, InStr(8, UCase(sSQL), "FROM") - 9)
    sFrom = " " & Mid(sSQL, InStr(UCase(sSQL), "FROM"), Len(sSQL))
    gdbCurrentDB.Execute "select " & sField & " into " & sConnect & sNewTblName & sFrom

    Screen.MousePointer = vbDefault
    MsgBar vbNullString, False
    MsgBox MSG61, 64
  End If

  Exit Sub

ExpErr:
  If Err = 3010 Then      ' La table existe.
    If MsgBox(MSG62, 32 + 1 + 256) = 1 Then
      gExpDB.TableDefs.Delete sNewTblName
      Resume
    Else
      Screen.MousePointer = vbDefault
      MsgBar vbNullString, False
      Exit Sub
    End If
  End If
 
  ' Vider la nouvelle table si les index ne peuvent être créés.
  If nErrState = 2 Then
    gExpDB.TableDefs.Delete sNewTblName
  End If
  ShowError
End Sub

Sub Import(rsImpTblName As String)
  On Error GoTo ImpErr

  Dim sOldTblName As String, sNewTblName As String, sConnect As String
  Dim idxFrom As Index
  Dim idxTo As Index
  Dim nErrState As Integer
  Dim i As Integer

  sOldTblName = MakeTableName(rsImpTblName, False)
  sNewTblName = MakeTableName(rsImpTblName, True)

  Screen.MousePointer = vbHourglass
  MsgBar MSG63 & "'" & sNewTblName & "'", True

  nErrState = 1
  Select Case gnDataType
    Case gnDT_MSACCESS
      sConnect = "[;database=" & gImpDB.Name & "]."
    Case gnDT_PARADOX3X
      sConnect = "[Paradox 3.X;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsPARADOX3X)
    Case gnDT_PARADOX4X
      sConnect = "[Paradox 4.X;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsPARADOX4X)
    Case gnDT_FOXPRO26
      sConnect = "[FoxPro 2.6;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsFOXPRO26)
    Case gnDT_FOXPRO25
      sConnect = "[FoxPro 2.5;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsFOXPRO25)
    Case gnDT_FOXPRO20
      sConnect = "[FoxPro 2.0;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsFOXPRO20)
    Case gnDT_DBASEIV
      sConnect = "[dBase IV;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsDBASEIV)
    Case gnDT_DBASEIII
      sConnect = "[dBase III;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsDBASEIII)
    Case gnDT_BTRIEVE
      sConnect = "[Btrieve;database=" & gImpDB.Name & "]."
    Case gnDT_EXCEL50, gnDT_EXCEL40, gnDT_EXCEL30
      sConnect = "[Excel 5.0;database=" & gImpDB.Name & "]."
    Case gnDT_SQLDB
      sConnect = "[" & gImpDB.Connect & "]."
    Case gnDT_TEXTFILE
      sConnect = "[Text;database=" & StripFileName(rsImpTblName) & "]."
      Set gImpDB = gwsMainWS.OpenDatabase(StripFileName(rsImpTblName), 0, 0, gsTEXTFILES)
  End Select
  gdbCurrentDB.Execute "select * into " & sNewTblName & " from " & sConnect & sOldTblName

  If gnDataType <> gnDT_TEXTFILE And gnDataType <> gnDT_EXCEL50 And _
     gnDataType <> gnDT_EXCEL40 And gnDataType <> gnDT_EXCEL30 Then
    nErrState = 2
    MsgBar gdbCurrentDB.RecordsAffected & " Lignes importées, Création d'index pour '" & sNewTblName & "'", True
    gdbCurrentDB.TableDefs.Refresh
    For Each idxFrom In gImpDB.TableDefs(sOldTblName).Indexes
      Set idxTo = gdbCurrentDB.TableDefs(sNewTblName).CreateIndex(idxFrom.Name)
      With idxTo
        .Fields = idxFrom.Fields
        .Unique = idxFrom.Unique
        If gnDataType <> gnDT_SQLDB And gsDataType <> gsSQLDB Then
          .Primary = idxFrom.Primary
        End If
      End With
      gdbCurrentDB.TableDefs(sNewTblName).Indexes.Append idxTo
    Next
  End If
    
  frmImpExp.lstTables.AddItem sNewTblName
'  frmTables.lstTables.AddItem sNewTblName
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False
  MsgBox MSG64 & "'" & sNewTblName & "'.", 64

  Exit Sub

NukeNewTbl:
  On Error Resume Next  ' uniquement en cas d'échec
  gdbCurrentDB.TableDefs.Delete sNewTblName
  ShowError
  Exit Sub
 
ImpErr:
  ' Vide la nouvelle table si les index ne peuvent être créés.
  If nErrState = 2 Then
    Resume NukeNewTbl
  End If
  ShowError
End Sub

Function MakeTableName(fname As String, newname As Integer) As String
  On Error Resume Next
  Dim i As Integer, t As Integer
  Dim tmp As String

  If gnDataType = gnDT_SQLDB And newname Then
    i = InStr(1, fname, ".")
    If i > 0 Then
      tmp = Mid(fname, 1, i - 1) & "_" & Mid(fname, i + 1, Len(fname))
    End If
  ElseIf InStr(fname, "\") > 0 Then
    ' Enlèver le chemin d'accès.
    For i = Len(fname) To 1 Step -1
      If Mid(fname, i, 1) = "\" Then
        Exit For
      End If
    Next
    tmp = Mid(fname, i + 1, Len(fname))
    i = InStr(1, tmp, ".")
    If i > 0 Then
      tmp = Mid(tmp, 1, i - 1)
    End If
  Else
    tmp = fname
  End If

  If newname Then
    If DupeTableName(tmp) Then
      t = 1
      While DupeTableName(tmp + CStr(t))
        t = t + 1
      Wend
      tmp = tmp + CStr(t)
    End If
  End If

  MakeTableName = tmp

End Function

'------------------------------------------------------------
' Objet:      définir l'ID local pour les ressources d'aide HTML
' Param lcid: ID locale dans laquelle elle doit être affichée
'------------------------------------------------------------
Public Sub setHelpLocaleID(ByVal LCID As Long)
'------------------------------------------------------------
    m_lcid = LCID
End Sub

'------------------------------------------------------------
' Objet:      définir le nom de fichier de la rubrique d'aide
' Param sName:  nom de fichier de la rubrique d'aide
'------------------------------------------------------------
Public Sub setHelpFile(ByVal sName As String)
'------------------------------------------------------------
    m_sHelpFile = sName
End Sub

'------------------------------------------------------------
' Public Sub DisplayTopic(ByVal toc As Long)
' Objet:      affiche la rubrique html identifiée le sommaire.
'             le fichier d'aide doit être déjà connu
' Param sHelpFile: fichier chm recherché
' Param toc:    id de la rubrique à afficher
' Param lcid:   ID locale dans laquelle elle doit être affichée
'------------------------------------------------------------
Public Sub DisplayTopic(ByVal toc As Long)
'------------------------------------------------------------
On Error GoTo errorHandle

    Debug.Assert Len(m_sHelpFile) > 0
    
    If Not initialiseHelp() Then Exit Sub
        
    m_HelpServices.DisplayTopicFromIdentifier m_sHelpFile, toc, VHS_Localize
        
errorHandle:
    ' L'aide html génère sa propre erreur si elle ne peut pas afficher l'aide
        
End Sub

'------------------------------------------------------------
' Public Sub KeywordSearch(sKey as string, lcid as long)
' Objet:      effectue une recherche par mot clé sur la
'             totalité des données msdn (installée).
' Param sKey:   mot clé à rechercher
' Param lcid:   ID locale dans laquelle elle doit être affichée
'------------------------------------------------------------
Public Sub KeywordSearch(ByVal sKey As String)
'------------------------------------------------------------
On Error GoTo errorHandle

    If Not initialiseHelp() Then Exit Sub
    
    m_HelpServices.KeywordSearch sKey, 0, 0
    
errorHandle:
    ' L'aide html génère sa propre erreur si elle ne peut pas afficher l'aide
    
End Sub

'------------------------------------------------------------
' Public Sub ReleaseHelp
' Objet:      nettoyer m_HelpServices
'------------------------------------------------------------
Public Sub ReleaseHelp()
'------------------------------------------------------------
    Set m_HelpServices = Nothing
End Sub

'------------------------------------------------------------
' Initialiser le système d'aide HTML
'------------------------------------------------------------
Private Function initialiseHelp() As Boolean
On Error GoTo errorHandle
    Dim helpInit As IVsHelpInit
    
    If m_HelpServices Is Nothing Then
        Set m_HelpServices = New VsHelpServices.VsHelpServices
        Set helpInit = m_HelpServices
        helpInit.LoadUIResources m_lcid
        DoEvents
    End If
    
    initialiseHelp = True

errorHandle:
    If Err <> 0 Then
        initialiseHelp = False
        MsgBox Err.Description
    End If
End Function

Public Function GetVbIdeLocale() As Long
'------------------------------------------------------------
    Dim hInstance   As Long
    Dim sLocale     As String
    Dim rc          As Long
    Const LOCALERESID = 2001
'------------------------------------------------------------
    hInstance = LoadLibraryEx("VB6IDE.DLL", 0&, LOAD_LIBRARY_AS_DATAFILE)
    If (hInstance <> 0) Then
        sLocale = String$(20, vbNullChar)
        rc = LoadStringA(hInstance, LOCALERESID, sLocale, Len(sLocale))
        If (rc > 0) Then
            GetVbIdeLocale = Val("&H" & sLocale)
        End If
        FreeLibrary hInstance
    End If
'------------------------------------------------------------
End Function


