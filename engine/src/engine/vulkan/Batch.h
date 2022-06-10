#pragma once

#include "MemoryManagement.h"

namespace Spyder::Vulkan {

	class Batch {
	public:
		Batch(Device &device, MemoryManagement memManager);

		void init(uint32_t size = 1 << 10);

	private:
		Device &r_Device;
		MemoryManagement &r_MemoryManager;
		Buffer m_Buffer{r_Device, r_MemoryManager};
	};

} // Vulkan