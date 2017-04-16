VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Triangle"
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

' La classe Triangle implémente l'interface
'   IShape et Polygon. Un objet Polygon
'   interne est maintenu et de nombreuses
'   activités sont déléguées (dessin,
'   stockage des points, etc). La propre
'   interface de la classe Triangle n'a
'   qu'une méthode.

Implements IShape
Implements Polygon

' L'objet Polygon interne maintient
'   les données et fait une grande
'   partie des opérations. L'objet
'   Triangle garde des références pour
'   les deux interfaces Polygon et IShape
'   de l'objet Polygon interne.
Private mpyg As Polygon
Private mish As IShape

' -------------------------------------
' L'implémentation de l'interface IShape
'   démarre ici.

' La procédure IShape.DrawToPictureBox
' ------ ----------------   est appelée pour
'   dessiner une forme; chaque classe de
'   forme doit donc fournir sa propre
'   implémentation.
'
Private Sub IShape_DrawToPictureBox(ByVal pb As PictureBox)
    ' Délègue à l'interface IShape de
    '   l'objet Polygon interne.
    Call mish.DrawToPictureBox(pb)
End Sub

' La méthode IShape.TimeTest est utilisée
' ====== --------       pour afficher la
'   dépréciation réduite de performances
'   de l'appel d'une méthode appelée sur
'   une interface qui implémente plusieurs
'   classes, en opposition à l'appel
'   d'une méthode semblable sur les interfaces
'   par défaut des classes.
'
Private Sub IShape_TimeTest()
End Sub

' -------------------------------------
' L'implémentation de l'interface Polygon
'   démarre ici.

' Polygon.Color délègue à l'objet
' ======= -----     Polygon interne.
'
Private Property Get Polygon_Color() As Long
    Polygon_Color = mpyg.Color
End Property
'
Private Property Let Polygon_Color(ByVal RHS As Long)
    mpyg.Color = RHS
End Property

' Polygon.TimeTest - L'objet Triangle dispose
' ======= --------  de trois méthodes TimeTest:
'   une sur l'interface IShape (pour afficher
'   le polymorphisme et les liaisons précoces),
'   une sur sa propre interface (pour afficher
'   les liaisons tardives) et celle-ci qui est
'   le résultat de l'implémentation de l'interface
'   Polygon par l'objet Rectangle; elle n'est pas
'   utilisée du tout.
Private Sub Polygon_TimeTest()
End Sub

' Polygon.GetPoint
' ======= --------
'
Private Sub Polygon_GetPoint(ByVal intPoint As Integer, X As Single, Y As Single)
    ' Délègue à l'objet Polygon interne.
    Call mpyg.GetPoint(intPoint, X, Y)
End Sub

' Polygon.GetPointCount
' ======= -------------
'
Private Property Get Polygon_GetPointCount() As Integer
    ' Il n'y a pas de point lors de la
    '   délégation à l'objet Polygon interne:
    '   un triangle est toujours
    '   défini par trois points.
Polygon_GetPointCount = 3
End Property

' Polygon.SetPoints - Lors de l'implémentation
' ======= ---------     de la méthode SetPoints
'   de l'interface Polygon, l'objet Triangle
'   exécute son propre code pour vérifier que
'   le tableau d'entrée contient uniquement
'   trois points (six Single), et délègue
'   ensuite à l'objet Polygon interne.
Private Sub Polygon_SetPoints(asngPoints() As Single)
    Dim blnBadArray As Boolean
    On Error Resume Next
    If UBound(asngPoints) <> 5 Then blnBadArray = True
    If Err.Number <> 0 Then blnBadArray = True
    If blnBadArray Then
        Err.Raise vbObjectError + 2082, , _
            " Un triangle est spécifié par un tableau commençant à zéro avec six éléments, les valeurs paires (0 y compris) correspondant aux valeurs X et les valeurs impaires aux valeurs Y."
        Exit Sub
    End If
    ' Délègue à l'objet Polygon interne, qui
    '   effectue la validation du tableau
    '   et le stocke.
    Call mpyg.SetPoints(asngPoints)
End Sub

' --------------------------------------
' La propre interface (par défaut) de
'   l'objet Triangle démarre ici.

' La méthode TimeTest ne prend pas
' --------   d'arguments, ne fait rien
'   et effectue immédiatement un renvoi.
'   Elle montre une liaison tardive, en
'   opposition à la liaison précoce
'   fournie en appelant la méthode
'   TimeTest sur l'interface IShape.
Public Sub TimeTest()
End Sub

' --------------------------------------
' Les procédures privées de la classe
'   Triangle (procédure d'aide et
'   procédure d'événement) démarrent ici.

Private Sub Class_Initialize()
    Dim asngPoints(0 To 5) As Single
    ' Code de débogage.
    mlngDebugID = DebugInit(Me)
    '
    ' Crée l'objet Polygon interne, et
    '   obtient une référence à son
    '   interface IShape.
    Set mpyg = New Polygon
    Set mish = mpyg
    ' Initialise l'objet Polygon interne.
    Call mpyg.SetPoints(asngPoints)
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


