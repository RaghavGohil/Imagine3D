#pragma once

#ifdef IM3D_PLATFORM_WINDOWS

extern IM3D::Application* IM3D::CreateApplication();

int main(int argc, char** argv) {
    auto application = IM3D::CreateApplication();
    application->Run();
    delete application;
}

#endif