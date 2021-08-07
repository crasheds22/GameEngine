#pragma once

#ifdef NG_PLATFORM_WINDOWS
	#if NG_DYNAMIC_LINK
		#ifdef NG_BUILD_DLL
			#define ENGINE_API __declspec(dllexport)
		#else
			#define ENGINE_API __declspec(dllimport)
		#endif
	#else
		#define ENGINE_API
	#endif
#endif

#ifdef NG_DEBUG
	#define NG_ENABLE_ASSERTS
#endif

#ifdef NG_ENABLE_ASSERTS
	#define NG_ASSERT(x, ...) { if (!(x)) { NG_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NG_CORE_ASSERT(x, ...) { if (!(x)) { NG_CORE_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NG_ASSERT(x, ...)
	#define NG_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
