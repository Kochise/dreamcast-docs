VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Schedule PIus OLE Server Demo"
   ClientHeight    =   1710
   ClientLeft      =   1740
   ClientTop       =   2550
   ClientWidth     =   4770
   Height          =   2400
   Left            =   1680
   LinkTopic       =   "Form1"
   ScaleHeight     =   1710
   ScaleWidth      =   4770
   Top             =   1920
   Width           =   4890
   Begin VB.ListBox List1 
      Height          =   1620
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   4455
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisSchPlus As SPL.Application
Dim appSchPlus As Object

Private Sub Form_Load()
Set appSchPlus = GetObject("", "Schedule+.Application")
Visible = True
With appSchPlus
    .Logon
    .ScheduleSelected.Activate 'Makes Visible
    Set MyAppt = .ScheduleSelected.singleappointments.New
        With MyAppt
            .SetProperties Text:="Santa Claus", _
                Start:=CVDate("12/24/95 23:30"), _
                End:=("12/25/95 00:30")
                
        End With
End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
appSchPlus.ScheduleSelected.Visible = False
appSchPlus.Logoff


End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo from Microsoft Developers Network Library" & vbCr & "Author: Ken Lassesen", VBA.vbInformation, App.Title
i% = SPL.OpenFlagConstants.opfCreateNew
End Sub

