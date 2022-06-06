#include "Framework.h"

Framework::Framework(int width, int height, const char *title) {
	engine.init();
}

void Framework::runGameLoop() {
	for (int i = 0; i < 10000; ++i) {
		engine.display();
	}
}
