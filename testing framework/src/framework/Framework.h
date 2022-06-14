#pragma once

#include "engine/Engine.h"

class Framework {
public:
	Framework(int width, int height, const char *title);
	void runGameLoop();

private:
	Spyder::Engine engine{};
	float totalTime{0};
};
