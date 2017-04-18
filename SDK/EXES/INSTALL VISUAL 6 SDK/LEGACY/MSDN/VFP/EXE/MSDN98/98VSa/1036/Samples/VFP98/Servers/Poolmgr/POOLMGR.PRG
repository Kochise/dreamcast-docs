#DEFINE TAB	CHR(9)
#DEFIN CRLF	CHR(13)+CHR(10)
#DEFINE STARTJOB_LOC	"Démarrage du job..."
#DEFINE ENDJOB_LOC		"Fin du job..."

DEFINE CLASS poolmgr AS custom OLEPUBLIC
	
	DIMENSION aJobObjs[1]
	aJobObjs[1]=""

	PROCEDURE Init
		DIMENSION THIS.aJobObjs[1,2]
		THIS.aJobObjs = .null.
		THIS.AddObject('timer1','PoolTimer')
		THIS.Timer1.Interval = 3000
	ENDPROC

	PROCEDURE Cleanup
		THIS.aJobObjs = .NULL.
		THIS.Timer1.aJobs = .NULL.
	ENDPROC
	
	PROCEDURE NewJob
		PARAMETER oNewJob
		IF TYPE("oNewJob") # "O" OR ISNULL(m.oNewJob)
			RETURN .F.
		ENDIF
		IF ALEN(THIS.aJobObjs,1) > 1 OR ISNULL(THIS.aJobObjs[1])
			DIMENSION THIS.aJobObjs[ALEN(THIS.aJobObjs,1)+1,2]
		ENDIF
		THIS.aJobObjs[ALEN(THIS.aJobObjs,1),1] = oNewJob
		THIS.aJobObjs[ALEN(THIS.aJobObjs,1),2] = 0
	ENDPROC

ENDDEFINE


DEFINE CLASS PoolTimer AS Timer
	Interval = 0
	DIMENSION aJobs[1]
	aJobs[1]= .null.
	PROCEDURE Timer
		LOCAL i
		* Check for completed jobs
		* Check for new jobs
		FOR i = 1 TO ALEN(THIS.Parent.aJobObjs,1)
			IF THIS.Parent.aJobObjs[m.i,2] = 0
				* New jobs
				IF ALEN(THIS.aJobs)>1 OR !ISNULL(THIS.aJobs[1])
					DIMENSION THIS.aJobs[ALEN(THIS.aJobs)+1]
				ENDIF
				DO CASE
				CASE  ATC("PRINT",THIS.Parent.aJobObjs[m.i,1].jobtype) # 0
					THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('Pool.PrintJob')
					* THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('PrintJob')
				CASE  ATC("GRAPH",THIS.Parent.aJobObjs[m.i,1].jobtype) # 0
					THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('Pool.GraphJob')
					* THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('GraphJob')
				CASE  ATC("FAX",THIS.Parent.aJobObjs[m.i,1].jobtype) # 0
					THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('Pool.FaxJob')
					* THIS.aJobs[ALEN(THIS.aJobs)] = CREATE('FaxJob')
				ENDCASE
				THIS.aJobs[ALEN(THIS.aJobs)].SetupJob(THIS.Parent.aJobObjs[m.i,1])
				THIS.Parent.aJobObjs[m.i,2] = 1
			ENDIF
		ENDFOR
	ENDPROC
ENDDEFINE


DEFINE CLASS JobTimer AS Timer
	TIMEOUT = 0
	Interval = 2000
	PROCEDURE Timer
		DO CASE
		CASE THIS.TIMEOUT = 0
			* New job
			THIS.PARENT.StartJob
			RETURN
		CASE THIS.TIMEOUT = 1
			* Job still running
			RETURN
		ENDCASE
	ENDPROC
ENDDEFINE


DEFINE CLASS Job AS form
	ShowWindow = 2
	oJob = ""

	PROCEDURE INIT
		THIS.AddObject('t1','JobTimer')
	ENDPROC

	PROCEDURE SetupJob
		PARAMETER oJob
		THIS.oJob = m.oJob
		THIS.Caption = THIS.oJob.Jobtype
		THIS.Visible = .T.
	ENDPROC

	PROCEDURE StartJob
		THIS.AddObject('lbl1','label')
		THIS.lbl1.Visible = .T.
		THIS.lbl1.caption = STARTJOB_LOC
		THIS.T1.Timeout = 1
	ENDPROC

	PROCEDURE EndJob
		THIS.T1.Timeout = 2
		THIS.lbl1.caption = ENDJOB_LOC
		THIS.oJob.JobDone()
		THIS.oJob = .null.
 		THIS.Visible = .F.
 		THISFORM.Release 
	ENDPROC

ENDDEFINE

DEFINE CLASS PrintJob AS Job OLEPublic
	PROCEDURE StartJob
		DoDefault()
		=INKEY(10)	
		THIS.EndJob()
	ENDPROC
ENDDEFINE

DEFINE CLASS FaxJob AS Job OLEPublic
	PROCEDURE StartJob
		DoDefault()
		=INKEY(5)	
		THIS.EndJob()
	ENDPROC
ENDDEFINE

DEFINE CLASS GraphJob AS Job OLEPublic
	PROCEDURE StartJob
		DoDefault()
		LOCAL nTotSeries,i
		public oXLChart1
		oXLChart1 = null
		oXLChart1 = GetObject('','excel.chart')
		oXLChart1.application.visible = .t.
		oXLChart1.application.worksheets(1).cells().clear

		_cliptext = ""+TAB+"Cats"+TAB+"Dogs"+CRLF+;
				 "1994"+TAB+"11"+TAB+"22"+CRLF+;
				 "1995"+TAB+"33"+TAB+"44"+CRLF+;
				 "1996"+TAB+"55"+TAB+"55"+CRLF

		oXLChart1.application.worksheets(1).cells(1,1).pastespecial
		oXLChart1.application.charts[1].autoformat(-4100,1)

		* Remove extra series added by Excel
		nTotSeries = oXLChart1.application.charts[1].SeriesCollection().count
		FOR i = m.nTotSeries to 4 STEP -1
			oXLChart1.application.charts[1].SeriesCollection(m.i).delete
		ENDFOR
		THIS.EndJob()
	ENDPROC
ENDDEFINE