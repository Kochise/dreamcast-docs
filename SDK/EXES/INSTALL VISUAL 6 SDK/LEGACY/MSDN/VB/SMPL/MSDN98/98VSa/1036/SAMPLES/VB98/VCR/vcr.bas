Attribute VB_Name = "VCRModule"
'********************************************************
' Sujet: Module général pour l'exemple d'application VCR. 
'        Contient des procédures partagées.
'********************************************************
Option Explicit

' Effectue l'instanciation de la classe Recorder.
Public Recorder As New clsRecorder

'**********************************************
' Sujet:    Active ou désactive les boutons de la
'           feuille VCR basée sur le mode en cours.
' Entrées:  Bouton: la bouton de commande appelant
'           la procédure.
'**********************************************
Sub ButtonManager(Button As Control)
    Dim vntControl As Variant   ' La valeur du contrôle
    
    ' Détermine sur quel bouton de fonction l'utilisateur
    ' a appuyé et met à jour les boutons et la classe Recorder.
    Select Case Button
        Case frmVCR.cmdPlay, frmVCR.cmdForward, frmVCR.cmdRewind
            frmVCR.cmdPause.Enabled = True
            frmVCR.cmdStop.Enabled = True
            frmVCR.cmdRec.Enabled = False
            frmVCR.cmdDown.Enabled = False
            frmVCR.cmdUp.Enabled = False
            Recorder.Enabled = False
        Case frmVCR.cmdRec
            frmVCR.cmdPause.Enabled = True
            frmVCR.cmdStop.Enabled = True
            frmVCR.cmdPlay.Enabled = False
            frmVCR.cmdForward.Enabled = False
            frmVCR.cmdRewind.Enabled = False
            frmVCR.cmdDown.Enabled = False
            frmVCR.cmdUp.Enabled = False
            Recorder.Enabled = False
        Case frmVCR.cmdPause
            frmVCR.cmdPause.Enabled = False
        Case frmVCR.cmdStop
            frmVCR.cmdStop.Enabled = False
            frmVCR.cmdPause.Enabled = False
            frmVCR.cmdRec.Enabled = True
            frmVCR.cmdPlay.Enabled = True
            frmVCR.cmdForward.Enabled = True
            frmVCR.cmdRewind.Enabled = True
            frmVCR.cmdDown.Enabled = True
            frmVCR.cmdUp.Enabled = True
            Recorder.Enabled = True
    End Select
    ' affecte le bouton à son contrôle Shape correspondant.
    vntControl = Button.Name
    vntControl = Right$(vntControl, Len(vntControl) - 3)
    vntControl = "shp" & vntControl
    ' appelle la routine pour mettre à jour les indicateurs.
    HighlightButton vntControl
End Sub
'*********************************************************
' Sujet:    Active ou désactive les contrôles de forme 
'           sur la feuille VCR basée sur le mode en cours.
' Entrées:  MyControl: le contrôle Shape passé
'           à la procédure.
'*********************************************************
Sub HighlightButton(MyControl As Variant)
    Dim i As Integer    ' Variable Compteur 
    
    ' Parcours la collection Controls.
    For i = 0 To frmVCR.Controls.Count - 1
        ' Test pour un contrôle Shape.
        If TypeOf frmVCR.Controls(i) Is Shape Then
            ' S'il s'agit du contrôle passé, le rend
            ' visible, sinon le rend invisible.
            If frmVCR.Controls(i).Name = MyControl Then
                frmVCR.Controls(i).Visible = True
            Else
                frmVCR.Controls(i).Visible = False
            End If
        End If
    Next
End Sub
'******************************************************
' Sujet:    Stocke le dernier numéro de chaîne pour
'           le restaurer après l'enregistrement.
' Entrées:  Channel: le numéro de chaîne passé
'           à la procédure.
' Renvois:  La chaîne stockée dans la variable Static.
'******************************************************
Function SaveChannel(Channel As Variant) As Integer
    Static intChannel As Integer ' Stocke la chaîne.
    
    ' Affecte la valeur à la variable Static.
    If Channel <> 0 Then
        intChannel = Channel
    End If
    
    ' Renvoie le numéro de chaîne.
    SaveChannel = intChannel
End Function
