This sample illustrates a pass-thru "stub" gina which can be used
in some cases to simplify gina development.

A common use for a gina is to implement code which requires the
credentials of the user logging onto the workstation.  The credentials
may be required for syncronization with foreign account databases
or custom authentication activities.

In this example case, it is possible to implement a simple gina
stub layer which simply passes control for the required functions
to the previously installed gina, and captures the interesting
parameters from that gina.  In this scenario, the existing functionality
in the existent gina is retained.  In addition, the development time
is reduced drastically, as existing functionality does not need to
be duplicated.

When dealing with credentials, take steps to maintain the security
of the credentials.  For instance, if transporting credentials over
a network, be sure to encrypt the credentials.

