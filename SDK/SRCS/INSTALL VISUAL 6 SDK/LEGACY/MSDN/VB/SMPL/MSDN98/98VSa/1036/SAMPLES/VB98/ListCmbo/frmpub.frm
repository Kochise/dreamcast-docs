VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form frmPublishers 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Éditeurs"
   ClientHeight    =   3090
   ClientLeft      =   1065
   ClientTop       =   2130
   ClientWidth     =   7350
   Icon            =   "frmpub.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3090
   ScaleWidth      =   7350
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdAbout 
      Caption         =   "&À propos de"
      Height          =   375
      Left            =   5880
      TabIndex        =   9
      Top             =   630
      Width           =   1065
   End
   Begin VB.CommandButton cmdDone 
      Cancel          =   -1  'True
      Caption         =   "&Terminé"
      Height          =   375
      Left            =   5880
      TabIndex        =   8
      Top             =   240
      Width           =   1065
   End
   Begin VB.OptionButton optListBox 
      Caption         =   "Utiliser le contrôle ListBox standard"
      Height          =   255
      Left            =   3360
      TabIndex        =   7
      Top             =   1860
      Width           =   2775
   End
   Begin VB.OptionButton optComboBox 
      Caption         =   "Utiliser le contrôle ComboBox standard"
      Height          =   315
      Left            =   3360
      TabIndex        =   6
      Top             =   1560
      Value           =   -1  'True
      Width           =   3135
   End
   Begin VB.TextBox txtCity 
      DataSource      =   "datPublishers"
      Height          =   285
      Left            =   1740
      Locked          =   -1  'True
      TabIndex        =   3
      Top             =   1140
      Width           =   4000
   End
   Begin VB.TextBox txtAddress 
      DataSource      =   "datPublishers"
      Height          =   285
      Left            =   1740
      Locked          =   -1  'True
      TabIndex        =   2
      Top             =   840
      Width           =   4000
   End
   Begin VB.TextBox txtCompanyName 
      DataSource      =   "datPublishers"
      Height          =   285
      Left            =   1740
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   540
      Width           =   4000
   End
   Begin VB.TextBox txtName 
      DataSource      =   "datPublishers"
      Height          =   285
      Left            =   1740
      Locked          =   -1  'True
      TabIndex        =   0
      Top             =   240
      Width           =   4000
   End
   Begin VB.Data datPublishers 
      Align           =   2  'Align Bottom
      Connect         =   "Access"
      DatabaseName    =   "..\..\..\Biblio.mdb"
      DefaultCursorType=   0  'DefaultCursor
      DefaultType     =   2  'UseODBC
      Exclusive       =   0   'False
      Height          =   345
      Left            =   0
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   2  'Snapshot
      RecordSource    =   ""
      Top             =   2745
      Width           =   7344
   End
   Begin VB.ComboBox cboState 
      DataSource      =   "datPublishers"
      Height          =   315
      Left            =   1740
      Sorted          =   -1  'True
      TabIndex        =   4
      Text            =   "cmbState"
      Top             =   1455
      Width           =   1215
   End
   Begin VB.ListBox lstState 
      DataSource      =   "datPublishers"
      Height          =   645
      Left            =   1740
      Sorted          =   -1  'True
      TabIndex        =   5
      Top             =   1455
      Visible         =   0   'False
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog dlgDialog 
      Left            =   120
      Top             =   2160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      Caption         =   "État :"
      Height          =   195
      Left            =   360
      TabIndex        =   14
      Top             =   1500
      Width           =   1305
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Ville :"
      Height          =   195
      Left            =   360
      TabIndex        =   13
      Top             =   1200
      Width           =   1305
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Adresse :"
      Height          =   195
      Left            =   360
      TabIndex        =   12
      Top             =   900
      Width           =   1305
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Nom de l'entreprise :"
      Height          =   195
      Left            =   240
      TabIndex        =   11
      Top             =   600
      Width           =   1425
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Nom :"
      Height          =   195
      Left            =   360
      TabIndex        =   10
      Top             =   300
      Width           =   1305
   End
End
Attribute VB_Name = "frmPublishers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdAbout_Click()
   Dim frmX As New frmAbout
   '
   ' Affiche la boîte de dialogue À propos de.
   '
   frmX.Show vbModal
   Set frmX = Nothing
   
End Sub

Private Sub cmdDone_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   Dim vntTemp As Variant
   Dim vnDummy As Variant
   
   On Error GoTo Form_LoadError
   
   ' Retrouve tous les états de la table.
   '
   datPublishers.DatabaseName = "..\..\..\Biblio.mdb"
   datPublishers.RecordSource = "SELECT DISTINCT state FROM Publishers"
   datPublishers.Refresh
   '
   ' Charge les abréviations des états dans les contrôles ListBox et ComboBox.
   ' Si le nom du fichier de la base de données est incorrect, une erreur récupérable se produit ici.
   Do While Not datPublishers.Recordset.EOF
      vntTemp = datPublishers.Recordset!State
      If IsNull(vntTemp) Then vntTemp = ""
      cboState.AddItem CStr(vntTemp)
      lstState.AddItem CStr(vntTemp)
      datPublishers.Recordset.MoveNext
   Loop
   '
   ' Retrouve tous les enregistrements de la table Publishers (Éditeurs).
   '
   datPublishers.RecordSource = "Publishers"
   datPublishers.RecordsetType = vbRSTypeTable
   datPublishers.Refresh
   '
   ' Lie les champs avec le contrôle Data
   '
   txtName.DataField = "Name"
   txtAddress.DataField = "Address"
   txtCompanyName.DataField = "Company Name"
   txtCity.DataField = "City"
   
   cboState.DataField = "State"
   lstState.DataField = "State"
    
Form_LoadExit:
Exit Sub
    
Form_LoadError:
    ' Si la base de données Biblio ne peut pas être trouvée, ouvre le contrôle CommonDialog
    ' pour permettre à l'utilisateur de la localiser.
    ' Le fichier biblio.mdb est placé dans le même dossier que VB5
    If Err = 3024 Then
        With dlgDialog
            .DialogTitle = "Impossible de trouver Biblio.mdb"
            .Filter = "(*.MDB)|*.mdb"
            .ShowOpen
        End With
        If dlgDialog.filename <> "" Then
        'Assurez-vous que le fichier de la base de donnée renvoyé est biblio.mdb
            If Right(UCase(dlgDialog.filename), Len("\biblio.mdb")) = "\BIBLIO.MDB" Then
                datPublishers.DatabaseName = dlgDialog.filename
                datPublishers.RecordSource = "SELECT DISTINCT state FROM Publishers"
                datPublishers.Refresh
            End If
            Resume Next
        Else
            Unload Me
        End If
    ElseIf Err <> 0 Then ' autre erreur
        MsgBox "Erreur non gérée: " & Err.Description
        End
    End If
    Resume Form_LoadExit
   
End Sub

Private Sub optComboBox_Click()
   '
   ' Bascule la visibilité des contrôles.
   '
   cboState.Visible = True
   lstState.Visible = False
   
End Sub

Private Sub optListBox_Click()
   '
   ' Bascule la visibilité des contrôles.
   '
   cboState.Visible = False
   lstState.Visible = True

End Sub


