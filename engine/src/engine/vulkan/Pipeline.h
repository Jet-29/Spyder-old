#pragma once

#include "Device.h"

namespace Spyder::Vulkan {

		class Pipeline {
		public:
			Pipeline(Device &device);
			~Pipeline() = default;

			Pipeline(const Pipeline &) = delete;
			Pipeline &operator=(const Pipeline &) = delete;

			void init(const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo);

			void bind(VkCommandBuffer commandBuffer);
			static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

		private:
			void createGraphicsPipeline(const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo);
			void createShaderModule(const std::vector<uint32_t> &code, VkShaderModule *shaderModule);

			Device &r_Device;
			VkPipeline m_GraphicsPipeline{};
			VkShaderModule m_VertShaderModule{};
			VkShaderModule m_FragShaderModule{};
		};

	} // Vulkan