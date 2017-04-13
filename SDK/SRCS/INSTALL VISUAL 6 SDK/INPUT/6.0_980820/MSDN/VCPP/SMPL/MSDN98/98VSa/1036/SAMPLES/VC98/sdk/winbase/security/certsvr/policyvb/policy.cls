VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Policy"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Private Const szOID_TEST1 As String = "0.1.2.3.4.5.6.0"
Private Const szOID_TEST2 As String = "0.1.2.3.4.5.6.1"
Private Const szOID_TEST3 As String = "0.1.2.3.4.5.6.2"

Public Function Initialize( _
    strConfig As String)
End Function

Public Function ShutDown()
End Function

Public Function GetDescription() As String
    GetDescription = "Property Form VB U/I Test Policy Module"
End Function

Public Function VerifyRequest( _
    strConfig As String, _
    Context As Long, _
    bNewRequest As Long, _
    Flags As Long) As Long
    
    Dim Str As String
    Dim PolicyForm As policyvb
    Dim CertServer As CCertServerPolicy
    Dim StringArray As CCertEncodeStringArray
    Dim SampleStructure1 As CCertEncodeSampleStructure1
    Dim Extension As String
    Dim NotBefore As Date
    Dim NotAfter As Date
    
    Set CertServer = New CCertServerPolicy
    Set StringArray = New CCertEncodeStringArray
    Set SampleStructure1 = New CCertEncodeSampleStructure1
    Set PolicyForm = New policyvb
    
    CertServer.SetContext Context
     
    'Collect user information from the request:
    Str = CertServer.GetRequestProperty(wszPROPSUBJECTDOT & wszPROPCOMMONNAME, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPCOMMONNAME, PROPTYPE_STRING, Str
    End If
    PolicyForm.NameText.Text = Str

    Str = CertServer.GetRequestAttribute(wszCERT_VERSION)
    PolicyForm.VersionText.Text = Str
    
    Str = CertServer.GetRequestAttribute(wszCERT_TYPE)
    PolicyForm.RequestTypeText.Text = Str
    
    Str = CertServer.GetCertificateProperty(wszPROPSUBJECTDOT & wszPROPORGANIZATION, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPORGANIZATION, PROPTYPE_STRING, Str
    End If
    PolicyForm.OrgText.Text = Str
    
    Str = CertServer.GetCertificateProperty(wszPROPSUBJECTDOT & wszPROPORGUNIT, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPORGUNIT, PROPTYPE_STRING, Str
    End If
    PolicyForm.OrgUnitText.Text = Str
    
    Str = CertServer.GetCertificateProperty(wszPROPSUBJECTDOT & wszPROPLOCALITY, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPLOCALITY, PROPTYPE_STRING, Str
    End If
    PolicyForm.LocalityText.Text = Str
    
    Str = CertServer.GetCertificateProperty(wszPROPSUBJECTDOT & wszPROPSTATE, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPSTATE, PROPTYPE_STRING, Str
    End If

    Str = CertServer.GetCertificateProperty(wszPROPSUBJECTDOT & wszPROPCOUNTRY, PROPTYPE_STRING)
    If (Len(Str) <> 0) Then
        CertServer.SetCertificateProperty wszPROPSUBJECTDOT & wszPROPCOUNTRY, PROPTYPE_STRING, Str
    End If
    PolicyForm.CountryText.Text = Str
    
    NotBefore = CertServer.GetCertificateProperty(wszPROPCERTIFICATENOTBEFOREDATE, PROPTYPE_DATE)
    PolicyForm.NotBeforeText.Text = CStr(NotBefore)
    
    NotAfter = CertServer.GetCertificateProperty(wszPROPCERTIFICATENOTAFTERDATE, PROPTYPE_DATE)
    PolicyForm.NotAfterText.Text = CStr(NotAfter)
    
    StringArray.Reset 3, CERT_RDN_IA5_STRING
    StringArray.SetValue 0, "VB Test String 1"
    StringArray.SetValue 1, "VB Test String 2"
    StringArray.SetValue 2, "VB Test String 3"
    Extension = StringArray.Encode
    
    CertServer.SetCertificateExtension _
            szOID_TEST1, _
            PROPTYPE_BINARY, _
            EXTENSION_DISABLE_FLAG, _
            Extension
            
    CertServer.SetCertificateExtension _
            szOID_TEST2, _
            PROPTYPE_STRING, _
            EXTENSION_CRITICAL_FLAG, _
            "http://UrlTest.htm"
            
    Extension = SampleStructure1.Encode( _
            "SampleStructure1 String1", _
            "SampleStructure1 String2", _
            39, _
            "BinaryBlob", _
            Now + 1)
            
    CertServer.SetCertificateExtension _
            szOID_TEST3, _
            PROPTYPE_BINARY, _
	    0, _
            Extension
    
    'If instructed to do so, grant/deny certificates after 3 second timer expires
    If (Flags) Then PolicyForm.DisplayTimer.Enabled = True
    
    If (StrComp("US", PolicyForm.CountryText.Text, 1) <> 0) Then
        PolicyForm.StatusText.Text = "Request denied; Country must be US!"
        PolicyForm.StatusText.Font.Bold = True
        PolicyForm.CountryText.Font.Strikethrough = True
        PolicyForm.cmdIssue.Enabled = False
        PolicyForm.cmdPending.Enabled = False
    Else
        PolicyForm.StatusText.Text = "Request is acceptable"
    End If
    
    'Display the user information and collect the response:
    PolicyForm.Show 1
    
    'assume VR_INSTANT_BAD:
    VerifyRequest = VR_INSTANT_BAD
        
    'if certificate was accepted or the U/I timed out, and it is acceptable,
    'return VR_INSTANT_OK:
    If (PolicyForm.cmdIssue.Enabled) Then
        If (StrComp("Deny", PolicyForm.Disposition.Text) <> 0) Then
            If (StrComp("Pending", PolicyForm.Disposition.Text) = 0) Then
                VerifyRequest = VR_PENDING
            Else
                ' "TimeOut" or "Issue":
                VerifyRequest = VR_INSTANT_OK
            End If
        End If
    End If
    Set PolicyForm = Nothing
    Set CertServer = Nothing
    Set StringArray = Nothing
    Set SampleStructure1 = Nothing
End Function

