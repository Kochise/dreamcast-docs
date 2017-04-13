/* need to look for SUPPORTS_SETTING_SECURITY before using XC_SECURITY*     */
/*****************************************************************************
 *
 *  MODULE NAME: CPICINIT.C
 *
 *  COPYRIGHTS:
 *             This module contains code made available by IBM
 *             Corporation on an AS IS basis.  Any one receiving the
 *             module is considered to be licensed under IBM copyrights
 *             to use the IBM-provided source code in any way he or she
 *             deems fit, including copying it, compiling it, modifying
 *             it, and redistributing it, with or without
 *             modifications.  No license under any IBM patents or
 *             patent applications is to be implied from this copyright
 *             license.
 *
 *             A user of the module should understand that IBM cannot
 *             provide technical support for the module and will not be
 *             responsible for any consequences of use of the program.
 *
 *             Any notices, including this one, are not to be removed
 *             from the module without the prior written consent of
 *             IBM.
 *
 *  AUTHOR:    Peter J. Schwaller
 *             VNET:     PJS at RALVM6           Tie Line: 444-4376
 *             Internet: pjs@ralvm6.vnet.ibm.com     (919) 254-4376
 *
 *  FUNCTION:  Provides procedures to be used in programs to help them set up
 *             all of the partner program information for CPI-C.  All of the
 *             information is stored in a CPICINIT structure.  The
 *             information is stored in the structure using default and set
 *             calls.
 *
 *             The cpicinit_setup_conversation procedure can then be used
 *             to issue the CPI-C calls to setup a conversation_id.
 *             All of the CPI-C calls from CMINIT to just before CMALLC
 *             are issued.  The program should issue CMALLC on its own
 *             so it can control error handling.
 *
 *             By collecting all of the partner program information within
 *             a single object, restarting a conversation that has failed
 *             is made easier, since the information does not have to
 *             be collected or read from a profile again.
 *
 *  AVAILABILITY:
 *             These sample programs and source are also available on
 *             CompuServe through the APPC Information Exchange.  To get
 *             to the APPC forum just type 'GO APPC' from any CompuServe
 *             prompt.  The samples are available in the Sample Programs
 *             library section.  Just search on the keyword CPICPGMS to
 *             find all the samples in this series.
 *
 *             Updates for the sample programs and support for many more
 *             CPI-C platforms will also be made available on CompuServe.
 *
 *  RELATED FILES:
 *             Uses CPICINIT.H
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Changed all printf and fprintf calls to use a write_*() call.
 *  08/18/92   Fixed problem with imbedded \0 added setting def_sym_dest_name
 *             in cpicinit_default_sym_dest_name().  This fixes a problem
 *             seen in MVS.
 *  08/23/92   Removed cpicinit_default_destination() and associated
 *             processing.   After review, we decided that this call was
 *             extraneous and that cpicinit_default_sym_dest_name() was
 *             a better mechanism for a default destination.
 *  11/13/92   Changed most return values from TRUE/FALSE to CPICINIT_OK and
 *             other return codes.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * OVERVIEW OF CPICINIT CALLS
 *
 * cpicinit_new()                     Creates a CPICINIT object.
 *                                    This must be done before any other
 *                                    cpicinit calls can be used.
 *
 * cpicinit_default_tp_name()         These calls set the initial values
 * cpicinit_default_mode_name()       for CPICINIT parameters.  These should
 * cpicinit_default_sym_dest_name()   all be issued right after the CPICINIT
 *                                    object is created.  Usually, these calls
 *                                    should set the values that should be used
 *                                    only if the user does not specify new
 *                                    values.
 *
 * cpicinit_set_tp_name()             These calls also set the values for
 * cpicinit_set_mode_name()           CPICINIT parameters.  These calls should
 * cpicinit_set_destination()         be used to set values from user input
 *                                    or profile values.  These calls should be
 *                                    used after the user has specified values,
 *                                    through command line parameters, program
 *                                    profiles, or interactive input.
 *
 *   Security calls - only available where supported by CPI-C
 * cpicinit_set_userid                Sets the userid for the conversation.
 * cpicinit_set_password              Sets the password for the conversation.
 * cpicinit_query_password_needed     If a userid was set, then a password
 *                                    is required.
 * cpicinit_get_password              Let cpicinit prompt the user for a
 *                                    password.
 * cpicinit_set_security_type         Set the security type for this conv.
 *
 * cpicinit_setup_conversation()      Handles all CMINIT and set calls.
 *                                    Should be used by the calling program
 *                                    instead of CMINIT.  See description
 *                                    of the procedure for more details.
 *
 * cpicinit_destroy()                 Destroys the CPICINIT object.
 *
 * cpicinit_pln_valid()               These are internal calls used by
 * cpicinit_mode_valid()              cpicinit_setup_conversation.
 *
 *****************************************************************************/

#if defined(WIN32) || defined(WINDOWS)
#include <windows.h>
#endif

#include "wincpic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* CPI-C error handling routines */
#include "cpicerrs.h"

/* CPI-C initialization routines */
#include "cpicinit.h"

/* Collection of routines with special ported version for each platform */
#include "cpicport.h"


/******************************************************************************
 *
 *  cpicinit_new
 *
 *  Creates a new CPICINIT object and returns its handle to the caller.
 *  This object handle must be used on all subsequent cpicinit calls.
 *  All internal fields are initialized appropriately.
 *
 *  If memory cannot be allocated for the CPICINIT object, NULL will be
 *  returned as the result of the call.  Otherwise, the return value will
 *  be a pointer to the CPICINIT object.
 *
 *****************************************************************************/
CPICINIT *
cpicinit_new(void)
{
    CPICINIT * cpicinit;

    cpicinit = (CPICINIT *) malloc(sizeof(*cpicinit));
    if (cpicinit == NULL) {
        return NULL;
    }

    /* Initialize the entire structure to 0's */
    memset(cpicinit,
           0,
           sizeof(*cpicinit));

    /* Set the default symbolic destination name to BLANKs. */
    /* This is the "default-default" if nothing else is set. */
    memset(cpicinit -> def_sym_dest_name,
           ' ',
           sizeof(cpicinit->def_sym_dest_name));
    cpicinit->def_sym_dest_name[sizeof(cpicinit->def_sym_dest_name)-1] = '\0';

    /* Indicate that the values have not yet been SET */
    cpicinit -> set_mode_name = NOT_SET;
    cpicinit -> set_destination = NOT_SET;
    cpicinit -> set_tp_name = NOT_SET;
    cpicinit -> set_userid = NOT_SET;
    cpicinit -> set_password = NOT_SET;
    cpicinit -> security_type = XC_SECURITY_SAME;

    /*
     * This flag is usedby other cpicinit calls to decide whether or not
     * to show errors encountered during processing.
     *
     * If this value is turned off, the cpicinit routines will not produce
     * any output, even in the event of an error.
     */
    cpicinit -> show_error = SET;


    /* return a pointer to the structure */
    return cpicinit;
}

/******************************************************************************
 *
 *  cpicinit_default_sym_dest_name
 *
 *  Sets a symbolic destination name to be used if no call is made to
 *  cpicinit_set_destination().
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_default_sym_dest_name( CPICINIT * cpicinit,
                                char *     def_sym_dest_name)
/*
 * Set the default symbolic destination name to be used if no destination
 * is ever set.
 */
{
    int length;
    int rc;


    /* Set the default symbolic destination name to BLANKs. */
    memset(cpicinit -> def_sym_dest_name,
           ' ',
           sizeof(cpicinit->def_sym_dest_name));
    cpicinit->def_sym_dest_name[sizeof(cpicinit->def_sym_dest_name)-1] = '\0';

    length = strlen(def_sym_dest_name);

    if (length < sizeof(cpicinit->def_sym_dest_name)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->def_sym_dest_name,
               def_sym_dest_name,
               length);
    } else {
        rc = CPICINIT_OK;
    }

    return rc;
}

/******************************************************************************
 *
 *  cpicinit_default_tp_name
 *
 *  Sets a symbolic destination name to be used if no call is made to
 *  cpicinit_set_destination().
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_default_tp_name(CPICINIT * cpicinit,
                         char *     tp_name)
/* initialize the tp_name */
{
    int length;
    int rc;

    length = strlen(tp_name);

    if (length < sizeof(cpicinit->tp_name)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->tp_name,
               tp_name,
               length);
        cpicinit->tp_name[length] = '\0';
    } else {
        rc = CPICINIT_OK;
        if (cpicinit -> show_error) {
             write_error(
                     "The TP name you specified is too long:\n%s\n",
                     tp_name);
             write_error(
                    "The maximum length of a TP name is %u characters.\n",
                    sizeof(cpicinit->tp_name)-1);
             write_error(
                     "TP name of %s will be used.\n", cpicinit->tp_name);
        }
    }

    return rc;
}

/******************************************************************************
 *
 *  cpicinit_default_mode_name
 *
 *  Sets the default mode name to be used if there is no call made to
 *  cpicinit_set_mode_name().
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_default_mode_name(CPICINIT * cpicinit,
                           char *     mode_name)
/* initialize the mode name */
{
    int length;
    int rc;

    length = strlen(mode_name);

    if (length < sizeof(cpicinit->mode_name)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->mode_name,
               mode_name,
               length);
        cpicinit->mode_name[length] = '\0';
        strupr(cpicinit->mode_name);
    } else {
        rc = CPICINIT_OK;
        if (cpicinit -> show_error) {
            write_error(
                    "The mode name you specified is too long:\n%s\n",
                    mode_name);
            write_error(
                   "The maximum length of a mode name is %u characters.\n",
                   sizeof(cpicinit->mode_name)-1);
            write_error(
                   "Mode name of %s will be used.\n", cpicinit->mode_name);
        }
    }

    return rc;
}


/*
 * The major difference between the default calls above and the set calls
 * below is the setting of a flag in the set calls indicating that the user
 * has specified this value.  This flag is used later as an indication that
 * any value set by the symbolic destination name entries should be
 * overridden.
 */


/******************************************************************************
 *
 *  cpicinit_set_tp_name
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_set_tp_name(CPICINIT * cpicinit,
                     char *     tp_name)
{
    cpicinit->set_tp_name = SET;
    return cpicinit_default_tp_name(cpicinit, tp_name);
}

/******************************************************************************
 *
 *  cpicinit_set_mode_name
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_set_mode_name(CPICINIT * cpicinit,
                       char *     mode_name)
{
    cpicinit->set_mode_name = SET;
    return cpicinit_default_mode_name(cpicinit, mode_name);
}

/******************************************************************************
 *
 *  cpicinit_set_destination
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_set_destination(CPICINIT * cpicinit,
                         char *     destination)
{
    int length;
    int rc;

    cpicinit->set_destination = SET;

    length = strlen(destination);

    if (length < sizeof(cpicinit->destination)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->destination,
               destination,
               length);
        cpicinit->destination[length] = '\0';
    } else {
        rc = CPICINIT_OK;
        if (cpicinit -> show_error) {
            write_error(
                    "The destination you specified is too long:\n%s\n",
                    destination);
            write_error(
            "The maximum length of a destination is %u characters.\n",
                sizeof(cpicinit->destination)-1);
            write_error(
                    "Destination %s will be used.\n", cpicinit->destination);
        }
    }

    return rc;
}

/******************************************************************************
 *
 *  cpicinit_set_userid
 *
 *  Sets the userid to be used for security on the conversation.  Issuing
 *  this call implies that the conversation will use security=PROGRAM;
 *  a password will also be required in order to get a conversation.
 *  The password should be set using either the cpicinit_set_password() call
 *  or the cpicinit_get_password() call.
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_set_userid(CPICINIT * cpicinit,
                    char *     userid)
/* initialize the userid */
{
    int length;
    int rc;

    length = strlen(userid);

    if (length < sizeof(cpicinit->userid)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->userid,
               userid,
               length);
        cpicinit->userid[length] = '\0';
        cpicinit->set_userid = SET;
        cpicinit->security_type = XC_SECURITY_PROGRAM;
    } else {
        rc = CPICINIT_OK;
        if (cpicinit -> show_error) {
            write_error(
                    "The userid you specified is too long:\n%s\n",
                    userid);
            write_error(
                   "The maximum length of a userid is %u characters.\n",
                   sizeof(cpicinit->userid)-1);
        }
    }

    return rc;

}
/******************************************************************************
 *
 *  cpicinit_query_password_needed
 *
 *  Can be used by the program to inquire whether a password will be required
 *  to establish a conversation.  This can be used by a program instead of
 *  keeping track itself of whether a userid has been specified.  If a password
 *  is required, the password should be set using either the
 *  cpicinit_set_password() call or the cpicinit_get_password() call.
 *
 *  Returns:
 *    TRUE   if password is required
 *    FALSE  if no password should be set
 *
 *****************************************************************************/
int
cpicinit_query_password_needed(CPICINIT * cpicinit)
{
    if (cpicinit->set_userid == SET && cpicinit->set_password == NOT_SET) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/******************************************************************************
 *
 *  cpicinit_set_password
 *
 *  Sets the password to be used with security=PROGRAM.  This call should be
 *  used in conjunction with the cpicinit_set_userid() call.
 *
 *  Returns:
 *    CPICINIT_OK,     if there was no error.
 *    CPICINIT_ERROR,  if there was an error.
 *
 *****************************************************************************/
int
cpicinit_set_password(CPICINIT * cpicinit,
                    char *     password)
/* initialize the password */
{
    int length;
    int rc;

    length = strlen(password);

    if (length < sizeof(cpicinit->password)) {
        rc = CPICINIT_ERROR;
        memcpy(cpicinit->password,
               password,
               length);
        cpicinit->password[length] = '\0';
        cpicinit->set_password = SET;
        cpicinit->security_type = XC_SECURITY_PROGRAM;
    } else {
        rc = CPICINIT_OK;
        if (cpicinit -> show_error) {
            write_error(
                    "The password you specified is too long:\n%s\n",
                    password);
            write_error(
                   "The maximum length of a password is %u characters.\n",
                   sizeof(cpicinit->password)-1);
        }
    }

    return rc;
}


/******************************************************************************
 *
 *  cpicinit_get_password
 *
 *****************************************************************************/
void
cpicinit_get_password(CPICINIT * cpicinit)
{
    write_output("\nPassword: ");           /* display the prompt            */

    if (!get_password(cpicinit->password, sizeof(cpicinit->password)-1)) {
        cpicinit->set_password = SET;
        cpicinit->security_type = XC_SECURITY_PROGRAM;
    }
    return;
}

/******************************************************************************
 *
 *  cpicinit_set_security_type
 *
 *****************************************************************************/
void
cpicinit_set_security_type(CPICINIT * cpicinit,
                           unsigned long security_type)
{
    cpicinit->security_type = security_type;
}


/******************************************************************************
 *
 *  cpicinit_setup_conversation
 *
 *  The goal of this procedure is to initialize a CPI-C conversation ID
 *  and make sure that partner destination information is all specified.
 *  This destination information includes partner LU name, mode name,
 *  and TP name.
 *
 *  To be as flexible as possible, the destination parameter can serve
 *  a dual role.  If specified, the destination is first used as the
 *  symbolic destination name.  If this does not produce a valid partner
 *  LU name, another symbolic destination name will be used and the
 *  destination parameter will be used instead as a partner LU name.
 *
 *  AN OVERVIEW OF THE PROCEDURE
 *
 *  If the destination was SET
 *      use destination as a symbolic destination name
 *      If CMINIT failed or there was no partner LU name extracted
 *          use the default symbolic destination name or all blanks
 *          use the destination as a partner LU name
 *
 *****************************************************************************/
int
cpicinit_setup_conversation(CPICINIT *      cpicinit,
                            unsigned char * cm_conv_id,
                            CPICERR *       cpicerr)
{
    CM_INT32 cm_rc = CM_OK;
    CM_INT32 length;
    int      dest_len;
    char sym_dest_name[9];

    /* check if a destination was set by the cpicinit_set_destination() call */
    if (cpicinit->set_destination == SET) {

        /* check if the destination could be a symbolic destination name     */
        if (((dest_len = strlen(cpicinit->destination)) <
                                                         MAX_SYM_DEST_NAME)) {
            /*
             * Try to use the specified destination as a symbolic
             * destination name.  A symbolic destination name is blank
             * padded and must contain all uppercase characters.
             */

            memset(sym_dest_name,           /* Initialize the sym dest name  */
                   ' ',                     /* to all blanks.                */
                   sizeof(sym_dest_name));

            memcpy(sym_dest_name,           /* Copy the destination into the */
                   cpicinit->destination,   /* sym dest name.                */
                   dest_len);
                                            /* place the null terminator     */
            sym_dest_name[MAX_SYM_DEST_NAME - 1] = '\0';

            strupr(sym_dest_name);          /* sym dest must be uppercase    */

            /*
             * Since we are using the destination as a sym_dest, make sure
             * we don't also use it as a partner LU name.
             */
            cpicinit->set_destination = NOT_SET;

            cminit(cm_conv_id,
                   (unsigned char *)sym_dest_name,
                   &cm_rc);

        } else {
            /*
             * The destination was too long to be a symbolic destination name.
             */
        }



        if (cm_rc != CM_OK || !cpicinit_pln_valid(cm_conv_id)) {

            /*
             * Since the destination was not a sym_dest, we can use it
             * later as a partner LU name.
             */
            cpicinit->set_destination = SET;

            /*
             * Try to use the default symbolic destination name.  If
             * configured, this symbolic destination can be used to
             * initialize the partner LU name and mode name entries,
             * or left blank.
             */
            cminit(cm_conv_id,
                   (unsigned char *)cpicinit->def_sym_dest_name,
                   &cm_rc);

            if (cm_rc != CM_OK) {
                /*
                 * Nothing else worked, so let's try the blank symbolic
                 * destination name.  All CPI-C values will be initialized
                 * to non usable values.
                 */
                cminit(cm_conv_id,
                       (unsigned char *)BLANK_SYM_DEST_NAME,
                       &cm_rc);
                if (cm_rc != CM_OK) {
                    return cpicerr_handle_rc(cpicerr, MSG_CMINIT, cm_rc);
                }

                /*
                 * Since the blank symbolic destination name was used,
                 * we must set the partner LU name and mode even if we
                 * use the defaults.
                 */
                cpicinit->set_destination = cpicinit->set_mode_name = SET;

            }

        }

    } else {
        /*
         * Although no destination was specified, we can try to continue
         * by using the default symbolic destination name.  If this entry
         * is configured with a valid partner LU, we may be able to
         * establish a connection with a partner.
         */
        cminit(cm_conv_id,
               (unsigned char * )cpicinit->def_sym_dest_name,
               &cm_rc);
        if (cm_rc != CM_OK) {
            /*
             * Fill in conversation information for CPI-C error reporting.
             */
            cpicerr_set_conv_id(cpicerr, cm_conv_id);
            return cpicerr_handle_rc(cpicerr, MSG_CMINIT, cm_rc);
        }
    }

    /*
     * Fill in conversation information for CPI-C error reporting.
     */
    cpicerr_set_conv_id(cpicerr, cm_conv_id);

    if (cpicinit->set_destination == SET) {
        CM_INT32 dest_length;
        dest_length = strlen(cpicinit->destination);

#if defined(PLN_COULD_REQUIRE_LOWERCASE)
        /*
         * strupr should only be performed if the partner LU name is
         * a fully qualified name.
         */
#ifdef FAPI
        if ((strchr(cpicinit->destination,'.') != NULL) ||
            (get_machine_mode() == 0)) {
            strupr(cpicinit->destination);
        }
#else
        if (strchr(cpicinit->destination,'.') != NULL) {
            strupr(cpicinit->destination);
        }
#endif
#else
        strupr(cpicinit->destination);
#endif

        cmspln(cm_conv_id,                  /* Set partner LU name           */
               (unsigned char *)cpicinit->destination,
               &dest_length,
               &cm_rc);
        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_CMSPLN, cm_rc);
    }

    /*
     * Since there is no way to query the TP name, we will always set it.
     * The default TP name can be overridden on the cpicinit_set_tp_name
     * call.
     */

    length = strlen(cpicinit->tp_name);
    cmstpn(cm_conv_id,                      /* Set TP name                   */
           (unsigned char *)cpicinit->tp_name,
           &length,
           &cm_rc);
    if (cm_rc != CM_OK)
        return cpicerr_handle_rc(cpicerr, MSG_CMSTPN, cm_rc);

    /*
     * If there was a cpicinit_set_mode_name call made previously or
     * present mode name is not initialized, we need to set the mode
     * name.
     */
    if ((cpicinit->set_mode_name == SET) ||
                                         !cpicinit_mode_valid(cm_conv_id)) {
        length = strlen(cpicinit->mode_name);
        cmsmn(cm_conv_id,                   /* Set mode name                 */
              (unsigned char *)cpicinit->mode_name,
              &length,
              &cm_rc);
        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_CMSMN, cm_rc);
    }

#if defined(SUPPORTS_SETTING_SECURITY)
    /*
     * If there was a cpicinit_set_userid AND cpicinit_set_password call made
     * previously, we need to set the security parameters.  The security
     * functions are not available on all CPI-C platforms.
     */

    if (cpicinit->security_type == XC_SECURITY_NONE) {
        CM_INT32 security_type;
        security_type = XC_SECURITY_NONE;
        xcscst(cm_conv_id,                  /* Set Security Type             */
               &security_type,
               &cm_rc);
        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_XCSCST, cm_rc);
    } else {
        if ((cpicinit->set_userid == SET) && (cpicinit->set_password == SET)) {
            CM_INT32 security_type;
            security_type = XC_SECURITY_PROGRAM;
            xcscst(cm_conv_id,              /* Set Security Type             */
                   &security_type,
                   &cm_rc);
            if (cm_rc != CM_OK)
                return cpicerr_handle_rc(cpicerr, MSG_XCSCST, cm_rc);

            length = strlen(cpicinit->userid);
            xcscsu(cm_conv_id,              /* Set Security Userid           */
                   (unsigned char *)cpicinit->userid,
                   &length,
                   &cm_rc);
            if (cm_rc != CM_OK)
                return cpicerr_handle_rc(cpicerr, MSG_XCSCSU, cm_rc);

            length = strlen(cpicinit->password);
            xcscsp(cm_conv_id,              /* Set Security Password         */
                   (unsigned char *)cpicinit->password,
                   &length,
                   &cm_rc);
            if (cm_rc != CM_OK)
                return cpicerr_handle_rc(cpicerr, MSG_XCSCSP, cm_rc);

        }
    }

#endif

    return FALSE;
}


/******************************************************************************
 *
 *  cpicinit_destroy
 *
 *  This function is the inverse of the cpicinit_new() call.  All memory
 *  allocated by cpicinit_new() is freed.
 *
 *  This function has no return code.
 *
 *****************************************************************************/
void
cpicinit_destroy(CPICINIT * cpicinit)
{
    free(cpicinit);
    return;
}

/******************************************************************************
 *
 *  cpicinit_pln_valid
 *
 *  Internal function, used by cpic_setup_conversation().
 *
 *  This function is used after a cminit() call to ensure that there was
 *  a partner LU name configured with the symbolic destination used on
 *  cminit().  If there was no partner LU name configured with the symbolic
 *  destination name, a partner LU name will have to be set with the cmspln()
 *  call.
 *
 *  Returns:
 *    TRUE  if a partner LU name was configured
 *    FALSE is there was no partner LU name configured
 *
 *****************************************************************************/
int
cpicinit_pln_valid(unsigned char * cm_conv_id)
{
    unsigned char  destination[MAX_DESTINATION]; /* variable to store the    */
                                            /* extracted partner LU name     */
    CM_INT32       length = 0;              /* length of partner LU name     */
    CM_RETURN_CODE cm_rc;                   /* CPI-C return code             */
    int            rc;                      /* procedure return code         */

    cmepln(cm_conv_id,                      /* extract partner LU name       */
           destination,
           &length,                         /* length of partner LU name     */
           &cm_rc );

    if (cm_rc != CM_OK || (length == 1 && destination[0] == ' ')) {
        rc = FALSE;
    } else {
        rc = TRUE;
    }
    return rc;
}

/******************************************************************************
 *
 *  cpicinit_mode_valid
 *
 *  Internal function, used by cpic_setup_conversation().
 *
 *  This function is used after a cminit() call to ensure that there was
 *  a mode name configured with the symbolic destination used on  cminit().
 *  If there was no mode name configured with the symbolic destination name,
 *  a partner LU name will have to be set with the cmsmn() call.
 *
 *  Returns:
 *    TRUE  if a mode name was configured
 *    FALSE is there was no mode name configured
 *
 *****************************************************************************/
cpicinit_mode_valid(unsigned char * cm_conv_id)
{
    unsigned char  mode[MAX_MODE_NAME];     /* variable to store the         */
                                            /* extracted mode name           */
    CM_INT32       length = 0;              /* length of mode name           */
    CM_RETURN_CODE cm_rc;                   /* CPI-C return code             */
    int            rc;                      /* procedure return code         */

    cmemn(cm_conv_id,                       /* extract mode name             */
          mode,
          &length,
          &cm_rc );

    if (cm_rc != CM_OK || length == 0) {
        rc = FALSE;
    } else {
        rc = TRUE;
    }
    return rc;

}

