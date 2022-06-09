#pragma once

#include "engine/vulkan/Device.h"

namespace Spyder::Vulkan {

	class DescriptorSetLayout {
	public:
		class Builder {
		public:
			Builder(Device &device);

			Builder &addBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags stageFlags, uint32_t count = 1);
			[[nodiscard]] std::unique_ptr<DescriptorSetLayout> build() const;

		private:
			Device &r_Device;
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
		};

		DescriptorSetLayout(Device &device, const std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> &bindings);
		~DescriptorSetLayout();

		DescriptorSetLayout(const DescriptorSetLayout &) = delete;
		DescriptorSetLayout &operator=(const DescriptorSetLayout &) = delete;

		[[nodiscard]] VkDescriptorSetLayout getDescriptorSetLayout() const { return m_DescriptorSetLayout; }

	private:
		Device &r_Device;
		VkDescriptorSetLayout m_DescriptorSetLayout{};
		std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> m_Bindings;

		friend class DescriptorWriter;
	};

} // Vulkan