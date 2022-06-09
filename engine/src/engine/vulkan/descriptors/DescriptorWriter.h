#pragma once

#include "DescriptorPool.h"
#include "DescriptorSetLayout.h"

namespace Spyder::Vulkan {

	class DescriptorWriter {
	public:
		DescriptorWriter(DescriptorSetLayout &setLayout, DescriptorPool &pool);

		DescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);
		DescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

		bool build(VkDescriptorSet &set);
		void overwrite(VkDescriptorSet &set);

	private:
		DescriptorSetLayout &r_SetLayout;
		DescriptorPool &r_Pool;
		std::vector<VkWriteDescriptorSet> m_Writes;
	};

} // Vulkan