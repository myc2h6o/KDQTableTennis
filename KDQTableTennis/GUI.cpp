#include "GUI.h"

KDQTableTennis *game;
const double BG_R = 0.9;
const double BG_G = 0.9;
const double BG_B = 0.9;
const double BG_A = 0.0;
const double VIEW_PORT_SIZE = 10;
const double VIEW_PORT_NEAR = 20;
const double VIEW_PORT_FAR = 1000;
const float SPOT_LIGHT_X = 100.0;
const float SPOT_LIGHT_Y = 100.0;
const float SPOT_LIGHT_Z = 200.0;
const int MILLISEC_PER_FRAME = 33;
static bool spot_light_on = true;

void GUI::init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("KDQ Table Tennis");
	glClearColor(BG_R, BG_G, BG_B, BG_A);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(frame);
	glutKeyboardFunc(processNormalKeys);

	//texture and curved surface
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-VIEW_PORT_SIZE, VIEW_PORT_SIZE, -VIEW_PORT_SIZE, VIEW_PORT_SIZE, VIEW_PORT_NEAR, VIEW_PORT_FAR);
	game = new KDQTableTennis();
	Camera::init();

	//environment light
	GLfloat env_light_position[] = { 250.0f, -150.0f, 100.0f, 1.0f };
	GLfloat env_light_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, env_light_position);		//position
	glLightfv(GL_LIGHT0, GL_AMBIENT, env_light_ambient);	//environment value
	glEnable(GL_LIGHT0);

	//spot light on white ball
	float spot_light_position[] = { SPOT_LIGHT_X, SPOT_LIGHT_Y, SPOT_LIGHT_Z, 1.0f};
	float spot_light_direction[] = { 0.0f, 0.0f, -1.0 };
	float spot_diffuse_light[] = { 0.8f, 0.8f, 0.8f, 0.5f };
	float spot_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.5f };
	glLightfv(GL_LIGHT1, GL_POSITION, spot_light_position);//position
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_light_direction);//direction
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 6.0f);	//degree * 2
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1f); //exponent value, focus better when less
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spot_diffuse_light); //diffuse reflection
	glMaterialfv(GL_FRONT, GL_SPECULAR, spot_mat_specular);	//specular reflection
	glEnable(GL_LIGHT1);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);	//focus better on 128 (range is [0, 128])
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

void GUI::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game->display();
	glFlush();
}

void GUI::reshape(int width, int height) {
	if (height == 0) height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width > height)
		glFrustum(-VIEW_PORT_SIZE * width / height, VIEW_PORT_SIZE * width / height, -VIEW_PORT_SIZE, VIEW_PORT_SIZE, VIEW_PORT_NEAR, VIEW_PORT_FAR);
	else
		glFrustum(-VIEW_PORT_SIZE, VIEW_PORT_SIZE, -VIEW_PORT_SIZE * height / width, VIEW_PORT_SIZE * height / width, VIEW_PORT_NEAR, VIEW_PORT_FAR);
	Camera::init();
}

void GUI::frame() {
	double start = clock();
	game->process();
	//refresh direction of spot light
	float spot_light_direction[] = { game->balls[CUE_BALL].getXPos() - SPOT_LIGHT_X, game->balls[CUE_BALL].getYPos() - SPOT_LIGHT_Y, -SPOT_LIGHT_Z };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_light_direction);
	display();
	
	double time_during = clock() - start;
	double time_wait = MILLISEC_PER_FRAME - time_during * 1000 / CLOCKS_PER_SEC;
	if (time_wait > 0) {
		Sleep(time_wait);
	}
}

void GUI::processNormalKeys(unsigned char key, int x, int y){
	if (key == 'a') {
		game->changeCueAngle(-2.0);
	}
	else if (key == 'd') {
		game->changeCueAngle(2.0);
	}
	else if (key == 'w') {
		game->hitCueBall();
	}
	else if (key == ' ') {
		if (spot_light_on) {
			glDisable(GL_LIGHT1);
			spot_light_on = false;
		}
		else {
			glEnable(GL_LIGHT1);
			spot_light_on = true;
		}
	}
}

void GUI::destory() { delete game; }