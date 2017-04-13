DCOMPERM
========

The DCOMPERM sample provides source code and several wrapper functions to
simplify the process of manipulating the access and launch permissions for
a COM server. Additionally, this sample provides code which demonstrates how
to set and retrieve the RunAs password for a COM server.

Wrapper Functions
-----------------

ChangeDefaultAccessACL ------------------------------------------------------

DWORD
ChangeDefaultAccessACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

Description:

Modify the default access access control list. The system uses the default
access ACL to determine if a principal is allowed to access the COM server
if the COM server does not have its own access ACL in the AppID section of
the registry.

Parameters:

    Principal               Name of user or group (e.g. "redmond\johndoe")

    SetPrincipal            TRUE if you want to add/update the principal's
                            entry in the ACL
                            FALSE if you want to remove the principal from
                            the ACL

    Permit                  TRUE if you want to allow the principal to access
                            the object
                            FALSE if you want to prevent the principal from
                            accessing the object

    (Note that the Permit flag applies only when SetPrincipal is TRUE.)

ChangeAppIDAccessACL --------------------------------------------------------

DWORD
ChangeAppIDAccessACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

Modify an AppID's access access control list. The system uses the AppID
access ACL to determine if a principal is allowed to access the COM server
associated with the AppID.

Parameters:
    AppID                   The Application ID you wish to modify
                            (e.g. "{99999999-9999-9999-9999-00AA00BBF7C7}")

    Principal               Name of user or group (e.g. "redmond\johndoe")

    SetPrincipal            TRUE if you want to add the principal to the ACL
                            FALSE if you want to remove the principal from
                            the ACL

    Permit                  TRUE if you want to allow the principal to access
                            the object
                            FALSE if you want to prevent the principal from
                            accessing the object


    (Note that the Permit flag applies only when SetPrincipal is TRUE.)

ChangeDefaultLaunchACL ------------------------------------------------------

DWORD
ChangeDefaultLaunchACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

Modify the default launch access control list. The system uses the
default launch ACL to determine if a principal is allowed to launch a
COM server if the COM server does not have its own launch ACL in the AppID
section of the registry.

Parameters:

    Principal               Name of user or group (e.g. "redmond\johndoe")

    SetPrincipal            TRUE if you want to add/update the principal's
                            entry in the ACL
                            FALSE if you want to remove the principal from
                            the ACL

    Permit                  TRUE if you want to allow the principal to launch
                            the object
                            FALSE if you want to prevent the principal from
                            launching the object

    (Note that the Permit flag applies only when SetPrincipal is TRUE.)

ChangeAppIDLaunchACL --------------------------------------------------------

DWORD
ChangeAppIDLaunchACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

Modify an AppID's launch access control list. The system uses the AppID
launch ACL to determine if a principal (a user or group of users) is allowed
to launch the COM server associated with the AppID.

Parameters:
    AppID                   The Application ID you set permissions for
                            (e.g. "{99999999-9999-9999-9999-00AA00BBF7C7}")

    Principal               Name of user or group (e.g. "redmond\johndoe")

    SetPrincipal            TRUE if you want to add the principal to the ACL
                            FALSE if you want to remove the principal from
                            the ACL

    Permit                  TRUE if you want to allow the principal to launch
                            the object
                            FALSE if you want to prevent the principal from
                            launching the object


    (Note that the Permit flag applies only when SetPrincipal is TRUE.)

GetRunAsPassword ------------------------------------------------------------

DWORD GetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Password
    );

Description:

Retrieves the RunAs password for an AppID.

Parameters:

    AppID                   The Application ID you wish to configure
                            (e.g. "{99999999-9999-9999-9999-00AA00BBF7C7}")

    Password                Password of the user you have specified in
                            the RunAs named value under the AppID registry
                            key.

SetRunAsPassword ------------------------------------------------------------

DWORD SetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Principal,
    LPTSTR Password
    );

Description:

Sets the RunAs password for an AppID. Note that if you have specified the
RunAs named value to "Interactive User" you do not need to set the RunAs
password.

Parameters:

    AppID                   The Application ID you wish to configure
                            (e.g. "{99999999-9999-9999-9999-00AA00BBF7C7}")

    Principal		    Name of the principal you have specified in the
			    RunAs named value under the AppID registry key

    Password                Password of the principal you have specified in
                            the RunAs named value under the AppID registry
                            key.


