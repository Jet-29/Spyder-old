#include "Types.h"

namespace Spyder {

	std::vector<VertexInputBindingDescription> Vertex::getBindingDescriptions() {
		std::vector<VertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = 0;
		return bindingDescriptions;
	}

	std::vector<VertexInputAttributeDescription> Vertex::getAttributeDescriptions() {
		std::vector<VertexInputAttributeDescription> attributeDescriptions{};

		attributeDescriptions.push_back({0, 0, Spyder_FORMAT_R32G32B32_SFLOAT, (uint32_t)offsetof(Vertex, position)});
		attributeDescriptions.push_back({1, 0, Spyder_FORMAT_R32G32B32_SFLOAT, (uint32_t)offsetof(Vertex, color)});
//	attributeDescriptions.push_back({2, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t)offsetof(Vertex, normal)});
//	attributeDescriptions.push_back({3, 0, VK_FORMAT_R32G32_SFLOAT, (uint32_t)offsetof(Vertex, uv)});
		return attributeDescriptions;
	}

	bool Vertex::operator==(const Vertex &other) const {
		return position == other.position && color == other.color;
	}
}