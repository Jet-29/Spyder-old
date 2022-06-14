#pragma once

#include "engine/vulkan/VulkanBase.h"
#include "engine/vulkan/SwapChain.h"
#include "engine/vulkan/Instance.h"

namespace Spyder::Vulkan {
	class UI {
	public:
		UI(Instance &instance, Device &device);
		~UI() = default;

		UI(const UI &) = delete;
		UI &operator=(const UI &) = delete;

		void init();
		void cleanup();

	private:
		Instance &r_Instance;
		Device &r_Device;
		VkDescriptorPool m_ImguiPool{};
		VkRenderPass m_ImguiRenderPass{};
	};
} // Spyder