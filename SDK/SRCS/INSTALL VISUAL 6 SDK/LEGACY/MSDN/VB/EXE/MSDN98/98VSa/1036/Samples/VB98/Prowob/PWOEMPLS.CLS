VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Employees"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs résultats. <<
'
' Stockage pour le numéro ID de débogage.
Private mlngDebugID As Long
Implements IDebug

' Collection privé effectuant la totalité
'   du travail.
Private colEmployees As New Collection

' La méthode NewEnum rend possible l'utilisation de
' -------       l'instruction For Each avec la classe
'   de la collection Employees. Pour plus d'informations,
'   reportez-vous à la section "Création de votre propre classe
'   Collection : la maison en briques" des Manuels en ligne.
'
' Pour que la méthode NewEnum travaille correctement, son
'   identificateur de procédure doit être -4. Pour vérifier
'   cela, cliquez sur Attributs de Procédure
'   dans le menu Outils. Dans la zone Nom,
'   cliquez sur l'élément, puis sur le bouton
'   Avancés. Vous pouvez voir que l'identificateur
'   de procédure est -4. (L'option Masquer ce
'   membre est cochée également; la méthode
'   NewEnum est donc cachée dans l'Explorateur
'   d'objets.)
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
    ' Délègue vers la méthode _NewEnum de
    '   l'objet Collection privé.
    Set NewEnum = colEmployees.[_NewEnum]
End Function

' La méthode Add créé un nouvel employé
' ---       dans la collection.
'
Public Function Add(ByVal Name As String, _
                ByVal Salary As Double) As Employee
    Dim empNew As New Employee
    Static intEmpNum As Integer
    ' L'utilisation de With raccourcit les références à la propriété (.ID au lieu de empNew.ID)
    ' et accélère l'exécution.
    With empNew
        ' Génère un identificateur unique pour le nouvel employé.
        intEmpNum = intEmpNum + 1
        .ID = "E" & Format$(intEmpNum, "00000")
        .Name = Name
        .Salary = Salary
        ' Ajoute la référence de l'objet Employee à la collection,
        ' en utilisant sa propriété ID comme clé.
        colEmployees.Add empNew, .ID
    End With
    ' Renvoyer une référence du nouveau membre est une bonne solution.
    Set Add = empNew
End Function

' Pour vérifier comment la méthode Item est devenue
'   la méthode par défaut pour la collection Employees,
'   cliquez sur Attributs de Procédure
'   dans le menu Outils. Dans la zone Nom,
'   cliquez sur l'élément, puis sur le bouton
'   Avancés. Vous pouvez voir que (Défaut)
'   est sélectionné dans la zone ID
'   de procédure.
Public Function Item(ByVal Index As Variant) As Employee
    Set Item = colEmployees.Item(Index)
End Function

Public Function Count() As Long
    Count = colEmployees.Count
End Function

Public Sub Delete(ByVal Index As Variant)
    colEmployees.Remove Index
End Sub

Private Sub Class_Initialize()
    mlngDebugID = DebugInit(Me)
End Sub

Private Sub Class_Terminate()
    DebugTerm Me
End Sub

' -------- Implémentation de IDebug --------
'
' IDebug.DebugID permet de distinguer
' ====== -------    les différents objets. Il
'   est requis par les procédures de débogage
'   DebugInit, DebugTerm et DebugShow
'   déclarées dans le module modFriend.

Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


