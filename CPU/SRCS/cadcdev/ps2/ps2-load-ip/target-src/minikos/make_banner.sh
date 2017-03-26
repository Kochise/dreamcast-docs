#!/bin/sh

# ps2-load-ip
#
# make_banner.sh
# Copyright (c)2000-2002 Dan Potter
# License: BSD
#
# $Id: make_banner.sh,v 1.1 2002/10/30 05:34:13 bardtx Exp $
#

#
# Re-creates the banner.c file for each compilation run
#

FILE=minikos/banner.h

echo -n '"This binary was built ' > $FILE
echo -n `date` >> $FILE
echo '\n"' >> $FILE

echo -n '"  by ' >> $FILE
echo -n `whoami` >> $FILE
echo -n '@' >> $FILE
if [ `uname` = Linux ]; then
	echo -n `hostname -f` >> $FILE
else
	echo -n `hostname` >> $FILE
fi
echo '\n"' >> $FILE

