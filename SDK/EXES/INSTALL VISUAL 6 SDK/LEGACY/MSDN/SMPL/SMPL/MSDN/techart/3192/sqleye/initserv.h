int InitServer(SRV_SERVER *server);
int ChkErr(SRV_SERVER *server,
           SRV_PROC   *srvproc,
           int         errornum,
           BYTE        severity,
           BYTE        state,
           int         oserrnum,
           DBCHAR     *errtext,
           int         errtextlen,
           DBCHAR     *oserrtext,
           int         oserrtextlen);
int RemoteMsgs(DBPROCESS  *dbproc,
               DBINT       msgno,
               INT  msgstate,
               INT  severity,
               char       *msgtext);
int RemoteErr(DBPROCESS  *dbproc,
              int severity,
              int dberr,
              int oserr,
              char  *dberrstr,
              char  *oserrstr);
void SetRemoteServerName(char *name);

