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
		float getDeltaTime();
		void close();

		bool shouldClose() { return m_Window.shouldClose(); }

		static GameObject createGameObject();
		void addToDrawList(GameObject &obj);
		void clearDrawList();

	private:
		void updateDeltaTime();
		Window m_Window{};
		Vulkan::Renderer m_Renderer{m_Window};
		GameObject::map m_GameObjects{};
		bool m_closed = false;

		float m_DeltaTime{0};
		float m_MaxDeltaTime = 0.5f;
		std::chrono::time_point<std::chrono::steady_clock> m_LastTime{};
	};
} // Spyder