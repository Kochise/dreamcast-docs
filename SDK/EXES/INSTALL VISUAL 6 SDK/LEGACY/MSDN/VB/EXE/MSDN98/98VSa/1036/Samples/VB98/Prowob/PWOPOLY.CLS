VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Polygon"
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

' La classe Polygon est une classe TRÈS
' -------       rudimentaire des objets Polygon.
'   Elle permet aux polygones d'être créés (avec
'   la méthode SetPoints); il n'existe aucun
'   moyen de modifier les points une fois définis
'   (sauf en rappelant la méthode SetPoints et en
'   redéfinissant tout le polygone).

Private Type POLYPOINT  ' préfixe pyp
    X As Single
    Y As Single
    Angle As Single
End Type

' Polygone par défaut à un point, aux coordonnées (0,0).
Private mapyp() As POLYPOINT

' Stockage pour la propriété Normalized en lecture seule.
Private mblnNormalized As Boolean

' Stockage pour la propriété Color.
Private mrgbColor As Long

' IShape est l'interface utilisée pour
' ------    l'affichage du polygone. Elle
'   dispose également d'une méthode TimeTest
'   utilisée pour comparer les dépréciations
'   de performance des appels aux liaisons
'   tardives et précoces.
Implements IShape

' -------------------------------------
' L'implémentation de l'interface IShape
'   démarre ici.

' La procédure IShape.DrawToPictureBox est
' ====== ----------------   appelée pour
'   dessiner une forme; chaque classe de
'   forme doit fournir sa propre implémentation.
'
Private Sub IShape_DrawToPictureBox(ByVal pb As PictureBox)
    Dim sngXLast As Single
    Dim sngYLast As Single
    Dim sngX As Single
    Dim sngY As Single
    Dim intMax As Integer
    Dim intCt As Integer
    
    intMax = UBound(mapyp)
    sngX = mapyp(intMax).X
    sngY = mapyp(intMax).Y
    If intMax = 0 Then
        pb.PSet (sngX, sngY), mrgbColor
    Else
        For intCt = 0 To intMax
            sngXLast = sngX
            sngYLast = sngY
            sngX = mapyp(intCt).X
            sngY = mapyp(intCt).Y
            pb.Line (sngXLast, sngYLast)-(sngX, sngY), mrgbColor
        Next
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

' --------------------------------------
' L'interface par défaut de la classe
'   Polygon (Propriétés et méthodes publiques)
'   démarre ici. Il s'agit de
'   l'interface Polygon que les objets
'   Triangle et Rectangle implémentent.

' Propriété Color.
' -----
'
Public Property Get Color() As Long
    Color = mrgbColor
End Property
'
Public Property Let Color(ByVal rgb As Long)
    If 0 <> (rgb And &HFF000000) Then
        Err.Raise vbObjectError + 2080, , _
            "Valeur de couleur non valide pour l'objet Polygon"
        Exit Property
    End If
    mrgbColor = rgb
End Property

' La méthode TimeTest ne prend pas d'arguments,
' --------      ne fait rien et effectue
'   immédiatement un renvoi. Elle est utilisée
'   pour montrer la dépréciation de performance
'   pour une liaison tardive, en opposition à
'   la liaison précoce fournie en appelant la
'   méthode TimeTest sur l'interface IShape.
'
' Vous pensez peut-être que nous aurions
'   dû faire de TimeTest une propriété
'   Friend, comme DebugID, pour enregistrer
'   les objets Triangle et Rectangle (qui
'   implémentent l'interface Polygon) depuis
'   l'implémentation de Polygon_TimeTest.
'   Les propriétés et les méthodes Friend
'   ne font PAS partie d'une interface de
'   classe. La raison pour laquelle nous
'   n'avons pas pu le faire est que TimeTest
'   doit être appelée, dans cet exemple, avec
'   une liaison TARDIVE, alors que les propriété
'   et les méthodes Friend doivent toujours
'   être appelées avec une liaison PRÉCOCE.
Public Sub TimeTest()
End Sub

' La méthode GetPoint affecte deux variables
' --------      ByRef de type Single aux
'   valeurs X et Y pour le point requis. Si
'   l'interface de l'objet Polygon n'a pas
'   été implémentée par les objets Triangle
'   et Rectangle, GetPoint peut être déclaré
'   comme Friend, et renvoyer une structure
'   POLYPOINT. Dans ce cas, elle serait
'   déclarée comme Public dans un module
'   standard; cependant, les membres Friend
'   ne font pas partie d'une interface de
'   la classe. Déclarer la méthode GetPoint
'   comme Friend empêcherait donc les objets
'   Triangle et Rectangle d'implémenter
'   l'instruction Polygon_GetPoint comme
'   liaison précoce.
'
Public Sub GetPoint(ByVal intPoint As Integer, _
        ByRef X As Single, ByRef Y As Single)
    X = mapyp(intPoint).X
    Y = mapyp(intPoint).Y
End Sub

' La propriété GetPointCount renvoie le nombre
' -------------     de points dans l'objet Polygon.
'
Public Property Get GetPointCount() As Integer
    GetPointCount = UBound(mapyp) + 1
End Property

' La méthode SetPoints accepte un tableau de
' ---------     données de type Single,
'   commençant à zéro. Les éléments
'   pairs (0, 2, etc.) correspondent aux
'   valeurs de X et les éléments impairs
'   aux valeurs de Y des points.
'
Public Sub SetPoints(asngPoints() As Single)
    Dim blnBadArray As Boolean
    Dim intMax As Integer
    Dim intPoint As Integer
    
    On Error Resume Next
    If LBound(asngPoints) <> 0 Then blnBadArray = True
    intMax = UBound(asngPoints)
    ' La limite supérieure d'un tableau commençant
    '   à zéro doit être un nombre impair; la valide.
    ' 
    If (intMax / 2#) = (intMax \ 2) Then blnBadArray = True
    ' Si une erreur se produit dans la fonction
    '   UBound, déclare le tableau comme invalide.
    If Err.Number <> 0 Then blnBadArray = True
    If blnBadArray Then
        Err.Raise vbObjectError + 2081, , _
            "La méthode SetPoints doit recevoir un tableau à une dimension commençant à zéro, avec un nombre impair d'éléments, les entrées paires correspondant aux valeurs de X et les entrées impaires aux valeurs de Y."
        Exit Sub
    End If
    ' Convertit l'index maximum du tableau des
    '   entrées en index maximum du tableau interne
    '   de l'objet Polygon.
    intMax = intMax \ 2
    ReDim mapyp(0 To intMax)
    ' Lit les valeurs du point.
    For intPoint = 0 To intMax
        mapyp(intPoint).X = asngPoints(intPoint * 2)
        mapyp(intPoint).Y = asngPoints(intPoint * 2 + 1)
    Next
End Sub

' --------------------------------------
' Les procédures privées de l'objet
'   Polygon (procédures d'aide et d'événement)
'   démarrent ici.

Private Sub Class_Initialize()
    ' Code de débogage.
    mlngDebugID = DebugInit(Me)
    '
    ' Objet Polygon par défaut affecté à un point.
    ReDim mapyp(0 To 0)
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

