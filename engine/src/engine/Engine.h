#pragma once

#include "engine/core/Base.h"
#include "engine/core/Window.h"
#include "engine/vulkan/Renderer.h"

namespace Spyder {
	class Engine {
	public:
		Engine() = default;
		~Engine() = default;
		Engine(const Engine &) = delete;
		Engine &operator=(const Engine &) = delete;

		void init();
		void display();

	private:
		Window m_Window{};
		Vulkan::Renderer m_Renderer{m_Window};
	};
} // Spyder