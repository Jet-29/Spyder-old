#pragma once

#include "engine/core/Base.h"
#include "engine/window/Window.h"
#include "engine/vulkan/Renderer.h"

namespace Spyder {
	class Engine {
	public:
		Engine();
		~Engine();
		Engine(const Engine &) = delete;
		Engine &operator=(const Engine &) = delete;

		void init();
		void display();
		void close();

		bool shouldClose() { return m_Window.shouldClose(); }

		static GameObject createGameObject();
		void addToDrawList(GameObject &obj);

	private:
		Window m_Window{};
		Vulkan::Renderer m_Renderer{m_Window};
		GameObject::map m_GameObjects{};
		bool m_closed = false;
	};
} // Spyder