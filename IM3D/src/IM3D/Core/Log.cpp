#include "IM3D/Core/Log.h"

namespace IM3D
{

    std::shared_ptr<spdlog::logger> Log::s_LogCore;
    std::shared_ptr<spdlog::logger> Log::s_LogClient;

    void Log::Init()
    {

        s_LogCore = spdlog::stdout_color_mt("CORE");
        s_LogCore->set_level(spdlog::level::trace); // Default to trace level

        s_LogClient = spdlog::stdout_color_mt("CLIENT");
        s_LogClient->set_level(spdlog::level::trace);

        //s_LogCore->trace("Core Logger initialized");

    }

};