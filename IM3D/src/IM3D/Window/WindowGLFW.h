#pragma once

#include "IM3Dpch.h"
#include "IM3D/Window/Window.h"
#include <GLFW/glfw3.h>

namespace IM3D {

    class WindowGLFW : public Window {
    public:
        WindowGLFW(const WindowOptions& options);
        ~WindowGLFW();

        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;
        void SetVsync(bool enabled) override;
        bool IsVsync() const override;

    private:
        GLFWwindow* m_Window;
    };

}
