VERSION 4.00
Begin VB.Form frmMSDNDemo 
   Caption         =   "MAPI OLE Server Demo"
   ClientHeight    =   1710
   ClientLeft      =   2400
   ClientTop       =   2820
   ClientWidth     =   4770
   Height          =   2400
   Left            =   2340
   LinkTopic       =   "Form1"
   ScaleHeight     =   1710
   ScaleWidth      =   4770
   Top             =   2190
   Width           =   4890
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   240
      Top             =   720
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Animate Star Texture"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4455
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "frmMSDNDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisPowerPnt As PowerPoint.Application
Dim ThisPresentation As PowerPoint.Presentation
Dim CurrentSlide As PowerPoint.Slide

Private Sub Command1_Click()
Timer1.Enabled = Not Timer1.Enabled
If Timer1.Enabled Then
    Command1.Caption = "&Stop Animate Texture"
Else
    Command1.Caption = "&Animate Texture"
End If
End Sub

Private Sub Form_Load()
'PowerPoint 7 is the first version as an OLE Server
Set ThisPowerPnt = CreateObject("PowerPoint.Application")
ThisPowerPnt.AppWindow.Visible = True

Set ThisPresentation = ThisPowerPnt.Presentations.Add( _
    WithWindow:=True _
    )
Set CurrentSlide = ThisPresentation.Slides.Add( _
    Index:=1, _
    Layout:=PowerPoint.SlideLayout.ppLayoutText _
    )
    With CurrentSlide
        'Note: Objects are "SlideObects"
        .Objects(1).Text = "MSDN PowerPoint Programmability"
        .Objects(2).Text = "Sixteen Point Star"
        .Objects.AddShape _
            type:=PowerPoint.ShapeType.ppShapeSixteenPointStar, _
            Left:=4800, _
            Top:=4300, _
            Width:=5000, _
            Height:=5000
        'Units of measurement in TWIPS (like Visual Basic)
        .Objects(3).GraphicFormat.Fill.PresetTextured _
            PowerPoint.PresetTexture.ppPresetTextureWovenMat
    End With
Command1_Click
End Sub

Private Sub Form_Unload(Cancel As Integer)
ThisPowerPnt.Quit
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
End Sub

Private Sub Timer1_Timer()
Static i
i = (i + 1) Mod PowerPoint.PresetTexture.ppPresetTextureWovenMat + 1
CurrentSlide.Objects(3).GraphicFormat.Fill.PresetTextured i
DoEvents
End Sub
