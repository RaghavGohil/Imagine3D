#include "IM3D/Core/Application.h"

namespace IM3D{

    Application::Application(){}
    Application::~Application(){}

    void Application::Init() const
    {

        Log::Init();
        Renderer::Init();
    }

    void Application::Run() const
    {
        auto window = Window::Create();
        while(true);
    }

};