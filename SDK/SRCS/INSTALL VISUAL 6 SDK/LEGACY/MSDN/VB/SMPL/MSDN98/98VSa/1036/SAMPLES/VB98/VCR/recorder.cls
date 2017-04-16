VERSION 1.0 CLASS 
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsRecorder"
Attribute VB_Base = "0{FCFB3D2A-A0FA-1068-A738-08002B3371B5}"
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Customizable = False
'***************************************************************
' Module de classe pour l'exemple d'application VCR. 
' Agit comme le module logique du magnétoscope pour
' stocker des données et suivre les activités d'enregistrement.
'***************************************************************

Option Explicit

Public Channel As Integer           ' Chaîne à enregistrer.
Public StartRecording As Variant    ' Heure de début.
Public StopRecording As Variant     ' Heure de fin.
Public Enabled As Boolean           ' Mode enregistrement.

Private Sub Class_Initialize()
    ' Initialise les propriétés de la classe.
    Enabled = True
    Channel = 3
    StartRecording = Empty
    StopRecording = Empty
End Sub
