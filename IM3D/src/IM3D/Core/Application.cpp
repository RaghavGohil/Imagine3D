#include "IM3D/Core/Application.h"

namespace IM3D{

    Application::Application(){}
    Application::~Application(){}

    void Application::Run() const
    {

        Log::Init();
        IM3D_LOG_CORE(IM3D_INFO,"IM3D has started running!");

    }

};