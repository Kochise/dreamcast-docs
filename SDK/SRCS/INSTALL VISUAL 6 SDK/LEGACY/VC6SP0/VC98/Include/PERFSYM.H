//
// Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
//

//
//  mqctrnm.h
//
//  Offset definition file for extensible counter objects and counters
//
//  These "relative" offsets must start at 0 and be multiples of 2 i.e.
//  even numbers. In the Open Procedure, they will be added to the
//  "First Counter" and "First Help" values for the device they belong to,
//  in order to determine the absolute location of the counter and
//  object names and corresponding Explain text in the registry.
//
//  This file is used by the extensible counter DLL code as well as the
//  counter name and Explain text definition file .INI file that is used
//  by LODCTR to load the names into the registry.
//

#define QMOBJ                   0
#define NUMSESSIONS             2
#define NUMIPSESSIONS           4
#define NUMIPXSESSIONS          6
#define NUMINQMPACKETS          8
#define TOTALINQMPACKETS       10
#define NUMOUTQMPACKETS        12
#define TOTALOUTQMPACKETS      14
#define TOTALPACKETSINQUEUES   16
#define TOTALBYTESINQUEUES     18


#define SESSIONOBJ             20
#define NUMSESSINPACKETS       22
#define NUMSESSOUTPACKETS      24
#define NUMSESSINBYTES         26
#define NUMSESSOUTBYTES        28
#define TOTALSESSINPACKETS     30
#define TOTALSESSINBYTES       32
#define TOTALSESSOUTPACKETS    34
#define TOTALSESSOUTBYTES      36

#define QUEUEOBJ               38
#define TOTALQUEUEINPACKETS    40
#define TOTALQUEUEINBYTES      42
#define TOTALJOURNALINPACKETS  44
#define TOTALJOURNALINBYTES    46

#define DSOBJ                       48
#define NUMOFSYNCREQUESTS           50
#define NUMOFSYNCREPLIES            52
#define NUMOFREPLREQRECV            54
#define NUMOFREPLREQSENT            56
#define NUMOFACCESSTOSRVR           58
#define NUMOFWRITEREQSENT           60
#define NUMOFERRRETURNEDTOAPP       62
