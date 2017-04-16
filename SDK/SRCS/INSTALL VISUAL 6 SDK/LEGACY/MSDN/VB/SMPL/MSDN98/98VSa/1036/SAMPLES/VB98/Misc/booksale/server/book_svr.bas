Attribute VB_Name = "ServerMain"
Option Explicit
Public rsAuthors As ADODB.Recordset
Public rsTitles As ADODB.Recordset
Public rsBookPages As ADODB.Recordset
Public rsCOGS As ADODB.Recordset

Enum BOOKMODEL
  gintSCHOOL_BOOK_MODEL
  gintPOP_NOVEL_MODEL
  gintCELEBRITY_BIOGRAPHY_MODEL
End Enum

Public Const gRoyalty = 0.15
Public gintInstanceCount As Integer

Public gCN As ADODB.Connection

Public gDBName As String

Public gintSalesModel As Integer
Public glngUnitsPerMonth As Long
Public gcurCostPerUnit As Currency
Public gcurPromoCost As Currency
Public gsngIncomeTaxRate As Single
Public gintSalesPeriod As Integer
Public gbolIsDiscount As Boolean
Public gintPromoStart As Integer
Public gintPromoDiscPeriod As Integer
Public gsngPromoDiscRate As Single
Public gintPubProfit As Integer
Public gcurAdvertisingCost As Currency

Sub Main()

End Sub

Sub ServerMsg(rstrMessage As String, rintButtons As Integer, rstrTitle As String)
  #If gbDEBUG Then
    MsgBox rstrMessage, rintButtons, rstrTitle
  #End If
End Sub

