@echo off
:make
PROGS\mkisofs -R -l -V Exemple -o Exemple.iso Exemple
PROGS\bin2boot Exemple.iso /nohack
PROGS\cdi2nero image.cdi Exemple.nrg
del Exemple.iso
del *.cdi
del *.tmp
cls
exit