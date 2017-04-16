* This is the main program for the FoxIsapi sample

* The first few lines allow this sample to be run as a normal APP
* either from within VFP or as a standalone EXE
Clear
Clear ALL
SET CLASSLIB TO employee
SET SAFETY OFF
PUBLIC ox
ox=CREATEOBJECT('employee')

IF VERSION(2) = 0	&& runtime
	ox.Visible = .T.
	READ EVENTS
	RETURN
ELSE
	ox.Show	&& must be design time
ENDIF




