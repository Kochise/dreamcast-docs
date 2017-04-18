#include "precomp.hpp"


typedef struct {
	WCHAR *roma;
	WCHAR *kana;
} ROMATABLE;

static ROMATABLE g_RomaTable[] = {
#if 0
	{L"1",	L"‚P"},
	{L"2",	L"‚Q"},
	{L"3",	L"‚R"},
	{L"4",	L"‚S"},
	{L"5",	L"‚T"},
	{L"6",	L"‚U"},
	{L"7",	L"‚V"},
	{L"8",	L"‚W"},
	{L"9",	L"‚X"},
	{L"0",	L"‚O"},
	{L";",	L"G"},
	{L"=",	L""},
	{L",",	L"A"},
	{L"-",	L"["},
	{L".",	L"B"},
	{L"/",	L"E"},
	{L"`",	L"e"},
	{L"[",	L"u"},
	{L"\\",	L""},
	{L"]",	L"v"},
	{L"\'",	L"f"},
#endif
    {L"a",  (WCHAR*) "\x42\x30\0"},
    {L"i",  (WCHAR*) "\x44\x30\0"},
    {L"u",  (WCHAR*) "\x46\x30\0"},
    {L"e",  (WCHAR*) "\x48\x30\0"},
    {L"o",  (WCHAR*) "\x4a\x30\0"},
    {L"la",  (WCHAR*) "\x41\x30\0"},
    {L"li",  (WCHAR*) "\x43\x30\0"},
    {L"lu",  (WCHAR*) "\x45\x30\0"},
    {L"le",  (WCHAR*) "\x47\x30\0"},
    {L"lo",  (WCHAR*) "\x49\x30\0"},
    {L"xa",  (WCHAR*) "\x41\x30\0"},
    {L"xi",  (WCHAR*) "\x43\x30\0"},
    {L"xu",  (WCHAR*) "\x45\x30\0"},
    {L"xe",  (WCHAR*) "\x47\x30\0"},
    {L"xo",  (WCHAR*) "\x49\x30\0"},
    {L"ka",  (WCHAR*) "\x4b\x30\0"},
    {L"ki",  (WCHAR*) "\x4d\x30\0"},
    {L"ku",  (WCHAR*) "\x4f\x30\0"},
    {L"ke",  (WCHAR*) "\x51\x30\0"},
    {L"ko",  (WCHAR*) "\x53\x30\0"},
    {L"ca",  (WCHAR*) "\x4b\x30\0"},
    {L"ci",  (WCHAR*) "\x57\x30\0"},
    {L"cu",  (WCHAR*) "\x4f\x30\0"},
    {L"ce",  (WCHAR*) "\x5b\x30\0"},
    {L"co",  (WCHAR*) "\x53\x30\0"},
    {L"kya",  (WCHAR*) "\x4d\x30\x83\x30\0"},
    {L"kyi",  (WCHAR*) "\x4d\x30\x43\x30\0"},
    {L"kyu",  (WCHAR*) "\x4d\x30\x85\x30\0"},
    {L"kye",  (WCHAR*) "\x4d\x30\x47\x30\0"},
    {L"kyo",  (WCHAR*) "\x4d\x30\x87\x30\0"},
    {L"qa",  (WCHAR*) "\x4f\x30\x41\x30\0"},
    {L"qi",  (WCHAR*) "\x4f\x30\x43\x30\0"},
    {L"qu",  (WCHAR*) "\x4f\x30\0"},
    {L"qe",  (WCHAR*) "\x4f\x30\x47\x30\0"},
    {L"qo",  (WCHAR*) "\x4f\x30\x49\x30\0"},
    {L"qya",  (WCHAR*) "\x4f\x30\x83\x30\0"},
    {L"qyi",  (WCHAR*) "\x4f\x30\x43\x30\0"},
    {L"qyu",  (WCHAR*) "\x4f\x30\x85\x30\0"},
    {L"qye",  (WCHAR*) "\x4f\x30\x47\x30\0"},
    {L"qyo",  (WCHAR*) "\x4f\x30\x87\x30\0"},
    {L"qwa",  (WCHAR*) "\x4f\x30\x41\x30\0"},
    {L"qwi",  (WCHAR*) "\x4f\x30\x43\x30\0"},
    {L"qwu",  (WCHAR*) "\x4f\x30\x45\x30\0"},
    {L"qwe",  (WCHAR*) "\x4f\x30\x47\x30\0"},
    {L"qwo",  (WCHAR*) "\x4f\x30\x49\x30\0"},
    {L"sa",  (WCHAR*) "\x55\x30\0"},
    {L"si",  (WCHAR*) "\x57\x30\0"},
    {L"su",  (WCHAR*) "\x59\x30\0"},
    {L"se",  (WCHAR*) "\x5b\x30\0"},
    {L"so",  (WCHAR*) "\x5d\x30\0"},
    {L"sha",  (WCHAR*) "\x57\x30\x83\x30\0"},
    {L"shi",  (WCHAR*) "\x57\x30\0"},
    {L"shu",  (WCHAR*) "\x57\x30\x85\x30\0"},
    {L"she",  (WCHAR*) "\x57\x30\x47\x30\0"},
    {L"sho",  (WCHAR*) "\x57\x30\x87\x30\0"},
    {L"sya",  (WCHAR*) "\x57\x30\x83\x30\0"},
    {L"syi",  (WCHAR*) "\x57\x30\x43\x30\0"},
    {L"syu",  (WCHAR*) "\x57\x30\x85\x30\0"},
    {L"sye",  (WCHAR*) "\x57\x30\x47\x30\0"},
    {L"syo",  (WCHAR*) "\x57\x30\x87\x30\0"},
    {L"swa",  (WCHAR*) "\x59\x30\x41\x30\0"},
    {L"swi",  (WCHAR*) "\x59\x30\x43\x30\0"},
    {L"swu",  (WCHAR*) "\x59\x30\x45\x30\0"},
    {L"swe",  (WCHAR*) "\x59\x30\x47\x30\0"},
    {L"swo",  (WCHAR*) "\x59\x30\x49\x30\0"},
    {L"ta",  (WCHAR*) "\x5f\x30\0"},
    {L"ti",  (WCHAR*) "\x61\x30\0"},
    {L"tu",  (WCHAR*) "\x64\x30\0"},
    {L"te",  (WCHAR*) "\x66\x30\0"},
    {L"to",  (WCHAR*) "\x68\x30\0"},
    {L"ltu",  (WCHAR*) "\x63\x30\0"},
    {L"xtu",  (WCHAR*) "\x63\x30\0"},
    {L"cha",  (WCHAR*) "\x61\x30\x83\x30\0"},
    {L"chi",  (WCHAR*) "\x61\x30\0"},
    {L"chu",  (WCHAR*) "\x61\x30\x85\x30\0"},
    {L"che",  (WCHAR*) "\x61\x30\x47\x30\0"},
    {L"cho",  (WCHAR*) "\x61\x30\x87\x30\0"},
    {L"tya",  (WCHAR*) "\x61\x30\x83\x30\0"},
    {L"tyi",  (WCHAR*) "\x61\x30\x43\x30\0"},
    {L"tyu",  (WCHAR*) "\x61\x30\x85\x30\0"},
    {L"tye",  (WCHAR*) "\x61\x30\x47\x30\0"},
    {L"tyo",  (WCHAR*) "\x61\x30\x87\x30\0"},
    {L"cya",  (WCHAR*) "\x61\x30\x83\x30\0"},
    {L"cyi",  (WCHAR*) "\x61\x30\x43\x30\0"},
    {L"cyu",  (WCHAR*) "\x61\x30\x85\x30\0"},
    {L"cye",  (WCHAR*) "\x61\x30\x47\x30\0"},
    {L"cyo",  (WCHAR*) "\x61\x30\x87\x30\0"},
    {L"tsa",  (WCHAR*) "\x64\x30\x41\x30\0"},
    {L"tsi",  (WCHAR*) "\x64\x30\x43\x30\0"},
    {L"tsu",  (WCHAR*) "\x64\x30\0"},
    {L"tse",  (WCHAR*) "\x64\x30\x47\x30\0"},
    {L"tso",  (WCHAR*) "\x64\x30\x49\x30\0"},
    {L"ltsu",  (WCHAR*) "\x63\x30\0"},
    {L"tha",  (WCHAR*) "\x66\x30\x83\x30\0"},
    {L"thi",  (WCHAR*) "\x66\x30\x43\x30\0"},
    {L"thu",  (WCHAR*) "\x66\x30\x85\x30\0"},
    {L"the",  (WCHAR*) "\x66\x30\x47\x30\0"},
    {L"tho",  (WCHAR*) "\x66\x30\x87\x30\0"},
    {L"twa",  (WCHAR*) "\x68\x30\x41\x30\0"},
    {L"twi",  (WCHAR*) "\x68\x30\x43\x30\0"},
    {L"twu",  (WCHAR*) "\x68\x30\x45\x30\0"},
    {L"twe",  (WCHAR*) "\x68\x30\x47\x30\0"},
    {L"two",  (WCHAR*) "\x68\x30\x49\x30\0"},
    {L"na",  (WCHAR*) "\x6a\x30\0"},
    {L"ni",  (WCHAR*) "\x6b\x30\0"},
    {L"nu",  (WCHAR*) "\x6c\x30\0"},
    {L"ne",  (WCHAR*) "\x6d\x30\0"},
    {L"no",  (WCHAR*) "\x6e\x30\0"},
    {L"nya",  (WCHAR*) "\x6b\x30\x83\x30\0"},
    {L"nyi",  (WCHAR*) "\x6b\x30\x43\x30\0"},
    {L"nyu",  (WCHAR*) "\x6b\x30\x85\x30\0"},
    {L"nye",  (WCHAR*) "\x6b\x30\x47\x30\0"},
    {L"nyo",  (WCHAR*) "\x6b\x30\x87\x30\0"},
    {L"ha",  (WCHAR*) "\x6f\x30\0"},
    {L"hi",  (WCHAR*) "\x72\x30\0"},
    {L"hu",  (WCHAR*) "\x75\x30\0"},
    {L"he",  (WCHAR*) "\x78\x30\0"},
    {L"ho",  (WCHAR*) "\x7b\x30\0"},
    {L"hya",  (WCHAR*) "\x72\x30\x83\x30\0"},
    {L"hyi",  (WCHAR*) "\x72\x30\x43\x30\0"},
    {L"hyu",  (WCHAR*) "\x72\x30\x85\x30\0"},
    {L"hye",  (WCHAR*) "\x72\x30\x47\x30\0"},
    {L"hyo",  (WCHAR*) "\x72\x30\x87\x30\0"},
    {L"fa",  (WCHAR*) "\x75\x30\x41\x30\0"},
    {L"fi",  (WCHAR*) "\x75\x30\x43\x30\0"},
    {L"fu",  (WCHAR*) "\x75\x30\0"},
    {L"fe",  (WCHAR*) "\x75\x30\x47\x30\0"},
    {L"fo",  (WCHAR*) "\x75\x30\x49\x30\0"},
    {L"fya",  (WCHAR*) "\x75\x30\x83\x30\0"},
    {L"fyi",  (WCHAR*) "\x75\x30\x43\x30\0"},
    {L"fyu",  (WCHAR*) "\x75\x30\x85\x30\0"},
    {L"fye",  (WCHAR*) "\x75\x30\x47\x30\0"},
    {L"fyo",  (WCHAR*) "\x75\x30\x87\x30\0"},
    {L"fwa",  (WCHAR*) "\x75\x30\x41\x30\0"},
    {L"fwi",  (WCHAR*) "\x75\x30\x43\x30\0"},
    {L"fwu",  (WCHAR*) "\x75\x30\x45\x30\0"},
    {L"fwe",  (WCHAR*) "\x75\x30\x47\x30\0"},
    {L"fwo",  (WCHAR*) "\x75\x30\x49\x30\0"},
    {L"ma",  (WCHAR*) "\x7e\x30\0"},
    {L"mi",  (WCHAR*) "\x7f\x30\0"},
    {L"mu",  (WCHAR*) "\x80\x30\0"},
    {L"me",  (WCHAR*) "\x81\x30\0"},
    {L"mo",  (WCHAR*) "\x82\x30\0"},
    {L"mya",  (WCHAR*) "\x7f\x30\x83\x30\0"},
    {L"myi",  (WCHAR*) "\x7f\x30\x43\x30\0"},
    {L"myu",  (WCHAR*) "\x7f\x30\x85\x30\0"},
    {L"mye",  (WCHAR*) "\x7f\x30\x47\x30\0"},
    {L"myo",  (WCHAR*) "\x7f\x30\x87\x30\0"},
    {L"ya",  (WCHAR*) "\x84\x30\0"},
    {L"yi",  (WCHAR*) "\x44\x30\0"},
    {L"yu",  (WCHAR*) "\x86\x30\0"},
    {L"ye",  (WCHAR*) "\x44\x30\x47\x30\0"},
    {L"yo",  (WCHAR*) "\x88\x30\0"},
    {L"lya",  (WCHAR*) "\x83\x30\0"},
    {L"lyi",  (WCHAR*) "\x43\x30\0"},
    {L"lyu",  (WCHAR*) "\x85\x30\0"},
    {L"lye",  (WCHAR*) "\x47\x30\0"},
    {L"lyo",  (WCHAR*) "\x87\x30\0"},
    {L"xya",  (WCHAR*) "\x83\x30\0"},
    {L"xyi",  (WCHAR*) "\x43\x30\0"},
    {L"xyu",  (WCHAR*) "\x85\x30\0"},
    {L"xye",  (WCHAR*) "\x47\x30\0"},
    {L"xyo",  (WCHAR*) "\x87\x30\0"},
    {L"ra",  (WCHAR*) "\x89\x30\0"},
    {L"ri",  (WCHAR*) "\x8a\x30\0"},
    {L"ru",  (WCHAR*) "\x8b\x30\0"},
    {L"re",  (WCHAR*) "\x8c\x30\0"},
    {L"ro",  (WCHAR*) "\x8d\x30\0"},
    {L"rya",  (WCHAR*) "\x8a\x30\x83\x30\0"},
    {L"ryi",  (WCHAR*) "\x8a\x30\x43\x30\0"},
    {L"ryu",  (WCHAR*) "\x8a\x30\x85\x30\0"},
    {L"rye",  (WCHAR*) "\x8a\x30\x47\x30\0"},
    {L"ryo",  (WCHAR*) "\x8a\x30\x87\x30\0"},
    {L"wa",  (WCHAR*) "\x8f\x30\0"},
    {L"wi",  (WCHAR*) "\x46\x30\x43\x30\0"},
    {L"wu",  (WCHAR*) "\x46\x30\0"},
    {L"we",  (WCHAR*) "\x46\x30\x47\x30\0"},
    {L"wo",  (WCHAR*) "\x92\x30\0"},
    {L"ga",  (WCHAR*) "\x4c\x30\0"},
    {L"gi",  (WCHAR*) "\x4e\x30\0"},
    {L"gu",  (WCHAR*) "\x50\x30\0"},
    {L"ge",  (WCHAR*) "\x52\x30\0"},
    {L"go",  (WCHAR*) "\x54\x30\0"},
    {L"gya",  (WCHAR*) "\x4e\x30\x83\x30\0"},
    {L"gyi",  (WCHAR*) "\x4e\x30\x43\x30\0"},
    {L"gyu",  (WCHAR*) "\x4e\x30\x85\x30\0"},
    {L"gye",  (WCHAR*) "\x4e\x30\x47\x30\0"},
    {L"gyo",  (WCHAR*) "\x4e\x30\x87\x30\0"},
    {L"gwa",  (WCHAR*) "\x50\x30\x41\x30\0"},
    {L"gwi",  (WCHAR*) "\x50\x30\x43\x30\0"},
    {L"gwu",  (WCHAR*) "\x50\x30\x45\x30\0"},
    {L"gwe",  (WCHAR*) "\x50\x30\x47\x30\0"},
    {L"gwo",  (WCHAR*) "\x50\x30\x49\x30\0"},
    {L"za",  (WCHAR*) "\x56\x30\0"},
    {L"zi",  (WCHAR*) "\x58\x30\0"},
    {L"zu",  (WCHAR*) "\x5a\x30\0"},
    {L"ze",  (WCHAR*) "\x5c\x30\0"},
    {L"zo",  (WCHAR*) "\x5e\x30\0"},
    {L"ja",  (WCHAR*) "\x58\x30\x83\x30\0"},
    {L"ji",  (WCHAR*) "\x58\x30\0"},
    {L"ju",  (WCHAR*) "\x58\x30\x85\x30\0"},
    {L"je",  (WCHAR*) "\x58\x30\x47\x30\0"},
    {L"jo",  (WCHAR*) "\x58\x30\x87\x30\0"},
    {L"jya",  (WCHAR*) "\x58\x30\x83\x30\0"},
    {L"jyi",  (WCHAR*) "\x58\x30\x43\x30\0"},
    {L"jyu",  (WCHAR*) "\x58\x30\x85\x30\0"},
    {L"jye",  (WCHAR*) "\x58\x30\x47\x30\0"},
    {L"jyo",  (WCHAR*) "\x58\x30\x87\x30\0"},
    {L"zya",  (WCHAR*) "\x58\x30\x83\x30\0"},
    {L"zyi",  (WCHAR*) "\x58\x30\x43\x30\0"},
    {L"zyu",  (WCHAR*) "\x58\x30\x85\x30\0"},
    {L"zye",  (WCHAR*) "\x58\x30\x47\x30\0"},
    {L"zyo",  (WCHAR*) "\x58\x30\x87\x30\0"},
    {L"da",  (WCHAR*) "\x60\x30\0"},
    {L"di",  (WCHAR*) "\x62\x30\0"},
    {L"du",  (WCHAR*) "\x65\x30\0"},
    {L"de",  (WCHAR*) "\x67\x30\0"},
    {L"do",  (WCHAR*) "\x69\x30\0"},
    {L"dya",  (WCHAR*) "\x62\x30\x83\x30\0"},
    {L"dyi",  (WCHAR*) "\x62\x30\x43\x30\0"},
    {L"dyu",  (WCHAR*) "\x62\x30\x85\x30\0"},
    {L"dye",  (WCHAR*) "\x62\x30\x47\x30\0"},
    {L"dyo",  (WCHAR*) "\x62\x30\x87\x30\0"},
    {L"dha",  (WCHAR*) "\x67\x30\x83\x30\0"},
    {L"dhi",  (WCHAR*) "\x67\x30\x43\x30\0"},
    {L"dhu",  (WCHAR*) "\x67\x30\x85\x30\0"},
    {L"dhe",  (WCHAR*) "\x67\x30\x47\x30\0"},
    {L"dho",  (WCHAR*) "\x67\x30\x87\x30\0"},
    {L"dwa",  (WCHAR*) "\x69\x30\x41\x30\0"},
    {L"dwi",  (WCHAR*) "\x69\x30\x43\x30\0"},
    {L"dwu",  (WCHAR*) "\x69\x30\x45\x30\0"},
    {L"dwe",  (WCHAR*) "\x69\x30\x47\x30\0"},
    {L"dwo",  (WCHAR*) "\x69\x30\x49\x30\0"},
    {L"ba",  (WCHAR*) "\x70\x30\0"},
    {L"bi",  (WCHAR*) "\x73\x30\0"},
    {L"bu",  (WCHAR*) "\x76\x30\0"},
    {L"be",  (WCHAR*) "\x79\x30\0"},
    {L"bo",  (WCHAR*) "\x7c\x30\0"},
    {L"bya",  (WCHAR*) "\x73\x30\x83\x30\0"},
    {L"byi",  (WCHAR*) "\x73\x30\x43\x30\0"},
    {L"byu",  (WCHAR*) "\x73\x30\x85\x30\0"},
    {L"bye",  (WCHAR*) "\x73\x30\x47\x30\0"},
    {L"byo",  (WCHAR*) "\x73\x30\x87\x30\0"},
    {L"pa",  (WCHAR*) "\x71\x30\0"},
    {L"pi",  (WCHAR*) "\x74\x30\0"},
    {L"pu",  (WCHAR*) "\x77\x30\0"},
    {L"pe",  (WCHAR*) "\x7a\x30\0"},
    {L"po",  (WCHAR*) "\x7d\x30\0"},
    {L"pya",  (WCHAR*) "\x74\x30\x83\x30\0"},
    {L"pyi",  (WCHAR*) "\x74\x30\x43\x30\0"},
    {L"pyu",  (WCHAR*) "\x74\x30\x85\x30\0"},
    {L"pye",  (WCHAR*) "\x74\x30\x47\x30\0"},
    {L"pyo",  (WCHAR*) "\x74\x30\x87\x30\0"},
    {L"va",  (WCHAR*) "\xf4\x30\x41\x30\0"},
    {L"vi",  (WCHAR*) "\xf4\x30\x43\x30\0"},
    {L"vu",  (WCHAR*) "\xf4\x30\0"},
    {L"ve",  (WCHAR*) "\xf4\x30\x47\x30\0"},
    {L"vo",  (WCHAR*) "\xf4\x30\x49\x30\0"},
    {L"vya",  (WCHAR*) "\xf4\x30\x83\x30\0"},
    {L"vyi",  (WCHAR*) "\xf4\x30\x43\x30\0"},
    {L"vyu",  (WCHAR*) "\xf4\x30\x85\x30\0"},
    {L"vye",  (WCHAR*) "\xf4\x30\x47\x30\0"},
    {L"vyo",  (WCHAR*) "\xf4\x30\x87\x30\0"},
    {L"wha",  (WCHAR*) "\x46\x30\x41\x30\0"},
    {L"whi",  (WCHAR*) "\x46\x30\x43\x30\0"},
    {L"whu",  (WCHAR*) "\x46\x30\0"},
    {L"whe",  (WCHAR*) "\x46\x30\x47\x30\0"},
    {L"who",  (WCHAR*) "\x46\x30\x49\x30\0"},
    {L"xka",  (WCHAR*) "\xf5\x30\0"},
    {L"lka",  (WCHAR*) "\xf5\x30\0"},
    {L"xke",  (WCHAR*) "\xf6\x30\0"},
    {L"lke",  (WCHAR*) "\xf6\x30\0"},
    {L"xwa",  (WCHAR*) "\x8e\x30\0"},
    {L"lwa",  (WCHAR*) "\x8e\x30\0"},
    {L"nn",  (WCHAR*) "\x93\x30\0"},
};

static WCHAR *g_SokuonTable[] = {
	L"ll",
	L"xx",
	L"kk",
	L"cc",
	L"qq",
	L"ss",
	L"tt",
	L"hh",
	L"ff",
	L"mm",
	L"yy",
	L"rr",
	L"ww",
	L"gg",
	L"zz",
	L"jj",
	L"dd",
	L"bb",
	L"pp",
	L"vv",
	L"ww",
};

#define RomaTableMax (sizeof(g_RomaTable) / sizeof(ROMATABLE))
#define SokuonTableMax (sizeof(g_SokuonTable) / sizeof(WCHAR*))

WORD RKMatch(WCHAR *pwszRoma, WCHAR *pwszKana)
{
	int	i, j;

	if (pwszRoma[0] >= 0x0021 && pwszRoma[0] <= 0x0040
		|| pwszRoma[0] >= 0x005B && pwszRoma[0] <= 0x0060
		|| pwszRoma[0] >= 0x007B && pwszRoma[0] <= 0x007E)
	{
		pwszKana[0] = pwszRoma[0] + 0xFEE0;
		pwszKana[1] = L'\0';

        // special case for period, comma and dash
        switch(pwszKana[0]) {
        case SYMBOLS_FW_PERIOD:
            pwszKana[0] = SYMBOLS_IDEO_PERIOD;
            break;
        case SYMBOLS_FW_COMMA:
            pwszKana[0] = SYMBOLS_IDEO_COMMA;
            break;
        case SYMBOLS_FW_DASH:
            pwszKana[0] = SYMBOLS_JAPANESE_DASH;
            break;
        case SYMBOLS_FW_BACKSLASH:
            pwszKana[0] = SYMBOLS_YEN;
            break;
        default:
            break;
        }

		return 1;
	}

	for (i = 0; i < RomaTableMax; i++)
	{
		if (_wcsicmp(pwszRoma, g_RomaTable[i].roma) == 0)
		{
			wcscpy(pwszKana, g_RomaTable[i].kana);
			return(wcslen(g_RomaTable[i].kana));
		}
	}

	if (pwszRoma[1] == L'\0' || pwszRoma[2] == L'\0') return 0;

	if (pwszRoma[0] == L'N' || pwszRoma[0] == L'n')
	{
		for (i = 0; i < RomaTableMax; i++)
		{
			if (_wcsicmp(pwszRoma + 1, g_RomaTable[i].roma) == 0)
			{
				wcscpy(pwszKana, (WCHAR*) "\x93\x30\0");
				wcscat(pwszKana, g_RomaTable[i].kana);
				return(wcslen(g_RomaTable[i].kana) + 1);
			}
		}
	}
	for (j = 0; j < SokuonTableMax; j++)
	{
		if (_wcsnicmp(pwszRoma, g_SokuonTable[j], 2) == 0)
		{
			for (i = 0; i < RomaTableMax; i++)
			{
				if (_wcsicmp(pwszRoma + 1, g_RomaTable[i].roma) == 0)
				{
					wcscpy(pwszKana, (WCHAR*) "\x63\x30\0");
					wcscat(pwszKana, g_RomaTable[i].kana);
					return(wcslen(g_RomaTable[i].kana) + 1);
				}
			}
		}
	}
	return 0;
}
