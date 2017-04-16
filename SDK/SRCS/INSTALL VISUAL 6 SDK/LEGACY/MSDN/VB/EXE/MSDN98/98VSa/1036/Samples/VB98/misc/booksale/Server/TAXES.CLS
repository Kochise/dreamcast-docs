VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Taxes"
Attribute VB_Creatable = True
Attribute VB_Exposed = False
Option Explicit

Public Function CalcNationalIncomeTax(cGrossSalary As Currency) As Currency
  frmBookSales.lblStatus(1).Caption = "Calcule le montant des taxes au niveau national."

    Select Case cGrossSalary
        Case Is <= 30000
            CalcNationalIncomeTax = cGrossSalary * 0.15

        Case cGrossSalary >= 30001 And cGrossSalary <= 60000
            CalcNationalIncomeTax = cGrossSalary * 0.28

        Case cGrossSalary >= 60001 And cGrossSalary <= 100000
            CalcNationalIncomeTax = cGrossSalary * 0.38

        Case cGrossSalary > 100000
            CalcNationalIncomeTax = cGrossSalary * 0.48

        Case Else
            CalcNationalIncomeTax = False

    End Select

End Function

Public Function CalcSalesTax(cGrossSalary As Currency, cYearToDate As Currency) As Currency
  
  frmBookSales.lblStatus(1).Caption = "Calcule la taxe sur les ventes estimées..."
      
    If cYearToDate > 58000 Then
      CalcSalesTax = 0
    
    Else
        CalcSalesTax = cGrossSalary * 0.0765
        
    End If
    
End Function

Public Function CalcRegionalIncomeTax(cGrossSalary As Currency, strState As String) As Currency

  frmBookSales.lblStatus(1).Caption = "Calcule le montant des taxes au niveau régional..."
    
    Select Case strState
      Case "PA"
        CalcRegionalIncomeTax = cGrossSalary * 0.028
        
      Case "WA"
        CalcRegionalIncomeTax = 0
          
      Case Else
        CalcRegionalIncomeTax = cGrossSalary * 0.022
            
    End Select
    
End Function

