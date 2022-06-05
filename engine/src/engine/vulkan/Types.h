#pragma once

#include <vulkan/vulkan.hpp>

namespace Spyder::Vulkan {
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct QueueFamilyIndices {
		uint32_t graphicsFamily{};
		uint32_t presentFamily{};
		bool graphicsFamilyHasValue = false;
		bool presentFamilyHasValue = false;

		[[nodiscard]] bool isComplete() const { return graphicsFamilyHasValue && presentFamilyHasValue; }
	};
}