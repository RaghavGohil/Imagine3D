#pragma once

#include "IM3D/Core/Log.h"

namespace IM3D
{

class Renderer
{

public:
    Renderer() = delete;
    static void Init();
    static enum class Context : uint8_t
    {
        None,
        OpenGL,
        // add more here?
    };
    static Context context;
    
private:

};

};