#pragma once

#include "Instance.h"
#include "Device.h"

#include "MemoryAllocator.h"

namespace Spyder::Vulkan {

	class MemoryManagement {
	public:
		MemoryManagement(Instance &instance, Device &device);
		~MemoryManagement() = default;

		MemoryManagement(const MemoryManagement &) = delete;
		MemoryManagement &operator=(const MemoryManagement &) = delete;

		void init();

		void createBuffer(VkBuffer buffer, VmaAllocation bufferMemoryAllocation, VkDeviceSize size, VkBufferUsageFlags usage);
		VkResult mapMemory(VmaAllocation memoryAllocation, void *data);
		void unmapMemory(VmaAllocation memoryAllocation);
		VkResult flushMemory(VmaAllocation memoryAllocation, VkDeviceSize offset, VkDeviceSize size);
		VkResult invalidateMemory(VmaAllocation memoryAllocation, VkDeviceSize offset, VkDeviceSize size);

	private:
		Instance &r_Instance;
		Device &r_Device;

		VmaAllocator m_Allocator{};
	};

} // Vulkan