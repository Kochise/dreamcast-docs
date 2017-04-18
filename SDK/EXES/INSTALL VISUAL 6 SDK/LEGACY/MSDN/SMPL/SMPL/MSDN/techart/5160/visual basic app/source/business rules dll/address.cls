VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Address"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'<Private>-------------------------------------------
Private Reason As String
'</Private>-------------------------------------------

'--------------------------------------------------------------------------
'<Purpose> This method validates a shipping address.
'          This is by no means an exhaustive validation, it is primarily an
'          example of how to create the object and call the method from an
'          Active Server Page.
'
'
'          Note:  All variables passed by VBScript are variants (for multiplatform)
'                 That is why all the parameters for this method are declared
'                 as variants.
'--------------------------------------------------------------------------
Public Function IsValidShippingInformation(FirstName As Variant, LastName As Variant, Company As Variant, Email As Variant, Address1 As Variant, Address2 As Variant, City As Variant, State As Variant, Zip As Variant, Country As Variant, Phone As Variant, Comments As Variant) As Boolean
    On Error GoTo IsValidShippingInformationError:
    
    '---- Initialize the Class Reason variable
    Reason = ""
    
    '---- Verify that they provided the required fields
    If (Trim(FirstName) = "") Then
        Reason = "No first name was provided"
    ElseIf (Trim(LastName) = "") Then
        Reason = "No last name was provided"
    ElseIf (Trim(Address1) = "") Then
        Reason = "No address was provided"
    ElseIf (Trim(City) = "") Then
        Reason = "No city was provided"
    ElseIf (Trim(State) = "") Then
        Reason = "No state was provided"
    ElseIf (Trim(Zip) = "") Then
        Reason = "No zip code was provided"
    ElseIf (Trim(Phone) = "") Then
        Reason = "No phone number was provided"
    End If
  
  '---- If Reason is not blank they did not provide all the required information
  If (Reason <> "") Then GoTo IsValidShippingInformationError:
  
  '---- If they provided all the required information return true
  IsValidShippingInformation = True
  Exit Function

IsValidShippingInformationError:
  '---- If a runtime error occurred set reason to the error
  If Error$ <> "" Then Reason = Error$
  IsValidShippingInformation = False

End Function

'--------------------------------------------------------------------------
'<Purpose> This is simply a method for external classes / applications
'          to access the Reason variable.
'--------------------------------------------------------------------------
Public Function GetValidationFailureReason() As String
  On Error GoTo GetValidationFailureReasonError:
  
  GetValidationFailureReason = Reason
  Exit Function
  
GetValidationFailureReasonError:
    GetValidationFailureReason = ""
    Exit Function
    
End Function
