#include "CompileShader.h"

namespace Spyder {
	std::vector<uint32_t> CompileShader::compileShader(const std::string &source, const std::string &shaderName, shaderc_shader_kind kind, const shaderc::Compiler &compiler, const shaderc::CompileOptions &compileOptions) {
		SPYDER_CORE_TRACE("Compiling shader...");
		shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, kind, shaderName.c_str(), compileOptions);
		if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
			SPYDER_CORE_ERROR("Shader compilation failed: {}", module.GetErrorMessage());
			return {};
		}

		SPYDER_CORE_TRACE("Shader compiled successfully");
		return {module.cbegin(), module.cend()};
	}
} // Spyder