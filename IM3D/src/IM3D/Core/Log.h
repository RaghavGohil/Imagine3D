#pragma once

#include "IM3Dpch.h"
#include "IM3D/Core/PlatformDetection.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace IM3D
{

    class IM3D_API Log
    {

    public:
        
        Log() = delete;
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetLogCore() { return s_LogCore; }
        inline static std::shared_ptr<spdlog::logger>& GetLogClient() { return s_LogClient; }

    private:

        static std::shared_ptr<spdlog::logger> s_LogCore;
        static std::shared_ptr<spdlog::logger> s_LogClient;

    };

    #define IM3D_TRACE  spdlog::level::trace
    #define IM3D_DEBUG  spdlog::level::debug
    #define IM3D_INFO   spdlog::level::info
    #define IM3D_WARN   spdlog::level::warn
    #define IM3D_ERR    spdlog::level::err
    #define IM3D_CTCL   spdlog::level::critical

    // Logging macros for core and client messages
    #define IM3D_LOG_CORE(severity, msg, ...) \
        ::IM3D::Log::GetLogCore()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, severity, msg, ##__VA_ARGS__)

    #define IM3D_LOG_CLIENT(severity, msg, ...) \
        ::IM3D::Log::GetLogClient()->log(spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}, severity, msg, ##__VA_ARGS__)

};
