#include "MemoryManagement.h"

namespace Spyder::Vulkan {
	MemoryManagement::MemoryManagement(Instance &instance, Device &device) : r_Instance{instance}, r_Device{device} {}

	void MemoryManagement::init() {
		VmaAllocatorCreateInfo allocatorCreateInfo = {};
		allocatorCreateInfo.vulkanApiVersion = r_Instance.getApiVersion();
		allocatorCreateInfo.physicalDevice = r_Device.getPhysicalDevice();
		allocatorCreateInfo.device = r_Device.getDevice();
		allocatorCreateInfo.instance = r_Instance.getInstance();

		vmaCreateAllocator(&allocatorCreateInfo, &m_Allocator);
	}

	void MemoryManagement::createBuffer(VkBuffer &buffer, VmaAllocation &bufferMemoryAllocation, VkDeviceSize size, VkBufferUsageFlags usage) {
		VkBufferCreateInfo bufferCreateInfo{};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.pNext = nullptr;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = usage;
		bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VmaAllocationCreateInfo allocationCreateInfo{};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;


		VK_CHECK(vmaCreateBuffer(m_Allocator, &bufferCreateInfo, &allocationCreateInfo, &buffer, &bufferMemoryAllocation, nullptr));
	}

	VkResult MemoryManagement::mapMemory(VmaAllocation &memoryAllocation, void **data) {
		return vmaMapMemory(m_Allocator, memoryAllocation, data);
	}

	void MemoryManagement::unmapMemory(VmaAllocation &memoryAllocation) {
		vmaUnmapMemory(m_Allocator, memoryAllocation);
	}

	VkResult MemoryManagement::flushMemory(VmaAllocation &memoryAllocation, VkDeviceSize offset, VkDeviceSize size) {
		return vmaFlushAllocation(m_Allocator, memoryAllocation, offset, size);
	}

	VkResult MemoryManagement::invalidateMemory(VmaAllocation &memoryAllocation, VkDeviceSize offset, VkDeviceSize size) {
		return vmaInvalidateAllocation(m_Allocator, memoryAllocation, offset, size);
	}
} // Vulkan