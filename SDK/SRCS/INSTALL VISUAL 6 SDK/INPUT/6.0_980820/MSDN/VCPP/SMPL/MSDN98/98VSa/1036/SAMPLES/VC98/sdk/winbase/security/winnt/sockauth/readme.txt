SockAuth

This sample is distantly related to the httpauth sample which
demonstrates the use of the SSPI package to implement the client side
of NTLM authentication when interacting with IIS.  However, this sample
shows both the client and server conversations with the security
provider when just a socket connection is used.

The server side, in this sample, authenticates the client and provides
evidence of this by reporting the client's user name back to the client
via the socket connection.

KerbAuth Directory

This directory contains a modified version of security.c file, which 
enables the sample to use Kerberos Security Package to obtain security
services.
Note the two changes:
    *  The package name is "kerberos"
    *  The TOKEN_SOURCE needs to be a valid principal name of the form
        "Domain\User"


NegoAuth Directory

This directory contains a modified version of security.c file, which
enables the sample to use Negotiate Security Package (SPNEGO) to obtain
security services.
Note the two changes:
    *   The package name is "negotiate"
    *   The TOKEN_SOURCE needs to be a valid principal name of the form
        "Domain\User"


Please copy the appropriate security.c to try out the sample using different
security packages.
