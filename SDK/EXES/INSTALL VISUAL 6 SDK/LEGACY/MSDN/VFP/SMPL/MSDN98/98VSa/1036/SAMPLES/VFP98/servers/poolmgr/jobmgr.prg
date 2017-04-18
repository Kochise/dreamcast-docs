* This is the class for a Job object created by the pool form
* which is passed to the Pool Manager object. When the Pool
* Manager is complete with processing the jog, it makes a call
* back into the Job object by invoking its JobDone method.

DEFINE CLASS newjob AS custom

	Timeout = 3000
	Jobtype = ""
	oFormRef = ""
	
	PROCEDURE Init
		PARAMETER oForm
		THIS.oFormRef = oForm
	ENDPROC
			
	PROCEDURE jobdone
		* Let's notify parent that job is complete
		IF TYPE("THIS.oFormRef")="O"
			THIS.oFormRef.JobDone(THIS.JobType)
		ENDIF
	ENDPROC
	
ENDDEFINE

DEFINE CLASS graphjob AS newjob
	JobType = "GRAPH"
ENDDEFINE

DEFINE CLASS printjob AS newjob
	JobType = "PRINT"
ENDDEFINE

DEFINE CLASS faxjob AS newjob
	JobType = "FAX"
ENDDEFINE
