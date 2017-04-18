Accessing a Floppy Disk 


SUMMARY
========

The FLOPPY sample is designed to show how to access a physical floppy disk
under Windows NT.

This program has two major features:

  - It can be used to display the geometry of a disk. For example, use the 
    command:

        mfmt -g a:

  - It can be used to produce a disk image, or to write a disk image to a 
    floppy. For example, use the commands:

        mfmt -c a: bootdisk         - produce a disk image of a:
        mfmt -c bootdisk a:         - make a: identical to bootdisk image

MORE INFORMATION
=================

This program is very simple. Minimal error checking is done. It is meant to 
provide an example of how to:

  - Open a physical disk.

  - Read a disk's geometry.

  - Perform a low-level format operation.

  - Read and write physical sectors.
