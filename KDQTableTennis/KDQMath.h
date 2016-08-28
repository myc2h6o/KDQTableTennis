#ifndef KDQ_MATH_H
#define KDQ_MATH_H

#include <stdlib.h>
#include <time.h>

#define PI 3.1415927
#define N_PERLIN 16

//perlin noise static class
class Perlin {
public:
	//set once for perlin noise array
	static void setPerlin();
	//bound should be larger than N_PERLIN
	static int getPerlin(const int &x, const int &y, const int &bound);
private:
	Perlin() {}
	~Perlin() {}
	Perlin(const Perlin&) {}
};

#endif