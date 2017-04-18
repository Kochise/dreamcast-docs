VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "The Cluts House"
   ClientHeight    =   5775
   ClientLeft      =   3585
   ClientTop       =   1740
   ClientWidth     =   7200
   Height          =   6180
   Left            =   3525
   LinkTopic       =   "Form1"
   ScaleHeight     =   5775
   ScaleWidth      =   7200
   Top             =   1395
   Width           =   7320
   Begin VB.CommandButton AddLightBulb 
      Caption         =   "Add Light Bulb"
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   5400
      Width           =   1935
   End
   Begin VB.Image Image1 
      Height          =   5400
      Left            =   0
      Picture         =   "MAIN.frx":0000
      Top             =   0
      Width           =   7200
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Private Sub AddLightBulb_Click()
    ' Try to create a light bulb object
    Dim hr As Long
    Dim punkLightBulb As Long
    hr = CoCreateInstance(CLSID_LightBulb, 0, CLSCTX_INPROC_SERVER, IID_IUnknown, punkLightBulb)
    If hr < 0 Then
        MsgBox ("Failed to create light bulb. Error " + Hex(hr) + "H")
        Exit Sub
    End If
    
    ' Try to get a pointer to its IDrawing interface
    Dim pIDrawing As Long
    hr = comQueryInterface(punkLightBulb, IID_IDrawing, pIDrawing)
    If hr < 0 Then
        MsgBox ("Failed to get IDrawing interface. Error " + Hex(hr) + "H")
        Exit Sub
    End If
    
    ' Set the palette to the palette in the image
    hr = IDrawing_SetPalette(pIDrawing, Image1.Picture.hPal)
    
    ' Call IDrawing::Draw and see what we get
    hr = IDrawing_Draw(pIDrawing, Form1.hDC, 120, 120)
    
    ' Finished with IDrawing interface
    hr = comRelease(pIDrawing)
    
    ' Finished with light bulb
    hr = comRelease(punkLightBulb)


End Sub

Private Sub Form_Load()
    InitCOMSupport
End Sub
