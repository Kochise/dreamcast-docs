//BaseLevelGetterExport.h
#ifndef BASE_LEVEL_GETTER_EXPORT_DLL_H
#define BASE_LEVEL_GETTER_EXPORT_DLL_H

#if defined(BASE_LEVEL_GETTER_DLL)
	#define BASE_LEVEL_GETTER_EXPORT __declspec(dllexport)
#else
	#define BASE_LEVEL_GETTER_EXPORT __declspec(dllimport)
#endif

#endif //BASE_LEVEL_GETTER_EXPORT_DLL_H


