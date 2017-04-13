/*************************************************************************

VIEWC.DLL - This Module creates Views based on the current Group Map in
SMS

Copyright (c), 1994 by Microsoft Corp.

Modified: 7/11/95 a-cvadai  Added error message messageboxes.
          9/13/95 a-cvadai  Changed outer- to inner-joins on all views

*************************************************************************/

#define DBNTWIN32               // must identify operating system environment
#include "windows.h"

#include <sqlfront.h>
#include <sqldb.h>         // DB-LIB header file (should always be included)
#include <stdio.h>
#include "smsview.h"
#include "viewdlls.h"

int RetCode, CmdComplete;

void ErrorMsg(int ,int);
int GenViews(dbproc,dbprocView,CreateGroupName,DropOnlyFlag,CommandLine)
DBPROCESS *dbproc;
DBPROCESS *dbprocView;
char *CreateGroupName;
int DropOnlyFlag;
int CommandLine;

{
  RETCODE result_code;
  struct VIEWDEF TableDef[MAX_COLUMNS];
  char szTmpText[500];
  char szText[500];
  char szMsgTitle[32];

  // Variables to bind to Group Map select
  char  ViewName[MAX_COLUMN_NAME],
        ArchitectureName[MAX_COLUMN_NAME],
        GroupName[MAX_COLUMN_NAME],
        AttributeName[MAX_COLUMN_NAME],
        ColumnName[MAX_COLUMN_NAME] ,
        CommonTableName[MAX_COLUMN_NAME],
        SpecificTableName[MAX_COLUMN_NAME];

   // Variables to keep Current View Details
   char CurCommonTableName[MAX_COLUMN_NAME],
        CurArchitectureName[MAX_COLUMN_NAME],
        CurSpecificTableName[MAX_COLUMN_NAME];

  int CurKey = 0,
      CurArchitectureKey,
      i= 0, LastMode,
      ViewSuffix = 0;

  int GroupKey,
      ArchitectureKey,
      Mode, 
      CommonSpecificFlag;

      RetCode = SUCCEED;
      CmdComplete=CommandLine;

     dberrhandle((void *)err_handler);
     dbmsghandle((void *)err_handler);
    // Set up a View that we can use to get all the Group Info

    dbcmd (dbproc , (char *) "SELECT AttributeMap.GroupKey,");
    dbcmd (dbproc , (char *) " ArchitectureMap.ArchitectureName, ");
    dbcmd (dbproc , (char *) " GroupMap.ArchitectureKey , ");
    dbcmd (dbproc , (char *) " GroupMap.GroupName,");
    dbcmd (dbproc , (char *) " AttributeMap.AttributeName,");
    dbcmd (dbproc , (char *) " AttributeMap.ColumnName,");
    dbcmd (dbproc , (char *) " AttributeMap.CommonSpecificFlag,");
    dbcmd (dbproc , (char *) " GroupMap.CommonTableName, ");
    dbcmd (dbproc , (char *) " GroupMap.SpecificTableName, ");
    dbcmd (dbproc , (char *) " ArchitectureMap.Mode ");

    dbcmd (dbproc , (char *) " FROM ArchitectureMap ArchitectureMap,");
    dbcmd (dbproc , (char *) " AttributeMap AttributeMap,");
    dbcmd (dbproc , (char *) " GroupMap GroupMap     ");

    dbcmd (dbproc , (char *) " WHERE GroupMap.ArchitectureKey = "
                             "AttributeMap.ArchitectureKey AND ");
    dbcmd (dbproc , (char *) " AttributeMap.ArchitectureKey = "
                             "ArchitectureMap.ArchitectureKey AND ");
    dbcmd (dbproc , (char *) " AttributeMap.GroupKey = GroupMap.GroupKey");

    // Check if only specific group's selected
    if (strlen(CreateGroupName) != 0) {
        dbcmd (dbproc , (char *) " AND GroupMap.GroupName ='");
        dbcmd (dbproc , (char *) CreateGroupName );
        dbcmd (dbproc,  (char *) "'");
    }

    dbcmd (dbproc , (char *) " ORDER BY ");
    dbcmd (dbproc , (char *) " ArchitectureMap.ArchitectureKey ,");
    dbcmd (dbproc , (char *) " AttributeMap.GroupKey");


    dbsqlexec (dbproc);

    // now check the results from the SQL server
    while ((result_code = dbresults(dbproc)) != NO_MORE_RESULTS) {
        if (result_code == SUCCEED) {
            dbbind(dbproc, 1, INTBIND, (DBINT) MAX_COLUMN_NAME,
                  (char *)&GroupKey);
            dbbind(dbproc, 2, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)ArchitectureName);
            dbbind(dbproc, 3, INTBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)&ArchitectureKey);
            dbbind(dbproc, 4, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                  (char *)GroupName);
            dbbind(dbproc, 5, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)AttributeName);
            dbbind(dbproc, 6, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)ColumnName);
            dbbind(dbproc, 7, INTBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)&CommonSpecificFlag);
            dbbind(dbproc, 8, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)CommonTableName);
            dbbind(dbproc, 9, NTBSTRINGBIND, (DBINT) MAX_COLUMN_NAME,
                   (char *)SpecificTableName);
            dbbind(dbproc, 10, INTBIND, (DBINT) MAX_COLUMN_NAME,
                  (char *)&Mode);


            // Loop through all the groups Breaking when a Arctecture , Group Changes

            CurKey = -1;
            i = 0;
            ViewSuffix = 0;
            while (dbnextrow(dbproc) != NO_MORE_ROWS ) {
                if ( ((CurKey != GroupKey || CurArchitectureKey != ArchitectureKey) && CurKey != -1)
                     || (i == MAX_COLUMNS) ) {
                    if (CreateV(ViewName, &TableDef[0],dbprocView,i,
                            CurArchitectureKey, CurKey, CurCommonTableName,
                            CurSpecificTableName, ViewSuffix,
                            CurArchitectureName, DropOnlyFlag, LastMode) == FAIL) {

                        LoadString(hInst, IDS_ERR_BADGROUP, szTmpText, 500);
                        LoadString(hInst, IDS_MSC_DBERROR, szMsgTitle, 32);

                        sprintf(szText, (const char *)szTmpText, ViewName);
                        MessageBox(NULL, szText, szMsgTitle, MB_ICONSTOP);
                    }
                    if ( i == MAX_COLUMNS && CurKey == GroupKey)
                        ViewSuffix++;
                    else
                        ViewSuffix = 0;

                    i = 0;
                }      // End if
                strcpy(ViewName, GroupName);
                strcpy(TableDef[i].ColName,ColumnName);
                TableDef[i].ComSpec = CommonSpecificFlag;

                CurArchitectureKey = ArchitectureKey;
                CurKey = GroupKey;
                strcpy(CurCommonTableName,CommonTableName);
                strcpy(CurSpecificTableName,SpecificTableName);
                strcpy(CurArchitectureName,ArchitectureName);
                LastMode = Mode;
                i++;

            }

            // Make sure we Create a view for the last group

            if (CreateV(ViewName,TableDef,dbprocView,i,CurArchitectureKey,
                    CurKey, CurCommonTableName, CurSpecificTableName,
                    ViewSuffix, CurArchitectureName, DropOnlyFlag, LastMode) == FAIL) {
                
                    LoadString(hInst, IDS_ERR_BADGROUP, szTmpText, 500);
                    LoadString(hInst, IDS_MSC_DBERROR, szMsgTitle, 32);

                    sprintf(szText, (const char *)szTmpText, ViewName);
                    MessageBox(NULL, szText, szMsgTitle, MB_ICONSTOP);

            }

            DropView(dbproc,"SNMP_Varbinds");
            DropView(dbproc,"GroupNames");

            if (!DropOnlyFlag) {
                CreateSNMPVarbindsView(dbprocView);
                CreateGroupView(dbprocView);
            }
        }
        else {
            return(FAIL);
            break;
        }
    } // while (TRUE)

    return(RetCode);
}



/******************************************************************************

Create a View that will logicaly represent the DataBase
Typical View Of the Disk Group would be

Create View SMS_Disk as select dwMachineID,
             Disk_COMM.Disk_Index0 , Disk_COMM.File_System0 ,
             Disk_COMM.Storage_Type0 , Disk_SPEC.Volume_Name0 ,
             Disk_SPEC.Serial_Number0 ,Disk_SPEC.Heads0 ,
             Disk_SPEC.Sectors0 , Disk_SPEC.Cylinders0 ,
             Disk_SPEC.__Disk_Full0 , Disk_SPEC.Free_Storage__MByte_0 ,
             Disk_SPEC.Storage_Size__MByte_0 , Disk_SPEC.Storage_Used__MByte_0
        from Disk_COMM  , Disk_SPEC, MachineDataTable
        where Disk_COMM.key =* CommonKey and Disk_SPEC.key =* SpecificKey
         and ArchitectureKey = 5 and GroupKey = 5
*****************************************************************************/

int CreateV(ViewName, TableDef,dbproc,NoCols,ArchitectureKey,GroupKey ,
        CurCommonTableName , CurSpecificTableName,ViewSuffix,
        CurArchitectureName,DropOnlyFlag, Mode)

char * ViewName;
struct VIEWDEF * TableDef;
DBPROCESS * dbproc;
int NoCols,
    ArchitectureKey ,
    GroupKey;
char * CurCommonTableName ,
     * CurSpecificTableName;
int ViewSuffix;
char * CurArchitectureName;
int DropOnlyFlag;


{
    int i ;
    char TableName[MAX_COLUMN_NAME];
    int CommonFlag = FALSE,
    SpecFlag = FALSE;
    BOOL bDirect = FALSE;

    char cmd[MAX_COLUMN_NAME];

    if (Mode == 1) {
        bDirect = TRUE;
    }

    for ( i= 0; ViewName[i]; i++)  // Change all Spaces to _ to derive Table Name
        if (ViewName[i] == ' ')
            ViewName[i] = '_';

    MakeUName(ViewName, CurSpecificTableName, CurCommonTableName);

    if (ViewSuffix) // If this is not the first view
        sprintf(ViewName,"%s%d",ViewName,ViewSuffix);


    DropView ( dbproc,ViewName);

    if( DropOnlyFlag )
        return(SUCCEED);

    // 9/13/1995 a-cvadai
    // First, make sure there is a 0-datakey row in each table
    // so the views can use inner-joins.
    // =======================================================

    if (!bDirect) {
    
        if (strlen(CurSpecificTableName) > 0) {
            dbcmd (dbproc, (char *) " IF NOT EXISTS (select * from ");
            dbcmd (dbproc, (char *) CurSpecificTableName);
            dbcmd (dbproc, (char *) " where datakey = 0) INSERT ");
            dbcmd (dbproc, (char *) CurSpecificTableName);
            dbcmd (dbproc, (char *) " (datakey) values (0)");
            dbsqlexec (dbproc);
            dbresults(dbproc); 
            do {
                while (dbnextrow(dbproc) == REG_ROW) {
                    ;
                }
            } while (dbresults(dbproc) == SUCCEED);

        }
   
        if (strlen(CurCommonTableName) > 0) {
            dbcmd (dbproc, (char *) " IF NOT EXISTS (select * from ");
            dbcmd (dbproc, (char *) CurCommonTableName);
            dbcmd (dbproc, (char *) " where datakey = 0) INSERT ");
            dbcmd (dbproc, (char *) CurCommonTableName);
            dbcmd (dbproc, (char *) " (datakey) values (0)"); 
            dbsqlexec (dbproc);
            dbresults(dbproc);
            do {
                while (dbnextrow(dbproc) == REG_ROW) {
                    ;
                }
            } while (dbresults(dbproc) == SUCCEED);

        }
    }

    dbcmd (dbproc , (char *) "Create View ");
    dbcmd (dbproc , (char *) PREFIX);
    dbcmd (dbproc , (char *) ViewName);
    dbcmd (dbproc , (char *) " as select ");

    if (!bDirect) {
        dbcmd (dbproc ,(char *) "dwMachineID , ");
    }
    else {
        dbcmd (dbproc ,(char *) "MachineID , ");
    }


    for ( i = 0; i < NoCols;i++) {
         // Check if this attribute is in the COMM or SPEC tables
        if (TableDef[i].ComSpec == COMMON)
            strcpy(TableName,CurCommonTableName);
        else
            strcpy(TableName,CurSpecificTableName);

        if (i)    // We need a , after the first Table name
            dbcmd(dbproc,(char *) " , ");

            dbcmd(dbproc,(char *) TableName); // Append the Table Name eg DISK_COMM
            dbcmd(dbproc,(char *) ".");
            dbcmd(dbproc,(char *) TableDef[i].ColName);

    } // End For

    dbcmd (dbproc,(char *)" from ");
    
    if (!bDirect) {
        dbcmd (dbproc,(char *)" MachineDataTable ");

        if (strlen (CurCommonTableName) != 0) {
            dbcmd (dbproc,(char *)" ,");

            // Append the Table Name eg DISK_COMM
            dbcmd(dbproc,(char *) CurCommonTableName);
            dbcmd(dbproc,(char *) "  ");
        }
    }

    if ( strlen (CurSpecificTableName) != 0) {
        if (!bDirect) {
            dbcmd (dbproc,(char *)" , ");
        }

        // Append the Table Name eg DISK_SPEC
        dbcmd(dbproc,(char *) CurSpecificTableName);
        dbcmd(dbproc,(char *) " ");
    }

    if (!bDirect) {

        dbcmd(dbproc ,(char *) "where " );
        if (strlen (CurCommonTableName) != 0) {
            dbcmd(dbproc ,(char *) CurCommonTableName);
            dbcmd(dbproc ,(char *) ".datakey = ");
            dbcmd(dbproc ,(char *) " CommonKey and ");
        }

        if ( strlen (CurSpecificTableName) != 0) {
            dbcmd(dbproc ,(char *) CurSpecificTableName);
            dbcmd(dbproc ,(char *) ".datakey = ");
            dbcmd(dbproc ,(char *) "SpecificKey and ");
        }
        dbcmd(dbproc ,(char *) "ArchitectureKey = ");
        sprintf(cmd,"%d", ArchitectureKey);
        dbcmd(dbproc ,(char *) cmd);
        dbcmd(dbproc ,(char *) " and GroupKey = ");
        sprintf(cmd,"%d", GroupKey);
        dbcmd(dbproc ,(char *) cmd);
    }

    dbsqlexec (dbproc);

    return ( CheckSQLReturn(dbproc, "Create View"));
}




DropView(DBPROCESS *dbproc, char * ViewName)
{

    // Check if View already exists and if so Drop it
    dbcmd (dbproc ,(char *) "IF EXISTS (SELECT * FROM sysobjects ");
    dbcmd (dbproc ,(char *) " WHERE id = object_id('dbo.");
    dbcmd (dbproc ,(char *) PREFIX);
    dbcmd (dbproc ,(char *) ViewName);
    dbcmd (dbproc ,(char *) "'))");
    dbcmd (dbproc ,(char *) " DROP view dbo.");
    dbcmd (dbproc ,(char *) PREFIX);
    dbcmd (dbproc ,(char *) ViewName);

    dbsqlexec (dbproc);

    return( CheckSQLReturn(dbproc, "Drop View"));


}


// Create a View of all the groups that have been made into Views

CreateGroupView(DBPROCESS * dbproc)
{

    dbcmd (dbproc , (char *) "Create View ");
    dbcmd (dbproc , (char *) PREFIX);
    dbcmd (dbproc , (char *) "GroupNames");
    dbcmd (dbproc , (char *) " as select ");
    dbcmd (dbproc , (char *) " GM.GroupName  ");

    dbcmd (dbproc , (char *) " FROM ArchitectureMap AM,");

    dbcmd (dbproc , (char *) " GroupMap GM ");

    dbcmd (dbproc , (char *) " WHERE ");

    dbcmd (dbproc , (char *) " GM.ArchitectureKey = AM.ArchitectureKey ");

    dbsqlexec (dbproc);
    return ( CheckSQLReturn(dbproc, "Create Group View"));
}

CreateSNMPVarbindsView(DBPROCESS * dbproc)
{

    dbcmd (dbproc , (char *) "Create View ");
    dbcmd (dbproc , (char *) PREFIX);
    dbcmd (dbproc , (char *) "SNMP_Varbinds");
    dbcmd (dbproc , (char *) " as select ");
    dbcmd (dbproc , (char *) " MachineID, Variable, ObjectIdentifier, DataType, Data1, Data2, Data3, Data4, Data5, Data6 ");

    dbcmd (dbproc , (char *) " FROM SNMP_Varbinds");

    dbsqlexec (dbproc);
    return ( CheckSQLReturn(dbproc, "Create Group View"));
}


//Make UniqueName

void MakeUName(vName,uName,cName)
    char * vName ,
         * uName , * cName;



{
    char p1[MAX_COLUMNS] = "";
    char p2[MAX_COLUMNS] = "";
    char commstr[] = "_COMM";
    char specstr[] = "_SPEC";
    char *psearch;
    int  lenp1;

    if ( strlen (uName) != 0) {
        if ((psearch = strstr(uName,specstr)) == NULL)
        strcpy(vName,uName);
    else {
        lenp1 = psearch-uName;
        strncpy (p1,uName,lenp1);
        strcpy (p2,psearch+5);
        sprintf(vName,"%s%s",p1,p2);

        }
    }
    else {
        if ((psearch = strstr(cName,commstr)) == NULL)
        strcpy(vName,cName);
    else {
        lenp1 = psearch-cName;
        strncpy (p1,cName,lenp1);
        strcpy (p2,psearch+5);
        sprintf(vName,"%s%s",p1,p2);
        }

    }

}


//     Check SQL return and empty return buffer

CheckSQLReturn(DBPROCESS * dbproc, char *Action)
{
    RETCODE result_code;
    int iResult = FAIL;
    
    while ((result_code = dbresults(dbproc)) != NO_MORE_RESULTS) {
        if (result_code == SUCCEED) {
            iResult = SUCCEED;
            while (dbnextrow(dbproc) != NO_MORE_ROWS)
                ;  /* do nothing */
        }
        else {
             return(FAIL);
             break;
        }
    }
    return (iResult);
}


//
int err_handler(DBPROCESS * dbproc, int severity, int dberr, int oserr,
                char * dberrstr, char * oserrstr)
{

    char    szString[512];
    char    szMsgTitle[32];
    int     iString;

    // Ignore any 'Changed context' errors.

    if (dberr == 5701 || dberr == 5703) {
        return 0;
    }

    LoadString(hInst, IDS_ERR_SQL_ERROR, szString, MAX_PATH);
    LoadString(hInst, IDS_MSC_DBERROR, szMsgTitle, 32);

    iString = sizeof(szString) - strlen(szString);
    if (dberrstr != NULL) {
        strncpy(szString, dberrstr, iString);
    }
    else if (oserr != DBNOERR && oserrstr != NULL) {
        strncpy(szString, oserrstr, iString);
    }
    szString[sizeof(szString)-1] = 0;

    if (strstr(szString, "General SQL Server") == NULL) {
        MessageBox(NULL, szString, szMsgTitle, MB_ICONSTOP);    
    }

    return(INT_CANCEL);
}
