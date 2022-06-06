#include "DescriptorWriter.h"

namespace Spyder::Vulkan {
	DescriptorWriter::DescriptorWriter(DescriptorSetLayout &setLayout, DescriptorPool &pool) : r_SetLayout{setLayout}, r_Pool{pool} {}

	DescriptorWriter &DescriptorWriter::writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo) {
		if (r_SetLayout.m_Bindings.count(binding) != 1)
			SPYDER_CORE_ERROR("Layer does not contain specified binding {}", binding);

		auto &bindingDescription = r_SetLayout.m_Bindings[binding];

		if(bindingDescription.descriptorCount != 1)
			SPYDER_CORE_ERROR("Binding single descriptor info, but binding expects multiple, {}", binding);

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pBufferInfo = bufferInfo;
		write.descriptorCount = 1;

		m_Writes.push_back(write);
		return *this;
	}

	DescriptorWriter &DescriptorWriter::writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo) {
		if (r_SetLayout.m_Bindings.count(binding) != 1)
			SPYDER_CORE_ERROR("Layer does not contain specified binding {}", binding);

		auto &bindingDescription = r_SetLayout.m_Bindings[binding];

		if(bindingDescription.descriptorCount != 1)
			SPYDER_CORE_ERROR("Binding single descriptor info, but binding expects multiple, {}", binding);

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pImageInfo = imageInfo;
		write.descriptorCount = 1;

		m_Writes.push_back(write);
		return *this;
	}

	bool DescriptorWriter::build(VkDescriptorSet &set) {
		bool success = r_Pool.allocateDescriptor(r_SetLayout.getDescriptorSetLayout(), set);
		if (!success) {
			SPYDER_CORE_WARN("Failed to build descriptor");
			return false;
		}
		overwrite(set);
		return true;
	}

	void DescriptorWriter::overwrite(VkDescriptorSet &set) {
		for (auto &write : m_Writes) {
			write.dstSet = set;
		}
		vkUpdateDescriptorSets(r_Pool.r_Device.getDevice(), m_Writes.size(), m_Writes.data(), 0, nullptr);
	}
} // Vulkan