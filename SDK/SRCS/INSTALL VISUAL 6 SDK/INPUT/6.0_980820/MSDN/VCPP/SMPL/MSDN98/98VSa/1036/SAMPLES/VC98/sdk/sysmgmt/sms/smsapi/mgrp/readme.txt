    SMS API Example: creation of machine group (mgrp.exe)
    =====================================================

This sample shows how to create a machine group using the SMS API.

Currently the API only allows top-level machine groups to be created, in
other words you cannot a) modify existing machine groups, and b) you
cannot create nested machine groups.

There has been one addition to the API set in order to enable this; this is
the SmsDupFolder API.

The sample opens a machine container, and a machine group container.
From the machine container we select the machines that we want inserted into
the machine group that we are about to create. In this example we just select
all the Personal Computer architecture machines, a real-world usage would be
more judicious in its selection.

From the machine group container we create a new machine group folder.
We then enter a loop duplicating each machine folder (SmsDupFolder) and
inserting it into the machine group folder (SmsLinkFolder) and committing
the insertion.

When the loop terminates we set the scalars for the new machine group folder.
There are two scalars: Name and Comment. The Comment is optional and can be
any text string. The name however, must be unique. This is solicited from the
user.

The new folder is then linked and committed.

The contents of this machine group folder are then displayed. Note that this
can be very lengthy.

