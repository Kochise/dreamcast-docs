
//////////////////////////////
// Version 1.30
// Nov 24th, 2000
// Version 1.20
// Jun 9th, 2000
// Version 1.10
// Jan 23rd, 2000
// Version 1.00
// May 20th, 1999
// Todd C. Wilson, Fresh Ground Software
// (todd@nopcode.com)
// This header file will kick in settings for Visual C++ 5 and 6 that will (usually)
// result in smaller exe's.
// The "trick" is to tell the compiler to not pad out the function calls; this is done
// by not using the /O1 or /O2 option - if you do, you implicitly use /Gy, which pads
// out each and every function call. In one single 500k dll, I managed to cut out 120k
// by this alone!
// The other two "tricks" are telling the Linker to merge all data-type segments together
// in the exe file. The relocation, read-only (constants) data, and code section (.text)
// sections can almost always be merged. Each section merged can save 4k in exe space,
// since each section is padded out to 4k chunks. This is very noticeable with smaller
// exes, since you could have only 700 bytes of data, 300 bytes of code, 94 bytes of
// strings - padded out, this could be 12k of runtime, for 1094 bytes of stuff! For larger
// programs, this is less overall, but can save at least 4k.
// Note that if you're using MFC static or some other 3rd party libs, you may get poor
// results with merging the readonly (.rdata) section - the exe may grow larger.
// To use this feature, define _MERGE_DATA_ in your project or before this header is used.
// With Visual C++ 5, the program uses a file alignment of 512 bytes, which results
// in a small exe. Under VC6, the program instead uses 4k, which is the same as the
// section size. The reason (from what I understand) is that 4k is the chunk size of
// the virtual memory manager, and that WinAlign (an end-user tuning tool for Win98)
// will re-align the programs on this boundary. The problem with this is that all of
// Microsoft's system exes and dlls are *NOT* tuned like this, and using 4k causes serious
// exe bloat. Very noticeable for smaller programs.
// The "trick" for this is to use the undocumented FILEALIGN linker parm to change the
// padding from 4k to 1/2k, which results in a much smaller exe - anywhere from 20%-75%
// depending on the size. Note that this is the same as using /OPT:NOWIN98, which *is*
// a previously documented switch, but was left out of the docs for some reason in VC6 and
// all of the current MSDN's - see KB:Q235956 for more information.
// Microsoft does say that using the 4k alignment will "speed up process loading",
// but I've been unable to notice a difference, even on my P180, with a very large (4meg) exe.
// Please note, however, that this will probably not change the size of the COMPRESSED
// file (either in a .zip file or in an install archive), since this 4k is all zeroes and
// gets compressed away.
// Also, the /ALIGN:4096 switch will "magically" do the same thing, even though this is the
// default setting for this switch. Apparently this sets the same values as the above two
// switches do. We do not use this in this header, since it smacks of a bug and not a feature.
// Thanks to Michael Geary <Mike@Geary.com> for some additional tips!

#ifdef NDEBUG
// /Og (global optimizations), /Os (favor small code), /Oy (no frame pointers)
#pragma optimize("gsy",on)

#pragma comment(linker,"/RELEASE")

// Note that merging the .rdata section will result in LARGER exe's if you using
// MFC (esp. static link). If this is desirable, define _MERGE_RDATA_ in your project.
#ifdef _MERGE_RDATA_
#pragma comment(linker,"/merge:.rdata=.data")
#endif // _MERGE_RDATA_

// Disabled following optimization because it causes problems with NX
// protection on WinXP SP2 (Oz)
//#pragma comment(linker,"/merge:.text=.data")

#pragma comment(linker,"/merge:.reloc=.data")

// Merging sections with different attributes causes a linker warning, so
// turn off the warning. From Michael Geary. Undocumented, as usual!
#pragma comment(linker,"/ignore:4078")

// With Visual C++ 5, you already get the 512-byte alignment, so you will only need
// it for VC6, and maybe later.
#if _MSC_VER >= 1000

// Option #1: use /filealign
// Totally undocumented! And if you set it lower than 512 bytes, the program crashes.
// Either leave at 0x200 or 0x1000
//#pragma comment(linker,"/FILEALIGN:0x200")

// Option #2: use /opt:nowin98
// See KB:Q235956 or the READMEVC.htm in your VC directory for info on this one.
// This is our currently preferred option, since it is fully documented and unlikely
// to break in service packs and updates.
#pragma comment(linker,"/opt:nowin98")

// Option #3: use /align:4096
// A side effect of using the default align value is that it turns on the above switch.
// May break in future versions!
//#pragma comment(linker,"/ALIGN:4096")

#endif // _MSC_VER >= 1000

#endif // NDEBUG
