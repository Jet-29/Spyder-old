#include "MemoryManagement.h"

namespace Spyder::Vulkan {
	MemoryManagement::MemoryManagement(Instance &instance, Device &device) : r_Instance{instance}, r_Device{device} {}

	void MemoryManagement::init() {
		SPYDER_CORE_TRACE("Initializing memory management...");
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
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;


		VK_CHECK(vmaCreateBuffer(m_Allocator, &bufferCreateInfo, &allocationCreateInfo, &buffer, &bufferMemoryAllocation, nullptr));
	}

	void MemoryManagement::createImage(VkImage &image, VmaAllocation &imageMemory, VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties) {
		VmaAllocationCreateInfo allocationCreateInfo{};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
		allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;

		VK_CHECK(vmaCreateImage(m_Allocator, &imageInfo, &allocationCreateInfo, &image, &imageMemory, nullptr));
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

	void MemoryManagement::destroyBuffer(VkBuffer &buffer, VmaAllocation &memoryAllocation) {
		m_DeletionQueues[m_CurrentIndex].push_function(
				[=]() {
					vmaDestroyBuffer(m_Allocator, buffer, memoryAllocation);
				});
	}

	void MemoryManagement::destroyImage(VkImage &image, VmaAllocation &memoryAllocation) {
		m_DeletionQueues[m_CurrentIndex].push_function(
				[=]() {
					vmaDestroyImage(m_Allocator, image, memoryAllocation);
				});
	}

	void MemoryManagement::cleanup() {
		SPYDER_CORE_TRACE("Memory management cleanup");
		for (DeletionQueue &deletionQueue : m_DeletionQueues) {
			deletionQueue.flush();
		}
		vmaDestroyAllocator(m_Allocator);
	}

	void MemoryManagement::flush() {
		m_DeletionQueues[m_CurrentIndex].flush();
	}

	void MemoryManagement::setCurrentIndex(uint32_t index) {
		m_CurrentIndex = index;
	}
} // Vulkan