#pragma once

#include "Instance.h"
#include "Device.h"
#include "SwapChain.h"

namespace Spyder::Vulkan {

	class Renderer {
	public:
		Renderer(Window &window);
		~Renderer() = default;

		Renderer(const Renderer &) = delete;
		Renderer &operator=(const Renderer &) = delete;

		void init();

	private:
		Window &r_Window;
		Instance m_Instance{};
		Surface m_Surface{m_Instance, r_Window};
		Device m_Device{m_Instance, m_Surface};
	};

} // Vulkan