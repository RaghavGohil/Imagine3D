#include "IM3D/Window/Window.h"
#include "IM3D/Window/WindowGLFW.h"

namespace IM3D {

    std::unique_ptr<Window> Window::Create(const WindowOptions& options) {
        return std::make_unique<WindowGLFW>(options);
    }

}
