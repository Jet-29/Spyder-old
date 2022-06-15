#pragma once

#include "Instance.h"
#include "Device.h"

namespace Spyder::Vulkan {

	struct DeletionQueue {
		std::deque<std::function<void()>> deletors;

		void push_function(std::function<void()> &&function) {
			deletors.push_back(function);
		}

		void flush() {
			for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
				(*it)();
			}

			deletors.clear();
		}
	};

	class MemoryManagement {
	public:
		MemoryManagement(Instance &instance, Device &device);
		~MemoryManagement() = default;

		MemoryManagement(const MemoryManagement &) = delete;
		MemoryManagement &operator=(const MemoryManagement &) = delete;

		void init();
		void setCurrentIndex(uint32_t index);
		void flush();
		void cleanup();

		void createBuffer(VkBuffer &buffer, VmaAllocation &bufferMemoryAllocation, VkDeviceSize size, VkBufferUsageFlags usage);
		void createImage(VkImage &image, VmaAllocation &imageMemory, VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties);
		VkResult mapMemory(VmaAllocation &memoryAllocation, void **data);
		void unmapMemory(VmaAllocation &memoryAllocation);
		VkResult flushMemory(VmaAllocation &memoryAllocation, VkDeviceSize offset, VkDeviceSize size);
		VkResult invalidateMemory(VmaAllocation &memoryAllocation, VkDeviceSize offset, VkDeviceSize size);

		void destroyBuffer(VkBuffer &buffer, VmaAllocation &memoryAllocation);
		void destroyImage(VkImage &image, VmaAllocation &memoryAllocation);

	private:
		Instance &r_Instance;
		Device &r_Device;

		uint32_t m_CurrentIndex{0};
		std::vector<DeletionQueue> m_DeletionQueues{MAX_FRAMES_IN_FLIGHT};

		VmaAllocator m_Allocator{};
	};

} // Vulkan