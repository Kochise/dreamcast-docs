Attribute VB_Name = "General"
Option Explicit
  
'<Public>------------------------------------------
'---- business rules object
Public ThisBusinessRule     As Object

'---- credit card transaction object
Public ThisOrder            As Object
'</Public>------------------------------------------

'--------------------------------------------------------------------------
'<Purpose> This is the startup routine for the application
'--------------------------------------------------------------------------
Public Sub Main()
    Dim ReturnValue As Boolean
    
    '---- Create the VB Ole server objects
    ReturnValue = CreateOLEServerObjects()
    
    '---- Load the form
    Load frmBilling
    
    '---- Load the credit card types
    ReturnValue = LoadCardTypes(frmBilling.cboCardType)
    'If Not ReturnValue Then
    
    '---- Load the expiration information
    ReturnValue = LoadCardExpirationInformation(frmBilling.cboExpirationMonth, frmBilling.cboExpirationYear)
    'If Not ReturnValue Then
    
    '---- Show the form
    frmBilling.Show
    
End Sub

'--------------------------------------------------------------------------
'<Purpose> This function loads credit card types
'--------------------------------------------------------------------------
Public Function LoadCardTypes(ThisCombo As ComboBox) As Boolean
    On Error GoTo LoadCardTypesError:
  
    ThisCombo.AddItem "Visa"
    ThisCombo.AddItem "MasterCard"
    ThisCombo.ListIndex = 0
  
    LoadCardTypes = True
    Exit Function
  
LoadCardTypesError:
    LoadCardTypes = False

End Function

'--------------------------------------------------------------------------
'<Purpose> This function loads the months and years into the expiration date
'          combos.
'--------------------------------------------------------------------------
Public Function LoadCardExpirationInformation(ThisMonth As ComboBox, ThisYear As ComboBox) As Boolean
    On Error GoTo LoadCardExpirationInformationError:
  
    '---- Load the Months
    ThisMonth.AddItem "Jan"
    ThisMonth.AddItem "Feb"
    ThisMonth.AddItem "Mar"
    ThisMonth.AddItem "Apr"
    ThisMonth.AddItem "May"
    ThisMonth.AddItem "Jun"
    ThisMonth.AddItem "Jul"
    ThisMonth.AddItem "Aug"
    ThisMonth.AddItem "Sep"
    ThisMonth.AddItem "Oct"
    ThisMonth.AddItem "Nov"
    ThisMonth.AddItem "Dec"
    
    ThisMonth.ListIndex = 0
    
    '---- Load the Years
    ThisYear.AddItem "1997"
    ThisYear.AddItem "1998"
    ThisYear.AddItem "1999"
    ThisYear.AddItem "2000"
    ThisYear.AddItem "2001"
    ThisYear.AddItem "2002"
    ThisYear.AddItem "2003"
    ThisYear.AddItem "2004"
    
    ThisYear.ListIndex = 0
        
    LoadCardExpirationInformation = True
    Exit Function
    
LoadCardExpirationInformationError:
    LoadCardExpirationInformation = False

End Function

'--------------------------------------------------------------------------
'<Purpose> Creates our VB OLE Server objects
'--------------------------------------------------------------------------
Public Function CreateOLEServerObjects() As Boolean
    On Error GoTo CreateOLEServerObjectsError:

    '---- Create the business rules object
    Set ThisBusinessRule = CreateObject("BusinessRules.Address")
      
    
       
    '---- Create the credit card transaction object
    Set ThisOrder = CreateObject("CreditCard.Transaction")

    CreateOLEServerObjects = True
    Exit Function
    
CreateOLEServerObjectsError:
    CreateOLEServerObjects = False

End Function

'--------------------------------------------------------------------------
'<Purpose> Destroys our VB OLE Server objects
'--------------------------------------------------------------------------
Public Function DestroyOLEServerObjects() As Boolean
    On Error GoTo DestroyOLEServerObjectsError:

    '---- Destroy the business rules object
    Set ThisBusinessRule = Nothing

    '---- Destroy the credit card transaction object
    Set ThisOrder = Nothing
    
    DestroyOLEServerObjects = True
    Exit Function
    
DestroyOLEServerObjectsError:
    DestroyOLEServerObjects = False
    Exit Function
End Function

'--------------------------------------------------------------------------
'<Purpose> Destroys any objects we create and exits the application
'--------------------------------------------------------------------------
Public Function ShutdownApplication() As Boolean
    Dim ReturnValue As Boolean
    
    On Error Resume Next
  
    '---- Destroy objects
    ReturnValue = DestroyOLEServerObjects()
    
    '---- Destroy the form
    Set frmBilling = Nothing
    
    '---- End Program
    End
    
End Function

'--------------------------------------------------------------------------
'<Purpose> Validates the shipping information provided by the user using
'          a VB OLE Server
'--------------------------------------------------------------------------
Public Function ValidateShippingInformation(FirstName As String, LastName As String, Company As String, Email As String, Address1 As String, Address2 As String, City As String, State As String, Zip As String, Country As String, Phone As String, Comments As String)
    Dim IsValid As Boolean
    
    On Error GoTo ValidateShippingInformationError:

    '---- Call the Business rule method that validates the shipping information
    IsValid = ThisBusinessRule.IsValidShippingInformation(FirstName, LastName, Company, Email, Address1, Address2, City, State, Zip, Country, Phone, Comments)
    
    '---- Return whether the information was valid
    ValidateShippingInformation = IsValid
    Exit Function
    
ValidateShippingInformationError:
    If (Error <> "") Then
        MsgBox "The following error occurred validating the shipping information: " & Error, vbOKOnly + vbInformation
    End If
    
    ValidateShippingInformation = False
    
End Function

'--------------------------------------------------------------------------
'<Purpose> Gets the message that describes the reason for the shipping
'          address validation failure
'--------------------------------------------------------------------------
Public Function GetShippingValidationFailure()
    On Error GoTo GetShippingValidationFailureError:

    Dim Reason As String

    '---- Get the reason from the business rules object
    Reason = ""
    Reason = ThisBusinessRule.GetValidationFailureReason()

    GetShippingValidationFailure = Reason
    Exit Function

GetShippingValidationFailureError:
    If (Error <> "") Then
        MsgBox "The following error occurred retrieving the shipping validation error: " & Error, vbOKOnly + vbInformation
    End If
    
    GetShippingValidationFailure = ""

End Function

'--------------------------------------------------------------------------
'<Purpose> Processes a credit card order using a VB OLE Server
'--------------------------------------------------------------------------
Public Function BillCreditCard(CardType As String, CardHolder As String, CardNumber As String, ExpirationMonth As String, ExpirationYear As String) As Boolean
    Dim OrderProcessed As Boolean
    
    On Error GoTo BillCreditCardError:


    '---- Process the order using the credit card object
    OrderProcessed = ThisOrder.BillCard(CardType, CardHolder, CardNumber, ExpirationMonth, ExpirationYear)

    '---- Return whether or not the card was successfully billed
    BillCreditCard = OrderProcessed

    Exit Function
    
BillCreditCardError:
    If (Error <> "") Then
        MsgBox "The following error occurred while attempting to bill the credit card: " & Error, vbOKOnly + vbInformation
    End If
    
    BillCreditCard = False

End Function

'--------------------------------------------------------------------------
'<Purpose> Gets the message that describes the reason for the credit card
'          processing failure
'--------------------------------------------------------------------------
Public Function GetCreditCardProcessingFailure() As String
    Dim Reason As String
    
    On Error GoTo GetCreditCardProcessingFailureError:

    '---- Get the reason from the Credit card object
    Reason = ""
    Reason = ThisOrder.GetTransactionFailureReason()

    GetCreditCardProcessingFailure = Reason
    Exit Function

GetCreditCardProcessingFailureError:
    If (Error <> "") Then
        MsgBox "The following error occurred while retrieving the transaction failure reason: " & Error, vbOKOnly + vbInformation
    End If
    
    GetCreditCardProcessingFailure = ""

End Function
