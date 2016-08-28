#include "Ball.h"

static GLUquadricObj* qobj = gluNewQuadric();

bool Ball::hitTest(Ball &ball) {
	double distance_22 = (ball.xPos - xPos)*(ball.xPos - xPos) + (ball.yPos - yPos)*(ball.yPos - yPos);
	double v_d = xSpeed * (ball.xPos - xPos) + ySpeed * (ball.yPos - yPos);
	double vpx = v_d*(ball.xPos - xPos) / distance_22;
	double vpy = v_d*(ball.yPos - yPos) / distance_22;
	double vcx = xSpeed - vpx;
	double vcy = ySpeed - vpy;

	double v_d2 = ball.xSpeed * (ball.xPos - xPos) + ball.ySpeed * (ball.yPos - yPos);
	double vpx2 = v_d2*(ball.xPos - xPos) / distance_22;
	double vpy2 = v_d2*(ball.yPos - yPos) / distance_22;
	double vcx2 = ball.xSpeed - vpx2;
	double vcy2 = ball.ySpeed - vpy2;
	if ((distance_22 <= radius * radius + 2 * radius * ball.radius + ball.radius * ball.radius) && (v_d > v_d2)) {
		xSpeed = vpx2 + vcx;
		ySpeed = vpy2 + vcy;
		ball.xSpeed = vpx + vcx2;
		ball.ySpeed = vpy + vcy2;
		return true;
	}
	return false;
}

void Ball::testBound() {
	if (xPos - radius <= leftBound || xPos + radius >= rightBound) {
		if (xPos - radius <= leftBound) xPos = leftBound + radius;
		else xPos = rightBound - radius;
		xSpeed = -xSpeed;
	}
	if (yPos - radius <= bottomBound || yPos + radius >= topBound) {
		if (yPos - radius <= bottomBound) yPos = bottomBound + radius;
		else yPos = topBound - radius;
		ySpeed = -ySpeed;
	}
}

void Ball::move() {
	xPos += xSpeed;
	yPos += ySpeed;
	zPos += zSpeed;
	double xMiu = miu * xSpeed / sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
	double yMiu = miu * ySpeed / sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
	xMiu = (xMiu > 0) ? xMiu : -xMiu;
	yMiu = (yMiu > 0) ? yMiu : -yMiu;
	if (xSpeed > xMiu)
		xSpeed -= xMiu;
	else if (-xSpeed > xMiu)
		xSpeed += xMiu;
	else
		xSpeed = 0;

	if (ySpeed > yMiu)
		ySpeed -= yMiu;
	else if (-ySpeed > yMiu)
		ySpeed += yMiu;
	else
		ySpeed = 0;
}

void Ball::display() {
	if (texName) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName);
	}
	glColor4f(colorR, colorG, colorB, 0.5);
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(qobj, radius, 10, 10);

	glPopMatrix();
	if (texName) {
		glDisable(GL_TEXTURE_2D);
	}
}