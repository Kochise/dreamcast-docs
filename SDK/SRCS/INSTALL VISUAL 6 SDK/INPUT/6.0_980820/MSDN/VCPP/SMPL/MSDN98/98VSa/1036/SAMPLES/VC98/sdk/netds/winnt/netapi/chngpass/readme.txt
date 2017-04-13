Networking (LAN Manager) API Sample


This sample changes the password for an arbitrary user on an arbitrary
target machine.

When targetting a domain controller for account update operations,
be sure to target the primary domain controller for the domain.
The account settings are replicated by the primary domain controller
to each backup domain controller as appropriate.  The NetGetDCName()
Lan Manager API call can be used to get the primary domain controller
computer name from a domain name.

Note that admin or account operator privilege is required on the
target machine unless argv[4] is present and represents the correct
current password.

NetUserSetInfo() at info-level 1003 is appropriate for administrative
over-ride of an existing password.

NetUserChangePassword() allows for an arbitrary user to over-ride
an existing password providing that the current password is confirmed.

