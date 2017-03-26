<? $subject = "FAQ"; include("koshdr.php") ?>

<?
$i = 0;
$j = 0;
function getnum() {
	global $j;
	$j++;
	echo $j;
}

function faq($text) {
	global $i;
?>
<p><b><font size="+1"><? echo $i ?>.<?getnum()?>. <? echo $text ?></font></b></p>
<?
}

function faqsect($text) {
	global $i;
	global $j;
	$i++;
	heading($i . ". " . $text);
	$j = 0;
}

?>


<? faqsect("About this FAQ"); ?>

<p>We're going to stick to the most basic and commonly asked questions here.
For really detailed stuff, you should look at the examples (somewhat out of
date, unfortunately), read the KOS headers, and ask on the mailing list.</p>


<? faqsect("Compiler / Setup"); ?>

<? faq("What KOS version should I use?"); ?>

<p>Despite the "in development" warning signs all over it, I recommend you
go with the KOS subversion releases. You can get these by pulling down your
own copy of the repo (recommended if you're doing anything serious) or by
downloading snapshots. This is covered in the KOS setup guide on this site.</p>

<p>Many people have stuck with 1.2.0. I'm not sure if it's just inertia,
fear of upgrades, or even lack of knowledge for upgrades. But many things
have been fixed in the 1.3.x current branch that people complain about in
1.2.0. Basically unless you have a huge code base you don't want to upgrade
(and it's not even as hard as you might think with that), please use the
latest subversion releases.</p>


<? faq("Why all this cruddy compilation, shell scripts, makefiles, oh my?"
. " Can't you just build it into a nice package so it's easy to set up?"); ?>

<p>Short answer: no. Longer answer: GCC is Unix software. It's more or less
written to assume it will be compiled not only on each major platform, but
on a specific version of a platform. So we *may* be able to produce nice
pre-compiled packages for your platform, but they may also fail mysteriously
due to dependencies. I tried just that a few years back with KOSWIN and decided
to give up on it.</p>

<p>That said, you will probably have the most luck if you are using someone's
precompiled setup by getting the latest Cygwin (for win32), using an
up to date and LSB-compliant Linux system, or with a recent Mac OSX.</p>


<? faq("What version of GCC do I need? Newlib? Binutils? KOS? Yikes!"); ?>

<p>Yes, it's all very confusing at first. Unfortunately there's not really
a very easy way to simplify it all. The simplest answer here is to check the
KOS web pages and ask around about what's working for people. My current
setup (and thus the "canonical" one) is the following: shl-elf GCC 3.4.1
in posix threads mode, shl-elf binutils 2.15, newlib 1.12.0 (patched
for KOS), and KOS from Subversion.</p>

<p>And to gather and build it all, I'd have to recommend Jim Ursetto's
dcsetup script. Several patches are required in the various tools to make
them work right in the latest KOS, and dcsetup does all this for you
automagically. Check the KOS compilation/setup guide for more info about
that.</p>


<? faq("But.. but... I have GCC 10.30.4 that's newer, and I wanna use it!"); ?>

<p>That's great! You're on your own. Please join the mailing list and let us
know how it works out for you, we might upgrade too. :) Until that time, the
only supported config will be the one listed above because most of the KOS
users and developers are using it, and it's been very well tested. Interim
and older versions of GCC are known to have serious compilation bugs on the
SH platform, and newer versions have a bad tendency to develop them.</p>


<? faq("Ok, I've got a compiler set up and I'm trying to build KOS. But it's"
. " giving me some error about not finding /Makefile.prefab and it quits"
. " pretty fast after starting to compile."); ?>

<p>You probably haven't set up your environ.sh properly (or at all). Again
check the KOS setup guide and make sure you have the right variables by typing
"set" by itself and looking for lots of KOS_* variables. KOS_BASE should
point to the base of your KOS tree (containing Makefile.prefab and such).</p>

<p>Newer versions try to detect this and spit a human-readable error.</p>


<? faq("I'm getting errors compiling things in utils. What to do?"); ?>

<p>It happens... that stuff is built for the host PC, not the DC. So sometimes
your platform doesn't have the libraries it needs by default, it needs
different flags, etc. Your best bet is to tinker around there and if you
can't get it working, post on the mailing list. If it's anything besides
genromfs, you can also probably just comment it out of the utils Makefile and
go on with your life, at least to start with.</p>


<? faq("Why don't you make KOS use a normal make / make install system?"
. " What's with all the environment variables and build kludges?"); ?>

<p>Basically the initial goal was to make it as excruciatingly simple to
set up as possible. Believe it or not, everyone hasn't used KOS since the
dawn of the DC scene. ;) So a lot of people would want to just download it
and try it, and not clutter up their compiler install. To that end, KOS also
included its own libc, libm, and other pieces, and thus also needed special
Makefiles to build your programs properly.</p>

<p>Nowadays, it's pretty much crushed all of its competition, so we've
started to look towards making it more of an installable product, and
duplicating less code. That's why it now uses an external Newlib for its libc
and libm, and it conforms to more POSIX functions each release (to ease
porting of unchanged libraries). So in a way, it makes more sense that it
will eventually become something you can install into your compiler tree.</p>

<p>But due to inertia and being simpler to switch among KOS trees, we still
have the environ.sh setup. It's really not too bad once you get used to it,
and worse comes to worse, you can always just make KOS_BASE point to a
place in your compiler tree. The GNU wrappers (kos-cc, kos-c++, etc) take
care of adding all the necessary compilation parameters, so there is also
no real need for a special Makefile anymore.</p>


<? faq("I have things like libpng installed on my machine already. Do I"
. " really need kos-ports still?"); ?>

<p>Yes, you do. There are two separate worlds involved in DC homebrew: your
host PC and the target DC. These two words will appear over and over if you
start looking into the tool chain, so learn them well! :) When you say you
have libpng installed on your machine, that is a host library. It is very
likely incompatible with the DC's processor and KOS' API. The reverse is true
of target libraries in kos-ports.</p>

<p>Sometimes you can get away with mixing headers between the two worlds,
but that's not very recommended. It's asking for trouble.</p>


<? faqsect("Getting Started With Code"); ?>

<? faq("The examples seem to be out of date or don't compile right. Where"
. " can I find some more up to date examples?"); ?>

<p>Unfortunately, right now you can't. The KOS 1.3.x API represents a
fairly stable version, but it's been in flux for a long time; so chances are,
sample code you come across on the net is out of date for the latest
version.</p>


<? faq("So how the @#%*@ do I figure out what I'm doing??"); ?>

<p>Whoa, calm down. Trust me, I know how you feel. :) The good news is, not
all the news is gloomy. The "hello" example is still pretty valid, to get
a basic project set up. If you want to do 3D, "parallax" and "tsunami" are
both pretty modern. The "lua" examples should still work, for basic scripting
support. And "ghettoplay-vorbis" under "sound" shows (if in a somewhat
drunken-code fashion) how to get OGG playback working. There's not a very
good example of the modern controller input API (maple) but the parallax and
tsunami example trees have a bit, and you could grab a copy of the Feet of
Fury public source release for that.</p>

<p>Hopefully the awful example situation will be rectified sooner or later!</p>


<? faqsect("Using KOS"); ?>

<? faq("What all is supported on the Dreamcast? What about peripheral X?"); ?>

<p>The answer is very likely "yes" these days. The main things not supported
in the main tree are the purupuru (jump) pack and the light gun. These are
generally figured out though and eventually support will probably get merged
into the main tree. You can find patches to add the support by looking around
a bit.</p>

<p>Specifically, several previously stubborn pieces of networking hardware
are now pretty much fully supported. The Broadband Adapter, LAN Adapter, and
modem (up to 33.6Kbps) work quite well. Using the lwIP port, you'll actually
have more hardware support out of the box for LAN networking than pretty much
any Sega official product. PPP support for the modem is still a work in
progress, though it's been getting close.</p>

<p>Some homebrew peripherals are also supported, like the DC Navi rewritable
flash BIOS and IDE adapter. These are enabled by setting subarch to "navi".</p>

<p>The more exotic peripherals are generally not supported. This includes
things like the DC camera, zip drive (did it even exist outside a lab?),
and maracas (though these are somewhat supported as regular controllers).</p>


<? faqsect("Debugging"); ?>

<? faq("Is there a debugger?"); ?>

<p>Not really. You can build GDB and use the gdb stub over a serial connection
to get rudimentary debugging, but it's not what you're going to be used to
unless you're an olde Unix hacker(tm). :)</p>


<? faq("My program crashed! Help! What can I do?"); ?>

<p>Well, first of all make sure you're getting the stdout output from KOS
when you run your program. You'll know if you've got this.</p>

<p>Now then, there are four basic kinds of crashes: unexpected
exit (including kernel panic), assertion failure, infinite loop, and
exception.</p>

<p>For unexpected exit, just look at the stdout output. You can usually
figure out what's going on there. If it doesn't give you enough info then
try searching for the likely-looking error string in the KOS source tree.
Sometimes the extra context helps.</p>

<p>For assertion failures, usually the message is pretty explanatory. You
can compile with frame pointers enabled (check environ.sh files in the KOS_BASE
dir) and get an actual stack trace for context. See "exception" below for
more info on what to do with this.</p>

<p>For infinite loops, your main quest is to get your program to break so
you can figure out where it's crashing. This is pretty easily accomplished
by installing a controller callback. This is called any time the user presses
a certain combination of buttons (assuming IRQs are enabled, which is usually).
See the Parallax font example for an example of this. Once you have a crash,
see "exceptions" below.</p>

<p>For exceptions, look for the PC and PR values. These are the code pointer
to the instruction that caused the crash (or sometimes, the instruction after
it), and the return address (i.e. one step up the stack). Use the
sh-elf-addr2line utility to get a source location:</p>

<p><pre>sh-elf-addr2line -e my.elf 8c010152</pre></p>

<p>If it comes back with "???" then you've likely corrupted your stack
pointer somewhere, or you jumped to an uninitialized function pointer, etc.</p>

<p>You can also check the assembly output:</p>

<p><pre>sh-elf-objdump -d -S my.elf | less</pre></p>

<p>Then type /^8c010152 (or whatever the address was) and hit enter. This
should jump down to the place in the code where it died. Sometimes looking
at the other registers in the exception output can help diagnose this.</p>

<p>If you really can't make any sense of how it got where it got or how the
compiler generated some code, you *may* have a compiler bug. Go ahead and post
to the KOS list about it.</p>

<p>You may also have a malloc issue. See below.</p>


<? faq("Are there tools to help find memory leaks, buffer overruns, etc?"); ?>

<p>Yes! You'll need to have built your own KOS to use it though.</p>

<p>You have two options: turning on debugging in the standard malloc, and
replacing malloc with a debug version.</p>

<p>The former is definitely the recommended choice for most usage, and it's
not a bad idea to leave it on while developing. Edit kernel/libc/koslib/malloc.c,
and look at the #define's at the top. 'DEBUG' turns on internal checks in
the malloc functions (mostly assert statements). These are basic and not
too helpful unless you have a catastrophic failure. KM_DBG enables KOS
memory debugging. This turns on "canary" zones before and after each block
and tracks all allocated blocks in a linked list to find leaks. Combined
with the INIT_MALLOCSTATS flag, you can see exactly where a piece of
memory was allocated, which thread allocated it, the size, and so on. Using
the sh-elf-addr2line util mentioned above, it's easy to hunt down where the
leak happened. KM_DBG_VERBOSE is like a sledge hammer to KM_DBG's claw
hammer. You have to enable both to make it work, and it prints to the
console every single time a malloc related function is called. This
obviously completely kills the speed of your program but it might help
you find a stubborn problem.</p>

<p>The latter option, debug malloc, is the Hole Hawg to KM_DBG_VERBOSE's
sledge hammer. The main thing it's good for is finding pieces of code that
double-free blocks and code that writes to dangling pointers. It does this
by never actually freeing any memory, but putting it on a "freed" list.
Needless to say this is pretty worthless in a program of any size, but if
you can track down the offending code to a small area it can be invaluable.
It's enabled by commenting out malloc.o from kernel/libc/koslib/Makefile, and
changing kernel/mm/Makefile to the second option.</p>

<p>On second thought, it looks like that 'mm' tree isn't even built in the
latest KOS. So you're on your own if you want to try it. ;) If you get it
working I'd love to get a patch.</p>



<? faqsect("KOS Hacking"); ?>

<? faq("I want to really learn this thing. Where can I find more info? The"
. " docs seem out of date."); ?>

<p>Yes, indeed, they are. It's another of those embarrassing things that needs
to be corrected sooner or later. But the best way is to just dig into the
code in KOS, especially the headers, and see what's there! It's actually
very well commented on the whole. Also look in kos-ports to see how various
things use KOS.</p>


<? faq("What's the lay of the land on this thing?"); ?>

<p>KOS' source tree is organized into two top-level sections: kos and
kos-ports.</p>

<p>The 'kos' tree contains KOS itself. This includes build utils and such.
Everything in the 'kernel' tree will be built into libkos.a, which is linked
into your program. Architecture/platform (arch) generic headers are located
in 'include'.</p>

<p>Under 'kernel', things are split into arch-specific, and arch-generic
parts. The arch-specific parts are in 'arch/&lt;arch&rt;', where the
&lt;arch&rt; you're probably interested in is "dreamcast". Arch-generic
pieces are just in the 'kernel' dir, organized by subsystem.</p>

<p>Inside the arch/&lt;arch&rt; dir (aka "the arch dir"), the organization
is somewhat loose. But every arch will contain an 'include' dir, inside of
which is an 'arch' dir (the contents of which are fairly uniform across
different platforms) and a platform dir (the contents of which are very
specific to the given platform). Also the arch dir contains a "kernel" dir
that has arch-specific pieces that support the arch-generic part of the
kernel.</p>

<p>The kos-ports tree simple contains directories with things to build. Any
subdir of this dir which contains a "kos" dir is considered a port to be
built. That top-level port dir (e.g. libjpeg) should include a Makefile
built from the ports Makefile.prefab, and the "kos" dir should contain a
*.cnf file for each arch that's supported. So e.g. a library could have a
dreamcast.cnf which gives DC-specific built instructions. The rest of the
structure of each port is specific to the port in question.</p>


<? faq("I did something cool. How can I submit a patch?"); ?>

<p>Yay! Doing my work for me, I like that. I like it so much that I'll
often go to ridiculous lengths to clean up a bad patch for inclusion,
depending on what it is. But it helps a lot if you follow these simple
guidelines:</p>

<p>Please make the patch against the newest version possible. This could
be a weekly snapshot or a copy of the subversion repo (the latter is
obviously preferable, but I can live with the former).</p>

<p>Don't modify the file unnecessarily and try to conform to the style
of the file(s) you're changing. I like to think of this as the "Minimum
Necessary Change" principle (see: Asimov's End of Eternity :). If some
change is not absolutely necessary, weed it out before submitting; if
you don't, I'll have to! If you submit a patch that has what I consider
to be gross C formatting, I'll likely run it through 'indent' and you may
not like the result.</p>

<p>When building a patch, use the "-ruN" diff arguments. If you're diffing
against a subversion copy, use "svn diff".</p>

<p>Submit patches to the patch tracker on SourceForge. This will add a
permanent record of the patch that everyone can investigate to find the
status of it, and it also sends a notification email to the KOS list so that
a maintainer can look at it.</p>


<? faqsect("Licensing"); ?>

<? faq("What's the deal with the KOS licensing? Can I use it in my"
. " commercial game? Don't I need to pay for that?"); ?>

<p>It's simple; yes; and no, respectively. All of KOS itself (the pieces
you link into your target DC app, and most of the host PC utils) are under
the KOS license. This is basically a 3-clause BSD license with different
author credits. The only responsibility you have is to credit the KOS
authors somewhere in your program (either in the program itself or in
your documentation). That's it, really! Even local modifications you make
don't need to be submitted to us, though of course we'll appreciate it.</p>

<p>Though if you make interesting enough changes, it may be
reverse engineered out or otherwise duplicated anyway ;)</p>

<p>Everything else is under its own license (namely, kos-ports). You should
check the license of each of those items before using them. For example things
that used to be part of KOS or its examples (like libkosh and libconio) are
all KOS licensed. But some pieces (like the MP3 playback) are *GPL* licensed.
Others, like plib, are LGPL with various exceptions.</p>

<p>Bottom line, it's pretty lenient and easy, but do a little due diligence
first!</p>




<? include("kosftr.php") ?>
