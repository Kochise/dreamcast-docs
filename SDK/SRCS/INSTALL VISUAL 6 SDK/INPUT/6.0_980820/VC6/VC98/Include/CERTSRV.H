//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1997.
//
//  File:       CertSrv.h
//  Contents:   Main Certificate Server header
//              Also includes .h files for the COM interfaces
//
//----------------------------------------------------------------------------

#if !defined( _CERTSRV_H_ )
#define _CERTSRV_H_

#include <certadm.h>
#include <certcli.h>
#include <certenc.h>
#include <certexit.h>
#include <certif.h>
#include <certpol.h>

#ifndef DBG_CERTSRV
# if defined(_DEBUG)
#  define DBG_CERTSRV     1
# elif defined(DBG)
#  define DBG_CERTSRV     DBG
# else
#  define DBG_CERTSRV     0
# endif
#endif


#define wszSERVICE_NAME		TEXT("CertSvc")

#define wszREGKEYBASE		TEXT("SYSTEM\\CurrentControlSet\\Services\\") \
				wszSERVICE_NAME

//======================================================================
// Full path to "CertSvc\Configuration\":
#define wszREGKEYCONFIGCANAME	wszREGKEYBASE TEXT("\\") \
				wszREGKEYCONFIG TEXT("\\")

//======================================================================
// Key Under "CertSvc":
#define wszREGKEYCONFIG		TEXT("Configuration")


//======================================================================
// Values Under "CertSvc\Configuration":
#define wszREGKEYDIRECTORY	TEXT("ConfigurationDirectory")
#define wszREGKEYDEFAULTCONFIG	TEXT("DefaultConfiguration")


//======================================================================
// Values Under "CertSvc\Configuration\<CAName>":
#define wszREGCERTENROLLCOMPATIBLE TEXT("CertEnrollCompatible")
#define wszREGKEYENABLED	TEXT("Enabled")
#define wszREGCONTAINERNAME     TEXT("KeySetName")
#define wszREGNAMESEPARATOR     TEXT("SubjectNameSeparator")
#define wszREGPOLICYFLAGS	TEXT("PolicyFlags")
#define wszREGSUBJECTTEMPLATE	TEXT("SubjectTemplate")
#define wszREGSUBJECTALTNAME	TEXT("SubjectAltName")
#define wszREGSUBJECTALTNAME2	TEXT("SubjectAltName2")
#define wszREGREVOCATIONCRLURL	TEXT("RevocationCRLURL")
#define wszREGREVOCATIONTYPE	TEXT("RevocationType")
#define wszREGREVOCATIONURL	TEXT("RevocationURL")
#define wszREGNETSCAPECERTTYPE  TEXT("NetscapeCertType")
#define wszREGDURATIONPERIOD	TEXT("ValidityPeriod")
#define wszREGDURATIONUNITS	TEXT("ValidityPeriodUnits")

#define szREGDBDSN		"DBDSN"
#define szREGDBUSER		"DBUser"
#define szREGDBPASSWORD		"DBPassword"

#define wszREGDBDSN		TEXT(szREGDBDSN)
#define wszREGDBUSER		TEXT(szREGDBUSER)
#define wszREGDBPASSWORD	TEXT(szREGDBPASSWORD)


//======================================================================
// Keys Under "CertSvc\Configuration\<CAName>":
#define wszREGKEYNAMES		TEXT("Names")
#define wszREGCSP		TEXT("CSP")


//======================================================================
// Values Under "CertSvc\Configuration\<CAName>\Names":
#define wszREGNAMEDEFAULT	TEXT("*")


//======================================================================
// Values Under "CertSvc\Configuration\<CAName>\CSP":
#define wszREGPROVIDERTYPE    TEXT("ProviderType");
#define wszREGPROVIDER        TEXT("Provider");
#define wszHASHALGORITHM      TEXT("HashAlgorithm");
#define wszMACHINEKEYSET      TEXT("MachineKeyset");


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\SubjectNameSeparator":
#define szNAMESEPARATORDEFAULT   ","
#define wszNAMESEPARATORDEFAULT   TEXT(szNAMESEPARATORDEFAULT)


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\RevocationType":
#define wszREVTYPE_CRL		TEXT("CRL")
#define wszREVTYPE_NETSCAPE	TEXT("Netscape")


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\ValidityPeriod":
#define wszDURATIONUNITSYEARS	TEXT("Years")
#define wszDURATIONUNITSMONTHS	TEXT("Months")
#define wszDURATIONUNITSWEEKS	TEXT("Weeks")
#define wszDURATIONUNITSDAYS	TEXT("Days")
#define wszDURATIONUNITSHOURS	TEXT("Hours")
#define wszDURATIONUNITSMINUTES	TEXT("Minutes")
#define wszDURATIONUNITSSECONDS	TEXT("Seconds")

//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\HierFileName":
#define wszRegHierFileName		TEXT("HierFileName")


#define wszCLASS_CERTADMIN	  TEXT("CertificateAuthority.Admin")
#define wszCLASS_CERTCONFIG	  TEXT("CertificateAuthority.Config")
#define wszCLASS_CERTGETCONFIG	  TEXT("CertificateAuthority.GetConfig")
#define wszCLASS_CERTENCODE	  TEXT("CertificateAuthority.Encode")
#define wszCLASS_CERTEXIT	  TEXT("CertificateAuthority.Exit")
#define wszCLASS_CERTPOLICY	  TEXT("CertificateAuthority.Policy")
#define wszCLASS_CERTREQUEST	  TEXT("CertificateAuthority.Request")
#define wszCLASS_CERTSERVEREXIT	  TEXT("CertificateAuthority.ServerExit")
#define wszCLASS_CERTSERVERPOLICY TEXT("CertificateAuthority.ServerPolicy")


//+--------------------------------------------------------------------------
// Name properties:

#define wszPROPDISTINGUISHEDNAME TEXT("DistinguishedName")
#define wszPROPRAWNAME           TEXT("RawName")
#define wszPROPNAMETYPE          TEXT("NameType")
#define wszPROPCOUNTRY           TEXT("Country")
#define wszPROPORGANIZATION      TEXT("Organization")
#define wszPROPORGUNIT           TEXT("OrgUnit")
#define wszPROPCOMMONNAME        TEXT("CommonName")
#define wszPROPLOCALITY          TEXT("Locality")
#define wszPROPSTATE             TEXT("State")
#define wszPROPTITLE             TEXT("Title")
#define wszPROPGIVENNAME         TEXT("GivenName")
#define wszPROPINITIALS          TEXT("Initials")
#define wszPROPSURNAME           TEXT("SurName")
#define wszPROPDOMAINCOMPONENT   TEXT("DomainComponent")
#define wszPROPEMAIL             TEXT("EMail")

//+--------------------------------------------------------------------------
// Subject Name properties:

#define wszPROPSUBJECTDOT	    TEXT("Subject.")
#define wszPROPSUBJECTDISTINGUISHEDNAME \
				    wszPROPSUBJECTDOT wszPROPDISTINGUISHEDNAME
#define wszPROPSUBJECTRAWNAME       wszPROPSUBJECTDOT wszPROPRAWNAME
#define wszPROPSUBJECTNAMETYPE      wszPROPSUBJECTDOT wszPROPNAMETYPE
#define wszPROPSUBJECTCOUNTRY       wszPROPSUBJECTDOT wszPROPCOUNTRY
#define wszPROPSUBJECTORGANIZATION  wszPROPSUBJECTDOT wszPROPORGANIZATION
#define wszPROPSUBJECTORGUNIT       wszPROPSUBJECTDOT wszPROPORGUNIT
#define wszPROPSUBJECTCOMMONNAME    wszPROPSUBJECTDOT wszPROPCOMMONNAME
#define wszPROPSUBJECTLOCALITY      wszPROPSUBJECTDOT wszPROPLOCALITY
#define wszPROPSUBJECTSTATE         wszPROPSUBJECTDOT wszPROPSTATE
#define wszPROPSUBJECTTITLE	    wszPROPSUBJECTDOT wszPROPTITLE
#define wszPROPSUBJECTGIVENNAME	    wszPROPSUBJECTDOT wszPROPGIVENNAME
#define wszPROPSUBJECTINITIALS	    wszPROPSUBJECTDOT wszPROPINITIALS
#define wszPROPSUBJECTSURNAME	    wszPROPSUBJECTDOT wszPROPSURNAME
#define wszPROPSUBJECTDOMAINCOMPONENT wszPROPSUBJECTDOT wszPROPDOMAINCOMPONENT
#define wszPROPSUBJECTEMAIL	    wszPROPSUBJECTDOT wszPROPEMAIL

#define wszPROPSUBJECTCOUNTRYOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_COUNTRY_NAME)

#define wszPROPSUBJECTORGANIZATIONOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_ORGANIZATION_NAME)

#define wszPROPSUBJECTORGUNITOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_ORGANIZATIONAL_UNIT_NAME)

#define wszPROPSUBJECTCOMMONNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_COMMON_NAME)

#define wszPROPSUBJECTLOCALITYOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_LOCALITY_NAME)

#define wszPROPSUBJECTSTATEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_STATE_OR_PROVINCE_NAME)

#define wszPROPSUBJECTTITLEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_TITLE)

#define wszPROPSUBJECTGIVENNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_GIVEN_NAME)

#define wszPROPSUBJECTINITIALSOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_INITIALS)

#define wszPROPSUBJECTSURNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_SUR_NAME)


//+--------------------------------------------------------------------------
// For mapping request attribute names to internal property names:

// Map to wszPROPSUBJECTCOMMONNAME:
#define wszATTRCOMMONNAME1		TEXT("CN")
#define wszATTRCOMMONNAME2		TEXT("CommonName")

// Map to wszPROPSUBJECTLOCALITY:
#define wszATTRLOCALITY1		TEXT("L")
#define wszATTRLOCALITY2		TEXT("Locality")

// Map to wszPROPSUBJECTSTATE:
#define wszATTRSTATE1			TEXT("S")
#define wszATTRSTATE2			TEXT("State")

// Map to wszPROPSUBJECTCOUNTRY:
#define wszATTRCOUNTRY1			TEXT("C")
#define wszATTRCOUNTRY2			TEXT("Country")

// Map to wszPROPSUBJECTORGANIZATION:
#define wszATTRORG1			TEXT("O")
#define wszATTRORG2			TEXT("Org")
#define wszATTRORG3			TEXT("Organization")

// Map to wszPROPSUBJECTORGUNIT:
#define wszATTRORGUNIT1			TEXT("OU")
#define wszATTRORGUNIT2			TEXT("OrgUnit")
#define wszATTRORGUNIT3			TEXT("OrganizationUnit")
#define wszATTRORGUNIT4			TEXT("OrganizationalUnit")

// Map to wszPROPSUBJECTDOMAINCOMPONENT:
#define wszATTRDOMAINCOMPONENT1		TEXT("DC")
#define wszATTRDOMAINCOMPONENT2		TEXT("DomainComponent")

// Map to wszPROPSUBJECTEMAIL:
#define wszATTREMAIL1			TEXT("E")
#define wszATTREMAIL2			TEXT("EMail")


//+--------------------------------------------------------------------------
// Request properties:

#define wszPROPREQUESTREQUESTID		    TEXT("RequestID")
#define wszPROPREQUESTRAWREQUEST	    TEXT("RawRequest")
#define wszPROPREQUESTATTRIBUTES	    TEXT("RequestAttributes")
#define wszPROPREQUESTTYPE		    TEXT("RequestType")
#define wszPROPREQUESTFLAGS		    TEXT("RequestFlags")
#define wszPROPREQUESTSTATUS		    TEXT("Status")
#define wszPROPREQUESTSTATUSCODE	    TEXT("StatusCode")
#define wszPROPREQUESTDISPOSITION	    TEXT("Disposition")
#define wszPROPREQUESTDISPOSITIONMESSAGE    TEXT("DispositionMessage")
#define wszPROPREQUESTSUBMITTEDWHEN	    TEXT("SubmittedWhen")
#define wszPROPREQUESTRESOLVEDWHEN	    TEXT("ResolvedWhen")
#define wszPROPREQUESTREVOKEDWHEN	    TEXT("RevokedWhen")
#define wszPROPREQUESTREVOKEDEFFECTIVEWHEN  TEXT("RevokedEffectiveWhen")
#define wszPROPREQUESTREVOKEDREASON  	    TEXT("RevokedReason")
#define wszPROPREQUESTERNAME		    TEXT("RequesterName")


//+--------------------------------------------------------------------------
// Request attribute properties:

#define wszPROPCHALLENGE		TEXT("Challenge")
#define wszPROPEXPECTEDCHALLENGE	TEXT("ExpectedChallenge")


//+--------------------------------------------------------------------------
// Certificate properties:

#define wszPROPCERTIFICATEREQUESTID	    TEXT("RequestID")
#define wszPROPRAWCERTIFICATE		    TEXT("RawCertificate")
#define wszPROPCERTIFICATETYPE		    TEXT("CertificateType")
#define wszPROPCERTIFICATESERIALNUMBER	    TEXT("SerialNumber")
#define wszPROPCERTIFICATENOTBEFOREDATE	    TEXT("NotBefore")
#define wszPROPCERTIFICATENOTAFTERDATE	    TEXT("NotAfter")
#define wszPROPCERTIFICATERAWPUBLICKEY	    TEXT("RawPublicKey")
#define wszPROPCERTIFICATEPUBLICKEYALGORITHM TEXT("PublicKeyAlgorithm")
#define wszPROPCERTIFICATERAWPUBLICKEYALGORITHMPARAMETERS \
    TEXT("RawPublicKeyAlgorithmParameters")


//+--------------------------------------------------------------------------
// Certificate extension properties:

#define EXTENSION_CRITICAL_FLAG	 0x00000001
#define EXTENSION_DISABLE_FLAG	 0x00000002
#define EXTENSION_POLICY_MASK	 0x0000ffff	// Settable by admin+policy

#define EXTENSION_ORIGIN_REQUEST 0x00010000
#define EXTENSION_ORIGIN_POLICY	 0x00020000
#define EXTENSION_ORIGIN_ADMIN	 0x00030000
#define EXTENSION_ORIGIN_SERVER	 0x00040000
#define EXTENSION_ORIGIN_MASK	 0x000f0000


//+--------------------------------------------------------------------------
// GetProperty/SetProperty Flags:
//
// Choose one Type

#define PROPTYPE_LONG		 0x00000001	// Signed long
#define PROPTYPE_DATE		 0x00000002	// Date+Time
#define PROPTYPE_BINARY		 0x00000003	// Binary data
#define PROPTYPE_STRING		 0x00000004	// Unicode String


// Request Status property values:

#define REQSTATUS_ACTIVE	1
#define REQSTATUS_ACCEPTED	2
#define REQSTATUS_DENIED	3
#define REQSTATUS_PENDING	4
#define REQSTATUS_ERROR		5


// VerifyRequest() return values

#define VR_PENDING	0	 // request will be accepted or denied later
#define VR_INSTANT_OK	1	 // request was accepted
#define VR_INSTANT_BAD	2	 // request was rejected


#ifndef szOID_CRL_DIST_POINTS
# define szOID_CRL_DIST_POINTS           "2.5.29.31"
# define CERT_ALT_NAME_URL                7
# define szOID_NETSCAPE_REVOCATION_URL   "2.16.840.1.113730.1.3"
#endif


#endif // _CERTSRV_H_
