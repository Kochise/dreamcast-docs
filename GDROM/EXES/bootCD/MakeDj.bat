@echo off
:make
PROGS\mkisofs -R -l -V Exemple -o Exemple.iso Exemple
PROGS\bin2boot Exemple.iso /nohack
del Exemple.iso
del *.tmp
cls
exit