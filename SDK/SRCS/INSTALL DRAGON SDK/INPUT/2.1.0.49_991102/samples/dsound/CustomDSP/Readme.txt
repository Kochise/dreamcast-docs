DirectSound sample program -- CustomDSP
-----------------------------------------

* Purpose:
This sample demonstrates how to load custom DSP programs into the Dreamcast
and play wav files using those custom programs.

The wav file is played twice without the DSP effect, and then twice with the
DSP effect, and then exits.

This sample allows the user to specify a particular audio source to play
(WAV file), as well as the file that contains the DSP effect (FPB file).
Both of these files may be specified with a full pathname (i.e., 
"\windows\longtest.wav"), or it may be specified with just the filename 
(i.e., "jump.wav"), in which case the sample will look for the file in 
<WCEDreamcastSDK>\release\(retail,debug)\Samples. The file "jump.wav"
is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s CustomDSP <WAV filename> <DSP filename>

Example: s CustomDSP Jump.wav Q_tunnel.fpb
Example: s CustomDSP \PC\Samples\Jump.wav \PC\Samples\Q_tunnel.fpb

Sample DSP programs are contained in
<WCEDreamcastSDK>\release\(retail/debug)\Samples

* This sample exits automatically.

* Here are filenames and brief descriptions of the included sample DSP 
programs:

qdlflng2.fpb    Dark, Large, Flange
qflngdly.fpb    Flange, Delay
q_bathrm.fpb    Bathroom Reverb
q_bcave.fpb     Bright Reverb
q_bmhl.fpb      Bright Medium Hall Reverb
q_bmrm.fpb      Bright Medium Room Reverb
q_bshl.fpb      Bright Small Hall Reverb
q_bshort.fpb    Bright Short Reverb
q_bsrm.fpb      Bright Small Room Reverb
q_bstdio.fpb    Bright Studio Reverb
q_bxlhl.fpb     Bright Extra Large Hall Reverb
q_cbgb.fpb      Bright Chamber Reverb
q_chorus.fpb    Chorus
q_church.fpb    Church Reverb
q_classl.fpb    Large Classroom Reverb
q_classm.fpb    Medium Classroom Reverb
q_classs.fpb    Small Classroom Reverb
q_dblchr.fpb    Delay, Chorus
q_dblphs.fpb    Delay, Phaser
q_dbooth.fpb    Dark Booth Reverb
q_dlflng.fpb    Delay, Flange
q_dmlrm.fpb     Dark Medium Large Room Reverb
q_dmrm.fpb      Dark Medium Room Reverb
q_dshl.fpb      Dark Small Hall Reverb
q_dxlhl.fpb     Dark Extra Large Hall Reverb
q_ekochr.fpb    Delay Echo, Chorus
q_kichen.fpb    Kitchen Reverb
q_lecho1.fpb    Large Echo
q_lecho2.fpb    Large Echo
q_mdlys1.fpb    Medium Delays
q_normhl.fpb    Normal Hall Reverb
q_phaser.fpb    Phaser
q_sdlys1.fpb    2 Path Delay
q_smphnc.fpb    Symphonic Surround
q_sslap1.fpb    Short Slap Delay
q_sslap2.fpb    Short Slap Delay
q_theatr.fpb    Theatre Room Reverb
q_tunnel.fpb    Tunnel Reverb
q_wbedrm.fpb    Warm Bedroom Reverb
q_wchmbr.fpb    Warm Chamber Reverb
q_wlhl.fpb      Warm Large Hall Reverb
q_wmhl.fpb      Warm Medium Hall Reverb
q_wmrm.fpb      Warm Medium Room Reverb
q_wsrm.fpb      Warm Small Room Reverb
q_wstore.fpb    Warm Store Room Reverb
