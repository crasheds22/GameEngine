#pragma once

#ifdef NG_PLATFORM_WINDOWS
	#ifdef NG_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#endif
