#ifndef BALL_H
#define BALL_H
#include <math.h>
#include "KDQMath.h"
#define GLUT_DISABLE_ATEXIT_HACK 
#include "GL/glut.h"

class Ball {
	friend class KDQTableTennis;
public:
	void move();
	bool hitTest(Ball &ball);
	void testBound();
	void display();
	double getXPos() { return xPos; }
	double getYPos() { return yPos; }
	void setZPos(double pos) { zPos = pos; }
private:
	//position and radius
	double xPos;
	double yPos;
	double zPos;
	double radius;
	//moving bound
	double leftBound;
	double rightBound;
	double bottomBound;
	double topBound;
	//moving speed
	double xSpeed;
	double ySpeed;
	double zSpeed;
	double maxSpeed;
	double miu;
	//color
	double colorR;
	double colorG;
	double colorB;
	//texture
	GLuint texName;
};

#endif