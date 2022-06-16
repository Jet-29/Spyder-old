#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <spdlog/spdlog.h>

namespace Spyder {
	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

		inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
	return os << glm::to_string(quaternion);
}

// Core log macros
#define SPYDER_CORE_TRACE(...)    ::Spyder::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPYDER_CORE_INFO(...)     ::Spyder::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPYDER_CORE_WARN(...)     ::Spyder::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPYDER_CORE_ERROR(...)    ::Spyder::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPYDER_CORE_CRITICAL(...) ::Spyder::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPYDER_TRACE(...)         ::Spyder::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPYDER_INFO(...)          ::Spyder::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPYDER_WARN(...)          ::Spyder::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPYDER_ERROR(...)         ::Spyder::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPYDER_CRITICAL(...)      ::Spyder::Log::GetClientLogger()->critical(__VA_ARGS__)
