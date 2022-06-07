#include "MemoryManagement.h"

namespace Spyder::Vulkan {
	MemoryManagement::MemoryManagement(Instance& instance, Device& device) : r_Instance{instance}, r_Device{device} {}

	void MemoryManagement::init() {
		VmaAllocatorCreateInfo allocatorCreateInfo = {};
		allocatorCreateInfo.vulkanApiVersion = r_Instance.getApiVersion();
		allocatorCreateInfo.physicalDevice = r_Device.getPhysicalDevice();
		allocatorCreateInfo.device = r_Device.getDevice();
		allocatorCreateInfo.instance = r_Instance.getInstance();

		vmaCreateAllocator(&allocatorCreateInfo, &m_Allocator);
	}
} // Vulkan