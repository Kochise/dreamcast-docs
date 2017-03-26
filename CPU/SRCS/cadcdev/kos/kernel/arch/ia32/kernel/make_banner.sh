#!/bin/sh

# Re-creates the banner.c file for each compilation run

echo 'char banner[] = ' > banner.c

echo -n '"KallistiOS/ia32 ##version##: ' >> banner.c
echo -n `date` >> banner.c
echo '\n"' >> banner.c

echo -n '"  ' >> banner.c
echo -n `whoami` >> banner.c
echo -n '@' >> banner.c
if [ `uname` = Linux ]; then
	echo -n `hostname -f` >> banner.c
else
	echo -n `hostname` >> banner.c
fi
echo -n ':' >> banner.c
echo -n $KOS_BASE >> banner.c
echo '\n"' >> banner.c

echo ';' >> banner.c

