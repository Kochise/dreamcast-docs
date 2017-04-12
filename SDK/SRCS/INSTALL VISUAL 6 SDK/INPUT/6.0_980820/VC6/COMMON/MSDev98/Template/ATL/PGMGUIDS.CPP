#define INITGUID
#define DBINITCONSTANTS

[!if=(FileExists, "FALSE")]
#include <oledb.h>
#include <msdadc.h>
[!else]
[!AddIncludeFile(TargetFile, "<oledb.h>")]
[!AddIncludeFile(TargetFile, "<msdadc.h>")]
[!endif]