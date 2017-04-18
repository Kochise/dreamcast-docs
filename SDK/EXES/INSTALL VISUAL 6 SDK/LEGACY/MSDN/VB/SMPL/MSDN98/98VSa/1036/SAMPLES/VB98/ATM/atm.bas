Attribute VB_Name = "modATM"
Option Explicit

' Variable de déplacement.
Public i As Long

' Table de conversion des monnaies depuis le franc français.
Public ConversionTable As Variant

' API de support du son de haut niveau.
    Declare Function sndPlaySound Lib "WINMM.DLL" Alias "sndPlaySoundA" _
        (lpszSoundName As Any, ByVal uFlags As Long) As Long

Global Const SND_ASYNC = &H1     ' Jouer de façon asynchrone.
Global Const SND_NODEFAULT = &H2 ' Ne pas utiliser le son par défaut.
Global Const SND_MEMORY = &H4    ' lpszSoundName pointe vers un fichier en mémoire.

Global SoundBuffer() As Byte

' Pointeur de souris sur les boutons de commande.
Dim curSelect As StdPicture

Sub ConversionTable_Initialize()
    ' Mis à jour le 08/14/1996.
    ConversionTable = Array(1@, 5.0776@, 1.4861@, 1519.28@, 126.1@, 107.95@)
End Sub

Sub BeginPlaySound(ByVal ResourceId As Integer)
    SoundBuffer = LoadResData(ResourceId, "ATM_SOUND")
    sndPlaySound SoundBuffer(0), SND_ASYNC Or SND_NODEFAULT Or SND_MEMORY
End Sub

Sub EndPlaySound()
    sndPlaySound ByVal vbNullString, 0&
End Sub

Sub Cursor_Initialize()
    Set curSelect = LoadResPicture(1, vbResCursor)
End Sub

Sub SetCursor(Button As CommandButton)
    With Button
    .MousePointer = 99
    .MouseIcon = curSelect
    End With
End Sub
