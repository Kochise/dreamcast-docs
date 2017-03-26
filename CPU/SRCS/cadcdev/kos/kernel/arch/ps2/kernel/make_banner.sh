#!/bin/sh

# Re-creates the banner.c file for each compilation run

echo 'char banner[] = ' > banner.c

if [ "${KOS_SUBARCH}" != "" ]; then
	echo -n '"KOS for '${KOS_ARCH}'['${KOS_SUBARCH}'] ##version##: ' >> banner.c
else
	echo -n '"KOS for '${KOS_ARCH}' ##version##: ' >> banner.c
fi
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

