// caps.cpp
// 
// Show ACM and codec caps

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>  // Multimedia registration
#include <msacm.h>	// Audio Compression Manager
#include <stdio.h>

void show_error(MMRESULT mmr)
{
	printf("Error: ");
	switch (mmr) {
	case ACMERR_NOTPOSSIBLE:
		printf("The index specified in uMetric cannot be returned for the specified hao");
		break;
	case MMSYSERR_INVALHANDLE:
		printf("The specified handle is invalid");
		break;
	case MMSYSERR_INVALPARAM:
		printf("At least one parameter is invalid");
		break;
	case MMSYSERR_NOTSUPPORTED:
		printf("The index specified in uMetric is not supported");
		break;
	default:
		printf("(unknown. mmr = %8.8xH)", mmr);
		break;
	}
	printf("\n");
}

BOOL CALLBACK FormatEnumProc(HACMDRIVERID hadid, LPACMFORMATDETAILS pafd, DWORD dwInstance, DWORD fdwSupport)
{
	printf("    %4.4lXH, %s\n", pafd->dwFormatTag, pafd->szFormat);


	return TRUE; // continue enumerating
}

BOOL CALLBACK DriverEnumProc(HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport)
{
	printf(" id: %8.8lxH", hadid);
	printf("  supports:\n");
	if (fdwSupport & ACMDRIVERDETAILS_SUPPORTF_ASYNC) printf("   async conversions\n");
	if (fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CODEC) printf("   different format conversions\n");
	if (fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CONVERTER) printf("   same format conversions\n");
	if (fdwSupport & ACMDRIVERDETAILS_SUPPORTF_FILTER) printf("   filtering\n");

	// get some details
	ACMDRIVERDETAILS dd;
	dd.cbStruct = sizeof(dd);
	MMRESULT mmr = acmDriverDetails(hadid, &dd, 0);
	if (mmr) {
		printf("   "); show_error(mmr);
	} else {
		printf("   Short name: %s\n", dd.szShortName);
		printf("   Long name:  %s\n", dd.szLongName);
		printf("   Copyright:  %s\n", dd.szCopyright);
		printf("   Licensing:  %s\n", dd.szLicensing);
		printf("   Features:   %s\n", dd.szFeatures);
		printf("   Supports %u formats\n", dd.cFormatTags);
		printf("   Supports %u filter formats\n", dd.cFilterTags);
	}

	// open the driver
	HACMDRIVER had = NULL;
	mmr = acmDriverOpen(&had, hadid, 0);
	if (mmr) {
		printf("   "); show_error(mmr);
	} else {
		DWORD dwSize = 0;
		mmr = acmMetrics(had, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
		if (dwSize < sizeof(WAVEFORMATEX)) dwSize = sizeof(WAVEFORMATEX); // for MS-PCM
		WAVEFORMATEX* pwf = (WAVEFORMATEX*) malloc(dwSize);
		memset(pwf, 0, dwSize);
		pwf->cbSize = LOWORD(dwSize) - sizeof(WAVEFORMATEX);
		pwf->wFormatTag = WAVE_FORMAT_UNKNOWN;
		ACMFORMATDETAILS fd;
		memset(&fd, 0, sizeof(fd));
		fd.cbStruct = sizeof(fd);
		fd.pwfx = pwf;
		fd.cbwfx = dwSize;
		fd.dwFormatTag = WAVE_FORMAT_UNKNOWN;
		mmr = acmFormatEnum(had, &fd, FormatEnumProc, 0, 0);  
		if (mmr) {
			printf("   ");
			show_error(mmr);
		}
		free(pwf);

		acmDriverClose(had, 0);
	}

	return TRUE; // continue enumeration
}

void main(int argc, char* argv[])
{
	// get the ACM version
	DWORD dwACMVer = acmGetVersion();
	printf("ACM version %u.%.02u build %u",
			HIWORD(dwACMVer) >> 8,
			HIWORD(dwACMVer) & 0x00FF,
			LOWORD(dwACMVer));
	if (LOWORD(dwACMVer) == 0) printf(" (Retail)");
	printf("\n");

	// show some ACM metrics
	printf("ACM metrics:\n");

	DWORD dwCodecs = 0;
	MMRESULT mmr = acmMetrics(NULL, ACM_METRIC_COUNT_CODECS, &dwCodecs);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu codecs installed\n", dwCodecs);
	}

	DWORD dwConverters = 0;
	mmr = acmMetrics(NULL, ACM_METRIC_COUNT_CONVERTERS, &dwConverters);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu converter drivers installed\n", dwConverters);
	}

	DWORD dwDrivers = 0;
	mmr = acmMetrics(NULL, ACM_METRIC_COUNT_DRIVERS, &dwDrivers);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu drivers installed\n", dwDrivers);
	}

	DWORD dwDisabled = 0;
	mmr = acmMetrics(NULL, ACM_METRIC_COUNT_DISABLED, &dwDisabled);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu drivers are disabled\n", dwDisabled);
	}

	DWORD dwFilters = 0;
	mmr = acmMetrics(NULL, ACM_METRIC_COUNT_FILTERS, &dwFilters);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu filters installed\n", dwFilters);
	}

	DWORD dwHardware = 0;
	mmr = acmMetrics(NULL, ACM_METRIC_COUNT_HARDWARE, &dwHardware);
	if (mmr) {
		show_error(mmr);
	} else {
		printf("%lu hardware drivers\n", dwHardware);
	}

	// enumerate the set of enabled drivers
	printf("Enabled drivers:\n");
	mmr = acmDriverEnum(DriverEnumProc, 0, 0); 
	if (mmr) show_error(mmr);



}

