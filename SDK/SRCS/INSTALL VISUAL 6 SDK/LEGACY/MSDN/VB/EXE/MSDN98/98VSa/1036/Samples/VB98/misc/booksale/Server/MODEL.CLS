VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Model"
Attribute VB_Creatable = True
Attribute VB_Exposed = False
Option Explicit

Function intGetMonthSales(intCurMonth As Integer, intSalesPeriod As Integer, intModelType As Integer) As Integer
  Dim intMonthSales As Integer
  Const intMAX_SCHOOL_BOOK = 2
  Const intMAX_POP_NOVEL = 7
  Const intMAX_CELEBRITY = 8
    
  Select Case intModelType
    Case gintSCHOOL_BOOK_MODEL
        intMonthSales = intMAX_SCHOOL_BOOK
        
    Case gintPOP_NOVEL_MODEL
        intMonthSales = -((intCurMonth - intSalesPeriod / 2) ^ 2 - intMAX_POP_NOVEL)
        
    Case gintCELEBRITY_BIOGRAPHY_MODEL
        intMonthSales = -((intCurMonth - intSalesPeriod / 4) ^ 2 - intMAX_CELEBRITY)
  
  End Select

  If intMonthSales < 0 Then
    intGetMonthSales = 0
    
  Else
    intGetMonthSales = intMonthSales
    
  End If
  
End Function

