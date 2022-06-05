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

		m_Window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, frameBufferResizedCallback);
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
		SPYDER_CORE_TRACE("Window was resized!");
		auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(openWindow));
		window->m_FrameBufferResized = true;
		window->m_WindowSize = {width, height};
	}
} // Spyder