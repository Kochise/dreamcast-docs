VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmTreeview 
   Caption         =   "TreeView et ListView"
   ClientHeight    =   5655
   ClientLeft      =   -105
   ClientTop       =   750
   ClientWidth     =   9660
   Icon            =   "treeview.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5655
   ScaleWidth      =   9660
   Begin VB.ComboBox cmbView 
      Height          =   315
      Left            =   6960
      TabIndex        =   4
      Text            =   "Combo1"
      Top             =   0
      Width           =   2415
   End
   Begin VB.CommandButton cmdLoad 
      Caption         =   "Charger"
      Height          =   270
      Left            =   2190
      TabIndex        =   1
      Top             =   4935
      Visible         =   0   'False
      Width           =   1050
   End
   Begin MSComCtlLib.StatusBar sbrDB 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   5400
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSComCtlLib.ProgressBar prgLoad 
      Height          =   210
      Left            =   255
      TabIndex        =   3
      Top             =   375
      Visible         =   0   'False
      Width           =   9090
      _ExtentX        =   16034
      _ExtentY        =   370
      _Version        =   393216
      Appearance      =   1
   End
   Begin MSComCtlLib.ListView lvwDB 
      Height          =   4215
      Left            =   3480
      TabIndex        =   2
      Top             =   615
      Width           =   5880
      _ExtentX        =   10372
      _ExtentY        =   7435
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      Icons           =   "imlIcons"
      SmallIcons      =   "imlSmallIcons"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      NumItems        =   0
      _Items          =   "treeview.frx":000C
   End
   Begin MSComDlg.CommonDialog dlgDialog 
      Left            =   1605
      Top             =   4830
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FilterIndex     =   474
      FontSize        =   8.01821e-38
   End
   Begin MSComCtlLib.TreeView tvwDB 
      Height          =   4215
      Left            =   255
      TabIndex        =   0
      Top             =   615
      Width           =   3120
      _ExtentX        =   5503
      _ExtentY        =   7435
      _Version        =   393217
      LineStyle       =   1
      Style           =   7
      ImageList       =   "imlSmallIcons"
      Appearance      =   1
      _Nodes          =   "treeview.frx":0034
   End
   Begin MSComCtlLib.ImageList imlIcons 
      Left            =   645
      Top             =   4800
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   1
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":005C
            Key             =   "book"
         EndProperty
      EndProperty
   End
   Begin MSComCtlLib.ImageList imlSmallIcons 
      Left            =   45
      Top             =   4815
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   13
      ImageHeight     =   13
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":00BA
            Key             =   "closed"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":0118
            Key             =   "cylinder"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":0176
            Key             =   "leaf"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":01D4
            Key             =   "open"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":0232
            Key             =   "smlBook"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "treeview.frx":0290
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuLoad 
         Caption         =   "&Charger"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "&Quitter"
      End
   End
End
Attribute VB_Name = "frmTreeview"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mNode As node               ' Variable de niveau module pour les objets Node.
Private mWksBiblio As Workspace     ' Variable de niveau module pour l'objet Workspace.
Private mItem As ListItem           ' Variable de niveau module pour l'objet ListItem.
Private EventFlag As Integer        ' Signale quel événement s'est produit.
Private mCurrentIndex As Integer    ' Indicateur pour vérifier que le nœud n'a pas déjà été cliqué.
Private mStatusBarStyle As Integer  ' Sert à changer le style du contrôle StatusBar.
Private cn As ADODB.Connection      ' Utilisation d'une seule connexion active.
Attribute cn.VB_VarHelpID = -1

Const PUBLISHER = 1                 ' Pour EventFlag, signale la modification des en-têtes d'objets.
Const TITLE = 2                     ' Pour EventFlag, signale le titre dans le contrôle ListView.

Private Sub cmdLoad_Click()
Dim intCounter As Integer ' Compteur pour Progressbar.Value
    Dim intIndex ' Variable pour l'index du nœud en cours.
    
    ' Défini le ConnectionString de l'objet Connection ADODB et l'ouvrir.
    
    ' Crée une variable objet Recordset ADODB.
    Dim rsPublishers As New ADODB.Recordset
    ' Ouvre le RecordSet.
    With rsPublishers
        .Open "SELECT PubID, [Company Name] FROM Publishers", cn, adOpenStatic, adLockOptimistic
        ' Vas au dernier enregistrement pour obtenir RecordCount puis revient.
        .MoveLast
        .MoveFirst
    End With
    ' Défini ProgressBar Max et le rendre visible.
    With prgLoad
        .Max = rsPublishers.RecordCount
        .Visible = True
    End With
    

    ' Ajoute un objet ListItem tant que l'enregistrement n'est pas le dernier.
    ' Utilise le champ Name pour le texte de l'objet ListItem.
    Do While Not rsPublishers.EOF
        intCounter = intCounter + 1
        prgLoad.Value = intCounter ' Rafraichi ProgressBar.
        ' Ajoute un noeud au contrôle TreeView, et définit ses propriétés.
        Set mNode = tvwDB.Nodes.Add(1, tvwChild, rsPublishers!pubID & " ID", CStr(rsPublishers![Company name]), "closed")
        mNode.Tag = "Publisher" ' Identifie la table.

        ' Affecte la variable intIndex avec la propriété Index du
        ' dernier noeud créé. Utilise cette variable pour ajouter
        ' les objets Node de l'enfant à ce noeud.
          intIndex = mNode.Index
        
       
        rsPublishers.MoveNext   ' Se déplace vers l'enregistrement suivant dans Publishers.
    Loop
    ' Masque le contrôle Progressbar
    prgLoad.Visible = False
    ' Affecte le style normal pour le contrôle Statusbar.
    sbrDB.Style = sbrNormal
    ' Trie les noeuds de Publishers.
    tvwDB.Nodes(1).Sorted = True
    ' Développe le noeud du haut.
    tvwDB.Nodes(1).Expanded = True
    
End Sub
Private Sub Combo1_Click()
    lvwDB.View = Combo1.ListIndex
End Sub

Private Sub cmbView_Click()
    ' Défini la propriété ListView.View.
    lvwDB.View = cmbView.ListIndex
End Sub

Private Function FindBiblio() As String
    On Error GoTo ErrHandler

    ' Configure cmdDialog en cas de Biblio.mdb introuvable.
    With dlgDialog
        .DialogTitle = "Biblio.mdb est introuvable"
        .Filter = "(*.MDB)|*.mdb"
    End With

    ' Cause une erreur si l'utilisateur clique sur annuler
    dlgDialog.CancelError = True
    dlgDialog.ShowOpen
        
    Do While UCase(Right(Trim(dlgDialog.FileName), 10)) <> "BIBLIO.MDB"
       MsgBox "Le nom du fichier est différent de BIBLIO.MDB"
       dlgDialog.ShowOpen
    Loop
    
    FindBiblio = dlgDialog.FileName
    Exit Function
ErrHandler:
    If Err = 32755 Then
      End
    End If
End Function

Private Sub Form_Load()
    
    ' Ouvre d'abord l'objet Connection global.
    On Error GoTo errFind
    Set cn = New ADODB.Connection
    ' ConnectionString contient le chemin de la base de données. Si
    ' Biblio.mdb n'est pas sur la machine, il peut se trouve sur le CD
    ' MSDN
    With cn
        .ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & _
        "C:\Program Files\Microsoft Visual Studio\VB98\Biblio.mdb"
        .Open
    End With
    
    ' Configure le contrôle cmbView.
    With cmbView
        .AddItem "Grandes icônes"      '0
        .AddItem "Petites icônes"      '1
        .AddItem "Liste"               '2
        .AddItem "Détails"             '3
        .ListIndex = 3
    End With

    ' Configure le contrôle ListView.
    lvwDB.View = lvwReport
        
    ' Configure le contrôle TreeView.
With tvwDB
        .Sorted = True
        Set mNode = .Nodes.Add()
        .LabelEdit = False
        .LineStyle = tvwRootLines
    End With
    
    With mNode ' Ajoute le premier noeud.
        .Text = "Publishers"
        .Tag = "Biblio"
        .Image = "closed"
    End With
    frmTreeview.Show
    
    mnuLoad_Click
    Exit Sub
   
    ' Si la base de données Biblio est introuvable, ouvre le
    ' contrôle de la boîte de dialogue commune pour permettre à
    ' l'utilisateur de la trouver.
errFind:
    If Err = -2147467259 Then
        Set cn = Nothing
        Set cn = New ADODB.Connection
        cn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & FindBiblio
        cn.Open
        Resume Next
    ElseIf Err <> 0 Then ' Une autre erreur.
        MsgBox "Erreur inattendue: " & Err.Description
        End
    End If
End Sub


Private Sub lvwDB_ColumnClick(ByVal ColumnHeader As ColumnHeader)
    lvwDB.SortKey = ColumnHeader.Index - 1
    ' Affecte la valeur True à la propriété Sorted pour trier la liste.
    lvwDB.Sorted = True

End Sub

Private Sub lvwDB_ItemClick(ByVal Item As ListItem)
    GetData Item.Key
 End Sub
Private Sub GetData(ISBN As String)
    ' L'indicateur global EventFlag renseigne sur l'utilisation de la Statusbar.
    
    If EventFlag <> TITLE Then
        sbrDB.Panels.Clear
        Dim pnlX As Panel
        Set pnlX = sbrDB.Panels.Add(, "ISBN")
        pnlX.AutoSize = sbrContents
        Set pnlX = sbrDB.Panels.Add(, "author")
        pnlX.AutoSize = sbrContents
        Set pnlX = sbrDB.Panels.Add(, "year")
        pnlX.Width = 1000
        Set pnlX = sbrDB.Panels.Add(, "description")
        pnlX.AutoSize = sbrContents
    End If
        
    ' Ouvre un jeu d'enregistrements ADODB pour lire
    ' les données de la Statusbar.
    Dim rsTitles As New ADODB.Recordset
    Dim strQ As String
    strQ = "SELECT Authors.Author, Titles.ISBN, Titles.[Year Published], " & _
    "Titles.Description FROM Authors INNER JOIN (Titles INNER JOIN " & _
    "[Title Author] ON " & _
    "Titles.ISBN = [Title Author].ISBN) ON Authors.Au_ID = " & _
    "[Title Author].Au_ID WHERE Titles.ISBN='" & ISBN & " '"

    ' Ouvre le jeu d'enregistrements.
    rsTitles.Open strQ, cn, adOpenStatic, adLockOptimistic
    
    ' Rempli les panneaux de la StatusBar avec les infos.
    sbrDB.Panels("author").Text = rsTitles!author
    sbrDB.Panels("ISBN").Text = rsTitles!ISBN
    If Not IsNull(rsTitles![Year Published]) Then
        sbrDB.Panels("year").Text = rsTitles![Year Published]
    Else
        sbrDB.Panels("year").Text = "n/a"
    End If
    If Not IsNull(rsTitles!Description) Then
        sbrDB.Panels("description").Text = rsTitles!Description
    Else
        sbrDB.Panels("description").Text = "n/a"
    End If
    If Not rsTitles.EOF Then rsTitles.MoveNext
    ' Ajoute les autres noms d'auteurs.
    Do Until rsTitles.EOF
        
        If Not IsNull(rsTitles!author) Then
            sbrDB.Panels("author").Text = sbrDB.Panels("author").Text & _
            " & " & rsTitles!author
        End If
        rsTitles.MoveNext
    Loop
    ' Défini EventFlag pour éviter la re-création des panneaux.
    EventFlag = TITLE
End Sub


Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuLoad_Click()
    Static Loaded As Boolean
    If Loaded = True Then
        Exit Sub
    Else
        cmdLoad_Click
        Loaded = Abs(Loaded - 1)
        mnuLoad.Enabled = False
    End If
End Sub

Private Sub tvwDB_Collapse(ByVal node As node)
    ' Seuls les noeuds dossiers sont réductibles.
    If node.Tag = "Publisher" Or node.Index = 1 Then node.Image = "closed"
End Sub

Private Sub tvwDB_Expand(ByVal node As node)
    ' Seul le noeud supérieur et les noeuds "Publisher" sont développables.
    If node.Tag = "Publisher" Or node.Index = 1 Then
        node.Image = "open"
        node.Sorted = True
    End If
    If node.Tag = "Publisher" And EventFlag <> _
    PUBLISHER Then MakeColumns
    ' Si Tag = "Publisher" et l'index mItemCurrentIndex
    ' est différent de Node.key, alors
    ' appele la fonction GetTitles.
    If node.Tag = "Publisher" And mCurrentIndex <> Val(node.Key) _
    Then GetTitles node, Val(node.Key)
    
    If node.Tag = "Publisher" Then PopStatus node

    node.Sorted = True

End Sub

Private Sub MakeColumns()
    ' Efface la collection ColumnHeaders.
    lvwDB.ColumnHeaders.Clear
    ' Ajoute quatre objets à la collection ColumnHeaders.
    lvwDB.ColumnHeaders.Add , , "Title", 2800
    lvwDB.ColumnHeaders.Add , , "Author"
    lvwDB.ColumnHeaders.Add , , "Year", 800
    lvwDB.ColumnHeaders.Add , , "ISBN"
    
    ' Défini la variable EventFlag pour ne pas refaire constamment l'opération.
    EventFlag = PUBLISHER
End Sub
Private Sub AddListItemsOnly(pubID)
    Dim rsTitles As New ADODB.Recordset
    Dim newNode As node
    Dim strQ As String
    strQ = "SELECT Titles.Title, Authors.Author, Titles.ISBN, " & _
    "Titles.[Year Published] FROM Authors INNER JOIN " & _
    "(Titles INNER JOIN [Title Author] " & _
    "ON Titles.ISBN = [Title Author].ISBN) ON Authors.Au_ID = " & _
    "[Title Author].Au_ID WHERE Titles.PubID=" & pubID
    
    lvwDB.ListItems.Clear
    With rsTitles
        .Open strQ, cn, adOpenStatic, adLockReadOnly, adCmdText
        .MoveLast
        .MoveFirst
        prgLoad.Max = .RecordCount + 1
    End With
    
    ' Affiche la barre de progression
    prgLoad.Visible = True

    Dim intCounter As Integer
    ' Crée un noeud fils.
    

    ' Ajoute une ListItem correspondante.
    AddListItem mItem, rsTitles
    
    rsTitles.MoveNext
    ' Parcoure le reste du RecordSet. Si l'enregistrement suivant
    ' est un doublon, uniquement ajouter le nom de l'auteur.
    ' Sinon, ajouter de nouveaux Node et ListItem.
    Do Until rsTitles.EOF
        intCounter = intCounter + 1 ' Pour la ProgressBar.
        prgLoad.Value = intCounter  ' Progression de la mise à jour.

        If mItem.Key = rsTitles!ISBN Then ' Doublon
            ' Ajoute l'auteur à la liste des auteurs.
            mItem.ListSubItems(1).Text = _
            mItem.ListSubItems(1).Text & _
            " & " & rsTitles!author
        Else
            AddListItem mItem, rsTitles
        End If
        rsTitles.MoveNext
    Loop
    prgLoad.Visible = False
    mCurrentIndex = pubID
End Sub

Private Function GetTitles(ByRef ParentNode As node, pubID) As Boolean
    Dim rsTitles As New ADODB.Recordset
    Dim newNode As node ' Pour un nouveau Node.
    Dim strQ As String
    Dim intCounter As Integer ' Pour la valeur de la ProgressBar.
    
    ' Vérifie que le noeud n'est pas déjà rempli. S'il l'est, alors
    ' ajoute uniquement les objets ListItem à la ListView et quitte.
    If ParentNode.Children Then
        AddListItemsOnly pubID
        Exit Function
    End If
    
    ' Si la ListView est déjà remplie, l'effacer.
    lvwDB.ListItems.Clear
    
    ' Requête SQL qui lit les champs nécessaires.
    strQ = "SELECT Titles.Title, Authors.Author, Titles.ISBN, " & _
    "Titles.[Year Published] FROM Authors INNER JOIN " & _
    "(Titles INNER JOIN [Title Author] " & _
    "ON Titles.ISBN = [Title Author].ISBN) ON Authors.Au_ID = " & _
    "[Title Author].Au_ID WHERE Titles.PubID=" & pubID
    
    ' Ouvre le RecordSet. Quitte si pas de résultat.
    With rsTitles
        .Open strQ, cn, adOpenStatic, adLockReadOnly, adCmdText
        If .BOF Then
            ' Si pas de résultat, retourne False et quitte
            GetTitles = False
            Exit Function
        End If
        .MoveLast
        .MoveFirst
        prgLoad.Max = .RecordCount + 1
    End With
    
    ' Affiche la barre de progression
    prgLoad.Visible = True
    
    On Error GoTo childErr
    ' Ajoute un premier noeud.
    AddNode newNode, ParentNode, rsTitles
    ' Ajoute un ListItem correspondant.
    AddListItem mItem, rsTitles
    
    rsTitles.MoveNext
    
    ' Parcoure le reste du RecordSet. Si l'enregistrement suivant
    ' est un doublon, uniquement ajoute le nom de l'auteur.
    ' Sinon, ajoute de nouveaux Node et ListItem.
    Do Until rsTitles.EOF
        intCounter = intCounter + 1 ' Pour la ProgressBar.
        prgLoad.Value = intCounter  ' Progression de la mise à jour.

        ' Vérifie Key par rapport à l'ISDN en cours. S'ils sont identiques
        ' alors l'enregistrement diffère uniquement par l'auteur
        ' Donc, ajoute l'auteur à la liste en cours.
        If newNode.Key = rsTitles!ISBN Then
            ' Ajoute l'auteur à la liste des auteurs.
            mItem.ListSubItems("author").Text = _
            mItem.ListSubItems("author").Text & _
            " & " & rsTitles!author
        Else ' Ajoute de nouveaux Node et ListItem
            AddNode newNode, ParentNode, rsTitles
            AddListItem mItem, rsTitles
        End If
        rsTitles.MoveNext
    Loop
    GetTitles = True ' retourne True (réussite)
    
    prgLoad.Visible = False
    mCurrentIndex = pubID
    Exit Function
childErr:
        Debug.Print Err.Number, Err.Description
        
        Debug.Print rsTitles!ISBN
        Resume Next
    
    Exit Function
End Function
Private Sub AddNode(ByRef newNode As node, ByRef ParentNode As node, ByRef rs As ADODB.Recordset)
    ' Ajoute un nouveau noeud. Les newNode et ParentNode sont requis.
    Set newNode = tvwDB.Nodes.Add(ParentNode, _
    tvwChild, rs!ISBN, rs!TITLE, "smlBook")
    newNode.Tag = "book"
End Sub
Private Sub AddListItem(ByRef xItem As ListItem, ByRef xRec As ADODB.Recordset)
    ' Ajoute un nouveau ListItem et défini ses texte, icône et petite icône.
    ' puis, ajoute trois ListSubItems et défini Key et Text pour chacun.
    Set xItem = lvwDB.ListItems.Add(Key:=xRec!ISBN, _
    Text:=xRec!TITLE, Icon:="book", SmallIcon:="smlBook")

    xItem.ListSubItems.Add Key:="author", Text:=xRec!author
    If Not IsNull(xRec![Year Published]) Then
        xItem.ListSubItems.Add Key:="year", Text:=xRec![Year Published]
    End If
    xItem.ListSubItems.Add Key:="isbn", Text:=xRec!ISBN
End Sub

Private Sub tvwDB_NodeClick(ByVal node As node)
    ' Vérifie Tag pour "Publisher" et la variable
    ' EventFlag pour voir si les ColumnHeaders sont
    ' déjà créés. Si ce n'est pas le cas, appele
    ' la procédure MakeColumns.
    If node.Tag = "Publisher" And EventFlag <> _
    PUBLISHER Then MakeColumns
    ' Si Tag = "Publisher" et l'index mItemCurrentIndex
    ' est différent de Node.key, alors appele la fonction
    ' GetTitles function, qui remplit le Node.
    If node.Tag = "Publisher" And mCurrentIndex <> Val(node.Key) _
    Then GetTitles node, Val(node.Key)
    
    If node.Tag = "Publisher" Then PopStatus node
    node.Sorted = True
        
    ' Si le Tag du noeud est "book" alors vérifie que le livre cliqué est visible dans la ListView en utilisant la méthode EnsureVisible.
    If node.Tag = "book" Then
        Dim liBook As ListItem
        Set liBook = lvwDB.FindItem(node.Text)
        liBook.EnsureVisible
    End If
    
End Sub
 
Private Sub PopStatus(node As node)
    ' Modifie la StatusBar pour refléter les valeurs actuelles.
    With sbrDB
        .Panels.Clear
        .Panels.Add , "name", node.Text
        .Panels.Add , "number", node.Children & " titles"
        .Panels(1).AutoSize = sbrContents
        .Panels(2).AutoSize = sbrSpring
    End With
End Sub

