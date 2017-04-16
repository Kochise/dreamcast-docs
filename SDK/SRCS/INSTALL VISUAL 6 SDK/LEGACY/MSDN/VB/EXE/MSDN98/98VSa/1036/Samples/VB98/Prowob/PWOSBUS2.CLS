VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SmallBusiness2"
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

' L'objet Collection de type Private est un
'   peu plus fiable qu'un objet Collection
'   de type Public mais il présente quelques
'   problèmes.
Private colEmployees As New Collection

' Problème 1: La collection est privée,
'   la méthode Add doit donc faire partie
'   de la classe SmallBusiness2. Étant donné
'   qu'il peut y avoir différents types
'   d'objets dans une procédure, il peut
'   exister autant de méthodes, telles que
'   AddProduct.
'
Public Function AddEmployee(ByVal Name As String, ByVal Salary As Double) As Employee
    Dim empNew As New Employee
    Static intEmpNum As Integer
    ' Utiliser l'instruction With raccourcit les références à la propriété (.ID au lieu de empNew.ID)
    ' et accélère l'exécution.
    With empNew
        ' Génère un ID unique pour le nouvel employé.
        intEmpNum = intEmpNum + 1
        .ID = "E" & Format$(intEmpNum, "00000")
        .Name = Name
        .Salary = Salary
        ' Ajoute la référence de l'objet Employee
        ' à la collection, en utilisant sa propriété
        ' ID comme clé.
        colEmployees.Add empNew, .ID
    End With
    ' La méthode AddEmployee doit renvoyer une référence
    '   au nouvel objet.
    Set AddEmployee = empNew
End Function

' Problème 1, la suite: Il existe également
'   des fonctions Count pour les autres
'   objets Business, des méthodes
'   Delete, etc. Rien qu'avec les objets
'   Employee, la classe SmallBusiness2
'   est déjà assez complexe.
'
Public Function EmployeeCount() As Long
    EmployeeCount = colEmployees.Count
End Function

Public Sub DeleteEmployee(ByVal Index As Variant)
    colEmployees.Remove Index
End Sub

' Problème 2: La méthode Employees
'   ne peut être utilisée avec l'instruction
'   For Each. Vous pouvez résoudre ce problème
'   en renvoyant une référence à la collection
'   privée, mais il ne s'agit plus dans ce cas
'   de collection privée; et on en revient à
'   la maison en paille.
'
Public Function Employees(ByVal Index As Variant) As Employee
    Set Employees = colEmployees.Item(Index)
End Function

' Problème 3: Il est toujours possible
'   pour les erreurs de code
'   d'ajouter des objets non valides à
'   la collection, en l'occurrence dans
'   l'objet SmallBusiness qui est très complexe.
Public Sub Trouble()
    Dim X As New Employee
    ' Étant donné que l'objet Collection
    '   accepte une référence à tous les objets,
    '   il est toujours possible, pour une
    '   erreur de codage interne, d'ajouter
    '   un objet Employee non initialisé.
    colEmployees.Add X
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
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


