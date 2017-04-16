////////////////////////////////////////////////////////////////////
//
// BPCPRI.H
//
// common bpc tuner priority definitions
//
// Copyright (c) 1997 Microsoft Corp.  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef BPCPRI_H
#define BPCPRI_H

#include <limits.h>

typedef enum BPC_PRIORITY {
    BPCPRI_MAX_PRI = LONG_MAX,

    // since the current owner wins a tie, if you really need
    // exclusive access use max pri and nobody can preempt you.
    BPCPRI_EXCLUSIVE = BPCPRI_MAX_PRI,

    // get ppv details for making a purchase with user permission to
    // interrupt everything
    BPCPRI_PPV_INT_ALL          = 11000,

    // viewing after the user has confirmed that they wish to interrupt a
    // recording
    BPCPRI_VIEW_INT_RECORD      = 10000,

    // normal recording.  this is higher then viewing so that someone
    // walking up to the tv who is unaware that a recording is in
    // progress will get a notification before they interrupt the recording
    // and so that a scheduled recording will start and run if a user
    // has gone away leaving the tv viewer running
    BPCPRI_RECORD               = 9000,

    // attempt to get ppv details for making a purchase with user
    // permission to interrupt viewing but not recording
    BPCPRI_PPV_DETAILS_INT_VIEW = 8000,

    //normal tv viewing
    BPCPRI_VIEW                 = 7000,

    // attempt to get ppv details for a purchase but don't
    // interrupting viewing or recording
    BPCPRI_PPV_DETAILS          = 6000,

    // download program guide database information
    BPCPRI_EPG_LOADER           = 5000,

    // msbdn data reception (webcast, etc.)
    BPCPRI_DATA_RECV            = 4000,

    // msbdn announcement listener
    BPCPRI_ANNOUNCE             = 3000,

    // leave tv viewing with power off.  apps should go to this priority
    // when they receive notification that their monitor is
    // powered off.  this allows the best instant on response when
    // no background downloads are occurring but allows data downloads and
    // epg downloads to interrupt viewing
    BPCPRI_POWER_OFF            = 2000,

    // idle ocx priority when no input device selected
    BPCPRI_IDLE                 = 1000,

    BPCPRI_NONE                 = 0,
    BPCPRI_MIN                  = BPCPRI_NONE,
} BPC_PRIORITY;

#endif
// end of file - bpcpri.h
