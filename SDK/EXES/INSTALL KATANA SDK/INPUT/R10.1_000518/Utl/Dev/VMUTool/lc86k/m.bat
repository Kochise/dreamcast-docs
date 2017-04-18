@echo off
m86k %1 .\obj\%1,.\list\%1,.\crf\%1,.\err\%1

L86K -p -l obj\gdummy obj\ghead obj\%1,eva\game

e2h86K .\eva\game.eva .\Hex\game.hex
del .\hex\game.hex
ren .\hex\game.h00 game.hex
move .\hex\game.hex ..\vms\project
