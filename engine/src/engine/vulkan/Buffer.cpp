#include "Buffer.h"

namespace Spyder::Vulkan {
	Buffer::Buffer(Device &device, MemoryManagement &memoryManagement) : r_Device{device}, r_MemoryManagement{memoryManagement} {}

	VkResult Buffer::map() {
		if (!m_Buffer && !m_Memory) SPYDER_CORE_ERROR("Called map con buffer before created");
		return r_MemoryManagement.mapMemory(m_Memory, &p_Mapped);
	}

	void Buffer::unmap() {
		if (p_Mapped) {
			r_MemoryManagement.unmapMemory(m_Memory);
			p_Mapped = nullptr;
		}
	}

	void Buffer::writeToBuffer(void *data, VkDeviceSize size, VkDeviceSize offset) {
		if (!p_Mapped) SPYDER_CORE_ERROR("Cannot copy to unmapped buffer");

		if (size == VK_WHOLE_SIZE) {
			memcpy(p_Mapped, data, m_BufferSize);
		} else {
			char *memOffset = (char *)p_Mapped;
			memOffset += offset;
			memcpy(memOffset, data, size);
		}
	}

	VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset) {
		return r_MemoryManagement.flushMemory(m_Memory, offset, size);
	}

	VkDescriptorBufferInfo Buffer::descriptorInfo(VkDeviceSize size, VkDeviceSize offset) {
		return VkDescriptorBufferInfo{m_Buffer, offset, size};
	}

	VkResult Buffer::invalidate(VkDeviceSize size, VkDeviceSize offset) {
		return r_MemoryManagement.invalidateMemory(m_Memory, offset, size);
	}

	void Buffer::writeToIndex(void *data, int index) {
		writeToBuffer(data, m_InstanceSize, index * m_AlignmentSize);
	}

	VkResult Buffer::flushIndex(int index) {
		return flush(m_AlignmentSize, index * m_AlignmentSize);
	}

	VkDescriptorBufferInfo Buffer::descriptorInfoForIndex(int index) {
		return descriptorInfo(m_AlignmentSize, index * m_AlignmentSize);
	}

	VkResult Buffer::invalidateIndex(int index) {
		return invalidate(m_AlignmentSize, index * m_AlignmentSize);
	}

	VkDeviceSize Buffer::getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment) {
		if (minOffsetAlignment > 0) {
			return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
		}
		return instanceSize;
	}

	void Buffer::createBuffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkDeviceSize minOffsetAlignment) {
		m_AlignmentSize = getAlignment(instanceSize, minOffsetAlignment);
		m_BufferSize = m_AlignmentSize * instanceCount;
		r_MemoryManagement.createBuffer(m_Buffer, m_Memory, m_BufferSize, usageFlags);
	}

	void Buffer::createBuffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags) {
		SPYDER_CORE_TRACE("Device minimum buffer offset: {}", r_Device.m_Properties.limits.minUniformBufferOffsetAlignment);
		createBuffer(instanceSize, instanceCount, usageFlags, r_Device.m_Properties.limits.minUniformBufferOffsetAlignment);
	}
} // Vulkan