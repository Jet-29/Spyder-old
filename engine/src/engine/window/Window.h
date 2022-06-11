#pragma once

#include "engine/core/Base.h"
#include "EventHandler.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Spyder {

	class Window {
	public:
		Window() = default;
		~Window() = default;

		void init(int w, int h, const char *t);
		void cleanup();

		Window(const Window &) = delete;
		Window &operator=(const Window &) = delete;

		[[nodiscard]] bool shouldClose() const;
		[[nodiscard]] const glm::vec2 &getWindowExtent() const;
		[[nodiscard]] bool wasWindowResized() const;
		[[nodiscard]] GLFWwindow *getWindow();
		[[nodiscard]] glm::vec3 &getBackgroundColor();
		[[nodiscard]] EventHandler &getEventHandler();

		void lockMouse();
		void unlockMouse();

		[[nodiscard]] float extentAspectRatio() const {
			return static_cast<float>(m_WindowSize[0]) / static_cast<float>(m_WindowSize[1]);
		}

		void resetWindowResizedFlag();
		void setBackground(glm::vec3 newColor);

	private:
		static void frameBufferResizedCallback(GLFWwindow *openWindow, int width, int height);

		GLFWwindow *m_Window = nullptr;
		EventHandler m_EventHandler{};
		glm::vec2 m_WindowSize{};
		bool m_FrameBufferResized = false;
		glm::vec3 m_BackgroundColor{};

		const char *title{};
	};

} // Spyder