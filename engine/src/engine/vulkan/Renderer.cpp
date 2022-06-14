#include "Renderer.h"

namespace Spyder::Vulkan {
	Renderer::Renderer(Window &window) : r_Window{window} {}

	void Renderer::init() {
		SPYDER_CORE_TRACE("Initializing vulkan renderer...");
		m_Instance.init();
		m_Surface.init();
		m_Device.init();
		m_MemoryManager.init();
		m_CommandPool.init();
		m_SwapChain.init(r_Window.getWindowExtent());
		m_ShaderCache.init();
		createDescriptors();
		m_MeshRenderer.init(m_SwapChain.getRenderPass(), p_GlobalUBODescriptorSetLayout->getDescriptorSetLayout());
		createCommandBuffers();
		m_GUI.init();
		SPYDER_CORE_TRACE("Vulkan render initialized");
	}

	void Renderer::cleanup() {
		SPYDER_CORE_TRACE("Renderer cleanup");
		m_Device.waitForDevice();

		m_GUI.cleanup();
		freeCommandBuffers();
		deleteDescriptors();
		m_MeshRenderer.cleanup();
		m_SwapChain.cleanup();
		m_CommandPool.cleanup();
		m_MemoryManager.cleanup();
		m_Device.cleanup();
		m_Surface.cleanup();
		m_Instance.cleanup();
	}

	void Renderer::createCommandBuffers() {
		SPYDER_CORE_TRACE("Creating command buffers");
		m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

		VK_CHECK(vkAllocateCommandBuffers(m_Device.getDevice(), &allocInfo, m_CommandBuffers.data()));
	}

	void Renderer::freeCommandBuffers() {
		SPYDER_CORE_TRACE("Freeing command buffers");
		vkFreeCommandBuffers(m_Device.getDevice(), m_CommandPool.getCommandPool(), static_cast<uint32_t>(m_CommandBuffers.size()), m_CommandBuffers.data());
		m_CommandBuffers.clear();
	}

	void Renderer::recreateSwapChain() {
		SPYDER_CORE_TRACE("Recreating swap chain...");
		auto extent = r_Window.getWindowExtent();
		while (extent[0] == 0 || extent[1] == 0) {
			extent = r_Window.getWindowExtent();
			glfwWaitEvents();
		}
		vkDeviceWaitIdle(m_Device.getDevice());


		m_SwapChain.recreate(extent);
	}

	void Renderer::beginFrame() {
		if (m_IsFrameStarted) SPYDER_CORE_WARN("Cannot begin frame if it is already in progress!");

		auto result = m_SwapChain.acquireNextImage(&m_CurrentImageIndex);

		while (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			result = m_SwapChain.acquireNextImage(&m_CurrentImageIndex);
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			SPYDER_CORE_ERROR("Failed to acquire next runtime image!");
		}

		m_IsFrameStarted = true;
		auto commandBuffer = m_CommandBuffers[m_CurrentFrameIndex];
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		VK_CHECK(vkBeginCommandBuffer(commandBuffer, &beginInfo));
	}

	void Renderer::endFrame() {
		if (!m_IsFrameStarted) SPYDER_CORE_WARN("Cannot end frame if it never started!");

		auto commandBuffer = m_CommandBuffers[m_CurrentFrameIndex];

		VK_CHECK(vkEndCommandBuffer(commandBuffer));

		auto result = m_SwapChain.submitCommandBuffers(&commandBuffer, &m_CurrentImageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || r_Window.wasWindowResized()) {
			r_Window.resetWindowResizedFlag();
			recreateSwapChain();
		} else if (result != VK_SUCCESS) {
			SPYDER_CORE_ERROR("failed to present swap chain image");
		}

		m_IsFrameStarted = false;
		m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void Renderer::beginSwapChainRenderPass() {
		if (!m_IsFrameStarted) SPYDER_CORE_WARN("Cannot begin swapchain render pass whilst in progress!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_SwapChain.getRenderPass();
		renderPassInfo.framebuffer = m_SwapChain.getFrameBuffer(m_CurrentImageIndex);

		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = m_SwapChain.getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};

		glm::vec3 color = r_Window.getBackgroundColor();
		VkClearColorValue background{color[0], color[1], color[2], 1.0f};
		clearValues[0].color = background;
		clearValues[1].depthStencil = {1.0f, 0};

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(m_CommandBuffers[m_CurrentFrameIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_SwapChain.getSwapChainExtent().width);
		viewport.height = static_cast<float>(m_SwapChain.getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{{0, 0}, m_SwapChain.getSwapChainExtent()};
		vkCmdSetViewport(m_CommandBuffers[m_CurrentFrameIndex], 0, 1, &viewport);
		vkCmdSetScissor(m_CommandBuffers[m_CurrentFrameIndex], 0, 1, &scissor);
	}

	void Renderer::endSwapChainRenderPass() {
		if (!m_IsFrameStarted) SPYDER_CORE_WARN("Cannot end swapchain render pass whilst not in progress!");
		vkCmdEndRenderPass(m_CommandBuffers[m_CurrentFrameIndex]);
	}

	void Renderer::createDescriptors() {
		SPYDER_CORE_TRACE("Creating descriptors");
		p_GlobalUBOPool = DescriptorPool::Builder(m_Device).setMaxSets(MAX_FRAMES_IN_FLIGHT).addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_FRAMES_IN_FLIGHT).build();

		for (auto &uboBuffer : p_GlobalUBOBuffers) {
			uboBuffer = std::make_unique<Buffer>(m_Device, m_MemoryManager);
			uboBuffer->createBuffer(sizeof(UBO), 1, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
			uboBuffer->map();
		}

		p_GlobalUBODescriptorSetLayout = DescriptorSetLayout::Builder(m_Device).addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS).build();

		for (int i = 0; i < p_GlobalUBODescriptorSets.size(); ++i) {
			auto bufferInfo = p_GlobalUBOBuffers[i]->descriptorInfo();
			DescriptorWriter(*p_GlobalUBODescriptorSetLayout, *p_GlobalUBOPool).writeBuffer(0, &bufferInfo).build(p_GlobalUBODescriptorSets[i]);
		}
	}

	void Renderer::deleteDescriptors() {
		SPYDER_CORE_TRACE("Destroying descriptors");
		for (auto &uboBuffer : p_GlobalUBOBuffers) {
			uboBuffer->cleanup();
		}

		p_GlobalUBODescriptorSetLayout->cleanup();
		p_GlobalUBOPool->cleanup();
	}

	void Renderer::render(GameObject::map &gameObjects) {
		beginFrame();
		FrameInfo frameInfo{m_CurrentFrameIndex, 0.1f, m_CommandBuffers[m_CurrentFrameIndex], p_GlobalUBODescriptorSets[m_CurrentFrameIndex], gameObjects};
		m_MemoryManager.setCurrentIndex(m_CurrentFrameIndex);
		m_MemoryManager.flush();
		m_CommandBufferFunctionQueue.flushForwards(frameInfo.commandBuffer);
		// update stuff

		beginSwapChainRenderPass();
		// render system to draw the stuff

		m_MeshRenderer.render(frameInfo);
		m_GUI.render(frameInfo);

		endSwapChainRenderPass();
		endFrame();
	}

} // Vulkan