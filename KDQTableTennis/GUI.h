#ifndef GUI_H
#define GUI_H
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK 
#include "GL/glut.h"
#include "KDQTableTennis.h"

class GUI {
public:
	static void init(int argc, char** argv);
	static void run() { glutMainLoop(); }
	static void destory();
private:
	static void display();
	static void reshape(int width, int height);
	static void frame();
	static void processNormalKeys(unsigned char key, int x, int y);
};

#endif