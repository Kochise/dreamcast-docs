Attribute VB_Name = "Module1"
Option Explicit

Declare Function timeGetTime Lib "winmm.dll" () As Long

' CoffeeWatch doit être un Exe ActiveX, car
'   il expose l'objet public NotifyMe
'   utilisé pour l'exemple de la méthode de
'   rappel. Il ne sera jamais exécuté comme
'   un composant mais comme une application
'   autonome.
Sub Main()
    If App.StartMode = vbSModeStandalone Then
        Form1.Show
    End If
End Sub
