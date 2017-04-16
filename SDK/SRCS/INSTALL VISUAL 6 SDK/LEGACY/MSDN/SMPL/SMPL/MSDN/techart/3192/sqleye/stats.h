void ProcessReadStats(DBPROCESS *, char * msgtext);
void ProcessWriteStats(DBPROCESS *, char * msgtext);
void ProcessExecStats(DBPROCESS *, char * msgtext);
void ProcessPAndCStats(DBPROCESS *, char * msgtext);
void ProcessCPUStats(DBPROCESS *, char * msgtext);
int SwitchStats(REMOTE_DBMS *rmt_dbms, DBPROCESS *rmtproc,char * query);
BOOL CatchStats(DBINT msgno, char * msgtext, DBPROCESS * dbproc,REMOTE_DBMS * remote);

