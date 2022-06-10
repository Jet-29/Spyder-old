#pragma once

#include "engine/vulkan/Device.h"
#include "engine/vulkan/Pipeline.h"
#include "engine/shaders/ShaderCache.h"
#include "engine/vulkan/MemoryManagement.h"

namespace Spyder::Vulkan {

	class MeshRenderer {
	public:
		MeshRenderer(Device &device, MemoryManagement &memManager, ShaderCache &shaderCache);
		~MeshRenderer() = default;

		MeshRenderer(const MeshRenderer &) = delete;
		MeshRenderer &operator=(const MeshRenderer &) = delete;

		void init(VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout);
		void render(FrameInfo &frameInfo);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);

		Device &r_Device;
		MemoryManagement &r_MemoryManager;
		Pipeline m_Pipeline{r_Device};

		ShaderCache &r_ShaderCache;

		VkPipelineLayout m_PipelineLayout{};
	};

} // Vulkan