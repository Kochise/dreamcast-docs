VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "TestClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs résultats. <<
'
' Stockage pour le numéro ID de débogage.
Private mlngDebugID As Long
Implements IDebug

' Stockage privé pour le type défini par
'   l'utilisateur (UDT) passé entre
'   les objets. Le type défini par l'utilisateur
'   est déclaré en tant que Public dans un
'   module standard (reportez-vous au module
'   modFriends). Dans cet exemple, mDemo
'   sert de stockage pour la propriété Demo,
'   ainsi que pour la combinaison
'   Fonction/Procédure de GetDemo/SetDemo.
Private mDemo As udtDEMO

' Propriété Demo: les propriétés Get et Let
' -------------     de la propriété Demo
'   montre la manière dont les procédures
'   de propriété déclarées au moyen du mot
'   clé Friend peuvent accepter et renvoyer
'   un type défini par l'utilisateur.
Friend Property Get Demo() As udtDEMO
    Demo = mDemo
End Property
' Vous remarquerez que l'argument de la propriété
'   Let doit être ByRef pour un type défini par
'   l'utilisateur.
Friend Property Let Demo(NewDemo As udtDEMO)
    mDemo = NewDemo
End Property

' Les propriétés GetDemo and SetDemo
' -------------------   montrent comment
'   les fonctions Friend peuvent renvoyer
'   des types définis par l'utilisateur,
'   et comment ces UDT peuvent être
'   des arguments des procédures Friend.
Friend Function GetDemo() As udtDEMO
    GetDemo = mDemo
End Function
' Vous remarquerez qu'un type défini par
'   l'utilisateur pour une procédure
'   doit être déclaré comme ByRef.
Friend Sub SetDemo(NewDemo As udtDEMO)
    mDemo = NewDemo
End Sub

' SetDemoParts est une méthode d'aide destinée
' ------------      à remplir les éléments
'   du type défini par l'utilisateur, pour
'   permettre leur passage. Dans une vraie
'   application, les éléments du type défini
'   par l'utilisateur devront être remplis
'   par code dans l'objet TestClass.
Public Sub SetDemoParts(ByVal A As Integer, _
        ByVal B As Long, ByVal C As String)
    mDemo.intA = A
    mDemo.lngB = B
    mDemo.strC = C
End Sub

' La méthode ShowDemo affiche les éléments du type
' --------      défini par l'utilisateur;
'   ils pourront ainsi être affichés après
'   le passage du type au deuxième objet.
Public Sub ShowDemo(ByVal Title As String, _
        ByVal Direction As String)
        
    MsgBox Direction & "  " _
        & GetDebugString(Me) & vbCrLf & vbCrLf _
        & mDemo.intA & vbCrLf _
        & mDemo.lngB & vbCrLf _
        & mDemo.strC, , Title
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

