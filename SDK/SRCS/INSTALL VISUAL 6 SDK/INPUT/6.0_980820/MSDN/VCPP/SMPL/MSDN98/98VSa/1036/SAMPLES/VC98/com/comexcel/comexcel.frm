VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2076
   ClientLeft      =   6432
   ClientTop       =   4620
   ClientWidth     =   2580
   LinkTopic       =   "Form1"
   ScaleHeight     =   2076
   ScaleWidth      =   2580
   Begin VB.CommandButton Command1 
      Caption         =   "GO!!"
      Height          =   495
      Left            =   720
      TabIndex        =   0
      Top             =   840
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub Command1_Click()
    Dim x As Excel.Application
    Set x = CreateObject("excel.application")
    x.Visible = True
    
    Dim Book As Excel.Workbook
    Set Book = x.Workbooks.Add(xlWorksheet)
    x.ActiveSheet.Name = "Market Share Percentages!"
        
    x.ActiveSheet.Range("A2").Value = "Company A"
    x.ActiveSheet.Range("B2").Value = "Company B"
    x.ActiveSheet.Range("C2").Value = "Company C"
    x.ActiveSheet.Range("D2").Value = "Company D"
    
    x.ActiveSheet.Range("A3").Value = 75
    x.ActiveSheet.Range("B3").Value = 14
    x.ActiveSheet.Range("C3").Value = 7
    x.ActiveSheet.Range("D3").Value = 4
    
    Dim Range As Excel.Range
    Set Range = x.ActiveSheet.Range("A2:D3")
    Book.Charts.Add.ChartWizard Range, xl3DPie, 7, xlRows, 1, 0, 2, "Market Share"
    
    Sleep 6000
    Book.Saved = True
    x.Quit
End Sub

