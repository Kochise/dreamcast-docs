
Sample: testall
===============

DESCRIPTION:

    This program illustrates the use of the SMS APIs to examine either
    a site container, a jobs container, or a package container. The
    only difference in code between them is the setting of filters.

    For the specified container, this program will set a standard set of
    filters for that container type, and then begin enumeration of that
    container and all the folders within it.

    After the preliminary work of soliciting from the user the datasource
    information and making a connection to that datasource, the program
    then solicits the container type to enumerate and sets appropriate
    filters (see below). A loop is then entered which retrieves and
    stores the handles of all folders in that container. The container
    is then closed. Closing a container as soon as possible has a space
    advantage in that an open parent causes a folder's reference count to
    be incremented. The folder will not be closed until this count reaches
    zero. If the container is left open then no folders at all will be
    removed from memory.

    We then loop through the list of folders and display them one at a time,
    after which the program either terminates or restarts (using the same
    datasource), according to the user's request.

    Displaying folders.
    This is accomplished in the DisplayFolder() function.

API USAGE:
    The following APIs are used in this program:

      SmsAPIVer

      SmsDataSourceConnect
      SmsDataSourceDisconnect

      SmsOpenContainer
      SmsSetFilter
      SmsPopulate
      SmsGetFolderCount
      SmsCloseContainer

      SmsCreateFilter
      SmsGetToken
      SmsGetTokenCount
      SmsAddToken
      SmsCloseFilter

      SmsGetFolderID
      SmsGetFolderType
      SmsGetNextFolder
      SmsGetScalarCount
      SmsGetNextScalar
      SmsCloseFolder


1. Site hierarchy
-----------------
This program will display the site/domain/machine/MIF group
tree for the associated datasource according to certain filter
conditions.
o site filter:         select either root site or specific site.
o architecture filter: select machines of architecture Personal Computer.
o machine filter:      only machines with SystemRole=Server.
o group filter:        select the identification group.
o greoup filter:       select the netcard group.

2. Jobs
-------
The user can select from the following types of jobs: workstation
install, server share, remove package, system. Selections are
ORed together, thus it is possible to select both workstation
install and remove package jobs. It is also possible to select
none of the above in which case the system defaults to selecting
all of them.
This might sound illogical, quite the contrary. A filter is a
restriction, if there are no restrictions then none are disallowed.

3. Packages
-----------
This uses the package filter to allow selection of any or all of the
following types of packages:
o Workstation
o Server
o Inventory


The program will enumerate all folders in the specified container,
for each folder it will display all scalars and then enumerate
all sub-folders.

