#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK 
#include "GL/glut.h"
#include <vector>

#define HEIGHT_GRAPH "resources/table.txt"
//[WARNING]attention for the height graph outside
#define MAX_HEIGHT 20

class Table {
	friend class KDQTableTennis;
public:
	Table();
	~Table() { delete[] height; }
	void display();
	int getLeft() { return left; }
	int getRight() { return right; }
	int getBottom() { return bottom; }
	int getTop() { return top; }
	double getHeight(double x, double y);
private:
	int left, right, bottom, top, dots;
	double colorR;
	double colorG;
	double colorB;
	int *height;
	std::vector<std::vector<double>> points;
	Table(const Table&) {}
};

#endif