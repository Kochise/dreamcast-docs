File Signature


The SIGNFILE sample is a console application that signs files. Files
signed with this sample can be later verified with the VERIFILE sample.

Note that the INITUSER sample (or equivalent) must be run prior to running
these samples, in order to create a key container for the default user.

Usage
-----

The SIGNFILE sample is run from the command line as follows:

    signfile <source file> <signature file> <description>

The <source file> argument specifies the filename of the file to be signed,
and the <signature file> argument specifies the filename of the file in which
to place the signature data. The <description> argument specifies a textual
description of the data being signed. This can consist of empty quotes ("")
if no description is required. See CryptSignHash in the online documentation
for more information on signatures and description strings.

The VERIFILE sample is run with the same arguments as SIGNFILE. If the
contents of the source file, signature file, or description string has
changed in any way from when the file was originally signed, the program
will fail.

Exercises for the Reader
------------------------

1. These samples would be more useful if the signature public key was stored
   in the signature file along with the signature data. This public key would
   need to be wrapped in a certificate (also known as a credential) to protect
   it from unauthorized modification. If this were to be done, then the data
   file and its signature could be verified by anyone, even if the original
   key pair used to produce the signature is destroyed.

2. The SIGNFILE sample could be easily modified such that the description data
   is stored in the signature file (in a non-encrypted format) along with the
   signature data. The VERIFILE sample could then read the description from
   the signature file, instead of requiring it as a command line argument.
