#include "Pipeline.h"

namespace Spyder::Vulkan {
	Pipeline::Pipeline(Device &device) : r_Device{device} {}

	void Pipeline::init(const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo) {
		SPYDER_CORE_TRACE("Initializing pipeline...");
		createGraphicsPipeline(vertShaderArray, fragShaderArray, configInfo);
	}

	void Pipeline::bind(VkCommandBuffer commandBuffer) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
	}

	void Pipeline::defaultPipelineConfigInfo(PipelineConfigInfo &configInfo) {
		SPYDER_CORE_TRACE("Creating default pipeline config");
		configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		configInfo.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

		configInfo.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		configInfo.viewportInfo.viewportCount = 1;
		configInfo.viewportInfo.pViewports = nullptr;
		configInfo.viewportInfo.scissorCount = 1;
		configInfo.viewportInfo.pScissors = nullptr;

		configInfo.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		configInfo.rasterizationInfo.depthClampEnable = VK_FALSE;
		configInfo.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
		configInfo.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
		configInfo.rasterizationInfo.lineWidth = 1.0f;
		configInfo.rasterizationInfo.cullMode = VK_CULL_MODE_NONE;
		configInfo.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		configInfo.rasterizationInfo.depthBiasEnable = VK_FALSE;
		configInfo.rasterizationInfo.depthBiasConstantFactor = 0.0f;
		configInfo.rasterizationInfo.depthBiasClamp = 0.0f;
		configInfo.rasterizationInfo.depthBiasSlopeFactor = 0.0f;

		configInfo.multiSampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		configInfo.multiSampleInfo.sampleShadingEnable = VK_FALSE;
		configInfo.multiSampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		configInfo.multiSampleInfo.minSampleShading = 1.0f;
		configInfo.multiSampleInfo.pSampleMask = nullptr;
		configInfo.multiSampleInfo.alphaToCoverageEnable = VK_FALSE;
		configInfo.multiSampleInfo.alphaToOneEnable = VK_FALSE;

		configInfo.colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		configInfo.colorBlendAttachment.blendEnable = VK_TRUE;
		configInfo.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		configInfo.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		configInfo.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		configInfo.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		configInfo.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		configInfo.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		configInfo.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		configInfo.colorBlendInfo.logicOpEnable = VK_FALSE;
		configInfo.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
		configInfo.colorBlendInfo.attachmentCount = 1;
		configInfo.colorBlendInfo.pAttachments = &configInfo.colorBlendAttachment;
		configInfo.colorBlendInfo.blendConstants[0] = 0.0f;
		configInfo.colorBlendInfo.blendConstants[1] = 0.0f;
		configInfo.colorBlendInfo.blendConstants[2] = 0.0f;
		configInfo.colorBlendInfo.blendConstants[3] = 0.0f;

		configInfo.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		configInfo.depthStencilInfo.depthTestEnable = VK_TRUE;
		configInfo.depthStencilInfo.depthWriteEnable = VK_TRUE;
		configInfo.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		configInfo.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		configInfo.depthStencilInfo.minDepthBounds = 0.0f;
		configInfo.depthStencilInfo.maxDepthBounds = 1.0f;
		configInfo.depthStencilInfo.stencilTestEnable = VK_FALSE;
		configInfo.depthStencilInfo.front = {};
		configInfo.depthStencilInfo.back = {};

		configInfo.dynamicsStateEnables = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
		configInfo.dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		configInfo.dynamicStateInfo.pDynamicStates = configInfo.dynamicsStateEnables.data();
		configInfo.dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(configInfo.dynamicsStateEnables.size());
		configInfo.dynamicStateInfo.flags = 0;

		auto vertexBinding = Vertex::getBindingDescriptions();
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		for (int i = 0; i < bindingDescriptions.size(); i++) {
			bindingDescriptions[i].binding = vertexBinding[i].binding;
			bindingDescriptions[i].stride = vertexBinding[i].stride;
			bindingDescriptions[i].inputRate = static_cast<VkVertexInputRate>(vertexBinding[i].inputRate);
		}

		auto vertexAttributes = Vertex::getAttributeDescriptions();
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		for (auto &vertexAttribute : vertexAttributes) {
			attributeDescriptions.push_back({vertexAttribute.location, vertexAttribute.binding, static_cast<VkFormat>(vertexAttribute.format), vertexAttribute.offset});
		}

		configInfo.bindingDescriptions = bindingDescriptions;
		configInfo.attributeDescriptions = attributeDescriptions;
	}

	void Pipeline::createGraphicsPipeline(const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo) {
		SPYDER_CORE_TRACE("Creating pipeline...");
		if (configInfo.pipelineLayout == VK_NULL_HANDLE) SPYDER_CORE_ERROR("Cannot create graphics pipeline, no pipeline layout provided");
		if (configInfo.renderPass == VK_NULL_HANDLE) SPYDER_CORE_ERROR("Cannot create graphics pipeline, no pipeline renderPass provided");

		createShaderModule(vertShaderArray, &m_VertShaderModule);
		createShaderModule(fragShaderArray, &m_FragShaderModule);

		VkPipelineShaderStageCreateInfo shaderStages[2]{};
		shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStages[0].module = m_VertShaderModule;
		shaderStages[0].pName = "main";
		shaderStages[0].flags = 0;
		shaderStages[0].pNext = nullptr;
		shaderStages[0].pSpecializationInfo = nullptr;

		shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStages[1].module = m_FragShaderModule;
		shaderStages[1].pName = "main";
		shaderStages[1].flags = 0;
		shaderStages[1].pNext = nullptr;
		shaderStages[1].pSpecializationInfo = nullptr;

		auto &bindingDescriptions = configInfo.bindingDescriptions;
		auto &attributeDescriptions = configInfo.attributeDescriptions;
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
		pipelineInfo.pViewportState = &configInfo.viewportInfo;
		pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
		pipelineInfo.pMultisampleState = &configInfo.multiSampleInfo;
		pipelineInfo.pColorBlendState = &configInfo.colorBlendInfo;
		pipelineInfo.pDepthStencilState = &configInfo.depthStencilInfo;
		pipelineInfo.pDynamicState = &configInfo.dynamicStateInfo;

		pipelineInfo.layout = configInfo.pipelineLayout;
		pipelineInfo.renderPass = configInfo.renderPass;
		pipelineInfo.subpass = configInfo.subPass;

		pipelineInfo.basePipelineIndex = -1;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		VK_CHECK(vkCreateGraphicsPipelines(r_Device.getDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline));
	}

	void Pipeline::createShaderModule(const std::vector<uint32_t> &code, VkShaderModule *shaderModule) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size() * 4;
		createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

		VK_CHECK(vkCreateShaderModule(r_Device.getDevice(), &createInfo, nullptr, shaderModule));
	}

	void Pipeline::cleanup() {
		SPYDER_CORE_TRACE("Pipeline cleanup");
		vkDestroyShaderModule(r_Device.getDevice(), m_VertShaderModule, nullptr);
		vkDestroyShaderModule(r_Device.getDevice(), m_FragShaderModule, nullptr);
		vkDestroyPipeline(r_Device.getDevice(), m_GraphicsPipeline, nullptr);
	}
} // Vulkan