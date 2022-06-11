#pragma once

#include "engine/vulkan/VulkanBase.h"
#include "Device.h"

namespace Spyder::Vulkan {

	class CommandPool {
	public:
		CommandPool(Device &device);
		~CommandPool() = default;

		CommandPool(const CommandPool &) = delete;
		CommandPool &operator=(const CommandPool &) = delete;

		void init();
		void cleanup();

		VkCommandPool getCommandPool() { return m_CommandPool; }

	private:
		Device &r_Device;
		VkCommandPool m_CommandPool{};
	};

} // Vulkan