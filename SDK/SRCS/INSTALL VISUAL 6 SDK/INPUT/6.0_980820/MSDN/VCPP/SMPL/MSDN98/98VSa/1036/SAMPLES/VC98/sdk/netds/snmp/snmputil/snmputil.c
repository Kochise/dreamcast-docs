/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1991-1995  Microsoft Corporation

Module Name:

    snmputil.c

Abstract:

    Sample SNMP Management API usage for Windows NT.

    This file is an example of how to code management applications using
    the SNMP Management API for Windows NT.  It is similar in operation to
    the other commonly available SNMP command line utilities.

    Extensive comments have been included to describe its structure and
    operation.  See also "Microsoft Windows/NT SNMP Programmer's Reference".

Created:

    28-Jun-1991

Revision History:

--*/


static char *vcsid = "@(#) $Logfile:   N:/agent/mgmtapi/vcs/snmputil.c_v  $ $Revision:   1.5  $";


// General notes:
//   Microsoft's SNMP Management API for Windows NT is implemented as a DLL
// that is linked with the developer's code.  These APIs (examples follow in
// this file) allow the developer's code to generate SNMP queries and receive
// SNMP traps.  A simple MIB compiler and related APIs are also available to
// allow conversions between OBJECT IDENTIFIERS and OBJECT DESCRIPTORS.


// Necessary includes.

#include <windows.h>

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <snmp.h>
#include <mgmtapi.h>


// Constants used in this example.

#define GET     1
#define GETNEXT 2
#define WALK    3
#define TRAP    4

#define TIMEOUT 6000 /* milliseconds */
#define RETRIES 3


// Main program.

INT _CRTAPI1 main(
    IN int  argumentCount,
    IN char *argumentVector[])
    {
    INT                operation;
    LPSTR              agent;
    LPSTR              community;
    RFC1157VarBindList variableBindings;
    LPSNMP_MGR_SESSION session;

    INT        timeout = TIMEOUT;
    INT        retries = RETRIES;

    BYTE       requestType;
    AsnInteger errorStatus;
    AsnInteger errorIndex;
    char        *chkPtr = NULL;


    // Parse command line arguments to determine requested operation.

    // Verify number of arguments...
    if      (argumentCount < 5 && argumentCount != 2)
        {
        printf("Error:  Incorrect number of arguments specified.\n");
        printf(
"\nusage:  snmputil [get|getnext|walk] agent community oid [oid ...]\n");
        printf(
  "        snmputil trap\n");

        return 1;
        }

    // Get/verify operation...
    argumentVector++;
    argumentCount--;
    if      (!strcmp(*argumentVector, "get"))
        operation = GET;
    else if (!strcmp(*argumentVector, "getnext"))
        operation = GETNEXT;
    else if (!strcmp(*argumentVector, "walk"))
        operation = WALK;
    else if (!strcmp(*argumentVector, "trap"))
        operation = TRAP;
    else
        {
        printf("Error:  Invalid operation, '%s', specified.\n",
               *argumentVector);

        return 1;
        }

    if (operation != TRAP)
        {
        if (argumentCount < 4)
            {
            printf("Error:  Incorrect number of arguments specified.\n");
            printf(
"\nusage:  snmputil [get|getnext|walk] agent community oid [oid ...]\n");
            printf(
  "        snmputil trap\n");

            return 1;
            }

        // Get agent address...
        argumentVector++;
        argumentCount--;
        agent = (LPSTR)SNMP_malloc(strlen(*argumentVector) + 1);
        strcpy(agent, *argumentVector);

        // Get agent community...
        argumentVector++;
        argumentCount--;
        community = (LPSTR)SNMP_malloc(strlen(*argumentVector) + 1);
        strcpy(community, *argumentVector);

        // Get oid's...
        variableBindings.list = NULL;
        variableBindings.len = 0;

        while(--argumentCount)
            {
            AsnObjectIdentifier reqObject;

            argumentVector++;

            // Convert the string representation to an internal representation.
            if (!SnmpMgrStrToOid(*argumentVector, &reqObject))
                {
                printf("Error: Invalid oid, %s, specified.\n", *argumentVector);

                return 1;
                }
            else
                {
                // Since sucessfull, add to the variable bindings list.
                variableBindings.len++;
                if ((variableBindings.list = (RFC1157VarBind *)SNMP_realloc(
                    variableBindings.list, sizeof(RFC1157VarBind) *
                    variableBindings.len)) == NULL)
                    {
                    printf("Error: Error allocating oid, %s.\n",
                           *argumentVector);

                    return 1;
                    }

                variableBindings.list[variableBindings.len - 1].name =
                    reqObject; // NOTE!  structure copy
                variableBindings.list[variableBindings.len - 1].value.asnType =
                    ASN_NULL;
                }
            } // end while()

        // Make sure only one variable binding was specified if operation
        // is WALK.
        if (operation == WALK && variableBindings.len != 1)
            {
            printf("Error: Multiple oids specified for WALK.\n");

            return 1;
            }


        // Establish a SNMP session to communicate with the remote agent.  The
        // community, communications timeout, and communications retry count
        // for the session are also required.

        if ((session = SnmpMgrOpen(agent, community, timeout, retries)) == NULL)
            {
            printf("error on SnmpMgrOpen %d\n", GetLastError());

            return 1;
            }

        } // end if(TRAP)


    // Determine and perform the requested operation.

    if      (operation == GET || operation == GETNEXT)
        {
        // Get and GetNext are relatively simple operations to perform.
        // Simply initiate the request and process the result and/or
        // possible error conditions.


        if (operation == GET)
            requestType = ASN_RFC1157_GETREQUEST;
        else
            requestType = ASN_RFC1157_GETNEXTREQUEST;


        // Request that the API carry out the desired operation.

        if (!SnmpMgrRequest(session, requestType, &variableBindings,
                            &errorStatus, &errorIndex))
            {
            // The API is indicating an error.

            printf("error on SnmpMgrRequest %d\n", GetLastError());
            }
        else
            {
            // The API succeeded, errors may be indicated from the remote
            // agent.

            if (errorStatus > 0)
                {
                printf("Error: errorStatus=%d, errorIndex=%d\n",
                       errorStatus, errorIndex);
                }
            else
                {
                // Display the resulting variable bindings.

                UINT i;
                char *string = NULL;

                for(i=0; i < variableBindings.len; i++)
                    {
                    SnmpMgrOidToStr(&variableBindings.list[i].name, &string);
                    printf("Variable = %s\n", string);
                    if (string) SNMP_free(string);

                    printf("Value    = ");
                    SnmpUtilPrintAsnAny(&variableBindings.list[i].value);

                    printf("\n");
                    } // end for()
                }
            }


        // Free the variable bindings that have been allocated.

        SnmpUtilVarBindListFree(&variableBindings);


        }
    else if (operation == WALK)
        {
        // Walk is a common term used to indicate that all MIB variables
        // under a given OID are to be traversed and displayed.  This is
        // a more complex operation requiring tests and looping in addition
        // to the steps for get/getnext above.


        AsnObjectIdentifier root;
        AsnObjectIdentifier tempOid;


        SnmpUtilOidCpy(&root, &variableBindings.list[0].name);

        requestType = ASN_RFC1157_GETNEXTREQUEST;


        while(1)
            {
            if (!SnmpMgrRequest(session, requestType, &variableBindings,
                                &errorStatus, &errorIndex))
                {
                // The API is indicating an error.

                printf("error on SnmpMgrRequest %d\n", GetLastError());

                break;
                }
            else
                {
                // The API succeeded, errors may be indicated from the remote
                // agent.


                // Test for end of subtree or end of MIB.

                if (errorStatus == SNMP_ERRORSTATUS_NOSUCHNAME ||
                    SnmpUtilOidNCmp(&variableBindings.list[0].name,
                                    &root, root.idLength))
                    {
                    printf("End of MIB subtree.\n\n");

                    break;
                    }


                // Test for general error conditions or sucesss.

                if (errorStatus > 0)
                    {
                    printf("Error: errorStatus=%d, errorIndex=%d \n",
                           errorStatus, errorIndex);

                    break;
                    }
                else
                    {
                    // Display resulting variable binding for this iteration.

                    char *string = NULL;

                    SnmpMgrOidToStr(&variableBindings.list[0].name, &string);
                    printf("Variable = %s\n", string);
                    if (string) SNMP_free(string);

                    printf("Value    = ");
                    SnmpUtilPrintAsnAny(&variableBindings.list[0].value);

                    printf("\n");
                    }
                } // end if()


            // Prepare for the next iteration.  Make sure returned oid is
            // preserved and the returned value is freed.

            SnmpUtilOidCpy(&tempOid, &variableBindings.list[0].name);

            SnmpUtilVarBindFree(&variableBindings.list[0]);

            SnmpUtilOidCpy(&variableBindings.list[0].name, &tempOid);
            variableBindings.list[0].value.asnType = ASN_NULL;

            SnmpUtilOidFree(&tempOid);

            } // end while()


        // Free the variable bindings that have been allocated.

        SnmpUtilVarBindListFree(&variableBindings);

        SnmpUtilOidFree(&root);


        }
    else if (operation == TRAP)
        {
        // Trap handling can be done two different ways: event driven or
        // polled.  The following code illustrates the steps to use event
        // driven trap reception in a management application.


        HANDLE hNewTraps = NULL;


        if (!SnmpMgrTrapListen(&hNewTraps))
            {
            printf("error on SnmpMgrTrapListen %d\n", GetLastError());
            }
        else
            {
            printf("snmputil: listening for traps...\n");
            }


        while(1)
            {
            DWORD dwResult;

            if ((dwResult = WaitForSingleObject(hNewTraps, 0xffffffff))
                == 0xffffffff)
                {
                printf("error on WaitForSingleObject %d\n",
                       GetLastError());
                }
            else if (!ResetEvent(hNewTraps))
                {
                printf("error on ResetEvent %d\n", GetLastError());
                }
            else
                {
                AsnObjectIdentifier enterprise;
                AsnNetworkAddress   IPAddress;
                AsnInteger          genericTrap;
                AsnInteger          specificTrap;
                AsnTimeticks        timeStamp;
                RFC1157VarBindList  variableBindings;

                UINT i;
                char *string = NULL;

                while(SnmpMgrGetTrap(&enterprise, &IPAddress, &genericTrap,
                                     &specificTrap, &timeStamp, &variableBindings))
                    {
                    printf("snmputil: trap generic=%d specific=%d\n",
                           genericTrap, specificTrap);
                    if (IPAddress.length == 4) {
                        printf("  from -> %d.%d.%d.%d\n",
                             (int)IPAddress.stream[0], (int)IPAddress.stream[1],
                             (int)IPAddress.stream[2], (int)IPAddress.stream[3]);

                    }
                    if (IPAddress.dynamic) {
                        SNMP_free(IPAddress.stream);
                    }

                    for(i=0; i < variableBindings.len; i++)
                        {
                        SnmpMgrOidToStr(&variableBindings.list[i].name, &string);
                        printf("Variable = %s\n", string);
                        if (string) SNMP_free(string);

                        printf("Value    = ");
                        SnmpUtilPrintAsnAny(&variableBindings.list[i].value);
                        } // end for()
                    printf("\n");


                    SnmpUtilOidFree(&enterprise);

                    SnmpUtilVarBindListFree(&variableBindings);
                    }
                }
            } // end while()


        } // end if(operation)


    if (operation != TRAP)
        {
        // Close SNMP session with the remote agent.

        if (!SnmpMgrClose(session))
            {
            printf("error on SnmpMgrClose %d\n", GetLastError());

            return 1;
            }
        }


    // Let the command interpreter know things went ok.

    return 0;

    } // end main()
