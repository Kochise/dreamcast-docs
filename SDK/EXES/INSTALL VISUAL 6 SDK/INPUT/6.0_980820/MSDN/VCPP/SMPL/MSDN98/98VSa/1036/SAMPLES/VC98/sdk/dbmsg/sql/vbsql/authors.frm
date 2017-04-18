VERSION 2.00
Begin Form fAuthors 
   BackColor       =   &H00C0C0C0&
   Caption         =   "Authors"
   ForeColor       =   &H00C0C0C0&
   Height          =   5655
   Icon            =   AUTHORS.FRX:0000
   Left            =   270
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4965
   ScaleWidth      =   9135
   Top             =   1695
   Width           =   9255
   Begin SSFrame frmTitles 
      Caption         =   "Titles"
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00000000&
      Height          =   2535
      Left            =   75
      TabIndex        =   41
      Top             =   2325
      Visible         =   0   'False
      Width           =   8970
      Begin SSPanel panGrid 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   2055
         Left            =   120
         TabIndex        =   42
         Top             =   330
         Width           =   8730
         Begin Grid grdTitles 
            Cols            =   9
            FixedCols       =   0
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   2025
            Left            =   15
            Rows            =   10
            TabIndex        =   43
            Top             =   15
            Width           =   8700
         End
      End
   End
   Begin SSRibbon cmdDown 
      AutoSize        =   0  'None
      BackColor       =   &H00C0C0C0&
      BevelWidth      =   1
      Height          =   420
      Left            =   8670
      PictureUp       =   AUTHORS.FRX:0302
      Top             =   75
      Width           =   420
   End
   Begin SSPanel Panel3D9 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   75
      TabIndex        =   38
      Top             =   1530
      Width           =   2625
      Begin SSCommand cmdMoreRows 
         BevelWidth      =   1
         Caption         =   "&More rows"
         Enabled         =   0   'False
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   345
         Left            =   15
         TabIndex        =   39
         Top             =   15
         Width           =   2595
      End
   End
   Begin SSPanel Panel3D1 
      Alignment       =   8  'Center - BOTTOM
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      ForeColor       =   &H00000000&
      Height          =   2190
      Left            =   2775
      TabIndex        =   29
      Top             =   75
      Width           =   5850
      Begin SSPanel panAuthors 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Index           =   1
         Left            =   105
         TabIndex        =   37
         Top             =   315
         Width           =   1140
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   1
            Left            =   15
            TabIndex        =   1
            Top             =   15
            Width           =   1110
         End
      End
      Begin SSPanel Panel3D8 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   3450
         TabIndex        =   36
         Top             =   1020
         Width           =   1695
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   6
            Left            =   15
            TabIndex        =   6
            Top             =   15
            Width           =   1665
         End
      End
      Begin SSPanel Panel3D2 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   5190
         TabIndex        =   35
         Top             =   1020
         Width           =   570
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   7
            Left            =   15
            TabIndex        =   7
            Top             =   15
            Width           =   540
         End
      End
      Begin SSPanel Panel3D3 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   2235
         TabIndex        =   34
         Top             =   1020
         Width           =   1170
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   5
            Left            =   15
            TabIndex        =   5
            Top             =   15
            Width           =   1140
         End
      End
      Begin SSPanel Panel3D4 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   90
         TabIndex        =   33
         Top             =   1020
         Width           =   2100
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   4
            Left            =   15
            TabIndex        =   4
            Top             =   15
            Width           =   2070
         End
      End
      Begin SSPanel Panel3D5 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   3180
         TabIndex        =   32
         Top             =   315
         Width           =   2580
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   3
            Left            =   15
            TabIndex        =   3
            Top             =   15
            Width           =   2550
         End
      End
      Begin SSPanel Panel3D6 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   1290
         TabIndex        =   31
         Top             =   315
         Width           =   1845
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   2
            Left            =   15
            TabIndex        =   2
            Top             =   15
            Width           =   1815
         End
      End
      Begin SSPanel Panel3D7 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   105
         TabIndex        =   30
         Top             =   1695
         Width           =   1635
         Begin TextBox txtAuthors 
            FontBold        =   0   'False
            FontItalic      =   0   'False
            FontName        =   "MS Sans Serif"
            FontSize        =   8.25
            FontStrikethru  =   0   'False
            FontUnderline   =   0   'False
            Height          =   285
            Index           =   8
            Left            =   15
            TabIndex        =   8
            Top             =   15
            Width           =   1605
         End
      End
      Begin SSCheck chkContract 
         Caption         =   "Contract"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   240
         Left            =   2235
         TabIndex        =   9
         Top             =   1725
         Width           =   930
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Id"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   1
         Left            =   120
         TabIndex        =   10
         Top             =   120
         Width           =   150
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "First"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   2
         Left            =   1320
         TabIndex        =   11
         Top             =   120
         Width           =   285
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Last"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   3
         Left            =   3195
         TabIndex        =   12
         Top             =   120
         Width           =   300
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Address"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   4
         Left            =   120
         TabIndex        =   13
         Top             =   825
         Width           =   570
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Zip Code"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   5
         Left            =   2295
         TabIndex        =   14
         Top             =   825
         Width           =   645
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "City"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   6
         Left            =   3480
         TabIndex        =   15
         Top             =   825
         Width           =   270
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "State"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   7
         Left            =   5205
         TabIndex        =   16
         Top             =   825
         Width           =   375
      End
      Begin Label lblAuthors 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Phone"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Index           =   8
         Left            =   120
         TabIndex        =   17
         Top             =   1500
         Width           =   465
      End
   End
   Begin SSPanel panItemsRemoved 
      Alignment       =   8  'Center - BOTTOM
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00000000&
      Height          =   300
      Left            =   75
      TabIndex        =   28
      Top             =   75
      Width           =   2625
   End
   Begin SSPanel panItemsRead 
      Alignment       =   8  'Center - BOTTOM
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00000000&
      Height          =   300
      Left            =   75
      TabIndex        =   27
      Top             =   1965
      Width           =   2625
   End
   Begin SSPanel panAuthors 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      ForeColor       =   &H00000000&
      Height          =   1035
      Index           =   0
      Left            =   75
      TabIndex        =   26
      Top             =   450
      Width           =   2625
      Begin ListBox lstPrim 
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   1005
         Left            =   15
         TabIndex        =   0
         Top             =   15
         Width           =   2595
      End
   End
   Begin Frame Frame1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Invisibles"
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   825
      Left            =   9300
      TabIndex        =   18
      Top             =   555
      Visible         =   0   'False
      Width           =   5700
      Begin SSCommand cmdSubGridDetail 
         Caption         =   "SubGridDetail"
         Font3D          =   1  'Raised w/light shading
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   495
         Left            =   3570
         TabIndex        =   40
         Top             =   240
         Visible         =   0   'False
         Width           =   1215
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   7
         Left            =   2850
         Picture         =   AUTHORS.FRX:049C
         TabIndex        =   25
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   6
         Left            =   2325
         Picture         =   AUTHORS.FRX:0636
         TabIndex        =   24
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   5
         Left            =   1935
         Picture         =   AUTHORS.FRX:07A0
         TabIndex        =   23
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   4
         Left            =   1410
         Picture         =   AUTHORS.FRX:093A
         TabIndex        =   22
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   3
         Left            =   885
         Picture         =   AUTHORS.FRX:0AA4
         TabIndex        =   21
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Enabled         =   0   'False
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   2
         Left            =   495
         Picture         =   AUTHORS.FRX:0C0E
         TabIndex        =   20
         Top             =   300
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Index           =   1
         Left            =   105
         Picture         =   AUTHORS.FRX:0D78
         TabIndex        =   19
         Top             =   300
         Width           =   345
      End
   End
   Begin Menu menFile 
      Caption         =   "&File"
      Begin Menu altClose 
         Caption         =   "&Close Form"
      End
      Begin Menu altDummy1 
         Caption         =   "-"
      End
      Begin Menu altExit 
         Caption         =   "&Exit"
      End
   End
   Begin Menu menEdit 
      Caption         =   "&Edit"
      Begin Menu altNew 
         Caption         =   "&New"
         Shortcut        =   ^N
      End
      Begin Menu altSave 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin Menu altDelete 
         Caption         =   "&Delete"
      End
      Begin Menu altClear 
         Caption         =   "Clear &Form"
         Shortcut        =   ^C
      End
      Begin Menu altRefresh 
         Caption         =   "&Refresh"
         Shortcut        =   ^R
      End
      Begin Menu altQuery 
         Caption         =   "&Query"
         Shortcut        =   ^Q
      End
      Begin Menu altCancel 
         Caption         =   "&Cancel"
      End
      Begin Menu altDummy2 
         Caption         =   "-"
      End
      Begin Menu altCopy 
         Caption         =   "Copy &to new"
      End
      Begin Menu altRelease 
         Caption         =   "&Release"
      End
   End
   Begin Menu menForms 
      Caption         =   "Fo&rms"
      Begin Menu altAuthors 
         Caption         =   "&Authors"
         Shortcut        =   ^A
      End
   End
   Begin Menu menWindow 
      Caption         =   "&Window"
      WindowList      =   -1  'True
      Begin Menu altCascade 
         Caption         =   "&Cascade"
      End
      Begin Menu altTile 
         Caption         =   "&Tile"
      End
      Begin Menu altArrangeIcons 
         Caption         =   "&Arrange Icons"
      End
      Begin Menu altDummy4 
         Caption         =   "-"
      End
      Begin Menu altNormalSize 
         Caption         =   "&Normal Size"
      End
   End
   Begin Menu menSettings 
      Caption         =   "&Options"
      Begin Menu altShowSQL 
         Caption         =   "&Show SQL"
      End
   End
   Begin Menu menHelp 
      Caption         =   "&Help"
      Begin Menu altContents 
         Caption         =   "&Contents"
      End
      Begin Menu altDummy3 
         Caption         =   "-"
      End
      Begin Menu altAbout 
         Caption         =   "&About..."
      End
   End
End
'
' The AUTHORS form
' =================
' Used for maintenance of information on authors
' including selecting, inserting, updating and deleting
' authors
'
' Constant definitions:
' --------------------
' The nominal Width and Height of the form are saved
' as constants to allow the form to be properly opened
' as a MDI Child and to regain its normal size when
' that option is chosen in the menu system (Window -
' Normal Size):
Const DEFWIDTH% = 9255
Const DEFMINHEIGHT% = 3060 - 280
Const DEFMAXHEIGHT% = 5650 - 280

' The value of the constant CHUNKSIZE% determins the number of
' rows that will be read from the result set
' per chunk and added to the listbox.
' The value of the constant LSTPRIMMAX% is the max number of
' rows that will be held in the listbox lstPrim. When the
' number has been exeeded the application will start to remove
' the top row for each new row added to the listbox.
'
' NOTE! Both of these constants are indeed changeble to match
' your specific needs and thoughts.
Const CHUNKSIZE% = 100
Const LSTPRIMMAX% = 500
    

' The list box shows authors names. To help locate an
' author whose name is selected in the list box his or
' her AU_ID is also stored in the list box invisible
' to the user. The LISTWIDTH constant is used to determine
' exactly where in the list box text string the AU_ID is
' stored. It begins on the position of LISTWIDTH + 1 (71):
Const LISTWIDTH% = 70

' Declare variables for a select channel and an update
' channel to SQL Server, known all over but not outside
' the form:
Dim SelChannel As Integer
Dim UpdChannel As Integer

' Declare a variable to store the last used Where clause.
' This allows a refresh operation, sending the same SQL
' select clause once again to the server using the refresh
' tool (shower) in the tool bar:
Dim LastWhereClause As String

' Declare a MODE variable to store the different modes
' of the form. Mode could take up either of the following
' values: SQLNEW, SQLSHOW or SQLREST. Those values are
' declared as symbolic constants in the module ADBGLOB.BAS.
' SQLNEW is the mode when a new author is being entered.
' SQLSHOW is the mode when an existing author is shown
' in the form for possible modification or deletion.
' SQLREST is the mode when the form is resting, i.e. when
' a selection is being made or when the form is waiting for
' examples to use for QBE.

Dim Mode As Integer

' The variable QualString save the qualification string
' returned from the call to SQLQUAL(). It containts references
' to the unique key and to the timestamp column.
' This is essential for Browse Mode.
Dim QualString As String


' The variable FormMaxOpen is TRUE if the subgrid is showned.
' The user brings it up by clicking on the push button for
' titles. To close the subgrid just click on the push button
' again and FormMaxOpen will be set to FALSE.

Dim FormMaxOpen As Integer

Sub altAbout_Click ()
'
' Show the about box
'

    fAbout.Show MODAL

End Sub

Sub altArrangeIcons_Click ()
'
' Arrange the icons of the MDI application
'

    MDIMA.Arrange ARRANGE_ICONS

End Sub

Sub altAuthors_click ()
'
' Show another instance of the authors form
' Try opening several instances showing different
' sets of authors in each separate form, for instance
' Utah authors in one form and Michigan authors in
' another. Tile the forms for better overview.
'

' Declare a new instance of the Authors form:
Dim newAuthors As New fAuthors

    ' Open the new instance:
    screen.MousePointer = 11
    newAuthors.Show
    screen.MousePointer = 0

End Sub

Sub altCancel_Click ()
'
' Cancels the ongoing operation; for instance modification
' of data about an author. If there is any operation
' to cancel, the cancel push button (with the X, like
' in Excel) will be enabled and then automatically pushed.
' If it is not enable there will be a beep:

    If MainButton(7).Enabled Then
        MainButton(7).Value = True
    Else
        Beep
    End If

End Sub

Sub altCascade_Click ()
'
' Cascade the icons of the MDI application
'


    MDIMA.Arrange CASCADE

End Sub

Sub altClear_Click ()
'
' Clears the content of the form by automatically
' pressing the Clear button in the main tool bar:

    If MainButton(4).Enabled Then
        MainButton(4).Value = True
    Else
        Beep
    End If

End Sub

Sub altClose_Click ()
'
' Closes the form by unloading it, thus securing
' that any unload procedure will be carried out:

    Unload Me

End Sub

Sub altContents_Click ()
Dim x%, lHelpPath As String
'
' Activate the help system
'
    
    lHelpPath = App.Path + "\pubs1.hlp"
    x% = WinHelp(MDIMA.hWnd, lHelpPath, HELP_INDEX, 0)

End Sub

Sub altCopy_Click ()
'
' Sets the mode to SQLNEW, thus allowing the record
' in the form to be modified and then inserted, then
' sets focus to the first text field in the form. This
' function can save some typing:

    Mode = SQLNEW
    txtAuthors(1).SetFocus

End Sub

Sub altDelete_Click ()
'
' Starts a delete procedure by pressing the delete
' button in the main tool bar. If it is enabled, the
' process controlled by the button will be started,
' otherwise there will be a beep, telling that there
' is nothing to delete at present:

    If MainButton(3).Enabled Then
        MainButton(3).Value = True
    Else
        Beep
    End If

End Sub

Sub altExit_Click ()
'
' Exit the entire application by unloading the MDI
' form. The result will be that any opened MDI child
' window will be unloaded, their respective unload
' procedures automatically carried out:

    Unload MDIMA

End Sub

Sub altNew_Click ()
'
' Start the NEW procedure to enter and insert information
' about a new author. If the corresponding button in the
' main tool bar is enabled, it is pushed, otherwise a new
' author could not be entered at this state of the form,
' and a beep is heard:

    If MainButton(1).Enabled Then
        MainButton(1).Value = True
    Else
        Beep
    End If

End Sub

Sub altNormalSize_Click ()
'
' Reinstate the normal size of the form, if changed
'

    If Me.WindowState <> 0 Then Me.WindowState = 0  ' normal size
    Me.Width = DEFWIDTH%
    If FormMaxOpen Then
        Me.Height = DEFMAXHEIGHT%
    Else
        Me.Height = DEFMINHEIGHT%
    End If
    CenterForm

End Sub

Sub altQuery_Click ()
'
' Send a query to SQL Server by pushing the corresponding
' push button in the tool bar, if it is enabled. If not,
' there is no query to send and a beep is heard:

    If MainButton(6).Enabled Then
        MainButton(6).Value = True
    Else
        Beep
    End If
    

End Sub

Sub altRefresh_Click ()
'
' Send the same query as was last sent to SQL Server,
' thereby refreshing the result set to include any
' changes made by other users since the data was last
' selected:
' Pushes the corresponding button in the main tool bar
' if it is enabled. If not, a beep is heard, signalling
' that refresh is an inappropriate operation at this time:

    If MainButton(5).Enabled Then
        MainButton(5).Value = True
    Else
        Beep
    End If

End Sub

Sub altRelease_Click ()
'
' Releases the record in the form from its connection
' with the database, allowing the user to make changes
' and then use the result as an example for a query.
'
' Sets the MODE variable to SQLREST, indicating that the
' form is "resting" (will not allow saving the info)

    Mode = SQLREST

End Sub

Sub altSave_Click ()
'
' Saves the content of the form to SQL Server by issuing
' an UPDATE or INSERT statement. Uses the corresponding
' push button in the main tool bar if it is enabled.
' Otherwise a beep is heard, indicating that there is
' nothing to save right now:

    If MainButton(2).Enabled Then
        MainButton(2).Value = True
    Else
        Beep
    End If

End Sub

Sub altShowSQL_Click ()
'
' Controls wether SQL statements are shown in a message
' box or not. When this menu option is checked, all
' SQL statements are shown before sent to the server:

    If altShowSQL.Checked Then
        altShowSQL.Checked = False
        ShowSQL = False
    Else
        altShowSQL.Checked = True
        ShowSQL = True
    End If

End Sub

Sub AltTile_Click ()
'
' Tile the icons of the MDI application
'


    MDIMA.Arrange TILE_HORIZONTAL

End Sub

Sub CenterForm ()

    Me.Top = screen.Height / 2 - Me.Height / 2 - 710

End Sub

Sub chkContract_Click (Value As Integer)
'
' If the form is not resting (MODE <> SQLREST), the
' SAVE and CANCEL buttons are enabled, indicating that
' some information that should be saved has been entered:

    If Mode <> SQLREST Then
        MainButton(2).Enabled = True        ' save button
        MainButton(7).Enabled = True        ' cancel button
    End If

End Sub

Sub ClearFields ()
'
' Clear the contents of any field in the form
'

Dim x As Integer, lMODE As Integer

    lMODE = Mode        ' Save actual Mode value
    Mode = SQLREST      ' Set Mode to resting
    For x = 1 To 8
        txtAuthors(x).Text = ""
    Next
    chkContract.Value = False
    Mode = lMODE        ' Reset initial mode

End Sub

Sub ClearForm ()
Dim lMODE As Integer

    lMODE = Mode        ' Save actual mode
    Mode = SQLREST      ' Set mode to resting
    lstPrim.Clear       ' Clear primary list box
    ClearFields         ' Clear all fields
    If FormMaxOpen Then ClearGrid grdTitles ' clear the grid
    panItemsRead.Caption = ""
    panItemsRemoved.Caption = ""
    Mode = lMODE        ' Reset initial mode
    SetMainButtons Mode ' Enable/Disable buttons in toolbar
    txtAuthors(1).SetFocus

End Sub

Sub ClearGrid (pGrid As Control)
'
' Clear the grid
'

Dim x As Integer, y As Integer

    For x = 1 To pGrid.Rows - 1
        pGrid.Row = x
        For y = 0 To pGrid.Cols - 1
            pGrid.Col = y
            pGrid.Text = ""
        Next
    Next

End Sub

Sub cmdDown_Click (Value As Integer)
'
' Shows the sub grid with titles for an author
'

    If cmdDown.Value = False Then
        SubGridClose
        Exit Sub
    End If
    If Me.WindowState <> 2 Then
        Me.Height = DEFMAXHEIGHT%
        CenterForm
    End If
    FormMaxOpen = True
    frmTitles.Visible = True
    If Len(RTrim$(txtAuthors(1).Text)) > 0 Then
        cmdSubGridDetail.Value = True
    Else
        HighlightGridRow grdTitles, 1
    End If
    

End Sub

Sub cmdMoreRows_Click ()
'
' This button is enabled whenever the result set
' contains rows that has not yet been read and
' transferred to the lstPrim listbox. When the
' user presses this button another chunk of
' CHUNKSIZE% rows are read. When all the rows of
' the result set has been read (NO_MORE_ROWS) this
' button is disabled.

    SQLGetRows

End Sub

Sub cmdSubGridDetail_Click ()
'
' Sending a SQL statement and filling the sub grid
' with titles for a specific author
'

Dim lCmd$, lId$, res%

    lId$ = txtAuthors(1).Text
    lCmd$ = "select t.title_id, title, type, price, "
    lCmd$ = lCmd$ + "advance, royalty, ytd_sales, "
    lCmd$ = lCmd$ + "notes, pubdate "
    lCmd$ = lCmd$ + "from titles t, titleauthor ta "
    lCmd$ = lCmd$ + "where t.title_id = ta.title_id "
    lCmd$ = lCmd$ + "and ta.au_id = " + Chr$(34) + lId$ + Chr$(34)
    ClearGrid grdTitles
    res% = SQLComm(UpdChannel%, lCmd$)
    If res% = SUCCEED Then SQLFillGrid grdTitles, UpdChannel%
    HighlightGridRow grdTitles, 1

End Sub

Function EvaluateForm ()
'
' Evaluate each field in the form and create a where clause
' for the Select statement
'

Dim lRetStr$, x As Integer

    ' Initialize return string.
    ' (Not neccessary but neater.)
    lRetStr$ = ""
    For x = 1 To 8      ' Loop through each text box in form
        If Len(RTrim$(txtAuthors(x).Text)) > 0 Then
            If Len(Trim$(lRetStr$)) Then lRetStr$ = lRetStr$ + " and "
            Select Case x
                ' Build condition for each field:
                Case 1
                    lRetStr$ = lRetStr$ + "au_id like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 2
                    lRetStr$ = lRetStr$ + "au_fname like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 3
                    lRetStr$ = lRetStr$ + "au_lname like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 4
                    lRetStr$ = lRetStr$ + "address like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 5
                    lRetStr$ = lRetStr$ + "zip like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 6
                    lRetStr$ = lRetStr$ + "city like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 7
                    lRetStr$ = lRetStr$ + "state like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
                Case 8
                    lRetStr$ = lRetStr$ + "phone like " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34)
            End Select
        End If
    Next
    ' Check check box content, build upon the where clause:
    If chkContract.Value = True Then        ' checked
        If Len(Trim$(lRetStr$)) Then lRetStr$ = lRetStr$ + " and "
        lRetStr$ = lRetStr$ + "contract = 1"
    End If
    LastWhereClause = lRetStr$      ' Save as last used clause
    EvaluateForm = lRetStr$         ' Return where clause

End Function

Sub Form_Activate ()

    If ShowSQL Then
        altShowSQL.Checked = True
    Else
        altShowSQL.Checked = False
    End If
    
End Sub

Sub Form_Load ()
'
' Set up the form at load time
'

Dim res%, lMsg$

    ' Set The Width and Height properties of the form
    ' to their predefined values. Setting the Top and
    ' Left properties to center the form within the
    ' MDI form:
    Me.Width = DEFWIDTH%
    Me.Height = DEFMINHEIGHT%
    CenterForm
    Me.Left = screen.Width / 2 - Me.Width / 2
    
    ' Opening two connections to SQL Server, one for selecting
    ' sets of authors, another for updating purposes.
    ' Putting the pubs database (Database$) in use:
    SelChannel = Logon%(Server$, LoginId$, Password$, WorkSta$, AppName$)
    UpdChannel = Logon%(Server$, LoginId$, Password$, WorkSta$, AppName$)
    res% = SqlUse(SelChannel, Database$)
    res% = SqlUse(UpdChannel, Database$)
    
    ' Check the status of the TIMESTAMP column in the Authors table
    res% = CheckifTimestamp(SelChannel)
    If res% = False Then
        res% = AskifAlter()
        If res% Then
            res% = AlterAuthors(SelChannel)
            Beep
            If res% Then
                lMsg$ = "The Authors table has been successfully altered with a TIMESTAMP column."
                MsgBox lMsg$, 64
            Else
                lMsg$ = "There was some problem altering and updating the Authors table." + NEWLINE$ + NEWLINE$
                lMsg$ = lMsg$ + "The sample application will terminate."
                MsgBox lMsg$, 48
                Unload MDIMA
            End If
        Else
            Beep
            MsgBox "Sorry, the sample application will terminate.", 48
            Unload MDIMA            ' this will terminate the application
        End If
    End If
    
    ' Specify the sub grid for titles
    SpecifyGrid

End Sub

Sub Form_Unload (Cancel As Integer)

    SqlClose SelChannel
    SqlClose UpdChannel

End Sub

Sub grdTitles_Click ()

    HighlightGridRow grdTitles, (grdTitles.Row)

End Sub

Sub HandleEmptyQual ()
Dim lMsg$

    Beep
    lMsg$ = EmptyQualString()
    MsgBox lMsg$, 16, "Empty qual string"
    RefreshFormFields

End Sub

Sub HighlightGridRow (pGrid As Control, pRowNmbr As Integer)
'
' Highlights the selected row in the grid
'

    If pRowNmbr = 0 Then pRowNmbr = 1       ' to avoide VB error
    pGrid.Row = pRowNmbr
    pGrid.SelStartRow = pRowNmbr
    pGrid.SelEndRow = pRowNmbr
    pGrid.Col = pGrid.Cols - 1
    pGrid.SelStartCol = 0
    pGrid.SelEndCol = pGrid.Cols - 1

End Sub

Sub lstPrim_Click ()
'
' If there are any items in the primary list box when
' a click event occurs, then SQLGetDetailRow is called
' to get all information on the selected author and put
' it in the form fields. MODE is set to SQLREST in order
' to prevent some change actions on the different fields.
' After the author is shown, MODE is set to SQLSHOW,
' indicating that the form is active (an author in it)

    If lstPrim.ListIndex <> -1 Then
        Mode = SQLREST
        SQLGetDetailRow
        Mode = SQLSHOW
    End If
    
End Sub

Sub MainButton_Click (index As Integer)
Dim x As Integer
'
' MainButton is a control array of push buttons.
' They may be clicked by the user directly or by
' menu choices where the users select a menu item
' and the menu item pushes a button by setting its
' Value property True.


    Select Case index
        Case 1              ' new
            ' Click button 4 to clear the fields:
            MainButton(4).Value = True
            ' Enable the cancel button:
            MainButton(7).Enabled = True
            ' Set MODE to SQLNEW to allow saving:
            Mode = SQLNEW
        Case 2              ' save
            ' Call the SAVE routine, who knows how
            ' to do inserts and updates:
            SQLSave
        Case 3              ' delete
            ' Call the SQLDelete routine:
            SQLDelete
        Case 4              ' clear form
            ClearForm
        Case 5              ' refresh
            ' Send the same Select statement as last was sent:
            SQLQuery "REFRESH"
        Case 6              ' query
            ' Send a Select statement based on examples given
            ' by filling in parts of the form:
            SQLQuery ""
        Case 7              ' cancel
            ' Reset to same as before any changes were made:
            If Mode = SQLSHOW Then
                Mode = SQLREST
                x = lstPrim.ListIndex
                lstPrim.ListIndex = -1
                lstPrim.ListIndex = x
                Mode = SQLSHOW
            Else
                ClearForm
                Mode = SQLREST
            End If
    End Select

End Sub

Sub RefreshFormFields ()
Dim x As Integer

    x = lstPrim.ListIndex
    lstPrim.ListIndex = -1
    lstPrim.ListIndex = x

End Sub

Function RowToListbox ()
'
' Building a string to be added to the listbox:

Dim lBoxString As String

    ' Last and First Name:
    lBoxString = RTrim$(SQLData(SelChannel, 1)) + ", " + SQLData(SelChannel, 2)
    ' Id:
    lBoxString = Left$(lBoxString + Space$(LISTWIDTH%), LISTWIDTH%) + SQLData(SelChannel, 3)
    RowToListbox = lBoxString

End Function

Sub SetMainButtons (pMode As Integer)
'
' Enable/Disable buttons in tool bar based on
' actual Mode:

    MainButton(1).Enabled = True
    MainButton(2).Enabled = False
    MainButton(4).Enabled = True
    MainButton(7).Enabled = False
    If pMode = SQLSHOW Then
        MainButton(3).Enabled = True
    Else
        MainButton(3).Enabled = False
    End If

End Sub

Sub SetNmbrofRowsPanels (pNmbrRows, pRemoved)
'
' Sets the right information for how many
' rows that have been read from the result
' set, and how many rows that have been
' removed from the listbox:

    If Len(panItemsRead.Caption) > 0 Then
        pNmbrRows = pNmbrRows + Val(panItemsRead.Caption)
    End If
    If Len(panItemsRemoved.Caption) > 0 Then
        pRemoved = Val(panItemsRemoved.Caption) + pRemoved
    End If
    panItemsRead.Caption = Str$(pNmbrRows) + " rows read"
    If pRemoved > 0 Then
        panItemsRemoved.Caption = Str$(pRemoved) + " rows removed"
    Else
        panItemsRemoved.Caption = ""
    End If

End Sub

Sub SpecifyGrid ()
'
' Specify the sub grid for titles
'

    grdTitles.Rows = 10
    grdTitles.Cols = 9
    grdTitles.Row = 0
    grdTitles.Col = 0
    grdTitles.Text = "Title id"
    grdTitles.ColWidth(0) = 750
    grdTitles.Col = 1
    grdTitles.Text = "Title"
    grdTitles.ColWidth(1) = 3500
    grdTitles.Col = 2
    grdTitles.Text = "Type"
    grdTitles.ColWidth(2) = 855
    grdTitles.Col = 3
    grdTitles.Text = "Price"
    grdTitles.ColWidth(3) = 645
    grdTitles.Col = 4
    grdTitles.Text = "Advance"
    grdTitles.ColWidth(4) = 960
    grdTitles.Col = 5
    grdTitles.Text = "Royalty"
    grdTitles.ColWidth(5) = 645
    grdTitles.Col = 6
    grdTitles.Text = "YTD sales"
    grdTitles.ColWidth(6) = 840
    grdTitles.Col = 7
    grdTitles.Text = "Notes"
    grdTitles.ColWidth(7) = 4050
    grdTitles.Col = 8
    grdTitles.Text = "Pub. date"
    grdTitles.ColWidth(8) = 1050
    
End Sub

Sub SQLDelete ()
'
' Create an appropriate delete statement, based on the actual
' record shown in the form. Ask the user to confirm the delete.
' If all is well: Send the delete statement:

Dim lCmd$, x As Integer, res%

    If Len(RTrim$(txtAuthors(1).Text)) = 0 Or Mode <> SQLSHOW Then
        Beep
        Exit Sub            ' Nothing to delete
    End If
    If Len(RTrim$(txtAuthors(1).Text)) > 0 Then
        lCmd$ = "Delete authors " + QualString
        ' Check if the variable QualString is blank - if so we can
        ' not allow any deletions
        If Len(RTrim$(QualString)) = 0 Then
            HandleEmptyQual
            screen.MousePointer = 0
            Exit Sub
        End If
        
        If MsgBox("Do you really want to delete this row?", 36, "Delete") = 6 Then
            ' Use the SQLComm function to perform the delete:
            screen.MousePointer = 11
            res% = SQLComm%(UpdChannel, lCmd$)
            If res% = SUCCEED% Then
                ' Remove record from form and set up form for continuation:
                Mode = SQLREST
                x = lstPrim.ListIndex
                ClearFields
                If x <> -1 Then lstPrim.RemoveItem x
                ClearGrid grdTitles
            End If
            screen.MousePointer = 0
        End If
    End If

End Sub

Sub SQLFillGrid (pGrid As Control, pChannel%)
'
' Filling then grid with data
'

Dim x As Integer

    pGrid.Row = 0: pGrid.Rows = 10
    Do
        res% = SQLNextRow(pChannel%)
        Select Case res%
        Case REGROW
            If pGrid.Row >= pGrid.Rows - 1 Then pGrid.Rows = pGrid.Rows + 1
            pGrid.Row = pGrid.Row + 1
            For x = 0 To pGrid.Cols - 1
                pGrid.Col = x
                pGrid.Text = SQLData(pChannel%, x + 1)
            Next
        Case NOMOREROWS
            pGrid.Col = 0
            pGrid.Row = 1
            Exit Do
        Case Else
            Exit Do        ' error message by ordinary VBSQL-error routine
        End Select
    Loop Until 1 = 0
' ------------------------------------------------

End Sub

Sub SQLGetDetailRow ()
'
' The user has selected an item in the primary list box.
' This routine creates and sends a SQL statement to
' retrieve all information on the selected author:

Dim lAu_Id$, lCmd$, res%, x As Integer

    screen.MousePointer = 11
    ' The AU_ID field is positioned beyond LISTWIDTH% in the list box item:
    lAu_Id$ = Mid$(lstPrim.List(lstPrim.ListIndex), LISTWIDTH% + 1)

    lCmd$ = "select au_id, au_fname, au_lname, address, zip, city, "
    lCmd$ = lCmd$ + "state, phone, contract "
    lCmd$ = lCmd$ + "from authors "
    lCmd$ = lCmd$ + "where au_id = " + Chr$(34) + lAu_Id$ + Chr$(34)
    lCmd$ = lCmd$ + " FOR BROWSE"
    
    ' Send the select statement and check the result:
    res% = SQLComm(UpdChannel, lCmd$)
    If res% = SUCCEED% Then
        res% = SQLNextRow(UpdChannel)
        QualString = sqlqual(UpdChannel, 1, "")
        If res% = REGROW Then
            ' Show each separate field:
            For x = 1 To 8
                txtAuthors(x).Text = SQLData(UpdChannel, x)
            Next
            chkContract.Value = SQLData(UpdChannel, 9)
        End If
    End If
    ' Check to see if the sub grid is showned - if so we will
    ' refresh it with data from the selected author
    If FormMaxOpen Then cmdSubGridDetail.Value = True
    screen.MousePointer = 0

End Sub

Sub SQLGetRows ()
'
' This routine loops through the result set and
' add rows to the listbox:


Dim lNmbrRows As Integer, lItems%, res%
Dim lNoMoreRowsToRead  As Integer, lRemoved As Integer

    lNoMoreRowsToRead = False
    For lNmbrRows = 1 To CHUNKSIZE%
        res% = SQLNextRow(SelChannel)
        If res% = REGROW Then
            lstPrim.AddItem RowToListbox()
        ElseIf res% = NOMOREROWS Then
            lNoMoreRowsToRead = True
            Exit For
        Else
            Exit For            ' error message by ordinary VBSQL-error routine
        End If
        If lstPrim.ListCount > LSTPRIMMAX% Then
            lstPrim.RemoveItem 0
            lRemoved = lRemoved + 1
        End If
    Next
    lNmbrRows = lNmbrRows - 1
    
    If lNoMoreRowsToRead Then          'no more rows to read from the result set
        cmdMoreRows.Enabled = False
    Else
        cmdMoreRows.Enabled = True
    End If
    
    SetNmbrofRowsPanels lNmbrRows, lRemoved

End Sub

Sub SQLInsert ()
'
' Create an Insert statement and send it to SQL Server:
'

Dim lCmd$, x As Integer, res%, lKey$

    screen.MousePointer = 11
    lCmd$ = "Insert authors ("
    lCmd$ = lCmd$ + "au_id, au_fname, au_lname, address, "
    lCmd$ = lCmd$ + "zip, city, state, phone, contract) "
    lCmd$ = lCmd$ + "values ("
    For x = 1 To 8      ' Evaluate the content of each field
        lCmd$ = lCmd$ + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
    Next
    lCmd$ = lCmd$ + Abs(chkContract.Value) + ")"
    
    ' Send to SQL Server and check result; Set up form after success:
    res% = SQLComm%(SelChannel, lCmd$)
    If res% = SUCCEED% Then
        Mode = SQLREST
        lKey$ = txtAuthors(1).Text
        MainButton(4).Value = True      ' Clear form
        txtAuthors(1).Text = lKey$      ' Set up query for inserted Author
        MainButton(6).Value = True      ' Send query
        Mode = SQLSHOW
    Else
        Mode = SQLREST
    End If
    lstPrim.SetFocus
    screen.MousePointer = 0
    
End Sub

Sub SQLQuery (pMode As String)
'
' Evaluate the form content for a QBE Select statement
' Send it to SQL Server. Read the result set and use it
' to populate the primary list box:

Dim lCmd$, lWhereClause$, res%

    screen.MousePointer = 11
    Mode = SQLREST
    panItemsRead.Caption = ""
    panItemsRemoved.Caption = ""
    If pMode = "REFRESH" Then
        lWhereClause$ = LastWhereClause$
    Else
        lWhereClause$ = EvaluateForm()
    End If
    lstPrim.Clear
    lCmd$ = "select au_lname, au_fname, au_id "
    lCmd$ = lCmd$ + "from authors "
    If Len(RTrim$(lWhereClause$)) Then
        lCmd$ = lCmd$ + "where " + lWhereClause$ + " "
    End If
    lCmd$ = lCmd$ + "order by au_lname, au_fname"
    
    res% = SQLComm(SelChannel, lCmd$)
    
    If res% = SUCCEED% Then
        SQLGetRows
    End If
    If lstPrim.ListCount > 0 Then
        lstPrim.ListIndex = 0           ' Autoclick on first in list box
        Mode = SQLSHOW
        SetMainButtons Mode
    Else
        Mode = SQLREST
    End If
    screen.MousePointer = 0

End Sub

Sub SQLSave ()
'
' Choose wether to create an insert or update statement based
' on the actual Mode:

    If Mode = SQLNEW Then
        SQLInsert
    Else
        SQLUpdate
    End If
    ' NOTE: Mode will be changed by SQLInsert/SQLUpdate
    SetMainButtons Mode

End Sub

Sub SQLUpdate ()
'
' Create an Update statement and send it to SQL Server:

Dim lCmd$, lRow$, x As Integer, res%

    screen.MousePointer = 11
    If Len(RTrim$(txtAuthors(1).Text)) > 0 Then
        lCmd$ = "Update authors set "
        For x = 2 To 8      ' Evaluate the content of each non key field
            Select Case x
                Case 2
                    lCmd$ = lCmd$ + "au_fname = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 3
                    lCmd$ = lCmd$ + "au_lname = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 4
                    lCmd$ = lCmd$ + "address = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 5
                    lCmd$ = lCmd$ + "zip = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 6
                    lCmd$ = lCmd$ + "city = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 7
                    lCmd$ = lCmd$ + "state = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
                Case 8
                    lCmd$ = lCmd$ + "phone = " + Chr$(34) + RTrim$(txtAuthors(x).Text) + Chr$(34) + ", "
            End Select
        Next
        lCmd$ = lCmd$ + "contract = " + Abs(chkContract.Value)
        lCmd$ = lCmd$ + " " + QualString
        ' Control to see if the variable QualString is blank - if so we can not allow any update
        If Len(RTrim$(QualString)) = 0 Then
            HandleEmptyQual
            screen.MousePointer = 0
            Exit Sub
        End If
        ' Send to SQL Server and check result; Set up form after success:
        res% = SQLComm%(UpdChannel, lCmd$)
        If res% = SUCCEED% Then
            Mode = SQLREST
            lRow$ = Left$(RTrim$(txtAuthors(3).Text) + ", " + txtAuthors(2).Text + Space$(LISTWIDTH%), LISTWIDTH%) + txtAuthors(1).Text
            ' Modify list box item to reflect possible changes from update:
            If lstPrim.ListIndex <> -1 Then     ' to prevent a VB error
                x = lstPrim.ListIndex
                lstPrim.RemoveItem x
                lstPrim.AddItem lRow$, x
                lstPrim.ListIndex = x
                Mode = SQLSHOW
            End If
        Else
            RefreshFormFields
        End If
    Else
        Beep
        MsgBox "The update operation was not successful.", 16
    End If
    screen.MousePointer = 0

End Sub

Sub SubGridClose ()
'
' Clears the grid and makes it invisible
'

    If Me.WindowState <> 2 Then
        Me.Height = DEFMINHEIGHT%
        CenterForm
    End If
    FormMaxOpen = False
    ClearGrid grdTitles
    frmTitles.Visible = False
    
End Sub

Sub txtAuthors_Change (index As Integer)
'
' If changes are made to any text field included in the
' control array of text boxes, and if MODE is anything
' else than SQLREST, then enable the save button and
' the cancel button. This makes it possible to save or
' cancel any modifications made:

    If Mode <> SQLREST Then
        MainButton(2).Enabled = True        ' save button
        MainButton(7).Enabled = True        ' cancel button
    End If

End Sub

Sub txtAuthors_GotFocus (index As Integer)

    ' Modification of key field prevented
    If Mode = SQLSHOW And index = 1 Then txtAuthors(index + 1).SetFocus
    ' Highlight existing entry
    txtAuthors(index).SelStart = 0
    txtAuthors(index).SelLength = Len(RTrim$(txtAuthors(index).Text))

End Sub

