#include "KDQMath.h"

static double perlinArray[N_PERLIN][N_PERLIN];

void Perlin::setPerlin() {
	srand(time(NULL));
	for (int i = 0; i < N_PERLIN; ++i) {
		for (int j = 0; j < N_PERLIN; ++j) {
			int r = rand();
			perlinArray[i][j] = ((1.0 - ((r * (r * r * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0) + 1.0) / 2;
		}
	}
}

int Perlin::getPerlin(const int &x, const int &y, const int &bound) {
	int x0 = x * N_PERLIN / bound;
	int y0 = y * N_PERLIN / bound;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	return (perlinArray[x0][y0] + perlinArray[x0][y1] + perlinArray[x1][y0] + perlinArray[x1][y1]) / 4.0 * 255;
}