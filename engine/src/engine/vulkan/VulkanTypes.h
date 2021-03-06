#pragma once

#include "engine/entity component system/GameObject.h"
#include "VulkanBase.h"

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

	struct FrameInfo {
		uint32_t frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		// todo:: add camera
		VkDescriptorSet descriptorSet;
		GameObject::map &gameObjects;
		uint32_t triangleCount = 0;
	};

	struct PushConstantData {
		glm::mat4 modelMatrix{1.0f};
		glm::mat4 AdditionalMatrix{1.0f};
	};

	struct UBO {
		glm::mat4 projection{1.0f};
		glm::mat4 view{1.0f};
	};

	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo &) = delete;
		PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

		std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		VkPipelineViewportStateCreateInfo viewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo multiSampleInfo{};
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
		std::vector<VkDynamicState> dynamicsStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subPass = 0;
	};

	struct CommandBufferFunctionQueue {
		void pushFunction(std::function<void(VkCommandBuffer commandBuffer)> &&function);
		void flushForwards(VkCommandBuffer commandBuffer);
		void flushBackwards(VkCommandBuffer commandBuffer);

	private:
		std::deque<std::function<void(VkCommandBuffer commandBuffer)>> functions;
	};
}