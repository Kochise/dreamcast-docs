VERSION 5.00
Begin VB.Form frmStraw 
   Caption         =   "Collection Employees - La maison en paille"
   ClientHeight    =   3525
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   4995
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3525
   ScaleWidth      =   4995
   WhatsThisHelp   =   -1  'True
   Begin VB.CommandButton cmdTrouble 
      Caption         =   "&Erreur"
      Height          =   315
      Left            =   3150
      TabIndex        =   8
      Top             =   2370
      Width           =   1545
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
      Height          =   315
      Left            =   3150
      TabIndex        =   9
      Top             =   2790
      Width           =   1545
   End
   Begin VB.CommandButton cmdListEmployees 
      Caption         =   "&Rafraîchir la liste"
      Height          =   315
      Left            =   3150
      TabIndex        =   7
      Top             =   1950
      Width           =   1545
   End
   Begin VB.CommandButton cmdDeleteEmployee 
      Caption         =   "&Supprimer"
      Height          =   315
      Left            =   3150
      TabIndex        =   6
      Top             =   1530
      Width           =   1545
   End
   Begin VB.CommandButton cmdAddEmployee 
      Caption         =   "&Ajouter"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   345
      Left            =   3150
      TabIndex        =   5
      Top             =   1080
      Width           =   1545
   End
   Begin VB.ListBox lstEmployees 
      Height          =   1815
      Left            =   180
      Sorted          =   -1  'True
      TabIndex        =   4
      Top             =   1080
      Width           =   2715
   End
   Begin VB.TextBox txtSalary 
      Height          =   285
      Left            =   2700
      TabIndex        =   3
      Top             =   450
      Width           =   1995
   End
   Begin VB.TextBox txtName 
      Height          =   285
      Left            =   180
      TabIndex        =   1
      Top             =   450
      Width           =   2265
   End
   Begin VB.Label Label2 
      Caption         =   "Sa&laire"
      Height          =   195
      Left            =   2700
      TabIndex        =   2
      Top             =   180
      Width           =   2025
   End
   Begin VB.Label Label1 
      Caption         =   "&Nom"
      Height          =   195
      Left            =   180
      TabIndex        =   0
      Top             =   180
      Width           =   2265
   End
End
Attribute VB_Name = "frmStraw"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public sbMain As New SmallBusiness1

Private Sub cmdAddEmployee_Click()
    Dim empNew As New Employee
    If Not IsNumeric(txtSalary) Then
        MsgBox "Le salaire n'est pas un montant valide."
        '   Mettre le focus sur le champ Salaire
        '   et sélectionner tout le texte.
        With txtSalary
            .SetFocus
            .SelStart = 0
            .SelLength = Len(.Text)
        End With
        Exit Sub
    End If
    With empNew
        .ID = sbMain.NewEmployeeID
        .Name = txtName.Text
        .Salary = CDbl(txtSalary.Text)
        sbMain.Employees.Add empNew, .ID
        lstEmployees.AddItem .ID & ", " & .Name & ", " & .Salary
        With lstEmployees
            ' Sélectionne le dernier élément ajouté.
            .ListIndex = .NewIndex
        End With
    End With
    txtName.Text = ""
    txtSalary.Text = ""
    txtName.SetFocus
End Sub

Private Sub cmdClose_Click()
    Unload Me
End Sub

Private Sub cmdDeleteEmployee_Click()
    Dim lngDeletedItem As Long
    With lstEmployees
        lngDeletedItem = .ListIndex
        ' Vérifie qu'un employé a été sélectionné.
        If .ListIndex > -1 Then
            ' L'identificateur de l'employé correspond aux
            ' six premiers caractères de la ligne.
            sbMain.Employees.Remove Left(lstEmployees.Text, 6)
            ' Supprime l'élément sélectionné.
            .RemoveItem .ListIndex
            If .ListCount = 0 Then
                ' Si la liste est vide,
                '   ne fait pas de tentative pour
                '   définir une nouvelle sélection.
                Exit Sub
            End If
            ' L'élément effacé était-il en dernière position dans
            '   la zone de liste? Si oui, son index sera
            '   supérieur ou égal au nombre de la liste...
            If .ListCount <= lngDeletedItem Then
                '   ...définit donc la sélection courante
                '   sur le nouvel élément en fin de liste...
                .ListIndex = lngDeletedItem - 1
            Else
                '   ...sinon, conserve la sélection dans
                '   la même position physique dans
                '   la liste.
                .ListIndex = lngDeletedItem
            End If
        Else
            MsgBox "Aucun employé n'est sélectionné."
        End If
    End With
End Sub

Private Sub cmdListEmployees_Click()
    Dim emp As Employee
    With lstEmployees
        .Clear
        For Each emp In sbMain.Employees
            .AddItem emp.ID & ", " & emp.Name & ", " & emp.Salary
            ' Cliquer sur le bouton Rafraîchir la liste, après avoir
            '   appuyé sur le bouton Erreur, provoque une erreur de
            '   compatibilité de types (soit dans l'instruction
            '   For Each, si l'élément non valide est le premier
            '   de la liste, soit à l'instruction Next)
            '   lorsque Visual Basic essaie de placer la
            '   référence à frmStraw dans la variable d'itération
            '   emp. Pour continuer l'exécution, déplacez la
            '   flèche jaune d'exécution sur l'instruction End Sub
            '   (ou cliquez sur End Sub et appuyez sur Ctrl+F9),
            '   puis appuyez sur F5.
        Next
        ' Si vous vous arrêtez ici, reportez-vous à la note ci-dessus.
        '
        If .ListCount <> 0 Then
            ' Si plusieurs éléments existent dans la liste,
            '   sélectionne le premier.
            .ListIndex = 0
        End If
    End With
End Sub

Private Sub cmdTrouble_Click()
    ' Étant donné que la classe Collection accepte
    '   tous les objets, une erreur de codage peut
    '   placer un objet non valide dans la collection.
    sbMain.Employees.Add Me
    MsgBox "Une référence à la feuille d'entrée des données vient d'être ajoutée à la collection. Pour voir le problème, cliquez sur le bouton Rafraîchir la liste."
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Affectez la valeur Nothing à toutes les
    '   références à cette feuille, pour
    '   libérer ses ressources.
    '   Cela demande deux opérations:
    '   (1) Affectez la valeur Nothing à la
    '       variable globale cachée de la feuille:
    Set frmStraw = Nothing
    '   (2) Effacez l'objet de la collection,
    '       car le bouton Erreur place une
    '       référence à la feuille dans la
    '       collection, ce qui crée une référence
    '       circulaire (la variable sbMain
    '       a une référence à Employees, qui
    '       a une référence à la feuille, qui
    '       a une référence à la variable
    '       sbMain) qui maintient tous les
    '       objets en vie.
    Set sbMain.Employees = Nothing
    '
    ' Bien entendu, il s'agit d'un bogue qui
    '   peut détruire de la sorte la collection
    '   Employees de l'objet SmallBusiness;
    '   mais, après tout, la Maison en paille
    '   est une solution à NE PAS appliquer.
End Sub

Private Sub txtName_Change()
    Call EnableAddButton
End Sub

Private Sub txtSalary_Change()
    Call EnableAddButton
End Sub

Private Sub txtSalary_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 48 To 57   ' Autorise les chiffres.
        Case 8          ' Autorise les retours arrière.
        Case 46         ' Autorise les points.
        Case Else
            KeyAscii = 0
            Beep
    End Select
End Sub

Private Sub EnableAddButton()
    If (Len(txtName) > 0) And (Len(txtSalary) > 0) Then
        cmdAddEmployee.Enabled = True
    Else
        cmdAddEmployee.Enabled = False
    End If
End Sub
