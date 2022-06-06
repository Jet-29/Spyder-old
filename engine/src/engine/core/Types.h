#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "engine/utilities/UtilityFunctions.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Spyder {
	typedef enum SpyderFormat {
		Spyder_FORMAT_R32_UINT = 98, Spyder_FORMAT_R32_SINT = 99, Spyder_FORMAT_R32_SFLOAT = 100, Spyder_FORMAT_R32G32_UINT = 101, Spyder_FORMAT_R32G32_SINT = 102, Spyder_FORMAT_R32G32_SFLOAT = 103, Spyder_FORMAT_R32G32B32_UINT = 104, Spyder_FORMAT_R32G32B32_SINT = 105, Spyder_FORMAT_R32G32B32_SFLOAT = 106, Spyder_FORMAT_R32G32B32A32_UINT = 107, Spyder_FORMAT_R32G32B32A32_SINT = 108, Spyder_FORMAT_R32G32B32A32_SFLOAT = 109,
	} SpyderFormat;

	struct VertexInputBindingDescription {
		uint32_t binding{};
		uint32_t stride{};
		uint32_t inputRate{};
	};

	struct VertexInputAttributeDescription {
		uint32_t location{};
		uint32_t binding{};
		uint32_t format{};
		uint32_t offset{};
	};

	struct Vertex {
		glm::vec3 position{};
		glm::vec3 color{};
//	glm::vec3 normal{};
//	glm::vec2 uv{};

		static std::vector<VertexInputBindingDescription> getBindingDescriptions();
		static std::vector<VertexInputAttributeDescription> getAttributeDescriptions();

		bool operator==(const Vertex &other) const;
	};

	struct VertexHash {
		size_t operator()(Vertex const &vertex) const {
			size_t seed = 0;
			UtilityFunctions::hashCombine(seed, vertex.position, vertex.color);
			return seed;
		}
	};

}