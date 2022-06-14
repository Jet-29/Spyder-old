#pragma once

#include "engine/vulkan/VulkanBase.h"
#include "engine/vulkan/SwapChain.h"
#include "engine/vulkan/Instance.h"
#include "engine/vulkan/CommandPool.h"
#include "engine/vulkan/gui/imgui/imgui.h"
#include "engine/vulkan/gui/imgui/imgui_impl_vulkan.h"
#include "engine/vulkan/gui/imgui/imgui_impl_glfw.h"

namespace Spyder::Vulkan {
	class UI {
	public:
		UI(Instance &instance, Device &device, SwapChain &swapChain, Window &window, CommandPool &commandPool);
		~UI() = default;

		UI(const UI &) = delete;
		UI &operator=(const UI &) = delete;

		void init();
		void render(FrameInfo &frameInfo);
		void cleanup();

	private:
		void setDarkThemeColors();

		Instance &r_Instance;
		Device &r_Device;
		Window &r_Window;
		SwapChain &r_SwapChain;
		CommandPool &r_CommandPool;

		VkDescriptorPool m_ImguiPool{};
		VkRenderPass m_ImguiRenderPass{};
	};
} // Spyder