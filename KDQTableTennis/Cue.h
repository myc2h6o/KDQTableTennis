#ifndef CUE_H
#define CUE_H
#include <math.h>
#include <time.h>
#include "KDQMath.h"
#define GLUT_DISABLE_ATEXIT_HACK 
#include "GL/glut.h"

class Cue {
	friend class KDQTableTennis;
public:
	Cue(){ objCylinder = gluNewQuadric(); }
	void display(double x, double y, double z);
private:
	GLUquadricObj *objCylinder;
	double gap;
	double angle;
};

#endif