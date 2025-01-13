#pragma once
#include "IM3Dpch.h"

namespace IM3D {

    struct WindowOptions {
        uint32_t Width = 1920;
        uint32_t Height = 1080;
        std::string Title = "Imagine3D Application";

        WindowOptions(uint32_t width = 1920, uint32_t height = 1080, const std::string& title = "Imagine3D Application")
            : Width(width), Height(height), Title(title) {}
    };

}
