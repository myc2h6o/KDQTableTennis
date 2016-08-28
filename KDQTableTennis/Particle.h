#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK 
#include "GL/glut.h"

#define N_PARTICLE 32
#define MAX_LIVING_FRAME 256
#define MAX_SPEED 8

class Particle {
public:
	Particle() {}
	~Particle(){}
	void init(double x, double y, double z);
	bool move();
	void display();
private:
	double xPos, yPos, zPos;
	int vx, vy, vz;
	int living_time;
	Particle(const Particle&) {}
};

class Particles{
public:
	Particles() {}
	Particles(double x, double y, double z);
	Particles(const Particles& par) {
		for (int i = 0; i < N_PARTICLE; ++i) {
			elements[i] = par.elements[i];
		}
	};
	bool move();
	void display();
	~Particles() {}
private:
	Particle elements[N_PARTICLE];
};
#endif