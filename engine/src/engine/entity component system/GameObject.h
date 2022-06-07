#pragma once

#include "Mesh.h"
#include "Transform.h"

#include <unordered_map>

namespace Spyder {

	class GameObject {
	public:
		GameObject(const GameObject &) = delete;
		GameObject &operator=(const GameObject) = delete;

		static GameObject createGameObject();
		using id_t = unsigned int;
		using map = std::unordered_map<id_t, GameObject>;

		[[nodiscard]] id_t getId() const;

		Transform m_Transform{};
		Mesh m_Mesh{};

	private:
		GameObject(id_t id);

		id_t m_id;
	};

} // Spyder