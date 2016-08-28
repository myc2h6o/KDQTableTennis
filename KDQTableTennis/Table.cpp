#include "Table.h"

Table::Table() {
	//loading height graph from outside
	FILE *fp = NULL;
	fp = fopen(HEIGHT_GRAPH, "r");
	if (fp == NULL) {
		printf("loading height graph error!\n");
		exit(1);
	}
	//get number of dots of width and height and top/right
	fscanf(fp, "%d", &dots);
	fscanf(fp, "%d", &right);
	top = right;
	left = 0;
	bottom = 0;
	height = new int[dots * dots];


	//get height
	for (int i = 0; i < dots; ++i) {
		for (int j = 0; j < dots; ++j) {
			fscanf(fp, "%d", height + i*dots + j);
		}
	}
	//calculate triangle points
	double step = (double)top / (dots-1);
	double left_bottom, left_top, right_bottom, right_top;
	std::vector<double> point;
	for (int i = 1; i < dots; ++i) {
		for (int j = 1; j < dots; ++j) {
			left_bottom = height[(i - 1)*dots + j - 1];
			left_top = height[i * dots + j - 1];
			right_bottom = height[(i - 1) * dots + j];
			right_top = height[i * dots + j];
			point.clear(); point.push_back((j - 1)*step);	point.push_back(i*step);		point.push_back(left_top);		points.push_back(point);
			point.clear(); point.push_back((j - 1)*step);	point.push_back((i - 1)*step);	point.push_back(left_bottom);	points.push_back(point);
			point.clear(); point.push_back(j*step);			point.push_back((i - 1)*step);	point.push_back(right_bottom);	points.push_back(point);
			point.clear(); point.push_back((j - 1)*step);	point.push_back(i*step);		point.push_back(left_top);		points.push_back(point);
			point.clear(); point.push_back(j*step);			point.push_back((i - 1)*step);	point.push_back(right_bottom);	points.push_back(point);
			point.clear(); point.push_back(j*step);			point.push_back(i*step);		point.push_back(right_top);		points.push_back(point);
		}
	}
	fclose(fp);

	//color
	colorR = 0.0;
	colorG = 0.3;
	colorB = 0.9;
}

double Table::getHeight(double x,double y) {
	if (x > right || y > top) return 0;
	double step = right / (dots - 1);
	if (x + y - int(y / step) * step - int(x / step) * step < step) {
		double x0 = int(y / step) * step;
		double y0 = int(x / step) * step;
		double h0 = height[int(y / step) * dots + int(x / step)];
		double h1 = height[(int(y / step) + 1) * dots + int(x / step)];
		double h2 = height[int(y / step) * dots + int(x / step) + 1];
		return ((y - x0)*(h1 - h0) + (x - y0)*(h2 - h0)) / step + h0;
	}
	else {
		double x0 = (int(y / step) + 1) * step;
		double y0 = (int(x / step) + 1) * step;
		double h0 = height[(int(y / step) + 1) * dots + int(x / step) + 1];
		double h1 = height[int(y / step) * dots + int(x / step) + 1];
		double h2 = height[(int(y / step) + 1) * dots + int(x / step)];
		return ((x0 - y)*(h1 - h0) + (y0 - x)*(h2 - h0)) / step + h0;
	}
}


void Table::display() {
	glColor3f(colorR, colorG, colorB);

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	int size = points.size();
	int cnt = 3;
	for (int i = 0; i < size; ++i) {
		//color according to height
		glColor3f(colorR + 0.8 * points[i][2] * (1.0 - colorR) / MAX_HEIGHT,
				  colorG + 0.8 * points[i][2] * (1.0 - colorG) / MAX_HEIGHT,
				  colorB + 0.8 * points[i][2] * (1.0 - colorB) / MAX_HEIGHT);
		if (cnt == 3) {
			cnt = 0;
			int x1 = points[i + 1][0] - points[i][0];
			int y1 = points[i + 1][1] - points[i][1];
			int z1 = points[i + 1][2] - points[i][2];
			int x2 = points[i + 2][0] - points[i + 1][0];
			int y2 = points[i + 2][1] - points[i + 1][1];
			int z2 = points[i + 2][2] - points[i + 1][2];
			float sum = y1*z2 - y2*z1 + x1*z2 - x2*z1 + x1*y2 - x2*y1;
			glNormal3f((y1*z2 - y2*z1) / sum, (x1*z2 - x2*z1) / sum, (x1*y2 - x2*y1) / sum);
		}
		glVertex3f(points[i][0], points[i][1], points[i][2]);
	}
	glEnd();

	glColor3f(0.4, 0.4, 0.9);
	glBegin(GL_QUADS);
	glVertex3f(left, bottom-4, MAX_HEIGHT);
	glVertex3f(left, bottom-4, 0);
	glVertex3f(right, bottom-4, 0);
	glVertex3f(right, bottom-4, MAX_HEIGHT);

	glVertex3f(left, top, MAX_HEIGHT);
	glVertex3f(left, top, 0);
	glVertex3f(right, top, 0);
	glVertex3f(right, top, MAX_HEIGHT);

	glVertex3f(left, top, MAX_HEIGHT);
	glVertex3f(left, top, 0);
	glVertex3f(left, bottom-4, 0);
	glVertex3f(left, bottom-4, MAX_HEIGHT);

	glVertex3f(right, top, MAX_HEIGHT);
	glVertex3f(right, top, 0);
	glVertex3f(right, bottom-4, 0);
	glVertex3f(right, bottom-4, MAX_HEIGHT);

	glEnd();
	glPopMatrix();
}