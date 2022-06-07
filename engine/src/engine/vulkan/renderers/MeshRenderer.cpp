#include "MeshRenderer.h"
#include "engine/shaders/Shaders.h"

namespace Spyder::Vulkan {
	MeshRenderer::MeshRenderer(Device &device, ShaderCache &shaderCache) : r_Device{device}, r_ShaderCache{shaderCache} {}

	void MeshRenderer::init(VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout) {
		createPipelineLayout(descriptorSetLayout);
		createPipeline(renderPass);
	}

	void MeshRenderer::render(FrameInfo &frameInfo) {
		m_Pipeline.bind(frameInfo.commandBuffer);
		vkCmdBindDescriptorSets(frameInfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 1, &frameInfo.DescriptorSet, 0, nullptr);
		vkCmdDraw(frameInfo.commandBuffer, 3, 1, 0, 0);

//		for (auto &kv : frameInfo.gameObjects) {
//			auto &obj = kv.second;
//			if (obj.m_Mesh.getUniqueVertices().size() == 0) continue;
//			PushConstantData push{};
//			push.modelMatrix = obj.m_Transform.mat4();
//
//			vkCmdPushConstants(frameInfo.commandBuffer, m_PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantData), &push);
//
//			obj.m_Mesh->bind(frameInfo.commandBuffer);
//			obj.m_Mesh->draw(frameInfo.commandBuffer);
//		}
	}

	void MeshRenderer::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PushConstantData);

		std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

		VK_CHECK(vkCreatePipelineLayout(r_Device.getDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout));
	}

	void MeshRenderer::createPipeline(VkRenderPass renderPass) {
		if (m_PipelineLayout == nullptr) SPYDER_CORE_ERROR("Cannot create pipeline before pipeline layout");
		PipelineConfigInfo pipelineConfig{};
		Pipeline::defaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = m_PipelineLayout;

		auto vertShader = r_ShaderCache.getShader(Shaders::VertexMeshShader, "Mesh Vertex Shader", shaderc_vertex_shader);
		auto fragShader = r_ShaderCache.getShader(Shaders::FragmentMeshShader, "Mesh Fragment Shader", shaderc_fragment_shader);

		m_Pipeline.init(vertShader, fragShader, pipelineConfig);
	}
} // Vulkan