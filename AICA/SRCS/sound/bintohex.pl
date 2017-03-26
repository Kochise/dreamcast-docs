#!/usr/local/bin/perl
undef $/;$z=<>;print "static unsigned char the_code[] = {";
for($i=0;$i<length($z);$i++){if(!(7&$i)){print "\n";}
printf " 0x%02x,",ord(substr($z,$i,1));}print "\n};\n";
