#pragma once

#include "Instance.h"
#include "Device.h"

#include "MemoryAllocator.h"

namespace Spyder::Vulkan {

		class MemoryManagement {
		public:
			MemoryManagement(Instance& instance, Device& device);
			~MemoryManagement() = default;

			MemoryManagement(const MemoryManagement &) = delete;
			MemoryManagement &operator=(const MemoryManagement &) = delete;

			void init();

		private:
			Instance &r_Instance;
			Device &r_Device;

			VmaAllocator m_Allocator;
		};

	} // Vulkan