// This is an example of an extended procedure DLL built with Open Data
// Services. The functions within the DLL can be invoked by using the extended
//	stored procedures support in SQL Server.  To register the functions 
// and allow all users to use them run the ISQL script INSTXP.SQL.
//
// For further information on Open Data Services refer to the Microsoft Open 
// Data Services Programmer's Reference.
//
//  The extended procedures implemented in this DLL are:
//
//  XP_PROCLIST	Returns all this DLL's extended stored procedures and 
//					their usuage.
//
//	 XP_DISKLIST	Returns a row for each defined drive containing its name 
//					and the amount of disk space available.
//
//  XP_DISKFREE   Returns the amount of space available on a given drive.
//             The value is placed into the defined return parameter of
//             the stored procedure.
//
//  XP_SCAN_XBASE	Reads an xBase file and sends it to the client as if it 
//					were a SQL Server query result set (the equivalent of a 
//					'SELECT * FROM tablename' SQL statement).
//
//  XP_ECHO		Used to demo the handling of output parameters in
//					extended procedures.
//
//  XP_TRACE	Used to show the installation and removal of pre-handlers
//					for language and rpc events. The pre-handlers installed
//					just print langauge and rpc events to the console in
//					readable form.  Start SQL Server at the command line
//					to see the output.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <srv.h>
#include <time.h>

// Miscellaneous defines
//
#define  XP_NOERROR		0
#define  XP_ERROR		1

#define  MAXNAME       31	// Maximum extended procedure name length
#define  MAXLEN        80	// Maximum string length
#define  COMMAND_PARAM	1	// Command Parameter
#define  OUTPUT_PARAM	2	// Command Parameter

// Extended procedure error codes
//
#define  SRV_MAXERROR           20000
#define  XP_PROCLIST_ERROR      SRV_MAXERROR + 1
#define  CMDSHELL_ERROR         SRV_MAXERROR + 2
#define  DISKLIST_ERROR         SRV_MAXERROR + 3
#define  SCAN_XBASE_ERROR       SRV_MAXERROR + 4
#define  TRACE_ERROR      		SRV_MAXERROR + 6

// Standard error macro for reporting API errors
//
#define SETERROR( api, retstring)               \
    sprintf(retstring,"%s: Error %d from %s on line %d\n",  \
        __FILE__, GetLastError(), api, __LINE__);
 
// SCAN_XBASE defines
//
#define XBASE_HDR_SIZE  		32
#define XBASE_MAX_COLUMNS 		128
#define XBASE_BUF_SIZE    		2048

// function prototypes for xp_trace callbacks
SRVRETCODE trace_lang(SRV_PROC *);
SRVRETCODE trace_rpc(SRV_PROC *);

// Stored Procedure information structure.
//
typedef struct xp_info {
    DBCHAR name[MAXNAME];   	// Extended procedure name
    DBCHAR usage[MAXLEN];   		// Usage string
} XP_INFO;

// Array of Extended Stored Procedures supported by this DLL.
//
XP_INFO Xps[] = 
{
    "xp_proclist",					// Procedure name
    "usage: xp_proclist",		 	// Procedure usage string

    "xp_disklist",
    "usage: xp_disklist",

    "xp_diskfree",
    "usage: xp_diskfree <[@drive =] drive letter> [,] <[@space =] free space>",

    "xp_scan_xbase",
    "usage: xp_scan_xbase <xbase file name>",

    "xp_echo",
    "usage: xp_echo @p1=<input> , @p2=<output-param> output",

    "xp_trace",
    "usage: xp_trace <[@state=] 'on'|'off'> [, [@users=] NULL | 'all']",
};
#define Xpcnumber sizeof(Xps) / sizeof(XP_INFO)

//
// PROCLIST
//    Returns the usage for all defined stored procedures
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns a result set to client
//
SRVRETCODE xp_proclist(srvproc)
SRV_PROC *srvproc;
{
    int paramnum;
    DBCHAR colname1[MAXNAME];
    DBCHAR colname2[MAXNAME];
    int i;

    // Get number of parameters
    //
    paramnum = srv_rpcparams(srvproc);

    // Check number of parameters
    //
    if (paramnum != -1) {
        // Send error message and return
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, XP_PROCLIST_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error executing extended stored procedure: Invalid Parameter",
                    SRV_NULLTERM);
	 	  // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	 	  // result set of an Extended Stored Procedure.
	 	  //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }

    sprintf(colname1, "spname");
    srv_describe(srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, MAXNAME,
                 SRVCHAR, 0, NULL);

    sprintf(colname2, "spusage");
    srv_describe(srvproc, 2, colname2, SRV_NULLTERM, SRVCHAR, MAXLEN, SRVCHAR,
                 0, NULL);

    // Return each XP handler as a row
    //
    for (i = 0; i < Xpcnumber; i++) {
        srv_setcoldata(srvproc, 1, Xps[i].name);
        srv_setcollen(srvproc, 1, strlen(Xps[i].name));

        srv_setcoldata(srvproc, 2, Xps[i].usage);
        srv_setcollen(srvproc, 2, strlen(Xps[i].usage));

        srv_sendrow(srvproc);
    }
	 // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	 // result set of an Extended Stored Procedure.
	 //
    srv_senddone(srvproc, (SRV_DONE_COUNT | SRV_DONE_MORE), 0, i);

    return(XP_NOERROR);
}

//
// XP_ECHO
//	Used to demo the handling of output parameters in extended procedures.
//	The first parameter should be the input parameter and the second
//	parameter should be the output.  The input parameter is placed in the
//	output parameter and returned.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
//

SRVRETCODE xp_echo(srvproc)
SRV_PROC *srvproc;
{
    int paramnum;

    // Check number of parameters
    //
    if ((paramnum = srv_rpcparams(srvproc)) != 2) {
        // Send error message and return
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, CMDSHELL_ERROR, SRV_INFO, (DBTINYINT)0,
		    NULL, 0, 0, "Error executing extended stored procedure: Invalid # of Parameters",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }

    // Set output parameter to input parameter.
    //

    srv_paramset(srvproc, 2, srv_paramdata(srvproc,1), srv_paramlen(srvproc,1));

    srv_senddone(srvproc, SRV_DONE_MORE, 0, 0);

    return(XP_NOERROR);

}

//
// XP_DISKLIST
//     Returns a row for each defined drive containing its name and the
//     amount of disk space available.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//     Returns a result set to client
//
SRVRETCODE xp_disklist(srvproc)
SRV_PROC *srvproc;
{
    int paramnum;
    DBCHAR colname1[MAXNAME];
    DBCHAR colname2[MAXNAME];
    DBCHAR drivename;
    DBCHAR rootname[16];
    int drivenum;
    int secPerCluster;
    int bytesPerSector;
    int freeClusters;
    int totalClusters;
    int drivenums;
    int space_remaining;
    int i = 0;

    // Get number of parameters
    //
    paramnum = srv_rpcparams(srvproc);

    // Check number of parameters
    //
    if (paramnum != -1) {
        // Send error message and return
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, DISKLIST_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error executing extended stored procedure: Invalid Parameter",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }
    sprintf(colname1, "drive");
    srv_describe(srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, 1, SRVCHAR, 1,
                 (BYTE *)&drivename);

    sprintf(colname2, "bytes free");
    srv_describe(srvproc, 2, colname2, SRV_NULLTERM, SRVINT4, 4, SRVINT4, 4,
                 (BYTE *)&space_remaining);

    drivenums = GetLogicalDrives();

    drivenums >>= 2;        //Ignore drives A and B
    for (drivename = 'C', drivenum = 3; drivename <= 'Z';
         drivename++, drivenum++) {

        if (drivenums & 1) {
            i++;
            sprintf(rootname, "%c:\\", drivename);
            GetDiskFreeSpace(rootname, &secPerCluster, &bytesPerSector,
                             &freeClusters, &totalClusters);
            space_remaining = secPerCluster * freeClusters * bytesPerSector;

            srv_sendrow(srvproc);
        }
        drivenums >>= 1;
    }
    // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
    // result set of an Extended Stored Procedure.
    //
    srv_senddone(srvproc, (SRV_DONE_COUNT | SRV_DONE_MORE), 0, i);
    return(XP_NOERROR);
}


//
// XP_DISKFREE
//    Returns the amount of space available on a given drive. The value
//     is placed into the defined return parameter of the stored procedure.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns messages and/or a result set to client. Returns a value in the
//     defined return parameter.
//
SRVRETCODE xp_diskfree(srvproc)
SRV_PROC *srvproc;
{
    DBCHAR *drive;
    DBCHAR colname1[MAXNAME];
    DBCHAR colname2[MAXNAME];
    DBINT paramlength;
    DBCHAR rootname[16];
    DBCHAR bErrorMsg[MAXLEN];

    int drivenum;
    int drivenums;
    int secPerCluster;
    int bytesPerSector;
    int freeClusters;
    int totalClusters;
    int space_remaining = -1;

    // Check number of parameters
    //
    if (srv_rpcparams(srvproc) > 0) {

	// Allocation local storage for drive name.
	//
	paramlength = srv_paramlen(srvproc, 1);
	drive = (DBCHAR *)malloc(paramlength);
	if (!drive) {

	    SETERROR("Malloc", bErrorMsg);
	    srv_sendmsg(srvproc, SRV_MSG_ERROR, CMDSHELL_ERROR, SRV_INFO, (DBTINYINT)0,
		       NULL, 0, 0, bErrorMsg, SRV_NULLTERM);
	    // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	    // result set of an Extended Stored Procedure.
	    //
	    srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	    return(XP_ERROR);
	}

	// Fetch drive letter.
	srv_bmove(srv_paramdata(srvproc, 1), drive, paramlength);
	drive = strupr(drive);

    } else

	// Default drive is C.
	drive = "C";

    drivenums = GetLogicalDrives();
    drivenum = drive[0] - 'A' + 1;

    drivenums >>= drivenum - 1; //Ignore drives A and B
    if (drivenums & 0x01) {

        sprintf(rootname, "%c:\\", drive[0]);
        GetDiskFreeSpace(rootname, &secPerCluster, &bytesPerSector,
                         &freeClusters, &totalClusters);

        space_remaining = secPerCluster * freeClusters * bytesPerSector;

    }

    // Process return values
    //
    if (srv_paramstatus(srvproc, 2) < 0 ) {
	// Setup column heading
	sprintf(colname1, "drive");
	sprintf(colname2, "space");
	srv_describe(srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, 1, SRVCHAR, 1,
		     (BYTE *)drive);
	srv_describe(srvproc, 2, colname2, SRV_NULLTERM,
		     SRVINT4, sizeof(space_remaining), SRVINT4,
		     sizeof(space_remaining), &space_remaining);

	srv_sendrow(srvproc);
	srv_senddone(srvproc, (SRV_DONE_COUNT | SRV_DONE_MORE), 0, 1);

   }
    else {
	srv_paramset(srvproc, 2, (BYTE *)&space_remaining, 4);
	srv_senddone(srvproc, SRV_DONE_MORE, 0, 0);
    }

    return(XP_NOERROR);
}



//
// XP_SCAN_XBASE
//    Reads an xBase file and sends it to the client as if it were a SQL
//    Server query result set (the equivalent of a 'SELECT * FROM
//    tablename' SQL statement).
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns messages and/or a result set to client
//
SRVRETCODE xp_scan_xbase(srvproc)
SRV_PROC *srvproc;
{
    int paramnum;
    DBINT paramtype;
    DBCHAR *filename;
    FILE *xbasefile;
    size_t count;
    char buffer[XBASE_BUF_SIZE];
    short numrecords;
    short headerlength;
    short recordlength;
    short lengthlist[XBASE_MAX_COLUMNS];
    int i;
    short j;
    short position;
    short numcolumns;

    // Get number of parameters
    //
    paramnum = srv_rpcparams(srvproc);

    // Check number of parameters
    //
    if (paramnum != 1) {
        // Send error message and return
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error executing extended stored procedure: Invalid Parameter",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }

    // Check parameters for correct type
    //
    paramtype = srv_paramtype(srvproc, paramnum);
    if (paramtype != SRVVARCHAR) {
        // Send error message and return
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0,
                    "Error executing extended stored procedure: Invalid Parameter Type",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }
    filename = srv_paramdata(srvproc, 1);

    // now read the database header info
    //
    if ((xbasefile = fopen(filename, "r")) == NULL) {
        srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }
    count = fread(buffer, XBASE_HDR_SIZE, 1, xbasefile);

    if (count == 0) {
        srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        fclose(xbasefile);
	return(XP_ERROR);
    }
    numrecords = *((short *)&buffer[4]);
    headerlength = *((short *)&buffer[8]);
    recordlength = *((short *)&buffer[10]);
    numcolumns = (headerlength - 32 - 1) / 32;

    // now get the column header information
    //
    for (j = 0; j < numcolumns; j++) {
        count = fread(buffer,
        XBASE_HDR_SIZE,
        1,
        xbasefile);
        if (count == 0) {
            srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                        NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
	         // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	         // result set of an Extended Stored Procedure.
	         //
            srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
            fclose(xbasefile);
	    return(XP_ERROR);
        }

        // we need to NULL terminate the column name (if it is a
        // full 11 characters int)
        //
        buffer[11] = '\0';

        // now find our the column length for this data buffer
        //
        lengthlist[j] = (short)buffer[16];

        // now 'describe' this column
        //
        srv_describe(srvproc, j + 1,// column number
                buffer,     // pointer to column name
                SRV_NULLTERM,// column name is NULL terminated
                SRVCHAR,    // datatype is char (xBase numbers are ASCII
                lengthlist[j],// column length
                SRVCHAR,    // destination datatype is also char
                lengthlist[j],// destination column length
                NULL);      // pointer to where the data will be

    }
    // now read the one byte 'column header seperator'
    //
    count = fread(buffer, 1, 1, xbasefile);
    if (count == 0) {
        srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
	     //
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        fclose(xbasefile);
	return(XP_ERROR);
    }
    for (i = 0; i < numrecords; i++) {
        count = fread(buffer, recordlength, 1, xbasefile);
        if (count == 0 && !feof(xbasefile)) {
            srv_sendmsg(srvproc, SRV_MSG_ERROR, SCAN_XBASE_ERROR, SRV_INFO, (DBTINYINT)0,
                        NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
	         // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	         // result set of an Extended Stored Procedure.
	         //
            srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
            fclose(xbasefile);
	    return(XP_ERROR);
        }

        // check to see if this is a deleted row
        //
        if (buffer[0] == '*')
            break;

        // Now set the length and data pointers for each column
        for (j = 0, position = 1; j < numcolumns; j++) {
            srv_setcollen(srvproc, j + 1, lengthlist[j]);
            srv_setcoldata(srvproc, j + 1, &buffer[position]);
            position += lengthlist[j];
        }

        // send the row to the client.
        //
        srv_sendrow(srvproc);
    }
	 // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	 // result set of an Extended Stored Procedure.
	 //
    srv_senddone(srvproc, SRV_DONE_COUNT | SRV_DONE_MORE, 0, i);
    fclose(xbasefile);
    return(XP_NOERROR);
}

//
// XP_TRACE
//	Used to demo the proc-specific pre-handlers in extended procedures.
//	Parameter 1 is @state, "on" or "off" to install or remove.  
//	Parameter 2 is @users, NULL to install pre-handlers on this
//		srvproc only , or 'all' to install server-wide pre-handlers
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//

SRVRETCODE xp_trace(srvproc)
SRV_PROC *srvproc;
{
    int      numparams;
    DBCHAR * paramname;
    int      i;
    int      position;
    int      len;
    DBINT    paramtype;
    DBINT    paramlength;
	char state[4];
	char users[4];
	char timestr[9];
	char *errmsg;
	SRV_SERVER *server;
	int	retcode;

	state[0] = '\0';
	users[0] = '\0';

    // Check parameters
	// Support both named and positional parameters
	//
	numparams = srv_rpcparams( srvproc );

    if ((numparams < 1) || (numparams > 2)) {
        errmsg = "Error: Invalid number of Parameters";
		goto ErrorExit;                    
    }	

    for( i = 1; i <= numparams; i++ )
    {
        paramname = srv_paramname( srvproc, i, &len );

        if( len )
        {
            if( !stricmp(paramname, "@state") )
                position = 1;
            else if( !stricmp(paramname, "@users") )
                position = 2;
            else {
                srv_sendmsg( srvproc,SRV_MSG_ERROR,TRACE_ERROR,
                             16,(DBTINYINT)1,NULL,0,0,"Invalid Parameter",SRV_NULLTERM );				
                return FAIL;
            }
        }
        else
            position = i;

        paramtype   = srv_paramtype( srvproc, i );
        if ( (paramlength = srv_paramlen( srvproc, i )) > 3 )
        	{
			errmsg = "Error:  Parameter value too long";
			goto ErrorExit;
			}        	

        switch( position )
        {
        case 1: // @state
            if( paramtype != SRVVARCHAR && paramtype != SRVNULL )
            {
		        errmsg = "Error:  Invalid @state parameter type, expecting varchar";
				goto ErrorExit;                    
            }
			srv_bmove(srv_paramdata(srvproc, i), state, paramlength);
			state[paramlength] = '\0';
			
	        break;

        case 2: // @users
            if( paramtype != SRVVARCHAR && paramtype != SRVNULL )
            {
		        errmsg = "Error:  Invalid @users parameter type, expecting varchar";
				goto ErrorExit;                    
            }

			srv_bmove(srv_paramdata(srvproc, i), users, paramlength);
			users[paramlength] = '\0';
            
            if ( (stricmp(users,"all") != 0) && paramlength ) 
			{
		        errmsg = "Error:  Invalid @users parameter, must be 'all' or NULL";
				goto ErrorExit;                    
			}
			break;
        } // switch( position )

    } // for( i = 1; i <= numparams; i++ )

	// check for required 1st parameter
	if ( (stricmp(state,"on") != 0) && (stricmp(state,"off") != 0) ) 
	{
		errmsg = "Error:  Required @state parameter must be 'on' or 'off'";
		goto ErrorExit;                    
	}    
	
	if (!stricmp(state,"on") && !strlen(users)) {
		// turn on trace for just this srvproc
		srv_pre_handle(NULL,srvproc,SRV_LANGUAGE,trace_lang,FALSE);
		retcode = srv_pre_handle(NULL,srvproc,SRV_RPC,trace_rpc,FALSE);
		switch (retcode) {
			case FAIL:
				errmsg = "Error installing pre-handlers";
				goto ErrorExit;                    
			case SRV_DUPLICATE_HANDLER:
				errmsg = "Pre-handler already installed";
				goto ErrorExit;                    
			default:												
				printf("%s  starting trace for KPID %s\n", _strtime(timestr),
											srv_pfield(srvproc, SRV_SPID, NULL));
		}
	}		
	else if (!stricmp(state,"off") && !strlen(users)) {
		// set remove flag to true
		srv_pre_handle(NULL,srvproc,SRV_LANGUAGE,trace_lang,TRUE);
		retcode = srv_pre_handle(NULL,srvproc,SRV_RPC,trace_rpc,TRUE);
		switch (retcode) {
			case FAIL:
				errmsg = "Pre-handler not found";
				goto ErrorExit;                    
			default:												
				printf("%s  stopping trace for KPID %s\n", _strtime(timestr),
										srv_pfield(srvproc, SRV_SPID, NULL));
		}
	}	
	else if (!stricmp(state,"on") && !stricmp(users, "all")) {
		// turn on trace for all connections
		server = SRV_GETSERVER(srvproc);
		srv_pre_handle(server,NULL,SRV_LANGUAGE,trace_lang,FALSE);
		retcode = srv_pre_handle(server,NULL,SRV_RPC,trace_rpc,FALSE);
		switch (retcode) {
			case FAIL:
				errmsg = "Error installing pre-handlers";
				goto ErrorExit;                    
			case SRV_DUPLICATE_HANDLER:
				errmsg = "Pre-handler already installed";
				goto ErrorExit;                    
			default:												
				printf("%s  starting trace for all connections \n", _strtime(timestr));			
		}
	}		
	else if (!stricmp(state,"off") && !stricmp(users, "all")) {
		// set remove flag to true
		server = SRV_GETSERVER(srvproc);
		srv_pre_handle(server,NULL,SRV_LANGUAGE,trace_lang,TRUE);
		retcode = srv_pre_handle(server,NULL,SRV_RPC,trace_rpc,TRUE);
		switch (retcode) {
			case FAIL:
				errmsg = "Pre-handler not found";
				goto ErrorExit;                    
			default:												
				printf("%s  stopping trace for all connections \n", _strtime(timestr));			
		}
	}	
	else {
        errmsg = "Error in xp_trace logic";
		goto ErrorExit;                    
	}	
			    
    return(XP_NOERROR);

ErrorExit:
// Send error message and return
    //
    srv_sendmsg(srvproc, SRV_MSG_ERROR, TRACE_ERROR, SRV_INFO, (DBTINYINT)0,
		    NULL, 0, 0, errmsg, SRV_NULLTERM);
	     
    srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
		return(XP_ERROR);

}
//****************************************************************************
// trace_lang
//      This is the pre-language handler routine to print language requests to 
//		stdio
//
// Parameters:
//    srvproc - a pointer to SRV_PROC stucture
//
// Returns:
//    SRV_CONTINUE
//
// Side Effects:
//
//****************************************************************************
SRVRETCODE trace_lang(srvproc)
SRV_PROC *srvproc;
{
    char timestr[9];
	DBCHAR *query;
	int query_len;

	query= srv_langptr(srvproc);
	query_len = srv_langlen(srvproc);

   	//print the request
    printf("%s  KPID %s lang:  %s\n", _strtime(timestr),
    	srv_pfield(srvproc, SRV_SPID, (int *)NULL),query);
	if (query[query_len-1] != '\n')
		printf("\n");
	
    return(SRV_CONTINUE);
}

//****************************************************************************
// trace_rpc
//      This is the pre-rpc handler routine to print language requests to 
//		stdio
//
// Parameters:
//    srvproc - a pointer to SRV_PROC stucture
//
// Returns:
//    SRV_CONTINUE
//
// Side Effects:
//
//****************************************************************************
SRVRETCODE trace_rpc(srvproc)
SRV_PROC *srvproc;
{
    int i;                  // Index variable
    short params;
    DBCHAR complete_rpc_name[4 * (MAXNAME + 1)]; //database.owner.name;#
	DBCHAR *rpc_db;
	DBCHAR *rpc_owner;
	DBCHAR *rpc_name;
	int rpc_number;
	char rpc_number_char[17];
	DBCHAR *rpc_paramname;
	DBCHAR * rpc_paramstatus;
	int rpc_paramtype;
	DBINT rpc_parammaxlen;
	DBINT rpc_paramlen;
	void *rpc_paramdata;
	char rpc_paramstr[256];
	char timestr[9];
	DBCHAR * rpc_typename;
	DBCHAR sztypestr[20];
	DBNUMERIC numeric;
    

    // Construct full RPC name 
    //
	memset (complete_rpc_name, 0, sizeof(complete_rpc_name));
	rpc_db = srv_rpcdb(srvproc, (int *)NULL);
	rpc_owner = srv_rpcowner(srvproc, (int *)NULL);
	rpc_name = srv_rpcname(srvproc, (int *)NULL);
	rpc_number = srv_rpcnumber(srvproc);
	
	if (rpc_db != NULL) {
		strcat(complete_rpc_name,rpc_db);
		strcat(complete_rpc_name,".");
	};
	if (rpc_owner != NULL) {
		strcat(complete_rpc_name,rpc_owner);
		strcat(complete_rpc_name,".");
	};
	strcat(complete_rpc_name,rpc_name);
	if (rpc_number > 0) {
    	strcat(complete_rpc_name,";");
		_itoa(rpc_number,rpc_number_char,10);
		strcat(complete_rpc_name, rpc_number_char);
	};
	
	//start printing the request

    printf("%s  KPID %s rpc:  %s", _strtime(timestr),
    	srv_pfield(srvproc, SRV_SPID, (int *)NULL),complete_rpc_name);
    
    // Set up any RPC parameters.
    //
    params = srv_rpcparams(srvproc);

    for (i = 1; i <= params; i++) {

		rpc_paramname = srv_paramname(srvproc, i, (int *)NULL);
		if (strlen(rpc_paramname) == 0) rpc_paramname = NULL;

        if ((BYTE)srv_paramstatus(srvproc, i) == SRV_PARAMRETURN)
        	rpc_paramstatus = "OUT";
		else
			rpc_paramstatus = " ";
		
        rpc_paramtype = srv_paramtype(srvproc, i);
        rpc_parammaxlen = srv_parammaxlen(srvproc, i);
		rpc_paramlen = srv_paramlen(srvproc, i);
       	rpc_paramdata = srv_paramdata(srvproc, i);      		

		switch (rpc_paramtype) {
			case SRVVARCHAR:
				sprintf(sztypestr, "%s(%d)","varchar",rpc_parammaxlen);
				break;
			case SRVCHAR:
				sprintf(sztypestr, "%s(%d)","char",rpc_parammaxlen);
				break;
			case SRVINTN:
				switch (rpc_paramlen) {
					case 1:
						rpc_typename = "tinyint";
						break;
					case 2:
						rpc_typename = "smallint";
						break;
					default:
						rpc_typename = "int";
						break;
				}
				sprintf(sztypestr, "%s null",rpc_typename);
				break;
			case SRVINT1:
				sprintf(sztypestr, "tinyint");
				break;
			case SRVINT2:
				sprintf(sztypestr, "smallint");
				break;
			case SRVINT4:
				sprintf(sztypestr, "int");
				break;

			case SRVMONEYN:
				switch (rpc_paramlen) {
					case 4:
						rpc_typename = "smallmoney";
						break;
					default:
						rpc_typename = "money";
						break;
				}
				sprintf(sztypestr, "%s null",rpc_typename);
				break;
			case SRVMONEY4:
				sprintf(sztypestr, "smallmoney");
				break;
			case SRVMONEY:
				sprintf(sztypestr, "money");
				break;

			case SRVDATETIMN:
				switch (rpc_paramlen) {
					case 4:
						rpc_typename = "smalldatetime";
						break;
					default:
						rpc_typename = "datetime";
						break;
				}
				sprintf(sztypestr, "%s null",rpc_typename);
				break;
			case SRVDATETIM4:
				sprintf(sztypestr, "smalldatetime");
				break;
			case SRVDATETIME:
				sprintf(sztypestr, "datetime");
				break;

			case SRVFLTN:
				switch (rpc_paramlen) {
					case 4:
						rpc_typename = "real";
						break;
					default:
						rpc_typename = "float";
						break;
				}
				sprintf(sztypestr, "%s null",rpc_typename);
				break;
			case SRVFLT4:
				sprintf(sztypestr, "real");
				break;
			case SRVFLT8:
				sprintf(sztypestr, "float");
				break;

			case SRVNUMERIC:
			case SRVNUMERICN:
			case SRVDECIMAL:
			case SRVDECIMALN:
				memset (&numeric, 0, sizeof(DBNUMERIC));
				memmove (&numeric, rpc_paramdata, rpc_paramlen);
				rpc_paramdata = &numeric;
				switch (rpc_paramtype) {
					case SRVNUMERIC:
					case SRVNUMERICN:
						rpc_typename = "numeric";
						break;
					case SRVDECIMAL:
					case SRVDECIMALN:
						rpc_typename = "decimal";
						break;
				}		
				sprintf(sztypestr, "%s(%d,%d)",rpc_typename, numeric.precision, numeric.scale);
				if (rpc_paramlen == 2) 
					rpc_paramlen = 0;
				break;
			case SRVTEXT:
				sprintf(sztypestr, "text");
				break;
			case SRVIMAGE:
				sprintf(sztypestr, "image");
				break;

			case SRVVARBINARY:
				sprintf(sztypestr, "%s(%d)","varbinary",rpc_parammaxlen);
				break;
			case SRVBINARY:
				sprintf(sztypestr, "%s(%d)","binary",rpc_parammaxlen);
				break;
			case SRVBIT:
				sprintf(sztypestr, "bit");
				break;

			case SRVNULL:
				sprintf(sztypestr, "srvnull");
				break;

			default:
				sprintf(sztypestr, "unknown type");
				break;

		} // end of switch (rpc_paramtype)

        if (rpc_paramlen > 0) {
			if (rpc_paramtype != SRVVARBINARY)  
				srv_convert(srvproc,rpc_paramtype,rpc_paramdata,
						rpc_paramlen,SRVCHAR,rpc_paramstr,-1);
			else
				strcpy(rpc_paramstr,"<conversion not supported>");
		}
		else 
			strcpy(rpc_paramstr,"<null>");


		printf("\r\n   P%3d: %-10s %-15s %4s %s",i,rpc_paramname, sztypestr, rpc_paramstatus, rpc_paramstr);
		
    }
	printf("\n\n");

    return(SRV_CONTINUE);
}
