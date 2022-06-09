#pragma once

#include "Types.h"
#include "engine/core/Window.h"
#include "Instance.h"
#include "Surface.h"

namespace Spyder::Vulkan {

	class Device {
	public:
		Device(Instance &instance, Surface &surface);
		~Device() = default;

		Device(const Device &) = delete;
		Device &operator=(const Device &) = delete;

		void init();
		void cleanup();

		VkDevice getDevice() { return m_Device; }

		VkPhysicalDevice getPhysicalDevice() { return m_PhysicalDevice; }

		VkQueue getGraphicsQueue() { return m_GraphicsQueue; }

		VkQueue getPresentQueue() { return m_PresentQueue; }

		SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(m_PhysicalDevice); }

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

		QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(m_PhysicalDevice); }

		VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
		VkPhysicalDeviceProperties m_Properties{};
	private:
		void pickPhysicalDevice();
		void createLogicalDevice();

		// helper functions
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		Instance &r_Instance;
		Surface &r_Surface;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

		VkDevice m_Device{};
		VkQueue m_GraphicsQueue{};
		VkQueue m_PresentQueue{};

		const std::vector<const char *> m_DeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	};

} // Vulkan