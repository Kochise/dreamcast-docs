@echo off
echo -------------------------------------------------------------------------
echo .
echo    This batch file will build the bank of sound effects required for the
echo    MIDI example.
echo .
echo .  The header (midibank.h) is placed into the project directory and the
echo .  bank is placed in the GD Workshop directory (..\gd_root\)
echo -------------------------------------------------------------------------

mkscript playmidi.kat assetPath mid\
mkbank playmidi.oss headerPath ..\ bankPath ..\gd_root\ 
