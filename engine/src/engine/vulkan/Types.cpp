#include "engine/vulkan/Types.h"
#include <ranges>

namespace Spyder::Vulkan {
	void CommandBufferFunctionQueue::pushFunction(std::function<void(VkCommandBuffer commandBuffer)> &&function) {
		functions.push_back(function);
	}

	void CommandBufferFunctionQueue::flushForwards(VkCommandBuffer commandBuffer) {
		for (auto &function : functions) {
			function(commandBuffer);
		}
		functions.clear();
	}

	void CommandBufferFunctionQueue::flushBackwards(VkCommandBuffer commandBuffer) {
		for (auto &function : std::ranges::reverse_view(functions)) {
			function(commandBuffer);
		}
		functions.clear();
	}
}