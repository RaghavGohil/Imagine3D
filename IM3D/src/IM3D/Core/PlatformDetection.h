#pragma once

#ifdef _WIN32
    #define IM3D_PLATFORM_WINDOWS
#else
    #error Imagine3D only supports Windows for now!
#endif

// DLL Export/Import Macros for Windows
#ifdef IM3D_PLATFORM_WINDOWS
    #ifdef IM3D_DYNAMIC_LINK
        #ifdef IM3D_BUILD_DLL
            #define IM3D_API __declspec(dllexport)
        #else
            #define IM3D_API __declspec(dllimport)
        #endif
    #else
        #define IM3D_API
    #endif
#else
    #define IM3D_API
#endif