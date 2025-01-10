#pragma once

#include "IM3D/Core/PlatformDetection.h"
#include "IM3D/Core/Log.h"

namespace IM3D
{

    class IM3D_API Application
    {
    
    public:
        Application(); 
        ~Application(); 
        void Run() const;
    private:
    };

    Application* CreateApplication(); // defined in the client for flexibility.

};