Remote


SUMMARY
=======

The REMOTE tool can be used as both a client and a server.

MORE INFORMATION
================

To Start the Client End of REMOTE
---------------------------------

REMOTE /C <ComputerName> <Unique Id> [/L] [/F] [/B]

ComputerName: The name of computer on which the server end of REMOTE was 
              run.
Unique Id:    The unique identifier of the REMOTE server on computer 
              ComputerName.
[/L]          Number of Lines to Get.
[/F]          Foreground color (blue, red, and so forth).
[/B]          Background color (blue, white, and so forth).

Example: REMOTE /C myserverX86 topsecret

This connects to a server session on \\myserverX86 with id topsecret if 
there was a REMOTE /S <"Cmd"> topsecret started on the machine 
\\myserverX86.

To Start the SERVER End of REMOTE
---------------------------------

REMOTE /S <"Cmd"> <Unique Id> [/U [domainname\]username] [/F] [/B]

"Cmd":      A console program that you control from another computer.
Unique Id:  The unique identifier that identifies this session of the REMOTE 
            server.
[/U]        User or Group who can connect to this session. If this is not
            specified, then anyone can connect.
[/F]        Foreground color (blue, red, and so forth).
[/B]        Background color (blue, white, and so forth).

Examples: REMOTE /S "cmd" emerald /U administrators
          REMOTE /S "i386kd -v" topsecret"

If you have started the server end of REMOTE on one computer and you want to 
interact with "i386kd -v" from another computer, start the client end of 
REMOTE on the other computer by typing:

    REMOTE /C <HostName> imbroglio

To connect to the session "Cmd", start:

    REMOTE /C <HostName> emerald

You can only connect to this session if you have administrator access on 
<HostName>.
