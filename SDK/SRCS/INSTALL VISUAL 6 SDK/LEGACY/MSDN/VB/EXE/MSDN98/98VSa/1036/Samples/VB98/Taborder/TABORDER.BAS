Attribute VB_Name = "modMain"
Option Explicit


Private Declare Sub PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd&, ByVal msg&, ByVal wp&, ByVal lp&)
Private Declare Sub SetFocus Lib "user32" (ByVal hwnd&)
Private Declare Function GetParent Lib "user32" (ByVal hwnd&) As Long
Const WM_SYSKEYDOWN = &H104
Const WM_SYSKEYUP = &H105
Const WM_SYSCHAR = &H106
Const VK_F = 70  ' les constantes VK_A à VK_Z sont identiques à leurs codes ASCII respectifs: 'A' à 'Z'.
Dim hwndMenu       As Long           ' Requis pour passer les touches de menu à VB.

Global gVBInstance  As VBIDE.VBE       ' Instance de l'interface de développement VB .
Global gwinWindow   As VBIDE.Window    ' Utilisée pour vérifier que l'on exécute une instance.
Global gdocTabOrder As Object          ' Objet document de l'utilisateur.


Global Const APP_CATEGORY = "Compléments Microsoft Visual Basic"

Function InRunMode(VBInst As VBIDE.VBE) As Boolean
  InRunMode = (VBInst.CommandBars("File").Controls(1).Enabled = False)
End Function

Sub HandleKeyDown(ud As Object, KeyCode As Integer, Shift As Integer)
  If Shift <> 4 Then Exit Sub
  If KeyCode < 65 Or KeyCode > 90 Then Exit Sub
  If gVBInstance.DisplayModel = vbext_dm_SDI Then Exit Sub
  
  If hwndMenu = 0 Then hwndMenu = FindHwndMenu(ud.hwnd)
  PostMessage hwndMenu, WM_SYSKEYDOWN, KeyCode, &H20000000
  KeyCode = 0
  SetFocus hwndMenu
End Sub

Function FindHwndMenu&(ByVal hwnd&)
  Dim h As Long
  
Loop2:
  h = GetParent(hwnd)
  If h = 0 Then FindHwndMenu = hwnd: Exit Function
  hwnd = h
  GoTo Loop2
End Function

