VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "vbdraw"
   ClientHeight    =   7425
   ClientLeft      =   3270
   ClientTop       =   5145
   ClientWidth     =   7545
   Height          =   7830
   Left            =   3210
   LinkTopic       =   "Form1"
   ScaleHeight     =   7425
   ScaleWidth      =   7545
   Top             =   4800
   Width           =   7665
   Begin VB.Timer RedrawTimer 
      Interval        =   50
      Left            =   5280
      Top             =   3960
   End
   Begin VB.PictureBox BufferPic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   3015
      Left            =   120
      ScaleHeight     =   2985
      ScaleWidth      =   4785
      TabIndex        =   6
      Top             =   3960
      Width           =   4815
   End
   Begin VB.PictureBox SpritePic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   5280
      ScaleHeight     =   585
      ScaleWidth      =   825
      TabIndex        =   4
      Top             =   2880
      Width           =   855
   End
   Begin VB.PictureBox BkgndPic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   3015
      Left            =   120
      ScaleHeight     =   2985
      ScaleWidth      =   4785
      TabIndex        =   2
      Top             =   480
      Width           =   4815
   End
   Begin VB.PictureBox PalettePic 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   1815
      Left            =   5280
      ScaleHeight     =   1785
      ScaleWidth      =   2025
      TabIndex        =   0
      Top             =   480
      Width           =   2055
   End
   Begin VB.Label Label4 
      Caption         =   "Buffer:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   3600
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Sprite:"
      Height          =   255
      Left            =   5280
      TabIndex        =   5
      Top             =   2520
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Bkgnd:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Palette:"
      Height          =   255
      Left            =   5280
      TabIndex        =   1
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim Palette As Object
Dim Bkgnd As Object
Dim RedBall As Object
Dim Buffer As Object
Dim iRedBallX As Integer
Dim iRedBallY As Integer
Dim vy As Integer

Sub Render()
    ' Copy the background image to the off-screen buffer
    Bkgnd.Draw Buffer.hDC, 0, 0
    
    ' Draw the sprites in place
    RedBall.CopyWithTransparency Buffer, iRedBallX, iRedBallY
    
End Sub

Sub Draw()
    ' Copy the off-screen buffer to the screen
    ' Make the palette active
    Palette.Apply (BufferPic.hDC)
    
    ' Show the picture
    Buffer.Draw BufferPic.hDC, 0, 0
    
    ' Done with palette
    Palette.Remove (BufferPic.hDC)
End Sub

Private Sub Form_Load()
    ' Create the bkgnd drawing surface
    Set Bkgnd = CreateObject("Drawing.DrawingSurface")
    
    ' Load the bkgnd image
    b% = Bkgnd.LoadFile("dogbk1.bmp")
    
    ' Create a palette object
    Set Palette = CreateObject("Drawing.ColorPalette")
    
    ' get the palette from the background image
    b% = Palette.CreateFromImage(Bkgnd)
    
    ' Make it an identity palette
    Palette.MakeIdentity
        
    ' Map the bkgnd image to our palette
    b% = Bkgnd.MapToPalette(Palette.hPal)
    
    ' Load the red ball and map it
    Set RedBall = CreateObject("Drawing.DrawingSurface")
    RedBall.LoadFile ("redball.bmp")
    RedBall.MapToPalette (Palette.hPal)
    iRedBallX = 0
    iRedBallY = 50
    vy = 0
    
    ' Create the off-screen buffer
    Set Buffer = CreateObject("Drawing.DrawingSurface")
    Buffer.CreateNew Bkgnd.Width, Bkgnd.Height, Palette.hPal
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' Done with palette
    Set Palette = Nothing
    
    ' Done with background etc
    Set Bkgnd = Nothing
    Set RedBall = Nothing
    Set Buffer = Nothing
End Sub

Private Sub PalettePic_Paint()
    ' Show the palette
    w = PalettePic.Width / Screen.TwipsPerPixelX - 1
    h = PalettePic.Height / Screen.TwipsPerPixelY - 1
    Palette.Draw PalettePic.hDC, 0, 0, w, h
End Sub

Private Sub BkgndPic_Paint()
    ' Make the palette active
    Palette.Apply (BkgndPic.hDC)
    
    ' Show the picture
    Bkgnd.Draw BkgndPic.hDC, 0, 0
    
    ' Done with palette
    Palette.Remove (BkgndPic.hDC)
End Sub

Private Sub RedrawTimer_Timer()
    ' Move the sprites
    iRedBallX = iRedBallX + 5
    If iRedBallX > 320 Then iRedBallX = -20
    vy = vy + 1
    iRedBallY = iRedBallY + vy
    If iRedBallY > 170 Then
        vy = -vy
        iRedBallY = 170
    End If
    
    ' Render and draw the changes
    Render
    Draw
End Sub


Private Sub SpritePic_Paint()
    ' Make the palette active
    Palette.Apply (SpritePic.hDC)
    
    ' Show the picture
    RedBall.Draw SpritePic.hDC, 0, 0
    
    ' Done with palette
    Palette.Remove (SpritePic.hDC)
End Sub

Private Sub BufferPic_Paint()
    ' Make the palette active
    Palette.Apply (BufferPic.hDC)
    
    ' Show the picture
    Buffer.Draw BufferPic.hDC, 0, 0
    
    ' Done with palette
    Palette.Remove (BufferPic.hDC)
End Sub


