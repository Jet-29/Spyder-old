#include "Framework.h"

Framework::Framework(int width, int height, const char *title) {
	engine.init();
}

void Framework::runGameLoop() {
	Spyder::GameObject myTriangle = Spyder::Engine::createGameObject();
	myTriangle.m_Mesh.loadModel({{{-0.5f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, {{0.0f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, {{0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}});
	engine.addToDrawList(myTriangle);
	while (!engine.shouldClose()) {
		totalTime += 0.01f;
		engine.display();
	}
	engine.close();
}
