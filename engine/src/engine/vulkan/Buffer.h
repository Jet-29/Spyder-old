#pragma once

#include "Device.h"
#include "MemoryManagement.h"

namespace Spyder::Vulkan {

	class Buffer {
	public:
		Buffer(Device &device, MemoryManagement &memoryManagement);
		~Buffer() = default;

		Buffer(const Buffer &) = delete;
		Buffer &operator=(const Buffer &) = delete;

		void createBuffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkDeviceSize minOffsetAlignment);
		void createBuffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags);

		VkResult map();
		void unmap();
		void writeToBuffer(void *data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkDescriptorBufferInfo descriptorInfo(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void writeToIndex(void *data, int index);
		VkResult flushIndex(int index);
		VkDescriptorBufferInfo descriptorInfoForIndex(int index);
		VkResult invalidateIndex(int index);

		[[nodiscard]] VkBuffer getBuffer() const {
			return m_Buffer;
		}

		[[nodiscard]] void *getMappedMemory() const {
			return p_Mapped;
		}

		[[nodiscard]] uint32_t getInstanceCount() const {
			return m_InstanceCount;
		}

		[[nodiscard]] VkDeviceSize getInstanceSize() const {
			return m_InstanceSize;
		}

		[[nodiscard]] VkDeviceSize getAlignmentSize() const {
			return m_AlignmentSize;
		}

		[[nodiscard]] VkBufferUsageFlags getUsageFlags() const {
			return m_UsageFlags;
		}

		[[nodiscard]] VkMemoryPropertyFlags getMemoryPropertyFlags() const {
			return m_MemoryPropertyFlags;
		}

		[[nodiscard]] VkDeviceSize getBufferSize() const {
			return m_BufferSize;
		}

	private:
		static VkDeviceSize getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);

		Device &r_Device;
		MemoryManagement &r_MemoryManagement;
		void *p_Mapped = nullptr;
		VkBuffer m_Buffer = VK_NULL_HANDLE;
		VmaAllocation m_Memory;

		uint32_t m_MinOffsetAlignment;

		VkDeviceSize m_BufferSize;
		uint32_t m_InstanceCount;
		VkDeviceSize m_InstanceSize;
		VkDeviceSize m_AlignmentSize;
		VkBufferUsageFlags m_UsageFlags;
		VkMemoryPropertyFlags m_MemoryPropertyFlags;
	};

} // Vulkan