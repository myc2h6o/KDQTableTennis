#ifndef FLAG_H
#define FLAG_H

#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/GLUT.H>

#define N_STRIDE_SLICE  5
#define N_HEIGHT_SLICE  2
#define N_DIRECTION     4


class Flag {
public:
	void init(GLuint texture, int height, int stride, int strength);
	void display(float x, float y, float  z, float  angleX, float  angleY, float angleZ, float angle);
	void move();
private:
	int str;
	GLuint texName;
	GLfloat controlPoint[N_HEIGHT_SLICE][N_STRIDE_SLICE][3];
	GLfloat textpts[2][2][2] = { { { 0.0,0.0 },{ 1.0,0.0 } },{ { 0.0,1.0 },{ 1.0,1.0 } } };
	int uping[N_HEIGHT_SLICE][N_DIRECTION] = {
		{ -1, 1, 1, -1 },
		{ -1, 1, 1, -1 },
	};
	int direction[N_DIRECTION] = { 0, 1, 0, -1 };
	//pole of flag
	GLUquadricObj *objCylinder;
};


#endif