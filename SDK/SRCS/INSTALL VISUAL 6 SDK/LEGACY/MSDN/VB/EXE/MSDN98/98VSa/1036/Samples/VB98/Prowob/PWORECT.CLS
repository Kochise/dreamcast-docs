VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Rectangle"
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

' L'objet Rectangle implémente deux interfaces;
'   il dispose également d'une propriété (Filled)
'   et d'une méthode (TimeTest) sur sa propre
'   interface.

Implements IShape
Implements Polygon

' L'objet Polygon interne détient en général
'   les données et fait une partie du travail.
'   L'objet Rectangle garde des références à
'   l'interface Polygon et IShape de l'objet
'   Polygon interne.
Private mpyg As Polygon
Private mish As IShape

' Stockage pour la propriété Color
'   (Implémentation de l'interface Polygon).
Private mrgbColor As Long

' Stockage pour la propriété Filled
'   (Sur l'interface par défaut de l'objet Rectangle).
Private mblnFilled As Boolean

' -------------------------------------
' L'implémentation de l'objet Rectangle
' de l'interface IShape démarre ici.

' La procédure IShape.DrawToPictureBox
' ------ ----------------   est appelée
'   pour dessiner une forme; chaque
'   classe de la forme doit donc fournir
'   sa propre implémentation.
'
Private Sub IShape_DrawToPictureBox(ByVal pb As PictureBox)
    ' Au lieu de déléguer à l'interface IShape
    '   de l'objet Polygon interne, l'objet
    '   Rectangle exploite la présence d'une
    '   commande de graphiques pour dessiner
    '   une boîte en une opération au lieu de
    '   quatre (les créations graphiques étant
    '   probablement le type d'opérations
    '   demandant le plus de temps).
    Dim sngX1 As Single, sngY1 As Single
    Dim sngX2 As Single, sngY2 As Single
    Call mpyg.GetPoint(0, sngX1, sngY1)
    Call mpyg.GetPoint(1, sngX2, sngY2)
    If mblnFilled Then
        pb.Line (sngX1, sngY1)-(sngX2, sngY2), mrgbColor, BF
    Else
        pb.Line (sngX1, sngY1)-(sngX2, sngY2), mrgbColor, B
    End If
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

' Polygon.Color - Étant donné que l'objet
' ======= -----     Polygon interne n'est pas
'   utilisé pour dessiner l'objet Rectangle,
'   la propriété Color est totalement écrasée.
'   Cela n'est pas requis; l'objet Rectangle
'   peut déléguer le stockage de la propriété
'   Color à l'objet Polygon interne (comme la
'   classe Triangle), en enregistrant le code
'   d'implémentation et l'espace de stockage.
'   La couleur peut ainsi être extraite de
'   l'objet Polygon interne une fois que le
'   dessin est réalisé.
Private Property Get Polygon_Color() As Long
    Polygon_Color = mrgbColor
End Property
'
Private Property Let Polygon_Color(ByVal RHS As Long)
    If 0 <> (RHS And &HFF000000) Then
        Err.Raise vbObjectError + 2080, , _
            "Valeur de couleur non valide pour l'objet Polygon."
        Exit Property
    End If
    mrgbColor = RHS
End Property

' Polygon.TimeTest - L'objet Rectangle dispose
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
    '   l'objet Rectangle est toujours
    '   défini par deux points.
    Polygon_GetPointCount = 2
End Property

' Polygon.SetPoints - Lors de l'implémentation
' ======= ---------     de la méthode SetPoints
'   de l'interface Polygon, l'objet Rectangle
'   exécute son propre code pour vérifier que
'   le tableau d'entrée contient uniquement
'   deux points (quatre Single), et délègue
'   ensuite à l'objet Polygon interne.
Private Sub Polygon_SetPoints(asngPoints() As Single)
    Dim blnBadArray As Boolean
    On Error Resume Next
    ' S'assure que le tableau d'entrée ne contient
    '   pas plus de quatre éléments. La méthode
    '   SetPoint de l'objet Polygon vérifie que
    '   le tableau commence à zéro.
    If UBound(asngPoints) <> 3 Then blnBadArray = True
    ' Si une erreur s'est produite lors de l'appel
    '   de la fonction UBound, le tableau est rejeté.
    If Err.Number <> 0 Then blnBadArray = True
    If blnBadArray Then
        Err.Raise vbObjectError + 2083, , _
            "Un rectangle est spécifié par un tableau de quatre nombres (gauche, haut, droite, bas) dans un tableau commençant à zéro."
        Exit Sub
    End If
    ' Délègue à l'objet Polygon interne, qui
    '   effectue la validation du tableau
    '   et le stocke.
    Call mpyg.SetPoints(asngPoints)
End Sub

' --------------------------------------
' La propre interface (par défaut) de
'   l'objet Rectangle démarre ici.

' La méthode TimeTest ne prend pas
' --------   d'arguments, et effectue
'   immédiatement un renvoi. Elle montre
'   une liaison tardive, en opposition à
'   la liaison précoce fournie en appelant
'   la méthode TimeTest sur l'interface
'   IShape.
Public Sub TimeTest()
End Sub

' La propriété Filled détermine si un
' ------    rectangle est rempli lors
'   du dessin.
Public Property Get Filled() As Boolean
    Filled = mblnFilled
End Property
'
Public Property Let Filled(ByVal NewValue As Boolean)
    mblnFilled = NewValue
End Property

' --------------------------------------
' Les procédures privées de la classe
'   (procédures d'aide et d'événement)
'   démarrent ici.

Private Sub Class_Initialize()
    Dim asngPoints(0 To 3) As Single
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

