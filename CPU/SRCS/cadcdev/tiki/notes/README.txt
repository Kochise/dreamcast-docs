
Tiki C++ Game Toolkit


General
-------

Tiki is a toolkit that fills a role similar to SDL in that it provides glue
to avoid having a lot of platform-specific code in your game's main code base.
It does not try to do everything, however, delegating graphics and audio to
things like OpenGL and OpenAL (respectively).

The really sore spots for portability are things like texture loading, endian
issues, user input, etc. Tiki includes a full texture loading system with
support for PNG and JPEG (for both lossy and lossless, as well as alpha
channel support). A file class is included with convenience methods to load
16 and 32 bit values in little or big endian, with automatic conversion to
the host platform's standard. A full event-driven input system is provided
which can receive events like keyboard and mouse input. Basic window handling
support is also included for each supported platform. On the audio end, Tiki
includes utility classes for very simply streaming audio and playing one-shot
sound effects, with a built-in OggVorbis decoding stream available.

Additionally Tiki is fully C++ based. This could be good or bad for you, but
I assume since you're looking at it, it'll be good for you. :) Namespaces
are used extensively, and STL/libstdc++ is used where appropriate.

Support is currently provided out of the box for Mac OS X and Windows. Support
for an SDL-based Linux port and a KOS-based Dreamcast port are also
experimentally underway.

Basically the goal of Tiki is to use the minimum amount of code to get you
going on your C++ game project with the minimum amount of code, and on as
many platforms as possible.

License
-------

Tiki is licensed under the 3-clause BSD license. This means (in non-binding
plain English) that you can pretty much use it for whatever you want as long
as you provide credit.
