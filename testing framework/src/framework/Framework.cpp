#include "Framework.h"

Framework::Framework(int width, int height, const char *title) {
	engine.init();
}

void Framework::runGameLoop() {
	while (!engine.shouldClose()) {
		engine.display();
	}
}
