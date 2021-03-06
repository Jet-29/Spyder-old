#include "Window.h"

namespace Spyder {
	void Window::init(int w, int h, const char *t) {
		if (m_Window) {
			SPYDER_CORE_WARN("Window already exists!");
			return;
		}
		m_WindowSize = {w, h};
		title = t;

		SPYDER_CORE_TRACE("Initializing GLFW window...");
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

		m_Window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, frameBufferResizedCallback);

		m_EventHandler.init(m_Window);

		SPYDER_CORE_TRACE("GLFW initialization complete");
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_Window);
	}

	const glm::vec2 &Window::getWindowExtent() const {
		return m_WindowSize;
	}

	bool Window::wasWindowResized() const {
		return m_FrameBufferResized;
	}

	GLFWwindow *Window::getWindow() {
		return m_Window;
	}

	glm::vec3 &Window::getBackgroundColor() {
		return m_BackgroundColor;
	}

	void Window::resetWindowResizedFlag() {
		m_FrameBufferResized = false;
	}

	void Window::setBackground(glm::vec3 newColor) {
		m_BackgroundColor = newColor;
	}

	void Window::frameBufferResizedCallback(GLFWwindow *openWindow, int width, int height) {
		auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(openWindow));
		if (window->m_FrameBufferResized) return;
		SPYDER_CORE_TRACE("Window was resized!");
		window->m_FrameBufferResized = true;
		window->m_WindowSize = {width, height};
	}

	void Window::lockMouse() {
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::unlockMouse() {
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	EventHandler &Window::getEventHandler() {
		return m_EventHandler;
	}

	void Window::cleanup() {
		glfwTerminate();
	}
} // Spyder