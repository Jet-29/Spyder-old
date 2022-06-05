#pragma once

#include "engine/core/Base.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Spyder {

	class Window {
	public:
		Window() = default;
		~Window() = default;

		void init(int w, int h, const char *t);

		Window(const Window &) = delete;
		Window &operator=(const Window &) = delete;

		[[nodiscard]] bool shouldClose() const;
		[[nodiscard]] const glm::vec2 &getWindowExtent() const;
		[[nodiscard]] bool wasWindowResized() const;
		[[nodiscard]] GLFWwindow *getWindow();
		[[nodiscard]] glm::vec3 &getBackgroundColor();

		void resetWindowResizedFlag();
		void setBackground(glm::vec3 newColor);

	private:
		static void frameBufferResizedCallback(GLFWwindow *openWindow, int width, int height);

		GLFWwindow *m_Window = nullptr;
		glm::vec2 m_WindowSize{};
		bool m_FrameBufferResized = false;
		glm::vec3 m_BackgroundColor{};

		const char *title{};
	};

} // Spyder