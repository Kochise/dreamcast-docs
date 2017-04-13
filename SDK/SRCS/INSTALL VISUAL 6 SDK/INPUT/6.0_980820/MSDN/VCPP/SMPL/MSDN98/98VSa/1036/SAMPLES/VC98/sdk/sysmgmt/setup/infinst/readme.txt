The InfInst sample demonstrates the basic use of the Win32 Setup APIs.

Win32 Setup APIs are a series of functions for installing files, 
modifying the registry, and modifying INI files.  The primary way
to use the Win32 Setup APIs is to combine the INF handling functions
with one or more INF files that describe the actions to perform 
during your install or uninstall.  One benefit of the Win32 Setup APIs
is that it provides dialog boxes that are consistent, familiar to user 
from the NT and Windows 95 setup, and localized if the OS is 
localized.  Moreover, the copy operations can handle things like
version checking and replacing in use files.  See the thorough 
documentation in the Win32 SDK help.  

Below are the primary APIs used in this sample. These are implemented
in the doinst.c file.  The rest of the sample is a basic wizard 
that collects simple information from the user. The wizard is based
on the win32\wizard sample and is not complete in its error handling
and in helping the user determine things like disks space.

The install process overview is:
  TASK                       SETUPAPI
  open a specific inf        SetupOpenInfFile
  call the wizard for input  (CreateWizard implement in the sample)
  set the directory ids      SetupSetDirectoryId
  create a file queue        SetupOpenFileQueue
  create a queue context     SetupInitDefaultQueueCallback
  add files to queue         SetupInstallFilesFromInfSection
  do the copy                SetupCommitFileQueue
  do the registry stuff      SetupInstallFromInfSection
  close the queue            SetupTermDefaultQueueCallback
  close the inf              SetupCloseFileQueue

Many of the Win32 Setup APIs are specific to device driver
installations which are not addressed in this sample. 