#include "Cue.h"

void Cue::display(double x, double y, double z) {
	double piAngle = PI * angle / 180;
	double xAn = cos(piAngle);
	double yAn = sin(piAngle);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(x + gap * xAn, y + gap * yAn, z);
	glRotatef(90, -yAn, xAn, 0);
	gluCylinder(objCylinder, 1.5, 2.0, 80.0, 10, 3);
	glPopMatrix();
}