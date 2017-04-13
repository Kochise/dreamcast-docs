Networking (LAN Manager) API Sample


This module illustrates how to use a Null session to overcome access
problems during network related query operations.

One example of the scenario this approach addresses is as follows:

User logs onto workstation A as the local administrator.

Administrator tries to query user information using the NetUserGetInfo()
API call on server B.  This call fails with ERROR_ACCESS_DENIED.

The reason this problem occurs is that the administrator password on
workstation A does not match the administrator password on server B.

During the network query operation, the default behavior is to establish
a connection to the remote server using the credentials of the logged-in
user.  In some scenarios, this behavior is not appropriate, and the
solution is to establish a connection using either known credentials,
or the Null credentials.  Null credentials are suitable for most query
operations against a remote machine.  However, if administrator
related actions are necessary, it is necessary to supply credentials
which have administrative privilege on the remote machine.  Valid
credentials consist of a username, password, and optional domain name.

Establishing a connection in this manner requires that no existing
connections exist to the remote machine tied to the current logon
session.

Note: Null sessions are those where the user credentials passed in the
session setup SMB are null.  This sample only implements a function to
establish a Null session, rather than a session with specific credentials.

Processes and Services running in the Local System account security context
have Null credentials by default, so establishing Null sessions in this
scenario is not required.

Applications that run only on Windows NT 4.0 and above can use
WNetAddConnection2() rather than NetUseAdd() to establish a Null session.
