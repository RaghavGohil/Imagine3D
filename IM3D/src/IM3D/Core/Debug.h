#pragma once

#include "IM3D/Core/Log.h" 

#ifdef IM3D_ENABLE_DEBUG
	#if defined(IM3D_PLATFORM_WINDOWS)
		#define IM3D_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define IM3D_ENABLE_ASSERTS
#else
	#define IM3D_DEBUGBREAK()
#endif

#ifdef IM3D_ENABLE_ASSERTS

    #define IM3D_ASSERT(condition, ...) { \
        if (!(condition)) { \
            IM3D_LOG_CORE(IM3D_ERR, "Assertion failed: {0}", __VA_ARGS__); \
            IM3D_DEBUGBREAK(); \
        } \
    }

    #define IM3D_ASSERT_NO_MSG(condition) { \
        if (!(condition)) { \
            IM3D_LOG_CORE(IM3D_ERR, "Assertion '{0}' failed at {1}:{2}", #condition); \
            IM3D_DEBUGBREAK(); \
        } \
    }

#else
    #define IM3D_ASSERT(...)
    #define IM3D_ASSERT_NO_MSG(...)
#endif