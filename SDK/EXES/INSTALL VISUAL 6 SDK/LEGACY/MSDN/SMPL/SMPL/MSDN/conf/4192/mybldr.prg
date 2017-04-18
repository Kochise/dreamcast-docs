* Receive PARAMETERs from VFP
*   Object Reference
*   Origin of call to builder
*
*NOTE: oSelected will contain only the object reference to the
*      first selected object.  Use ASELOBJ() to reference all
*      selected objects.
PARAMETERS oSelected, cOrigin

* Do the form that presents the user with a UI for this builder
DO FORM FWLabel

* All done!
RETURN 
