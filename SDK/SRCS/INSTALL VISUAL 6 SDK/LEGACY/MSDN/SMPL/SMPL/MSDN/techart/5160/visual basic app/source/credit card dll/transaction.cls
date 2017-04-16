VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Transaction"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'<Private>------------------------------------------
Private Reason As String
'</Private>------------------------------------------

'--------------------------------------------------------------------------
'<Purpose> This method bills a credit card.  This is a stubbed out method
'          used for demonstrational purposes only.  If this were a real application
'          you would interface with something like a Commerce Server object
'          at this point (you would also need to pass in the amount to charge
'          to the card).
'
'          Note that all VBScript variables are variants (for multiplatform) that is why all
'          that is why all of the parameters are declared as variants.
'--------------------------------------------------------------------------
Public Function BillCard(CardType As Variant, CardHolder As Variant, CardNumber As Variant, ExpirationMonth As Variant, ExpirationYear As Variant) As Boolean
     On Error GoTo BillCardError:
     
     '---- Initialize Reason variable
     Reason = ""
     
     '---- Make sure they provided all the information
     If (Trim(CardType) = "") Then
        Reason = "credit card type was not provided"
     ElseIf (Trim(CardHolder) = "") Then
        Reason = "card holder name was not provided"
     ElseIf (Trim(CardNumber) = "") Then
        Reason = "card number was not provided"
     ElseIf (Trim(ExpirationMonth) = "") Then
        Reason = "card expiration month was not provided"
     ElseIf (ExpirationYear = "") Then
        Reason = "card expiration year was not provided"
     End If
     
     '---- If reason is not blank then they did not enter
     '---- all of the required information
     If (Reason <> "") Then GoTo BillCardError
     
     '---- Return true if they provided all the information
     BillCard = True
     Exit Function
    
BillCardError:
     BillCard = False

End Function

'--------------------------------------------------------------------------
'<Purpose> This method returns a string that describes the reason the credit
'          card transaction failed.  This is a stubbed out method used for
'          demonstrational purposes only.  It simply returns the classes
'          private variable Reason.
'--------------------------------------------------------------------------
Public Function GetTransactionFailureReason() As String

  On Error GoTo GetTransactionFailureReasonError:
  
  GetTransactionFailureReason = Reason
  Exit Function
  
GetTransactionFailureReasonError:
  GetTransactionFailureReason = ""

End Function
