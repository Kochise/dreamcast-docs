VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SmallBusiness3"
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

' La collection Employees de type Private
'   maintient les objets Employee.
Private emps As New Employees

' Plutôt que de déclarer une variable Employees
'   de type Public en tant que New Employees,
'   il est préférable de coder la procédure
'   pour obtenir une collection privée et
'   créer une propriété en lecture seule
'   pour renvoyer la collection Employees.
'   Ainsi, la collection ne peut être libérée
'   accidentellement en affectant la valeur
'   Nothing à la variable de type Public.
Public Property Get Employees() As Employees
    Set Employees = emps
End Property

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
'   déclarées dans module modFriend.
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


