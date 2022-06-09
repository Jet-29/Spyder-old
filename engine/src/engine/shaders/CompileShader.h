#pragma once

#include <vector>
#include <string>
#include <shaderc/shaderc.hpp>
#include "engine/core/Base.h"

namespace Spyder {

	class CompileShader {
	public:
		static std::vector<uint32_t> compileShader(const std::string &source, const std::string &shaderName, shaderc_shader_kind kind, const shaderc::Compiler &compiler, const shaderc::CompileOptions &compileOptions);
	};

} // Spyder