// conv.cpp
//
// convert a PCM wave to some other format

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>  // Multimedia registration
#include <msacm.h>	// Audio Compression Manager
#include <stdio.h>
#include <math.h>

// Locate a driver that supports a given format and return its ID
typedef struct {
	HACMDRIVERID hadid;
	WORD wFormatTag;
} FIND_DRIVER_INFO;

// callback function for format enumeration
BOOL CALLBACK find_format_enum(HACMDRIVERID hadid, LPACMFORMATDETAILS pafd, DWORD dwInstance, DWORD fdwSupport)
{
	FIND_DRIVER_INFO* pdi = (FIND_DRIVER_INFO*) dwInstance;
	if (pafd->dwFormatTag == (DWORD)pdi->wFormatTag) {
		// found it
		pdi->hadid = hadid;
		return FALSE; // stop enumerating
	}

	return TRUE; // continue enumerating
}

// callback function for driver enumeration
BOOL CALLBACK find_driver_enum(HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport)
{
	FIND_DRIVER_INFO* pdi = (FIND_DRIVER_INFO*) dwInstance;

	// open the driver
	HACMDRIVER had = NULL;
	MMRESULT mmr = acmDriverOpen(&had, hadid, 0);
	if (mmr) {

		// some error
		return FALSE; // stop enumerating

	}

	// enumerate the formats it supports
	DWORD dwSize = 0;
	mmr = acmMetrics(had, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
	if (dwSize < sizeof(WAVEFORMATEX)) dwSize = sizeof(WAVEFORMATEX); // for MS-PCM
	WAVEFORMATEX* pwf = (WAVEFORMATEX*) malloc(dwSize);
	memset(pwf, 0, dwSize);
	pwf->cbSize = LOWORD(dwSize) - sizeof(WAVEFORMATEX);
	pwf->wFormatTag = pdi->wFormatTag;
	ACMFORMATDETAILS fd;
	memset(&fd, 0, sizeof(fd));
	fd.cbStruct = sizeof(fd);
	fd.pwfx = pwf;
	fd.cbwfx = dwSize;
	fd.dwFormatTag = pdi->wFormatTag;
	mmr = acmFormatEnum(had, &fd, find_format_enum, (DWORD)(VOID*)pdi, 0);  
	free(pwf);
	acmDriverClose(had, 0);
	if (pdi->hadid || mmr) {
		// found it or some error
		return FALSE; // stop enumerating
	}

	return TRUE; // continue enumeration
}

// locate the first driver that supports a given format tag
HACMDRIVERID find_driver(WORD wFormatTag)
{
	FIND_DRIVER_INFO fdi;
	fdi.hadid = NULL;
	fdi.wFormatTag = wFormatTag;
	MMRESULT mmr = acmDriverEnum(find_driver_enum, (DWORD)(VOID*)&fdi, 0); 
	if (mmr) return NULL;
	return fdi.hadid;
}

// get a description of the first format supported for a given tag
WAVEFORMATEX* get_driver_format(HACMDRIVERID hadid, WORD wFormatTag)
{
	// open the driver
	HACMDRIVER had = NULL;
	MMRESULT mmr = acmDriverOpen(&had, hadid, 0);
	if (mmr) {
		return NULL;
	}

	// allocate a structure for the info
	DWORD dwSize = 0;
	mmr = acmMetrics(had, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
	if (dwSize < sizeof(WAVEFORMATEX)) dwSize = sizeof(WAVEFORMATEX); // for MS-PCM
	WAVEFORMATEX* pwf = (WAVEFORMATEX*) malloc(dwSize);
	memset(pwf, 0, dwSize);
	pwf->cbSize = LOWORD(dwSize) - sizeof(WAVEFORMATEX);
	pwf->wFormatTag = wFormatTag;

	ACMFORMATDETAILS fd;
	memset(&fd, 0, sizeof(fd));
	fd.cbStruct = sizeof(fd);
	fd.pwfx = pwf;
	fd.cbwfx = dwSize;
	fd.dwFormatTag = wFormatTag;

	// set up a struct to control the enumeration
	FIND_DRIVER_INFO fdi;
	fdi.hadid = NULL;
	fdi.wFormatTag = wFormatTag;

	mmr = acmFormatEnum(had, &fd, find_format_enum, (DWORD)(VOID*)&fdi, 0);  
	acmDriverClose(had, 0);
	if ((fdi.hadid == NULL) || mmr) {
		free(pwf);
		return NULL;
	}
	
	return pwf;
}

int main(int argc, char* argv[])
{
	// First we create a wave that might have been just recorded.
	// The format is 11.025 kHz, 8 bit mono PCM which is a recording
	// format available on all machines.
	// our sample wave will be 1 second long and will be a sine wave 
	// of 1kHz which is exactly 1,000 cycles

	WAVEFORMATEX wfSrc;
	memset(&wfSrc, 0, sizeof(wfSrc));
	wfSrc.cbSize = 0;
	wfSrc.wFormatTag = WAVE_FORMAT_PCM; // pcm
	wfSrc.nChannels = 1; // mono
	wfSrc.nSamplesPerSec = 11025; // 11.025 kHz
	wfSrc.wBitsPerSample = 8; // 8 bit
	wfSrc.nBlockAlign = wfSrc.nChannels * wfSrc.wBitsPerSample / 8;
	wfSrc.nAvgBytesPerSec = wfSrc.nSamplesPerSec * wfSrc.nBlockAlign;

	DWORD dwSrcSamples = wfSrc.nSamplesPerSec;
	BYTE* pSrcData = new BYTE [dwSrcSamples]; // 1 second duration
	BYTE* pData = pSrcData;
	double f = 1000.0;
	double pi = 4.0 * atan(1.0);
	double w = 2.0 * pi * f;
	for (DWORD dw = 0; dw < dwSrcSamples; dw++) {
		double t = (double) dw / (double) wfSrc.nSamplesPerSec; 
		*pData++ = 128 + (BYTE)(127.0 * sin(w * t));
	}


	// Select a format to convert to
	// WORD wFormatTag = WAVE_FORMAT_ADPCM;
	// WORD wFormatTag = WAVE_FORMAT_IMA_ADPCM;
	// WORD wFormatTag = WAVE_FORMAT_GSM610;
	// WORD wFormatTag = WAVE_FORMAT_ALAW;
	// WORD wFormatTag = WAVE_FORMAT_MULAW;
	// WORD wFormatTag = 0x32; // MSN
	WORD wFormatTag = WAVE_FORMAT_DSPGROUP_TRUESPEECH;

	// Now we locate a CODEC that supports the destination format tag
	HACMDRIVERID hadid = find_driver(wFormatTag);
	if (hadid == NULL) {
		printf("No driver found\n");
		exit(1);
	}
	printf("Driver found (hadid: %4.4lXH)\n", hadid);

	// show some information about the driver
	ACMDRIVERDETAILS dd;
	dd.cbStruct = sizeof(dd);
	MMRESULT mmr = acmDriverDetails(hadid, &dd, 0);
	printf("   Short name: %s\n", dd.szShortName);
	printf("   Long name:  %s\n", dd.szLongName);
	printf("   Copyright:  %s\n", dd.szCopyright);
	printf("   Licensing:  %s\n", dd.szLicensing);
	printf("   Features:   %s\n", dd.szFeatures);

	// get the details of the format
	// Note: this is just the first of one or more possible formats for the given tag
	WAVEFORMATEX* pwfDrv = get_driver_format(hadid, wFormatTag);
	if (pwfDrv == NULL) {
		printf("Error getting format info\n");
		exit(1);
	}
	printf("Driver format: %u bits, %lu samples per second\n", pwfDrv->wBitsPerSample, pwfDrv->nSamplesPerSec);

	// get a PCM format tag the driver supports
	// Note: we just pick the first supported PCM format which might not really
	// be the best choice.
	WAVEFORMATEX* pwfPCM = get_driver_format(hadid, WAVE_FORMAT_PCM);
	if (pwfPCM == NULL) {
		printf("Error getting PCM format info\n");
		exit(1);
	}
	printf("PCM format: %u bits, %lu samples per second\n", pwfPCM->wBitsPerSample, pwfPCM->nSamplesPerSec);

	////////////////////////////////////////////////////////////////////////////////
	// convert the source wave to the PCM format supported by the CODEC
	// we use any driver that can do the PCM to PCM conversion
	HACMSTREAM hstr = NULL;
	mmr = acmStreamOpen(&hstr,
						NULL, // any driver
						&wfSrc, // source format
						pwfPCM, // destination format
						NULL, // no filter
						NULL, // no callback
						0, // instance data (not used)
						ACM_STREAMOPENF_NONREALTIME); // flags
	if (mmr) {
		printf("Failed to open a stream to do PCM to PCM conversion\n");
		exit(1);
	}

	// allocate a buffer for the result of the conversion.
	DWORD dwSrcBytes = dwSrcSamples * wfSrc.wBitsPerSample / 8;
	DWORD dwDst1Samples = dwSrcSamples * pwfPCM->nSamplesPerSec / wfSrc.nSamplesPerSec;
	DWORD dwDst1Bytes = dwDst1Samples * pwfPCM->wBitsPerSample / 8;
	BYTE* pDst1Data = new BYTE [dwDst1Bytes];

#ifdef _DEBUG
	// fill the dest buffer with zeroes just so we can see if anything got 
	// converted in the debugger
	memset(pDst1Data, 0, dwDst1Bytes);
#endif

	// fill in the conversion info
	ACMSTREAMHEADER strhdr;
	memset(&strhdr, 0, sizeof(strhdr));
	strhdr.cbStruct = sizeof(strhdr);
	strhdr.pbSrc = pSrcData; // the source data to convert
	strhdr.cbSrcLength = dwSrcBytes;
	strhdr.pbDst = pDst1Data;
	strhdr.cbDstLength = dwDst1Bytes;

	// prep the header
	mmr = acmStreamPrepareHeader(hstr, &strhdr, 0); 

	// convert the data
	printf("Converting to intermediate PCM format...\n");
	mmr = acmStreamConvert(hstr, &strhdr, 0);
	if (mmr) {
		printf("Failed to do PCM to PCM conversion\n");
		exit(1);
	}
	printf("Converted OK\n");

	// close the stream
	acmStreamClose(hstr, 0);

	///////////////////////////////////////////////////////////////////////////////////
	// convert the intermediate PCM format to the final format

	// open the driver
	HACMDRIVER had = NULL;
	mmr = acmDriverOpen(&had, hadid, 0);
	if (mmr) {
		printf("Failed to open driver\n");
		exit(1);
	}

	// open the conversion stream
	// Note the use of the ACM_STREAMOPENF_NONREALTIME flag. Without this
	// some software compressors will report error 512 - not possible
	mmr = acmStreamOpen(&hstr,
						had, // driver handle
						pwfPCM, // source format
						pwfDrv, // destination format
						NULL, // no filter
						NULL, // no callback
						0, // instance data (not used)
						ACM_STREAMOPENF_NONREALTIME); // flags
	if (mmr) {
		printf("Failed to open a stream to do PCM to driver format conversion\n");
		exit(1);
	}

	// allocate a buffer for the result of the conversion.
	// compute the output buffer size based on the average byte rate
	// and add a bit for randomness
	// the IMA_ADPCM driver fails the conversion without this extra space
	DWORD dwDst2Bytes = pwfDrv->nAvgBytesPerSec * dwDst1Samples / pwfPCM->nSamplesPerSec;
	dwDst2Bytes = dwDst2Bytes * 3 / 2; // add a little room
	BYTE* pDst2Data = new BYTE [dwDst2Bytes];

#ifdef _DEBUG
	// fill the dest buffer with zeroes just so we can see if anything got 
	// converted in the debugger
	memset(pDst2Data, 0, dwDst2Bytes);
#endif

	// fill in the conversion info
	ACMSTREAMHEADER strhdr2;
	memset(&strhdr2, 0, sizeof(strhdr2));
	strhdr2.cbStruct = sizeof(strhdr2);
	strhdr2.pbSrc = pDst1Data; // the source data to convert
	strhdr2.cbSrcLength = dwDst1Bytes;
	strhdr2.pbDst = pDst2Data;
	strhdr2.cbDstLength = dwDst2Bytes;

	// prep the header
	mmr = acmStreamPrepareHeader(hstr, &strhdr2, 0); 

	// convert the data
	printf("Converting to final format...\n");
	mmr = acmStreamConvert(hstr, &strhdr2, 0);
	if (mmr) {
		printf("Failed to do PCM to driver format conversion\n");
		exit(1);
	}
	printf("Converted OK\n");

	// close the stream and driver
	mmr = acmStreamClose(hstr, 0);
	mmr = acmDriverClose(had, 0);

	// show the conversion stats
	printf("Source wave had %lu bytes\n", dwSrcBytes);
	printf("Converted wave has %lu bytes\n", strhdr2.cbDstLengthUsed);
	printf("Compression ratio is %f\n", (double) dwSrcBytes / (double) strhdr2.cbDstLengthUsed); 

	return 0;
}
