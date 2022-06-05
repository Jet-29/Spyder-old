#include "Engine.h"

namespace Spyder {
	void Engine::init() {
		Log::Init();
		m_Window.init(1280, 720, "Spyder Graphics Engine");
		m_Renderer.init();
	}
} // Spyder