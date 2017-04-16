VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{86CF1D34-0C5F-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmRevenue 
   Caption         =   "Revenus des livres"
   ClientHeight    =   5880
   ClientLeft      =   2505
   ClientTop       =   2415
   ClientWidth     =   6990
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "BOOK_CLI.frx":0000
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5880
   ScaleWidth      =   6990
   WhatsThisHelp   =   -1  'True
   Begin VB.Frame Frame1 
      Caption         =   "Paramètres des revenus"
      Height          =   2685
      Left            =   80
      TabIndex        =   4
      Top             =   2250
      Width           =   6660
      Begin VB.CheckBox chkDiscount 
         Caption         =   "Réduction promotionnelle"
         Height          =   270
         Left            =   4080
         TabIndex        =   8
         Top             =   960
         Width           =   2115
      End
      Begin VB.Frame Frame3 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   1545
         Left            =   3915
         TabIndex        =   15
         Top             =   990
         Width           =   2595
         Begin VB.TextBox txtRevParm 
            Enabled         =   0   'False
            Height          =   300
            Index           =   5
            Left            =   1755
            TabIndex        =   10
            Text            =   "3"
            Top             =   690
            Width           =   375
         End
         Begin VB.TextBox txtRevParm 
            Enabled         =   0   'False
            Height          =   300
            Index           =   4
            Left            =   1755
            TabIndex        =   9
            Text            =   "2"
            Top             =   315
            Width           =   375
         End
         Begin VB.TextBox txtRevParm 
            Enabled         =   0   'False
            Height          =   300
            Index           =   6
            Left            =   1755
            TabIndex        =   11
            Text            =   "15"
            Top             =   1080
            Width           =   375
         End
         Begin MSComCtl2.UpDown udDiscount 
            Height          =   255
            Index           =   4
            Left            =   2280
            TabIndex        =   32
            Top             =   360
            Width           =   150
            _ExtentX        =   423
            _ExtentY        =   450
            _Version        =   393216
            Enabled         =   -1  'True
         End
         Begin MSComCtl2.UpDown udDiscount 
            Height          =   255
            Index           =   5
            Left            =   2280
            TabIndex        =   33
            Top             =   720
            Width           =   150
            _ExtentX        =   423
            _ExtentY        =   450
            _Version        =   393216
            Enabled         =   -1  'True
         End
         Begin MSComCtl2.UpDown udDiscount 
            Height          =   255
            Index           =   6
            Left            =   2280
            TabIndex        =   34
            Top             =   1080
            Width           =   150
            _ExtentX        =   423
            _ExtentY        =   450
            _Version        =   393216
            Enabled         =   -1  'True
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            BackStyle       =   0  'Transparent
            Caption         =   "Durée (mois):"
            Enabled         =   0   'False
            Height          =   195
            Index           =   5
            Left            =   150
            TabIndex        =   25
            Top             =   720
            Width           =   1485
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            BackStyle       =   0  'Transparent
            Caption         =   "Mois de départ:"
            Enabled         =   0   'False
            Height          =   195
            Index           =   4
            Left            =   480
            TabIndex        =   24
            Top             =   360
            Width           =   1155
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            BackStyle       =   0  'Transparent
            Caption         =   "Réduction %:"
            Enabled         =   0   'False
            Height          =   195
            Index           =   6
            Left            =   555
            TabIndex        =   23
            Top             =   1080
            Width           =   1080
         End
      End
      Begin VB.CommandButton cmdCogs 
         Caption         =   "..."
         Height          =   330
         Left            =   3720
         TabIndex        =   3
         Top             =   390
         Width           =   315
      End
      Begin VB.TextBox txtRevParm 
         Height          =   300
         Index           =   3
         Left            =   2445
         TabIndex        =   7
         Text            =   "5000"
         Top             =   2145
         Width           =   1215
      End
      Begin VB.TextBox txtRevParm 
         Height          =   300
         Index           =   2
         Left            =   2445
         TabIndex        =   6
         Text            =   "12"
         Top             =   1590
         Width           =   1215
      End
      Begin VB.TextBox txtRevParm 
         Height          =   300
         Index           =   1
         Left            =   2445
         TabIndex        =   5
         Text            =   "10000"
         Top             =   1020
         Width           =   1215
      End
      Begin VB.TextBox txtRevParm 
         Height          =   300
         Index           =   0
         Left            =   1440
         TabIndex        =   16
         TabStop         =   0   'False
         Top             =   405
         Width           =   2160
      End
      Begin VB.TextBox txtRevParm 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   7
         Left            =   4215
         TabIndex        =   28
         TabStop         =   0   'False
         Top             =   1245
         Width           =   405
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Unités/Mois:"
         Height          =   195
         Index           =   3
         Left            =   480
         TabIndex        =   22
         Top             =   2190
         Width           =   1815
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Période (mois):"
         Height          =   195
         Index           =   2
         Left            =   495
         TabIndex        =   21
         Top             =   1620
         Width           =   1800
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Dépenses de publicité:"
         Height          =   195
         Index           =   1
         Left            =   450
         TabIndex        =   20
         Top             =   1080
         Width           =   1845
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Code COGS:"
         Height          =   195
         Index           =   0
         Left            =   330
         TabIndex        =   19
         Top             =   450
         Width           =   1005
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "Royalties de l'auteur:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Index           =   7
         Left            =   4320
         TabIndex        =   27
         Top             =   1350
         Width           =   1080
      End
   End
   Begin VB.Frame frmSalesModel 
      Caption         =   "Modèle de ventes"
      Height          =   1350
      Left            =   80
      TabIndex        =   2
      Top             =   765
      Width           =   6660
      Begin VB.OptionButton optAnalysis 
         Height          =   975
         Index           =   2
         Left            =   4920
         Picture         =   "BOOK_CLI.frx":030A
         Style           =   1  'Graphical
         TabIndex        =   29
         Top             =   240
         Width           =   1575
      End
      Begin VB.OptionButton optAnalysis 
         Height          =   975
         Index           =   1
         Left            =   2580
         Picture         =   "BOOK_CLI.frx":166C
         Style           =   1  'Graphical
         TabIndex        =   30
         Top             =   240
         Width           =   1575
      End
      Begin VB.OptionButton optAnalysis 
         Height          =   975
         Index           =   0
         Left            =   240
         Picture         =   "BOOK_CLI.frx":29CE
         Style           =   1  'Graphical
         TabIndex        =   31
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
      Height          =   390
      Left            =   5520
      TabIndex        =   14
      Top             =   5025
      Width           =   1215
   End
   Begin VB.CommandButton cmdHelp 
      Caption         =   "&Aide"
      Height          =   390
      Left            =   120
      TabIndex        =   13
      Top             =   5010
      Width           =   1215
   End
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Exécuter"
      Default         =   -1  'True
      Height          =   420
      Left            =   3900
      TabIndex        =   12
      Top             =   5010
      Width           =   1245
   End
   Begin VB.ComboBox cboBooks 
      Height          =   315
      Left            =   2160
      Sorted          =   -1  'True
      TabIndex        =   1
      Top             =   360
      Width           =   4620
   End
   Begin VB.ComboBox cboAuthors 
      Height          =   315
      Left            =   80
      Sorted          =   -1  'True
      TabIndex        =   0
      Top             =   360
      Width           =   1980
   End
   Begin MSComCtlLib.StatusBar sbrRev 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   26
      Top             =   5565
      Width           =   6990
      _ExtentX        =   12330
      _ExtentY        =   556
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
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
   Begin MSComDlg.CommonDialog dlgFindDB 
      Left            =   1695
      Top             =   4980
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FontSize        =   1,73861e-39
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Livres:"
      Height          =   195
      Index           =   1
      Left            =   2190
      TabIndex        =   18
      Top             =   135
      Width           =   480
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Auteur:"
      Height          =   195
      Index           =   0
      Left            =   90
      TabIndex        =   17
      Top             =   135
      Width           =   555
   End
End
Attribute VB_Name = "frmRevenue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mSQL As String

Private Sub cboAuthors_Click()
  
  GetTitles cboAuthors.Text

End Sub


Private Sub chkDiscount_Click()
    Label2(4).Enabled = Not Label2(4).Enabled
    Label2(5).Enabled = Not Label2(5).Enabled
    Label2(6).Enabled = Not Label2(6).Enabled
    txtRevParm(4).Enabled = Not txtRevParm(4).Enabled
    txtRevParm(5).Enabled = Not txtRevParm(5).Enabled
    txtRevParm(6).Enabled = Not txtRevParm(6).Enabled
    udDiscount(4).Enabled = Not udDiscount(4).Enabled
    udDiscount(5).Enabled = Not udDiscount(5).Enabled
    udDiscount(6).Enabled = Not udDiscount(6).Enabled
    
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdCogs_Click()
  goStatusPanel.Text = "Détermine le coût des biens."
  Load frmCogs
  goStatusPanel.Text = ""
  
End Sub

Private Sub cmdHelp_Click()
Dim sHelpString As String
      
    sHelpString = "1. Sélectionnez un auteur et un titre de livre." & vbCrLf & _
                  "2. Sélectionnez un modèle de vente." & vbCrLf & _
                  "3. Cliquez sur le bouton Sélection pour définir le prix des COGS." & vbCrLf & _
                  "4. Entrez un montant alloué aux dépenses de publicité." & vbCrLf & _
                  "5. Entrez un nombre de mois de la période des ventes." & vbCrLf & _
                  "6. Entrez un nombre d'unités vendues par mois." & vbCrLf & _
                  "7. Optionellement, cliquez sur la case à cocher des réductions" & vbCrLf & _
                  "    promotionnelles pour ajouter une promotion de vente pour ce livre." & vbCrLf & _
                  "8. Cliquez sur le bouton Exécuter pour afficher un graphique " & vbCrLf & _
                  "    des revenus de l'éditeur et des royalties de l'auteur."

    MsgBox sHelpString, vbInformation, "Aide du livre des revenus"
End Sub

Private Sub cmdExecute_Click()

  If cboBooks.Text = "<Aucun>" Or cboBooks.Text = "" Then
    MsgBox "Impossible de créer un graphique quand aucun titre de livre n'est disponible.", _
                  vbExclamation, " Erreur de création du graphique"
    Exit Sub
  End If
                         
  goStatusPanel.Text = "Création du graphique..."
  Load frmChart
  frmChart.Show
      
End Sub

Private Function GetBooksale() As String
   ' Retourne le chemin de booksale.mdb.
   ' Si booksale.mdb n'est pas à l'emplacement par défaut,
   ' présente à l'utilisateur un contrôle CommonDialog et
   ' et lui demande de localiser la base de données.
    On Error GoTo ErrHandler

   With dlgFindDB
      .DialogTitle = "Veuillez rechercher Booksale.mdb"
      .InitDir = App.Path
      .FileName = gDBName
      .Filter = "Access (*.mdb)| *.mdb"
      .CancelError = True 'Cause une erreur si l'utilisateur clique sur annuler
      .ShowOpen
   End With
    
   Do While UCase(Right(Trim(dlgFindDB.FileName), Len("booksale.mdb"))) <> "BOOKSALE.MDB"
         MsgBox "Le nom du fichier est différent de BOOKSALE.MDB"
         dlgFindDB.ShowOpen
   Loop
   
   GetBooksale = dlgFindDB.FileName
   Exit Function
ErrHandler:
    If Err = 32755 Then 'Annuler cause une erreur
      MsgBox "Fin de l'application"
      End
    End If
End Function

Private Sub LoadDB()
  ' Charge booksale.mdb. Si le fichier n'est pas dans le
  ' répertoire attendu, affiche le contrôle CommonDialog
  ' qui permet à l'utilisateur de rechercher le fichier.
   
   gDBName = "booksale.mdb"
   On Error GoTo LoadDBError
   Set gCN = New ADODB.Connection ' Objet Connection global.

   ' Définir la chaîne de connexion pour l'objet Connection.
   gCN.ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & _
   Left(App.Path, Len(App.Path) - Len("client")) & gDBName
   gCN.Open ' Ouvrir la connexion.
   Load frmRevenue
  
  Exit Sub
LoadDBError:
   Select Case Err.Number
   Case -2147467259
      ' Fichier introuvable, utiliser CommonDialog pour le rechercher.
      gCN.ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & _
      GetBooksale
      Resume
   Case Else ' Autres erreurs inconnues
       MsgBox Err.Number & ": " & Err.Description
   End Select
End Sub


Private Sub Form_Load()
  
   'LoadDB ' Charger la base de données et ouvrir la connexion.
    Screen.MousePointer = vbHourglass

    Me.Show

On Error GoTo LoadError
   Set goStatusPanel = sbrRev.Panels(1)
   goStatusPanel.Text = "Extraction de la liste des auteurs..."
   Set gobjServer = CreateObject("BookSaleSvr.Sales")
   GetAuthors
  
  goStatusPanel.Text = "Connexion aux règles à distance..."

  goStatusPanel.Text = "La connexion à distance a réussi..."
  
LoadExit:
Screen.MousePointer = vbDefault
Exit Sub
  
LoadError:
  
   If Err.Number = 429 Then ' erreur CreateObject
       MsgBox "Avant de lancer le programme, créer le fichier BookSaleSvr.exe du projet book_svr.vbp", vbExclamation, " Erreur CreateObject"
       End
  ElseIf Err <> 0 Then ' Une autre erreur.
      MsgBox Error$ & " - " & Str$(Err), vbExclamation, "Erreur dans Form_Load"
      End
  End If
  
  Resume LoadExit

End Sub

Private Sub Form_Unload(Cancel As Integer)

  Set gSn = Nothing
  Set gobjServer = Nothing

End Sub

Private Sub optAnalysis_Click(Index As Integer)

  frmSalesModel.Tag = Index

End Sub

Private Sub txtRevParm_GotFocus(Index As Integer)
  txtRevParm(Index).SelStart = 0
  txtRevParm(Index).SelLength = Len(txtRevParm(Index).Text)
  
End Sub

Private Sub udDiscount_DownClick(Index As Integer)

  If Val(txtRevParm(Index).Text) > 1 Then
    txtRevParm(Index).Text = Val(txtRevParm(Index).Text) - 1
  End If

End Sub

Private Sub udDiscount_UpClick(Index As Integer)

  If Val(txtRevParm(Index).Text) < 99 Then
    txtRevParm(Index).Text = Val(txtRevParm(Index).Text) + 1
  End If

End Sub

