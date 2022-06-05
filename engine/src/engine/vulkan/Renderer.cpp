#include "Renderer.h"

namespace Spyder::Vulkan {
	Renderer::Renderer(Window &window) : r_Window{window} {}

	void Renderer::init() {
		SPYDER_CORE_TRACE("Initializing vulkan renderer...");
		m_Instance.init();
		m_Surface.init();
		m_Device.init();
		SPYDER_CORE_TRACE("Vulkan render initialized");
	}
} // Vulkan