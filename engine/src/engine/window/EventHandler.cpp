#include "EventHandler.h"

namespace Spyder {
	EventHandler::EventHandler() {

	}

	void EventHandler::init(GLFWwindow *window) {
		glfwSetKeyCallback(window, keyCallback);
	}

	void EventHandler::checkEvents() {
		glfwPollEvents();
	}

	void EventHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	}

	void EventHandler::mousePosCallback(GLFWwindow *window, double xPos, double yPos) {

	}
} // Spyder