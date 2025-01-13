#pragma once

#include "IM3Dpch.h"

#ifdef IM3D_PLATFORM_WINDOWS

extern std::shared_ptr<IM3D::Application> IM3D::CreateApplication();

int main(int argc, char** argv) {
    std::shared_ptr<IM3D::Application> application = IM3D::CreateApplication();
    application->Init();
    application->Run();
}

#endif