<? $subject = "Dreamcast(tm) Scene"; include("koshdr.php") ?>

<? heading("General"); ?>

<p>The "Dreamcast scene" is a term used to generally encompass all aspects
of DC hobbyness and homebrew; basically anything that wasn't done officially
by Sega(tm), and especially (lately), things done after Sega oficially
cancelled the system's production and support.</p>

<p>Generally this includes ports of other OSes (NetBSD, Linux, QNX, etc);
original toolkit development (libdream, ronin, KOS); games development
(e.g. Feet of Fury); emulator development (DSNES, etc); and hardware
hacking (e.g. DC Navi and other HD adapters, USB cable, etc).</p>

<p>It <b>very explicitly</b> does <b>not</b> include things like warez
and copying of commercially released games. Such things are not tolerated
in "the scene" and mentioning it except in an academic sort of way is a
good way to get banned from a forum. Even borderline topics like making
private mods to a commercial game for your own use is pretty well considered
verboten. Basically, if you are making completely new things, or you are
using some legal code (Free, open source, etc) then we're glad to have you.</p>


<? heading("History"); ?>

<p>This topic is really covered a lot better by other sources. But I'll give
a very brief overview of the highlights here, probably out of order:</p>

<p>A group called Hitmen produced the first non-Sega DC demo, called A.G.E.,
using their device called the Dreamcast Debug Handler (or DDH). It was never
released publically so the world will never know much about it beyond a few
screen shots from a magazine.</p>

<p>Marcus Comstedt figured out using the "CDX" demo how to make a bootable
CDR for the DC without any sort of mod chip. He published his results and
produced some example code on how to use the hardware.</p>

<p>Dan Potter and Tursi created libdream, which was basically some of Marcus'
code repackaged in a convenient form along with a libc. It develops wild
hormone imbalance and becomes more than it was ever intended to become,
with all the original pieces being replaced over time. Despite Dan's best
efforts it's still in use today in some projects. ;)</p>

<p>Stars (libdream example) and Ghetto Pong become the first publically
released DC homebrew demo and DC homebrew game (respectively).</p>

<p>Marcus Brown and the Linux-SH team make a real Linux porting effort called
DCLinux. After some time of hacking on it, they made a disc you can burn
that boots up to a shell prompt, runs X11, and so on. Marcus Comstedt also
produces NetBSD/DC.</p>

<p>Marcus Comstedt and the DSNES team produce DreamSNES, a fast and excellent
port of snes9x, using their internal libronin. It's a runaway hit and breaks
open the doors for a whole flood of emulators to follow (once people got 
ahold of the idea...). The Dreamcast now boasts (very likely) the most
emulators on any single platform except PC.</p>

<p>Dan Potter and Jordan DeLong start on the KallistiOS project, which
incorporates the best parts of libdream along with an actual embedded OS
core (threads, file system, etc). It loses, regains, and loses again a
"real OS" capability to load programs dynamically and do IPC. Today it's
simply a very powerful development kit targetted primarily at the DC, with
a reasonable embedded OS thrown in the mix. Most modern DC homebrew is
written to the KOS APIs. KOS is now collectively maintained and developed
by a group of people on SourceForge as a Free Software project.</p>

<p>The enigmatic Bitmaster starts producing hardware hack docs, describing
how to use a flash BIOS, make peripherals for the parallel port, etc. Building
on this, several schematics surface for IDE and ethernet adapters (later
mostly obsoleted by Sega's BBA). Dan Potter produces a knockoff (I wrote
this page, can you tell? :) called DC Navi that incorporates a reset switch,
a flash BIOS, and an IDE adapter.</p>

<p>GOAT Store teams up with the newly formed Cryptic Allusion (Dan Potter and
Roddy Toomim aka DJ Geki) to commercially release Feet of Fury, breaking open
the doors for commercial homebrew development.</p>

<br>

<p>And that's about where it stands... While a relatively small group of 
people know about it and are interested in it, the "DC Scene" has become
moderately famous around the world among Sega, DC, and retro console
enthusiasts (as the beleaguered machine officially joined those ranks a
couple of years back). A lot of people have heard of it (ask a random
person in a game store some time...) but, at risk of sounding pompous, not
many know of KOS' importance in the scene. Hopefully you're here to check
it out because you found out!</p>


<? heading("Community"); ?>

<p>You can find more info about the current community by checking on the
<a href="list.php">lists page</a>.</p>

<? include("kosftr.php") ?>
