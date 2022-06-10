#include "Batch.h"

namespace Spyder::Vulkan {
	Batch::Batch(Device &device, MemoryManagement memManager) : r_Device{device}, r_MemoryManager{memManager} {}

	void Batch::init(uint32_t size) {
		m_Buffer.createBuffer(size, );
	}
} // Vulkan