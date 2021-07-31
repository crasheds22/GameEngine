#ifndef LOG_H
#define LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine {

	class ENGINE_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> CoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger> ClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define NG_CORE_ERROR(...)	::Engine::Log::CoreLogger()->error(__VA_ARGS__)
#define NG_CORE_WARN(...)	::Engine::Log::CoreLogger()->warn(__VA_ARGS__)
#define NG_CORE_INFO(...)	::Engine::Log::CoreLogger()->info(__VA_ARGS__)
#define NG_CORE_TRACE(...)	::Engine::Log::CoreLogger()->trace(__VA_ARGS__)

#define NG_ERROR(...)	::Engine::Log::ClientLogger()->error(__VA_ARGS__)
#define NG_WARN(...)	::Engine::Log::ClientLogger()->warn(__VA_ARGS__)
#define NG_INFO(...)	::Engine::Log::ClientLogger()->info(__VA_ARGS__)
#define NG_TRACE(...)	::Engine::Log::ClientLogger()->trace(__VA_ARGS__)

#endif