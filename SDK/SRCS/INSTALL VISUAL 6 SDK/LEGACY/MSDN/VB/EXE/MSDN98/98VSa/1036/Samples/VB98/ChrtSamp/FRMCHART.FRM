VERSION 5.00
Object = "{65E121D4-0C60-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmChart 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Microsoft Chart Sample"
   ClientHeight    =   7050
   ClientLeft      =   1095
   ClientTop       =   1995
   ClientWidth     =   10560
   Icon            =   "frmChart.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7050
   ScaleWidth      =   10560
   ShowInTaskbar   =   0   'False
   Begin MSComDlg.CommonDialog dlgChart 
      Left            =   10080
      Top             =   360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComCtlLib.ProgressBar prgArrays 
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   0
      Visible         =   0   'False
      Width           =   10455
      _ExtentX        =   18441
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.ComboBox cmbRows 
      Height          =   315
      Left            =   1320
      TabIndex        =   8
      Top             =   840
      Width           =   975
   End
   Begin VB.CommandButton cmdPPGandTotalGallons 
      Caption         =   "Litres/réservoir, Prix/litre, && prix total/réservoir"
      Height          =   855
      Left            =   360
      TabIndex        =   1
      Top             =   2640
      Width           =   1695
   End
   Begin VB.CommandButton cmdGalAndMPG 
      Caption         =   "Litres && L/Km"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   2280
      Width           =   1695
   End
   Begin VB.CommandButton cmdPricePerTank 
      Caption         =   "Prix/réservoir"
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   6120
      Width           =   1695
   End
   Begin VB.ComboBox cmbType 
      Height          =   315
      Left            =   1320
      TabIndex        =   7
      Top             =   360
      Width           =   975
   End
   Begin VB.CommandButton cmdPrices 
      Caption         =   "Prix/Litre"
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   5760
      Width           =   1695
   End
   Begin VB.CommandButton cmdGallons 
      Caption         =   "Litres/réservoir"
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   5400
      Width           =   1695
   End
   Begin VB.CommandButton cmdMiles 
      Caption         =   "Kilomètres/réservoir"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   5040
      Width           =   1695
   End
   Begin VB.CommandButton cmdMPG 
      Caption         =   "Kilomètres/litre"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   4680
      Width           =   1695
   End
   Begin MSChart20Lib.MSChart chtSample 
      Height          =   6015
      Left            =   2520
      OleObjectBlob   =   "frmChart.frx":0442
      TabIndex        =   9
      Top             =   960
      Width           =   7815
   End
   Begin VB.Label lblDataPoint 
      Caption         =   "Sélectionnez un point du graphique pour afficher sa valeur. Double-cliquez pour le modifier."
      Height          =   615
      Left            =   3120
      TabIndex        =   15
      Top             =   360
      Width           =   6735
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label4 
      Caption         =   "Graphiques de combinaison"
      Height          =   495
      Left            =   360
      TabIndex        =   13
      Top             =   1560
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "# de lignes à afficher"
      Height          =   375
      Left            =   120
      TabIndex        =   12
      Top             =   840
      Width           =   1095
   End
   Begin VB.Shape Shape2 
      Height          =   2175
      Left            =   120
      Top             =   1440
      Width           =   2175
   End
   Begin VB.Label Label2 
      Caption         =   "Graphiques de série de données uniques "
      Height          =   495
      Left            =   360
      TabIndex        =   11
      Top             =   4200
      Width           =   1695
   End
   Begin VB.Shape Shape1 
      Height          =   2535
      Left            =   120
      Top             =   4080
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   "Type de graphique"
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   360
      Width           =   1215
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuExit 
         Caption         =   "&Quitter"
      End
   End
End
Attribute VB_Name = "frmChart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ------------------------------------------------------------------------
'      Copyright © 1998 Microsoft Corporation.  Tous droits réservés.
'
' Vous disposez d'un droit accordé à titre gratuit d'utiliser, modifier, reproduire et distribuer,
' de quelque manière que ce soit, des extraits de Fichiers d'Applications Exemples. Vous reconnaissez être informé et vous  acceptez que Microsoft exclut toute garantie, obligation ou responsabilité relatives à
' l'exercice du droit gratuit qui vous est accordé ci-dessus.
' ------------------------------------------------------------------------

Option Explicit
Private cmdLastClicked As CommandButton ' Stocke le dernier bouton de commande utilisé.
Private Const cdlHelpTopics = &HB 'La constante Help qui manque dans
                                  'la bibliothèque de type Common Dialog.

Private Sub chtSample_LostFocus()
    lblDataPoint.Caption = "Selectionnez un point pour visualiser sa valeur. Double-cliquez pour la modifier."
End Sub

Private Sub chtSample_PointActivated(Series As Integer, DataPoint As Integer, MouseFlags As Integer, Cancel As Integer)
    Dim vtPoint
    With chtSample
        .Column = Series
        .Row = DataPoint
        vtPoint = InputBox("Modifiez le point de données :", , .Data)
        If vtPoint <> "" Then
            If IsNumeric(vtPoint) Then
                .Data = vtPoint
            Else
                MsgBox "Ce n'est pas un point de données valide!"
            End If
        End If
    End With
    
End Sub

Private Sub chtSample_PointSelected(Series As Integer, DataPoint As Integer, MouseFlags As Integer, Cancel As Integer)
    ' Ceci permet à l'utilisateur de visualiser la valeur d'un point de données dans une
    '   série en sélectionant celle-ci. La valeur du point de données est affiché dans l'étiquette
    '   nommée lblDatapoint.
    chtSample.Column = Series
    chtSample.Row = DataPoint
    lblDataPoint.Caption = "Valeur des séries " & Series & ", point " & DataPoint & " = " & chtSample.Data
End Sub

Private Sub cmbType_LostFocus()
    lblDataPoint.Caption = "Sélectionnez un point pour visualiser sa valeur"
End Sub

Private Sub Form_Load()
    Me.Show
    SetupChart          ' Configure le graphique.
    
    
    ' Configure le contrôle combobox avec des types de graphique.
    With cmbType
        .AddItem "3dBar"    ' 0
        .AddItem "2dBar"    ' 1
        .AddItem "3dLine"   ' 2
        .AddItem "2dLine"   ' 3
        .AddItem "3dArea"   ' 4
        .AddItem "2dArea"   ' 5
        .AddItem "3dStep"   ' 6
        .AddItem "2dStep"   ' 7
        .AddItem "3dCombination"    ' 8
        .AddItem "2dCombination"    ' 9
        .AddItem "2dPie"    ' 14
        .AddItem "2dXY"     ' 16
        .ListIndex = 3
    End With
    
    ' Le contrôle combobox cmbRows affiche le nombre de lignes dans le graphique.
    '   Par défaut, il affiche toutes les lignes. Mais si vous ne souhaitez
    '   visualiser que quelques lignes, cliquez simplement sur le contrôle
    '   combobox et sélectionnez les lignes que vous souhaitez afficher dans le graphique.
    Dim i As Integer
    For i = 5 To intRows
        cmbRows.AddItem i
    Next i
    cmbRows.ListIndex = intRows - 5
    
    threeColChart    ' Affiche un graphique de combinaison.
    ' La variable cmdLastClicked contient le dernier bouton de commande utilisé.
    '   Cette information est utilisée à chaque fois que le nombre de lignes affichées (à l'aide du contrôle
    '   cmbRows) est modifié. Une fois les lignes modifiées, le dernier bouton référencé
    '   dans la variable est sélectioné afin de remplir le graphique.
    Set cmdLastClicked = cmdPPGandTotalGallons
End Sub


Private Sub cmbRows_Click()
    ' Cependant, si l'utilisateur ne souhaitait effectuer aucune modification, il n'aura pas besoin
    ' d'exécuter le reste du code.
    Static intCount As Integer
    If intCount > 0 And intRows = cmbRows.Text Then Exit Sub
    intCount = intCount + 1
    
    ' Lorsque ce contrôle combobox est sélectionné, la variable publique intRows prend la valeur
    '   du contrôle combobox. Le code affiche ensuite le contrôle progressbar qui est utilisé
    '   pour donner des informations sur la progression des données du tableau. Le code appelle ensuite
    '   la procédure MakeArrays, qui remplit les tableaux à l'aide des nouvelles
    '   valeurs intRows. Une fois les tableaux remplis, le contrôle progressbar est à nouveau masqué,
    '   puis la variable cmdLastClicked, qui contient le dernier bouton sélectionné,
    '   est réactivée.
    intRows = cmbRows.Text
    With prgArrays ' Affiche le contrôle ProgressBar pendant le remplissage des tableaux, ce qui peut
                   '  demander plusieurs secondes.
        .Max = intRows
        .Visible = True
    End With
    
    ' Remplit les tableaux avec les valeurs de la feuille de calcul utilisant les fonctions utilisateur.
    '   Ces tableaux seront ensuite utilisés quand l'utilisateur clique sur un des boutons
    '   du formulaire.
    PopOneArray arrMiles, "B"
    PopOneArray arrMPG, "E"
    PopOneArray arrGall, "C"
    PopOneArray arrPrices, "D"
    PopOneArray arrPerTank, "H"
    PopTwoArray arrMPGandTank, "C", "E"
    PopThreeArray arrMPGandMiles, "D", "C", "H"

    prgArrays.Visible = False ' Masque le contrôle Progressbar, une fois l'opération terminée.
    
    ' Si la variable cmdLastClicked contient un bouton, cliquez sur celui-ci. Le même graphique est alors retracé
    '   avec le nouveau tableau.
    If Not cmdLastClicked Is Nothing Then cmdLastClicked.Value = True
    
End Sub


Private Sub cmbType_Click()
    Select Case cmbType.ListIndex
    Case 0 To 9
        chtSample.chartType = cmbType.ListIndex
    Case 10
        chtSample.chartType = VtChChartType2dPie
    Case 11
        chtSample.chartType = VtChChartType2dXY
    End Select
    If chtSample.Chart3d = True Then
        lblDataPoint.Caption = "Maintenez la touche Ctrl enfoncée et déplacez le curseur vers le bas pour faire pivoter le graphique."
    End If
End Sub

Private Sub cmdGalAndMPG_Click()
        ' Affiche un graphique de combinaison.
    twoColChart
    Set cmdLastClicked = cmdGalAndMPG
End Sub

Private Sub cmdGallons_Click()
    Chart arrGall, "Litres/réservoir", "Litre" ' Affiche le nombre de litres.
    Set cmdLastClicked = cmdGallons
End Sub

Private Sub cmdMiles_Click()
    Chart arrMiles, "Kilomètres/réservoir", "Kilomètres/réservoir"
    Set cmdLastClicked = cmdMiles
End Sub

Private Sub cmdMPG_Click()
    ' Le tableau publique Km/Litre a été lors de la procédure SetupChart.
    ' Km/Litre
    Chart arrMPG, "Kilomètres/Litre", "Kilomètres/Litre"
    Set cmdLastClicked = cmdMPG
End Sub

Private Sub cmdPPGandTotalGallons_Click()
    threeColChart
    Set cmdLastClicked = cmdPPGandTotalGallons
End Sub

Private Sub cmdPricePerTank_Click()
    Chart arrPerTank, "Prix/réservoir", "Prix/réservoir"
    Set cmdLastClicked = cmdPricePerTank
End Sub

Private Sub cmdPrices_Click()
    Chart arrPrices, "Prix/Litre", "Prix/Litre"
    Set cmdLastClicked = cmdPrices
End Sub


Private Sub Form_Terminate()
    ' Cette procédure définit toutes les variables d'objet sur Nothing.
    Cleanup
End Sub

Private Sub mnuContents_Click()
    With dlgChart
        .HelpFile = App.Path & "\MSChart.hlp"
        .HelpCommand = cdlHelpTopics
        .ShowHelp
    End With
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub
