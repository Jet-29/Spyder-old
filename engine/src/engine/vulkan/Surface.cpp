#include "Surface.h"

namespace Spyder::Vulkan {
	Surface::Surface(Instance &instance, Window &window) : r_Instance{instance}, r_Window{window} {}

	void Surface::init() {
		SPYDER_CORE_TRACE("Creating surface...");
		VK_CHECK(glfwCreateWindowSurface(r_Instance.getInstance(), r_Window.getWindow(), nullptr, &m_Surface));
		SPYDER_CORE_TRACE("Surface created");
	}
} // Vulkan