#include "Flag.h"

void Flag::init(GLuint texture, int height, int stride, int strength) {
	/*
	 *height : height of flag in z axis
	 *stide : stride between two point in x axis
	 *strength : swing in y axis
	 */
	str = strength;
	texName = texture;
	//control point
	for (int i = 0; i < N_HEIGHT_SLICE; ++i) {
		for (int j = 0; j < N_STRIDE_SLICE; ++j) {
			controlPoint[i][j][0] = stride * j;
			controlPoint[i][j][1] = strength * direction[(j + i * 2) % N_DIRECTION];
			controlPoint[i][j][2] = height * i;
		}
	}
	//pole of flag
	objCylinder = gluNewQuadric();
}

void Flag::display(float x, float y, float  z, float angleX, float angleY, float angleZ, float angle) {
	//no lighting with flag
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	if(texName != 0) glBindTexture(GL_TEXTURE_2D, texName);
	glTranslatef(x, y, z);
	glRotatef(angle, angleX, angleY, angleZ);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 5, 0, 1, 15, 2, &controlPoint[0][0][0]);
	if (texName != 0) glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &textpts[0][0][0]);
	glMapGrid2f(10.0, 0.0, 1.0, 10.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 10.0, 0, 10.0);

	glTranslatef(1, 0, -20);
	gluCylinder(objCylinder, 1.0, 1.0, 20.0, 10, 3);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Flag::move() {
	for (int i = 0; i < N_HEIGHT_SLICE; ++i) {
		for (int j = 1; j < N_STRIDE_SLICE; ++j) {
			controlPoint[i][j][1] += uping[i][j - 1] * sqrt(0.2 * (str*str - (controlPoint[i][j][1] * controlPoint[i][j][1])));
			if (controlPoint[i][j][1] >= str) {
				controlPoint[i][j][1] = 0.95 * str;
				uping[i][j - 1] = -1;
			}
			else if (controlPoint[i][j][1] <= -str) {
				controlPoint[i][j][1] = -0.95 * str;
				uping[i][j - 1] = 1;
			}
		}
	}
}