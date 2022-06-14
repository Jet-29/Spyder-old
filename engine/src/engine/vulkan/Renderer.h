#pragma once

#include "Instance.h"
#include "Device.h"
#include "SwapChain.h"
#include "CommandPool.h"
#include "MemoryManagement.h"
#include "engine/vulkan/renderers/MeshRenderer.h"
#include "engine/vulkan/descriptors/DescriptorWriter.h"
#include "Buffer.h"
#include "engine/vulkan/gui/UI.h"

namespace Spyder::Vulkan {

	class Renderer {
	public:
		Renderer(Window &window);
		~Renderer() = default;

		Renderer(const Renderer &) = delete;
		Renderer &operator=(const Renderer &) = delete;

		void init();
		void render(GameObject::map &gameObjects);
		void cleanup();

	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();
		void createDescriptors();
		void deleteDescriptors();

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
		SwapChain m_SwapChain{m_Device, m_Surface, m_MemoryManager};
		ShaderCache m_ShaderCache{};
		MeshRenderer m_MeshRenderer{m_Device, m_MemoryManager, m_ShaderCache};
		UI m_GUI{m_Instance, m_Device};

		std::unique_ptr<DescriptorPool> p_GlobalUBOPool{};
		std::unique_ptr<DescriptorSetLayout> p_GlobalUBODescriptorSetLayout{};
		std::vector<std::unique_ptr<Buffer>> p_GlobalUBOBuffers{MAX_FRAMES_IN_FLIGHT};
		std::vector<VkDescriptorSet> p_GlobalUBODescriptorSets{MAX_FRAMES_IN_FLIGHT};

		std::vector<VkCommandBuffer> m_CommandBuffers;
		uint32_t m_CurrentImageIndex{0};
		uint32_t m_CurrentFrameIndex{0};
		bool m_IsFrameStarted = false;
	};

} // Vulkan