#pragma once

#include "IM3Dpch.h"
#include "IM3D/Core/PlatformDetection.h"
#include "IM3D/Core/Log.h"
#include "IM3D/Renderer/Renderer.h"
#include "IM3D/Window/Window.h"

namespace IM3D
{

    class IM3D_API Application
    {
    
    public:

        Application(); 
        ~Application(); 
        void Init() const;
        void Run() const;

    private:

    };

    std::shared_ptr<Application> CreateApplication(); // defined in the client for flexibility.

};