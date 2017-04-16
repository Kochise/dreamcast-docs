VERSION 5.00
Begin VB.Form frmImplements 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Polymorphisme et mot clé Implements"
   ClientHeight    =   3510
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5310
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   2  'Custom
   Picture         =   "PWOImple.frx":0000
   ScaleHeight     =   3510
   ScaleWidth      =   5310
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrDisplay 
      Interval        =   220
      Left            =   1800
      Top             =   2760
   End
   Begin VB.PictureBox picShapes 
      BackColor       =   &H00FFFFFF&
      Height          =   1095
      Left            =   120
      Picture         =   "PWOImple.frx":0446
      ScaleHeight     =   1035
      ScaleWidth      =   1155
      TabIndex        =   2
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton cmdLate 
      Caption         =   "Liaison &tardive"
      Height          =   375
      Left            =   3600
      TabIndex        =   1
      Top             =   3030
      Width           =   1575
   End
   Begin VB.CommandButton cmdEarly 
      Caption         =   "Liaison &précoce"
      Height          =   375
      Left            =   3600
      TabIndex        =   0
      Top             =   2580
      Width           =   1575
   End
   Begin VB.Label lblLateResult 
      Height          =   255
      Left            =   1560
      TabIndex        =   6
      Top             =   3120
      Width           =   1935
   End
   Begin VB.Label lblEarlyResult 
      Height          =   255
      Left            =   1560
      TabIndex        =   5
      Top             =   2640
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "Dépréciation des performances d'un appel de méthode"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1380
      TabIndex        =   4
      Top             =   2010
      Width           =   3795
   End
   Begin VB.Label Label1 
      Caption         =   $"PWOImple.frx":088C
      Height          =   1875
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   5055
   End
End
Attribute VB_Name = "frmImplements"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Const NUMOBJECTS = 100
Const NUMREPEATSEARLY As Long = 10000
Const NUMREPEATSLATE As Long = 500

' Pour la démonstration, trois tableaux
'   de références à un objet sont conservés.
'   Chaque objet créé par l'exemple possède
'   une entrée dans les trois tableaux:
' Tableau des interfaces IShape;
Private maishEarly(1 To NUMOBJECTS) As IShape
' Tableau des interfaces Polygon;
Private mapyg(1 To NUMOBJECTS) As Polygon
' Tableau des interfaces par défaut (Polygon,
'   Triangle ou Rectangle, selon
'   l'objet).
Private maobjLate(1 To NUMOBJECTS) As Object

' Le test d'heure pour la liaison précoce
'   appelle chaque liaison précoce des
'   objets NUMOBJECTS, au moyen de
'   l'interface IShape. La méthode
'   TimeTest se situe tout au dessus: elle
'   ne prend pas d'arguments et effectue
'   immédiatement le renvoi. L'opération
'   est répétée pour toutes les instances
'   de NUMREPEATSEARLY.
'
Private Sub cmdEarly_Click()
    Dim lngCt As Long
    Dim intCt As Integer
    Dim timeMark As Long
    
    ' Désactive l'affichage des formes
    '   pendant le test.
    tmrDisplay.Enabled = False
    cmdEarly.Caption = "En cours..."
    timeMark = timeGetTime
    For lngCt = 1 To NUMREPEATSEARLY
        For intCt = 1 To NUMOBJECTS
            ' Effectue les appels à la méthode
            '   TimeTest au moyen de l'interface
            '   IShape, avec l'implémentation
            '   des trois classes (Polygon,
            '   Rectangle et Triangle).
            maishEarly(intCt).TimeTest
        Next
    Next
    timeMark = timeGetTime - timeMark
    lblEarlyResult = ShowElapsed(timeMark, _
        NUMOBJECTS * NUMREPEATSEARLY, _
        "Dépréciation des performances d'un appel à une liaison précoce")
    cmdEarly.Caption = "Liaison &précoce"
    '
    ' Rétablit l'affichage des formes.
    tmrDisplay.Enabled = True
End Sub

Private Sub cmdLate_Click()
    Dim lngCt As Long
    Dim intCt As Integer
    Dim timeMark As Long
    
    ' Désactive l'affichage des formes
    '   pendant le test.
    tmrDisplay.Enabled = False
    cmdLate.Caption = "En cours..."
    timeMark = timeGetTime
    For lngCt = 1 To NUMREPEATSLATE
        For intCt = 1 To NUMOBJECTS
            ' Effectue les appels à la liaison
            '   tardive de la méthode TimeTest,
            '   au moyen des interfaces par défaut
            '   des objets (Polygon, Rectangle
            '   et Triangle).
            maobjLate(intCt).TimeTest
        Next
    Next
    timeMark = timeGetTime - timeMark
    lblLateResult = ShowElapsed(timeMark, _
        NUMOBJECTS * NUMREPEATSLATE, _
        "Dépréciation des performances d'un appel à une liaison tardive")
    cmdLate.Caption = "Liaison &tardive"
    '
    ' Rétablit l'affichage des formes.
    tmrDisplay.Enabled = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Libère les ressources associées à
    '   la feuille, en effaçant la variable
    '   globale cachée.
    Set frmImplements = Nothing
End Sub

' Si la zone d'image de l'affichage des
'   formes est cliquée, affiche toutes
'   les formes en même temps (en utilisant
'   une liaison précoce).
Private Sub picShapes_Click()
    Dim intCt As Integer
    For intCt = 1 To NUMOBJECTS
        Call maishEarly(intCt).DrawToPictureBox(picShapes)
    Next
End Sub

Private Sub Form_Load()
    Dim intCt As Integer
    Dim asngPoints() As Single
    Set Picture = New StdPicture
    Call Randomize(Timer)
    For intCt = 1 To NUMOBJECTS
        ' Crée de manière aléatoire 1/3 de polygones,
        '   1/3 de triangles et 1/3 de rectangles.
        '   Stocke la référence à chacun de ces
        '   objets dans le tableau de liaison tardive.
        Select Case Int(Rnd * 3)
            Case 0
                Set maobjLate(intCt) = New Polygon
            Case 1
                Set maobjLate(intCt) = New Triangle
            Case 2
                Set maobjLate(intCt) = New Rectangle
        End Select
        ' Enregistre une référence à l'interface
        '   IShape de l'objet pour illustrer une
        '   liaison précoce utilisant le polymorphisme.
        '   Chacune des trois classes implémente
        '   l'interface IShape; Visual Basic est
        '   donc capable de demander l'interface
        '   IShape et de réaliser l'affectation.
        Set maishEarly(intCt) = maobjLate(intCt)
        ' Enregistre également une référence à
        '   l'interface de l'objet Polygon.
        Set mapyg(intCt) = maobjLate(intCt)
        ' S'il s'agit d'un objet Polygon (plutôt
        '   que de Triangle ou de Rectangle, qui
        '   implémentent simplement l'interface
        '   Polygon), celui-ci sera d'un seul
        '   point. Attribuez-lui un nombre
        '   aléatoire de points (entre 4 et 24).
        If mapyg(intCt).GetPointCount = 1 Then
            ReDim asngPoints(0 To (Int(21 * Rnd) + 4) * 2 - 1)
            Call mapyg(intCt).SetPoints(asngPoints)
        End If
        ' Affecte à l'objet une couleur aléatoire.
        mapyg(intCt).Color = Int(Rnd * &HFFFFFF)
    Next
    Debug.Print "En retournant en arrière et en regardant les "
    Debug.Print "nombres du débogage des objets Shape, "
    Debug.Print "vous remarquerez qu'un nombre d'objets "
    Debug.Print "supérieur à " & NUMOBJECTS & " a été créé. "
    Debug.Print "Cela est dû au fait que chaque objet Triangle "
    Debug.Print "et Rectangle créé un objet Polygon."
    '
    ' Affecte des valeurs aléatoires
    '   à chaque point dans chaque objet.
    Call NewShapes
End Sub

Private Sub tmrDisplay_Timer()
    ' Effectue une itération de manière répétitive
    '   à travers les objets Shape, en les
    '   affichant dans un contrôle PictureBox.
    Static intCt As Integer
    picShapes.Cls
    intCt = intCt + 1
    If intCt > NUMOBJECTS Then intCt = 1
    Call maishEarly(intCt).DrawToPictureBox(picShapes)
End Sub

' La procédure d'aide ShowElapsed affiche
' -----------       le résultat d'un test
'   d'heure d'une liaison précoce ou tardive.
'
Private Function ShowElapsed(ByVal Milliseconds As Long, _
        ByVal Iterations As Long, _
        ByVal Caption As String) As String
    Dim strMSec As String
    strMSec = Format$(Milliseconds / Iterations, "0.0000")
    
    MsgBox Format$(Iterations, "#,###,##0") _
        & " itérations en " _
        & Format$(Milliseconds / 1000#, "##,##0.00") _
        & " secondes" & vbCrLf _
        & strMSec _
        & " millisecondes par appel", , Caption
        
    ShowElapsed = strMSec & " msec/appel"
End Function

' Le procédure NewShapes modifie la forme
' ---------     de chaque objet, en appelant
'   la procédure MakeRandomPoints pour
'   générer un jeu de points aléatoires.
'   Cela ne change pas le nombre de points
'   d'un objet Polygon.
'
Private Sub NewShapes()
    Dim intCt As Integer
    Dim intPt As Integer
    Dim pyg As Polygon
    Dim asngPoints() As Single
    Dim intNumPts As Integer
    
    For intCt = 1 To NUMOBJECTS
        intNumPts = mapyg(intCt).GetPointCount
        Call MakeRandomPoints(intNumPts, asngPoints)
        Call mapyg(intCt).SetPoints(asngPoints)
    Next
End Sub

' La procédure MakeRandomPoints crée un jeu
' ----------------      de points aléatoires
'   pour un objet Polygon, en les plaçant dans
'   un tableau à une dimension et débutant à
'   zéro, requis par la méthode SetPoints.
'
Private Sub MakeRandomPoints( _
        ByVal intNumPts As Integer, _
        asngPoints() As Single)
        
    Dim intPt As Integer
    
    ReDim asngPoints(0 To intNumPts * 2 - 1)
    For intPt = 0 To intNumPts * 2 - 1 Step 2
        asngPoints(intPt) = Rnd * picShapes.ScaleWidth
        asngPoints(intPt + 1) = Rnd * picShapes.ScaleHeight
    Next
End Sub

