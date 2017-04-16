VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.MDIForm frmMDI 
   BackColor       =   &H8000000C&
   Caption         =   "Gestionnaire de données"
   ClientHeight    =   6510
   ClientLeft      =   4110
   ClientTop       =   2355
   ClientWidth     =   9480
   HelpContextID   =   2016116
   Icon            =   "VDMDI.frx":0000
   LinkTopic       =   "MDIForm1"
   LockControls    =   -1  'True
   Begin MSComCtlLib.Toolbar tlbToolBar 
      Align           =   1  'Align Top
      Height          =   360
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   9480
      _ExtentX        =   16722
      _ExtentY        =   635
      ButtonWidth     =   609
      ButtonHeight    =   582
      AllowCustomize  =   0   'False
      Wrappable       =   0   'False
      Appearance      =   1
      HelpContextID   =   65278
      Style           =   1
      ImageList       =   "imlToolbarPics"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   12
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Table"
            Object.ToolTipText     =   "Jeu d'enregistrements de type Table"
            ImageIndex      =   1
            Style           =   2
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Dynaset"
            Object.ToolTipText     =   "Jeu d'enregistrements de type Dynaset"
            ImageIndex      =   2
            Style           =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Snapshot"
            Object.ToolTipText     =   "Jeu d'enregistrements de type Snapshot"
            ImageIndex      =   3
            Style           =   2
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.Visible         =   0   'False
            Key             =   "PassThrough"
            Object.ToolTipText     =   "Jeu d'enregistrements de type Passthrough"
            ImageIndex      =   4
            Style           =   2
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "DataControl"
            Object.ToolTipText     =   "Utiliser le contrôle Data sur la feuille"
            ImageIndex      =   5
            Style           =   2
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "NoDataControl"
            Object.ToolTipText     =   "Ne pas utiliser de contrôle Data sur la feuille"
            ImageIndex      =   6
            Style           =   2
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "DBGrid"
            Object.ToolTipText     =   "Utiliser le contrôle DBGrid sur la feuille"
            ImageIndex      =   7
            Style           =   2
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Key             =   "BeginTrans"
            Object.ToolTipText     =   "Commencer une transaction"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Key             =   "Rollback"
            Object.ToolTipText     =   "Annuler la transaction en cours"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Enabled         =   0   'False
            Key             =   "Commit"
            Object.ToolTipText     =   "Valider la transaction en cours"
            ImageIndex      =   10
         EndProperty
      EndProperty
   End
   Begin VB.PictureBox Picture1 
      Align           =   1  'Align Top
      BorderStyle     =   0  'None
      Height          =   15
      Left            =   0
      ScaleHeight     =   15
      ScaleWidth      =   9480
      TabIndex        =   2
      Top             =   360
      Width           =   9480
   End
   Begin MSComDlg.CommonDialog dlgCMD1 
      Left            =   -15
      Top             =   690
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FilterIndex     =   1144
   End
   Begin MSComCtlLib.StatusBar stsStatusBar 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   0
      Top             =   6210
      Width           =   9480
      _ExtentX        =   16722
      _ExtentY        =   529
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   2
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   13653
            Text            =   "Prêt"
            TextSave        =   "Prêt"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
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
   Begin MSComCtlLib.ImageList imlToolbarPics 
      Left            =   495
      Top             =   705
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483634
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   10
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":014A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":025C
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":036E
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":0480
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":0592
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":06A4
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":07B6
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":08C8
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":09DA
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "VDMDI.frx":0AEC
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuDatabase 
      Caption         =   "&Fichier"
      HelpContextID   =   2096095
      Begin VB.Menu mnuDBOpen 
         Caption         =   "&Ouvrir une base de données..."
         HelpContextID   =   2016062
         Begin VB.Menu mnuDBOMDB 
            Caption         =   "&Microsoft Access..."
         End
         Begin VB.Menu mnuDBOdBASE 
            Caption         =   "&Dbase"
            Begin VB.Menu mnuDBOdBASE5 
               Caption         =   "&5.0..."
            End
            Begin VB.Menu mnuDBOdBASE4 
               Caption         =   "I&V..."
            End
            Begin VB.Menu mnuDBOdBASE3 
               Caption         =   "&III..."
            End
         End
         Begin VB.Menu mnuDBOFoxPro 
            Caption         =   "&FoxPro"
            Begin VB.Menu mnuDBOFox30 
               Caption         =   "&3.0..."
            End
            Begin VB.Menu mnuDBOFox26 
               Caption         =   "2.&6..."
            End
            Begin VB.Menu mnuDBOFox25 
               Caption         =   "2.&5..."
            End
            Begin VB.Menu mnuDBOFox20 
               Caption         =   "2.&0..."
            End
         End
         Begin VB.Menu mnuDBOParadox 
            Caption         =   "&Paradox"
            Begin VB.Menu mnuDBOParadox5 
               Caption         =   "&5.0..."
            End
            Begin VB.Menu mnuDBOParadox4 
               Caption         =   "&4.X..."
            End
            Begin VB.Menu mnuDBOParadox3 
               Caption         =   "&3.X..."
            End
         End
         Begin VB.Menu mnuDBOBtrieve 
            Caption         =   "&Btrieve..."
         End
         Begin VB.Menu mnuDBOExcel 
            Caption         =   "&Excel..."
         End
         Begin VB.Menu mnuDBOText 
            Caption         =   "Fichiers &texte..."
         End
         Begin VB.Menu mnuDBOODBC 
            Caption         =   "&ODBC..."
            HelpContextID   =   2016138
         End
      End
      Begin VB.Menu mnuDBNew 
         Caption         =   "&Nouvelle base de données..."
         HelpContextID   =   2016083
         Begin VB.Menu mnuDBNMDB 
            Caption         =   "&Microsoft Access"
            Begin VB.Menu mnuDBNMDB2x 
               Caption         =   "MDB version &2.0..."
            End
            Begin VB.Menu mnuDBNMDB70 
               Caption         =   "MDB version &7.0..."
            End
         End
         Begin VB.Menu mnuDBNdBASE 
            Caption         =   "&Dbase"
            Begin VB.Menu mnuDBNdBASE5 
               Caption         =   "&5.0..."
            End
            Begin VB.Menu mnuDBNdBASE4 
               Caption         =   "I&V..."
            End
            Begin VB.Menu mnuDBNdBASE3 
               Caption         =   "&III..."
            End
         End
         Begin VB.Menu mnuDBNFoxPro 
            Caption         =   "&FoxPro"
            Begin VB.Menu mnuDBNFox30 
               Caption         =   "&3.0..."
            End
            Begin VB.Menu mnuDBNFox26 
               Caption         =   "2.&6..."
            End
            Begin VB.Menu mnuDBNFox25 
               Caption         =   "2.&5..."
            End
            Begin VB.Menu mnuDBNFox20 
               Caption         =   "2.&0..."
            End
         End
         Begin VB.Menu mnuDBNParadox 
            Caption         =   "&Paradox"
            Begin VB.Menu mnuDBNParadox5 
               Caption         =   "&5.0..."
            End
            Begin VB.Menu mnuDBNParadox4 
               Caption         =   "&4.X..."
            End
            Begin VB.Menu mnuDBNParadox3 
               Caption         =   "&3.X..."
            End
         End
         Begin VB.Menu mnuDBNBtrieve 
            Caption         =   "&Btrieve..."
         End
         Begin VB.Menu mnuDBNODBC 
            Caption         =   "&ODBC..."
         End
         Begin VB.Menu mnuDBNText 
            Caption         =   "Fichiers &texte..."
         End
      End
      Begin VB.Menu mnuDBClose 
         Caption         =   "&Fermer"
         Enabled         =   0   'False
         HelpContextID   =   2016079
      End
      Begin VB.Menu mnuBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDBImpExp 
         Caption         =   "&Importer/Exporter..."
         Enabled         =   0   'False
         HelpContextID   =   2016092
      End
      Begin VB.Menu mnuDBWorkspace 
         Caption         =   "E&space de travail..."
         HelpContextID   =   2016080
      End
      Begin VB.Menu mnuDBErrors 
         Caption         =   "&Erreurs..."
         HelpContextID   =   2016081
      End
      Begin VB.Menu mnuBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDBCompact 
         Caption         =   "Co&mpacter un fichier MDB..."
         HelpContextID   =   2016084
         Begin VB.Menu mnuDBC70MDB 
            Caption         =   "MDB version &7.0..."
            HelpContextID   =   2016084
         End
         Begin VB.Menu mnuDBC20MDB 
            Caption         =   "MDB version &2.0..."
            HelpContextID   =   2016084
         End
      End
      Begin VB.Menu mnuDBRepair 
         Caption         =   "&Réparer un fichier MDB..."
         HelpContextID   =   2016085
      End
      Begin VB.Menu mnuBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&1"
         HelpContextID   =   2016095
         Index           =   1
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&2"
         HelpContextID   =   2016095
         Index           =   2
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&3"
         HelpContextID   =   2016095
         Index           =   3
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&4"
         HelpContextID   =   2016095
         Index           =   4
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&5"
         HelpContextID   =   2016095
         Index           =   5
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&6"
         HelpContextID   =   2016095
         Index           =   6
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&7"
         HelpContextID   =   2016095
         Index           =   7
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBMRU 
         Caption         =   "&8"
         HelpContextID   =   2016095
         Index           =   8
         Visible         =   0   'False
      End
      Begin VB.Menu mnuBarMRU 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBExit 
         Caption         =   "&Quitter"
         HelpContextID   =   2016095
      End
   End
   Begin VB.Menu mnuUtil 
      Caption         =   "&Utilitaires"
      Enabled         =   0   'False
      HelpContextID   =   2096097
      Begin VB.Menu mnuUQuery 
         Caption         =   "Créateur de &requêtes..."
         HelpContextID   =   2016115
      End
      Begin VB.Menu mnuUDataFormDesigner 
         Caption         =   "Créateur de &feuilles de données..."
         HelpContextID   =   2098108
         Visible         =   0   'False
      End
      Begin VB.Menu mnuUReplace 
         Caption         =   "Remplacement &global..."
         HelpContextID   =   2016091
      End
      Begin VB.Menu mnuUBar1 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuUAttachments 
         Caption         =   "&Pièces jointes..."
         HelpContextID   =   2016086
         Visible         =   0   'False
      End
      Begin VB.Menu mnuUGroupsUsers 
         Caption         =   "&Groupes/Utilisateurs..."
         HelpContextID   =   2016088
         Visible         =   0   'False
      End
      Begin VB.Menu mnuUSystemDB 
         Caption         =   "&System.md?"
         HelpContextID   =   2016090
         Visible         =   0   'False
      End
      Begin VB.Menu mnuUBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPref 
         Caption         =   "&Préférences"
         HelpContextID   =   2093354
         Begin VB.Menu mnuPOpenOnStartup 
            Caption         =   "&Ouvrir la dernière base de données au démarrage"
         End
         Begin VB.Menu mnuPAllowSys 
            Caption         =   "&Inclure les tables système"
         End
         Begin VB.Menu mnuBar4 
            Caption         =   "-"
         End
         Begin VB.Menu mnuPQueryTimeout 
            Caption         =   "Valeur de &QueryTimeout..."
         End
         Begin VB.Menu mnuPLoginTimeout 
            Caption         =   "Valeur de &LoginTimeout..."
         End
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "Fe&nêtre"
      HelpContextID   =   2016100
      WindowList      =   -1  'True
      Begin VB.Menu mnuWTile 
         Caption         =   "&Mosaïque"
      End
      Begin VB.Menu mnuWCascade 
         Caption         =   "&Cascade"
      End
      Begin VB.Menu mnuWArrange 
         Caption         =   "&Organiser les icônes"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&?"
      HelpContextID   =   2093307
      Begin VB.Menu mnuHTopics 
         Caption         =   "&Rubriques"
      End
      Begin VB.Menu mnuBar7 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHAbout 
         Caption         =   "À propo&s de..."
      End
   End
   Begin VB.Menu mnuDBPopUp 
      Caption         =   ""
      Visible         =   0   'False
      Begin VB.Menu mnuDBPUOpen 
         Caption         =   "&Ouvrir"
      End
      Begin VB.Menu mnuDBPUDesign 
         Caption         =   "&Modifier la structure..."
      End
      Begin VB.Menu mnuDBPUEdit 
         Caption         =   "É&diter"
      End
      Begin VB.Menu mnuDBPURename 
         Caption         =   "&Renommer"
      End
      Begin VB.Menu mnuDBPUDelete 
         Caption         =   "&Supprimer"
      End
      Begin VB.Menu mnuDBPUBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDBPUCopyStruct 
         Caption         =   "Copier la structure..."
      End
      Begin VB.Menu mnuDBPURemoveAll 
         Caption         =   "Supprimer tous les enregistrements"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuDBPURefresh 
         Caption         =   "Actualiser la liste"
      End
      Begin VB.Menu mnuDBPUBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDBPUNewTable 
         Caption         =   "Nouvelle &table"
      End
      Begin VB.Menu mnuDBPUNewQuery 
         Caption         =   "Nouvelle &requête"
      End
   End
End
Attribute VB_Name = "frmMDI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Option Compare Binary
'>>>>>>>>>>>>>>>>>>>>>>>>
' Constantes pour les options de menus
Const MNU_Database = "&Fichier"
Const MNU_DBOpen = "&Ouvrir une base de données"
Const MNU_DBOMDB = "&Microsoft Access..."
Const MNU_DBOText = "Fichiers &texte..."
Const MNU_DBOODBC = "&ODBC..."
Const MNU_DBNew = "&Nouvelle base de données..."
Const MNU_DBNMDB = "&Microsoft Access"
Const MNU_DBNMDB2x = "MDB version &2.0..."
Const MNU_DBNMDB70 = "MDB version &7.0..."
Const MNU_DBNODBC = "&ODBC..."
Const MNU_DBNText = "Fichiers &texte..."
Const MNU_DBClose = "&Fermer"
Const MNU_DBImpExp = "&Importer/Exporter..."
Const MNU_DBWorkspace = "E&space de travail..."
Const MNU_DBErrors = "&Erreurs..."
Const MNU_DBCompact = "Co&mpacter un fichier MDB..."
Const MNU_DBRepair = "&Réparer un fichier MDB..."
Const MNU_DBExit = "&Quitter"
Const MNU_Util = "&Utilitaires"
Const MNU_UQuery = "Créateur de &requêtes..."
Const MNU_UDataFormDesigner = "Créateur de &feuilles de données..."
Const MNU_UReplace = "Remplacement &global..."
Const MNU_UAttachments = "&Pièces jointes..."
Const MNU_UGroupsUsers = "&Groupes/Utilisateurs..."
Const MNU_USystemDB = "&Sytem.md?"
Const MNU_Pref = "&Préférences"
Const MNU_POpenOnStartup = "&Ouvrir la dernière base de données au démarrage"
Const MNU_PAllowSys = "&Inclure les tables système"
Const MNU_PQueryTimeout = "Valeur de &QueryTimeout..."
Const MNU_PLoginTimeout = "Valeur de &LoginTimeout..."
Const MNU_Window = "Fe&nêtre"
Const MNU_WTile = "&Mosaïque"
Const MNU_WCascade = "&Cascade"
Const MNU_WArrange = "&Organiser les icônes"
Const MNU_Help = "&?"
Const MNU_HTopics = "&Rubriques..."
Const MNU_HSearch = "&Rechercher de l'aide sur..."
Const MNU_HAbout = "À propo&s de..."
Const MNU_DBPUOpen = "&Ouvrir"
Const MNU_DBPUDesign = "&Modifier la structure..."
Const MNU_DBPUEdit = "É&diter"
Const MNU_DBPURename = "&Renommer"
Const MNU_DBPUDelete = "&Supprimer"
Const MNU_DBPUCopyStruct = "Copier la structure..."
Const MNU_DBPURemoveAll = "Supprimer tous les enregistrements"
Const MNU_DBPURefresh = "Actualiser la liste"
Const MNU_DBPUNewTable = "Nouvelle &table"
Const MNU_DBPUNewQuery = "Nouvelle &requête"

' Valeurs des propriétés Tooltips
Const TOOLTIP1 = "Jeu d'enregistrements de type Table"
Const TOOLTIP2 = "Jeu d'enregistrements de type Dynaset"
Const TOOLTIP3 = "Jeu d'enregistrements de type Snapshot"
Const TOOLTIP4 = "Jeu d'enregistrements de type Passthrough"
Const TOOLTIP5 = "Utiliser le contrôle Data sur la feuille"
Const TOOLTIP6 = "Ne pas utiliser le contrôle Data sur la feuille"
Const TOOLTIP7 = "Utiliser le contrôle DBGrid sur la feuille"
Const TOOLTIP8 = "Commence une transaction"
Const TOOLTIP9 = "Annule la transaction en cours"
Const TOOLTIP10 = "Valide la transaction en cours"

' Chaînes diverses
Const MSG3 = "Appuyez sur n'importe quelle touche pour fermer la boîte de dialogue À propos de"
Const MSG4 = "Entrez les nouveaux paramètres de la nouvelle base de données"
Const MSG5 = "Entrez le nom du pilote indiqué dans le fichier ODBCINST.INI:"
Const MSG6 = "Nom du pilote"
Const MSG7 = "Vous devrez fermer d'abord!"
Const MSG8 = "NOTE: Utilisez la table liée est la méthode recommandée"
Const MSG9 = "Microsoft Access MDBs (*.mdb)|*.mdb|Tous les fichiers (*.*)|*.*"
Const MSG10 = "Ouvrez la base de données Microsoft Access à réparer"
Const MSG11 = "Réparation "
Const MSG12 = "Ouvrir la base de données réparée?"
Const MSG13 = "System Databases|SYSTEM.MD?"
Const MSG14 = "Sélectionnez SYSTEM.MD? (Microsoft Access Security File)"
Const MSG15 = " Utilisateur: "
Const MSG16 = "La base de données en cours va être fermée suite à une erreur!"
Const MSG17 = "Aucun utilisateur trouvé, essayez 'Utilitaires/System.md?'!"
Const MSG18 = "LoginTimeout (en secondes):"
Const MSG19 = "Aucune base de données ouverte"
Const MSG20 = "QueryTimeout (en secondes):"
Const MSG21 = "Supprimer la table?"
Const MSG22 = "Supprimer QueryDef?"
Const MSG23 = "Supprimer le champ?"
Const MSG24 = "Supprimer l'index?"
Const MSG25 = "Supprimer tous les enregistrements de la table?"
Const MSG26 = "Lignes supprimées: "
Const MSG27 = "System.md? non trouvé, en ajoutez un pour VB?"
Const MSG28 = "Les transactions ne sont pas gérées par ce pilote!"
Const MSG29 = "Toutes les modifications seront perdues, voulez-vous quand même annuler la transaction?"
Const MSG30 = " : Cette propriété est en lecture seule !"
Const MSG31 = "Cette fonction requiert un projet actif!"
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim mHwnd As Long

Private Sub mnuDBC70MDB_Click()
  CompactDB dbVersion30
End Sub

Private Sub mnuDBNMDB2x_Click()
  NewMDB dbVersion20
End Sub

Private Sub mnuDBNMDB70_Click()
  NewMDB dbVersion30
End Sub

Private Sub mnuDBOExcel_Click()
  ' Nous pouvons utiliser Excel 5.0 pour tous les
  ' fichiers Excel: le fichier ISAM reconnaît la
  ' version à l'ouverture du fichier.
  gsDataType = gsEXCEL50
  OpenLocalDB False
End Sub

Private Sub mnuDBPUDesign_Click()
  On Error Resume Next

  If gnodDBNode2 Is Nothing Then Exit Sub
  If gnodDBNode2.Tag = TABLE_STR Then
    gbAddTableFlag = False
    Screen.MousePointer = vbHourglass
    frmTblStruct.Show vbModal
  ElseIf gnodDBNode2.Tag = QUERY_STR Then
    Set frmDatabase.tvDatabase.SelectedItem = gnodDBNode2
    frmSQL.txtSQLStatement.Text = gdbCurrentDB.QueryDefs(gnodDBNode2.Text).SQL
  End If

End Sub

Sub mnuDBPUEdit_Click()
  On Error GoTo mnuDBPUEdit_ClickErr
  
  Dim prpObj As Property
  Dim vTmp As Variant
  Dim vNew As Variant
  Dim frmProp As New frmProperty
  
  If gnodDBNode2.Parent.Parent Is Nothing Then
   ' Doit être une propriété d'une base de données.
    Set prpObj = gdbCurrentDB.Properties(VBA.Left(gnodDBNode2.Text, InStr(gnodDBNode2.Text, "=") - 1))
  Else
    Select Case gnodDBNode2.Parent.Parent.Tag
      Case TABLE_STR
        Set prpObj = gdbCurrentDB.TableDefs(gnodDBNode2.Parent.Parent.Text).Properties(VBA.Left(gnodDBNode2.Text, InStr(gnodDBNode2.Text, "=") - 1))
      Case QUERY_STR
        Set prpObj = gdbCurrentDB.QueryDefs(gnodDBNode2.Parent.Parent.Text).Properties(VBA.Left(gnodDBNode2.Text, InStr(gnodDBNode2.Text, "=") - 1))
      Case FIELDS_STR
        Set prpObj = gdbCurrentDB.TableDefs(gnodDBNode2.Parent.Parent.Parent.Text).Fields(gnodDBNode2.Parent.Text).Properties(VBA.Left(gnodDBNode2.Text, InStr(gnodDBNode2.Text, "=") - 1))
      Case INDEXES_STR
        Set prpObj = gdbCurrentDB.TableDefs(gnodDBNode2.Parent.Parent.Parent.Text).Indexes(gnodDBNode2.Parent.Text).Properties(VBA.Left(gnodDBNode2.Text, InStr(gnodDBNode2.Text, "=") - 1))
      Case Else
        Exit Sub
    End Select
  End If
  
  ' Stocke la valeur
  vTmp = prpObj.Value
  
  On Error Resume Next
  ' Tente de lui affecter sa valeur actuelle.
  ' pour vérifier s'il est en lecture seule.
  prpObj.Value = vTmp
  If Err Then
    ' Lecture seule, quitte.
    Err.Clear
    MsgBox "'" & prpObj.Name & "'" & MSG30, vbExclamation
    Exit Sub
  End If
  On Error GoTo mnuDBPUEdit_ClickErr
  
  With frmProp
    Set .PropObject = prpObj
    .Show vbModal
    If .OK Then
      gnodDBNode2.Text = prpObj.Name & "=" & prpObj.Value
      ' Vérifie s'il s'agit d'une propriété Name.
      If prpObj.Name = "Name" Then
        gnodDBNode2.Parent.Text = prpObj.Value
      End If

    End If
    Unload frmProp
  End With
  Set frmProp = Nothing
  
  Exit Sub
mnuDBPUEdit_ClickErr:
  ShowError
End Sub

Private Sub mnuDBPUNewQuery_Click()
  ' Charge le créateur de requêtes.
  Unload frmQuery      ' Efface le contenu des objets existants
  frmQuery.Show
End Sub

Private Sub mnuDBPUNewTable_Click()
  gbAddTableFlag = True
  Screen.MousePointer = vbHourglass
  frmTblStruct.Show vbModal
End Sub

Sub mnuDBPUOpen_Click()
  On Error Resume Next
  
  gbFromSQL = False
  Screen.MousePointer = vbHourglass
  
  If gnodDBNode.Tag = TABLE_STR Then
    OpenTable StripConnect(gnodDBNode2.Text)
  ElseIf gnodDBNode.Tag = QUERY_STR Then
    OpenQuery gnodDBNode2.Text, False
  End If
  
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False

End Sub

Private Sub mnuHAbout_Click()
  MsgBar MSG3, False
  frmAboutBox.Show vbModal
  MsgBar vbNullString, False
End Sub

Private Sub mnuDBC20MDB_Click()
  CompactDB dbVersion20
End Sub


Private Sub mnuDBClose_Click()
  CloseCurrentDB
End Sub

Private Sub mnuDBErrors_Click()
  On Error Resume Next
  Screen.MousePointer = vbHourglass
  RefreshErrors
  Screen.MousePointer = vbDefault
  If Err Then ShowError
End Sub

Private Sub mnuDBExit_Click()
  Unload Me
End Sub

Private Sub mnuDBNBtrieve_Click()
   gsDataType = gsBTRIEVE
   NewLocalISAM
End Sub

Private Sub mnuDBNDbase3_Click()
   gsDataType = gsDBASEIII
   NewLocalISAM
End Sub

Private Sub mnuDBNDbase4_Click()
   gsDataType = gsDBASEIV
   NewLocalISAM
End Sub

Private Sub mnuDBNDbase5_Click()
   gsDataType = gsDBASE5
   NewLocalISAM
End Sub

Private Sub mnuDBNFox20_Click()
   gsDataType = gsFOXPRO20
   NewLocalISAM
End Sub

Private Sub mnuDBNFox25_Click()
   gsDataType = gsFOXPRO25
   NewLocalISAM
End Sub

Private Sub mnuDBNFox26_Click()
   gsDataType = gsFOXPRO26
   NewLocalISAM
End Sub

Private Sub mnuDBNFox30_Click()
   gsDataType = gsFOXPRO30
   NewLocalISAM
End Sub

Private Sub mnuDBNODBC_Click()
  On Error GoTo DBNErr

  Dim sDriverName As String

  MsgBar MSG4, False

  ' Le pilote doit être une entrée valide figurant dans le fichier
  ' ODBCINST.INI.
  sDriverName = InputBox(MSG5, MSG6, gsDEFAULT_DRIVER)

  If Len(sDriverName) = 0 Then Exit Sub ' Annulation
  
  DBEngine.RegisterDatabase vbNullString, sDriverName, False, vbNullString

  SendKeys "%FOO"   ' Force l'ouverture d'une boîte de dialogue de la base de données.

  MsgBar vbNullString, False
  Exit Sub

DBNErr:
  ShowError
End Sub

Private Sub mnuDBNParadox3_Click()
  gsDataType = gsPARADOX3X
  NewLocalISAM
End Sub

Private Sub mnuDBNParadox4_Click()
  gsDataType = gsPARADOX4X
  NewLocalISAM
End Sub

Private Sub mnuDBNParadox5_Click()
  gsDataType = gsPARADOX5X
  NewLocalISAM
End Sub

Private Sub mnuDBNText_Click()
  gsDataType = gsTEXTFILES
  NewLocalISAM
End Sub

Private Sub mnuDBOMDB_Click()
  gsDataType = gsMSACCESS
  OpenLocalDB False
End Sub

Private Sub mnuDBOBtrieve_Click()
  gsDataType = gsBTRIEVE
  OpenLocalDB False
End Sub

Private Sub mnuDBODbase3_Click()
   gsDataType = gsDBASEIII
   OpenLocalDB False
End Sub

Private Sub mnuDBODbase4_Click()
   gsDataType = gsDBASEIV
   OpenLocalDB False
End Sub

Private Sub mnuDBODbase5_Click()
   gsDataType = gsDBASE5
   OpenLocalDB False
End Sub

Private Sub mnuDBOFox20_Click()
   gsDataType = gsFOXPRO20
   OpenLocalDB False
End Sub

Private Sub mnuDBOFox25_Click()
   gsDataType = gsFOXPRO25
   OpenLocalDB False
End Sub

Private Sub mnuDBOFox26_Click()
   gsDataType = gsFOXPRO26
   OpenLocalDB False
End Sub

Private Sub mnuDBOFox30_Click()
   gsDataType = gsFOXPRO30
   OpenLocalDB False
End Sub

Private Sub mnuDBOODBC_Click()
  Dim frm As New frmODBCLogon

  frm.Show vbModal
  
  If frm.DBOpened Then
    ShowDBTools
    RefreshTables Nothing
    MsgBar MSG8, False
  End If
  
  Unload frm
  Set frm = Nothing
  
End Sub

Private Sub mnuDBOParadox3_Click()
   gsDataType = gsPARADOX3X
   OpenLocalDB False
End Sub

Private Sub mnuDBOParadox4_Click()
   gsDataType = gsPARADOX4X
   OpenLocalDB False
End Sub

Private Sub mnuDBOParadox5_Click()
   gsDataType = gsPARADOX5X
   OpenLocalDB False
End Sub

Private Sub mnuDBOText_Click()
   gsDataType = gsTEXTFILES
   OpenLocalDB False
End Sub

Private Sub mnuDBRepair_Click()
  On Error GoTo RepairAccErr

  Dim sNewName As String

  ' Obtient le nom du fichier à réparer.
  With dlgCMD1
    .Filter = MSG9
    .DialogTitle = MSG10
    .FilterIndex = 1
    .Flags = FileOpenConstants.cdlOFNHideReadOnly
    .ShowOpen
  End With
  If Len(dlgCMD1.FileName) > 0 Then
    sNewName = dlgCMD1.FileName
  Else
    Exit Sub
  End If

  Screen.MousePointer = vbHourglass
  MsgBar MSG11 & sNewName, True
  DBEngine.RepairDatabase sNewName
  Screen.MousePointer = vbDefault
  MsgBar vbNullString, False

  If MsgBox(MSG12, vbYesNo + vbQuestion) = vbYes Then
    If gbDBOpenFlag Then
      Call mnuDBClose_Click
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

RepairAccErr:
  If Err <> 32755 Then
    ShowError
  End If
End Sub

Private Sub mnuHTopics_Click()
  DisplayTopic 2016111
End Sub



Private Sub mnuUSystemDB_Click()
  On Error Resume Next
  
  Dim sTmp As String
  Dim x As Integer
  
  With dlgCMD1
    .Filter = MSG13
    .DialogTitle = MSG14
    .FilterIndex = 1
    .FileName = "SYSTEM.MDW"
    .CancelError = True
    .Flags = FileOpenConstants.cdlOFNHideReadOnly + FileOpenConstants.cdlOFNFileMustExist
  End With
  On Error Resume Next
  dlgCMD1.ShowOpen
  If Err = 32755 Then         ' L'utilisateur a annulé
    Exit Sub
  Else
    sTmp = dlgCMD1.FileName  ' Doit être un fichier correct.
    SaveSetting APP_CATEGORY & "\VisData", "Engines", "SystemDB", sTmp
  End If

End Sub

Private Sub mnuDBWorkspace_Click()
  On Error GoTo WSErr
    
  Dim sDBName As String
  Dim sConnect As String
  Dim sUser As String
    
  If gbDBOpenFlag Then
    ' Sauvegarde les anciennes définitions.
    sDBName = gdbCurrentDB.Name
    sConnect = gdbCurrentDB.Connect
    sUser = gwsMainWS.UserName
  End If
  
  frmLogin.Show vbModal
  stsStatusBar.Panels(2).Text = MSG15 & gwsMainWS.UserName & " "
  
  ' Rouvre la base de données si l'utilisateur a changé.
  If UCase(sUser) <> UCase(gwsMainWS.UserName) And gbDBOpenFlag Then
    ' Réinitialise tous les objets qui sont non valides
    ' après avoir rouvert la base de données.
    CloseAllRecordsets
    Set gdbCurrentDB = gwsMainWS.OpenDatabase(sDBName, False, gnReadOnly, sConnect)
  End If
  
  Exit Sub
  
WSErr:
  ShowError
  If gbDBOpenFlag Then
    MsgBox MSG16, 48
  End If
  Call mnuDBClose_Click
End Sub

Private Sub mnuUAttachments_Click()
  On Error Resume Next
  Screen.MousePointer = vbHourglass
  frmAttachments.Show
  Screen.MousePointer = vbDefault
  If Err Then ShowError
End Sub

Private Sub mnuUGroupsUsers_Click()
  On Error Resume Next
    
  If gwsMainWS.Users.Count = 0 Then
    Beep
    MsgBox MSG17, 48
    Exit Sub
  End If
    
  Screen.MousePointer = vbHourglass
  frmGroupsUsers.Show
  Screen.MousePointer = vbDefault
  If Err Then ShowError
End Sub

Private Sub mnuPAllowSys_Click()
  On Error Resume Next

  mnuPAllowSys.Checked = Not mnuPAllowSys.Checked
  If Not gbDBOpenFlag Then Exit Sub
  
  RefreshTables Nothing
  
End Sub

Private Sub mnuPLoginTimeout_Click()
  On Error GoTo LTErr

  Dim sNewValue As String

  sNewValue = InputBox(MSG18, , CStr(glLoginTimeout))
  If Len(sNewValue) = 0 Then Exit Sub

  ' Tente d'affecter la nouvelle valeur.
  If Val(sNewValue) >= 0 Then
    glLoginTimeout = Val(sNewValue)
    DBEngine.LoginTimeout = glLoginTimeout
  End If

  Exit Sub

LTErr:
  ShowError
End Sub

Private Sub mnuPOpenOnStartup_Click()
  mnuPOpenOnStartup.Checked = Not mnuPOpenOnStartup.Checked
End Sub

Private Sub mnuPQueryTimeout_Click()
  On Error GoTo QTErr

  Dim sNewValue As String

  If Not gbDBOpenFlag Then MsgBox MSG19, 48: Exit Sub
  
  sNewValue = InputBox(MSG20, , CStr(gdbCurrentDB.QueryTimeout))
  If Len(sNewValue) = 0 Then Exit Sub

  ' Tente d'affecter la nouvelle valeur.
  gdbCurrentDB.QueryTimeout = Val(sNewValue)
  glQueryTimeout = Val(sNewValue)

  Exit Sub

QTErr:
  ShowError
  ' Réinitialise la valeur du contrôle de la feuille après l'erreur.
  glQueryTimeout = gdbCurrentDB.QueryTimeout
End Sub

Private Sub mnuUDataFormDesigner_Click()

  On Error Resume Next
  ' Vérifie que le projet à été chargé
  If gVDClass.VBInstance.ActiveVBProject Is Nothing Then
    MsgBox MSG31, vbInformation
    Exit Sub
  End If
  
  frmDFD.Show vbModal
  If Err Then ShowError
End Sub

Private Sub mnuUQuery_Click()
  frmQuery.Show
  frmQuery.WindowState = 0
End Sub

Private Sub mnuDBPUCopyStruct_Click()
  On Error Resume Next
  frmCopyStruct.Show vbModal
  If Err Then ShowError
End Sub

Private Sub mnuDBPUDelete_Click()
  On Error GoTo TblDelErr

  Dim sName As String
  If gnodDBNode2 Is Nothing Then Exit Sub
  
  Select Case gnodDBNode2.Tag
    Case TABLE_STR
      sName = StripConnect(gnodDBNode2.Text)
      If MsgBox(MSG21, vbYesNo + vbQuestion) = vbYes Then
        gdbCurrentDB.TableDefs.Delete sName
        frmDatabase.tvDatabase.Nodes.Remove gnodDBNode2.Index
      End If
    Case QUERY_STR
      sName = gnodDBNode2.Text
      If MsgBox(MSG22, vbYesNo + vbQuestion) = vbYes Then
        gdbCurrentDB.QueryDefs.Delete sName
        frmDatabase.tvDatabase.Nodes.Remove gnodDBNode2.Index
      End If
    Case FIELD_STR
      sName = gnodDBNode2.Text
      If MsgBox(MSG23, vbYesNo + vbQuestion) = vbYes Then
        gdbCurrentDB.TableDefs(gnodDBNode2.Parent.Parent.Text).Fields.Delete sName
        frmDatabase.tvDatabase.Nodes.Remove gnodDBNode2.Index
      End If
    Case INDEX_STR
      sName = gnodDBNode2.Text
      If MsgBox(MSG24, vbYesNo + vbQuestion) = vbYes Then
        gdbCurrentDB.TableDefs(gnodDBNode2.Parent.Parent.Text).Indexes.Delete sName
        frmDatabase.tvDatabase.Nodes.Remove gnodDBNode2.Index
      End If
  End Select

  Exit Sub

TblDelErr:
  ShowError
End Sub

Private Sub mnuDBPURefresh_Click()
  gdbCurrentDB.TableDefs.Refresh
  RefreshTables Nothing
End Sub

Private Sub mnuDBPURename_Click()
  On Error GoTo mnuDBPURename_ClickErr
  
  If Not gnodDBNode2 Is Nothing Then
    ' L'affecte au nouveau nœud pour le modifier.
    Set frmDatabase.tvDatabase.SelectedItem = gnodDBNode2
    frmDatabase.tvDatabase.StartLabelEdit
  End If

  Exit Sub

mnuDBPURename_ClickErr:
  ShowError
End Sub

Private Sub mnuDBPURemoveAll_Click()
  On Error GoTo RemoveAllErr

  Dim sTBLName As String
  
  sTBLName = StripConnect(gnodDBNode.Text)

  If MsgBox(MSG25 & " '" & sTBLName & "'", vbYesNo + vbQuestion) = vbYes Then
    ' supprime toutes les lignes en utilisant une instruction SQL.
    If gsDataType = gsSQLDB Then
      gdbCurrentDB.Execute ("delete from " & sTBLName), dbSQLPassThrough
    Else
      gdbCurrentDB.Execute ("delete from " & sTBLName)
    End If
    If gdbCurrentDB.RecordsAffected > 0 Then
      MsgBox MSG26 & gdbCurrentDB.RecordsAffected, 48
      If gbTransPending Then gbDBChanged = True
    End If

  End If

  Exit Sub

RemoveAllErr:
  If Err = gnEOF_ERR Then Resume Next
  ShowError
End Sub

Private Sub mnuDBImpExp_Click()
  On Error Resume Next
  frmImpExp.Show vbModal
  If Err Then ShowError
End Sub

Private Sub mnuUReplace_Click()
  On Error GoTo ReplaceErr

  frmReplace.Show vbModal

  Exit Sub

ReplaceErr:
  ShowError
End Sub

Private Sub mnuWArrange_Click()
  Me.Arrange 3
End Sub

Private Sub mnuWCascade_Click()
  Me.Arrange 0
End Sub

Private Sub mnuWTile_Click()
  Me.Arrange 2
End Sub

Private Sub MDIForm_Load()
  On Error GoTo MDILErr

  Dim x As Integer

  ' Charge les chaînes contenues
  ' dans les constantes de menus.
  mnuDatabase.Caption = MNU_Database
  mnuDBOpen.Caption = MNU_DBOpen
  mnuDBOMDB.Caption = MNU_DBOMDB
  mnuDBOText.Caption = MNU_DBOText
  mnuDBOODBC.Caption = MNU_DBOODBC
  mnuDBNew.Caption = MNU_DBNew
  mnuDBNMDB.Caption = MNU_DBNMDB
  mnuDBNMDB2x.Caption = MNU_DBNMDB2x
  mnuDBNMDB70.Caption = MNU_DBNMDB70
  mnuDBNODBC.Caption = MNU_DBNODBC
  mnuDBNText.Caption = MNU_DBNText
  mnuDBClose.Caption = MNU_DBClose
  mnuDBImpExp.Caption = MNU_DBImpExp
  mnuDBWorkspace.Caption = MNU_DBWorkspace
  mnuDBErrors.Caption = MNU_DBErrors
  mnuDBCompact.Caption = MNU_DBCompact
  mnuDBRepair.Caption = MNU_DBRepair
  mnuDBExit.Caption = MNU_DBExit
  mnuUtil.Caption = MNU_Util
  mnuUQuery.Caption = MNU_UQuery
  mnuUDataFormDesigner.Caption = MNU_UDataFormDesigner
  mnuUReplace.Caption = MNU_UReplace
  mnuUAttachments.Caption = MNU_UAttachments
  mnuUGroupsUsers.Caption = MNU_UGroupsUsers
  mnuUSystemDB.Caption = MNU_USystemDB
  mnuPref.Caption = MNU_Pref
  mnuPOpenOnStartup.Caption = MNU_POpenOnStartup
  mnuPAllowSys.Caption = MNU_PAllowSys
  mnuPQueryTimeout.Caption = MNU_PQueryTimeout
  mnuPLoginTimeout.Caption = MNU_PLoginTimeout
  mnuWindow.Caption = MNU_Window
  mnuWTile.Caption = MNU_WTile
  mnuWCascade.Caption = MNU_WCascade
  mnuWArrange.Caption = MNU_WArrange
  mnuHelp.Caption = MNU_Help
  mnuHTopics.Caption = MNU_HTopics
  mnuHAbout.Caption = MNU_HAbout
  mnuDBPUOpen.Caption = MNU_DBPUOpen
  mnuDBPUDesign.Caption = MNU_DBPUDesign
  mnuDBPUEdit.Caption = MNU_DBPUEdit
  mnuDBPURename.Caption = MNU_DBPURename
  mnuDBPUDelete.Caption = MNU_DBPUDelete
  mnuDBPUCopyStruct.Caption = MNU_DBPUCopyStruct
  mnuDBPURemoveAll.Caption = MNU_DBPURemoveAll
  mnuDBPURefresh.Caption = MNU_DBPURefresh
  mnuDBPUNewTable.Caption = MNU_DBPUNewTable
  mnuDBPUNewQuery.Caption = MNU_DBPUNewQuery
  
  ' Info-bulles
  tlbToolBar.Buttons(1).ToolTipText = TOOLTIP1
  tlbToolBar.Buttons(2).ToolTipText = TOOLTIP2
  tlbToolBar.Buttons(3).ToolTipText = TOOLTIP3
  tlbToolBar.Buttons(4).ToolTipText = TOOLTIP4
  tlbToolBar.Buttons(6).ToolTipText = TOOLTIP5
  tlbToolBar.Buttons(7).ToolTipText = TOOLTIP6
  tlbToolBar.Buttons(8).ToolTipText = TOOLTIP7
  tlbToolBar.Buttons(10).ToolTipText = TOOLTIP8
  tlbToolBar.Buttons(11).ToolTipText = TOOLTIP9
  tlbToolBar.Buttons(12).ToolTipText = TOOLTIP10

  gnMULocking = True   ' Verrouillage pessimiste par défaut.
  App.HelpFile = "vb98.chm"
  setHelpFile App.HelpFile            ' Affecte le nom du fichier d'aide HTML pour le moteur d'Aide HTML
  setHelpLocaleID GetVbIdeLocale      ' Lit la valeur locale de VBIDE pour le moteur d'Aide HTML
 
  ' Désactive les options de menus relatives à
  ' Btrieve sous un environnement 32 bits.
  mnuDBOBtrieve.Visible = False
  mnuDBNBtrieve.Visible = False

  'Obtient les coordonnées de la feuille.
  x = Val(GetRegistryString("WindowState", "2"))
  If x = vbMaximized Then
    Show
  ElseIf x <> vbMinimized Then
    frmMDI.WindowState = x
  Else
    frmMDI.WindowState = 0
  End If
  If frmMDI.WindowState = 0 Then
    frmMDI.Left = Val(GetRegistryString("WindowLeft", "0"))
    frmMDI.Top = Val(GetRegistryString("WindowTop", "0"))
    Show
    frmMDI.Width = Val(GetRegistryString("WindowWidth", "9135"))
    frmMDI.Height = Val(GetRegistryString("WindowHeight", "6900"))
  End If
  
  On Error GoTo MDILErr
  
  ' Configure le moteur de BD
  DBEngine.IniPath = "HKEY_CURRENT_USER\Software\VB and VBA Program Settings\" & APP_CATEGORY & "\" & APPNAME
  DBEngine.DefaultUser = "admin"
  DBEngine.DefaultPassword = vbNullString

  ' Connexion au moteur Jet
  On Error Resume Next
  Set gwsMainWS = DBEngine.CreateWorkspace("MainWS", "admin", vbNullString)
  If Err = 3029 Then
    frmLogin.Show vbModal
  ElseIf Err = 3044 Then  ' Chemin non valide pour le fichier system.mda.
    If MsgBox(MSG27, vbYesNo + vbQuestion) = vbYes Then
      mnuUSystemDB_Click
    Else
      ' Sauvegarde l'information pour ne plus demander
      ' de confirmation.
      SaveSetting APP_CATEGORY & "\VisData", "Engines", "SystemDB", vbNullString
    End If
  ElseIf Err <> 0 Then
    ShowError
    Unload Me
    Exit Sub
  End If
  stsStatusBar.Panels(2).Text = MSG15 & gwsMainWS.UserName & " "
  
  On Error GoTo MDILErr
  
  ' Ajoute un espace de travail à la collection afin de contenir
  ' le nombre de lignes.
  Workspaces.Append gwsMainWS
  Me.Show
  LoadRegistrySettings
  
  ' Tente d'ouvrir la dernière base de données si cette option a
  ' été activée dans le sous-menu Préférences du menu Utilitaires.
  If frmMDI.mnuPOpenOnStartup.Checked And Len(gsDBName) > 0 Then
    If gsDataType = gsSQLDB Then
       ' Pour une base de données ODBC, utilise la commande
       ' sendkeys pour ouvrir la boîte de dialogue ODBC.
       ' SendKeys "%FOO{Enter}"
      mnuDBOODBC_Click
    Else
      OpenLocalDB True
    End If
  Else
    HideDBTools
  End If

  Exit Sub

MDILErr:
  ShowError
End Sub

Private Sub MDIForm_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  On Error Resume Next
  ShutDownVisData
End Sub

Private Sub mnuDBMRU_Click(Index As Integer)
  On Error GoTo MRUErr

  gsDBName = Mid(mnuDBMRU(Index).Caption, 4, Len(mnuDBMRU(Index).Caption))
  gsDataType = mnuDBMRU(Index).Tag
  If UCase(Left(gsDataType, 5)) <> gsSQLDB Then
    OpenLocalDB True
  Else
    ' Doit être une base de données ODBC: il faut charger la
    ' feuille frmOpenDB.
    ' Obtient la connexion
    GetODBCConnectParts gsDataType
    ' Appelle la routine de chargement de la feuille.
    mnuDBOODBC_Click
  End If

  Exit Sub

MRUErr:
  ShowError
End Sub

Private Sub tlbToolBar_ButtonClick(ByVal BUTTON As BUTTON)
  On Error GoTo tlbToolBar_ButtonClickErr
  
  Select Case BUTTON.Key
    Case "DataControl"
      gnFormType = gnFORM_DATACTL
    Case "NoDataControl"
      gnFormType = gnFORM_NODATACTL
    Case "DBGrid"
      gnFormType = gnFORM_DATAGRID
    
    Case "Table"
      gnRSType = gnRS_TABLE
    Case "Dynaset"
      gnRSType = gnRS_DYNASET
    Case "Snapshot"
      gnRSType = gnRS_SNAPSHOT
    Case "PassThrough"
      gnRSType = gnRS_PASSTHRU
    
    Case "BeginTrans"
      If gdbCurrentDB.Transactions = False Then
        Beep
        MsgBox MSG28
        Exit Sub
      End If
      gwsMainWS.BeginTrans
      gbDBChanged = False
      gbTransPending = True
      tlbToolBar.Buttons("BeginTrans").Enabled = False
      tlbToolBar.Buttons("Commit").Enabled = True
      tlbToolBar.Buttons("Rollback").Enabled = True
    Case "Rollback"
      If MsgBox(MSG29, vbYesNo + vbQuestion) = vbYes Then
        gwsMainWS.Rollback
        gbDBChanged = False
        gbTransPending = False
        tlbToolBar.Buttons("BeginTrans").Enabled = True
        tlbToolBar.Buttons("Commit").Enabled = False
        tlbToolBar.Buttons("Rollback").Enabled = False
      End If
    Case "Commit"
      gwsMainWS.CommitTrans
      gbDBChanged = False
      gbTransPending = False
      tlbToolBar.Buttons("BeginTrans").Enabled = True
      tlbToolBar.Buttons("Commit").Enabled = False
      tlbToolBar.Buttons("Rollback").Enabled = False
  End Select
  
  Exit Sub
tlbToolBar_ButtonClickErr:
  ShowError
End Sub
