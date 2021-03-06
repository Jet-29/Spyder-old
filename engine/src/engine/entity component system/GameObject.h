#pragma once

#include "Mesh.h"
#include "Transform.h"

namespace Spyder {

	class GameObject {
	public:
		GameObject(const GameObject &) = delete;
		GameObject &operator=(const GameObject) = delete;
		GameObject(GameObject &&) = default;
		GameObject &operator=(GameObject &&) = default;

		static GameObject createGameObject();
		using id_t = unsigned int;
		using map = std::unordered_map<id_t, GameObject>;

		void draw();

		[[nodiscard]] id_t getId() const;

		Transform m_Transform{};
		Mesh m_Mesh{};

	private:
		GameObject(id_t id);

		id_t m_id;
	};

} // Spyder