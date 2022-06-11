#include "framework/Framework.h"

int main() {
	Framework framework{800, 800, "Spyder"};
	framework.runGameLoop();
	SPYDER_TRACE("Application finished successfully");
	return 0;
}