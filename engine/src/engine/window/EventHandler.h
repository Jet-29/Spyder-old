#pragma once

#include "engine/core/Base.h"
#include <GLFW/glfw3.h>

namespace Spyder {

	class EventHandler {
	public:
		EventHandler();

		void init(GLFWwindow *window);
		void checkEvents();

	private:
		static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void mousePosCallback(GLFWwindow *window, double xPos, double yPos);

	};

} // Spyder