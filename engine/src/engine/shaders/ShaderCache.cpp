#include "ShaderCache.h"
#include "CompileShader.h"

namespace Spyder {

	std::vector<uint32_t> ShaderCache::getShader(const std::string &source, const std::string& shaderName, shaderc_shader_kind kind) {
		SPYDER_CORE_TRACE("Checking if shader has been compiled");
		if (cache.contains(source)) {
			SPYDER_CORE_TRACE("Shader already compiled, using cached");
			return cache.at(source);
		}
		SPYDER_CORE_TRACE("Shader not compiled, compiling...");
		cache[source] = CompileShader::compileShader(source, shaderName, kind, m_Compiler, m_CompileOptions);
		return cache.at(source);
	}

	ShaderCache::ShaderCache() {
		SPYDER_CORE_TRACE("ShaderCache initialized");
		m_CompileOptions.SetOptimizationLevel(shaderc_optimization_level_performance);
	}
} // Spyder