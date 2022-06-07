#pragma once

#include "Instance.h"
#include "Device.h"
#include "SwapChain.h"
#include "CommandPool.h"
#include "MemoryManagement.h"

namespace Spyder::Vulkan {

	class Renderer {
	public:
		Renderer(Window &window);
		~Renderer() = default;

		Renderer(const Renderer &) = delete;
		Renderer &operator=(const Renderer &) = delete;

		void init();

		void render();

	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();

		void beginFrame();
		void endFrame();
		void beginSwapChainRenderPass();
		void endSwapChainRenderPass();

		Window &r_Window;
		Instance m_Instance{};
		Surface m_Surface{m_Instance, r_Window};
		Device m_Device{m_Instance, m_Surface};
		MemoryManagement m_MemoryManager{m_Instance, m_Device};
		CommandPool m_CommandPool{m_Device};
		SwapChain m_SwapChain{m_Device, m_Surface};

		std::vector<VkCommandBuffer> m_CommandBuffers;
		uint32_t m_CurrentImageIndex{0};
		uint32_t m_CurrentFrameIndex{0};
		bool m_IsFrameStarted = false;
	};

} // Vulkan