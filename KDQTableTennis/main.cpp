#include "GUI.h"
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "GLAUX.LIB")

int main(int argc, char** argv) {
	GUI::init(argc, argv);
	GUI::run();
	return 0;
}