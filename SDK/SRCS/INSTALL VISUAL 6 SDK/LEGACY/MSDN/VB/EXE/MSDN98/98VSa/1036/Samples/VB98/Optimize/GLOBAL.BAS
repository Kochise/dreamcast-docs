Attribute VB_Name = "Global"
Option Explicit
Public Const VBVer = "5.0"
Public Const LastAppUpdate = "9/4/96"

Public Const WM_SYSCOMMAND = &H112
Public Const SC_RESTORE = &HF120
Public Const SWP_NOMOVE = 2
Public Const SWP_NOSIZE = 1
Public Const FLAGS = SWP_NOMOVE Or SWP_NOSIZE
Public Const HWND_TOPMOST = -1
Public Const HWND_NOTOPMOST = -2

Public Const WM_SETREDRAW = &HB

' L'API de Windows appelle la création d'une fenêtre Topmost.

Declare Function SetWindowPos Lib "User32" (ByVal h&, ByVal hb&, ByVal x&, ByVal y&, ByVal cx&, ByVal cy&, ByVal f&) As Long
Declare Function FindWindow Lib "User32" (ByVal lpClassName As Any, ByVal lpWindowName As Any) As Long
Declare Function SendMessage Lib "User32" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long

Declare Function SetParent Lib "User32" (ByVal hWndChild As Long, ByVal hWndNewParent As Long) As Long

Type BookAuthor
    ID As Integer
    Name As String * 25
End Type

Dim arDemos(20) As String

Public Function SetRedraw(hWnd As Long, lState As Long) As Long
  
  Dim lRetVal As Long
  
  On Error GoTo SetRedraw_Error
  ' Définit iState = 0 pour désactiver la mise à jour automatique
  ' Définit iState = 1 pour activer la mise à jour automatique
  lRetVal = SendMessage(hWnd, WM_SETREDRAW, lState, 0)
  If lRetVal <> False Then GoTo SetRedraw_Error
  
  SetRedraw = True
  Exit Function
  
SetRedraw_Error:
  SetRedraw = lRetVal
  Exit Function
  
End Function

Public Function SetTopWindow(hWnd As Long, bState As Boolean) As Boolean
      
  If bState = True Then 'Place la fenêtre au premier plan
    SetTopWindow = SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, FLAGS)
  ElseIf bState = False Then ' Désactive l'indicateur TopMost
    SetTopWindow = SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, FLAGS)
  Else
    Debug.Print "bState inconnu."
    SetTopWindow = False
  End If
  
End Function

' Centre la feuille qui a été passée en paramêtre.
Sub CenterMe(frmForm As Form)
  frmForm.Left = (Screen.Width - frmForm.Width) / 2
  frmForm.Top = (Screen.Height - frmForm.Height) / 2
End Sub

Sub Main()
  Dim iCount As Integer
  Dim iLimit As Integer
  Dim tvwSample As TreeView
  Dim nodRoot As Node
  Dim nodX As Node
  Dim sLastParent As String
  Dim ilImages As ListImages
  Dim iNextParentImage As Integer
  
  Set tvwSample = frmExplore.tvExample
  Set ilImages = frmExplore.ilExplore.ListImages
  
  frmExplore.Show
  
  ' Affiche les catégories de vitesse.
  arDemos(0) = "Algorithmes"
  arDemos(1) = "Affiche la vitesse"
  arDemos(2) = "Dessine l'image"
  arDemos(3) = "Affiche la vitesse"
  arDemos(4) = "Graphiques"
  arDemos(5) = "Affiche la vitesse"
  
  ' Catégories des vitesses réelles.
  arDemos(6) = "Manipulation des chaînes"
  arDemos(7) = "Vitesse réelle"
  arDemos(8) = "Optimisations du code"
  arDemos(9) = "Vitesse réelle"
  arDemos(10) = "Types numériques"
  arDemos(11) = "Vitesse réelle"
  
  ' Catégories d'utilisation des ressources.
  arDemos(12) = "Contrôles Picture et Image"
  arDemos(13) = "Utilisation des ressources"
  arDemos(14) = "Suppression des objets de la feuille"
  arDemos(15) = "Utilisation des ressources"
  
  ' Catégories de vitesse apparente.
  arDemos(16) = "Écran de présentation"
  arDemos(17) = "Vitesse apparente"
    
  ' Catégories de collections
  arDemos(18) = "Collections"
  arDemos(19) = "Collections"
  
  Set nodRoot = tvwSample.Nodes.Add(, , "Root", "Optimisation des exemples")
  nodRoot.Image = 1
  iNextParentImage = 2
  ' Définit le premier type de démonstration.
  ' Crée un nouveau type de démonstration en dehors de la racine et
  ' transforme ce nœud en un enfant.
  iCount = 0
  sLastParent = arDemos(iCount + 1)
  Set nodX = tvwSample.Nodes.Add("Root", tvwChild, sLastParent, arDemos(iCount + 1))
  nodX.Image = iNextParentImage  ' Affiche la vitesse.
  iNextParentImage = iNextParentImage + 1
  ' Transforme ce nœud en un enfant pour le dernier type de démonstration.
  Set nodX = tvwSample.Nodes.Add(sLastParent, tvwChild, , arDemos(iCount))
  nodX.Image = 7
  iLimit = UBound(arDemos)
  For iCount = 2 To iLimit - 1 Step 2
    If arDemos(iCount + 1) <> arDemos(iCount - 1) Then
      nodX.EnsureVisible  ' Vérifie que tous les enfants sont visibles dans le dernier groupe.
      ' Crée un nouveau type de démonstration en dehors de la racine et transforme ce nœud en un enfant.
      sLastParent = arDemos(iCount + 1)
      Set nodX = tvwSample.Nodes.Add("Root", tvwChild, sLastParent, arDemos(iCount + 1))
      nodX.Image = iNextParentImage
      iNextParentImage = iNextParentImage + 1
    End If
    ' Transforme ce nœud en un enfant pour le dernier type de démonstration.
    Set nodX = tvwSample.Nodes.Add(sLastParent, tvwChild, , arDemos(iCount))
    nodX.Image = 7
  Next iCount
    
  nodX.EnsureVisible
  
  ' Supprime tous les objets que nous avons créés.
  Set nodX = Nothing
  Set nodRoot = Nothing
  Set ilImages = Nothing
  Set tvwSample = Nothing

End Sub

Sub PosForm(frmForm As Form)
  frmForm.Left = frmExplore.Left + frmExplore.Width
  frmForm.Top = frmExplore.Top
End Sub


