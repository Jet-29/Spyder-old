#pragma once

#include "engine/vulkan/Device.h"

namespace Spyder::Vulkan {
	class DescriptorPool {
	public:
		class Builder {
		public:
			Builder(Device &device);

			Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);
			Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);
			Builder &setMaxSets(uint32_t count);
			[[nodiscard]] std::unique_ptr<DescriptorPool> build() const;

		private:
			Device &r_Device;
			std::vector<VkDescriptorPoolSize> poolSizes{};
			uint32_t maxSets = 1000;
			VkDescriptorPoolCreateFlags poolFlags = 0;
		};

		DescriptorPool(Device &device, uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize> &poolSizes);
		~DescriptorPool() = default;

		DescriptorPool(const DescriptorPool &) = delete;
		DescriptorPool &operator=(const DescriptorPool &) = delete;

		void cleanup();
		bool allocateDescriptor(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;
		void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;
		void resetPool();

	private:
		Device &r_Device;
		VkDescriptorPool m_DescriptorPool{};

		friend class DescriptorWriter;
	};

} // Vulkan