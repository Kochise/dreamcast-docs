[!Dialog("ConsProp98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddSymbolToSymbol(TargetHeader, ProjectDirectory, HeaderName)]
[!AddStringToSymbol(HeaderTemplate, GalleryPath, "consumer.h")]

[!target(TargetHeader)]
[!include(HeaderTemplate)]
[!target()]

[!if!(stdafx.h)]
[!set(stdafx.h, "stdafx.h")]
[!endif]
[!if!(stdafx.cpp)]
[!set(stdafx.cpp, "stdafx.cpp")]
[!endif]
[!set(atldbcli.h, "<atldbcli.h>")]
[!AddIncludeFile(stdafx.h, atldbcli.h)]

[!AddFileToProject(TargetHeader)]
[!Commit]
