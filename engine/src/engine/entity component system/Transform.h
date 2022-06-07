#pragma once

#include <glm/glm.hpp>

namespace Spyder {

	class Transform {
		glm::vec3 translation{0.0f, 0.0f, 0.0f};
		glm::vec3 scale{1.0f, 1.0f, 1.0f};
		glm::vec3 rotation{0.0f, 0.0f, 0.0f};

		glm::mat4 mat4();
	};

} // Spyder