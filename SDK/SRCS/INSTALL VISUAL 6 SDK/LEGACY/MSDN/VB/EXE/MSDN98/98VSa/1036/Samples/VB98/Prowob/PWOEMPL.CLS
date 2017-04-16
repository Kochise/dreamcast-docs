VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Employee"
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

' Propriétés de la classe Employee.
Public Name As String
Public Salary As Double

' Données privées pour la propriété ID définie une seule fois.
Private mstrID As String

Property Get ID() As String
    ID = mstrID
End Property
'
' La première fois que la propriété ID est
' définie, la variable statique de type Boolean est également
' définie. Les appels suivants ne font rien.
'(Il serait préférable de déclencher une erreur.)
Property Let ID(strNew As String)
    Static blnAlreadySet As Boolean
    If Not blnAlreadySet Then
        blnAlreadySet = True
        mstrID = strNew
    End If
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
'   déclarées dans le module modFriend.

Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


