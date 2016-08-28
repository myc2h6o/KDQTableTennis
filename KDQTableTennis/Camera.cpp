#include "Camera.h"

void Camera::init() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100, -160, 160, 100, -40, 100, 0, 1, 0);
}