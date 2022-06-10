#include "Batch.h"

namespace Spyder::Vulkan {
	Batch::Batch(Device &device, MemoryManagement &memManager) : r_Device{device}, r_MemoryManager{memManager} {}


	void Batch::clearBatch() {
		m_Vertices.clear();
		m_Indices.clear();
	}

	void Batch::addToBatch(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices) {
		for (uint32_t &index : indices) {
			m_Vertices.push_back(vertices[index]);
			m_Indices.push_back(index);
		}
	}

	void Batch::buildBatch() {
		m_VertexBuffer.createBuffer(sizeof(Vertex), m_Vertices.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		m_VertexBuffer.map();
		m_VertexBuffer.writeToBuffer(m_Vertices.data());

		m_IndexBuffer.createBuffer(sizeof(Vertex), m_Vertices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
		m_IndexBuffer.map();
		m_IndexBuffer.writeToBuffer(m_Indices.data());
	}

	VkBuffer Batch::getVertexBuffer() {
		return m_VertexBuffer.getBuffer();
	}

	VkBuffer Batch::getIndexBuffer() {
		return m_IndexBuffer.getBuffer();;
	}

	void Batch::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = {m_VertexBuffer.getBuffer()};
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer.getBuffer(), 0, VK_INDEX_TYPE_UINT32);
	}

	void Batch::draw(VkCommandBuffer commandBuffer) {
		vkCmdDrawIndexed(commandBuffer, m_Indices.size(), 1, 0, 0, 0);
	}
} // Vulkan