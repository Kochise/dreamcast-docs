@rem stereo.bat -- Create STEREO Audio64 streams

@echo off

@rem *** scratch variable ***
@set _src_=s44pcm.wav\
@set _dst_=..\gd_root\s_
@set _abstract_=abstract.txt
@set _halfbuffer_=4
@set _adpcm_=adpcm
@set _leadin_=1
@set _leadout_=2
@set _mkstreampath_=%KATANA_ROOT%\utl\snd\pc\

%_mkstreampath_%mkstream %_src_%0drum.wav %_dst_%0drum.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%2sybass.wav %_dst_%2sybass.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%3clguit.wav %_dst_%3clguit.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%4fuzzgui.wav %_dst_%4fuzzgui.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%5wahgui.wav %_dst_%5wahgui.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%6rhodep.wav %_dst_%6rhodep.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%
%_mkstreampath_%mkstream %_src_%7vocal.wav %_dst_%7vocal.str %_adpcm_% abstract %_abstract_% halfPlayBufferSizeInSectors %_halfbuffer_% leadIn %_leadin_% leadOut %_leadout_%

@rem *** cleanup ***
@set _src_=
@set _dst_=
@set _abstract_=
@set _halfbuffer_=
@set _adpcm_=
@set _leadin_=
@set _leadout_=
@set _mkstreampath_=

@echo on
