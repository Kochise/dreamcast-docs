

DESCRIPTION:

    The "newpkg" sample is a command line program that illustrates
    how to use the SMS SDK to view, create and delete packages.


USAGE:

    When the newpkg program is run, it displays help text that
    describes how to use the program.


FILES PROVIDED:

    makefile
    readme.txt
    newpkg.cpp


BUILDING THE SAMPLE:

    To build this sample program just type nmake.


SMS API CALLS USED:

      SmsDataSourceConnect
      SmsDataSourceDisconnect
      SmsOpenContainer
      SmsCloseContainer
      SmsCreateFolder
      SmsPopulate
      SmsGetNextFolder
      SmsDescribeFolder
      SmsGetFolderID
      SmsGetFolderType
      SmsGetFolderCount
      SmsLinkFolder
      SmsUnlinkFolder
      SmsCommitFolder
      SmsRewind
      SmsCloseFolder
      SmsGetScalarCount
      SmsSetScalar
      SmsGetNextScalar
