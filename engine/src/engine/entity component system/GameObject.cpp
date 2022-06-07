#include "GameObject.h"

namespace Spyder {
	GameObject::GameObject(GameObject::id_t id) : m_id{id} {}

	GameObject GameObject::createGameObject() {
		static id_t currentId = 0;
		return GameObject{currentId++};
	}

	GameObject::id_t GameObject::getId() const {
		return m_id;
	}
} // Spyder