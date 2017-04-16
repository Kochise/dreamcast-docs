StandardScreen::Init	&& call the Init code found in StandardScreen

THISFORM.ShowButton 	&& turn off buttons that have property "select" = .F.

* Assign values to on-screen fields:
THISFORM.InputField1.Value 	   = "USER"
THISFORM.FinancialField2.Value = "5,345.00"
THISFORM.FinancialField3.Value = "10,324.45"
THISFORM.FinancialField4.Value ="-2,349.20"
THISFORM.Ratings5.Value ="High"


* You can only call this next method, which is found in StandardScreen,
* if the form contains fields that are based on the class "FinancialField" 
* from MYLIB.VCX. Otherwise, an error results.
THISFORM.FinancialFields

* Disable (but leave visible) all fields 
* based on class "Ratings" if user doesn't have access.
IF NOT Granted ( "RATINGS", "READ"  )
   THISFORM.SetAll ( "Visible", .F.,  "Ratings"  )
ENDIF
IF NOT Granted ( "RATINGS", "WRITE" )
   THISFORM.SetAll ( "Readonly", .T.,  "Ratings"  )
ENDIF