#include "Renderer.h"

namespace Spyder::Vulkan {
	Renderer::Renderer(Window &window) : r_Window{window} {}

	void Renderer::init() {
		SPYDER_CORE_TRACE("Initializing vulkan renderer...");
		m_Instance.init();
		m_Surface.init();
		m_Device.init();
		m_CommandPool.init();
		m_SwapChain.init(r_Window.getWindowExtent());
		createCommandBuffers();
		SPYDER_CORE_TRACE("Vulkan render initialized");
	}

	void Renderer::createCommandBuffers() {
		m_CommandBuffers.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

		VK_CHECK(vkAllocateCommandBuffers(m_Device.getDevice(), &allocInfo, m_CommandBuffers.data()));
	}

	void Renderer::freeCommandBuffers() {
		vkFreeCommandBuffers(m_Device.getDevice(), m_CommandPool.getCommandPool(), static_cast<uint32_t>(m_CommandBuffers.size()), m_CommandBuffers.data());
		m_CommandBuffers.clear();
	}

	void Renderer::recreateSwapChain() {
		auto extent = r_Window.getWindowExtent();
		while (extent[0] == 0 || extent[1] == 0) {
			extent = r_Window.getWindowExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_Device.getDevice());

		m_SwapChain.cleanup();
		m_SwapChain.init(extent);
	}

	void Renderer::beginFrame() {
		if (m_IsFrameStarted) SPYDER_CORE_WARN("Cannot begin frame if it is already in progress!");

		auto result = m_SwapChain.acquireNextImage(&m_CurrentImageIndex);

		while (result == VK_ERROR_OUT_OF_DATE_KHR) {
			result = m_SwapChain.acquireNextImage(&m_CurrentImageIndex);
			recreateSwapChain();
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
		m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;
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

	void Renderer::render() {
		beginFrame();
		// setup frame info

		// update stuff

		beginSwapChainRenderPass();
		// render system to draw the stuff

		endSwapChainRenderPass();
		endFrame();
	}
} // Vulkan