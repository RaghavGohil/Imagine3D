#pragma once

#include "IM3Dpch.h"
#include "IM3D/Window/WindowOptions.h"

namespace IM3D {

    class Window {
    public:
        virtual ~Window() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual void SetVsync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;

        static std::unique_ptr<Window> Create(const WindowOptions& options = WindowOptions());
    protected:
        WindowOptions m_Options;
    };

}
