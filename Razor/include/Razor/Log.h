#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Razor
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> GetCoreLogger()
        {
            return s_CoreLogger;
        }

        inline static std::shared_ptr<spdlog::logger> GetClientLogger()
        {
            return s_ClientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define RZR_CORE_TRACE(...)   Razor::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RZR_CORE_INFO(...)    Razor::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RZR_CORE_WARN(...)    Razor::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RZR_CORE_ERROR(...)   Razor::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RZR_CORE_FATAL(...)   Razor::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Clinet log macros
#define RZR_TRACE(...)   Razor::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RZR_INFO(...)    Razor::Log::GetClientLogger()->info(__VA_ARGS__)
#define RZR_WARN(...)    Razor::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RZR_ERROR(...)   Razor::Log::GetClientLogger()->error(__VA_ARGS__)
#define RZR_FATAL(...)   Razor::Log::GetClientLogger()->fatal(__VA_ARGS__)