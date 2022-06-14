#pragma once

#include "Device.h"
#include "MemoryManagement.h"

#include <glm/glm.hpp>
#include <memory>

namespace Spyder::Vulkan {

	class SwapChain {
	public:
		SwapChain(Device &device, Surface &surface, MemoryManagement &memManager);
		SwapChain(Device &device, Surface &surface, MemoryManagement &memManager, std::shared_ptr<SwapChain> previous);

		~SwapChain() = default;

		SwapChain(const SwapChain &) = delete;
		SwapChain &operator=(const SwapChain &) = delete;

		void init(glm::vec2 windowSize);
		void recreate(glm::vec2 windowSize);
		void cleanup();

		VkFramebuffer getFrameBuffer(uint32_t index) { return m_SwapChainFramebuffers[index]; }

		VkRenderPass getRenderPass() { return m_RenderPass; }

		VkImageView getImageView(uint32_t index) { return m_SwapChainImageViews[index]; }

		size_t imageCount() { return m_SwapChainImages.size(); }

		VkFormat getSwapChainImageFormat() { return m_SwapChainImageFormat; }

		VkExtent2D getSwapChainExtent() { return m_SwapChainExtent; }

		[[nodiscard]] uint32_t width() const { return m_SwapChainExtent.width; }

		[[nodiscard]] uint32_t height() const { return m_SwapChainExtent.height; }

		VkFormat findDepthFormat();
		VkResult acquireNextImage(uint32_t *imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer *buffers, const uint32_t *imageIndex);
		[[nodiscard]] bool compareSwapFormats(const SwapChain &swapChain) const;

	private:
		void createSwapChain();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkFormat m_SwapChainImageFormat{};
		VkFormat m_SwapChainDepthFormat{};
		VkExtent2D m_SwapChainExtent{};

		std::vector<VkFramebuffer> m_SwapChainFramebuffers{};
		VkRenderPass m_RenderPass{};

		std::vector<VkImage> m_DepthImages{};
		std::vector<VmaAllocation> m_DepthImageMemories{};
		std::vector<VkImageView> m_DepthImageViews{};
		std::vector<VkImage> m_SwapChainImages{};
		std::vector<VkImageView> m_SwapChainImageViews{};

		Device &r_Device;
		Surface &r_Surface;
		MemoryManagement &r_MemoryManager;
		glm::vec2 m_WindowSize{};
		VkExtent2D m_WindowExtent{};

		VkSwapchainKHR swapChain{};
		std::shared_ptr<SwapChain> oldSwapChain{};

		std::vector<VkSemaphore> imageAvailableSemaphores{};
		std::vector<VkSemaphore> renderFinishedSemaphores{};
		std::vector<VkFence> inFlightFences{};
		std::vector<VkFence> imagesInFlight{};
		size_t currentFrame = 0;
	};

} // Vulkan