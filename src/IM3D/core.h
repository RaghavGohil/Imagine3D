#pragma once

// DLL Export/Import Macros for Windows
#ifdef IM3D_PLATFORM_WINDOWS
    #ifdef IM3D_DYNAMIC_LINK
        #ifdef IM3D_BUILD_DLL
            #define IM3D_API __declspec(dllexport)
        #else
            #define IM3D_API __declspec(dllimport)
        #endif
    #else
        #error Imagine3D only supports Windows for now!
    #endif
#else
    #error Imagine3D only supports Windows for now!
    #define IM3D_API
#endif

// Application Entry Point
//#ifdef IM3D_PLATFORM_WINDOWS
//extern IM3D_API int Main(int argc, char** argv);
//
//#define IM3D_ENTRY_POINT(...) \
//int main(int argc, char** argv) { \
//    return Main(argc, argv); \
//}
//#else
//    #error Imagine3D only supports Windows for now!
//    #define IM3D_API
//#endif