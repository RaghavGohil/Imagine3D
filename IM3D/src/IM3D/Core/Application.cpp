#include "IM3Dpch.h"
#include "IM3D/Core/Application.h"

namespace IM3D{

    Application::Application(){}
    Application::~Application(){}

    void Application::Run() const
    {
        Log log;
        std::cout << "IM3D engine is now running!" << std::endl;
    }

};