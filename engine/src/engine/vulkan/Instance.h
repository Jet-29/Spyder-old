#pragma once

#include "engine/vulkan/VulkanBase.h"
#include <vulkan/vulkan.hpp>

namespace Spyder::Vulkan {

	class Instance {
	public:
#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif

		Instance() = default;
		~Instance() = default;

		Instance(const Instance &) = delete;
		Instance &operator=(const Instance &) = delete;

		void init();
		void cleanup();

		[[nodiscard]] VkInstance getInstance() { return m_Instance; }

		[[nodiscard]] uint32_t getApiVersion() const { return m_ApiVersion; }

		[[nodiscard]] std::vector<const char *> getValidationLayers() { return m_ValidationLayers; }

		const std::vector<const char *> m_ValidationLayers = {"VK_LAYER_KHRONOS_validation"};


	private:
		bool checkValidationLayerSupport();
		std::vector<const char *> getRequiredExtensions();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
		void hasGflwRequiredInstanceExtensions();

		void createInstance();
		void setupDebugMessenger();

		VkInstance m_Instance{};
		VkDebugUtilsMessengerEXT m_DebugMessenger{};

		uint32_t m_ApiVersion = VK_API_VERSION_1_3;

	};

} // Vulkan