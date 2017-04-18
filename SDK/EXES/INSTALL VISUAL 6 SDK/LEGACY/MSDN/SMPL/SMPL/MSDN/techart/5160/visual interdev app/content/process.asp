<%@ LANGUAGE="vbscript" %>
<%'-------------------------------------------------------------------------------
' Microsoft Visual InterDev & Visual Basic Sample
' 
' This file is an Active Server Page that contains the processing logic
' for the sample billing application. The Active Server Page contains embedded
' server-side scripting (VBScript) that instantiates and calls into the the Visual Basic
' Billing and Credit components as server-side components. 
' The purpose of the page is to perform the processing of the user input entered 
' in the billing information HTML form so that the results can be displayed on
' any platform running any standard Web browser.  
'-------------------------------------------------------------------------------%>

<SCRIPT RUNAT=Server LANGUAGE="VBScript">

  '---- OLE Server Objects
  Dim ThisBusinessRule
  Dim ThisOrder

  '---- Shipping Information
  Dim FirstName
  Dim LastName
  Dim Company
  Dim Email
  Dim Address1
  Dim Address2
  Dim City
  Dim State
  Dim Zip
  Dim Country
  Dim Phone
  Dim Comments

  '---- Billing Information
  Dim CardType
  Dim CardHolder
  Dim CardNumber
  Dim ExpirationMonth
  Dim ExpirationYear

  '--------------------------------------------------------------------------
  ' Purpose: Creates our VB OLE Server objects using Internet Information Server
  '--------------------------------------------------------------------------
  Function CreateOLEServerObjects()
   'This line has been commented out vs. Visual Basic App
   'On Error Resume Next
    If Err.Number > 0 Then Err.Clear
  
    '---- Create the business rules object 
    Set ThisBusinessRule = Server.CreateObject("BusinessRules.Address")

    '---- Create the credit card transaction object
    Set ThisOrder = Server.CreateObject("CreditCard.Transaction")

    If Err.Number > 0 Then 
      CreateOLEServerObjects = False
    Else
      CreateOLEServerObjects = True
    End If

    Exit Function

  End Function

  '--------------------------------------------------------------------------
  ' Purpose: Destroys our VB OLE Server objects 
  '--------------------------------------------------------------------------
  Function DestroyOLEServerObjects()
    On Error Resume Next

    '---- Destroy the business rules object 
    Set ThisBusinessRule = Nothing

    '---- Destroy the credit card transaction object
    Set ThisOrder = Nothing

    DestroyOLEServerObjects = True
    Exit Function

  End Function

  '--------------------------------------------------------------------------
  'Purpose: Validates the shipping information provided by the user using 
  '               a VB OLE Server via Internet Information Server
  '--------------------------------------------------------------------------
  Function ValidateShippingInformation()
    On Error Resume Next

    Dim IsValid

    If Err.Number > 0 Then Err.Clear

    '---- Call the Business rule method that validates the shipping information
    IsValid = ThisBusinessRule.IsValidShippingInformation(FirstName, LastName, Company, Email, Address1, Address2, City, State, Zip, Country, Phone, Comments)

    '---- Return whether the information was valid
    ValidateShippingInformation = IsValid

    '---- If we encountered an error then invalid
    If Err.Number > 0 Then ValidateShippingInformation = False

    Exit Function

  End Function

  '--------------------------------------------------------------------------
  ' Purpose: Gets the message that describes the reason for the 
  '                shipping address validation failure
  '--------------------------------------------------------------------------
  Function GetShippingValidationFailure()
    On Error Resume Next

    Dim Reason

    Reason = ""
    Reason = ThisBusinessRule.GetValidationFailureReason()

    GetShippingValidationFailure = Reason
    Exit Function

  End Function

  '--------------------------------------------------------------------------
  ' Purpose: Processes a credit card order using a VB OLE Server via
  '                Internet Information Server
  '--------------------------------------------------------------------------
  Function BillCreditCard()
    On Error Resume Next

    Dim OrderProcessed

    If Err.Number > 0 Then Err.Clear


    '---- Process the order using the credit card object
    OrderProcessed = ThisOrder.BillCard(CardType, CardHolder, CardNumber, ExpirationMonth, ExpirationYear) 

    '---- Return whether the card was successfully billed
    BillCreditCard = OrderProcessed

    '---- If we encountered an error then invalid
    If Err.Number > 0 Then BillCreditCard = False

    Exit Function

  End Function

  '--------------------------------------------------------------------------
  ' Purpose: Gets the message that describes the reason for the credit card 
  '                processing failure
  '--------------------------------------------------------------------------
  Function GetCreditCardProcessingFailure()
    On Error Resume Next

    Dim Reason

    Reason = ""
    Reason = ThisOrder.GetTransactionFailureReason()

    GetCreditCardProcessingFailure = Reason
    Exit Function

  End Function

'--------------------------------------------------------------------------
' Purpose: Validates shipping data input by the user.  If the data is valid 
'                credit card is billed for the order.
'--------------------------------------------------------------------------
 Sub Main
    On Error Resume Next

    '---- Boolean for checking function return values
    Dim ReturnValue

    '---- String to display reason for failure to the user
    Dim Reason

    '---- Create our server objects
    ReturnValue = CreateOLEServerObjects()
    If ReturnValue = False Then 
	ReturnValue = DestroyOLEServerObjects()
    Response.Write("An error has occurred in the processing of your order.<br>")
    Response.Write("Unable to create one or more server components.<br>")
    Response.Write("Make sure the credit object (creditcard.dll) and business object (businessrules.dll) have been properly registered on the Web server.<br>")

	Exit Sub
	End If

    '---- Get information passed by the html submit process

    '---- Shipping information
    FirstName = Request.Form("txtFirstName")
    LastName = Request.Form("txtLastName")
    Company = Request.Form("txtCompany")
    Email = Request.Form("txtEmail")
    Address1 = Request.Form("txtAddress1")
    Address2 = Request.Form("txtAddress2")
    City = Request.Form("txtCity")
    State = Request.Form("txtState")
    Zip = Request.Form("txtZip")
    Country = Request.Form("txtCountry")
    Phone = Request.Form("txtPhone")
    Comments = Request.Form("txtComments")

    '---- Credit Card Information
    CardType = Request.Form("cboCardType")
    CardHolder = Request.Form("txtCardHolder")
    CardNumber = Request.Form("txtCardNumber")
    ExpirationMonth = Request.Form("cboExpirationMonth")
    ExpirationYear = Request.Form("cboExpirationYear")


    '---- Validate the shipping information
    ReturnValue = ValidateShippingInformation()

    If ReturnValue Then

      '---- Bill the customers credit card
      ReturnValue = BillCreditCard()

      If ReturnValue Then

        '---- Let the user know their order was placed.

       Response.Write("Your order has been successfully processed.")
      Else

        '---- Find out why the credit card processing failed

        Reason = GetCreditCardProcessingFailure()

        If Reason =  "" Then
          Reason = "We were unable to process your credit card transaction.  Your order cannot be processed at this time."
        Else
          Reason = "Your credit card transaction could not be processed for the following reason: " & Reason & ". Your order cannot be processed at this time."
        End If

        Response.Write(Reason)
      End If
    Else

      '---- Find out why the validation failed
      Reason = GetShippingValidationFailure()
      
      If Reason =  "" Then
        Reason = "We were unable to validate your shipping information.  Make sure that you provide your name, address and phone number.  Your order cannot be processed at this time."
      Else
        Reason = "Your shipping information could not be processed for the following reason: " & Reason & ". Make sure that you provide your name, address and phone number.  Your order cannot be processed at this time."
      End If

      Response.Write(Reason)
    End If

    '---- Destroy the objects that we created
    ReturnValue = DestroyOLEServerObjects()
 End Sub
</Script>

<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual InterDev 1.0">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE>Process Order</TITLE>
</HEAD>
<Body bgcolor="#FFFFFF">
<p align="Left"><img src="shipping.gif"></p><br>
Processing Your Order, please wait....<p>
<%
'----Start of processing --------------------------------------
 Call Main()  
%>
<p>
<p>
<a href="billing_information.htm">Back to Billing Information Page</a></p>
</BODY>
</HTML>
