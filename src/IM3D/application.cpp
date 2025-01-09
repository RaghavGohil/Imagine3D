#include "application.h"
#include <iostream>
namespace IM3D{
    Application::Application(){}
    Application::~Application(){}
    void Application::Run()
    {
        std::cout << "Welcome to IM3D Game Engine!" << std::endl;
    }
};