#include "DescriptorPool.h"

namespace Spyder::Vulkan {
	DescriptorPool::Builder::Builder(Device &device) : r_Device{device} {}

	DescriptorPool::Builder &DescriptorPool::Builder::addPoolSize(VkDescriptorType descriptorType, uint32_t count) {
		SPYDER_CORE_TRACE("Adding pool with size {}", count);
		poolSizes.push_back({descriptorType, count});
		return *this;
	}

	DescriptorPool::Builder &DescriptorPool::Builder::setPoolFlags(VkDescriptorPoolCreateFlags flags) {
		SPYDER_CORE_TRACE("Setting pool flags to {}", flags);
		poolFlags = flags;
		return *this;
	}

	DescriptorPool::Builder &DescriptorPool::Builder::setMaxSets(uint32_t count) {
		SPYDER_CORE_TRACE("Setting max size to {}", count);
		maxSets = count;
		return *this;
	}

	std::unique_ptr<DescriptorPool> DescriptorPool::Builder::build() const {
		SPYDER_CORE_TRACE("Building pool with maxSets {0}, flags {1}", maxSets, poolFlags);
		return std::make_unique<DescriptorPool>(r_Device, maxSets, poolFlags, poolSizes);
	}

	DescriptorPool::DescriptorPool(Device &device, uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize> &poolSizes) : r_Device{device} {
		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		descriptorPoolInfo.pPoolSizes = poolSizes.data();
		descriptorPoolInfo.maxSets = maxSets;
		descriptorPoolInfo.flags = poolFlags;

		VK_CHECK(vkCreateDescriptorPool(r_Device.getDevice(), &descriptorPoolInfo, nullptr, &m_DescriptorPool));
	}

	DescriptorPool::~DescriptorPool() {
		vkDestroyDescriptorPool(r_Device.getDevice(), m_DescriptorPool, nullptr);
	}

	bool DescriptorPool::allocateDescriptor(const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const {
		SPYDER_CORE_TRACE("Allocating descriptor...");
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.pSetLayouts = &descriptorSetLayout;
		allocInfo.descriptorSetCount = 1;

		if (vkAllocateDescriptorSets(r_Device.getDevice(), &allocInfo, &descriptor) != VK_SUCCESS) {
			SPYDER_CORE_WARN("Failed to allocate descriptor sets");
			return false;
		}
		return true;
	}

	void DescriptorPool::freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const {
		SPYDER_CORE_TRACE("Freeing descriptor...");
		vkFreeDescriptorSets(r_Device.getDevice(), m_DescriptorPool, static_cast<uint32_t>(descriptors.size()), descriptors.data());
	}

	void DescriptorPool::resetPool() {
		SPYDER_CORE_TRACE("Resetting descriptor...");
		vkResetDescriptorPool(r_Device.getDevice(), m_DescriptorPool, 0);
	}
} // Vulkan