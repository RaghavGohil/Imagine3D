#include "IM3D/Window/WindowGLFW.h"
#include <stdexcept> // For error handling

namespace IM3D {

    WindowGLFW::WindowGLFW(const WindowOptions& options) : m_Window(nullptr) {
        m_Options = options;

        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        m_Window = glfwCreateWindow(m_Options.Width, m_Options.Height, m_Options.Title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_Window);
    }

    WindowGLFW::~WindowGLFW() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }

    uint32_t WindowGLFW::GetWidth() const {
        return m_Options.Width;
    }

    uint32_t WindowGLFW::GetHeight() const {
        return m_Options.Height;
    }

    void WindowGLFW::SetVsync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
    }

    bool WindowGLFW::IsVsync() const {
        return glfwGetWindowAttrib(m_Window, GLFW_CONTEXT_VERSION_MAJOR);
    }

}
