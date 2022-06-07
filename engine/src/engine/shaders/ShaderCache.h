#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <shaderc/shaderc.hpp>

namespace Spyder {

	class ShaderCache {
	public:
		ShaderCache() = default;
		~ShaderCache() = default;

		ShaderCache(const ShaderCache &) = delete;
		ShaderCache &operator=(const ShaderCache &) = delete;

		void init();

		std::vector<uint32_t> getShader(const std::string &source, const std::string &shaderName, shaderc_shader_kind kind);

	private:
		std::unordered_map<std::string, std::vector<uint32_t>> cache{};
		shaderc::Compiler m_Compiler{};
		shaderc::CompileOptions m_CompileOptions{};
	};

} // Spyder