#include "Engine.h"

namespace Spyder {
	Engine::Engine() {
		Log::Init();
	}

	void Engine::init() {
		SPYDER_CORE_INFO("Initializing the engine...");
		m_Window.init(1280, 720, "Spyder Graphics Engine");
		m_Renderer.init();
		SPYDER_CORE_INFO("Engine initialized");
	}

	void Engine::display() {
		updateDeltaTime();
		m_Window.getEventHandler().checkEvents();
		m_Renderer.render(m_GameObjects, getDeltaTime());
	}

	GameObject Engine::createGameObject() {
		SPYDER_CORE_TRACE("Creating game object...");
		return GameObject::createGameObject();
	}

	void Engine::addToDrawList(GameObject &obj) {
		SPYDER_CORE_TRACE("Adding game object to draw list...");
		m_GameObjects.emplace(obj.getId(), std::move(obj));
	}

	Engine::~Engine() {
		if (!m_closed) {
			SPYDER_CORE_WARN("Closing engine without calling close()");
			close();
		}
	}

	void Engine::close() {
		SPYDER_CORE_INFO("Closing engine...");
		m_closed = true;
		m_Renderer.cleanup();
		m_Window.cleanup();
		SPYDER_CORE_TRACE("Engine cleanup successful");
	}

	void Engine::clearDrawList() {
		m_GameObjects.clear();
	}

	float Engine::getDeltaTime() {
	return m_DeltaTime;
	}

	void Engine::updateDeltaTime() {
		auto newTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - m_LastTime).count();
		m_DeltaTime = deltaTime;
		m_LastTime = newTime;
		if (m_MaxDeltaTime != 0) {
			m_DeltaTime = std::min(m_DeltaTime, m_MaxDeltaTime);
		}
	}

} // Spyder