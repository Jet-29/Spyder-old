#include "Engine.h"

namespace Spyder {
	Engine::Engine() {
		Log::Init();
	}

	void Engine::init() {
		m_Window.init(1280, 720, "Spyder Graphics Engine");
		m_Renderer.init();
	}

	void Engine::display() {
		m_Renderer.render();
	}
} // Spyder