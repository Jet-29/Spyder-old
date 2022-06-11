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
		m_Window.getEventHandler().checkEvents();
		m_Renderer.render(m_GameObjects);
	}

	GameObject Engine::createGameObject() {
		return GameObject::createGameObject();
	}

	void Engine::addToDrawList(GameObject &obj) {
		m_GameObjects.emplace(obj.getId(), std::move(obj));
	}

	Engine::~Engine() {
		if (!m_closed) {
			SPYDER_CORE_WARN("Closing engine without calling close()");
		}
	}

	void Engine::close() {
		SPYDER_CORE_INFO("Closing engine...");
		m_closed = true;
		m_Renderer.cleanup();
		m_Window.cleanup();
	}

} // Spyder