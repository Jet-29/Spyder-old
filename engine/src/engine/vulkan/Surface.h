#pragma once

#include <vulkan/vulkan.hpp>
#include "engine/window/Window.h"
#include "engine/vulkan/Instance.h"

namespace Spyder::Vulkan {

	class Surface {
	public:
		Surface(Instance &instance, Window &window);
		~Surface() = default;

		Surface(const Surface &) = delete;
		Surface &operator=(const Surface &) = delete;

		void init();
		void cleanup();

		VkSurfaceKHR getSurface() { return m_Surface; }

	private:
		Instance &r_Instance;
		Window &r_Window;
		VkSurfaceKHR m_Surface{};

	};

} // Vulkan