# Startup script for KOS kernel

echo Starting Daemons...

# Uncomment the things you want to auto-load below.
cd /rd
# splash.elf
# maple.elf
# fs_vmu.elf
# fs_ramdisk.elf
# startnet.elf
# telnetd.elf &
# httpd.elf &
# debug.elf &
# netiohost.elf &

echo Finished starting daemons
