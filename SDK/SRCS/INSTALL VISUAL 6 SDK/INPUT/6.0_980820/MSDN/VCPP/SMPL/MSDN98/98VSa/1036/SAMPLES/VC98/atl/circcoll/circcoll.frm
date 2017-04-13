VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "CircColl Sample Driver"
   ClientHeight    =   7020
   ClientLeft      =   1152
   ClientTop       =   1368
   ClientWidth     =   8472
   Height          =   7404
   Left            =   1104
   LinkTopic       =   "Form1"
   ScaleHeight     =   7020
   ScaleWidth      =   8472
   Top             =   1032
   Width           =   8568
   Begin VB.CommandButton Command1 
      Caption         =   "Get Circle Collection"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2295
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub Command1_Click()

    ScaleMode = 3   ' Set scale to pixels.
    FillStyle = 0   ' solid
    
    ' get a collection of objects
    Dim x As New MyCircleCollectionCreator
    Set coll = x.GetCircles(5)
    Cls
    ' draw it using the Circle() primitive
    For i = 1 To coll.Count
        FillColor = RGB(Rnd * 255, Rnd * 255, Rnd * 255)
        Circle (coll.Item(i).XCenter, coll.Item(i).YCenter), coll.Item(i).Radius
        Print coll.Item(i).Label
    Next i
    
    MsgBox ("Now change values and redraw")
    ' change vaules of objects inside the collection
    For i = 1 To coll.Count
        Set circ = coll.Item(i)
        s = "New "
        s = s + circ.Label
        circ.Radius = circ.Radius * 0.5
        circ.XCenter = circ.XCenter + 50 * i
        circ.YCenter = circ.YCenter + 50 * i
        circ.Label = s
    Next i
    Cls
    ' now redraw to show new values
    For Each circ In coll
        FillColor = RGB(Rnd * 255, Rnd * 255, Rnd * 255)
        Circle (circ.XCenter, circ.YCenter), circ.Radius, RGB(Rnd * 255, Rnd * 255, Rnd * 255)
        Print circ.Label
    Next circ

End Sub


