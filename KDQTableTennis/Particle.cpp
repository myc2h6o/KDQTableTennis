#include "Particle.h"

void Particle::init(double x, double y, double z) {
	xPos = x;
	yPos = y;
	zPos = z;
	vx = rand() % MAX_SPEED - MAX_SPEED / 2;
	vy = rand() % MAX_SPEED - MAX_SPEED / 2;
	vz = rand() % MAX_SPEED * 2;
	living_time = rand() % MAX_LIVING_FRAME;
}

bool Particle::move() {
	//return if the particle is still alive
	xPos += vx;
	yPos += vy;
	zPos += vz;
	if (zPos < 0) return false;
	vz -= 3;
	if(--living_time < 0) return false;
	return true;
}

void Particle::display() {
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glColor3f(0.9, 0.7, 0.3);
	glutSolidSphere(0.6, 10, 10);
	glPopMatrix();
}

Particles::Particles(double x, double y, double z) {
	for (int i = 0; i < N_PARTICLE; ++i) {
		elements[i].init(x, y, z);
	}
}

bool Particles::move() {
	int nAlive = 0;
	for (int i = 0; i < N_PARTICLE; ++i) {
		if (elements[i].move()) {
			nAlive++;
		}
	}
	if (nAlive > N_PARTICLE / 4) return true;
	else return false;
}

void Particles::display() {
	for (int i = 0; i < N_PARTICLE; ++i) {
		elements[i].display();
	}
}