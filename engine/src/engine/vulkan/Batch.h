#pragma once

#include "MemoryManagement.h"
#include "Buffer.h"
#include "engine/core/Base.h"

namespace Spyder::Vulkan {

	class Batch {
	public:
		Batch(Device &device, MemoryManagement &memManager);

		void addToBatch(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);
		void buildBatch();
		void cleanup();
		void clearBatch();

		VkBuffer getVertexBuffer();
		VkBuffer getIndexBuffer();

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);

	private:
		Device &r_Device;
		MemoryManagement &r_MemoryManager;
		Buffer m_VertexBuffer{r_Device, r_MemoryManager};
		Buffer m_IndexBuffer{r_Device, r_MemoryManager};
		std::vector<Vertex> m_Vertices{};
		std::vector<uint32_t> m_Indices{};
	};

} // Vulkan