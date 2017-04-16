VERSION 5.00
Begin VB.Form frmBricks 
   Caption         =   "Collection Employees - La maison en briques"
   ClientHeight    =   3525
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   4995
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3525
   ScaleWidth      =   4995
   Begin VB.CommandButton cmdTrouble 
      Caption         =   "&Erreur"
      Enabled         =   0   'False
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
Attribute VB_Name = "frmBricks"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public sbMain As New SmallBusiness3

Private Sub cmdAddEmployee_Click()
    Dim empNew As Employee
    If Not IsNumeric(txtSalary) Then
        MsgBox "Le salaire n'est pas un montant valide."
        With txtSalary
            .SetFocus
            .SelStart = 0
            .SelLength = Len(.Text)
        End With
        Exit Sub
    End If
    ' Le nouvel employé peut uniquement être créé
    '   en appelant la méthode Add de la
    '   collection Employees.
    Set empNew = sbMain.Employees.Add(txtName.Text, CDbl(txtSalary.Text))
    ' Ajoute un nouvel employé à la zone de liste.
    With empNew
        lstEmployees.AddItem .ID & ", " & .Name & ", " & .Salary
    End With
    With lstEmployees
        ' Sélectionne le dernier élément ajouté.
        .ListIndex = .NewIndex
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
            sbMain.Employees.Delete Left(.Text, 6)
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
            With emp
                lstEmployees.AddItem .ID & ", " & .Name & ", " & .Salary
            End With
        Next
        If .ListCount <> 0 Then
            ' Si plusieurs éléments existent dans la liste,
            '   sélectionne le premier.
            .ListIndex = 0
        End If
    End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Affecte la valeur Nothing à la variable globale
    '   cachée de cette feuille, pour libérer
    '   ses ressources.
    Set frmBricks = Nothing
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

