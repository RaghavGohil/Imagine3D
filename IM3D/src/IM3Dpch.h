#pragma once

// global includes
#ifdef __cplusplus
    #include <iostream>
    #include <memory>
    #include <utility>
    #include <algorithm>
    #include <functional>
    #include <string>
    #include <sstream>
    #include <fstream>
    #include <array>
    #include <vector>
    #include <unordered_map>
    #include <unordered_set>
#endif

// platform specific
#ifdef IM3D_PLATFORM_WINDOWS
    #include <windows.h>
    #ifndef NOMINMAX
        // min max issue
        #define NOMINMAX
    #endif
#endif