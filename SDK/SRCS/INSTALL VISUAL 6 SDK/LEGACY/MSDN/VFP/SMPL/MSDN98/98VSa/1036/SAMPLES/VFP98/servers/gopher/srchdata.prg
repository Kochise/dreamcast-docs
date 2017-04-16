* The idea behind this class being used in a a Custom OLE Server is that it
* case provides a smart search business object which knows how and where to 
* look across the network for a customer who may be located in 1 of 50
* different databases (e.g., like a Gopher). 
* 
* This simple scenario here shows a similar search strategy, 
* only the search paths being a local and a remote DBC. 
* Local data = Testdata and Remote data = Tastrade.
*
* Note: make sure you change the Database path below to accommodate your VFP working directory.
*

#DEFINE FOXHOME	"\VFP\"

DEFINE CLASS Gopher AS Custom OLEPUBLIC

	oDERef = ""

	PROCEDURE UpdateDE
		PARAMETER oNewDE,lRemote
		IF TYPE("oNewDE")#"O" OR ISNULL(m.oNewDE)
			* Failed
			RETURN .F.
		ENDIF
		THIS.oDERef = m.oNewDE
		
		IF !m.lRemote
			* Use local data
			THIS.oDERef.cursor1.database = FOXHOME + "SAMPLES\DATA\TESTDATA.DBC"
			THIS.oDERef.cursor1.cursorsource = "Employee"
		ELSE
			* Use remote data (simulated)
			THIS.oDERef.cursor1.database = FOXHOME + "SAMPLES\TASTRADE\DATA\TASTRADE.DBC"
			THIS.oDERef.cursor1.cursorsource = "Employee"
		ENDIF
		THIS.oDERef = ""
	ENDPROC
	
ENDDEFINE