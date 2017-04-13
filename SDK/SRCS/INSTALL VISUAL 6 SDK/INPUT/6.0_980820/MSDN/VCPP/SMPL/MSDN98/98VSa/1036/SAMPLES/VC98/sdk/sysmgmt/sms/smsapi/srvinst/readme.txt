DESCRIPTION:

    The srvinst sample program illustrates how to create a server install
    job and monitor its status until the job completes.  This sample also
    illustrates how to create a run command on workstation job.


USAGE:

    When the srvinst program is run, it displays help text that
    describes how to use the program.


FILES PROVIDED:

    readme.txt
    makefile
    smsdefs.h
    srvinst.h
    status.cpp

BUILDING THE SAMPLE:

    To build this sample program type 'nmake'.


SMS API CALLS USED:

    SmsDataSourceConnect
    SmsDataSourceDisconnect
    SmsOpenContainer
    SmsCloseContainer
    SmsCreateFolder
    SmsLinkFolder
    SmsCommitFolder
    SmsCloseFolder
    SmsGetNextFolder
    SmsSetScalar
    SmsGetScalarByName
