#include "CommandPool.h"

namespace Spyder::Vulkan {
	CommandPool::CommandPool(Device &device) : r_Device{device} {}

	void CommandPool::init() {
		QueueFamilyIndices queueFamilyIndices = r_Device.findPhysicalQueueFamilies();

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VK_CHECK(vkCreateCommandPool(r_Device.getDevice(), &poolInfo, nullptr, &m_CommandPool));
	}
} // Vulkan